//
// Copyright (c) 2023 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Tagged type is just wrapper around value
//

#pragma once

#include <utility>

#include "craftpp/types/unit.hpp"

namespace craftpp::types {

template<typename T, typename TagV = Unit>
struct Tagged {
    using Value = T;
    using Tag = TagV;

    T value;

    Tagged() = default;
    Tagged(const Tagged&) = default;
    Tagged(Tagged&&) = default;
    explicit Tagged(const T&);
    explicit Tagged(T&&);

    static Tagged move_from(T&&);
    static Tagged copy_from(const T&);

    Tagged& operator=(const Tagged&) = default;
    Tagged& operator=(Tagged&&) = default;

    bool operator==(const Tagged&) const = default;
};

//
// implementation
//
template<typename T, typename Tag>
inline Tagged<T, Tag>::Tagged(const T& v)
    : value(v)
{}

template<typename T, typename Tag>
inline Tagged<T, Tag>::Tagged(T&& v)
    : value(std::move(v))
{}

template<typename T, typename Tag>
inline Tagged<T, Tag> Tagged<T, Tag>::move_from(T&& t) {
    return Tagged{std::move(t)};
}
template<typename T, typename Tag>
inline Tagged<T, Tag> Tagged<T, Tag>::copy_from(const T& t) {
    return Tagged{t};
}

}

