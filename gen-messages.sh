#!/usr/bin/env bash

find messages/terminal -type f -exec flatc --cpp -o module-quill/src/message -I messages/terminal {} +
find messages/terminal -type f -exec flatc --js --no-js-exports -o web/frontend/web/js/message -I messages/terminal {} +
