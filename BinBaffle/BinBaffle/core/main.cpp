#include <iostream>

#include "util/files.h"
#include "pe/pe.h"
#include "globals.h"

void print_help();

int main(const int argc, char* argv[]) {
	if (argc < 2) {
        print_help();
    }

    std::string binary_path = argv[1];
    if (binary_path == "-h" || binary_path == "--help") {
        print_help();
    }

    // parse options
    for (int i = 2; i < argc; ++i) {
        std::string arg_ = argv[i];

        // PDB path
        if (arg_ == "-pdb") {
            globals::pdb_enabled = true;
            globals::pdb_path = argv[i+1]; // out of bounds ??
            continue;
        }

        // MAP path
        if (arg_ == "-map") {
            globals::map_enabled = true;
            globals::map_path = argv[i+1]; // out of bounds ??
            continue;
        }
    }

    auto file = util::read_file(binary_path);
    if (file.empty()) {
        throw std::runtime_error("Got empty binary");
    }

    auto* img_x64 = reinterpret_cast<win::image_x64_t*>(file.data());
    auto* img_x86 = reinterpret_cast<win::image_x86_t*>(file.data());

    if (!pe::isValid(img_x64)) {
        throw std::runtime_error("Invalid pe header");
    }

    if (pe::isX64(img_x64)) {
        obfuscate(img_x64);
    }
    else {
        obfuscate(img_x86);
    }
    
    return 0;
}

void print_help() {
    std::cout << "\t\t\t--- BinBaffle ---\n\n";
    std::cout << "\t\t* Making your binaries take a detour through the labyrinth of obfuscation\n\n";

    std::cout << "\tUsage: binbaffle example.exe [options]\n";
    std::cout << "\tOptions:\n";
    std::cout << "\t\t-map <MAP file>\n";
    std::cout << "\t\t-pdb <PDB file>\n";
}