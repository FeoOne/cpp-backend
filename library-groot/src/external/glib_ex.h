/**
 * @file glib_ex.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef GROOT_GLIB_EX_H
#define GROOT_GLIB_EX_H

#include <glib.h>

#define GR_GOBJECT_RETAIN(obj)      do { obj = static_cast<decltype(obj)>(g_object_ref(obj)); } while (false)
#define GR_GOBJECT_RELEASE(obj)     g_object_unref(obj)

namespace groot {



}

#endif /* GROOT_GLIB_EX_H */
