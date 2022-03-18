/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:55:20 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 19:10:29 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace Reg {
    class Byte {
    public:
        Byte() = default;
        Byte(uint8_t value);
        ~Byte();

        uint8_t get() const;
        bool    get_bit(uint8_t bit) const;
        void    set(uint8_t value);

        void reset();

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

    class Word {
    public:
        Word() = default;
        Word(uint16_t value);
        Word(Byte &high, Byte &low);
        ~Word();

        uint16_t get() const;
        bool     get_bit(uint8_t bit) const;
        void     set(uint16_t value);

        void reset();

        Byte low();
        Byte high();

    private:
        uint16_t _value = 0;
    };
} // namespace Reg
