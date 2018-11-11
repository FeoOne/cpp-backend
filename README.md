## Dependencies
* libuv
* libconfig
* zlib
* glib
* libsoup
* libuuid
* postgresql-devel (libpq)
* libgmp
* libcurl

## Setup Environment
```
$ ./envsetup.sh
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build . --target pmgen -- -j 2
$ cd tools/pmgen/pmgen -i ../message/schema/backend.pro -o ../message/generated/
$ cd -
$ cmake --build . --target backend -- -j 2
$ modules/backend/backend -c ../config/backend.cfg
```

## Project Structure
### tools
Support toolset.
##### pmgen
Protocol message code generator.
### libraries
Shared code.
##### stl
Data structs, patterns, helpers, wrappers, tools.
##### engine
Application framework.
### modules
Standalone apllications.
##### backend
Support communicate with web frontend via websocket.
