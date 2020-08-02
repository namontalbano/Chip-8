#include "ROM.h"

ROM::ROM() {
    for (int i = 0; i < 80; ++i) {
        memory[i] = font_set[i];
    }
}

ROM::~ROM() {}

void ROM::set_file_path(const char *path) {
    file_path_ = path;
}

const char *ROM::get_file_path() {
    return file_path_;
}

uint8_t* ROM::load() {

    printf("Loading ROM: %s\n", file_path_);

    FILE* rom = std::fopen(file_path_, "rb");
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
            memory[i + 512] = (uint8_t)rom_buffer[i];
        }
    }
    else {
        std::cerr << "ROM too large to fit in memory" << std::endl;
        exit(3);
    }

    fclose(rom);
    free(rom_buffer);

    return memory;
}