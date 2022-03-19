/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:53 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 18:13:14 by nforay           ###   ########.fr       */
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
 * 8bit load/store/move instructions *******************************************
 */

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
void Cpu::instr_ld(Reg::Byte &dst, const Reg::BytePair &src) { dst.set(Cpu::read(src.get())); };

/**
 * @brief      Write value from src at dst.
 * @param      dst  The 16-bit destination address
 * @param      src  The 8-bit source register
 */
void Cpu::instr_ld(const Reg::Word &dst, const Reg::Byte &src) {
    Cpu::write(dst.get(), src.get());
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
    dst.set(Cpu::read(Reg::Word(high, low).get()));
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
    Cpu::write(Reg::Word(high, low).get(), src.get());
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
    a.set(Cpu::read(hl.get()));
    hl.dec();
};

/**
 * @brief      Put A into memory address HL. Decrement HL.
 * Same as: LD (HL),A - DEC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_hld_a(Reg::Byte &a) {
    Cpu::write(hl.get(), a.get());
    hl.dec();
};

/**
 * @brief      Put value at address HL into A. Increment HL.
 * Same as: LD A,(HL) - INC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_a_hli(Reg::Byte &a) {
    a.set(Cpu::read(hl.get()));
    hl.inc();
};

/**
 * @brief      Put A into memory address HL. Increment HL.
 * Same as: LD (HL),A - INC HL
 * @param      dst The 8-bit A register
 */
void Cpu::instr_ld_hli_a(Reg::Byte &a) {
    Cpu::write(hl.get(), a.get());
    hl.inc();
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
void Cpu::instr_ld(Reg::BytePair &dst) {
    uint16_t value = Cpu::read(pc.get());
    pc.inc();
    value |= (Cpu::read(pc.get()) << 8);
    pc.inc();
    dst.set(value);
};

/**
 * @brief      Put HL into Stack Pointer (SP).
 * @param      dst The 16-bit Word SP
 * @param      src The 16-bit register pair HL
 */
void Cpu::instr_ld(Reg::Word &dst, const Reg::BytePair &src) { dst.set(src.get()); };

/**
 * @brief      Put SP + n (immediate value) effective address into HL.
 */
void Cpu::instr_ld_hl_sp_n() {
    uint8_t n = Cpu::read(pc.get());
    pc.inc();
    hl.set(sp.get() + n);
    f.set_zero(0);
    f.set_sub(0);
    // HACK: needs research
    f.set_half_carry(0); // check behaviour
    f.set_carry(0);      // check behaviour
};

/**
 * @brief      Put Stack Pointer (SP) at address n.
 */
void Cpu::instr_ld_nn_sp() {
    uint8_t low = Cpu::read(pc.get());
    pc.inc();
    uint8_t high = Cpu::read(pc.get());
    pc.inc();
    Cpu::write(Reg::Word(high, low).get(), sp.get());
};

/**
 * @brief      Push register pair nn onto stack.
 * Decrement Stack Pointer (SP) twice.
 */
void Cpu::instr_push_nn(const Reg::BytePair &src) { Cpu::push(src); };

/**
 * @brief      Pop two bytes off stack into register pair nn.
 * Increment Stack Pointer (SP) twice.
 */
void Cpu::instr_pop_nn(Reg::BytePair &src) { Cpu::pop(src); };

/**
 * 8bit arithmetic/logical instructions ****************************************
 */

/**
 * @brief      Add n to A.
 */
void Cpu::instr_add(const Reg::Byte &src) {
    uint16_t value = a.get() + src.get();
    a.set(value & 0x00FF);
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(value > 0xF); // check behaviour
    f.set_carry(value & 0x100);    // check behaviour
};

/**
 * @brief      Add value at Register Pair (HL) to A.
 */
void Cpu::instr_add(const Reg::BytePair &src) {
    uint16_t value = a.get() + read(src.get());
    a.set(value & 0x00FF);
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(value > 0xF); // check behaviour
    f.set_carry(value & 0x100);    // check behaviour
};

/**
 * @brief      Add value at 16-bit nn (immediate address) to A.
 */
void Cpu::instr_add_n() {
    uint16_t value = a.get() + read(pc.get());
    pc.inc();
    a.set(value & 0x00FF);
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(value > 0xF); // check behaviour
    f.set_carry(value & 0x100);    // check behaviour
};

/**
 * @brief      Add n + Carry flag to A.
 */
void Cpu::instr_adc(const Reg::Byte &src) {
    uint16_t value = a.get() + src.get() + f.get_carry();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry((a.get() & 0xF + src.get() & 0xF + f.get_carry()) > 0xF); // check behaviour
    f.set_carry(value & 0x100);                                                // check behaviour
    a.set(value & 0x00FF);
};

/**
 * @brief      Add value at Register Pair (HL) + Carry flag to A.
 */
void Cpu::instr_adc(const Reg::BytePair &src) {
    uint8_t  tmp   = read(src.get());
    uint16_t value = a.get() + tmp + f.get_carry();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry((a.get() & 0xF + tmp & 0xF + f.get_carry()) > 0xF); // check behaviour
    f.set_carry(value & 0x100);                                          // check behaviour
    a.set(value & 0x00FF);
};

/**
 * @brief      Add value at 16-bit nn (immediate address) + Carry flag to A.
 */
void Cpu::instr_adc_n() {
    uint8_t tmp = read(pc.get());
    pc.inc();
    uint16_t value = a.get() + tmp + f.get_carry();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry((a.get() & 0xF + tmp & 0xF + f.get_carry()) > 0xF); // check behaviour
    f.set_carry(value & 0x100);                                          // check behaviour
    a.set(value & 0x00FF);
};

/**
 * @brief      Substract n from A.
 */
void Cpu::instr_sub(const Reg::Byte &src) {
    uint8_t value = a.get() - src.get();
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - src.get() & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < src.get());                        // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Substract value at Register Pair (HL) from A.
 */
void Cpu::instr_sub(const Reg::BytePair &src) {
    uint8_t tmp   = read(src.get());
    uint8_t value = a.get() - tmp;
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp);                        // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Substract value at 16-bit nn (immediate address) from A.
 */
void Cpu::instr_sub_n() {
    uint8_t tmp = read(pc.get());
    pc.inc();
    uint8_t value = a.get() - tmp;
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp);                        // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Substract n + Carry flag from A.
 */
void Cpu::instr_sbc(const Reg::Byte &src) {
    uint8_t value = a.get() - src.get() - f.get_carry();
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - src.get() & 0xF - f.get_carry()) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < src.get()); // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Substract value at Register Pair (HL) + Carry flag from A.
 */
void Cpu::instr_sbc(const Reg::BytePair &src) {
    uint8_t tmp   = read(src.get());
    uint8_t value = a.get() - tmp - f.get_carry();
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF - f.get_carry()) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp); // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Substract value at 16-bit nn (immediate address) + Carry flag from A.
 */
void Cpu::instr_sbc_n() {
    uint8_t tmp = read(pc.get());
    pc.inc();
    uint8_t value = a.get() - tmp - f.get_carry();
    f.set_zero(value == 0);
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF - f.get_carry()) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp); // check behaviour Set if no borrow.
    a.set(value);
};

/**
 * @brief      Logically AND n with A, result in A.
 */
void Cpu::instr_and(const Reg::Byte &src) {
    a.set(a.get() & src.get());
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(1);
    f.set_carry(0);
};

/**
 * @brief      Logically AND value at Register Pair (HL) with A, result in A.
 */
void Cpu::instr_and(const Reg::BytePair &src) {
    a.set(a.get() & read(src.get()));
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(1);
    f.set_carry(0);
};

/**
 * @brief      Logically AND value at 16-bit nn (immediate address) with A, result in A.
 */
void Cpu::instr_and_n() {
    a.set(a.get() & read(pc.get()));
    pc.inc();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(1);
    f.set_carry(0);
};

/**
 * @brief      Logically OR n with A, result in A.
 */
void Cpu::instr_or(const Reg::Byte &src) {
    a.set(a.get() | src.get());
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Logically OR value at Register Pair (HL) with A, result in A.
 */
void Cpu::instr_or(const Reg::BytePair &src) {
    a.set(a.get() | read(src.get()));
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Logically OR value at 16-bit nn (immediate address) with A, result in A.
 */
void Cpu::instr_or_n() {
    a.set(a.get() | read(pc.get()));
    pc.inc();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
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
void Cpu::instr_inc(uint8_t){};
void Cpu::instr_inc(uint16_t){};
void Cpu::instr_dec(uint8_t){};
void Cpu::instr_dec(uint16_t){};
void Cpu::instr_daa(){};
void Cpu::instr_scf(){};
void Cpu::instr_cpl(){};
void Cpu::instr_ccf(){};
void Cpu::instr_sbc(){};
void Cpu::instr_xor(uint8_t){};
void Cpu::instr_xor(uint16_t){};
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
