#include "ei_ram_memory.h"

#if defined(__GNUC__)
uint8_t EiRamMemory::ram_memory[RAM_TOTAL_SIZE]__attribute__((section (".ram_memory")));
#else
#pragma Bss(".ram_memory")
uint8_t EiRamMemory::ram_memory[RAM_TOTAL_SIZE];
#pragma Bss()
#endif

EiRamMemory::EiRamMemory(uint32_t config_size):EiDeviceMemory(config_size, 0, RAM_TOTAL_SIZE, RAM_BLOCK_SIZE)
{


}

uint32_t EiRamMemory::read_data(uint8_t *data, uint32_t address, uint32_t num_bytes)
{
    if (num_bytes > memory_size - address) {
        num_bytes = memory_size - address;
    }

    memcpy(data, &ram_memory[address], num_bytes);

    return num_bytes;
}

uint32_t EiRamMemory::write_data(const uint8_t *data, uint32_t address, uint32_t num_bytes)
{
    if (num_bytes > memory_size - address) {
        num_bytes = memory_size - address;
    }

    memcpy(&ram_memory[address], data, num_bytes);

    return num_bytes;
}

uint32_t EiRamMemory::erase_data(uint32_t address, uint32_t num_bytes)
{
    if (num_bytes > memory_size - address) {
        num_bytes = memory_size - address;
    }

    memset(&ram_memory[address], 0, num_bytes);

    return num_bytes;
}
