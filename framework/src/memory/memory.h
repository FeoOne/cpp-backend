/**
 * @file memory.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef PROJECT_MEMORY_H
#define PROJECT_MEMORY_H

#define FW_DELETE_DEFAULT_CTOR(c)               c() = delete;
#define FW_DELETE_DEFAULT_COPY_CTOR(c)          c(const c&) = delete;
#define FW_DELETE_DEFAULT_MOVE_CTOR(c)          c(c&&) = delete;
#define FW_DELETE_DEFAULT_COPY_ASSIGN(c)        c& operator=(const c&) = delete;
#define FW_DELETE_DEFAULT_MOVE_ASSIGN(c)        c& operator=(c&&) = delete;

#define FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)    \
    FW_DELETE_DEFAULT_COPY_CTOR(c)              \
    FW_DELETE_DEFAULT_MOVE_CTOR(c)              \
    FW_DELETE_DEFAULT_COPY_ASSIGN(c)            \
    FW_DELETE_DEFAULT_MOVE_ASSIGN(c)

#define FW_DELETE_ALL_DEFAULT(c)                \
    FW_DELETE_DEFAULT_CTOR(c)                   \
    FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)

namespace framework {



}

#endif //PROJECT_MEMORY_H
