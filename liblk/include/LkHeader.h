#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include <Common.h>

class LkHeader {
public:
    uint32_t magic;
    uint32_t data_size;
    std::string name;
    AddressingMode addressing_mode;
    uint32_t memory_address;

    LkHeader(uint32_t magic, uint32_t data_size, std::string name, AddressingMode mode, uint32_t mem_addr)
        : magic(magic), data_size(data_size), name(std::move(name)), addressing_mode(mode), memory_address(mem_addr) {}

    static LkHeader parse(const std::vector<uint8_t>& buffer, size_t offset);

    void print() const;
};