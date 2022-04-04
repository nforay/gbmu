/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:10 by nforay            #+#    #+#             */
/*   Updated: 2022/04/04 19:13:02 by nforay           ###   ########.fr       */
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

void Ppu::reset() { SPDLOG_TRACE("Ppu reset"); }

bool Ppu::is_window_open() const { return _window.isOpen(); }

bool Ppu::is_window_focused() const { return _window.hasFocus(); }

void Ppu::clock() {
    SPDLOG_TRACE("Ppu clock");
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            SPDLOG_TRACE("Close Window");
            _window.close();
        }
    }
    _LY.inc();
}
