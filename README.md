# Seeed Studio Grove Vision AI & SenseCAP A1101 firmware

[Edge Impulse](https://www.edgeimpulse.com) enables developers to create the next generation of intelligent device solutions with embedded Machine Learning. This repository contains the Edge Impulse firmware for the Seeed Studio Grove Vision AI module and for the SenseCAP A1101. This device supports all Edge Impulse features, including ingestion, remote management, and inferencing.

See our tutorials on how to use both devices with Edge Impulse Studio
* [Grove Vision AI Module](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/seeed-grove-vision-ai)
* [SenseCAP A1101](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/seeed-sensecap-a1101)

---
**NOTE**

If you are using the Grove Vision AI module or SenseCAP A1101 with Edge Impulse for the first time, upgrade the firmware on the USB-UART BL702 converter.

1. Download [the following firmware](https://cdn.edgeimpulse.com/build-system/BL702-firmware-grove-vision-ai.zip) from Edge Impulse CDN server.
2. Follow [the instruction to flash the BL702 firmware](https://wiki.seeedstudio.com/Grove-Vision-AI-Module/#update-bl702-chip-firmware).

---

## Source code organization

* You can find the main firmware source code here:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_visionai`
    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_sensecap`

* To build the firmware, use the following makefile:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/makefile` and pass `APP_TYPE` (one of: `edge_impulse_visionai` or `edge_impulse_cansecap`)

* If you want to deploy your model (exported as a `C++ Library` from Studio), extract the exported `zip` file content into:

    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_visionai/ei-model`
    `Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_sensecap/ei-model`

### Reporting issues

This repository is a snapshot of the Edge Impulse internal code base, therefore PRs won't be merged. If you find any bugs or want to contribute use our [Developer Forum](https://forum.edgeimpulse.com/) to submit them.

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
    docker run -v $PWD:/app seeed-vision-ai-build edge_impulse_visionai
    ```
    Or use `edge_impulse_sensecap` as a parameter to build firmware for SenseCAP A1101.

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

1. Build the firmware and convert it into UF2 format. For Grove Vision AI:

    ```sh
    cd firmware-seeed-vision-ai-internal/Synopsys_PA8535_EM9D_DFSS_SDK_3.3
    APP_TYPE=edge_impulse_visionai make
    make flash
    python3 tools/ufconv/uf2conv.py -t 0 -c tools/image_gen_cstm/output/output.img -o firmware.uf2
    ```
    Or use `APP_TYPE=edge_impulse_sensecap` for SenseCAP A1101.

## Flashing the board

### Grove Vision AI

1. Connect Grove Vision AI Module to the host PC via USB Type-C cable
1. Double-click the `BOOT` button on the Grove Vision AI Module to enter mass storage mode
1. After this, you will see a new storage drive shown on your file explorer as **GROVEAI**
1. Drag and drop the previous **firmware.uf2** file to GROVEAI drive

Once the copying is finished, **GROVEAI** drive will disappear.

### SenseCAP A1101

1. Connect SenseCAP A1101 to the host PC via USB Type-C cable
1. Double-click the button next to the USB-C socket to enter mass storage mode
1. After this, you will see a new storage drive shown on your file explorer as **VISIONAI**
1. Drag and drop the previous **firmware.uf2** file to VISIONAI drive

## How to view the camera stream?

1. Install [Edge Impulse CLI](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-installation) tools
1. Connect your device to the PC, open the terminal/command line, and run:

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
