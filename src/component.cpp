/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:15:39 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 19:00:48 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component.hpp"

Component::Component(Bus *bus) : _bus(bus) { SPDLOG_TRACE("Component Constructor"); }

Component::~Component() { SPDLOG_TRACE("Component Destructor"); }

void Component::write(const uint16_t &addr, const uint8_t &data) { _bus->write(addr, data); }

uint8_t Component::read(const uint16_t &addr) const { return _bus->read(addr); }

uint8_t *Component::getPointer(const uint16_t &addr) const { return &_bus->_ram[addr]; }