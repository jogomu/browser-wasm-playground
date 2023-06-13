#!/bin/bash

docker run -it --rm -p 8000:8000 -w /code -v $(pwd):/code browser-wasm-playground /bin/bash --init-file /emsdk/emsdk_env.sh
