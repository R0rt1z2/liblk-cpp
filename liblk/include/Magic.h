#pragma once

#include <cstdint>

class Magic {
public:
    enum Value : uint32_t {
        MAGIC = 0x58881688,
        EXT_MAGIC = 0x58891689,
        SSSS = 0x53535353,
        BFBF = 0x42464246
    };

    static bool is(const uint32_t value, const Value magic) {
        return value == static_cast<uint32_t>(magic);
    }
};
