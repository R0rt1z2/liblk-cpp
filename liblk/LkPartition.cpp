#include <sstream>
#include <stdexcept>

#include <Magic.h>
#include <LkPartition.h>
#include <Utils.h>

LkPartition LkPartition::parse(const std::vector<uint8_t>& buffer, const size_t offset) {
    if (buffer.size() < 4) throw std::runtime_error("wrong buffer size");
    const uint32_t magic = Utils::read_le32(buffer, 0);

    size_t start_offset;
    if (Magic::is(magic, Magic::BFBF)) {
        // This is usually universal for BFBF images
        start_offset = 0x4040;
    } else if (Magic::is(magic, Magic::SSSS)) {
        if (buffer.size() < 48) {
            throw std::runtime_error("wrong buffer size");
        }
        start_offset = Utils::read_le32(buffer, 44);
        if (start_offset >= buffer.size()) {
            throw std::runtime_error("start offset out of bounds");
        }
    } else {
        start_offset = offset;
    }

    auto header = LkHeader::parse(buffer, start_offset);

    bool has_ext = false;
    std::unique_ptr<LkExtHeader> ext_header = nullptr;
    size_t header_size = 512;
    size_t data_size = header.data_size;

    if (start_offset + 48 <= buffer.size()) {
        uint32_t ext_magic = Utils::read_le32(buffer, start_offset + 48);
        if (Magic::is(ext_magic, Magic::EXT_MAGIC)) {
            has_ext = true;
            ext_header = std::make_unique<LkExtHeader>(
                LkExtHeader::parse(buffer, start_offset + 52));
            header_size = ext_header->header_size;
            data_size |= ext_header->data_size << 32;
        }
    }

    if (offset + header_size + data_size > buffer.size()) {
        std::ostringstream oss;
        oss << "partition out of bounds (offset=0x" << std::hex << offset
            << ", header_size=0x" << header_size
            << ", data_size=0x" << data_size << ")";
        throw std::runtime_error(oss.str());
    }

    std::vector data(
        // We skip the header because we already parsed it and we don't need it anymore :)
        std::next(buffer.begin(), static_cast<std::ptrdiff_t>(start_offset + header_size)),
        std::next(buffer.begin(), static_cast<std::ptrdiff_t>(start_offset + header_size + data_size))
    );

    size_t end_offset = offset + header_size + data_size;
    size_t alignment = has_ext ? ext_header->alignment : 8;
    if (alignment && (end_offset % alignment)) {
        end_offset += alignment - (end_offset % alignment);
    }

    return {std::move(header), std::move(data), has_ext, end_offset, std::move(ext_header)};
}

void LkPartition::print() const {
    header.print();
    if (has_ext && ext_header) {
        ext_header->print();
    }
}