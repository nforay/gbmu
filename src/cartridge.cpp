/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:54 by nforay            #+#    #+#             */
/*   Updated: 2022/03/31 18:31:32 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartridge.hpp"

Cartridge::Cartridge(Bus *bus) : Component(bus) { SPDLOG_TRACE("Cartridge Constructor"); }

Cartridge::~Cartridge() { SPDLOG_TRACE("Cartridge Destructor"); }

MBC1::MBC1(Bus *bus, const std::vector<uint8_t> &data) : Cartridge(bus) {
    SPDLOG_TRACE("MBC1 Constructor");
    std::move(data.begin(), data.end(), std::back_inserter(_rom));
};

MBC2::MBC2(Bus *bus, const std::vector<uint8_t> &data) : Cartridge(bus) {
    SPDLOG_TRACE("MBC2 Constructor");
};

MBC3::MBC3(Bus *bus, const std::vector<uint8_t> &data) : Cartridge(bus) {
    SPDLOG_TRACE("MBC3 Constructor");
};

MBC5::MBC5(Bus *bus, const std::vector<uint8_t> &data) : Cartridge(bus) {
    SPDLOG_TRACE("MBC5 Constructor");
};
