#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

echo "Generating messages for «quill»..."
flatc -c -o ${DIR}/module-quill/src/message ${DIR}/messages/terra.fbs
echo "Done."
