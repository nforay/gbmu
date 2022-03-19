/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:53 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 02:28:56 by nforay           ###   ########.fr       */
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
    pc.inc();
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

/**
 * @brief      Write 8-bit value from 16-bit immediate value (LS byte 1st) to dst.
 * @param      dst The 8-bit destination register
 */
void Cpu::instr_ld_nn_from(Reg::Byte &dst) {
    uint8_t low = Cpu::read(pc.get());
    pc.inc();
    uint8_t high = Cpu::read(pc.get());
    pc.inc();
    dst.set(Cpu::read(Reg::Word(high, low).get())); // TODO: check behaviour
};

/**
 * @brief      Write 8-bit value at 16-bit immediate address (LS byte 1st).
 * @param      dst The 8-bit destination register
 */
void Cpu::instr_ld_nn_to(Reg::Byte &src) {
    uint8_t low = Cpu::read(pc.get());
    pc.inc();
    uint8_t high = Cpu::read(pc.get());
    pc.inc();
    Cpu::write(Reg::Word(high, low).get(), src.get()); // TODO: check behaviour
};

/**
 * @brief      Put value at address $FF00 + register C into A.
 * @param      dst The 8-bit A register
 * @param      dst The 8-bit C register
 */
void Cpu::instr_ld_a_c(Reg::Byte &a, const Reg::Byte &c) {
    uint8_t value = Cpu::read(0xFF00 + c.get());
    a.set(value);
};

/**
 * @brief      Put A into address $FF00 + register C.
 * @param      dst The 8-bit C register
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_c_a(const Reg::Byte &c, const Reg::Byte &a) {
    Cpu::write(0xFF00 + c.get(), a.get());
};

/**
 * @brief      Put value at address HL into A. Decrement HL.
 * Same as: LD A,(HL) - DEC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_a_hld(Reg::Byte &a) {
    uint8_t value = Cpu::read(Reg::Word(h, l).get()); // TODO: optimise, no need to construct a new word ?
    a.set(value);
    hl.dec(); // BUG: hl not linked with Bytes h & l
};

/**
 * @brief      Put A into memory address HL. Decrement HL.
 * Same as: LD (HL),A - DEC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_hld_a(Reg::Byte &a) {
    Cpu::write(Reg::Word(h, l).get(), a.get()); // TODO: optimise, no need to construct a new word ?
    hl.dec();                                   // BUG: hl not linked with Bytes h & l
};

/**
 * @brief      Put value at address HL into A. Increment HL.
 * Same as: LD A,(HL) - INC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_a_hli(Reg::Byte &a) {
    uint8_t value = Cpu::read(Reg::Word(h, l).get()); // TODO: optimise, no need to construct a new word ?
    a.set(value);
    hl.inc(); // BUG: hl not linked with Bytes h & l
};

/**
 * @brief      Put A into memory address HL. Increment HL.
 * Same as: LD (HL),A - INC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_hli_a(Reg::Byte &a) {
    Cpu::write(Reg::Word(h, l).get(), a.get()); // TODO: optimise, no need to construct a new word ?
    hl.inc();                                   // BUG: hl not linked with Bytes h & l
};


/**
 * @brief      Put A into memory address $FF00+n (one byte immediate value).
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_n_a(const Reg::Byte &a) {
    uint8_t n = Cpu::read(pc.get());
    pc.inc();
    Cpu::write(0xFF00 + n, a.get());
};

/**
 * @brief      Put memory address $FF00+n into A (one byte immediate value).
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_a_n(Reg::Byte &a) {
    uint8_t n = Cpu::read(pc.get());
    pc.inc();
    a.set(Cpu::read(0xFF00 + n));
};

/**
 * @brief      Put 16-bit immediate value into Word dst.
 * @param      dst The 16-bit register pair
 */
void Cpu::instr_ld(Reg::Word &dst) {
    uint8_t low = Cpu::read(pc.get());
    pc.inc();
    uint8_t high = Cpu::read(pc.get());
    pc.inc();
    dst.set(Reg::Word(high, low).get()); // BUG: Word not linked with Bytes
};

/**
 * @brief      Put HL into Stack Pointer (SP).
 * @param      dst The 16-bit Word SP
 * @param      src The 16-bit register pair HL
 */
void Cpu::instr_ld(Reg::Word &dst, const Reg::Word &src){};

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
