# Flare 🔥

**Under development - doesn't really do anything yet**

Wireless lighting platform for various hardware and creative applications.

Designed around Nordic's [nRF52](https://www.nordicsemi.com/eng/Products/nRF52-Series-SoC) SoC (ARM Cortex M4, Bluetooth 5, 512kB Flash, 64kB RAM), but will also work on the [nRF51](https://www.nordicsemi.com/eng/Products/nRF51-Series-SoC) series or other Zephyr [supported boards](http://docs.zephyrproject.org/boards/boards.html) (depending on which Flare features are enabled).

## Roadmap

- [x] Configurable for multiple hardware platforms
- [ ] LED Drivers
    - [ ] PWM
    - [ ] TI I²C driver IC
    - [ ] WS2812, APA102 (maybe)
    - [ ] Dummy (development)
- [ ] Control via Bluetooth Low Energy GATT
- [ ] iOS ANCS support
- [ ] [Bluetooth Mesh](https://www.bluetooth.com/specifications/mesh-specifications)
- [ ] Effects generator
- [ ] Pre-generated effect support
- [ ] Start-up memory mode
- [ ] iOS/Android app
- [ ] BLE beacon / presence awareness
- [ ] Battery management system
- [ ] Sensor support (light, temperature, motion)
- [ ] Raspberry Pi / IP gateway
- [ ] DMX interface
- [ ] Docker build environment

## Hardware & Applications

### Development kits

- nRF52
    - [PCA10040](http://docs.zephyrproject.org/boards/arm/nrf52_pca10040/doc/nrf52_pca10040.html)
- nRF51
    - [PCA10028](http://docs.zephyrproject.org/boards/arm/nrf51_pca10028/doc/nrf51_pca10028.html)
    - [BLE400](http://docs.zephyrproject.org/boards/arm/nrf51_ble400/doc/nrf51_ble400.html)
    - [micro:bit](http://docs.zephyrproject.org/boards/arm/bbc_microbit/doc/board.html)

### Lamp Jar

*Hardware in [development](https://www.instagram.com/lightlabs/).*

### Status Lamp

*Not in development yet.*

## Development setup

1. You need [Zephyr 1.11.0](http://docs.zephyrproject.org/1.11.0/getting_started/getting_started.html) installed.
2. You also need the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) (we're using `7-2017-q4-major`, but any recent should work).
3. Make sure these environment variables set:
    - `ZEPHYR_BASE`: the path to Zephyr e.g. `~/zephyr`.
    - `ZEPHYR_TOOLCHAIN_VARIANT`: `gccarmemb`.
    - `GCCARMEMB_TOOLCHAIN_PATH`: the path to gcc-arm e.g. `/usr/local/gcc-arm/gcc-arm-none-eabi-7-2017-q4-major`.
    - In fish shell, you can persist these using: `set -Ux ZEPHYR_BASE ~/zephyr`.

## Build

```
cmake -GNinja -DBOARD=nrf51_pca10028 -Bbuild -H.
```

```
ninja -C build
```

### Flash to development kit

```
ninja -C build flash
```

### View logs (nRF5 DK)

This requires the [J-Link Software Pack](https://www.segger.com/downloads/jlink/).

```
JLinkRTTLogger -device nrf51422 -if swd -speed 4000 -RTTChannel 0 /dev/stdout
```
