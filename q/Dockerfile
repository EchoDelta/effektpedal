FROM ubuntu:latest as build
ENV DEBIAN_FRONTEND=noninteractive TZ="Europe/Oslo"
RUN apt update && apt install -y git libasound-dev g++ cmake
RUN mkdir /q && cd /q && git clone --recurse-submodules https://github.com/cycfi/q.git .
RUN mkdir /q/build && cd /q/build && cmake -G"CodeBlocks - Unix Makefiles" ../
RUN cd /q/build && make && cd example && make

FROM ubuntu:latest
RUN apt update && apt install -y libasound-dev
RUN apt install -y alsa-base alsa-tools alsa-utils
RUN usermod -G audio root
RUN mkdir /q && mkdir /q/example
RUN echo pcm.!default plughw:Device >> ~/.asoundrc
RUN echo ctl.!default plughw:Device >> ~/.asoundrc
WORKDIR /q/example
COPY --from=build /q/build/example .
CMD /q/example/example_sin_synth

# DOCKER_HOST=ssh://pi4 docker run --device=/dev/snd:/dev/snd q:latest
