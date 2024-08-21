#pragma once

#include "../../pe/pe.h"

/*
    The func_parser module is essentially reading the start and end Relative Virtual Addresses (RVAs) of functions from different sources (MAP or PDB).
    
    So, the func_parser is using these two types of files to locate the positions (addresses) of all functions in the code. 
    This is a crucial first step for the obfuscation process, as it identifies what areas of the binary code correspond to which functions in the source code, 
    providing a map to guide successive stages of the obfuscation process.

    Further, RVAs are often used in PE files because they are relative to the image base of the module when it is loaded into memory. 
    By using RVAs, the parser does not need to know the exact addresses where the code will be loaded, and thus increases the portability of the executable.
*/
//template <pe::raw_image_t Img>
namespace func_parser {
    Img* image_ = nullptr;
    std::vector<function_list_t> function_lists_ = {};
    function_list_t function_list_ = {}; // function_lists_ combined and sanitized basically

    void parse();
    void parse_pdb();
    void parse_map();

    void collect_functions();
}