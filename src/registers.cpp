/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:19:22 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 17:49:59 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "registers.hpp"

Register::Byte::Byte(uint8_t value) : _value(value) {}

Register::Byte::~Byte() {}

uint8_t Register::Byte::get() const { return _value; }

bool Register::Byte::get_bit(uint8_t bit) const { return (_value >> bit) & 1; }

void Register::Byte::set(uint8_t value) { _value = value; }

void Register::Byte::reset() { _value = 0; }

bool Register::Flag::get_zero() const { return get_bit(7); }

bool Register::Flag::get_sub() const { return get_bit(6); }

bool Register::Flag::get_half_carry() const { return get_bit(5); }

bool Register::Flag::get_carry() const { return get_bit(4); }

void Register::Flag::set_zero(bool value) { set_bit(7, value); }

void Register::Flag::set_sub(bool value) { set_bit(6, value); }

void Register::Flag::set_half_carry(bool value) { set_bit(5, value); }

void Register::Flag::set_carry(bool value) { set_bit(4, value); }

Register::Word::Word(uint16_t value) : _value(value) {}

Register::Word::~Word() {}

Register::Word::Word(Byte &high, Byte &low) : _value(high.get() << 8 | low.get()) {}

uint16_t Register::Word::get() const { return _value; }

bool Register::Word::get_bit(uint8_t bit) const { return (_value >> bit) & 1; }

void Register::Word::set(uint16_t value) { _value = value; }

void Register::Word::reset() { _value = 0; }

Byte Register::Word::low() { return Byte(_value & 0xFF); } // 00000000 11111111

Byte Register::Word::high() { return Byte(_value >> 8); }