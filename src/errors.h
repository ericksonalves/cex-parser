#ifndef ERRORS_H
#define ERRORS_H

#include <string>

namespace error
{
    const std::string could_not_open_file("Could not open given file");
    const std::string no_input_arguments("No input arguments given");
    const std::string sequential_program("Given trace is from a sequential program");
    const std::string trace_is_not_counterexample("Given trace is not a counterexample");
}

#endif
