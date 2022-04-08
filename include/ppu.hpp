/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:13 by nforay            #+#    #+#             */
/*   Updated: 2022/04/08 17:21:45 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "component.hpp"
#include "logger.h"
#include "registers.hpp"

enum class VideoMode {
    ACCESS_OAM = 0,
    ACCESS_VRAM,
    HBLANK,
    VBLANK,
};

class Ppu : public Component {

public:
    Ppu(Bus *bus);
    virtual ~Ppu();

    virtual void    reset();
    virtual uint8_t clock() { return 0x00; };
    virtual uint8_t clock(const uint8_t &cycles);
    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;

    bool is_window_open() const;
    bool is_window_focused() const;
    void update_tile_data(const uint16_t &addr, const uint8_t &data);

private:
    sf::RenderWindow       _window;
    sf::RenderWindow       _background_map_window;
    sf::RenderWindow       _tile_data_window;
    sf::Image              _tile_data;
    std::vector<sf::Uint8> _vram{std::vector<sf::Uint8>(128 * 128 * 4, 0xFF)};
    uint                   _cycles{0};
    VideoMode              _mode{VideoMode::ACCESS_OAM};
    Reg::BytePtr           _LCDC  = Component::getPointer(0xFF40);
    Reg::BytePtr           _STAT  = Component::getPointer(0xFF41);
    Reg::BytePtr           _SCY   = Component::getPointer(0xFF42);
    Reg::BytePtr           _SCX   = Component::getPointer(0xFF43);
    Reg::BytePtr           _LY    = Component::getPointer(0xFF44);
    Reg::BytePtr           _LYC   = Component::getPointer(0xFF45);
    Reg::BytePtr           _DMA   = Component::getPointer(0xFF46);
    Reg::BytePtr           _BGP   = Component::getPointer(0xFF47);
    Reg::BytePtr           _OBP0  = Component::getPointer(0xFF48);
    Reg::BytePtr           _OBP1  = Component::getPointer(0xFF49);
    Reg::BytePtr           _WY    = Component::getPointer(0xFF4A);
    Reg::BytePtr           _WX    = Component::getPointer(0xFF4B);
    Reg::BytePtr           _HDMA1 = Component::getPointer(0xFF51);
    Reg::BytePtr           _HDMA2 = Component::getPointer(0xFF52);
    Reg::BytePtr           _HDMA3 = Component::getPointer(0xFF53);
    Reg::BytePtr           _HDMA4 = Component::getPointer(0xFF54);
    Reg::BytePtr           _HDMA5 = Component::getPointer(0xFF55);
    Reg::BytePtr           _BCPS  = Component::getPointer(0xFF68);
    Reg::BytePtr           _BCPD  = Component::getPointer(0xFF69);
    Reg::BytePtr           _OCPS  = Component::getPointer(0xFF6A);
    Reg::BytePtr           _OCPD  = Component::getPointer(0xFF6B);
};

const uint CLOCKS_PER_HBLANK        = 204;
const uint CLOCKS_PER_SCANLINE_OAM  = 80;
const uint CLOCKS_PER_SCANLINE_VRAM = 172;
const uint CLOCKS_PER_SCANLINE      = 456;
