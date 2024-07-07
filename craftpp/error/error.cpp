//
// Copyright (c) 2023 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Error library
//

#include "craftpp/error/error.hpp"
#include "craftpp/string/string_view.hpp"

namespace craftpp::error {

std::string Error::message() const {
    std::vector<std::string_view> out;
    for (auto rit = m_context.rbegin(); rit != m_context.rend(); ++rit) {
        out.emplace_back(*rit);
    }
    std::string message = m_code.message();
    out.emplace_back(message);
    return string::join(out, ": ");
}

}
