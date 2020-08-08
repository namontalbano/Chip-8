#include <cstring>
#include <iostream>
#include "Fonts.h"

class ROM {

public:

    ROM();

    uint8_t *getMemory() { return _memory; }

    void load();
    void setFilePath(const char *path);

    void setReloaded(bool reloaded);
    bool isReloaded() { return _reload; }

private:
    const char *_filePath;
    uint8_t _memory[4096];
    bool _reload;
};

