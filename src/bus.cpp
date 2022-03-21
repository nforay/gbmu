/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bus.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:09:43 by nforay            #+#    #+#             */
/*   Updated: 2022/03/21 01:41:34 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bus.hpp"

Bus::Bus() { SPDLOG_TRACE("Bus Constructor"); }

Bus::~Bus() { SPDLOG_TRACE("Bus Destructor"); }

void Bus::write(const uint16_t &addr, const uint8_t data) {
    if (addr >= 0x0000 && addr <= 0xFFFF) {
        SPDLOG_TRACE("Bus write: 0x{:04X} = 0x{:02X}", addr, data);
        _ram[addr] = data;
    } else {
        SPDLOG_ERROR("Attempt to write in unmapped memory: 0x{:04X} = 0x{:02X}", addr, data);
    }
}

uint8_t Bus::read(const uint16_t &addr) const {
    if (addr >= 0x0000 && addr <= 0xFFFF) {
        SPDLOG_TRACE("Bus read: 0x{:04X} = 0x{:02X}", addr, _ram[addr]);
        return _ram[addr];
    } else {
        SPDLOG_ERROR("Attempt to read in unmapped memory: 0x{:04X}", addr);
        return 0x00;
    }
}

void Bus::reset() {
    SPDLOG_TRACE("Bus reset");
    _ram.fill(0x00);
    _ram[0xFF10] = 0x80;
    _ram[0xFF11] = 0xBF;
    _ram[0xFF12] = 0xF3;
    _ram[0xFF14] = 0xBF;
    _ram[0xFF16] = 0x3F;
    _ram[0xFF19] = 0xBF;
    _ram[0xFF1A] = 0x7F;
    _ram[0xFF1B] = 0xFF;
    _ram[0xFF1C] = 0x9F;
    _ram[0xFF1E] = 0xBF;
    _ram[0xFF20] = 0xFF;
    _ram[0xFF21] = 0x00;
    _ram[0xFF24] = 0x77;
    _ram[0xFF25] = 0xF3;
    _ram[0xFF26] = 0xF1;
    _ram[0xFF40] = 0x91;
    _ram[0xFF47] = 0xFC;
    _ram[0xFF48] = 0xFF;
    _ram[0xFF49] = 0xFF;
}
