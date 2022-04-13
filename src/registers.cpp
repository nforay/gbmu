/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:19:22 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 18:21:53 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "registers.hpp"

Reg::BytePtr::BytePtr(uint8_t *addr) : _ptr(addr) {}

uint8_t Reg::BytePtr::get() const { return *_ptr; }

bool Reg::BytePtr::get_bit(uint8_t bit) const { return (*_ptr >> bit) & 1; }

void Reg::BytePtr::set_bit(uint8_t bit, bool value) {
    if (value)
        *_ptr |= (1 << bit);
    else
        *_ptr &= ~(1 << bit);
}

void Reg::BytePtr::set(uint8_t value) { *_ptr = value; }

void Reg::BytePtr::reset() { *_ptr = 0; }

void Reg::BytePtr::inc() { (*_ptr)++; }

void Reg::BytePtr::dec() { (*_ptr)--; }

Reg::Byte::Byte(uint8_t value) : _value(value) {}

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

Reg::BytePair::BytePair(Reg::Byte &high, Reg::Byte &low) : _high(high), _low(low) {}

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

Reg::Word::Word(Reg::Byte &high, Reg::Byte &low) : _value(high.get() << 8 | low.get()) {}

Reg::Word::Word(const uint8_t &high, const uint8_t &low) : _value(high << 8 | low) {}

uint16_t Reg::Word::get() const { return _value; }

bool Reg::Word::get_bit(uint8_t bit) const { return (_value >> bit) & 1; }

void Reg::Word::set(uint16_t value) { _value = value; }

void Reg::Word::reset() { _value = 0; }

void Reg::Word::inc() { _value++; }

void Reg::Word::dec() { _value--; }

uint8_t Reg::Word::low() const { return _value & 0xFF; } // 00000000 11111111

uint8_t Reg::Word::high() const { return _value >> 8; }