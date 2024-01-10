///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToRanges.h
/// @brief Declaration of data::convert::ToRanges class.
///
#pragma once

#include "../Ranges.h"

namespace csvvalidator::data {
namespace convert {

///
/// @brief Worker class to convert a list of lineNumbers to data::display::Ranges
///
class ToRanges
{
public:
    ///
    /// @brief Create Ranges from the given lines, depending on the range width
    ///        and the lower and upper limit of the final ranges.
    ///
    /// @param[in] - p_lineNumbers : the list of the linenumbes, which will be
    ///                              the center of their own range
    /// @param[in] - p_width       : the width of the range, that many lines
    ///                              are added to the range below and above the
    ///                              center
    /// @param[in] - p_lowerLimit  : the lower limit of the range
    /// @param[in] - p_upperLimit  : the upper limit of the range
    /// 
    /// @return a list of ranges
    ///
    static const display::Ranges get(const std::vector<size_t>& p_lineNumbers,
                                     const size_t p_width,
                                     const size_t p_lowerLimit,
                                     const size_t p_upperLimit);

    static size_t width;
    static size_t lowerLimit;
    static size_t upperLimit;
};

} // namespace convert
} // namespace csvvalidator::data
