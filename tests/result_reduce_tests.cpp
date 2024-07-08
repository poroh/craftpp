//
// Copyright (c) 2024 Dmitry Poroh
// All rights reserved.
// Distributed under the terms of the MIT License. See the LICENSE file.
//
// Result reduce Tests
//

#include <gtest/gtest.h>
#include <memory>
#include <queue>
#include "craftpp/result/reduce.hpp"

namespace craftpp::test {

class ResultReduceTest : public ::testing::Test {
public:
    template<typename T>
    using Result = result::Result<T>;
    using RVI = Result<int>;
};

TEST_F(ResultReduceTest, basic) {
    std::vector<int> v { 1, 2, 3 };
    auto r = result::reduce(v.begin(), v.end(), 0, [&](int acc, int v) -> Result<int> {
        return acc + v;
    });
    ASSERT_TRUE(r.is_ok());
    EXPECT_EQ(r.unwrap(), 6);
}

}
