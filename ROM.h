#include <cstring>
#include <iostream>
#include "Fonts.h"

class ROM {

public:

    ROM();
    ~ROM();

    uint8_t memory_[4096];

    void load();
    void set_file_path(const char *path);
    const char *get_file_path();

private:

    const char *file_path_;
};

