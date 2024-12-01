#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>
#include <string>

#include <Common.h>
#include <LkPartition.h>

class LkImage {
private:
    std::vector<uint8_t> lk_contents;
    std::vector<LkPartition> partitions;

    std::map<std::string, int> name_counts;

public:
    explicit LkImage(const std::string& path);

    void parsePartitions(bool rename_duplicates);

    void applyPatch(const std::vector<uint8_t>& needle, const std::vector<uint8_t>& patch);

    void printPartitionList() const;

    const LkPartition* getPartitionByName(const std::string& name) const;
};
