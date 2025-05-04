FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y \
      build-essential \
      make \
      git \
      cmake \
      libgl1-mesa-dev \
      libx11-dev \
      libxcursor-dev \
      libxrandr-dev \
      libxi-dev \
      libxinerama-dev \
      libxxf86vm-dev \
      libxext-dev \
      libasound2-dev \
      libpulse-dev \
      libopenal-dev \
      libvorbis-dev \
      libmpg123-dev \
      libssl-dev && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/raysan5/raylib.git && \
    cd raylib && \
    mkdir build && cd build && \
    cmake -DBUILD_EXAMPLES=OFF .. && \
    make && make install

WORKDIR /app

COPY . .

ARG BUILD_TYPE
ARG TEST_NAME

RUN if [ "${BUILD_TYPE}" = "debug" ]; then \
  make debug; \
elif [ "${BUILD_TYPE}" = "release" ]; then \
  make release; \
fi

WORKDIR /app/out

CMD ["./asv"]
