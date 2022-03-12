/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:12:21 by nforay            #+#    #+#             */
/*   Updated: 2022/03/12 02:10:23 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spdlog/spdlog.h"
#include <tclap/CmdLine.h>

#include "config.h"

int main(int argc, char **argv) {
    spdlog::info("Logger started");
    try {
        TCLAP::CmdLine cmd("Command description message", ' ', PROJECT_VER);
        cmd.parse(argc, argv);
    } catch (TCLAP::ArgException &e) {
        spdlog::error("Error: {} for arg {}", e.error(), e.argId());
    }
    spdlog::info("exit");
    return 0;
}