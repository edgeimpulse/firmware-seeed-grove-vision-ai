#!/bin/bash

set -e

cd Synopsys_PA8535_EM9D_DFSS_SDK_3.3/

if [ "${1}" == "clean" ];
then
    make clean
    if [ $? -ne 0 ]; then
        echo "Clean error"
        exit 1
    fi
    exit 0
fi

APP_TYPE="${1}" make -j ${MAKE_JOBS:-$(nproc)}
if [ $? -ne 0 ]; then
    echo "Build error"
    exit 1
fi

make flash
if [ $? -ne 0 ]; then
    echo "Error creating flash image"
    exit 1
fi

# Create resulting UF2 file in the root directory
python3 tools/ufconv/uf2conv.py -t 0 -c tools/image_gen_cstm/output/output.img -o ../firmware.uf2
if [ $? -ne 0 ]; then
    echo "Error converting image to UF2 format"
    exit 1
fi
