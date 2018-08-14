/**
 * @file go_memory.h
 * @author Feo
 * @date 14/08/2018
 * @brief
 */

#ifndef ENGINE_GO_MEMORY_H
#define ENGINE_GO_MEMORY_H

#define GO_REF(obj)         static_cast<decltype(obj)>(g_object_ref(obj))
#define GO_UNREF(obj)       g_object_unref(obj);

#endif /* ENGINE_GO_MEMORY_H */
