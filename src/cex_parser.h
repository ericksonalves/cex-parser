#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "definitions.h"
#include "errors.h"
#include "regular_expressions.h"
#include "state.h"
#include "utils.h"

class cex_parser
{
public:
    cex_parser(const int argc, const char** argv);

    ~cex_parser();

    const std::string get_interleaving() const;

private:
    std::string m_file_under_verification;
    std::vector<state> m_states;
};
