#include "state.h"

state::state(const std::vector<std::string>& raw_state)
{
    bool found_delimiter = false;
    for (std::vector<std::string>::const_iterator it = raw_state.cbegin(); it != raw_state.cend(); ++it) {
        if (it->compare(constants::trace_delimiter) != 0) {
            if (!found_delimiter)
                m_state_id.push_back(*it);
            else
                m_state_trace.push_back(*it);
        }
        else {
            found_delimiter = true;
        }
    }
}

state::~state()
{
    m_state_id.clear();
    m_state_trace.clear();
}

const std::vector<std::string>& state::id() const
{
    return m_state_id;
}

const std::vector<std::string>& state::trace() const
{
    return m_state_trace;
}
