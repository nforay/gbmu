/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:53:24 by nforay            #+#    #+#             */
/*   Updated: 2022/04/01 23:44:00 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <vector>

#include "cartridge_header.hpp"
#include "logger.h"

class Cartridge {
public:
    virtual ~Cartridge();

    virtual void    write(const uint16_t &addr, uint8_t data) = 0;
    virtual uint8_t read(const uint16_t &addr) const          = 0;

protected:
    Cartridge(const std::vector<uint8_t> &data, const CartridgeHeader &header);
    CartridgeHeader      _header;
    std::vector<uint8_t> _rom;
    std::vector<uint8_t> _ram;
};

class MBC1 : public Cartridge {
public:
    MBC1(const std::vector<uint8_t> &data, const CartridgeHeader &header);
    virtual ~MBC1();

    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;
};

class MBC2 : public Cartridge {
public:
    MBC2(const std::vector<uint8_t> &data, const CartridgeHeader &header);
    virtual ~MBC2();

    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;
};

class MBC3 : public Cartridge {
public:
    MBC3(const std::vector<uint8_t> &data, const CartridgeHeader &header);
    virtual ~MBC3();

    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;
};

class MBC5 : public Cartridge {
public:
    MBC5(const std::vector<uint8_t> &data, const CartridgeHeader &header);
    virtual ~MBC5();

    virtual void    write(const uint16_t &addr, uint8_t data);
    virtual uint8_t read(const uint16_t &addr) const;
};
