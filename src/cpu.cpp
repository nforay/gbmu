/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:07:13 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 19:28:55 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.hpp"

Cpu::Cpu(Bus *bus) : Component(bus) { SPDLOG_TRACE("Cpu Constructor"); }

Cpu::~Cpu() { SPDLOG_TRACE("Cpu Destructor"); }

void Cpu::write(uint16_t addr, uint8_t data) { Component::write(addr, data); }

uint8_t Cpu::read(uint16_t addr) { return Component::read(addr); }

void Cpu::reset() { SPDLOG_TRACE("Cpu reset"); }

void Cpu::clock() { SPDLOG_TRACE("Cpu clock"); }

void Cpu::execute(uint8_t opcode, Reg::Word &pc) {
    if (opcode != 0xCB) {
        SPDLOG_TRACE("Cpu execute opcode 0x{:02X} : {}", opcode, opcode_names[opcode]);
        switch (opcode) {
        case 0x00:
            opcode_00();
            break;
        case 0x01:
            opcode_01();
            break;
        case 0x02:
            opcode_02();
            break;
        case 0x03:
            opcode_03();
            break;
        case 0x04:
            opcode_04();
            break;
        case 0x05:
            opcode_05();
            break;
        case 0x06:
            opcode_06();
            break;
        case 0x07:
            opcode_07();
            break;
        case 0x08:
            opcode_08();
            break;
        case 0x09:
            opcode_09();
            break;
        case 0x0A:
            opcode_0A();
            break;
        case 0x0B:
            opcode_0B();
            break;
        case 0x0C:
            opcode_0C();
            break;
        case 0x0D:
            opcode_0D();
            break;
        case 0x0E:
            opcode_0E();
            break;
        case 0x0F:
            opcode_0F();
            break;
        case 0x10:
            opcode_10();
            break;
        case 0x11:
            opcode_11();
            break;
        case 0x12:
            opcode_12();
            break;
        case 0x13:
            opcode_13();
            break;
        case 0x14:
            opcode_14();
            break;
        case 0x15:
            opcode_15();
            break;
        case 0x16:
            opcode_16();
            break;
        case 0x17:
            opcode_17();
            break;
        case 0x18:
            opcode_18();
            break;
        case 0x19:
            opcode_19();
            break;
        case 0x1A:
            opcode_1A();
            break;
        case 0x1B:
            opcode_1B();
            break;
        case 0x1C:
            opcode_1C();
            break;
        case 0x1D:
            opcode_1D();
            break;
        case 0x1E:
            opcode_1E();
            break;
        case 0x1F:
            opcode_1F();
            break;
        }
    } else {
        opcode = read(pc.get());
        SPDLOG_TRACE("Cpu execute opcode 0x{:02X} : {}", opcode, opcode_names[opcode]);
        switch (opcode) {}
    }
}