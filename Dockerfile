FROM --platform=amd64 ubuntu:20.04

WORKDIR /app

RUN apt update && \
    apt install -y wget build-essential && \
    apt install -y python3-numpy python3-pip

RUN pip install requests

# Grab toolchain
RUN mkdir -p /opt/arc_gnu && \
    cd /opt/arc_gnu && \
    wget https://cdn.edgeimpulse.com/build-system/himax.arc_gnu_ei_prebuilt_minimal_elf32_le_linux_install.2020.09.tar.gz && \
    tar xf himax.arc_gnu_ei_prebuilt_minimal_elf32_le_linux_install.2020.09.tar.gz && \
    rm -rf himax.arc_gnu_ei_prebuilt_minimal_elf32_le_linux_install.2020.09.tar.gz

COPY build-firmware.sh /app/

# Add to PATH
ENV PATH="${PATH}:/opt/arc_gnu/arc_gnu_ei_prebuilt_minimal_elf32_le_linux_install/bin/"

ENTRYPOINT [ "/app/build-firmware.sh" ]
