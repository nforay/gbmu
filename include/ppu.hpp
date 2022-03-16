/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:13 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:36:33 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "component.hpp"
#include "logger.h"

class Ppu : public Component {

public:
    Ppu(Bus *bus);
    virtual ~Ppu();

    virtual void    reset();
    virtual void    clock();
    virtual void    write(uint16_t addr, uint8_t data);
    virtual uint8_t read(uint16_t addr);
};
