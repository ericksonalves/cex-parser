#include "cex_parser.h"

cex_parser::cex_parser(const int argc, const char** argv)
{
    if (argc <= 1)
        throw std::invalid_argument(error::no_input_arguments);

    std::ifstream input_file;

    input_file.open(argv[1], std::ifstream::in);

    if (!input_file.is_open())
        throw std::runtime_error(error::could_not_open_file);

    std::string current_line;
    std::vector<std::string> bmc_trace;

    while (std::getline(input_file, current_line))
        bmc_trace.push_back(current_line);

    input_file.close();

    if (!utils::is_counterexample(bmc_trace))
        throw std::runtime_error(error::trace_is_not_counterexample);

    size_t begin = bmc_trace[0].find(" ") + 1;
    size_t end = bmc_trace[0].find(":");

    m_file_under_verification = bmc_trace[0].substr(begin, end - begin);

    std::vector<std::string>::const_iterator it;
    for (it = bmc_trace.cbegin(); it != bmc_trace.cend() && it->compare(constants::counterexample) != 0; ++it);
    bmc_trace.erase(bmc_trace.begin(), it + 2);

    std::vector<std::string>::const_iterator last_delimiter = bmc_trace.cbegin();

    std::vector<std::vector<std::string>> raw_states;

    for (std::vector<std::string>::const_iterator it = bmc_trace.cbegin(); it != bmc_trace.cend(); ++it) {
        if (it->size() == 0) {
            std::vector<std::string> raw_state;
            for (std::vector<std::string>::const_iterator x = last_delimiter; x != it; ++x)
                raw_state.push_back(*x);
            raw_states.push_back(raw_state);
            last_delimiter = it + 1;
        }
    }

    bmc_trace.clear();

    for (const std::vector<std::string>& raw_state : raw_states)
        m_states.push_back(state(raw_state));

    raw_states.clear();
}

cex_parser::~cex_parser()
{
    m_states.clear();
}

const std::string cex_parser::get_interleaving() const
{
    std::vector<int> threads;
    std::vector<int> full_trace_threads;
    std::vector<int> lines;
    std::vector<int> full_trace_lines;
    int last_thread_id = 0;
    int full_trace_last_thread_id = 0;
    int last_line = -1;
    for (const state& st : m_states) {
        for (const std::string& id : st.id()) {
            if (std::regex_match(id, regular_expressions::is_state)) {
                int current_thread_id = utils::char_to_int(id[id.size() - 1]);
                full_trace_threads.push_back(full_trace_last_thread_id);
                full_trace_lines.push_back(last_line);
                full_trace_last_thread_id = current_thread_id;
                if (current_thread_id != last_thread_id) {
                     threads.push_back(last_thread_id);
                     lines.push_back(last_line);
                     last_thread_id = current_thread_id;
                }
            }
            if (id.find(m_file_under_verification) != std::string::npos) {
                size_t start = id.find(constants::line) + 5;
                size_t end = id.find(" ", start);
                std::string current_line = id.substr(start, end - start);
                last_line = std::stoi(current_line);
            }
        }
    }
    threads.push_back(last_thread_id);
    lines.push_back(last_line);

    std::ostringstream output;
    output << "I: ";
    for (unsigned int i = 0; i != threads.size(); ++i)
        output << utils::format_result(threads[i], lines[i], i != threads.size() - 1);
    output << std::endl;
    output << "Full trace" << std::endl;
    for (unsigned int i = 0; i != full_trace_threads.size(); ++i)
        output <<
        utils::format_result(full_trace_threads[i], full_trace_lines[i], i != full_trace_threads.size() - 1);
    return output.str();
}
