///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToRanges.cpp
/// @brief Definition of data::convert::ToRanges class and worker functions.
///

#include "ToRanges.h"
#include "../../utils/Utility.h"
#include "../Ranges.h"

#include <limits>
#include <string>

namespace csvvalidator::data {
namespace convert {

size_t ToRanges::width      = 0;
size_t ToRanges::lowerLimit = 0;
size_t ToRanges::upperLimit = 0;

const display::Ranges rawRanges(const std::vector<size_t>& p_lineNumbers);
const display::Ranges merge(const display::Ranges& p_rawRanges);

const display::Ranges ToRanges::get(const std::vector<size_t>& p_lineNumbers,
                                    const size_t p_width,
                                    const size_t p_lowerLimit,
                                    const size_t p_upperLimit)
{
    LOG(utils::INDENTATION + "Getting error-ranges\n", utils::verbose);
    width      = p_width;
    lowerLimit = p_lowerLimit;
    upperLimit = p_upperLimit;
    display::Ranges raw_ranges { rawRanges(p_lineNumbers) };
    LOG(utils::INDENTATION + "Raw ranges = " + std::to_string(raw_ranges.size()) + "\n", utils::verbose);
    raw_ranges.normalize();
    raw_ranges.sort();
    const display::Ranges ranges { merge(raw_ranges) };
    LOG(utils::INDENTATION + "Merged ranges = " + std::to_string(ranges.size()) + "\n", utils::verbose);
    return ranges;
}

inline bool isMaxWidth()
{
    return ToRanges::width == std::numeric_limits<size_t>::max();
}

const size_t getLowerBound(const size_t p_middleOfTheRange)
{
    if (isMaxWidth()) {
        return ToRanges::lowerLimit;
    }
    const size_t headroom { ToRanges::lowerLimit + ToRanges::width };
    const bool outOfBound { p_middleOfTheRange < headroom };
    return outOfBound ? ToRanges::lowerLimit : p_middleOfTheRange - ToRanges::width;
}

inline bool willOwerflow()
{
    return ToRanges::upperLimit < ToRanges::width;
}

const size_t getUpperBound(const size_t p_middleOfTheRange)
{
    if (isMaxWidth() || willOwerflow()) {
        return ToRanges::upperLimit;
    }
    const size_t headroom { ToRanges::upperLimit - ToRanges::width };
    const bool outOfBound { headroom < p_middleOfTheRange };
    return outOfBound ? ToRanges::upperLimit : p_middleOfTheRange + ToRanges::width;
}

const display::Ranges rawRanges(const std::vector<size_t>& p_lineNumbers)
{
    LOG(utils::INDENTATION + "Getting raw ranges\n", utils::verbose);
    data::display::Ranges ranges {};
    for (const size_t& number : p_lineNumbers) {
        data::display::Range range({ getLowerBound(number), getUpperBound(number) });
        ranges.push_back(range);
    }
    return ranges;
}

void combine(const display::Range& p_sourceRange,
             display::Range* p_targetRange)
{
    if (!p_targetRange) {
        LOG("Program logic error @ merge()! nullptr as p_targetRange\n", true);
        return;
    }
    if (p_sourceRange.first < p_targetRange->first) {
        p_targetRange->first = p_sourceRange.first;
    }
    if (p_sourceRange.second > p_targetRange->second) {
        p_targetRange->second = p_sourceRange.second;
    }
}

bool overlapping(const display::Range& p_range1,
                 const display::Range& p_range2)
{
    if (p_range1.first <= p_range2.first) {
        return p_range2.first <= p_range1.second;
    }
    return p_range1.first <= p_range2.second;
}

const display::Ranges merge(const display::Ranges& p_rawRanges)
{
    LOG(utils::INDENTATION + "Merging ranges\n", utils::verbose);
    display::Ranges finalRanges {};
    for (const display::Range& rawRange : p_rawRanges) {
        if (finalRanges.empty() || !overlapping(finalRanges.back(), rawRange)) {
            finalRanges.push_back(rawRange);
            continue;
        }
        combine(rawRange, &finalRanges.back());
    }
    return finalRanges;
}

} // namespace convert
} // namespace csvvalidator::data
