#include <cstring>
#include <iostream>
#include "Fonts.h"

class ROM {

public:
    ROM();
    ~ROM();

    u_int8_t* load();
    uint8_t memory[4096];

    void set_file_path(const char *path);
    const char *get_file_path();

private:
    const char *file_path_;
};

