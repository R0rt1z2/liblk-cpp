#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class LkExtHeader {
public:
    uint32_t header_size;
    uint32_t header_version;
    uint32_t image_type;
    uint32_t image_list_end;
    uint32_t alignment;
    uint64_t data_size;
    uint64_t memory_address;

    LkExtHeader(uint32_t header_size, uint32_t header_version, uint32_t image_type, uint32_t image_list_end,
                uint32_t alignment, uint64_t data_size, uint64_t memory_address)
        : header_size(header_size), header_version(header_version), image_type(image_type),
          image_list_end(image_list_end), alignment(alignment), data_size(data_size),
          memory_address(memory_address) {}

    static LkExtHeader parse(const std::vector<uint8_t>& buffer, size_t offset);

    void print() const;
};