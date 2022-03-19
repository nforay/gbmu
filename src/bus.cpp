/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bus.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:09:43 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 15:44:12 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bus.hpp"

Bus::Bus() { SPDLOG_TRACE("Bus Constructor"); }

Bus::~Bus() { SPDLOG_TRACE("Bus Destructor"); }

void Bus::write(uint16_t addr, const uint8_t data) {
    if (addr >= 0x0000 && addr <= 0xFFFF) {
        SPDLOG_TRACE("Bus write: 0x{:04X} = 0x{:02X}", addr, data);
        _ram[addr] = data;
    } else {
        SPDLOG_ERROR("Attempt to write in unmapped memory: 0x{:04X} = 0x{:02X}", addr, data);
    }
}

u_int8_t Bus::read(uint16_t addr) {
    if (addr >= 0x0000 && addr <= 0xFFFF) {
        SPDLOG_TRACE("Bus read: 0x{:04X} = 0x{:02X}", addr, _ram[addr]);
        return _ram[addr];
    } else {
        SPDLOG_ERROR("Attempt to read in unmapped memory: 0x{:04X}", addr);
        return 0x00;
    }
}
