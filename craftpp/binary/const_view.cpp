//
// Copyright (c) 2023 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Binary packet view (does not contain own data, just works over existing buffer)
//

#include <numeric>
#include "craftpp/binary/const_view.hpp"

namespace craftpp::binary {

ConstView::ByteVec ConstView::concat(const std::vector<ConstView>& views) {
    size_t sz = std::accumulate(views.begin(), views.end(),
                                size_t{0},
                                [](size_t acc, const auto& v) { return acc + v.size(); });
    ConstView::ByteVec result(sz);
    auto pos = result.begin();
    for (const auto& v: views) {
        pos = std::copy(v.begin(), v.end(), pos);
    }
    return result;
}

}
