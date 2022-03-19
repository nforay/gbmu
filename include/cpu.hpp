/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:05:43 by nforay            #+#    #+#             */
/*   Updated: 2022/03/19 19:04:41 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "component.hpp"
#include "logger.h"
#include "registers.hpp"

class Cpu : public Component {

public:
    Cpu(Bus *bus);
    virtual ~Cpu();

    virtual void    reset();
    virtual void    clock();
    virtual void    write(uint16_t addr, const uint8_t data);
    virtual uint8_t read(uint16_t addr);
    void            execute(uint8_t opcode, Reg::Word &pc);
    void            push(const Reg::BytePair &data);
    void            pop(Reg::BytePair &data);

    enum class Condition {
        NZ,
        Z,
        NC,
        C,
    };

    Reg::Flag f;

    Reg::Byte a, b, c, d, e, h, l;

    Reg::BytePair af = Reg::BytePair(a, f);
    Reg::BytePair bc = Reg::BytePair(b, c);
    Reg::BytePair de = Reg::BytePair(d, e);
    Reg::BytePair hl = Reg::BytePair(h, l);

    Reg::Word pc, sp; // Program Counter, Stack Pointer

    /* instructions */
    /* Misc/control instructions */
    void instr_nop();
    void instr_halt();
    void instr_stop();
    void instr_cb(); // CB prefix -> opcode 16-bit
    void instr_di();
    void instr_ei();

    /* Jumps/calls instructions */
    void instr_jr();
    void instr_jr(Condition);
    void instr_jp();
    void instr_jp(Condition);
    void instr_jp(uint16_t);
    void instr_ret();
    void instr_ret(Condition);
    void instr_reti();
    void instr_call();
    void instr_call(Condition);
    void instr_rst();

    /* 8bit load/store/move instructions */
    void instr_ld(Reg::Byte &dst);
    void instr_ld(Reg::Byte &dst, const Reg::Byte &src);
    void instr_ld(Reg::Byte &dst, const Reg::BytePair &src);
    void instr_ld(const Reg::Word &dst, const Reg::Byte &src);
    void instr_ld(const Reg::Word &dst);
    void instr_ld_nn_from(Reg::Byte &dst);
    void instr_ld_nn_to(Reg::Byte &dst);
    void instr_ld_a_c(Reg::Byte &a, const Reg::Byte &c);
    void instr_ld_c_a(const Reg::Byte &c, const Reg::Byte &a);
    void instr_ld_a_hld(Reg::Byte &a);
    void instr_ld_hld_a(Reg::Byte &a);
    void instr_ld_a_hli(Reg::Byte &a);
    void instr_ld_hli_a(Reg::Byte &a);
    void instr_ld_n_a(const Reg::Byte &a);
    void instr_ld_a_n(Reg::Byte &a);

    /* 16bit load/store/move instructions */
    void instr_ld(Reg::BytePair &dst);
    void instr_ld(Reg::Word &dst, const Reg::BytePair &src);
    void instr_ld_hl_sp_n();
    void instr_ld_nn_sp();
    void instr_push_nn(const Reg::BytePair &src);
    void instr_pop_nn(Reg::BytePair &src);

    /* 8bit arithmetic/logical instructions */
    void instr_add(const Reg::Byte &src);
    void instr_add(const uint16_t &addr);
    void instr_add_n();
    void instr_adc(const Reg::Byte &src);
    void instr_adc(const uint16_t &addr);
    void instr_adc_n();
    void instr_sub(const Reg::Byte &src);
    void instr_sub(const uint16_t &addr);
    void instr_sub_n();
    void instr_sbc(const Reg::Byte &src);
    void instr_sbc(const uint16_t &addr);
    void instr_sbc_n();
    void instr_and(const Reg::Byte &src);
    void instr_and(const uint16_t &addr);
    void instr_and_n();
    void instr_or(const Reg::Byte &src);
    void instr_or(const uint16_t &addr);
    void instr_or_n();
    void instr_xor(const Reg::Byte &src);
    void instr_xor(const uint16_t &addr);
    void instr_xor_n();
    void instr_cp(const Reg::Byte &src);
    void instr_cp(const uint16_t &addr);
    void instr_cp_n();
    void instr_inc(Reg::Byte &src);
    void instr_inc(const uint16_t &addr);
    void instr_dec(Reg::Byte &src);
    void instr_dec(const uint16_t &addr);

    void instr_daa();
    void instr_scf();
    void instr_cpl();
    void instr_ccf();

    /* 	16bit arithmetic/logical instructions */
    void instr_inc(Reg::Word);
    void instr_add(Reg::Word);
    void instr_dec(Reg::Word);

    /* 	8bit rotations/shifts and bit instructions */
    void instr_rlca();
    void instr_rla();
    void instr_rrca();
    void instr_rra();
    void instr_rlc();
    void instr_rl();
    void instr_rrc();
    void instr_rr();
    void instr_sla();
    void instr_sra();
    void instr_swap();
    void instr_srl();
    void instr_bit();
    void instr_res();
    void instr_set();

    /* clang-format off */
    /* opcodes 8-bit loads */
    void opcode_00(); void opcode_01(); void opcode_02(); void opcode_03(); void opcode_04(); void opcode_05(); void opcode_06(); void opcode_07(); void opcode_08(); void opcode_09(); void opcode_0A(); void opcode_0B(); void opcode_0C(); void opcode_0D(); void opcode_0E(); void opcode_0F();
    void opcode_10(); void opcode_11(); void opcode_12(); void opcode_13(); void opcode_14(); void opcode_15(); void opcode_16(); void opcode_17(); void opcode_18(); void opcode_19(); void opcode_1A(); void opcode_1B(); void opcode_1C(); void opcode_1D(); void opcode_1E(); void opcode_1F();
    void opcode_20(); void opcode_21(); void opcode_22(); void opcode_23(); void opcode_24(); void opcode_25(); void opcode_26(); void opcode_27(); void opcode_28(); void opcode_29(); void opcode_2A(); void opcode_2B(); void opcode_2C(); void opcode_2D(); void opcode_2E(); void opcode_2F();
    void opcode_30(); void opcode_31(); void opcode_32(); void opcode_33(); void opcode_34(); void opcode_35(); void opcode_36(); void opcode_37(); void opcode_38(); void opcode_39(); void opcode_3A(); void opcode_3B(); void opcode_3C(); void opcode_3D(); void opcode_3E(); void opcode_3F();
    void opcode_40(); void opcode_41(); void opcode_42(); void opcode_43(); void opcode_44(); void opcode_45(); void opcode_46(); void opcode_47(); void opcode_48(); void opcode_49(); void opcode_4A(); void opcode_4B(); void opcode_4C(); void opcode_4D(); void opcode_4E(); void opcode_4F();
    void opcode_50(); void opcode_51(); void opcode_52(); void opcode_53(); void opcode_54(); void opcode_55(); void opcode_56(); void opcode_57(); void opcode_58(); void opcode_59(); void opcode_5A(); void opcode_5B(); void opcode_5C(); void opcode_5D(); void opcode_5E(); void opcode_5F();
    void opcode_60(); void opcode_61(); void opcode_62(); void opcode_63(); void opcode_64(); void opcode_65(); void opcode_66(); void opcode_67(); void opcode_68(); void opcode_69(); void opcode_6A(); void opcode_6B(); void opcode_6C(); void opcode_6D(); void opcode_6E(); void opcode_6F();
    void opcode_70(); void opcode_71(); void opcode_72(); void opcode_73(); void opcode_74(); void opcode_75(); void opcode_76(); void opcode_77(); void opcode_78(); void opcode_79(); void opcode_7A(); void opcode_7B(); void opcode_7C(); void opcode_7D(); void opcode_7E(); void opcode_7F();
    void opcode_80(); void opcode_81(); void opcode_82(); void opcode_83(); void opcode_84(); void opcode_85(); void opcode_86(); void opcode_87(); void opcode_88(); void opcode_89(); void opcode_8A(); void opcode_8B(); void opcode_8C(); void opcode_8D(); void opcode_8E(); void opcode_8F();
    void opcode_90(); void opcode_91(); void opcode_92(); void opcode_93(); void opcode_94(); void opcode_95(); void opcode_96(); void opcode_97(); void opcode_98(); void opcode_99(); void opcode_9A(); void opcode_9B(); void opcode_9C(); void opcode_9D(); void opcode_9E(); void opcode_9F();
    void opcode_A0(); void opcode_A1(); void opcode_A2(); void opcode_A3(); void opcode_A4(); void opcode_A5(); void opcode_A6(); void opcode_A7(); void opcode_A8(); void opcode_A9(); void opcode_AA(); void opcode_AB(); void opcode_AC(); void opcode_AD(); void opcode_AE(); void opcode_AF();
    void opcode_B0(); void opcode_B1(); void opcode_B2(); void opcode_B3(); void opcode_B4(); void opcode_B5(); void opcode_B6(); void opcode_B7(); void opcode_B8(); void opcode_B9(); void opcode_BA(); void opcode_BB(); void opcode_BC(); void opcode_BD(); void opcode_BE(); void opcode_BF();
    void opcode_C0(); void opcode_C1(); void opcode_C2(); void opcode_C3(); void opcode_C4(); void opcode_C5(); void opcode_C6(); void opcode_C7(); void opcode_C8(); void opcode_C9(); void opcode_CA(); void opcode_CB(); void opcode_CC(); void opcode_CD(); void opcode_CE(); void opcode_CF();
    void opcode_D0(); void opcode_D1(); void opcode_D2(); void opcode_D3(); void opcode_D4(); void opcode_D5(); void opcode_D6(); void opcode_D7(); void opcode_D8(); void opcode_D9(); void opcode_DA(); void opcode_DB(); void opcode_DC(); void opcode_DD(); void opcode_DE(); void opcode_DF();
    void opcode_E0(); void opcode_E1(); void opcode_E2(); void opcode_E3(); void opcode_E4(); void opcode_E5(); void opcode_E6(); void opcode_E7(); void opcode_E8(); void opcode_E9(); void opcode_EA(); void opcode_EB(); void opcode_EC(); void opcode_ED(); void opcode_EE(); void opcode_EF();
    void opcode_F0(); void opcode_F1(); void opcode_F2(); void opcode_F3(); void opcode_F4(); void opcode_F5(); void opcode_F6(); void opcode_F7(); void opcode_F8(); void opcode_F9(); void opcode_FA(); void opcode_FB(); void opcode_FC(); void opcode_FD(); void opcode_FE(); void opcode_FF();

    /* opcodes 16-bit loads */
    void opcode_CB_00(); void opcode_CB_01(); void opcode_CB_02(); void opcode_CB_03(); void opcode_CB_04(); void opcode_CB_05(); void opcode_CB_06(); void opcode_CB_07(); void opcode_CB_08(); void opcode_CB_09(); void opcode_CB_0A(); void opcode_CB_0B(); void opcode_CB_0C(); void opcode_CB_0D(); void opcode_CB_0E(); void opcode_CB_0F();
    void opcode_CB_10(); void opcode_CB_11(); void opcode_CB_12(); void opcode_CB_13(); void opcode_CB_14(); void opcode_CB_15(); void opcode_CB_16(); void opcode_CB_17(); void opcode_CB_18(); void opcode_CB_19(); void opcode_CB_1A(); void opcode_CB_1B(); void opcode_CB_1C(); void opcode_CB_1D(); void opcode_CB_1E(); void opcode_CB_1F();
    void opcode_CB_20(); void opcode_CB_21(); void opcode_CB_22(); void opcode_CB_23(); void opcode_CB_24(); void opcode_CB_25(); void opcode_CB_26(); void opcode_CB_27(); void opcode_CB_28(); void opcode_CB_29(); void opcode_CB_2A(); void opcode_CB_2B(); void opcode_CB_2C(); void opcode_CB_2D(); void opcode_CB_2E(); void opcode_CB_2F();
    void opcode_CB_30(); void opcode_CB_31(); void opcode_CB_32(); void opcode_CB_33(); void opcode_CB_34(); void opcode_CB_35(); void opcode_CB_36(); void opcode_CB_37(); void opcode_CB_38(); void opcode_CB_39(); void opcode_CB_3A(); void opcode_CB_3B(); void opcode_CB_3C(); void opcode_CB_3D(); void opcode_CB_3E(); void opcode_CB_3F();
    void opcode_CB_40(); void opcode_CB_41(); void opcode_CB_42(); void opcode_CB_43(); void opcode_CB_44(); void opcode_CB_45(); void opcode_CB_46(); void opcode_CB_47(); void opcode_CB_48(); void opcode_CB_49(); void opcode_CB_4A(); void opcode_CB_4B(); void opcode_CB_4C(); void opcode_CB_4D(); void opcode_CB_4E(); void opcode_CB_4F();
    void opcode_CB_50(); void opcode_CB_51(); void opcode_CB_52(); void opcode_CB_53(); void opcode_CB_54(); void opcode_CB_55(); void opcode_CB_56(); void opcode_CB_57(); void opcode_CB_58(); void opcode_CB_59(); void opcode_CB_5A(); void opcode_CB_5B(); void opcode_CB_5C(); void opcode_CB_5D(); void opcode_CB_5E(); void opcode_CB_5F();
    void opcode_CB_60(); void opcode_CB_61(); void opcode_CB_62(); void opcode_CB_63(); void opcode_CB_64(); void opcode_CB_65(); void opcode_CB_66(); void opcode_CB_67(); void opcode_CB_68(); void opcode_CB_69(); void opcode_CB_6A(); void opcode_CB_6B(); void opcode_CB_6C(); void opcode_CB_6D(); void opcode_CB_6E(); void opcode_CB_6F();
    void opcode_CB_70(); void opcode_CB_71(); void opcode_CB_72(); void opcode_CB_73(); void opcode_CB_74(); void opcode_CB_75(); void opcode_CB_76(); void opcode_CB_77(); void opcode_CB_78(); void opcode_CB_79(); void opcode_CB_7A(); void opcode_CB_7B(); void opcode_CB_7C(); void opcode_CB_7D(); void opcode_CB_7E(); void opcode_CB_7F();
    void opcode_CB_80(); void opcode_CB_81(); void opcode_CB_82(); void opcode_CB_83(); void opcode_CB_84(); void opcode_CB_85(); void opcode_CB_86(); void opcode_CB_87(); void opcode_CB_88(); void opcode_CB_89(); void opcode_CB_8A(); void opcode_CB_8B(); void opcode_CB_8C(); void opcode_CB_8D(); void opcode_CB_8E(); void opcode_CB_8F();
    void opcode_CB_90(); void opcode_CB_91(); void opcode_CB_92(); void opcode_CB_93(); void opcode_CB_94(); void opcode_CB_95(); void opcode_CB_96(); void opcode_CB_97(); void opcode_CB_98(); void opcode_CB_99(); void opcode_CB_9A(); void opcode_CB_9B(); void opcode_CB_9C(); void opcode_CB_9D(); void opcode_CB_9E(); void opcode_CB_9F();
    void opcode_CB_A0(); void opcode_CB_A1(); void opcode_CB_A2(); void opcode_CB_A3(); void opcode_CB_A4(); void opcode_CB_A5(); void opcode_CB_A6(); void opcode_CB_A7(); void opcode_CB_A8(); void opcode_CB_A9(); void opcode_CB_AA(); void opcode_CB_AB(); void opcode_CB_AC(); void opcode_CB_AD(); void opcode_CB_AE(); void opcode_CB_AF();
    void opcode_CB_B0(); void opcode_CB_B1(); void opcode_CB_B2(); void opcode_CB_B3(); void opcode_CB_B4(); void opcode_CB_B5(); void opcode_CB_B6(); void opcode_CB_B7(); void opcode_CB_B8(); void opcode_CB_B9(); void opcode_CB_BA(); void opcode_CB_BB(); void opcode_CB_BC(); void opcode_CB_BD(); void opcode_CB_BE(); void opcode_CB_BF();
    void opcode_CB_C0(); void opcode_CB_C1(); void opcode_CB_C2(); void opcode_CB_C3(); void opcode_CB_C4(); void opcode_CB_C5(); void opcode_CB_C6(); void opcode_CB_C7(); void opcode_CB_C8(); void opcode_CB_C9(); void opcode_CB_CA(); void opcode_CB_CB(); void opcode_CB_CC(); void opcode_CB_CD(); void opcode_CB_CE(); void opcode_CB_CF();
    void opcode_CB_D0(); void opcode_CB_D1(); void opcode_CB_D2(); void opcode_CB_D3(); void opcode_CB_D4(); void opcode_CB_D5(); void opcode_CB_D6(); void opcode_CB_D7(); void opcode_CB_D8(); void opcode_CB_D9(); void opcode_CB_DA(); void opcode_CB_DB(); void opcode_CB_DC(); void opcode_CB_DD(); void opcode_CB_DE(); void opcode_CB_DF();
    void opcode_CB_E0(); void opcode_CB_E1(); void opcode_CB_E2(); void opcode_CB_E3(); void opcode_CB_E4(); void opcode_CB_E5(); void opcode_CB_E6(); void opcode_CB_E7(); void opcode_CB_E8(); void opcode_CB_E9(); void opcode_CB_EA(); void opcode_CB_EB(); void opcode_CB_EC(); void opcode_CB_ED(); void opcode_CB_EE(); void opcode_CB_EF();
    void opcode_CB_F0(); void opcode_CB_F1(); void opcode_CB_F2(); void opcode_CB_F3(); void opcode_CB_F4(); void opcode_CB_F5(); void opcode_CB_F6(); void opcode_CB_F7(); void opcode_CB_F8(); void opcode_CB_F9(); void opcode_CB_FA(); void opcode_CB_FB(); void opcode_CB_FC(); void opcode_CB_FD(); void opcode_CB_FE(); void opcode_CB_FF();
    /* clang-format on */
};
