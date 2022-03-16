/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:10 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:21:01 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppu.hpp"

Ppu::Ppu(Bus *bus) : Component(bus) { SPDLOG_TRACE("Ppu Constructor"); }

Ppu::~Ppu() { SPDLOG_TRACE("Ppu Destructor"); }

void Ppu::write(uint16_t addr, uint8_t data) { Component::write(addr, data); }

uint8_t Ppu::read(uint16_t addr) { return Component::read(addr); }

void Ppu::reset() { SPDLOG_TRACE("Ppu reset"); }

void Ppu::clock() { SPDLOG_TRACE("Ppu clock"); }
