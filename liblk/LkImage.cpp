#include <algorithm>
#include <fstream>
#include <iostream>

#include <LkImage.h>

LkImage::LkImage(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("could not open file");

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size < 0) throw std::runtime_error("invalid file size");
    if (static_cast<size_t>(size) > lk_contents.max_size()) {
        throw std::runtime_error("file too large to fit in memory");
    }

    lk_contents.resize(static_cast<size_t>(size));
    file.read(reinterpret_cast<char*>(lk_contents.data()), size);
    file.close();

    if (!file) throw std::runtime_error("error reading file");
}

void LkImage::parsePartitions(bool rename_duplicates) {
    size_t offset = 0;

    while (offset < lk_contents.size()) {
        try {
            auto partition = LkPartition::parse(lk_contents, offset);
            if (partition.has_ext && partition.ext_header->image_list_end) {
                // We reached the end of the partition list
                partitions.push_back(std::move(partition));
                break;
            }

            if (rename_duplicates) {
                auto& name = partition.header.name;
                int& count = name_counts[name];
                if (count > 0) {
                    partition.header.name += " (" + std::to_string(count) + ")";
                }
                ++count;
            }

            partitions.push_back(std::move(partition));

            offset = partitions.back().end_offset;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing partition: " << e.what() << '\n';
            break;
        }
    }
}

void LkImage::applyPatch(const std::vector<uint8_t>& needle, const std::vector<uint8_t>& patch) {
    const auto it = std::search(lk_contents.begin(),
        lk_contents.end(), needle.begin(), needle.end());
    if (it == lk_contents.end()) throw std::runtime_error("needle not found");

    const std::ptrdiff_t offset = std::distance(lk_contents.begin(), it);
    std::copy(patch.begin(), patch.end(), lk_contents.begin() + offset);
}


void LkImage::printPartitionList() const {
    for (const auto& partition : partitions) {
        std::cout << "-----------------------------\n";
        partition.print();
        if (&partition == &partitions.back()) {
            std::cout << "-----------------------------\n";
        }
    }
}

const LkPartition* LkImage::getPartitionByName(const std::string& name) const {
const auto it = std::find_if(partitions.begin(), partitions.end(),
                       [&name](const LkPartition& partition) {
                           return partition.header.name == name;
                       });

    return it != partitions.end() ? &(*it) : nullptr;
}