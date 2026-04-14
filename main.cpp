#include "rom_loader.h"
#include "emulator.h" // Ваш эмулятор

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: emulator <rom_file>\n";
        return 1;
    }

    ROMLoader loader;
    if (!loader.load_rom(argv[1])) {
        std::cerr << "Failed to load ROM\n";
        return 1;
    }

    if (!loader.is_valid_rom()) {
        std::cerr << "Invalid ROM format\n";
        return 1;
    }struct NCSDHeader {
    char magic[4];           // «NCSD»
    uint64_t media_id;       // ID носителя
    uint32_t size_low;       // Размер (младшие 32 бита)
    uint32_t size_high;      // Размер (старшие 32 бита)
    uint32_t partitions[8];   // Указатели на разделы (offset * 0x200)
    uint8_t flags[8];        // Флаги (шифрование, регион и т. д.)
    // ... другие поля
};


    Emulator emulator;

    // Передаём данные ROM в эмулятор
    // (в реальной реализации здесь будет загрузка в память эмулятора)
    emulator.load_rom_data(loader.get_header(), loader.get_content());

    // Запускаем эмуляцию
    emulator.run();

    return 0;
}
