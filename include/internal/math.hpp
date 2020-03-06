// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: math.hpp - Version 1.0.0
// Author: crdrisko
// Date: 03/03/2020-18:45:41
// Description: Mathematical functions from various math libraries adapted for PhysicalQuantities

#ifndef CPP_UNITS_MATH_HPP
#define CPP_UNITS_MATH_HPP

#include <cmath>
#include <functional>

#include <utils-api/errors.hpp>

#include "physicalQuantity.hpp"

namespace PhysicalQuantities::Math
{
    template <int L, int M, int T, int I, int Th, int N, int J>
    constexpr auto log(const PhysicalQuantity< Dimensionality<L, M, T, I, Th, N, J> >& value)
    {
        if (value.getMagnitude() < 0.0)
            Utilities_API::Errors::printFatalErrorMessage(1, "The value inside the natural logarithm must be positive.");

        return PhysicalQuantity< Dimensionality<> >( std::log(value.getMagnitude()) );
    }


    template <typename NewDimensionality, int L, int M, int T, int I, int Th, int N, int J>
    constexpr auto pow(const PhysicalQuantity< Dimensionality<L, M, T, I, Th, N, J> >& value, int power)
    {
        return PhysicalQuantity<NewDimensionality>( std::pow(value.getMagnitude(), power) );
    }
}

#endif
