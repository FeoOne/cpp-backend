/**
 * @file glib_ex.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef STL_GLIB_EX_H
#define STL_GLIB_EX_H

#include <glib.h>

#define STL_GOBJECT_RETAIN(obj)      do { obj = static_cast<decltype(obj)>(g_object_ref(obj)); } while (false)
#define STL_GOBJECT_RELEASE(obj)     g_object_unref(obj)

namespace stl {



}

#endif /* STL_GLIB_EX_H */
