/**
 * @file merchandise_manager.h
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#ifndef BACKEND_MERCHANDISE_MANAGER_H
#define BACKEND_MERCHANDISE_MANAGER_H

#include <engine.h>

#include "data/merchandise.h"

namespace backend {

    class merchandise_manager {
    public:
        merchandise_manager();
        ~merchandise_manager();

        void add(data::merchandise *merchandise) noexcept;

    private:
        mutable std::timed_mutex    _mutex;

        std::unordered_map<stl::uuid, data::merchandise *>      _merchandises;

    };

}

#endif /* PROJECT_MERCHANDISE_MANAGER_H */
