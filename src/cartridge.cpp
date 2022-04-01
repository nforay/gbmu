/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:54 by nforay            #+#    #+#             */
/*   Updated: 2022/04/02 00:13:16 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartridge.hpp"

Cartridge::Cartridge(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : _header(header), _rom(data) {
    SPDLOG_TRACE("Cartridge Constructor");
    SPDLOG_INFO("Cartridge Title: \"{}\"", _header.title);
    // SPDLOG_INFO("Cartridge Type: {}", _header.cartridgeType);
    // SPDLOG_INFO("Cartridge Rom Size: {}", _header.romSize);
    // SPDLOG_INFO("Cartridge Ram Size: {}", _header.ramSize);
    SPDLOG_INFO("Cartridge Header Checksum isvalid: {}", checkHeaderChecksum(data) ? "true" : "false");
    SPDLOG_INFO("Cartridge Global Checksum isvalid: {}", checkGlobalChecksum(data) ? "true" : "false");
}

Cartridge::~Cartridge() { SPDLOG_TRACE("Cartridge Destructor"); }

MBC1::MBC1(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC1 Constructor");
};

MBC1::~MBC1() { SPDLOG_TRACE("MBC1 Destructor"); }

void MBC1::write(const uint16_t &addr, uint8_t data){};

uint8_t MBC1::read(const uint16_t &addr) const { return 0; };

MBC2::MBC2(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC2 Constructor");
};

MBC2::~MBC2() { SPDLOG_TRACE("MBC2 Destructor"); }

void MBC2::write(const uint16_t &addr, uint8_t data){};

uint8_t MBC2::read(const uint16_t &addr) const { return 0; };

MBC3::MBC3(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC3 Constructor");
};

MBC3::~MBC3() { SPDLOG_TRACE("MBC3 Destructor"); }

void MBC3::write(const uint16_t &addr, uint8_t data){};

uint8_t MBC3::read(const uint16_t &addr) const { return 0; };

MBC5::MBC5(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC5 Constructor");
};

MBC5::~MBC5() { SPDLOG_TRACE("MBC5 Destructor"); }

void MBC5::write(const uint16_t &addr, uint8_t data){};

uint8_t MBC5::read(const uint16_t &addr) const { return 0; };
