#ifndef REGULAR_EXPRESSIONS_H
#define REGULAR_EXPRESSIONS_H

#include <regex>
#include <string>

namespace regular_expressions
{
    const std::regex is_state(std::string("State(.*)"));
}

#endif
