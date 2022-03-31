/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbmu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:49 by nforay            #+#    #+#             */
/*   Updated: 2022/03/31 18:31:28 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gbmu.hpp"

#include <fstream>  //TODO: wrapper for cartridge
#include <unistd.h> //tmp usleep()

Gbmu::Gbmu() {
    SPDLOG_TRACE("Gbmu Constructor");
    init();
}

Gbmu::~Gbmu() { SPDLOG_TRACE("Gbmu Destructor"); }

void Gbmu::init() {
    SPDLOG_TRACE("Gbmu init");
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
    _bus->reset();
}

void Gbmu::run() {
    SPDLOG_INFO("Gbmu run");
    while (_ppu.get()->is_window_open()) {
        if (_ppu.get()->is_window_focused()) {
            u_int8_t opcode = _cpu->read(_cpu->pc.get());
            _cpu->pc.inc();
            _cpu->execute(opcode, _cpu->pc);
            usleep(1000 * 100);
            SPDLOG_INFO("Registers: af: 0x{:04X}, bc: 0x{:04X}, de: 0x{:04X}, hl: 0x{:04X}, sp: "
                        "0x{:04X}, pc: 0x{:04X}",
                        _cpu->af.get(), _cpu->bc.get(), _cpu->de.get(), _cpu->hl.get(),
                        _cpu->sp.get(), _cpu->pc.get());
            _ppu->clock();
        } else {
            usleep(100);
        }
    }
}

void Gbmu::insert_cartridge(std::string filename) {
    SPDLOG_INFO("Gbmu insert_cartridge: {}", filename);
    std::ifstream file_stream(filename.c_str(), std::ios::binary | std::ios::ate);
    if (!file_stream.good()) {
        SPDLOG_ERROR("Error opening file: {}", filename);
        return;
    }
    std::ifstream::pos_type position  = file_stream.tellg();
    auto                    file_size = static_cast<size_t>(position);
    std::vector<char>       cartridge_rom(file_size);

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(&cartridge_rom[0], static_cast<std::streamsize>(position));
    file_stream.close();

    auto data  = std::vector<uint8_t>(cartridge_rom.begin(), cartridge_rom.end());
    _cartridge = std::make_shared<Cartridge>(_bus.get(), data);
    int size   = cartridge_rom.size() > 0x7FFF ? 0x7FFF : cartridge_rom.size(); // HACK
    for (int i = 0; i < size; i++) {
        _bus->_ram[i] = cartridge_rom[i];
    }
}
