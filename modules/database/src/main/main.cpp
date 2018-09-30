/**
 * @file main.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include <engine.h>

#include "main/database_consts.h"
#include "job/job_context.h"

int main(int argc, char **argv)
{
    return engine::application::start(argc,
                                      argv,
                                      EX_CONTEXT_CREATOR(database::job_context),
                                      database::consts::APP_DESCRIPTION);
}
