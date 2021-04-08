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
