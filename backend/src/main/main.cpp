/**
 * @file main.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <cstdlib>

#include "main/application.h"

using namespace backend;

int main(int argc, char **argv)
{
    application::uptr app = application::make_unique();
    app->load_config("/Users/Feo/GDrive/FeoSoftware/bitpt/config/backend.cfg");
    app->prepare();
    app->run();

    return EXIT_SUCCESS;
}
