/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:05:07 by nforay            #+#    #+#             */
/*   Updated: 2022/03/16 23:36:27 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include "bus.hpp"

class Component {

public:
    virtual ~Component();

    virtual void    reset() = 0;
    virtual void    clock() = 0;
    virtual void    write(uint16_t addr, uint8_t data);
    virtual uint8_t read(uint16_t addr) const;

protected:
    Component(Bus *bus);

private:
    Bus *_bus;
};
