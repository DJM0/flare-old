# Flare 🔥

**Under development - doesn't really do anything yet**

Currently using the [nRF51422](https://www.nordicsemi.com/eng/Products/ANT/nRF51422) SoC (32-bit Cortex M0, 256kB/128kB embedded flash, 32kB/16kB RAM). Development is being done on a [nRF51 Development Kit (pca10028)](https://www.nordicsemi.com/eng/Products/nRF51-DK).

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

### View logs

This requires the [J-Link Software Pack](https://www.segger.com/downloads/jlink/).

```
JLinkRTTLogger -device nrf51422 -if swd -speed 4000 -RTTChannel 0 /dev/stdout
```
