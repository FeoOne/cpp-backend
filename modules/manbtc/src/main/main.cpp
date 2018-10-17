/**
 * @file main.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include <engine.h>

#include "main/manbtc_consts.h"
#include "job/job_context.h"

int main(int argc, char **argv)
{
    return engine::application::start(argc,
                                      argv,
                                      EX_CONTEXT_CREATOR(manbtc::job_context),
                                      manbtc::consts::APP_DESCRIPTION);
}
