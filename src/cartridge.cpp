/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:54 by nforay            #+#    #+#             */
/*   Updated: 2022/04/02 00:29:04 by nforay           ###   ########.fr       */
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

void MBC1::write(const uint16_t &addr, uint8_t data) {
    // TODO: implement bank switching
    SPDLOG_INFO("MBC1 write addr: 0x{:04X}, data: 0x{:02X}", addr, data);
    _ram[addr] = data;
}

uint8_t MBC1::read(const uint16_t &addr) const {
    // TODO: implement bank switching
    SPDLOG_INFO("MBC1 read addr: 0x{:04X}, data: 0x{:02X}", addr, _rom[addr]);
    return _rom[addr];
};

MBC2::MBC2(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC2 Constructor");
};

MBC2::~MBC2() { SPDLOG_TRACE("MBC2 Destructor"); }

void MBC2::write(const uint16_t &addr, uint8_t data) {
    SPDLOG_INFO("MBC2 write addr: 0x{:04X}, data: 0x{:02X}", addr, data);
    _ram[addr] = data;
};

uint8_t MBC2::read(const uint16_t &addr) const {
    SPDLOG_INFO("MBC2 read addr: 0x{:04X}, data: 0x{:02X}", addr, _rom[addr]);
    return _rom[addr];
};

MBC3::MBC3(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC3 Constructor");
};

MBC3::~MBC3() { SPDLOG_TRACE("MBC3 Destructor"); }

void MBC3::write(const uint16_t &addr, uint8_t data) {
    SPDLOG_INFO("MBC3 write addr: 0x{:04X}, data: 0x{:02X}", addr, data);
    _ram[addr] = data;
};

uint8_t MBC3::read(const uint16_t &addr) const {
    SPDLOG_INFO("MBC3 read addr: 0x{:04X}, data: 0x{:02X}", addr, _rom[addr]);
    return _rom[addr];
};

MBC5::MBC5(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC5 Constructor");
};

MBC5::~MBC5() { SPDLOG_TRACE("MBC5 Destructor"); }

void MBC5::write(const uint16_t &addr, uint8_t data) {
    SPDLOG_INFO("MBC5 write addr: 0x{:04X}, data: 0x{:02X}", addr, data);
    _ram[addr] = data;
};

uint8_t MBC5::read(const uint16_t &addr) const {
    SPDLOG_INFO("MBC5 read addr: 0x{:04X}, data: 0x{:02X}", addr, _rom[addr]);
    return _rom[addr];
};
