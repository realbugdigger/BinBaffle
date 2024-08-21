#pragma once
#include "../common/common.h"
#include "../../../util/files.h"

namespace func_parser::map {
    function_list_t discover_functions(const std::filesystem::path& map_path, const std::vector<pe::section_t>& sections);
} // namespace func_parser::map