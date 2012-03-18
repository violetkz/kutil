
#include "config.hpp"

config::config(const char *file)
    :config_file_path_(file),stmt_collector_()
{
}

void config::parse(){
    std::ifstream f(config_file_path_.c_str());
    if (f.bad()){
        //FIXME: handle the file open error.
    }

    conf_parser cp(f, stmt_collector_);
    cp.parse();
}

#ifdef _DEBUG_CONFIG

config::print(){
    stmt_collector_.print();
}
#endif
