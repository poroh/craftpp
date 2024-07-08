//
// Copyright (c) 2024 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Craftpp errors
//

#include <system_error>

namespace craftpp::error {

enum class Code {
    ok = 0,
    value_required_in_maybe,
};

std::error_code make_code(Code) noexcept;

const std::error_category& error_category() noexcept;

//
// inlines
//
inline std::error_code make_code(Code ec) noexcept {
    return std::error_code((int)ec, error_category());
}

}
