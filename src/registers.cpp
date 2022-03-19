/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:19:22 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 15:46:59 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "registers.hpp"

Reg::Byte::Byte(uint8_t value) : _value(value) {}

Reg::Byte::~Byte() {}

uint8_t Reg::Byte::get() const { return _value; }

bool Reg::Byte::get_bit(uint8_t bit) const { return (_value >> bit) & 1; }

void Reg::Byte::set_bit(uint8_t bit, bool value) {
    if (value)
        _value |= (1 << bit);
    else
        _value &= ~(1 << bit);
}

void Reg::Byte::set(uint8_t value) { _value = value; }

void Reg::Byte::reset() { _value = 0; }

void Reg::Byte::inc() { _value++; }

void Reg::Byte::dec() { _value--; }

bool Reg::Flag::get_zero() const { return get_bit(7); }

bool Reg::Flag::get_sub() const { return get_bit(6); }

bool Reg::Flag::get_half_carry() const { return get_bit(5); }

bool Reg::Flag::get_carry() const { return get_bit(4); }

void Reg::Flag::set_zero(bool value) { set_bit(7, value); }

void Reg::Flag::set_sub(bool value) { set_bit(6, value); }

void Reg::Flag::set_half_carry(bool value) { set_bit(5, value); }

void Reg::Flag::set_carry(bool value) { set_bit(4, value); }

Reg::BytePair::BytePair(Byte &high, Byte &low) : _high(high), _low(low) {}

Reg::BytePair::~BytePair() {}

Reg::Byte &Reg::BytePair::high() const { return _high; }

Reg::Byte &Reg::BytePair::low() const { return _low; }

void Reg::BytePair::set(uint16_t value) {
    _high.set((value & 0xFF00) >> 8);
    _low.set(value & 0x00FF);
}

uint16_t Reg::BytePair::get() const { return (_high.get() << 8) | _low.get(); }

void Reg::BytePair::reset() {
    _high.reset();
    _low.reset();
}

void Reg::BytePair::inc() {
    uint16_t value = get();
    value++;
    set(value);
}

void Reg::BytePair::dec() {
    uint16_t value = get();
    value--;
    set(value);
}

Reg::Word::Word(uint16_t value) : _value(value) {}

Reg::Word::~Word() {}

Reg::Word::Word(Byte &high, Byte &low) : _value(high.get() << 8 | low.get()) {}

Reg::Word::Word(const uint8_t &high, const uint8_t &low) : _value(high << 8 | low) {}

uint16_t Reg::Word::get() const { return _value; }

bool Reg::Word::get_bit(uint8_t bit) const { return (_value >> bit) & 1; }

void Reg::Word::set(uint16_t value) { _value = value; }

void Reg::Word::reset() { _value = 0; }

void Reg::Word::inc() { _value++; }

void Reg::Word::dec() { _value--; }

Reg::Byte Reg::Word::low() { return Reg::Byte(_value & 0xFF); } // 00000000 11111111

Reg::Byte Reg::Word::high() { return Reg::Byte(_value >> 8); }