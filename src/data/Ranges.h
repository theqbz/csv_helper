///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Ranges.h
/// @brief Declarations of display::Ranges and display::Range datastructure
///
/// These datastructures stores ranges with ordering functions
///
#pragma once

#include <algorithm>
#include <compare>
#include <utility>
#include <vector>

namespace csvvalidator::data {
namespace display {

///
/// @brief A range defined by a start and end point.
///
/// The points represented by a < size_t, size_t > pair. The range contains
/// both the start and end points.
///
struct Range : public std::pair<size_t, size_t>
{
    ///
    /// @brief Make the start and end points of the Range in non-descending
    ///        order.
    ///
    inline void normalize()
    {
        if (first > second) {
            std::swap(first, second);
        }
    }

    inline std::strong_ordering operator<=>(const Range& p_other) const { return this->first <=> p_other.first; }
};

///
/// @brief Container for Ranges.
///
/// Ranges consists of a vector of Range.
///
struct Ranges : public std::vector<Range>
{
    ///
    /// @brief Normalize all of the Ranges.
    ///
    void normalize()
    {
        for (Range& range : *this) {
            range.normalize();
        }
    }

    inline void sort() { std::sort(this->begin(), this->end()); }
};

} // namespace display
} // namespace csvvalidator::data
