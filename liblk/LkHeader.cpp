#include <iostream>
#include <cstring>
#include <stdexcept>

#include <LkHeader.h>
#include <Utils.h>

LkHeader LkHeader::parse(const std::vector<uint8_t>& buffer, const size_t offset) {
    if (offset + 48 > buffer.size()) throw std::runtime_error("Header out of bounds");

    uint32_t magic = Utils::read_le32(buffer, offset);
    uint32_t data_size = Utils::read_le32(buffer, offset + 4);
    char name_cstr[32];
    std::memcpy(name_cstr, &buffer[offset + 8], 32);
    const uint32_t addressing_mode_raw = Utils::read_le32(buffer, offset + 40);
    uint32_t memory_address = Utils::read_le32(buffer, offset + 44);

    auto mode = static_cast<AddressingMode>(static_cast<int32_t>(addressing_mode_raw));
    return {magic, data_size, std::string(name_cstr),
                    mode, memory_address};
}

void LkHeader::print() const {
    std::cout << "| Partition Name    : " << name << '\n'
              << "| Data Size         : " << data_size << '\n'
              << "| Addressing Mode   : " << static_cast<int>(addressing_mode) << '\n'
              << "| Address           : " << std::hex << "0x" << memory_address << std::dec << '\n';
}