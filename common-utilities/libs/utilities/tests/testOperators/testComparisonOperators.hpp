// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testComparisonOperators.hpp
// Author: crdrisko
// Date: 09/18/2020-09:01:46
// Description: Provides ~100% unit test coverage over all comparison operators

#ifndef COMMON_UTILITIES_TESTING_TESTCOMPARISONOPERATORS_HPP
#define COMMON_UTILITIES_TESTING_TESTCOMPARISONOPERATORS_HPP

#include <gtest/gtest.h>

#include "utilities.hpp"

using namespace CppUtils::Operators;

namespace CppUtils::Internal::Testing
{
    class SomewhatComparable1 : private EqualityComparable<SomewhatComparable1>
    {
    private:
        int value;

    public:
        explicit SomewhatComparable1(int Value) noexcept : value {Value} {}

        friend bool operator==(const SomewhatComparable1& lhs, const SomewhatComparable1& rhs) noexcept
        {
            return lhs.value == rhs.value;
        }
    };

    class SomewhatComparable2 : private LessThanComparable<SomewhatComparable2>
    {
    private:
        int value;

    public:
        explicit SomewhatComparable2(int Value) noexcept : value {Value} {}

        friend bool operator<(const SomewhatComparable2& lhs, const SomewhatComparable2& rhs) noexcept
        {
            return lhs.value < rhs.value;
        }
    };

    class Comparable : private CompletelyComparable<Comparable>
    {
    private:
        int value;

    public:
        explicit Comparable(int Value) noexcept : value {Value} {}

        friend bool operator==(const Comparable& lhs, const Comparable& rhs) noexcept { return lhs.value == rhs.value; }
        friend bool operator<(const Comparable& lhs, const Comparable& rhs) noexcept { return lhs.value < rhs.value; }
    };
}   // namespace CppUtils::Internal::Testing

//! \test Testing the \c CppUtils::Operators::EqualityComparable class
GTEST_TEST(testComparisonOperators, aClassThatInheritsFromEqualityComparableCanOnlyCallEqualityComparisons)
{
    CppUtils::Internal::Testing::SomewhatComparable1 value1 {5};
    CppUtils::Internal::Testing::SomewhatComparable1 value2 {5};
    CppUtils::Internal::Testing::SomewhatComparable1 value3 {10};

    ASSERT_TRUE(value1 == value2);
    ASSERT_FALSE(value1 == value3);

    ASSERT_TRUE(value1 != value3);
    ASSERT_FALSE(value1 != value2);

    // ASSERT_TRUE(value1 < value3);                        // Error: no operator "<" matches these operands
}

//! \test Testing the \c CppUtils::Operators::LessThanComparable class
GTEST_TEST(testComparisonOperators, aClassThatInheritsFromLessThanComparableCanOnlyCallInequalityComparisons)
{
    CppUtils::Internal::Testing::SomewhatComparable2 value1 {5};
    CppUtils::Internal::Testing::SomewhatComparable2 value2 {5};
    CppUtils::Internal::Testing::SomewhatComparable2 value3 {10};

    ASSERT_TRUE(value1 < value3);
    ASSERT_FALSE(value1 < value2);

    ASSERT_TRUE(value3 > value2);
    ASSERT_FALSE(value1 > value2);

    ASSERT_TRUE(value1 <= value2);
    ASSERT_FALSE(value3 <= value2);

    ASSERT_TRUE(value3 >= value2);
    ASSERT_FALSE(value1 >= value3);

    // ASSERT_TRUE(value1 == value2);                       // Error: no operator "==" matches these operands
}

//! \test Testing the \c CppUtils::Operators::CompletelyComparable class
GTEST_TEST(testComparisonOperators, aClassThatInheritsFromCompletelyComparableCanCallAllComparisons)
{
    CppUtils::Internal::Testing::Comparable value1 {5};
    CppUtils::Internal::Testing::Comparable value2 {5};
    CppUtils::Internal::Testing::Comparable value3 {10};

    ASSERT_TRUE(value1 == value2);
    ASSERT_FALSE(value1 == value3);

    ASSERT_TRUE(value1 != value3);
    ASSERT_FALSE(value1 != value2);

    ASSERT_TRUE(value1 < value3);
    ASSERT_FALSE(value1 < value2);

    ASSERT_TRUE(value3 > value2);
    ASSERT_FALSE(value1 > value2);

    ASSERT_TRUE(value1 <= value2);
    ASSERT_FALSE(value3 <= value2);

    ASSERT_TRUE(value3 >= value2);
    ASSERT_FALSE(value1 >= value3);
}

#endif
