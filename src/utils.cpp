#include "utils.h"

const bool utils::is_counterexample(const std::vector<std::string>& bmc_trace)
{
    for (std::vector<std::string>::const_reverse_iterator it = bmc_trace.rbegin(); it != bmc_trace.rend(); ++it)
    {
        if (it->compare(constants::verification_failed) == 0)
            return true;
    }
    return false;
}

const int utils::char_to_int(const char&c)
{
    return static_cast<int>(c - '0');
}

const std::string utils::format_result(const int& thread_id, const int& line, const bool& has_next)
{
    std::ostringstream format;
    format << "(T" << thread_id << ", L" << line << ")" << (has_next ? " => " : "");
    return format.str();
}
