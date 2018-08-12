/**
 * @file event.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

namespace engine {

    class event {
    public:
        event();
        ~event();

    private:

    };

    template<typename T>
    class basic_event : public event {
    public:


    };

}

#endif /* ENGINE_EVENT_H */
