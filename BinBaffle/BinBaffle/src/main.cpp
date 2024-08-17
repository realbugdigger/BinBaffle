#include <iostream>
#include <string_view>

void print_help();

int main(const int argc, char* argv[]) {
	// check for binary arguments
    if (argc < 2) {
        print_help();
    }

    // Get the binary path, check for some meme stuff
    std::string binary_path = argv[1];
    if (binary_path == "-h" || binary_path == "--help") {
        print_help();
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