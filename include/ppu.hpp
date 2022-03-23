/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:13 by nforay            #+#    #+#             */
/*   Updated: 2022/03/23 17:23:46 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Window.hpp>

#include "component.hpp"
#include "logger.h"

class Ppu : public Component {

public:
    Ppu(Bus *bus);
    virtual ~Ppu();

    virtual void    reset();
    virtual void    clock();
    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;

    bool is_window_open() const;
    bool is_window_focused() const;

private:
    sf::Window window;
};
