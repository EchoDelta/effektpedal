# Verdens beste effektpedal!

En (bærbar) effektboks for gitar som skal kjøre på en Raspberry Pi. Skal ha input for gitar og output for hodetelefon. Prosesserer signaler i real time.

## Plan

- [ ] Finne et audio interface for Raspberry Pi slik at man kan få gitar-input.
- [ ] Finne ut hvordan man leser ut samples fra audio interface-et.
- [ ] Få til å spille ut lyden i real time
- [ ] Legge inn mulighet for å prosessere lyd med diverse moduler / plug-ins

## Effektidéer

- [ ] Delay
- [ ] Looper
- [ ] Multitap delay
- [ ] Reverb (feks [C++ Reverb – DSP Final Project](https://nebkelectronics.wordpress.com/2019/05/07/c-reverb-dsp-final-project/))
- [ ] Fuzz!
- [ ] Flanger

## Oppsett av raspberry pi'en

https://gist.github.com/torgeir/688369351d91152a3c63a4e51135f661

## Ressurser / lenker

- https://forum.juce.com/t/audio-thru-xlr-cable-into-raspberry-pi/35452
- https://github.com/iPlug2/iPlug2OOS - alternativ til juce
- http://www.audioinjector.net/rpi-ultra
- https://www.amazon.com/dp/B01N905VOY
- https://github.com/Streampunk/naudiodon#readme
- http://www.portaudio.com/
- https://wiki.linuxaudio.org/wiki/raspberrypi

# Build the base image

```
DOCKER_HOST=ssh://pi4 docker build -f Dockerfile.base -t <dockerhub-username>/effektpedal:latest
```

Remember to update the Dockerfile.effektpedal to depend on this image ☝️

Push it to dockerhub

```
DOCKER_HOST=ssh://pi4 docker push torgeir/effektpedal:latest
```

# Run on Raspberry PI

Build the local code on the pi:

```
DOCKER_HOST=ssh://pi4 docker build -f Dockerfile.effektpedal -t compiled
```

To run it:

```
DOCKER_HOST=ssh://pi4 docker run --device=/dev/snd:/dev/snd compiled
```

Build and run on the pi:

```
DOCKER_HOST=ssh://pi4 docker build -f Dockerfile.effektpedal -t compiled . \
&& DOCKER_HOST=ssh://pi4 docker run --device=/dev/snd:/dev/snd compiled
```

To debug in a shell:

```
DOCKER_HOST=ssh://pi4 docker run --device=/dev/snd:/dev/snd -it --entrypoint /bin/bash compiled
```

# Make it persistently run on PI boot

```
DOCKER_HOST=ssh://pi4 docker run -d --restart=always --name effektpedal --device=/dev/snd:/dev/snd compiled
```

# To make redeploy possible, run this first

```
DOCKER_HOST=ssh://pi4 docker rm effektpedal
```

# All in one go

```
DOCKER_HOST=ssh://pi4 docker stop effektpedal; \
  DOCKER_HOST=ssh://pi4 docker rm effektpedal; \
  DOCKER_HOST=ssh://pi4 docker build -f Dockerfile.effektpedal -t compiled . \
  && DOCKER_HOST=ssh://pi4 docker run -d --name effektpedal --restart=always --device=/dev/snd:/dev/snd compiled
```

# Troubleshooting

## Kill the running container:

```
DOCKER_HOST=ssh://pi4 docker stop $(docker ps | tail -n 1 | awk '{print $1}')
```


## Debug docker image size

```
ncdu -X .dockerignore
```

## Prune all images

```
docker images prune -f
```


## Its rediculously loud!?


```sh
amixer sset 'Master' 50%
amixer sset 'Capture' 50%
sudo alsactl store
```