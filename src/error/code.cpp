//
// Copyright (c) 2024 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Util errors
//

#include "error/code.hpp"

namespace craftpp::error {

class ErrorCategory : public std::error_category {
public:
    const char* name() const noexcept override {
        return "net error";
    }
    std::string message(int code) const override {
        switch ((Code)code) {
        case Code::ok:  return "success";
        case Code::value_required_in_maybe: return "value required";
        }
        return "unknown util error";
    }
};

const std::error_category& error_category() noexcept {
    static const ErrorCategory cat;
    return cat;
}

}
