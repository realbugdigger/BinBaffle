#include "func_parser.h"
#include "../../globals.h"

namespace func_parser {
    void parse() {
        if (globals::pdb_enabled)
        {
            parse_pdb();
        }
        else {
            parse_map();
        }
    }

    void parse_pdb() {
        // Obtaining base of code
        //
        const auto base_of_code = image_->raw_image->get_nt_headers()->optional_header.base_of_code;

        // Trying to parse from a custom pdb path first
        //
        if (globals::pdb_path.has_value()) {
            if (push(pdb::discover_functions(config_.pdb_path.value(), base_of_code))) {
                return;
            }
        }

        // Trying to parse from a codeview path
        //
        if (push(pdb::discover_functions(image_->find_codeview70(), base_of_code))) {
            return;
        }

        // Trying to find .pdb near the executable
        //
        auto pdb_path = obfuscator_config_.binary_path;
        pdb_path = pdb_path.replace_extension(".pdb");
        push(pdb::discover_functions(pdb_path, base_of_code));
    }
    
    void parse_map() {

    }

    void collect_functions() {
        // Parsing from all sources possible
        parse();

        // Combining and sanitizing results
        function_list_ = combiner::combine_function_lists(function_lists_);
        
        function_list_ = sanitizer::sanitize_function_list(function_list_, image_);
        
        // If 0 functions found
        //
        if (function_list_.empty()) {
            throw std::runtime_error("parser: Parsed 0 functions in total");
        }
    }
}