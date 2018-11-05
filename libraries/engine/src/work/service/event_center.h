//
// Created by Feo on 30/10/2018.
//

#ifndef ENGINE_EVENT_CENTER_H
#define ENGINE_EVENT_CENTER_H

#include <stl.h>

namespace engine {

    class event_stream;

    /**
     * event_binding
     */
    class event_binding final {
    public:
        STL_DECLARE_SMARTPOINTERS(event_binding)
        STL_DELETE_ALL_DEFAULT(event_binding)

        explicit event_binding(event_stream *stream) noexcept;
        ~event_binding();

    private:
        event_stream *      _stream;

    };

    /**
     * event_stream
     */
    class event_stream {
    public:
        virtual ~event_stream() = default;

    private:
        friend class event_binding;

        virtual void unbind(event_binding *binding) noexcept = 0;

    };

    /**
     * empty_event_stream
     */
     class empty_event_stream : public event_stream {
     public:
         STL_DECLARE_SMARTPOINTERS(empty_event_stream)
         STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(empty_event_stream)

         empty_event_stream() :
                 _is_iterate { false },
                 _functions {},
                 _to_remove {}
         {}

         virtual ~empty_event_stream() = default;

         inline event_binding::uptr&& bind(std::function<void()>&& fn) noexcept {
             auto binding = event_binding::make_unique(this);
             _functions.insert({ binding.get(), std::move(fn) });
             return std::move(binding);
         }

         inline void fire() noexcept {
             for (auto pair: _functions) {
                 pair.second();
             }

             while (!_to_remove.empty()) {
                 auto it = _functions.find(_to_remove.front());
                 if (it != _functions.end()) {
                     _functions.erase(it);
                 }
                 _to_remove.pop();
             }
         }

     private:
         bool                                                                   _is_iterate;
         std::unordered_map<event_binding *, std::function<void()>>             _functions;
         std::queue<event_binding *>                                            _to_remove;

         inline void unbind(event_binding *binding) noexcept final {
             if (_is_iterate) {
                 _to_remove.push(binding);
             } else {
                 auto it = _functions.find(binding);
                 if (it != _functions.end()) {
                     _functions.erase(it);
                 }
             }
         }

     };

    /**
     * arg_event_stream
     */
    template<typename... Args>
    class arg_event_stream : public event_stream {
    public:
        STL_DECLARE_SMARTPOINTERS(arg_event_stream<Args...>)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(arg_event_stream)

        arg_event_stream() :
                _is_iterate { false },
                _functions {},
                _to_remove {}
        {}

        virtual ~arg_event_stream() = default;

        inline event_binding::uptr&& bind(std::function<void(Args&&...)>&& fn) noexcept {
            auto binding = event_binding::make_unique(this);
            _functions.insert({ binding.get(), std::move(fn) });
            return std::move(binding);
        }

        inline void fire(Args&&... args) noexcept {
            for (auto pair: _functions) {
                pair.second(std::forward<Args>(args)...);
            }

            while (!_to_remove.empty()) {
                auto it = _functions.find(_to_remove.front());
                if (it != _functions.end()) {
                    _functions.erase(it);
                }
                _to_remove.pop();
            }
        }

    private:
        bool                                                                    _is_iterate;
        std::unordered_map<event_binding *, std::function<void(Args&&...)>>     _functions;
        std::queue<event_binding *>                                             _to_remove;

        inline void unbind(event_binding *binding) noexcept final {
            if (_is_iterate) {
                _to_remove.push(binding);
            } else {
                auto it = _functions.find(binding);
                if (it != _functions.end()) {
                    _functions.erase(it);
                }
            }
        }

    };

}

#endif /* ENGINE_EVENT_CENTER_H */
