#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

struct ROMHeader {
    uint8_t magic[4];      // «NCSD» для .3ds
    uint8_t device_id[8];
    uint64_t size;
    uint32_t partition_table[8]; // Указатели на разделы
    uint8_t flags[8];
};

class ROMLoader {
public:
    bool load_rom(const std::string& filepath);
    bool is_valid_rom() const;
    const ROMHeader& get_header() const;

private:
    ROMHeader header;
    std::vector<uint8_t> content;
    std::string file_type;

    bool parse_3ds_file();
    bool parse_cia_file();
    bool parse_3dsx_file();
    bool decrypt_content();
};
