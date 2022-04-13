/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:12:21 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 19:21:07 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tclap/CmdLine.h>

#include "config.h"
#include "gbmu.hpp"
#include "logger.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main(int argc, char **argv) {
    SPDLOG_INFO("Logger started");
    spdlog::init_thread_pool(8192, 1);
    auto  stdout_sink     = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto *stdout_sink_ptr = stdout_sink.get();
    auto  rotating_sink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/gbmu.txt", 1024 * 1024 * 10, 3);
    std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
    auto logger = std::make_shared<spdlog::async_logger>("loggername", sinks.begin(), sinks.end(),
                                                         spdlog::thread_pool(),
                                                         spdlog::async_overflow_policy::block);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::trace);
    stdout_sink_ptr->set_level(spdlog::level::err);
    std::string romfile;
    try {
        TCLAP::CmdLine cmd("GBMU", ' ', PROJECT_VER);
#ifndef NDEBUG
        TCLAP::SwitchArg silentSwitch("s", "silent", "Disable logging", cmd, false);
        TCLAP::SwitchArg traceSwitch("t", "trace", "Set Logger level to trace", cmd, false);
#endif
        TCLAP::ValueArg<std::string> filepathArg("f", "file", "file to load", true, "", "string");
        cmd.add(filepathArg);
        cmd.parse(argc, argv);
        romfile = filepathArg.getValue();
#ifndef NDEBUG
        if (traceSwitch.getValue())
            stdout_sink_ptr->set_level(spdlog::level::trace);
        if (silentSwitch.getValue())
            stdout_sink_ptr->set_level(spdlog::level::off);
#endif
    } catch (TCLAP::ArgException &e) {
        SPDLOG_ERROR("Error: {} for arg {}", e.error(), e.argId());
    }
    {
        Gbmu gbmu;
        gbmu.reset();
        gbmu.insert_cartridge(romfile); // testrom path
        gbmu.run();
    }
    SPDLOG_INFO("exit");
    return 0;
}
