#include <memory>

#include <LkHeader.h>
#include <LkExtHeader.h>

class LkPartition {
public:
    LkHeader header;
    std::vector<uint8_t> data;
    bool has_ext;
    size_t end_offset;
    std::unique_ptr<LkExtHeader> ext_header;

    LkPartition(LkHeader header, std::vector<uint8_t> data, bool has_ext, size_t end_offset, 
                std::unique_ptr<LkExtHeader> ext_header = nullptr)
        : header(std::move(header)), data(std::move(data)), has_ext(has_ext), end_offset(end_offset),
          ext_header(std::move(ext_header)) {}

    static LkPartition parse(const std::vector<uint8_t>& buffer, size_t offset);

    void print() const;
};