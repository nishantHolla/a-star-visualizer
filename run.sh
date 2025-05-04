#!/bin/bash

docker run --name asv-container \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix asv:$1 ./asv $@
docker stop asv-container
docker rm asv-container
