/**
 * @file main.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include <rocket.h>

#include "main/strange_consts.h"
#include "job/job_context.h"

int main(int argc, char **argv)
{
    return rocket::application::start(argc,
                                      argv,
                                      RC_CONTEXT_CREATOR(strange::job_context),
                                      strange::consts::APP_DESCRIPTION);
}
