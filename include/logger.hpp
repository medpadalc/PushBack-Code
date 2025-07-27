#pragma once

#include <string>
#include <sstream>

#include "lemlib/logger/baseSink.hpp"
#include "lemlib/logger/message.hpp"
#include "robodash/apix.h"
#include "robodash/core.h"

namespace logging {

class Logger : public lemlib::BaseSink {
public:
    Logger();

    void print(std::string str);
    void println(std::string str);

    template<typename... Args>
    void printfmt(fmt::format_string<Args...> format, Args&&... args) {
        print(fmt::format(format, std::forward<Args>(args)...));
    }

    void sendMessage(const lemlib::Message& message) override;

protected:
    rd_view_t *view;

    lv_obj_t *output;
    lv_obj_t *output_container;
    std::ostringstream stream;
};

std::shared_ptr<Logger> getLogger();

};