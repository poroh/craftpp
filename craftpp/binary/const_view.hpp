//
// Copyright (c) 2023 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Binary packet view (does not contain own data, just works over existing buffer)
//

#pragma once

#include <string_view>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>

#include "craftpp/binary/endian.hpp"
#include "craftpp/maybe/maybe.hpp"

namespace craftpp::binary {

class ConstView : private std::basic_string_view<const uint8_t> {
    using Base = std::basic_string_view<value_type>;
public:
    using ByteT = uint8_t;
    using ByteVec = std::vector<ByteT>;
    template<typename T>
    using Maybe = craftpp::maybe::Maybe<T>;
    struct Interval {
        size_t offset;
        size_t count;
    };
    ConstView(const void *, size_t count);
    explicit ConstView(const ByteVec&);

    template<size_t SIZE>
    explicit ConstView(const std::array<ByteT, SIZE>&);

    bool contains(const Interval& i) const;
    using Base::data;
    using Base::size;
    using Base::begin;
    using Base::end;

    uint8_t assured_read_u8(size_t offset) const;
    uint16_t assured_read_u16be(size_t offset) const;
    uint32_t assured_read_u32be(size_t offset) const;
    uint64_t assured_read_u64be(size_t offset) const;
    ConstView assured_subview(size_t offset, size_t size) const;

    Maybe<uint8_t> read_u8(size_t offset) const;
    Maybe<uint16_t> read_u16be(size_t offset) const;
    Maybe<uint32_t> read_u32be(size_t offset) const;
    Maybe<uint64_t> read_u64be(size_t offset) const;
    Maybe<ConstView> subview(size_t offset) const;
    Maybe<ConstView> subview(size_t offset, size_t size) const;
    Maybe<ConstView> subview(const Interval&) const;

    static ByteVec concat(const std::vector<ConstView>&);

    bool operator==(const ConstView&) const noexcept;
};

using ByteVec = ConstView::ByteVec;

//
// inlines
//
inline ConstView::ConstView(const std::vector<uint8_t>& v)
    : ConstView(v.data(), v.size())
{}

template<size_t SIZE>
inline ConstView::ConstView(const std::array<uint8_t, SIZE>& v)
    : ConstView(v.data(), v.size())
{}

inline ConstView::ConstView(const void *buf, size_t count)
    : Base((ByteT *)buf, count)
{}


inline uint8_t ConstView::assured_read_u8(size_t offset) const {
    return data()[offset];
}

inline uint16_t ConstView::assured_read_u16be(size_t offset) const {
    uint16_t value;
    memcpy(&value, &data()[offset], sizeof(value));
    return network_to_host_u16(value);
}

inline uint32_t ConstView::assured_read_u32be(size_t offset) const {
    uint32_t value;
    memcpy(&value, &data()[offset], sizeof(value));
    return network_to_host_u32(value);
}

inline uint64_t ConstView::assured_read_u64be(size_t offset) const {
    uint64_t value;
    memcpy(&value, &data()[offset], sizeof(value));
    return network_to_host_u64(value);
}

inline ConstView ConstView::assured_subview(size_t offset, size_t count) const {
    return ConstView(data() + offset, count);
}

inline ConstView::Maybe<uint8_t> ConstView::read_u8(size_t offset) const {
    if (offset + sizeof(uint8_t) > size()) {
        return maybe::none();
    }
    return assured_read_u8(offset);
}

inline ConstView::Maybe<uint16_t> ConstView::read_u16be(size_t offset) const {
    if (offset + sizeof(uint16_t) > size() ) {
        return maybe::none();
    }
    return assured_read_u16be(offset);
}

inline ConstView::Maybe<uint32_t> ConstView::read_u32be(size_t offset) const {
    if (offset + sizeof(uint32_t) > size() ) {
        return maybe::none();
    }
    return assured_read_u32be(offset);
}

inline ConstView::Maybe<uint64_t> ConstView::read_u64be(size_t offset) const {
    if (offset + sizeof(uint64_t) > size() ) {
        return maybe::none();
    }
    return assured_read_u64be(offset);
}

inline bool ConstView::contains(const Interval& i) const {
    return i.offset + i.count <= size();
}

inline ConstView::Maybe<ConstView> ConstView::subview(size_t offset) const {
    if (offset > size()) {
        return maybe::none();
    }
    return subview(offset, size() - offset);
}

inline ConstView::Maybe<ConstView> ConstView::subview(size_t offset, size_t count) const {
    if (offset + count > size()) {
        return maybe::none();
    }
    return assured_subview(offset, count);
}

inline ConstView::Maybe<ConstView> ConstView::subview(const Interval& i) const {
    return subview(i.offset, i.count);
}

inline bool ConstView::operator==(const ConstView& other) const noexcept {
    return static_cast<const Base&>(*this) == static_cast<const Base&>(other);
}

}
