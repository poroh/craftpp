//
// Copyright (c) 2024 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Reduce elements of containers
//

#include <craftpp/result/result.hpp>
#include <craftpp/maybe/maybe.hpp>
#include <iostream>

namespace craftpp::result {

template<typename Iter, typename Accumulator, typename Function>
Result<Accumulator> reduce(Iter start, Iter end, Accumulator acc, Function f) {
    for (; start != end; ++start) {
        Result<Accumulator> next = f(std::move(acc), *start);
        if (next.is_err()) {
            return next.unwrap_err();
        } else {
            acc = std::move(next.unwrap());
        }
    }
    return acc;
}

template<typename Iter, typename Function>
MaybeError reduce(Iter start, Iter end, Function f) {
    auto wf = [&](auto&&, auto&& v) {
        return f(v);
    };
    return reduce(start, end, Unit::create(), wf);
}

}

