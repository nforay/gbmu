/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bus.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:07:03 by nforay            #+#    #+#             */
/*   Updated: 2022/03/30 18:47:58 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <memory>
#include <stdint.h>

#include "cartridge.hpp"
#include "logger.h"

class Bus {

public:
    Bus();
    ~Bus();
    void    write(const uint16_t &addr, const uint8_t data);
    uint8_t read(const uint16_t &addr) const;
    void    reset();

    std::array<uint8_t, 64 * 1024> _ram;
    std::array<uint8_t, 256>       _bootrom;
    std::shared_ptr<Cartridge>     _cartridge;
};
