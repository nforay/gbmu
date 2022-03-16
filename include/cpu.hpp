/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:05:43 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:36:31 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "component.hpp"
#include "logger.h"

class Cpu : public Component {

public:
    Cpu(Bus *bus);
    virtual ~Cpu();

    virtual void    reset();
    virtual void    clock();
    virtual void    write(uint16_t addr, uint8_t data);
    virtual uint8_t read(uint16_t addr);
};
