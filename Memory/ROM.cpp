#include "ROM.h"

ROM::ROM() {
    for (int i = 0; i < 80; ++i) {
        _memory[i] = font_set[i];
    }
}

void ROM::setFilePath(const char *path) {
    _filePath = path;
    load();
    setReloaded(true);
}

void ROM::setReloaded(bool reloaded){
    _reload = reloaded;
}

void ROM::load() {

    printf("Loading ROM: %s\n", _filePath);

    FILE* rom = std::fopen(_filePath, "rb");
    if (rom == nullptr) {
        std::cerr << "Failed to open ROM" << std::endl;
        exit(3);
    }

    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    rewind(rom);

    char* rom_buffer = (char*) malloc(sizeof(char) * rom_size);
    if (rom_buffer == nullptr) {
        std::cerr << "Failed to allocate memory for ROM" << std::endl;
        exit(3);
    }

    size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
    if (result != rom_size) {
        std::cerr << "Failed to read ROM" << std::endl;
        exit(3);
    }

    if ((4096-512) > rom_size){
        for (int i = 0; i < rom_size; ++i) {
            _memory[i + 512] = (uint8_t)rom_buffer[i];
        }
    }
    else {
        std::cerr << "ROM too large to fit in memory" << std::endl;
        exit(3);
    }

    fclose(rom);
    free(rom_buffer);
}