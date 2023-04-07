#!/bin/bash

# Edge Impulse ingestion SDK
# Copyright (c) 2022 EdgeImpulse Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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

APP_TYPE="${1}" make
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
