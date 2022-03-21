/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:10 by nforay            #+#    #+#             */
/*   Updated: 2022/03/21 01:18:17 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppu.hpp"

Ppu::Ppu(Bus *bus) : Component(bus) { SPDLOG_TRACE("Ppu Constructor"); }

Ppu::~Ppu() { SPDLOG_TRACE("Ppu Destructor"); }

void Ppu::write(const uint16_t &addr, uint8_t data) { Component::write(addr, data); }

uint8_t Ppu::read(const uint16_t &addr) const { return Component::read(addr); }

void Ppu::reset() { SPDLOG_TRACE("Ppu reset"); }

void Ppu::clock() { SPDLOG_TRACE("Ppu clock"); }
