/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:10 by nforay            #+#    #+#             */
/*   Updated: 2022/04/05 15:49:05 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppu.hpp"

Ppu::Ppu(Bus *bus) : Component(bus) {
    SPDLOG_TRACE("Ppu Constructor");
    _window.create(sf::VideoMode(320, 288), "GBMU");
}

Ppu::~Ppu() { SPDLOG_TRACE("Ppu Destructor"); }

void Ppu::write(const uint16_t &addr, uint8_t data) { Component::write(addr, data); }

uint8_t Ppu::read(const uint16_t &addr) const { return Component::read(addr); }

void Ppu::reset() {
    SPDLOG_TRACE("Ppu reset");
    _mode   = VideoMode::ACCESS_OAM;
    _cycles = 0;
}

bool Ppu::is_window_open() const { return _window.isOpen(); }

bool Ppu::is_window_focused() const { return _window.hasFocus(); }

uint8_t Ppu::clock(const uint8_t &cycles) {
    SPDLOG_TRACE("Ppu clock - cycles = {} + {}", _cycles, cycles);
    _cycles += cycles;
    switch (_mode) {
    case VideoMode::ACCESS_OAM:
        if (_cycles >= CLOCKS_PER_SCANLINE_OAM) {
            _cycles = _cycles % CLOCKS_PER_SCANLINE_OAM;
            _mode   = VideoMode::ACCESS_VRAM;
            SPDLOG_INFO("switching to VideoMode::ACCESS_VRAM");
        }
        break;
    case VideoMode::ACCESS_VRAM:
        if (_cycles >= CLOCKS_PER_SCANLINE_VRAM) {
            _cycles = _cycles % CLOCKS_PER_SCANLINE_VRAM;
            _mode   = VideoMode::HBLANK;
            SPDLOG_INFO("switching to VideoMode::HBLANK");
        }
        break;
    case VideoMode::HBLANK:
        if (_cycles >= CLOCKS_PER_HBLANK) {
            _LY.inc();
            SPDLOG_INFO("Incrementing Current Scanline to {}", _LY.get());
            _cycles = _cycles % CLOCKS_PER_HBLANK;
            if (_LY.get() == 144) {
                _mode = VideoMode::VBLANK;
                SPDLOG_INFO("switching to VideoMode::VBLANK");
            } else {
                _mode = VideoMode::ACCESS_OAM;
                SPDLOG_INFO("switching to VideoMode::ACCESS_OAM");
            }
        }
        break;
    case VideoMode::VBLANK:
        if (_cycles >= CLOCKS_PER_SCANLINE) {
            _LY.inc();
            SPDLOG_INFO("Incrementing Current Scanline to {}", _LY.get());
            _cycles = _cycles % CLOCKS_PER_SCANLINE;
            if (_LY.get() == 154) {
                _LY.reset();
                SPDLOG_TRACE("Resetting Current Scanline to 0");
                _mode = VideoMode::ACCESS_OAM;
                SPDLOG_INFO("switching to VideoMode::ACCESS_OAM");
            }
        }
        break;
    }
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            SPDLOG_TRACE("Close Window");
            _window.close();
        }
    }
    return (0x00);
}
