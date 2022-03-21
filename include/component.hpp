/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:05:07 by nforay            #+#    #+#             */
/*   Updated: 2022/03/21 01:14:57 by nforay           ###   ########.fr       */
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
    virtual void    write(const uint16_t &addr, const uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;

protected:
    Component(Bus *bus);

private:
    Bus *_bus;
};
