/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:05:43 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 19:10:23 by nforay           ###   ########.fr       */
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
    virtual void    write(uint16_t addr, uint8_t data);
    virtual uint8_t read(uint16_t addr);
    void            execute(uint8_t opcode, Reg::Word &pc);

    enum class Condition {
        NZ,
        Z,
        NC,
        C,
    };

    Reg::Flag f;

    Reg::Byte a, b, c, d, e, h, l;

    Reg::Word pc, sp; // Program Counter, Stack Pointer

    /* instructions */
    /* Misc/control instructions */
    void instr_nop();
    void instr_halt();
    void instr_cb(); // CB prefix -> opcode 16-bit
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
    void instr_ld(uint8_t);

    /* 16bit load/store/move instructions */
    void instr_ld(uint16_t);

    /* 8bit arithmetic/logical instructions */
    void instr_inc(uint8_t);
    void instr_inc(uint16_t);
    void instr_dec(uint8_t);
    void instr_dec(uint16_t);
    void instr_daa();
    void instr_scf();
    void instr_cpl();
    void instr_ccf();
    void instr_add();
    void instr_adc();
    void instr_sub();
    void instr_sbc();
    void instr_and(uint8_t);
    void instr_and(uint16_t);
    void instr_xor(uint8_t);
    void instr_xor(uint16_t);
    void instr_or(uint8_t);
    void instr_or(uint16_t);
    void instr_cp();

    /* 	16bit arithmetic/logical instructions */
    void instr_inc(uint16_t);
    void instr_add(uint16_t);

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
    
    // from docs/html/Gameboy (LR35902) OPCODES.html : regex '([^\n]*)\n.*?\n.{7}\s?' -> '"$1", '
    char* opcode_names[256] = {
        "NOP", "LD BC,d16", "LD (BC),A", "INC BC", "INC B", "DEC B", "LD B,d8", "RLCA", "LD (a16),SP", "ADD HL,BC", "LD A,(BC)", "DEC BC", "INC C", "DEC C", "LD C,d8", "RRCA",
        "STOP 0", "LD DE,d16", "LD (DE),A", "INC DE", "INC D", "DEC D", "LD D,d8", "RLA", "JR r8", "ADD HL,DE", "LD A,(DE)", "DEC DE", "INC E", "DEC E", "LD E,d8", "RRA",
        "JR NZ,r8", "LD HL,d16", "LD (HL+),A", "INC HL", "INC H", "DEC H", "LD H,d8", "DAA", "JR Z,r8", "ADD HL,HL", "LD A,(HL+)", "DEC HL", "INC L", "DEC L", "LD L,d8", "CPL",
        "JR NC,r8", "LD SP,d16", "LD (HL-),A", "INC SP", "INC (HL)", "DEC (HL)", "LD (HL),d8", "SCF", "JR C,r8", "ADD HL,SP", "LD A,(HL-)", "DEC SP", "INC A", "DEC A", "LD A,d8", "CCF",
        "LD B,B", "LD B,C", "LD B,D", "LD B,E", "LD B,H", "LD B,L", "LD B,(HL)", "LD B,A", "LD C,B", "LD C,C", "LD C,D", "LD C,E", "LD C,H", "LD C,L", "LD C,(HL)", "LD C,A",
        "LD D,B", "LD D,C", "LD D,D", "LD D,E", "LD D,H", "LD D,L", "LD D,(HL)", "LD D,A", "LD E,B", "LD E,C", "LD E,D", "LD E,E", "LD E,H", "LD E,L", "LD E,(HL)", "LD E,A",
        "LD H,B", "LD H,C", "LD H,D", "LD H,E", "LD H,H", "LD H,L", "LD H,(HL)", "LD H,A", "LD L,B", "LD L,C", "LD L,D", "LD L,E", "LD L,H", "LD L,L", "LD L,(HL)", "LD L,A",
        "LD (HL),B", "LD (HL),C", "LD (HL),D", "LD (HL),E", "LD (HL),H", "LD (HL),L", "HALT", "LD (HL),A", "LD A,B", "LD A,C", "LD A,D", "LD A,E", "LD A,H", "LD A,L", "LD A,(HL)", "LD A,A",
        "ADD A,B", "ADD A,C", "ADD A,D", "ADD A,E", "ADD A,H", "ADD A,L", "ADD A,(HL)", "ADD A,A", "ADC A,B", "ADC A,C", "ADC A,D", "ADC A,E", "ADC A,H", "ADC A,L", "ADC A,(HL)", "ADC A,A",
        "SUB B", "SUB C", "SUB D", "SUB E", "SUB H", "SUB L", "SUB (HL)", "SUB A", "SBC A,B", "SBC A,C", "SBC A,D", "SBC A,E", "SBC A,H", "SBC A,L", "SBC A,(HL)", "SBC A,A",
        "AND B", "AND C", "AND D", "AND E", "AND H", "AND L", "AND (HL)", "AND A", "XOR B", "XOR C", "XOR D", "XOR E", "XOR H", "XOR L", "XOR (HL)", "XOR A",
        "OR B", "OR C", "OR D", "OR E", "OR H", "OR L", "OR (HL)", "OR A", "CP B", "CP C", "CP D", "CP E", "CP H", "CP L", "CP (HL)", "CP A",
        "RET NZ", "POP BC", "JP NZ,a16", "JP a16", "CALL NZ,a16", "PUSH BC", "ADD A,d8", "RST 00H", "RET Z", "RET", "JP Z,a16", "PREFIX CB", "CALL Z,a16", "CALL a16", "ADC A,d8", "RST 08H",
        "RET NC", "POP DE", "JP NC,a16", "illegal opcode", "CALL NC,a16", "PUSH DE", "SUB d8", "RST 10H", "RET C", "RETI", "JP C,a16", "illegal opcode", "CALL C,a16", "illegal opcode", "SBC A,d8", "RST 18H",
        "LDH (a8),A", "POP HL", "LD (C),A", "illegal opcode", "illegal opcode", "PUSH HL", "AND d8", "RST 20H", "ADD SP,r8", "JP (HL)", "LD (a16),A", "illegal opcode", "illegal opcode", "illegal opcode", "XOR d8", "RST 28H",
        "LDH A,(a8)", "POP AF", "LD A,(C)", "DI", "illegal opcode", "PUSH AF", "OR d8", "RST 30H", "LD HL,SP+r8", "LD SP,HL", "LD A,(a16)", "EI", "illegal opcode", "illegal opcode", "CP d8", "RST 38H"
    };

    char* opcode_CB_names[256] = {
        "RLC B", "RLC C", "RLC D", "RLC E", "RLC H", "RLC L", "RLC (HL)", "RLC A", "RRC B", "RRC C", "RRC D", "RRC E", "RRC H", "RRC L", "RRC (HL)", "RRC A",
        "RL B", "RL C", "RL D", "RL E", "RL H", "RL L", "RL (HL)", "RL A", "RR B", "RR C", "RR D", "RR E", "RR H", "RR L", "RR (HL)", "RR A",
        "SLA B", "SLA C", "SLA D", "SLA E", "SLA H", "SLA L", "SLA (HL)", "SLA A", "SRA B", "SRA C", "SRA D", "SRA E", "SRA H", "SRA L", "SRA (HL)", "SRA A",
        "SWAP B", "SWAP C", "SWAP D", "SWAP E", "SWAP H", "SWAP L", "SWAP (HL)", "SWAP A", "SRL B", "SRL C", "SRL D", "SRL E", "SRL H", "SRL L", "SRL (HL)", "SRL A",
        "BIT 0,B", "BIT 0,C", "BIT 0,D", "BIT 0,E", "BIT 0,H", "BIT 0,L", "BIT 0,(HL)", "BIT 0,A", "BIT 1,B", "BIT 1,C", "BIT 1,D", "BIT 1,E", "BIT 1,H", "BIT 1,L", "BIT 1,(HL)", "BIT 1,A",
        "BIT 2,B", "BIT 2,C", "BIT 2,D", "BIT 2,E", "BIT 2,H", "BIT 2,L", "BIT 2,(HL)", "BIT 2,A", "BIT 3,B", "BIT 3,C", "BIT 3,D", "BIT 3,E", "BIT 3,H", "BIT 3,L", "BIT 3,(HL)", "BIT 3,A",
        "BIT 4,B", "BIT 4,C", "BIT 4,D", "BIT 4,E", "BIT 4,H", "BIT 4,L", "BIT 4,(HL)", "BIT 4,A", "BIT 5,B", "BIT 5,C", "BIT 5,D", "BIT 5,E", "BIT 5,H", "BIT 5,L", "BIT 5,(HL)", "BIT 5,A",
        "BIT 6,B", "BIT 6,C", "BIT 6,D", "BIT 6,E", "BIT 6,H", "BIT 6,L", "BIT 6,(HL)", "BIT 6,A", "BIT 7,B", "BIT 7,C", "BIT 7,D", "BIT 7,E", "BIT 7,H", "BIT 7,L", "BIT 7,(HL)", "BIT 7,A",
        "RES 0,B", "RES 0,C", "RES 0,D", "RES 0,E", "RES 0,H", "RES 0,L", "RES 0,(HL)", "RES 0,A", "RES 1,B", "RES 1,C", "RES 1,D", "RES 1,E", "RES 1,H", "RES 1,L", "RES 1,(HL)", "RES 1,A",
        "RES 2,B", "RES 2,C", "RES 2,D", "RES 2,E", "RES 2,H", "RES 2,L", "RES 2,(HL)", "RES 2,A", "RES 3,B", "RES 3,C", "RES 3,D", "RES 3,E", "RES 3,H", "RES 3,L", "RES 3,(HL)", "RES 3,A",
        "RES 4,B", "RES 4,C", "RES 4,D", "RES 4,E", "RES 4,H", "RES 4,L", "RES 4,(HL)", "RES 4,A", "RES 5,B", "RES 5,C", "RES 5,D", "RES 5,E", "RES 5,H", "RES 5,L", "RES 5,(HL)", "RES 5,A",
        "RES 6,B", "RES 6,C", "RES 6,D", "RES 6,E", "RES 6,H", "RES 6,L", "RES 6,(HL)", "RES 6,A", "RES 7,B", "RES 7,C", "RES 7,D", "RES 7,E", "RES 7,H", "RES 7,L", "RES 7,(HL)", "RES 7,A",
        "SET 0,B", "SET 0,C", "SET 0,D", "SET 0,E", "SET 0,H", "SET 0,L", "SET 0,(HL)", "SET 0,A", "SET 1,B", "SET 1,C", "SET 1,D", "SET 1,E", "SET 1,H", "SET 1,L", "SET 1,(HL)", "SET 1,A",
        "SET 2,B", "SET 2,C", "SET 2,D", "SET 2,E", "SET 2,H", "SET 2,L", "SET 2,(HL)", "SET 2,A", "SET 3,B", "SET 3,C", "SET 3,D", "SET 3,E", "SET 3,H", "SET 3,L", "SET 3,(HL)", "SET 3,A",
        "SET 4,B", "SET 4,C", "SET 4,D", "SET 4,E", "SET 4,H", "SET 4,L", "SET 4,(HL)", "SET 4,A", "SET 5,B", "SET 5,C", "SET 5,D", "SET 5,E", "SET 5,H", "SET 5,L", "SET 5,(HL)", "SET 5,A",
        "SET 6,B", "SET 6,C", "SET 6,D", "SET 6,E", "SET 6,H", "SET 6,L", "SET 6,(HL)", "SET 6,A", "SET 7,B", "SET 7,C", "SET 7,D", "SET 7,E", "SET 7,H", "SET 7,L", "SET 7,(HL)", "SET 7,A"
    };
    /* clang-format on */
};
