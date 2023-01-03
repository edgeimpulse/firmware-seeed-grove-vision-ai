# Seeed Studio Grove Vision AI firmware

[Edge Impulse](https://www.edgeimpulse.com) enables developers to create the next generation of intelligent device solutions with embedded Machine Learning. This repository contains the Edge Impulse firmware for the Seeed Studio Grove Vision AI module. This device supports all Edge Impulse features, including ingestion, remote management, and inferencing.

See our [tutorial on how to use the module with Edge Impulse Studio](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/seeed-grove-vision-ai)

---
**NOTE**

If you are using the Grove Vision AI module with Edge Impulse for the first time, upgrade the firmware on the USB-UART BL702 converter.

1. Download [the following firmware](https://cdn.edgeimpulse.com/build-system/BL702-firmware-grove-vision-ai.zip) from Edge Impulse CDN server.
2. Follow [the instruction to flash the BL702 firmware](https://wiki.seeedstudio.com/Grove-Vision-AI-Module/#update-bl702-chip-firmware).

---

## Source code organization

* You can find the main firmware source code here:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_firmware`

* To build the firmware, use the following makefile:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/makefile`

* If you want to deploy your model (exported as a `C++ Library` from Studio), extract the exported `zip` file content into:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_firmware/ei-model`

## How to build the firmware?

You can build firmware using the provided `Dockerfile` (the most straightforward solution).
Another option is a native local build.

### Build firmware using Docker

1. Make sure you have [Docker](https://www.docker.com/products/docker-desktop) installed.
1. Build the container:
   
    ```sh
    docker build -t seeed-vision-ai-build .
    ```

1. Run the build script using

    ```sh
    docker run --rm --interactive -v $PWD:/app seeed-vision-ai-build /bin/bash build-firmware.sh
    ```

1. You can find the resulting firmware in `firmware.uf2` file.

### Build using native tools

We tested this build method on Ubuntu 20.04 and Fedora 36.

1. Install the required tools

    ```sh
    sudo apt install make
    sudo apt install python3-numpy
    ```

1. Download and install the GNU toolchain for ARC processors

    ```sh
    cd ~
    wget https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases/download/arc-2020.09-release/arc_gnu_2020.09_prebuilt_elf32_le_linux_install.tar.gz
    tar -xvf arc_gnu_2020.09_prebuilt_elf32_le_linux_install.tar.gz
    export PATH="$HOME/arc_gnu_2020.09_prebuilt_elf32_le_linux_install/bin:$PATH"
    ```

1. Build the firmware and convert it into UF2 format

    ```sh
    cd firmware-seeed-vision-ai-internal/Synopsys_PA8535_EM9D_DFSS_SDK_3.3
    make
    make flash
    python3 tools/ufconv/uf2conv.py -t 0 -c tools/image_gen_cstm/output/output.img -o firmware.uf2
    ```


## Flashing the board

Below is the procedure to flash the firmware on the Grove - Vision AI Module.

1. Connect Grove - Vision AI Module to the host PC via USB Type-C cable 
1. Double-click the boot button on Grove - Vision AI Module to enter mass storage mode
1. After this, you will see a new storage drive shown on your file explorer as **GROVEAI**
1. Drag and drop the previous **firmware.uf2** file to GROVEAI drive

Once the copying is finished, **GROVEAI** drive will disappear.

## How to view the camera stream?

1. Install [Edge Impulse CLI](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-installation) tools
1. Connect your board to the PC, open the terminal/command line, and run:

    ```sh
    edge-impulse-run-impulse --debug
    ```

1. You should see an output similar to the one below. Open the link 

    ```
    Edge Impulse impulse runner v1.15.1
    [SER] Connecting to /dev/tty.usbmodem21401
    [SER] Serial is connected, trying to read config...
    [SER] Retrieved configuration
    [SER] Device is running AT command version 1.7.0

    Want to see a feed of the camera and live classification in your browser? Go to http://127.0.0.1:4915
    ```

    Open the displayed link in a browser, and you will see the preview:
