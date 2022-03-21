/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:12:21 by nforay            #+#    #+#             */
/*   Updated: 2022/03/21 03:56:13 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tclap/CmdLine.h>

#include "config.h"
#include "gbmu.hpp"
#include "logger.h"

int main(int argc, char **argv) {
    SPDLOG_INFO("Logger started");
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
            spdlog::set_level(spdlog::level::trace);
        if (silentSwitch.getValue())
            spdlog::set_level(spdlog::level::off);
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
