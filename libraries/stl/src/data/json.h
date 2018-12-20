/**
 * @file json.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef STL_JSON_H
#define STL_JSON_H

#include <json/json.h>

#define STL_PRINT_JSON(json)                                    \
    do { Json::StreamWriterBuilder write_builder;               \
    auto data { Json::writeString(write_builder, json) };       \
    printf("%s\n\n", data.data()); } while (false)

#endif /* STL_JSON_H */
