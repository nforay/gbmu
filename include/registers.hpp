/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:55:20 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 18:55:05 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace Reg {
    class BytePtr {
    public:
        BytePtr(uint8_t *addr);
        ~BytePtr() = default;

        uint8_t get() const;
        bool    get_bit(uint8_t bit) const;
        void    set_bit(uint8_t bit, bool value);
        void    set(uint8_t value);
        void    inc();
        void    dec();
        void    reset();

    private:
        uint8_t *_ptr;
    };

    class Byte {
    public:
        Byte() = default;
        Byte(uint8_t value);
        ~Byte() = default;

        uint8_t get() const;
        bool    get_bit(uint8_t bit) const;
        void    set_bit(uint8_t bit, bool value);
        void    set(uint8_t value);
        void    inc();
        void    dec();
        void    reset();

    private:
        uint8_t _value = 0;
    };

    class Flag : public Byte {
    public:
        bool get_zero() const;
        bool get_sub() const;
        bool get_half_carry() const;
        bool get_carry() const;
        void set_zero(bool value);
        void set_sub(bool value);
        void set_half_carry(bool value);
        void set_carry(bool value);
    };

    class BytePair {
    public:
        BytePair(Byte &high, Byte &low);
        ~BytePair() = default;

        Byte &   high() const;
        Byte &   low() const;
        void     set(uint16_t value);
        uint16_t get() const;
        void     reset();
        void     inc();
        void     dec();

    private:
        Byte &_high;
        Byte &_low;
    };

    class Word {
    public:
        Word() = default;
        Word(uint16_t value);
        Word(Byte &high, Byte &low);
        Word(const uint8_t &high, const uint8_t &low);
        ~Word() = default;

        uint16_t get() const;
        bool     get_bit(uint8_t bit) const;
        void     set(uint16_t value);
        void     reset();
        void     inc();
        void     dec();
        uint8_t  low() const;
        uint8_t  high() const;

    private:
        uint16_t _value = 0;
    };
} // namespace Reg
