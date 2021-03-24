FROM ubuntu:latest as build
ENV DEBIAN_FRONTEND=noninteractive TZ="Europe/Oslo"
RUN apt update && apt install -y git libasound-dev g++ cmake
RUN mkdir /q && cd /q && git clone --recurse-submodules https://github.com/cycfi/q.git .
RUN mkdir /q/build && cd /q/build && cmake -G"CodeBlocks - Unix Makefiles" ../
RUN cd /q/build && make && cd example && make

FROM ubuntu:latest
RUN apt update && apt install -y libasound-dev
RUN mkdir /q && mkdir /q/example
WORKDIR /q/example
COPY --from=build /q/build/example .
CMD /q/example/example_list_devices
