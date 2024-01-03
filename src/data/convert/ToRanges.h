///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToRanges.h
/// @brief Declarations of data::convert::Ranges class.
///
#pragma once

#include "../Ranges.h"

namespace csvvalidator::data {
namespace convert {

///
/// @brief Worker class to convert a list of lineNumbers to
///        data::display::Ranges
///
class Ranges
{
public:
    ///
    /// @brief Create ranges from the given lines, depending on the range width
    ///        and upper limit.
    ///
    /// @param[in] - p_lineNumbers : the list of the linenumbes, which will be
    ///                              the center of their own range
    /// @param[in] - p_width       : the width of the range, that many lines
    ///                              are added to the range below and above the
    ///                              center
    /// @param[in] - p_lowelLimit  : the lower limit of the range
    /// @param[in] - p_upperLimit  : the upper limit of the range
    ///
    static const display::Ranges get(const std::vector<size_t>& p_lineNumbers,
                                     const size_t p_width,
                                     const size_t p_lowerLimit,
                                     const size_t p_upperLimit);

    static const display::Ranges rawRanges(const std::vector<size_t>& p_lineNumbers);
    static const size_t lowerBound(const size_t p_initialNumber);
    static const size_t upperBound(const size_t p_initialNumber);

    static const display::Ranges merge(const display::Ranges& p_rawRanges);
    static bool overlapping(const display::Range& p_range1, const display::Range& p_range2);
    static void combine(const display::Range& p_source, display::Range* p_target);

    static size_t width;
    static size_t lowerLimit;
    static size_t upperLimit;
};

} // namespace convert
} // namespace csvvalidator::data
