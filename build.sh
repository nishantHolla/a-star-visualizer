#!/bin/bash

docker buildx build --load --build-arg BUILD_TYPE=$1 -t asv:$1 .
