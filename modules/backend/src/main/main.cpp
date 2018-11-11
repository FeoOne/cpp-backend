/**
 * @file main.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <btc/ecc.h>
#include <engine.h>

#include "main/backend_consts.h"
#include "job/job_context.h"

int main(int argc, char **argv)
{
    btc_ecc_start();
    return engine::application::start(argc,
                                      argv,
                                      EX_CONTEXT_CREATOR(backend::job_context),
                                      backend::consts::app_description);
}
