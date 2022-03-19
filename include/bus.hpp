/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bus.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:07:03 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 15:44:21 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <stdint.h>

#include "logger.h"

class Bus {

public:
    Bus();
    ~Bus();
    void    write(uint16_t addr, const uint8_t data);
    uint8_t read(uint16_t addr);

    std::array<u_int8_t, 64 * 1024> _ram;
};
