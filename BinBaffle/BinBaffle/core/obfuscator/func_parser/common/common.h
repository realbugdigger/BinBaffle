#pragma once
#include <cstdint>
#include <format>
#include <optional>
#include <string>
#include <vector>

namespace func_parser {
    struct function_t {
        constexpr function_t() = default;

        bool valid = false;
        std::string name = {};
        std::uint64_t rva = 0;
        std::optional<std::size_t> size = std::nullopt;

        // im not really sure how to properly merge stuff like
        // names. technically there could be a different size of function in the
        // different sources, but I'll let the future me to decide on this
        void merge(const function_t& another) {
            // Trying to merge size
            if (!this->size.has_value() && another.size.has_value()) {
                this->size = std::make_optional<std::size_t>(another.size.value());
            }

            // Copying name if item is in a valid state now
            if (!this->valid && another.valid) {
                this->valid = another.valid;
                this->name = another.name;
            }
        }
    };

    using function_list_t = std::vector<function_t>;
}
