#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>
#include "definitions.h"

namespace utils
{
    const bool is_counterexample(const std::vector<std::string>& bmc_trace);
    const int char_to_int(const char&c);
    const std::string format_result(const int& thread_id, const int& line, const bool& has_next);
}

#endif
