/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge_header.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:29:31 by nforay            #+#    #+#             */
/*   Updated: 2022/04/01 16:27:43 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <string>

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
    KB32 = 0,
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
    KB0 = 0,
    KB2,
    KB8,
    KB32,
    KB128,
    KB64,
};

class CartridgeHeader { // unused: newLicense, destination, oldLicense, ManufacturerCode, SGBFlag
public:
    std::string   title;
    CartridgeType cartridgeType;
    ROMSize       romSize;
    RAMSize       ramSize;
    uint8_t       romVersion;
    uint8_t       headerChecksum;
    uint16_t      globalChecksum;
    uint8_t       cgbFlag;
};

std::string parseTitle(const std::vector<uint8_t> &data);

CartridgeType parseCartridgeType(uint8_t code);

ROMSize parseROMSize(uint8_t code);

RAMSize parseRAMSize(uint8_t code);

CartridgeHeader parseHeader(const std::vector<uint8_t> &data);

bool checkHeaderChecksum(const std::vector<uint8_t> &data);

bool checkGlobalChecksum(const std::vector<uint8_t> &data);