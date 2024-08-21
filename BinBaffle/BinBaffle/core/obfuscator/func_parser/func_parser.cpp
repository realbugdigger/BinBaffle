#include "func_parser.h"
#include "../../globals.h"
#include "common/combiner.h"
#include "pdb/pdb.h"
#include "../../../external/zasm/x86/emitter.hpp"

namespace func_parser {
    void parse() {
        if (globals::pdb_enabled)
        {
            parse_pdb();
        }
        if (globals::map_enabled)
        {
            parse_map();
        }
    }

    void parse_pdb() {
        // Obtaining base of code
        const auto base_of_code = image_->raw_image->get_nt_headers()->optional_header.base_of_code;

        // Trying to parse from a custom pdb path first
        if (!globals::pdb_path.empty()) {
            if (push(pdb::discover_functions(globals::pdb_path, base_of_code))) {
                return;
            }
        }

        // Trying to parse from a codeview path
        if (push(pdb::discover_functions(image_->find_codeview70(), base_of_code))) {
            return;
        }

        // Trying to find .pdb near the executable
        auto pdb_path = globals::binary_path;
        pdb_path = pdb_path.replace_extension(".pdb");
        push(pdb::discover_functions(pdb_path, base_of_code));
    }
    
    void parse_map() {
        // Trying to parse from a custom path first
        if (!globals::map_path.empty()) {
            if (push(map::discover_functions(config_.map_path.value(), image_->sections))) {
                return;
            }
        }

        // Trying to find .map file near the binary
        auto map_path = globals::binary_path;
        map_path = map_path.replace_extension(".map");
        push(map::discover_functions(map_path, image_->sections));
    }

    void collect_functions() {
        // Parsing from all sources possible
        parse();

        // Combining and sanitizing results
        func_parser::function_list_ = func_parser::combiner::combine_function_lists(func_parser::function_lists_);
        
        func_parser::function_list_ = sanitizer::sanitize_function_list(func_parser::function_list_, func_parser::image_);
        
        // If 0 functions found
        if (func_parser::function_list_.empty()) {
            throw std::runtime_error("parser: Parsed 0 functions in total");
        }
    }
}