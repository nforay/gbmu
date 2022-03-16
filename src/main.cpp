/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:12:21 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:37:06 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tclap/CmdLine.h>

#include "config.h"
#include "gbmu.hpp"
#include "logger.h"

int main(int argc, char **argv) {
    SPDLOG_INFO("Logger started");
    try {
        TCLAP::CmdLine cmd("GBMU", ' ', PROJECT_VER);
#ifndef NDEBUG
        TCLAP::SwitchArg silentSwitch("s", "silent", "Disable logging", cmd, false);
        TCLAP::SwitchArg traceSwitch("t", "trace", "Set Logger level to trace", cmd, false);
#endif
        cmd.parse(argc, argv);
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
        gbmu.init();
        gbmu.reset();
        gbmu.run();
    }
    SPDLOG_INFO("exit");
    return 0;
}
