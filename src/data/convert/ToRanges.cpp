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
    if (p_rawRanges.empty()) {
        return {};
    }
    display::Ranges finalRanges {};
    for (auto currentRawRange = p_rawRanges.begin();
         currentRawRange != p_rawRanges.end();
         ++currentRawRange) {
        if (finalRanges.empty() || !overlapping(finalRanges.back(), *currentRawRange)) {
            finalRanges.push_back(*currentRawRange);
            continue;
        }
        combine(*currentRawRange, &finalRanges.back());
    }
    return finalRanges;
}

const size_t lowerBound(const size_t p_initialNumber)
{
    if (ToRanges::width == std::numeric_limits<size_t>::max()) {
        return ToRanges::lowerLimit;
    }
    return p_initialNumber < ToRanges::lowerLimit + ToRanges::width ? ToRanges::lowerLimit
                                                                    : p_initialNumber - ToRanges::width;
}

const size_t upperBound(const size_t p_initialNumber)
{
    if (ToRanges::width == std::numeric_limits<size_t>::max() || ToRanges::upperLimit < ToRanges::width) {
        return ToRanges::upperLimit;
    }
    return ToRanges::upperLimit - ToRanges::width < p_initialNumber ? ToRanges::upperLimit
                                                                    : p_initialNumber + ToRanges::width;
}

const display::Ranges rawRanges(const std::vector<size_t>& p_lineNumbers)
{
    LOG(utils::INDENTATION + "Getting raw ranges\n", utils::verbose);
    data::display::Ranges ranges {};
    for (const size_t& number : p_lineNumbers) {
        data::display::Range range({ lowerBound(number), upperBound(number) });
        ranges.push_back(range);
    }
    return ranges;
}

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

} // namespace convert
} // namespace csvvalidator::data
