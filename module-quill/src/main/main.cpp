/**
 * @file main.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <engine.h>

#include "main/backend_const.h"
#include "job/backend_context.h"

int main(int argc, char **argv)
{
    return engine::application::start(argc,
                                      argv,
                                      EG_CONTEXT_CREATOR(backend::backend_context),
                                      backend::backend_const::APP_DESCRIPTION);
}
