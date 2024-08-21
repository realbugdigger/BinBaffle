#pragma once

#include <filesystem>

#include "../common/common.h"
#include "../../../../external/linux_pe/nt/directories/dir_debug.hpp"

//https://llvm.org/docs/PDB/index.html

namespace func_parser::pdb {
    function_list_t discover_functions(const std::filesystem::path& pdb_path, std::uint64_t base_of_code = 0ULL);

    inline function_list_t discover_functions(const win::cv_pdb70_t* code_view, const std::uint64_t base_of_code = 0ULL) {
        // Return an empty set if there's no code view
        if (code_view == nullptr) {
            return {};
        }

        /*
        * CodeView is another format which comes into the picture. While MSF defines the structure of the overall file, 
          and PDB defines the set of streams that appear within the MSF file and the format of those streams, 
          CodeView defines the format of symbol and type records that appear within specific streams.
        */
        return discover_functions(code_view->pdb_name, base_of_code);
    }
}