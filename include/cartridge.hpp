/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:24 by nforay            #+#    #+#             */
/*   Updated: 2022/03/31 18:30:00 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>

#include "cartridge_header.hpp"
#include "component.hpp"
#include "logger.h"

enum class CartridgeType { ROM_ONLY, MBC1, MBC2, MBC3, MBC5, UNKNOWN };

namespace header {
    const uint16_t EntryPoint       = 0x0100;
    const uint16_t NintendoGraphic  = 0x0104;
    const uint16_t Title            = 0x0134;
    const uint16_t ManufacturerCode = 0x013F;
    const uint16_t CGBFlag          = 0x0143;
    const uint16_t NewLicenseCode   = 0x0144;
    const uint16_t SGBFlag          = 0x0146;
    const uint16_t CartridgeType    = 0x0147;
    const uint16_t ROMSize          = 0x0148;
    const uint16_t RAMSize          = 0x0149;
    const uint16_t DestinationCode  = 0x014A;
    const uint16_t OldLicenseCode   = 0x014B;
    const uint16_t MaskROMVersion   = 0x014C;
    const uint16_t HeaderChecksum   = 0x014D;
    const uint16_t GlobalChecksum   = 0x014E;

} // namespace header

enum class ROMSize {
    KB32,
    KB64,
    KB128,
    KB256,
    KB512,
    MB1,
    MB2,
    MB4,
    MB8,
};

enum class RAMSize {
    KB0,
    KB2,
    KB8,
    KB32,
    KB128,
    KB64,
};

class CartridgeHeader { // unused: newLicense, destination, oldLicense, ManufacturerCode
public:
    std::string   title;
    CartridgeType type;
    ROMSize       romSize;
    RAMSize       ramSize;
    uint8_t       romVersion;
    uint16_t      headerChecksum;
    uint16_t      globalChecksum;
    bool          cgbFlag;
    bool          sgbFlag;
};

class Cartridge : public Component {
public:
    ~Cartridge();

    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;
    void            reset(){};
    void            clock(){};

protected:
    Cartridge(Bus *bus);
    std::unique_ptr<CartridgeHeader> _header;
    std::vector<uint8_t>             _rom;
};

class MBC1 : public Cartridge {
public:
    MBC1(Bus *bus, const std::vector<uint8_t> &data);
    ~MBC1();
};

class MBC2 : public Cartridge {
public:
    MBC2(Bus *bus, const std::vector<uint8_t> &data);
    ~MBC2();
};

class MBC3 : public Cartridge {
public:
    MBC3(Bus *bus, const std::vector<uint8_t> &data);
    ~MBC3();
};

class MBC5 : public Cartridge {
public:
    MBC5(Bus *bus, const std::vector<uint8_t> &data);
    ~MBC5();
};
