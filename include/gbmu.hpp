/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbmu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:49 by nforay            #+#    #+#             */
/*   Updated: 2022/03/20 02:08:42 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <vector>

#include "cpu.hpp"
#include "logger.h"
#include "ppu.hpp"


class Gbmu {

public:
    Gbmu();
    ~Gbmu();

    void init();
    void reset();
    void run();
    void insert_cartridge(std::string filename);

private:
    std::unique_ptr<Bus>                    _bus{std::make_unique<Bus>()};
    std::shared_ptr<Cpu>                    _cpu;
    std::shared_ptr<Ppu>                    _ppu;
    std::vector<std::shared_ptr<Component>> _components;
};
