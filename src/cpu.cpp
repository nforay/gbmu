/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:07:13 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:06:56 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.hpp"

Cpu::Cpu(Bus *bus) : Component(bus) { SPDLOG_TRACE("Cpu Constructor"); }

Cpu::~Cpu() { SPDLOG_TRACE("Cpu Destructor"); }

void Cpu::write(uint16_t addr, uint8_t data) { Component::write(addr, data); }

uint8_t Cpu::read(uint16_t addr) { return Component::read(addr); }

void Cpu::reset() { SPDLOG_TRACE("Cpu reset"); }

void Cpu::clock() { SPDLOG_TRACE("Cpu clock"); }
