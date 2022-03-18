/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:53 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 23:12:05 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.hpp"

/**
 * @brief      No operation
 */
void Cpu::instr_nop(){};

/**
 * @brief      Power down CPU until an interrupt occurs. Use this when ever
 * possible to reduce energy consumption.
 */
void Cpu::instr_halt(){}; // TODO: Implement

/**
 * @brief      Halt CPU & LCD display until button pressed
 */
void Cpu::instr_stop(){}; // TODO: Implement

/**
 * @brief      This instruction disables interrupts but not immediately.
 * Interrupts are disabled after instruction after DI is executed.
 */
void Cpu::instr_di(){}; // TODO: Implement

/**
 * @brief      Enable interrupts. This intruction enables interrupts but not
 * immediately. Interrupts are enabled after instruction after EI is executed.
 */
void Cpu::instr_ei(){}; // TODO: Implement

/**
 * @brief      Put value at pc into register
 * @param      dst  The 8-bit destination register
 */
void Cpu::instr_ld(Reg::Byte &dst) {
    uint8_t value = Cpu::read(pc.get());
    dst.set(value);
};

/**
 * @brief      Put value src into dst.
 * @param      dst  The 8-bit destination register
 * @param      src  The 8-bit source register
 */
void Cpu::instr_ld(Reg::Byte &dst, const Reg::Byte &src) { dst.set(src.get()); };

/**
 * @brief      Put value at src into dst.
 * @param      dst  The 8-bit destination register
 * @param      src  The 16-bit source register pair (HL)
 */
void Cpu::instr_ld(Reg::Byte &dst, const Reg::Word &src) { dst.set(Cpu::read(src.get())); };

/**
 * @brief      Write value from src at dst.
 * @param      dst  The 16-bit destination address
 * @param      src  The 8-bit source register
 */
void Cpu::instr_ld(const Reg::Word &dst, const Reg::Byte &src) {
    Cpu::write(dst.get(), src.get()); // TODO: check behaviour
};

/**
 * @brief      Write 8-bit immediate value at dst.
 * @param      dst The 16-bit destination address
 */
void Cpu::instr_ld(const Reg::Word &dst) {
    uint8_t value = Cpu::read(pc.get());
    Cpu::write(dst.get(), value);
};

void Cpu::instr_cb(){};
void Cpu::instr_jr(){};
void Cpu::instr_jr(Cpu::Condition cond){};
void Cpu::instr_jp(){};
void Cpu::instr_jp(Cpu::Condition cond){};
void Cpu::instr_jp(uint16_t){};
void Cpu::instr_ret(){};
void Cpu::instr_ret(Cpu::Condition cond){};
void Cpu::instr_reti(){};
void Cpu::instr_call(){};
void Cpu::instr_call(Cpu::Condition cond){};
void Cpu::instr_rst(){};
void Cpu::instr_ld(uint16_t){};
void Cpu::instr_inc(uint8_t){};
void Cpu::instr_inc(uint16_t){};
void Cpu::instr_dec(uint8_t){};
void Cpu::instr_dec(uint16_t){};
void Cpu::instr_daa(){};
void Cpu::instr_scf(){};
void Cpu::instr_cpl(){};
void Cpu::instr_ccf(){};
void Cpu::instr_add(){};
void Cpu::instr_adc(){};
void Cpu::instr_sub(){};
void Cpu::instr_sbc(){};
void Cpu::instr_and(uint8_t){};
void Cpu::instr_and(uint16_t){};
void Cpu::instr_xor(uint8_t){};
void Cpu::instr_xor(uint16_t){};
void Cpu::instr_or(uint8_t){};
void Cpu::instr_or(uint16_t){};
void Cpu::instr_cp(){};
void Cpu::instr_inc(Reg::Word){};
void Cpu::instr_add(Reg::Word){};
void Cpu::instr_dec(Reg::Word){};
void Cpu::instr_rlca(){};
void Cpu::instr_rla(){};
void Cpu::instr_rrca(){};
void Cpu::instr_rra(){};
void Cpu::instr_rlc(){};
void Cpu::instr_rl(){};
void Cpu::instr_rrc(){};
void Cpu::instr_rr(){};
void Cpu::instr_sla(){};
void Cpu::instr_sra(){};
void Cpu::instr_swap(){};
void Cpu::instr_srl(){};
void Cpu::instr_bit(){};
void Cpu::instr_res(){};
void Cpu::instr_set(){};
