#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <memory>
#include <verilated.h>
#include "Vveryl_cpu_top.h"

namespace fs = std::filesystem;

extern "C" const char* get_env_value(const char* key) {
    const char* value = std::getenv(key);
    if (value == nullptr) {
        return "";
    }
    return value;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " MEMORY_FILE_PATH [CYCLE]" << std::endl;
        return 1;
    }

    std::string memory_file_path = argv[1];
    try {
        fs::path absolute_path = fs::absolute(memory_file_path);
        memory_file_path = absolute_path.string();
    } catch (const std::exception& e) {
        std::cerr << "Invalid memory file path: " << e.what() << std::endl;
        return 1;
    }

    uint64_t cycles = 0;
    if (argc >= 3) {
        std::string cycles_string = argv[2];
        try {
            cycles = std::stoull(cycles_string);
        } catch (const std::exception& e) {
            std::cerr << "Invalid cycle count: " << e.what() << std::endl;
            return 1;
        }
    }

    const char* original_env = get_env_value("MEMORY_FILE_PATH");
    setenv("MEMORY_FILE_PATH", memory_file_path.c_str(), 1);

    // top
    auto dut = std::make_unique<Vveryl_cpu_top>();

    // reset
    dut->clk = 0;
    dut->rst = 1;
    dut->eval();
    dut->rst = 0;
    dut->eval();

    if (original_env != nullptr) {
        setenv("MEMORY_FILE_PATH", original_env, 1);
    } else {
        unsetenv("MEMORY_FILE_PATH");
    }

    // loop
    dut->rst = 1;
    for (uint64_t i = 0; !Verilated::gotFinish() && (cycles == 0 || i / 2 < cycles); i++) {
        dut->clk = !dut->clk;
        dut->eval();
    }

    dut->final();
}