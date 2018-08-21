/**
 * @file glib_ex.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef GROOT_GLIB_EX_H
#define GROOT_GLIB_EX_H

#include <glib.h>

#define FW_GOBJECT_REF(obj)         obj = static_cast<decltype(obj)>(g_object_ref(obj))
#define FW_GOBJECT_UNREF(obj)       g_object_unref(obj);

namespace groot {



}

#endif /* GROOT_GLIB_EX_H */
