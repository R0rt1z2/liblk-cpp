#include <iostream>
#include <stdexcept>

#include <Utils.h>
#include <LkExtHeader.h>

LkExtHeader LkExtHeader::parse(const std::vector<uint8_t>& buffer, const size_t offset) {
    if (offset + 28 > buffer.size()) throw std::runtime_error("extension header out of bounds");

    uint32_t header_size = Utils::read_le32(buffer, offset);
    uint32_t header_version = Utils::read_le32(buffer, offset + 4);
    uint32_t image_type = Utils::read_le32(buffer, offset + 8);
    uint32_t image_list_end = Utils::read_le32(buffer, offset + 12);
    uint32_t alignment = Utils::read_le32(buffer, offset + 16);
    uint64_t data_size = Utils::read_le64(buffer, offset + 20);
    uint64_t memory_address = Utils::read_le64(buffer, offset + 28);

    return {header_size, header_version, image_type, image_list_end, alignment, data_size, memory_address};
}

void LkExtHeader::print() const {
    std::cout << "| Ext Header Size   : " << header_size << '\n'
              << "| Ext Header Version: " << header_version << '\n'
              << "| Image Type        : " << std::hex << "0x" << image_type << std::dec << '\n'
              << "| Image List End    : " << image_list_end << '\n'
              << "| Alignment         : " << alignment << '\n'
              << "| Data Size         : " << data_size << '\n'
              << "| Memory Address    : " << std::hex << "0x" << memory_address << std::dec << '\n';
}