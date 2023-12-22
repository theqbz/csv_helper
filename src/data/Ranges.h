///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Ranges.h
/// @brief Declaration of range datastructure
///

#pragma once

#include <algorithm>
#include <compare>
#include <utility>
#include <vector>

namespace csvvalidator {
namespace data {
namespace display {

struct Range : public std::pair<size_t, size_t>
{
    ///
    /// @brief Make the begining and the end point of the Range in a non
    ///        descending order.
    ///
    inline void normalize()
    {
        if (first > second) {
            std::swap(first, second);
        }
    }

    inline std::strong_ordering operator<=>(const Range& p_other) const
    {
        return this->first <=> p_other.first;
    }
};

struct Ranges : public std::vector<Range>
{
    ///
    /// @brief Make all the begining and the end points of all the Range in a
    ///        non descending order.
    ///
    void normalize()
    {
        for (Range& range : *this) {
            range.normalize();
        }
    }

    inline void sort()
    {
        std::sort(this->begin(), this->end());
    }
};

} // namespace display
} // namespace data
} // namespace csvvalidator
