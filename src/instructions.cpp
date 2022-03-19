/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:32:53 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 20:19:03 by nforay           ###   ########.fr       */
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
 * @brief      Add value at addr from Register Pair (HL) to A.
 */
void Cpu::instr_add(const uint16_t &addr) {
    uint16_t value = a.get() + read(addr);
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
 * @brief      Add value at addr from Register Pair (HL) + Carry flag to A.
 */
void Cpu::instr_adc(const uint16_t &addr) {
    uint8_t  tmp   = read(addr);
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
 * @brief      Substract value at addr from Register Pair (HL) from A.
 */
void Cpu::instr_sub(const uint16_t &addr) {
    uint8_t tmp   = read(addr);
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
 * @brief      Substract value at addr from Register Pair (HL) + Carry flag from A.
 */
void Cpu::instr_sbc(const uint16_t &addr) {
    uint8_t tmp   = read(addr);
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
 * @brief      Logically AND value at addr from Register Pair (HL) with A, result in A.
 */
void Cpu::instr_and(const uint16_t &addr) {
    a.set(a.get() & read(addr));
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
 * @brief      Logically OR value at addr from Register Pair (HL) with A, result in A.
 */
void Cpu::instr_or(const uint16_t &addr) {
    a.set(a.get() | read(addr));
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

/**
 * @brief      Logical exclusive OR n with register A, result in A.
 */
void Cpu::instr_xor(const Reg::Byte &src) {
    a.set(a.get() ^ src.get());
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Logical exclusive OR value at addr from Register Pair (HL) with A,
 *  result in A.
 */
void Cpu::instr_xor(const uint16_t &addr) {
    a.set(a.get() ^ read(addr));
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Logical exclusive OR value at 16-bit nn (immediate address) with A, result in A.
 */
void Cpu::instr_xor_n() {
    a.set(a.get() ^ read(pc.get()));
    pc.inc();
    f.set_zero(a.get() == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Compare A with n. This is basically an A - n subtraction instruction
 *  but the results are thrown away.
 */
void Cpu::instr_cp(const Reg::Byte &src) {
    f.set_zero(a.get() == src.get());
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - src.get() & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < src.get());
};

/**
 * @brief      Compare A with value at addr from Register Pair (HL). This is
 * basically an A - n subtraction instruction but the results are thrown away.
 */
void Cpu::instr_cp(const uint16_t &addr) {
    uint8_t tmp = read(addr);
    f.set_zero(tmp == a.get());
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp);
};

/**
 * @brief      Compare A with value at 16-bit nn (immediate address). This is
 *  basically an A - n subtraction instruction but the results are thrown away.
 */
void Cpu::instr_cp_n() {
    uint8_t tmp = read(pc.get());
    pc.inc();
    f.set_zero(tmp == a.get());
    f.set_sub(1);
    f.set_half_carry((a.get() & 0xF - tmp & 0xF) < 0); // check behaviour Set if no borrow from bit 4.
    f.set_carry(a.get() < tmp);
};

/**
 * @brief      Increment register n.
 */
void Cpu::instr_inc(Reg::Byte &src) {
    src.inc();
    f.set_zero(src.get() == 0);
    f.set_sub(0);
    f.set_half_carry((src.get() & 0x0F) == 0); // check behaviour Set if carry from bit 3.
};

/**
 * @brief      Increment value at Register Pair (HL).
 */
void Cpu::instr_inc(const uint16_t &addr) {
    uint8_t tmp = static_cast<uint8_t>(read(addr) + 1);
    write(addr, tmp);
    f.set_zero(tmp == 0);
    f.set_sub(0);
    f.set_half_carry((tmp & 0x0F) == 0); // check behaviour Set if carry from bit 3.
};

/**
 * @brief      Decrement register n.
 */
void Cpu::instr_dec(Reg::Byte &src) {
    src.dec();
    f.set_zero(src.get() == 0);
    f.set_sub(1);
    f.set_half_carry((src.get() & 0x0F) == 0x0F); // check behaviour Set if no borrow from bit 4.
};

/**
 * @brief      Decrement value at Register Pair (HL).
 */
void Cpu::instr_dec(const uint16_t &addr) {
    uint8_t tmp = static_cast<uint8_t>(read(addr) - 1);
    write(addr, tmp);
    f.set_zero(tmp == 0);
    f.set_sub(1);
    f.set_half_carry((tmp & 0x0F) == 0x0F); // check behaviour Set if no borrow from bit 4.
};

/**
 * 16bit arithmetic/logical instructions ***************************************
 */

/**
 * @brief      Add Register Pair src to Register Pair HL.
 * @param      src 16-bit Register Pair.
 */
void Cpu::instr_add_hl(const Reg::BytePair &src) {
    uint32_t value = hl.get() + src.get();
    f.set_sub(0);
    f.set_half_carry((hl.get() & 0xFFF + src.get() & 0xFFF) > 0xFFF); // check behaviour
    f.set_carry((value & 0x1000) != 0);                               // check behaviour
    hl.set(value & 0xFFFF);
};

/**
 * @brief      Add Word src to Register Pair HL.
 * @param      src Word.
 */
void Cpu::instr_add_hl(const Reg::Word &src) {
    uint32_t value = hl.get() + src.get();
    f.set_sub(0);
    f.set_half_carry((hl.get() & 0xFFF + src.get() & 0xFFF) > 0xFFF); // check behaviour
    f.set_carry((value & 0x1000) != 0);                               // check behaviour
    hl.set(value & 0xFFFF);
};

/**
 * @brief      Add one byte signed immediate value to Stack Pointer (SP).
 */
void Cpu::instr_add_sp_n() {
    uint32_t value = sp.get() + read(pc.get());
    pc.inc();
    f.set_zero(0);
    f.set_sub(0);
    f.set_half_carry(0); // TODO: needs reasearch
    f.set_carry(0);      // TODO: needs reasearch
    sp.set(value & 0xFFFF);
};

/**
 * @brief      Increment 16-bit Register Pair nn
 */
void Cpu::instr_inc_nn(Reg::BytePair &src) { src.inc(); }

/**
 * @brief      Increment Word nn
 */
void Cpu::instr_inc_nn(Reg::Word &src) { src.inc(); }

/**
 * @brief      Decrement 16-bit Register Pair nn
 */
void Cpu::instr_dec_nn(Reg::BytePair &src) { src.dec(); }

/**
 * @brief      Decrement Word nn
 */
void Cpu::instr_dec_nn(Reg::Word &src) { src.dec(); }

/**
 * @brief       Decimal adjust register A. This instruction adjusts register A
 *  so that the correct representation of Binary Coded Decimal (BCD) is obtained.
 */
void Cpu::instr_daa() {
    uint8_t tmp = a.get();
    // https://forums.nesdev.org/viewtopic.php?p=196282#p196282
    if (!f.get_sub()) { // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (f.get_carry() || tmp > 0x99) {
            tmp += 0x60;
            f.set_carry(1);
        }
        if (f.get_half_carry() || (tmp & 0x0f) > 0x09) {
            tmp += 0x6;
        }
    } else { // after a subtraction, only adjust if (half-)carry occurred
        if (f.get_carry()) {
            tmp -= 0x60;
        }
        if (f.get_half_carry()) {
            tmp -= 0x6;
        }
    }
    a.set(tmp);
    f.set_zero(tmp == 0);
    f.set_half_carry(0);
};

/**
 * @brief      Complement A register. (Flip all bits.)
 */
void Cpu::instr_cpl() {
    a.set(~a.get());
    f.set_sub(1);
    f.set_half_carry(1);
};

/**
 * @brief      Complement carry flag. If C flag is set, then reset it.
 *  If C flag is reset, then set it.
 */
void Cpu::instr_ccf() {
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(!f.get_carry());
};

/**
 * @brief      Set Carry flag.
 */
void Cpu::instr_scf() {
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(1);
};

/**
 * 8bit rotations/shifts and bit instructions **********************************
 */

/**
 * @brief      Swap upper & lower nibles of n.
 */
void Cpu::instr_swap(Reg::Byte &src) {
    uint8_t tmp = src.get();
    tmp         = ((tmp & 0x0F) << 4 | (tmp & 0xF0) >> 4);
    src.set(tmp);
    f.set_zero(tmp == 0);
    f.set_sub(0);
    f.set_half_carry(0);
    f.set_carry(0);
};

/**
 * @brief      Swap upper & lower nibles of Byte at address.
 */
void Cpu::instr_swap(const uint16_t &addr) {
    uint8_t tmp = read(addr);
    tmp         = ((tmp & 0x0F) << 4 | (tmp & 0xF0) >> 4);
    write(addr, tmp);
    f.set_zero(tmp == 0);
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
void Cpu::instr_srl(){};
void Cpu::instr_bit(){};
void Cpu::instr_res(){};
void Cpu::instr_set(){};
