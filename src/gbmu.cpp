/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbmu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:49 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 14:46:26 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gbmu.hpp"

Gbmu::Gbmu() { SPDLOG_TRACE("Gbmu Constructor"); }

Gbmu::~Gbmu() { SPDLOG_TRACE("Gbmu Destructor"); }

void Gbmu::init() {
    SPDLOG_INFO("Gbmu init");
    _cpu = std::make_shared<Cpu>(_bus.get());
    _ppu = std::make_shared<Ppu>(_bus.get());
    _components.emplace_back(_cpu);
    _components.emplace_back(_ppu);
}

void Gbmu::reset() {
    SPDLOG_INFO("Gbmu reset");
    for (auto component : _components) {
        component->reset();
    }
}

void Gbmu::run() {
    SPDLOG_INFO("Gbmu run");
    _cpu->write(0x0000, 0x01);
    _cpu->write(0x1337, 0x42);
    for (auto component : _components) {
        component->clock();
    }
    if (_cpu->read(0x0000) == 0x01) {
        SPDLOG_INFO("Gbmu bus ok");
    }
    _cpu->execute(0x00, _cpu->pc);
    _cpu->execute(0xCB, _cpu->pc);
    _cpu->execute(0xD3, _cpu->pc);
    _cpu->execute(0x10, _cpu->pc);
    _cpu->b.set(0x13);
    _cpu->c.set(0x37);
    _cpu->read(_cpu->bc.get());
    _cpu->write(0x0001, 0x37);
    _cpu->write(0x0002, 0x13);
    _cpu->pc.set(0x0001);
    _cpu->execute(0xFA, _cpu->pc);
}

void Gbmu::insert_cartridge(std::string filename) {
    SPDLOG_INFO("Gbmu insert_cartridge: {}", filename);
}
