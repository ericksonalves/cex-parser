#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include "definitions.h"

class state
{
public:
    state(const std::vector<std::string>& raw_state);

    ~state();

    const std::vector<std::string>& id() const;

    const std::vector<std::string>& trace() const;

private:
    std::vector<std::string> m_state_id;

    std::vector<std::string> m_state_trace;
};

#endif
