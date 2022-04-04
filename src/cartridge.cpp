/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:54 by nforay            #+#    #+#             */
/*   Updated: 2022/04/04 17:28:08 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartridge.hpp"

auto in_range = [](const uint16_t &addr, const address_range &range) -> bool {
    return ((addr - range.start) <= range.diff);
};

Cartridge::Cartridge(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : _header(header), _rom(data) {
    SPDLOG_TRACE("Cartridge Constructor");
    SPDLOG_INFO("Cartridge Title: \"{}\"", _header.title);
    SPDLOG_INFO("Cartridge Type: 0x{:01X}", (uint8_t)_header.cartridgeType);
    SPDLOG_INFO("Cartridge Rom Size: 0x{:01X} ({}B)", (uint8_t)_header.romSize,
                0x8000 << (uint8_t)_header.romSize);
    SPDLOG_INFO("Cartridge Ram Size: 0x{:01X} ({}B)", (uint8_t)_header.ramSize, _header.getRamSize());
    SPDLOG_INFO("Cartridge Header Checksum isvalid: {}", checkHeaderChecksum(data) ? "true" : "false");
    SPDLOG_INFO("Cartridge Global Checksum isvalid: {}", checkGlobalChecksum(data) ? "true" : "false");
}

Cartridge::~Cartridge() { SPDLOG_TRACE("Cartridge Destructor"); }

MBC1::MBC1(const std::vector<uint8_t> &data, const CartridgeHeader &header)
    : Cartridge(data, header) {
    SPDLOG_TRACE("MBC1 Constructor");
    _ram.resize(_header.getRamSize());
    _rom_bank_count = (data.size() / 0x4000) + (data.size() % 0x4000 ? 1 : 0);
    _ram_bank_count = _header.getRamSize() / 0x2000;
};

MBC1::~MBC1() { SPDLOG_TRACE("MBC1 Destructor"); }

// banking: TCAGBD.pdf page 54
void MBC1::write(const uint16_t &addr, uint8_t data) {
    SPDLOG_INFO("MBC1 write addr: 0x{:04X}, data: 0x{:02X}", addr, data);
    if (addr <= MBC1_range::ramEnable.end)
        _ram_enabled = (data == 0x0A);
    else if (in_range(addr, MBC1_range::switchableRamBank))
        _ram[addr - 0xA000 + _selected_ram_bank * (0xBFFF - 0xA000)] = data;
    else if (in_range(addr, MBC1_range::romBankSelect)) {
        lower = data;
        if (!lower)
            lower = 1;
        _selected_rom_bank = ((upper << 3) | (lower & 0x1F));
        if (_selected_rom_bank > _rom_bank_count)
            SPDLOG_CRITICAL("MBC1: selected rom bank is out of range");
    } else if (in_range(addr, MBC1_range::ramBankSelect)) {
        if (!_ram.empty() && _mode == BankMode::RAM && _ram_enabled)
            _selected_ram_bank = data;
        else {
            upper              = data;
            _selected_ram_bank = ((upper << 3) | (lower & 0x1F)); // need safety check
        }
        if (_selected_ram_bank > _ram_bank_count)
            SPDLOG_CRITICAL("MBC1: selected ram bank is out of range");
    } else if (in_range(addr, MBC1_range::bankingmode))
        _mode = (data ? BankMode::RAM : BankMode::ROM);
}

// banking: TCAGBD.pdf page 54
uint8_t MBC1::read(const uint16_t &addr) const {
    if (in_range(addr, MBC1_range::romBank0)) {
        SPDLOG_INFO("MBC1 read ROM addr: 0x{:04X}, data: 0x{:02X}", addr, _rom[addr]);
        return _rom[addr];
    }
    if (in_range(addr, MBC1_range::switchableRomBank)) {
        SPDLOG_INFO("MBC1 read ROM addr: 0x{:04X}, data: 0x{:02X}", addr,
                    _rom[addr - 0x4000 + _selected_rom_bank * 0x4000]);
        return _rom[addr - 0x4000 + _selected_rom_bank * 0x4000];
    }
    if (in_range(addr, MBC1_range::switchableRamBank)) {
        SPDLOG_INFO("MBC1 read RAM addr: 0x{:04X}, data: 0x{:02X}", addr,
                    _ram[addr - 0xA000 + _selected_ram_bank * 0x2000]);
        return _ram[addr - 0xA000 + _selected_ram_bank * 0x2000];
    }
    return (0x00);
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
