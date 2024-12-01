#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

namespace Utils {
    inline uint32_t read_le32(const std::vector<uint8_t>& buffer, size_t offset) {
        return static_cast<uint32_t>(buffer[offset]) |
               (static_cast<uint32_t>(buffer[offset + 1]) << 8) |
               (static_cast<uint32_t>(buffer[offset + 2]) << 16) |
               (static_cast<uint32_t>(buffer[offset + 3]) << 24);
    }

    inline uint64_t read_le64(const std::vector<uint8_t>& buffer, size_t offset) {
        return static_cast<uint64_t>(read_le32(buffer, offset)) |
               (static_cast<uint64_t>(read_le32(buffer, offset + 4)) << 32);
    }
}
