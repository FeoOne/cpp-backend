Dependencies:
* libuv
* libconfig
* zlib
* glib
* libsoup
* libuuid
* postgresql-devel (libpq)

Setup:
```
$ ./init.sh
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build . --target pmgen -- -j 2
$ cd tools/pmgen/pmgen -i ../message/schema/backend.pro -o ../message/generated/
$ cd -
$ cmake --build . --target backend -- -j 2
$ cmake --build . --target database -- -j 2
$ modules/backend/backend -c ../config/backend.cfg
$ modules/backend/database -c ../config/database.cfg
```
