/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge_header.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:29:37 by nforay            #+#    #+#             */
/*   Updated: 2022/04/04 04:06:31 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cartridge_header.hpp"

std::string parseTitle(const std::vector<uint8_t> &data) {
    std::string title;
    for (int i = 0; data[header::Title + i] && i < 16; i++) {
        title += static_cast<char>(data[header::Title + i]);
    }
    return title;
}

CartridgeType parseCartridgeType(uint8_t code) {
    switch (code) {
    case 0x00: // ROM Only
    case 0x08: // ROM + RAM
    case 0x09: // ROM + RAM + Battery
        return CartridgeType::ROM_ONLY;
    case 0x01: // MBC1
    case 0x02: // MBC1 + RAM
    case 0x03: // MBC1 + RAM + Battery
        return CartridgeType::MBC1;
    case 0x05: // MBC2
    case 0x06: // MBC2 + RAM + Battery
        return CartridgeType::MBC2;
    case 0x0F: // MBC3 + Timer + Battery
    case 0x10: // MBC3 + RAM + Timer + Battery
    case 0x11: // MBC3
    case 0x12: // MBC3 + RAM
    case 0x13: // MBC3 + RAM + Battery
        return CartridgeType::MBC3;
    case 0x19: // MBC5
    case 0x1A: // MBC5 + RAM
    case 0x1B: // MBC5 + RAM + Battery
    case 0x1C: // MBC5 + Rumble
    case 0x1D: // MBC5 + RAM + Rumble
    case 0x1E: // MBC5 + RAM + Battery + Rumble
        return CartridgeType::MBC5;
    default:
        SPDLOG_ERROR("Unknown cartridge type: {}", code);
        return CartridgeType::UNKNOWN;
    }
}

ROMSize parseROMSize(uint8_t code) {
    switch (code) {
    case 0x00:
        return ROMSize::KB32;
    case 0x01:
        return ROMSize::KB64;
    case 0x02:
        return ROMSize::KB128;
    case 0x03:
        return ROMSize::KB256;
    case 0x04:
        return ROMSize::KB512;
    case 0x05:
        return ROMSize::MB1;
    case 0x06:
        return ROMSize::MB2;
    case 0x07:
        return ROMSize::MB4;
    case 0x08:
        return ROMSize::MB8;
    default:
        SPDLOG_ERROR("Unknown ROM size: {}", code);
        return ROMSize::KB32;
    }
}

RAMSize parseRAMSize(uint8_t code) {
    switch (code) {
    case 0x00:
        return RAMSize::KB0;
    case 0x01:
        return RAMSize::KB2;
    case 0x02:
        return RAMSize::KB8;
    case 0x03:
        return RAMSize::KB32;
    case 0x04:
        return RAMSize::KB128;
    case 0x05:
        return RAMSize::KB64;
    default:
        SPDLOG_ERROR("Unknown RAM size: {}", code);
        return RAMSize::KB0;
    }
}

CartridgeHeader parseHeader(const std::vector<uint8_t> &data) {
    CartridgeHeader header;
    header.title          = parseTitle(data);
    header.cartridgeType  = parseCartridgeType(data[header::CartridgeType]);
    header.romSize        = parseROMSize(data[header::ROMSize]);
    header.ramSize        = parseRAMSize(data[header::RAMSize]);
    header.headerChecksum = data[header::HeaderChecksum];
    header.globalChecksum = ((data[header::GlobalChecksum] << 8) | data[header::GlobalChecksum + 1]);
    header.cgbFlag        = data[header::CGBFlag];
    return header;
}

uint32_t CartridgeHeader::getRamSize() const {
    switch (this->ramSize) {
    case RAMSize::KB0:
        return 0;
    case RAMSize::KB2:
        return (2 * 1024);
    case RAMSize::KB8:
        return (8 * 1024);
    case RAMSize::KB32:
        return (8 * 1024);
    case RAMSize::KB128:
        return (32 * 1024);
    case RAMSize::KB64:
        return (64 * 1024);
    default:
        return 0;
    }
}

bool checkHeaderChecksum(const std::vector<uint8_t> &data) {
    uint8_t checksum = 0;
    for (int i = header::Title; i < header::HeaderChecksum; i++) {
        checksum -= data[i] - 1;
    }
    return checksum == data[header::HeaderChecksum];
}

bool checkGlobalChecksum(const std::vector<uint8_t> &data) {
    uint16_t checksum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (i != header::GlobalChecksum && i != header::GlobalChecksum + 1) {
            checksum += data[i];
        }
    }
    return checksum == ((data[header::GlobalChecksum] << 8) | data[header::GlobalChecksum + 1]);
}