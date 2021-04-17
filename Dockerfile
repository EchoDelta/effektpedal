FROM ubuntu:latest as build
ENV DEBIAN_FRONTEND=noninteractive TZ="Europe/Oslo"
RUN apt update && apt install -y libasound-dev g++ cmake
COPY . /effektpedal
RUN mkdir /effektpedal/build && cd /effektpedal/build && cmake -G"CodeBlocks - Unix Makefiles" ../
RUN cd /effektpedal/build && make

FROM ubuntu:latest
RUN apt update && apt install -y libasound-dev alsa-base alsa-tools alsa-utils
RUN usermod -G audio root
RUN echo pcm.!default plughw:Device >> ~/.asoundrc
RUN echo ctl.!default plughw:Device >> ~/.asoundrc
RUN mkdir /effektpedal && mkdir /effektpedal/test
WORKDIR /effektpedal/test
COPY --from=build /effektpedal/build/test .
CMD echo 1 | /effektpedal/test/EffektPedal_Test_Delay
