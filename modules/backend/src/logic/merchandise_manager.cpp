/**
 * @file merchandise_manager.cpp
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#include "logic/merchandise_manager.h"

namespace backend {

    merchandise_manager::merchandise_manager()
    {

    }

    merchandise_manager::~merchandise_manager()
    {

    }

    void merchandise_manager::add(data::merchandise *merchandise) noexcept
    {
        STL_UNIQUE_LOCK(lock, _mutex);
        _merchandises[merchandise->guid()] = merchandise;
    }



}
