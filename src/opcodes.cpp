/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:27:58 by nforay            #+#    #+#             */
/*   Updated: 2022/03/18 23:11:25 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.hpp"

void Cpu::opcode_00() { Cpu::instr_nop(); };
void Cpu::opcode_01(){};
void Cpu::opcode_02(){};
void Cpu::opcode_03(){};
void Cpu::opcode_04(){};
void Cpu::opcode_05(){};
void Cpu::opcode_06() { Cpu::instr_ld(b); };
void Cpu::opcode_07(){};
void Cpu::opcode_08(){};
void Cpu::opcode_09(){};
void Cpu::opcode_0A(){};
void Cpu::opcode_0B(){};
void Cpu::opcode_0C(){};
void Cpu::opcode_0D(){};
void Cpu::opcode_0E() { Cpu::instr_ld(c); };
void Cpu::opcode_0F(){};
void Cpu::opcode_10() { Cpu::instr_stop(); };
void Cpu::opcode_11(){};
void Cpu::opcode_12(){};
void Cpu::opcode_13(){};
void Cpu::opcode_14(){};
void Cpu::opcode_15(){};
void Cpu::opcode_16() { Cpu::instr_ld(d); };
void Cpu::opcode_17(){};
void Cpu::opcode_18(){};
void Cpu::opcode_19(){};
void Cpu::opcode_1A(){};
void Cpu::opcode_1B(){};
void Cpu::opcode_1C(){};
void Cpu::opcode_1D(){};
void Cpu::opcode_1E() { Cpu::instr_ld(e); };
void Cpu::opcode_1F(){};
void Cpu::opcode_20(){};
void Cpu::opcode_21(){};
void Cpu::opcode_22(){};
void Cpu::opcode_23(){};
void Cpu::opcode_24(){};
void Cpu::opcode_25(){};
void Cpu::opcode_26() { Cpu::instr_ld(h); };
void Cpu::opcode_27(){};
void Cpu::opcode_28(){};
void Cpu::opcode_29(){};
void Cpu::opcode_2A(){};
void Cpu::opcode_2B(){};
void Cpu::opcode_2C(){};
void Cpu::opcode_2D(){};
void Cpu::opcode_2E() { Cpu::instr_ld(l); };
void Cpu::opcode_2F(){};
void Cpu::opcode_30(){};
void Cpu::opcode_31(){};
void Cpu::opcode_32(){};
void Cpu::opcode_33(){};
void Cpu::opcode_34(){};
void Cpu::opcode_35(){};
void Cpu::opcode_36() { Cpu::instr_ld(Reg::Word(h, l)); };
void Cpu::opcode_37(){};
void Cpu::opcode_38(){};
void Cpu::opcode_39(){};
void Cpu::opcode_3A(){};
void Cpu::opcode_3B(){};
void Cpu::opcode_3C(){};
void Cpu::opcode_3D(){};
void Cpu::opcode_3E(){};
void Cpu::opcode_3F(){};
void Cpu::opcode_40() { Cpu::instr_ld(b, b); };
void Cpu::opcode_41() { Cpu::instr_ld(b, c); };
void Cpu::opcode_43() { Cpu::instr_ld(b, d); };
void Cpu::opcode_42() { Cpu::instr_ld(b, e); };
void Cpu::opcode_44() { Cpu::instr_ld(b, h); };
void Cpu::opcode_45() { Cpu::instr_ld(b, l); };
void Cpu::opcode_46() { Cpu::instr_ld(b, Reg::Word(h, l)); };
void Cpu::opcode_47(){};
void Cpu::opcode_48() { Cpu::instr_ld(c, b); };
void Cpu::opcode_4A() { Cpu::instr_ld(c, c); };
void Cpu::opcode_49() { Cpu::instr_ld(c, d); };
void Cpu::opcode_4B() { Cpu::instr_ld(c, e); };
void Cpu::opcode_4C() { Cpu::instr_ld(c, h); };
void Cpu::opcode_4D() { Cpu::instr_ld(c, l); };
void Cpu::opcode_4E() { Cpu::instr_ld(c, Reg::Word(h, l)); };
void Cpu::opcode_4F(){};
void Cpu::opcode_50() { Cpu::instr_ld(d, b); };
void Cpu::opcode_51() { Cpu::instr_ld(d, c); };
void Cpu::opcode_52() { Cpu::instr_ld(d, d); };
void Cpu::opcode_53() { Cpu::instr_ld(d, e); };
void Cpu::opcode_54() { Cpu::instr_ld(d, h); };
void Cpu::opcode_55() { Cpu::instr_ld(d, l); };
void Cpu::opcode_56() { Cpu::instr_ld(d, Reg::Word(h, l)); };
void Cpu::opcode_57(){};
void Cpu::opcode_58() { Cpu::instr_ld(e, b); };
void Cpu::opcode_59() { Cpu::instr_ld(e, c); };
void Cpu::opcode_5A() { Cpu::instr_ld(e, d); };
void Cpu::opcode_5B() { Cpu::instr_ld(e, e); };
void Cpu::opcode_5C() { Cpu::instr_ld(e, h); };
void Cpu::opcode_5D() { Cpu::instr_ld(e, l); };
void Cpu::opcode_5E() { Cpu::instr_ld(e, Reg::Word(h, l)); };
void Cpu::opcode_5F(){};
void Cpu::opcode_60() { Cpu::instr_ld(h, b); };
void Cpu::opcode_61() { Cpu::instr_ld(h, c); };
void Cpu::opcode_62() { Cpu::instr_ld(h, d); };
void Cpu::opcode_63() { Cpu::instr_ld(h, e); };
void Cpu::opcode_64() { Cpu::instr_ld(h, h); };
void Cpu::opcode_65() { Cpu::instr_ld(h, l); };
void Cpu::opcode_66() { Cpu::instr_ld(h, Reg::Word(h, l)); };
void Cpu::opcode_67(){};
void Cpu::opcode_68() { Cpu::instr_ld(l, b); };
void Cpu::opcode_69() { Cpu::instr_ld(l, c); };
void Cpu::opcode_6A() { Cpu::instr_ld(l, d); };
void Cpu::opcode_6B() { Cpu::instr_ld(l, e); };
void Cpu::opcode_6C() { Cpu::instr_ld(l, h); };
void Cpu::opcode_6D() { Cpu::instr_ld(l, l); };
void Cpu::opcode_6E() { Cpu::instr_ld(l, Reg::Word(h, l)); };
void Cpu::opcode_6F(){};
void Cpu::opcode_70() { Cpu::instr_ld(Reg::Word(h, l), b); };
void Cpu::opcode_71() { Cpu::instr_ld(Reg::Word(h, l), c); };
void Cpu::opcode_72() { Cpu::instr_ld(Reg::Word(h, l), d); };
void Cpu::opcode_73() { Cpu::instr_ld(Reg::Word(h, l), e); };
void Cpu::opcode_74() { Cpu::instr_ld(Reg::Word(h, l), h); };
void Cpu::opcode_75() { Cpu::instr_ld(Reg::Word(h, l), l); };
void Cpu::opcode_76() { Cpu::instr_halt(); };
void Cpu::opcode_77(){};
void Cpu::opcode_78() { Cpu::instr_ld(a, b); };
void Cpu::opcode_79() { Cpu::instr_ld(a, c); };
void Cpu::opcode_7A() { Cpu::instr_ld(a, d); };
void Cpu::opcode_7B() { Cpu::instr_ld(a, e); };
void Cpu::opcode_7C() { Cpu::instr_ld(a, h); };
void Cpu::opcode_7D() { Cpu::instr_ld(a, l); };
void Cpu::opcode_7E() { Cpu::instr_ld(a, Reg::Word(h, l)); };
void Cpu::opcode_7F() { Cpu::instr_ld(a, a); };
void Cpu::opcode_80(){};
void Cpu::opcode_81(){};
void Cpu::opcode_82(){};
void Cpu::opcode_83(){};
void Cpu::opcode_84(){};
void Cpu::opcode_85(){};
void Cpu::opcode_86(){};
void Cpu::opcode_87(){};
void Cpu::opcode_88(){};
void Cpu::opcode_89(){};
void Cpu::opcode_8A(){};
void Cpu::opcode_8B(){};
void Cpu::opcode_8C(){};
void Cpu::opcode_8D(){};
void Cpu::opcode_8E(){};
void Cpu::opcode_8F(){};
void Cpu::opcode_90(){};
void Cpu::opcode_91(){};
void Cpu::opcode_92(){};
void Cpu::opcode_93(){};
void Cpu::opcode_94(){};
void Cpu::opcode_95(){};
void Cpu::opcode_96(){};
void Cpu::opcode_97(){};
void Cpu::opcode_98(){};
void Cpu::opcode_99(){};
void Cpu::opcode_9A(){};
void Cpu::opcode_9B(){};
void Cpu::opcode_9C(){};
void Cpu::opcode_9D(){};
void Cpu::opcode_9E(){};
void Cpu::opcode_9F(){};
void Cpu::opcode_A0(){};
void Cpu::opcode_A1(){};
void Cpu::opcode_A2(){};
void Cpu::opcode_A3(){};
void Cpu::opcode_A4(){};
void Cpu::opcode_A5(){};
void Cpu::opcode_A6(){};
void Cpu::opcode_A7(){};
void Cpu::opcode_A8(){};
void Cpu::opcode_A9(){};
void Cpu::opcode_AA(){};
void Cpu::opcode_AB(){};
void Cpu::opcode_AC(){};
void Cpu::opcode_AD(){};
void Cpu::opcode_AE(){};
void Cpu::opcode_AF(){};
void Cpu::opcode_B0(){};
void Cpu::opcode_B1(){};
void Cpu::opcode_B2(){};
void Cpu::opcode_B3(){};
void Cpu::opcode_B4(){};
void Cpu::opcode_B5(){};
void Cpu::opcode_B6(){};
void Cpu::opcode_B7(){};
void Cpu::opcode_B8(){};
void Cpu::opcode_B9(){};
void Cpu::opcode_BA(){};
void Cpu::opcode_BB(){};
void Cpu::opcode_BC(){};
void Cpu::opcode_BD(){};
void Cpu::opcode_BE(){};
void Cpu::opcode_BF(){};
void Cpu::opcode_C0(){};
void Cpu::opcode_C1(){};
void Cpu::opcode_C2(){};
void Cpu::opcode_C3(){};
void Cpu::opcode_C4(){};
void Cpu::opcode_C5(){};
void Cpu::opcode_C6(){};
void Cpu::opcode_C7(){};
void Cpu::opcode_C8(){};
void Cpu::opcode_C9(){};
void Cpu::opcode_CA(){};
void Cpu::opcode_CB(){};
void Cpu::opcode_CC(){};
void Cpu::opcode_CD(){};
void Cpu::opcode_CE(){};
void Cpu::opcode_CF(){};
void Cpu::opcode_D0(){};
void Cpu::opcode_D1(){};
void Cpu::opcode_D2(){};
void Cpu::opcode_D3(){};
void Cpu::opcode_D4(){};
void Cpu::opcode_D5(){};
void Cpu::opcode_D6(){};
void Cpu::opcode_D7(){};
void Cpu::opcode_D8(){};
void Cpu::opcode_D9(){};
void Cpu::opcode_DA(){};
void Cpu::opcode_DB(){};
void Cpu::opcode_DC(){};
void Cpu::opcode_DD(){};
void Cpu::opcode_DE(){};
void Cpu::opcode_DF(){};
void Cpu::opcode_E0(){};
void Cpu::opcode_E1(){};
void Cpu::opcode_E2(){};
void Cpu::opcode_E3(){};
void Cpu::opcode_E4(){};
void Cpu::opcode_E5(){};
void Cpu::opcode_E6(){};
void Cpu::opcode_E7(){};
void Cpu::opcode_E8(){};
void Cpu::opcode_E9(){};
void Cpu::opcode_EA(){};
void Cpu::opcode_EB(){};
void Cpu::opcode_EC(){};
void Cpu::opcode_ED(){};
void Cpu::opcode_EE(){};
void Cpu::opcode_EF(){};
void Cpu::opcode_F0(){};
void Cpu::opcode_F1(){};
void Cpu::opcode_F2(){};
void Cpu::opcode_F3() { Cpu::instr_di(); };
void Cpu::opcode_F4(){};
void Cpu::opcode_F5(){};
void Cpu::opcode_F6(){};
void Cpu::opcode_F7(){};
void Cpu::opcode_F8(){};
void Cpu::opcode_F9(){};
void Cpu::opcode_FA(){};
void Cpu::opcode_FB() { Cpu::instr_di(); };
void Cpu::opcode_FC(){};
void Cpu::opcode_FD(){};
void Cpu::opcode_FE(){};
void Cpu::opcode_FF(){};

void Cpu::opcode_CB_00(){};
void Cpu::opcode_CB_01(){};
void Cpu::opcode_CB_02(){};
void Cpu::opcode_CB_03(){};
void Cpu::opcode_CB_04(){};
void Cpu::opcode_CB_05(){};
void Cpu::opcode_CB_06(){};
void Cpu::opcode_CB_07(){};
void Cpu::opcode_CB_08(){};
void Cpu::opcode_CB_09(){};
void Cpu::opcode_CB_0A(){};
void Cpu::opcode_CB_0B(){};
void Cpu::opcode_CB_0C(){};
void Cpu::opcode_CB_0D(){};
void Cpu::opcode_CB_0E(){};
void Cpu::opcode_CB_0F(){};
void Cpu::opcode_CB_10(){};
void Cpu::opcode_CB_11(){};
void Cpu::opcode_CB_12(){};
void Cpu::opcode_CB_13(){};
void Cpu::opcode_CB_14(){};
void Cpu::opcode_CB_15(){};
void Cpu::opcode_CB_16(){};
void Cpu::opcode_CB_17(){};
void Cpu::opcode_CB_18(){};
void Cpu::opcode_CB_19(){};
void Cpu::opcode_CB_1A(){};
void Cpu::opcode_CB_1B(){};
void Cpu::opcode_CB_1C(){};
void Cpu::opcode_CB_1D(){};
void Cpu::opcode_CB_1E(){};
void Cpu::opcode_CB_1F(){};
void Cpu::opcode_CB_20(){};
void Cpu::opcode_CB_21(){};
void Cpu::opcode_CB_22(){};
void Cpu::opcode_CB_23(){};
void Cpu::opcode_CB_24(){};
void Cpu::opcode_CB_25(){};
void Cpu::opcode_CB_26(){};
void Cpu::opcode_CB_27(){};
void Cpu::opcode_CB_28(){};
void Cpu::opcode_CB_29(){};
void Cpu::opcode_CB_2A(){};
void Cpu::opcode_CB_2B(){};
void Cpu::opcode_CB_2C(){};
void Cpu::opcode_CB_2D(){};
void Cpu::opcode_CB_2E(){};
void Cpu::opcode_CB_2F(){};
void Cpu::opcode_CB_30(){};
void Cpu::opcode_CB_31(){};
void Cpu::opcode_CB_32(){};
void Cpu::opcode_CB_33(){};
void Cpu::opcode_CB_34(){};
void Cpu::opcode_CB_35(){};
void Cpu::opcode_CB_36(){};
void Cpu::opcode_CB_37(){};
void Cpu::opcode_CB_38(){};
void Cpu::opcode_CB_39(){};
void Cpu::opcode_CB_3A(){};
void Cpu::opcode_CB_3B(){};
void Cpu::opcode_CB_3C(){};
void Cpu::opcode_CB_3D(){};
void Cpu::opcode_CB_3E(){};
void Cpu::opcode_CB_3F(){};
void Cpu::opcode_CB_40(){};
void Cpu::opcode_CB_41(){};
void Cpu::opcode_CB_42(){};
void Cpu::opcode_CB_43(){};
void Cpu::opcode_CB_44(){};
void Cpu::opcode_CB_45(){};
void Cpu::opcode_CB_46(){};
void Cpu::opcode_CB_47(){};
void Cpu::opcode_CB_48(){};
void Cpu::opcode_CB_49(){};
void Cpu::opcode_CB_4A(){};
void Cpu::opcode_CB_4B(){};
void Cpu::opcode_CB_4C(){};
void Cpu::opcode_CB_4D(){};
void Cpu::opcode_CB_4E(){};
void Cpu::opcode_CB_4F(){};
void Cpu::opcode_CB_50(){};
void Cpu::opcode_CB_51(){};
void Cpu::opcode_CB_52(){};
void Cpu::opcode_CB_53(){};
void Cpu::opcode_CB_54(){};
void Cpu::opcode_CB_55(){};
void Cpu::opcode_CB_56(){};
void Cpu::opcode_CB_57(){};
void Cpu::opcode_CB_58(){};
void Cpu::opcode_CB_59(){};
void Cpu::opcode_CB_5A(){};
void Cpu::opcode_CB_5B(){};
void Cpu::opcode_CB_5C(){};
void Cpu::opcode_CB_5D(){};
void Cpu::opcode_CB_5E(){};
void Cpu::opcode_CB_5F(){};
void Cpu::opcode_CB_60(){};
void Cpu::opcode_CB_61(){};
void Cpu::opcode_CB_62(){};
void Cpu::opcode_CB_63(){};
void Cpu::opcode_CB_64(){};
void Cpu::opcode_CB_65(){};
void Cpu::opcode_CB_66(){};
void Cpu::opcode_CB_67(){};
void Cpu::opcode_CB_68(){};
void Cpu::opcode_CB_69(){};
void Cpu::opcode_CB_6A(){};
void Cpu::opcode_CB_6B(){};
void Cpu::opcode_CB_6C(){};
void Cpu::opcode_CB_6D(){};
void Cpu::opcode_CB_6E(){};
void Cpu::opcode_CB_6F(){};
void Cpu::opcode_CB_70(){};
void Cpu::opcode_CB_71(){};
void Cpu::opcode_CB_72(){};
void Cpu::opcode_CB_73(){};
void Cpu::opcode_CB_74(){};
void Cpu::opcode_CB_75(){};
void Cpu::opcode_CB_76(){};
void Cpu::opcode_CB_77(){};
void Cpu::opcode_CB_78(){};
void Cpu::opcode_CB_79(){};
void Cpu::opcode_CB_7A(){};
void Cpu::opcode_CB_7B(){};
void Cpu::opcode_CB_7C(){};
void Cpu::opcode_CB_7D(){};
void Cpu::opcode_CB_7E(){};
void Cpu::opcode_CB_7F(){};
void Cpu::opcode_CB_80(){};
void Cpu::opcode_CB_81(){};
void Cpu::opcode_CB_82(){};
void Cpu::opcode_CB_83(){};
void Cpu::opcode_CB_84(){};
void Cpu::opcode_CB_85(){};
void Cpu::opcode_CB_86(){};
void Cpu::opcode_CB_87(){};
void Cpu::opcode_CB_88(){};
void Cpu::opcode_CB_89(){};
void Cpu::opcode_CB_8A(){};
void Cpu::opcode_CB_8B(){};
void Cpu::opcode_CB_8C(){};
void Cpu::opcode_CB_8D(){};
void Cpu::opcode_CB_8E(){};
void Cpu::opcode_CB_8F(){};
void Cpu::opcode_CB_90(){};
void Cpu::opcode_CB_91(){};
void Cpu::opcode_CB_92(){};
void Cpu::opcode_CB_93(){};
void Cpu::opcode_CB_94(){};
void Cpu::opcode_CB_95(){};
void Cpu::opcode_CB_96(){};
void Cpu::opcode_CB_97(){};
void Cpu::opcode_CB_98(){};
void Cpu::opcode_CB_99(){};
void Cpu::opcode_CB_9A(){};
void Cpu::opcode_CB_9B(){};
void Cpu::opcode_CB_9C(){};
void Cpu::opcode_CB_9D(){};
void Cpu::opcode_CB_9E(){};
void Cpu::opcode_CB_9F(){};
void Cpu::opcode_CB_A0(){};
void Cpu::opcode_CB_A1(){};
void Cpu::opcode_CB_A2(){};
void Cpu::opcode_CB_A3(){};
void Cpu::opcode_CB_A4(){};
void Cpu::opcode_CB_A5(){};
void Cpu::opcode_CB_A6(){};
void Cpu::opcode_CB_A7(){};
void Cpu::opcode_CB_A8(){};
void Cpu::opcode_CB_A9(){};
void Cpu::opcode_CB_AA(){};
void Cpu::opcode_CB_AB(){};
void Cpu::opcode_CB_AC(){};
void Cpu::opcode_CB_AD(){};
void Cpu::opcode_CB_AE(){};
void Cpu::opcode_CB_AF(){};
void Cpu::opcode_CB_B0(){};
void Cpu::opcode_CB_B1(){};
void Cpu::opcode_CB_B2(){};
void Cpu::opcode_CB_B3(){};
void Cpu::opcode_CB_B4(){};
void Cpu::opcode_CB_B5(){};
void Cpu::opcode_CB_B6(){};
void Cpu::opcode_CB_B7(){};
void Cpu::opcode_CB_B8(){};
void Cpu::opcode_CB_B9(){};
void Cpu::opcode_CB_BA(){};
void Cpu::opcode_CB_BB(){};
void Cpu::opcode_CB_BC(){};
void Cpu::opcode_CB_BD(){};
void Cpu::opcode_CB_BE(){};
void Cpu::opcode_CB_BF(){};
void Cpu::opcode_CB_C0(){};
void Cpu::opcode_CB_C1(){};
void Cpu::opcode_CB_C2(){};
void Cpu::opcode_CB_C3(){};
void Cpu::opcode_CB_C4(){};
void Cpu::opcode_CB_C5(){};
void Cpu::opcode_CB_C6(){};
void Cpu::opcode_CB_C7(){};
void Cpu::opcode_CB_C8(){};
void Cpu::opcode_CB_C9(){};
void Cpu::opcode_CB_CA(){};
void Cpu::opcode_CB_CB(){};
void Cpu::opcode_CB_CC(){};
void Cpu::opcode_CB_CD(){};
void Cpu::opcode_CB_CE(){};
void Cpu::opcode_CB_CF(){};
void Cpu::opcode_CB_D0(){};
void Cpu::opcode_CB_D1(){};
void Cpu::opcode_CB_D2(){};
void Cpu::opcode_CB_D3(){};
void Cpu::opcode_CB_D4(){};
void Cpu::opcode_CB_D5(){};
void Cpu::opcode_CB_D6(){};
void Cpu::opcode_CB_D7(){};
void Cpu::opcode_CB_D8(){};
void Cpu::opcode_CB_D9(){};
void Cpu::opcode_CB_DA(){};
void Cpu::opcode_CB_DB(){};
void Cpu::opcode_CB_DC(){};
void Cpu::opcode_CB_DD(){};
void Cpu::opcode_CB_DE(){};
void Cpu::opcode_CB_DF(){};
void Cpu::opcode_CB_E0(){};
void Cpu::opcode_CB_E1(){};
void Cpu::opcode_CB_E2(){};
void Cpu::opcode_CB_E3(){};
void Cpu::opcode_CB_E4(){};
void Cpu::opcode_CB_E5(){};
void Cpu::opcode_CB_E6(){};
void Cpu::opcode_CB_E7(){};
void Cpu::opcode_CB_E8(){};
void Cpu::opcode_CB_E9(){};
void Cpu::opcode_CB_EA(){};
void Cpu::opcode_CB_EB(){};
void Cpu::opcode_CB_EC(){};
void Cpu::opcode_CB_ED(){};
void Cpu::opcode_CB_EE(){};
void Cpu::opcode_CB_EF(){};
void Cpu::opcode_CB_F0(){};
void Cpu::opcode_CB_F1(){};
void Cpu::opcode_CB_F2(){};
void Cpu::opcode_CB_F3(){};
void Cpu::opcode_CB_F4(){};
void Cpu::opcode_CB_F5(){};
void Cpu::opcode_CB_F6(){};
void Cpu::opcode_CB_F7(){};
void Cpu::opcode_CB_F8(){};
void Cpu::opcode_CB_F9(){};
void Cpu::opcode_CB_FA(){};
void Cpu::opcode_CB_FB(){};
void Cpu::opcode_CB_FC(){};
void Cpu::opcode_CB_FD(){};
void Cpu::opcode_CB_FE(){};
void Cpu::opcode_CB_FF(){};
