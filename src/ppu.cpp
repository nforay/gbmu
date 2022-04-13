/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppu.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:09:10 by nforay            #+#    #+#             */
/*   Updated: 2022/04/13 23:01:02 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppu.hpp"

Ppu::Ppu(Bus *bus) : Component(bus) {
    SPDLOG_TRACE("Ppu Constructor");
    _window.create(sf::VideoMode(320, 288), "GBMU");
    _background_map_window.create(sf::VideoMode(256, 256), "Background Map");
    _tile_data_window.create(sf::VideoMode(128, 128), "Tile data");
    _tile_data.create(128, 128, sf::Color::Black);
    _font.loadFromFile("roms/victormono.ttf");
}

Ppu::~Ppu() { SPDLOG_TRACE("Ppu Destructor"); }

void Ppu::write(const uint16_t &addr, uint8_t data) {
    Component::write(addr, data);
    if (addr >= 0x8000 && addr <= 0x9FFF) {
        update_tile_data(addr, data); // debug
    }
}

uint8_t Ppu::read(const uint16_t &addr) const { return Component::read(addr); }

void Ppu::reset() {
    SPDLOG_TRACE("Ppu reset");
    _mode   = VideoMode::ACCESS_OAM;
    _cycles = 0;
    _vram.resize(128 * 128 * 4);

    // TMP:
    // 2 Bits per pixel (4 colors) https://www.huderlem.com/demos/gameboy2bpp.html
    std::vector<uint8_t> tmp_vram(16);
    tmp_vram = {0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83,
                0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};
    for (int i = 0; i < 16; i++) {
        write(0x8000 + i, tmp_vram[i]);
    }
    sf::Image test;
    test.create(128, 128, &_vram[0]);
    _tile_data_texture.loadFromImage(test);
}

bool Ppu::is_window_open() const { return _window.isOpen(); }

bool Ppu::is_window_focused() const { return _window.hasFocus(); }

#include <sstream>
void Ppu::display_scanline() {
    std::stringstream ss;
    ss << "Scanline: " << (int)_LY.get();
    sf::Text text;
    text.setString(ss.str());
    text.setFont(_font);
    text.setFillColor(sf::Color::White);
    _window.clear();
    _window.draw(text);
    _window.display();
}

uint8_t Ppu::clock(const uint8_t &cycles) {
    SPDLOG_TRACE("Ppu clock - cycles = {} + {}", _cycles, cycles);
    _cycles += cycles;
    switch (_mode) {
    case VideoMode::ACCESS_OAM:
        if (_cycles >= CLOCKS_PER_SCANLINE_OAM) {
            _cycles = _cycles % CLOCKS_PER_SCANLINE_OAM;
            _mode   = VideoMode::ACCESS_VRAM;
            _STAT.set_bit(0, true); // Screen Mode: H-Blank
            _STAT.set_bit(1, true); // Screen Mode: V-Blank
            SPDLOG_INFO("switching to VideoMode::ACCESS_VRAM");
        }
        break;
    case VideoMode::ACCESS_VRAM:
        if (_cycles >= CLOCKS_PER_SCANLINE_VRAM) {
            _cycles = _cycles % CLOCKS_PER_SCANLINE_VRAM;
            _mode   = VideoMode::HBLANK;
            _STAT.set_bit(0, false); // Screen Mode: H-Blank
            _STAT.set_bit(1, false); // Screen Mode: V-Blank
            SPDLOG_INFO("switching to VideoMode::HBLANK");
        }
        break;
    case VideoMode::HBLANK:
        if (_cycles >= CLOCKS_PER_HBLANK) {
            _LY.inc();
            SPDLOG_INFO("Incrementing Current Scanline to {}", _LY.get());
            display_scanline();
            _cycles = _cycles % CLOCKS_PER_HBLANK;
            if (_LY.get() == 144) {
                _mode = VideoMode::VBLANK;
                _STAT.set_bit(0, true);  // Screen Mode: H-Blank
                _STAT.set_bit(1, false); // Screen Mode: V-Blank
                SPDLOG_INFO("switching to VideoMode::VBLANK");
            } else {
                _mode = VideoMode::ACCESS_OAM;
                _STAT.set_bit(0, false); // Screen Mode: H-Blank
                _STAT.set_bit(1, true);  // Screen Mode: V-Blank
                SPDLOG_INFO("switching to VideoMode::ACCESS_OAM");
            }
        }
        break;
    case VideoMode::VBLANK:
        if (_cycles >= CLOCKS_PER_SCANLINE) {
            _LY.inc();
            SPDLOG_INFO("Incrementing Current Scanline to {}", _LY.get());
            display_scanline();
            _cycles = _cycles % CLOCKS_PER_SCANLINE;
            if (_LY.get() == 154) {
                // drawing screen happens here
                _LY.reset();
                SPDLOG_TRACE("Resetting Current Scanline to 0");
                _mode = VideoMode::ACCESS_OAM;
                _STAT.set_bit(0, false); // Screen Mode: H-Blank
                _STAT.set_bit(1, true);  // Screen Mode: V-Blank
                SPDLOG_INFO("switching to VideoMode::ACCESS_OAM");
            }
        }
        break;
    }
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            SPDLOG_TRACE("Close Window");
            _window.close();
            _background_map_window.close();
            _tile_data_window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                _tile_data_sprite.setTexture(_tile_data_texture);
                _tile_data_sprite.scale((float)_tile_data_window.getSize().x /
                                            (float)_tile_data.getSize().x,
                                        (float)_tile_data_window.getSize().y /
                                            (float)_tile_data.getSize().y);
                _tile_data_window.draw(_tile_data_sprite);
                _tile_data_window.display();
            }
        }
    }
    return (0x00);
}

void Ppu::update_tile_data(const uint16_t &addr, const uint8_t &data) {
    const sf::Color _palette[5] = {sf::Color(0xFF, 0xFF, 0xFF), sf::Color(0xAA, 0xAA, 0xAA),
                                   sf::Color(0x55, 0x55, 0x55), sf::Color(0, 0, 0), sf::Color(1, 1, 1, 0)};
    uint8_t         tile_x      = ((addr - 0x8000) % 0x800) / 0x80;
    uint8_t         tile_y      = (addr - 0x8000) / 0x800;
    uint8_t         line        = ((addr - 0x8000) % 0x80) / 0x2;
    uint8_t         upper       = addr & 0x1 ? data : Component::read(addr + 0x1);
    uint8_t         lower       = addr & 0x1 ? Component::read(addr - 0x1) : data;
    for (uint8_t pos_x = 0; pos_x < 8; pos_x++) {
        uint8_t color_index = (((upper >> (7 - pos_x)) & 0x1) << 1) | ((lower >> (7 - pos_x)) & 0x1);
        _vram[(tile_y * 0x400 + line * 0x80 + tile_x * 0x40 + pos_x) * 4] = _palette[color_index].r;
        _vram[(tile_y * 0x400 + line * 0x80 + tile_x * 0x40 + pos_x) * 4 + 1] =
            _palette[color_index].g;
        _vram[(tile_y * 0x400 + line * 0x80 + tile_x * 0x40 + pos_x) * 4 + 2] =
            _palette[color_index].b;
        _vram[(tile_y * 0x400 + line * 0x80 + tile_x * 0x40 + pos_x) * 4 + 3] = 0xFF;
    }
}
