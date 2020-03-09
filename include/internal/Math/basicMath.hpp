// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: basicMath.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/31/2020-15:42:41
// Description: Common mathematical function definitions and prototypes

#ifndef UTILITIES_API_BASICMATH_HPP
#define UTILITIES_API_BASICMATH_HPP

#include <vector>

namespace Utilities_API::Math
{
    template<typename T>
    constexpr bool withinRange(const T& value, const T& min, const T& max)
    {
        return (value <= max) && (value >= min);
    }

    template<int min, int max, typename T>
    constexpr bool withinRange(const T& value)
    {
        return withinRange(value, static_cast<T>(min), static_cast<T>(max));
    }

    template<typename T>
    constexpr auto linearlyInterpolate(const std::vector<T>& x, T y1, T y2)
    {
        std::vector<T> y;

        long double slope { (y2 - y1) / (x[x.size() - 1] - x[0]) };
        long double intercept { y1 - (slope * x[0]) };

        for (const auto& element : x)
            y.push_back(slope * element + intercept);

        return y;
    }
}

#endif
