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
    }

    Emulator emulator;

    // Передаём данные ROM в эмулятор
    // (в реальной реализации здесь будет загрузка в память эмулятора)
    emulator.load_rom_data(loader.get_header(), loader.get_content());

    // Запускаем эмуляцию
    emulator.run();

    return 0;
}
