/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbmu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:49 by nforay            #+#    #+#             */
/*   Updated: 2022/03/17 18:56:21 by nforay           ###   ########.fr       */
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
    for (auto component : _components) {
        component->clock();
    }
    if (_cpu->read(0x0000) == 0x01) {
        SPDLOG_INFO("Gbmu bus ok");
    }
}

void Gbmu::insert_cartridge(std::string filename) {
    SPDLOG_INFO("Gbmu insert_cartridge: {}", filename);
}
