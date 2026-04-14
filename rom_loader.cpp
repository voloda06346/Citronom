#include "rom_loader.h"
#include <fstream>
#include <iostream>

bool ROMLoader::load_rom(const std::string& filepath) {
    // Чтение файла
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << "\n";
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    content.resize(file_size);
    file.read(reinterpret_cast<char*>(content.data()), file_size);
    file.close();

    // Определение типа файла
    if (filepath.size() >= 4) {
        std::string ext = filepath.substr(filepath.size() - 4);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        if (ext == ".3ds") {
            file_type = "3ds";
            return parse_3ds_file();
        } else if (ext == ".cia") {
            file_type = "cia";
            return parse_cia_file();
        } else if (ext == ".3dsx") {
            file_type = "3dsx";
            return parse_3dsx_file();
        }
    }

    std::cerr << "Unsupported file type: " << filepath << "\n";
    return false;
}

bool ROMLoader::parse_3ds_file() {
    if (content.size() < sizeof(ROMHeader)) {
        std::cerr << "File too small for 3DS ROM\n";
        return false;
    }

    // Копируем заголовок
    memcpy(&header, content.data(), sizeof(ROMHeader));

    // Проверяем магическое число
    if (header.magic[0] != 'N' || header.magic[1] != 'C' ||
        header.magic[2] != 'S' || header.magic[3] != 'D') {
        std::cerr << "Invalid 3DS ROM magic\n";
        return false;
    }

    std::cout << "Loaded 3DS ROM: size=" << header.size << " bytes\n";

    // Здесь должна быть расшифровка (AES) и загрузка разделов
    // В реальной реализации потребуется работа с ключами шифрования

    return true;
}

bool ROMLoader::parse_cia_file() {
    std::cerr << "CIA parsing not implemented yet\n";
    // Реализация требует парсинга структуры CIA:
    // - Заголовок CIA
    // - Ticket
    // - TMD (Title Metadata)
    // - Контентные разделы (CXI, CFA)
    return false;
}

bool ROMLoader::parse_3dsx_file() {
    std::cerr << "3DSX parsing not implemented yet\n";
    // 3DSX имеет простой заголовок ELF‑подобной структуры
    return false;