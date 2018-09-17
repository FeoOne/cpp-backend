/**
 * @file main.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <rocket.h>

#include "main/quill_consts.h"
#include "job/job_context.h"

int main(int argc, char **argv)
{
    return rocket::application::start(argc,
                                      argv,
                                      RC_CONTEXT_CREATOR(quill::job_context),
                                      quill::consts::APP_DESCRIPTION);
}
