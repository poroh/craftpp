//
// Copyright (c) 2023-2024 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Useful string view algorithms
//

#pragma once

#include <string_view>
#include <utility>
#include <sstream>
#include <vector>
#include "craftpp/maybe/maybe.hpp"

namespace craftpp::string {

using SV = std::string_view;
using MaybeSV = maybe::Maybe<SV>;
using PairSV = std::pair<SV, SV>;
using MaybePairSV = maybe::Maybe<PairSV>;

// Safe version of std::string_view::remote_prefix
MaybeSV remote_prefix(SV, size_t sz);

// Split string_view using sep
MaybePairSV split(SV, char sep);

// Split using sep - all occurance
template<template <typename...> class Result = std::vector>
Result<SV> split_all(SV, char sep);

// Join string views with sep
template<typename Container>
std::string join(const Container&, const std::string& sep);

//
// implementation
//
inline MaybeSV remove_prefix(SV sv, size_t sz) {
    if (sz > sv.size()) {
        return maybe::none();
    }
    sv.remove_prefix(sz);
    return sv;
}

inline MaybePairSV split(SV sv, char sep) {
    if (auto pos = sv.find(sep); pos != SV::npos) {
        auto first = SV{sv.data(), pos};
        return remove_prefix(sv, pos + 1)
            .fmap([&](const SV& second) {
                return std::make_pair(std::move(first), std::move(second));
            });
    }
    return maybe::none();
}

template<template <typename...> class Result>
Result<SV> split_all(SV sv, char sep) {
    Result<SV> result;
    while (!sv.empty()) {
        sv = split(sv, sep).fmap([&](auto&& pair) {
            result.emplace_back(std::move(pair.first));
            return pair.second;
        }).value_or_call([&] {
            result.emplace_back(std::move(sv));
            return SV{};
        });
    }
    return result;
}

template<typename Container>
std::string join(const Container& c, const std::string& sep) {
    std::ostringstream sstr;
    for (auto it = c.begin(); it != c.end(); ++it) {
        sstr << (it == c.begin() ? "" : sep) << *it;
    }
    return sstr.str();
}

}
