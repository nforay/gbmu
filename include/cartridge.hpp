/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:24 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 22:51:00 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <vector>

#include "cartridge_header.hpp"
#include "logger.h"

class address_range {
public:
    address_range(const uint16_t &start, const uint16_t &end)
        : start(start), end(end), diff(end - start) {}
    const uint16_t start;
    const uint16_t end;
    const uint16_t diff;
};

enum class BankMode {
    ROM = 0,
    RAM,
};

class Cartridge {
public:
    virtual ~Cartridge();

    virtual void    write(const uint16_t &addr, uint8_t data) = 0;
    virtual uint8_t read(const uint16_t &addr) const          = 0;

protected:
    Cartridge(std::vector<uint8_t> &data, CartridgeHeader &header);
    CartridgeHeader      _header;
    std::vector<uint8_t> _rom;
    std::vector<uint8_t> _ram;
};

class MBC1 : public Cartridge {
public:
    MBC1(std::vector<uint8_t> &data, CartridgeHeader &header);
    ~MBC1() override;

    void    write(const uint16_t &addr, uint8_t data) override;
    uint8_t read(const uint16_t &addr) const override;

    BankMode _mode              = BankMode::ROM;
    bool     _ram_enabled       = false;
    uint8_t  _selected_rom_bank = 1;
    uint8_t  _selected_ram_bank = 0;
    uint8_t  _ram_bank_count    = 0;
    uint8_t  _rom_bank_count    = 0;
    uint8_t  _lower             = 1;
    uint8_t  _upper             = 0;
};

class MBC2 : public Cartridge {
public:
    MBC2(std::vector<uint8_t> &data, CartridgeHeader &header);
    ~MBC2() override;

    void    write(const uint16_t &addr, uint8_t data) override;
    uint8_t read(const uint16_t &addr) const override;
};

class MBC3 : public Cartridge {
public:
    MBC3(std::vector<uint8_t> &data, CartridgeHeader &header);
    ~MBC3() override;

    void    write(const uint16_t &addr, uint8_t data) override;
    uint8_t read(const uint16_t &addr) const override;
};

class MBC5 : public Cartridge {
public:
    MBC5(std::vector<uint8_t> &data, CartridgeHeader &header);
    ~MBC5() override;

    void    write(const uint16_t &addr, uint8_t data) override;
    uint8_t read(const uint16_t &addr) const override;
};

namespace MBC1_range {
    const address_range romBank0          = address_range(0x0000, 0x3FFF); // Read
    const address_range switchableRomBank = address_range(0x4000, 0x7FFF); // Read
    const address_range switchableRamBank = address_range(0xA000, 0xBFFF); // Read/Write
    const address_range ramEnable         = address_range(0x0000, 0x1FFF); // Write
    const address_range romBankSelect     = address_range(0x2000, 0x3FFF); // Write
    const address_range ramBankSelect     = address_range(0x4000, 0x5FFF); // Write
    const address_range bankingmode       = address_range(0x6000, 0x7FFF); // Write
} // namespace MBC1_range
