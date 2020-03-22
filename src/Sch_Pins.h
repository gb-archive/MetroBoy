#pragma once
#include "Sch_Common.h"

namespace Schematics {

struct WavePins {
  void dump_pins(TextPainter& text) {
    text.dprintf("----- WAVE_PINS -----\n");
    text.dprintf("CLK_AxxxxxGH %d\n", BORY_AxxxxxGH.a.val);
  }

  PinOut BORY_AxxxxxGH;
};

//-----------------------------------------------------------------------------
// These signals connect directly to OAM

struct OamPins {

  void dump_pins(TextPainter& text) {
    text.dprintf("----- OAM_PINS -----\n");
    text.dprintf("CLK_A %d\n", CLK_A.a.val);
    text.dprintf("OE    %d\n", OE.a.val);
    text.dprintf("WR_A  %d\n", WR_A.a.val);
    text.dprintf("WR_B  %d\n", WR_B.a.val);

    text.add_text("Axx   ");
    dump2(text, A7.a);
    dump2(text, A6.a);
    dump2(text, A5.a);
    dump2(text, A4.a);
    dump2(text, A3.a);
    dump2(text, A2.a);
    dump2(text, A1.a);
    dump2(text, A0.a);
    text.newline();

    text.add_text("A_Dx  ");
    dump2(text, A_D7.a);
    dump2(text, A_D6.a);
    dump2(text, A_D5.a);
    dump2(text, A_D4.a);
    dump2(text, A_D3.a);
    dump2(text, A_D2.a);
    dump2(text, A_D1.a);
    dump2(text, A_D0.a);
    text.newline();

    text.add_text("B_Dx  ");
    dump2(text, B_D7.a);
    dump2(text, B_D6.a);
    dump2(text, B_D5.a);
    dump2(text, B_D4.a);
    dump2(text, B_D3.a);
    dump2(text, B_D2.a);
    dump2(text, B_D1.a);
    dump2(text, B_D0.a);
    text.newline();

    text.newline();
  }

  /*p25.COTA*/ PinOut CLK_A;
  /*p28.ZODO*/ PinOut OE;
  /*p28.ZONE*/ PinOut WR_A; // definitely write
  /*p28.ZOFE*/ PinOut WR_B; // definitely write

  /*p28.GEKA*/ PinOut A0;
  /*p28.ZYFO*/ PinOut A1;
  /*p28.YFOT*/ PinOut A2;
  /*p28.YFOC*/ PinOut A3;
  /*p28.YVOM*/ PinOut A4;
  /*p28.YMEV*/ PinOut A5;
  /*p28.XEMU*/ PinOut A6;
  /*p28.YZET*/ PinOut A7;

  Tribuf A_D0;
  Tribuf A_D1;
  Tribuf A_D2;
  Tribuf A_D3;
  Tribuf A_D4;
  Tribuf A_D5;
  Tribuf A_D6;
  Tribuf A_D7;

  Tribuf B_D0;
  Tribuf B_D1;
  Tribuf B_D2;
  Tribuf B_D3;
  Tribuf B_D4;
  Tribuf B_D5;
  Tribuf B_D6;
  Tribuf B_D7;
};

//-----------------------------------------------------------------------------

struct CpuPins {

  void dump_pins(TextPainter& text) {
    text.dprintf("----- CPU DBG/RST -----\n");
    text.dprintf("PIN_RESET     %d\n", PIN_RESET   .a.val);
    text.dprintf("CPU_RESET     %d\n", CPU_RESET   .a.val);
    text.dprintf("CLK_GOOD      %d\n", CLK_GOOD    .a.val);
    text.dprintf("T1nT2         %d\n", T1nT2        .a.val);
    text.dprintf("T1T2n         %d\n", T1T2n        .a.val);

    text.dprintf("----- CPU CLOCKS -----\n");
    text.dprintf("BOWA_xBCDEFGH %d\n", BOWA_xBCDEFGH.a.val);
    text.dprintf("BEDO_Axxxxxxx %d\n", BEDO_Axxxxxxx.a.val);
    text.dprintf("BEKO_ABCDxxxx %d\n", BEKO_ABCDxxxx.a.val);
    text.dprintf("BUDE_xxxxEFGH %d\n", BUDE_xxxxEFGH.a.val);
    text.dprintf("BUKE_AxxxxxGH %d\n", BUKE_AxxxxxGH.a.val);
    text.dprintf("BOMA_Axxxxxxx %d\n", BOMA_Axxxxxxx.a.val);
    text.dprintf("BOGA_xBCDEFGH %d\n", BOGA_xBCDEFGH.a.val);

    text.dprintf("----- FROM CPU -----\n");
    text.dprintf("CLKREQ        %d\n", CLKREQ      .a.val);
    text.dprintf("FROM_CPU5     %d\n", FROM_CPU5   .a.val);
    text.dprintf("FROM_CPU6     %d\n", FROM_CPU6   .a.val);

    text.dprintf("----- TO CPU -----\n");
    text.dprintf("AFER          %d\n", AFER        .a.val);
    text.dprintf("TO_CPU2       %d\n", TO_CPU2      .a.val);
    text.dprintf("SYRO          %d\n", SYRO         .a.val);
    text.dprintf("READ_BOOTROM  %d\n", READ_BOOTROM .a.val);

    text.dprintf("----- CPU INT -----\n");
    text.dprintf("INT_VBLANK    %d\n", INT_VBLANK .a.val);
    text.dprintf("INT_STAT      %d\n", INT_STAT   .a.val);
    text.dprintf("INT_TIMER     %d\n", INT_TIMER  .a.val);
    text.dprintf("INT_SERIAL    %d\n", INT_SERIAL .a.val);
    text.dprintf("INT_JOYPAD    %d\n", INT_JOYPAD .a.val);
    text.dprintf("ACK_VBLANK    %d\n", ACK_VBLANK .a.val);
    text.dprintf("ACK_STAT      %d\n", ACK_STAT   .a.val);
    text.dprintf("ACK_TIMER     %d\n", ACK_TIMER  .a.val);
    text.dprintf("ACK_SERIAL    %d\n", ACK_SERIAL .a.val);
    text.dprintf("ACK_JOYPAD    %d\n", ACK_JOYPAD .a.val);

    text.dprintf("----- CPU BUS -----\n");
    text.dprintf("CPU_RAW_RD    %d\n", CPU_RAW_RD  .a.val);
    text.dprintf("CPU_RAW_WR    %d\n", CPU_RAW_WR  .a.val);
    text.dprintf("ADDR_VALID    %d\n", ADDR_VALIDn  .a.val);
    
    text.add_text("Axx ");
    dump2(text, A15.a);
    dump2(text, A14.a);
    dump2(text, A13.a);
    dump2(text, A12.a);
    text.add_char(':');
    dump2(text, A11.a);
    dump2(text, A10.a);
    dump2(text, A09.a);
    dump2(text, A08.a);
    text.add_char(':');
    dump2(text, A07.a);
    dump2(text, A06.a);
    dump2(text, A05.a);
    dump2(text, A04.a);
    text.add_char(':');
    dump2(text, A03.a);
    dump2(text, A02.a);
    dump2(text, A01.a);
    dump2(text, A00.a);
    text.newline();

    text.add_text("Dxx ");
    dump2(text, D7.a);
    dump2(text, D6.a);
    dump2(text, D5.a);
    dump2(text, D4.a);
    text.add_char(':');
    dump2(text, D3.a);
    dump2(text, D2.a);
    dump2(text, D1.a);
    dump2(text, D0.a);
    text.newline();

    text.newline();
  }

  int get_addr() const {
    return pack(A00, A01, A02, A03, A04, A05, A06, A07,
                A08, A09, A10, A11, A12, A13, A14, A15);
  }

  int get_data() const {
    return pack(D0, D1, D2, D3, D4, D5, D6, D7);
  }

  void preset_addr(bool oe, uint16_t addr) {
    A00.preset(oe, addr & 0x0001);
    A01.preset(oe, addr & 0x0002);
    A02.preset(oe, addr & 0x0004);
    A03.preset(oe, addr & 0x0008);
    A04.preset(oe, addr & 0x0010);
    A05.preset(oe, addr & 0x0020);
    A06.preset(oe, addr & 0x0040);
    A07.preset(oe, addr & 0x0080);
    A08.preset(oe, addr & 0x0100);
    A09.preset(oe, addr & 0x0200);
    A10.preset(oe, addr & 0x0400);
    A11.preset(oe, addr & 0x0800);
    A12.preset(oe, addr & 0x1000);
    A13.preset(oe, addr & 0x2000);
    A14.preset(oe, addr & 0x4000);
    A15.preset(oe, addr & 0x8000);
  }

  /*
  void preset_data(bool oe, uint8_t data) {
    D0.preset(oe, data & 0x01);
    D1.preset(oe, data & 0x02);
    D2.preset(oe, data & 0x04);
    D3.preset(oe, data & 0x08);
    D4.preset(oe, data & 0x10);
    D5.preset(oe, data & 0x20);
    D6.preset(oe, data & 0x40);
    D7.preset(oe, data & 0x80);
  }
  */

  void set_data(bool oe, uint8_t data) {
    D0.set(oe, data & 0x01);
    D1.set(oe, data & 0x02);
    D2.set(oe, data & 0x04);
    D3.set(oe, data & 0x08);
    D4.set(oe, data & 0x10);
    D5.set(oe, data & 0x20);
    D6.set(oe, data & 0x40);
    D7.set(oe, data & 0x80);
  }

  //----------


  // ADDR_VALID and one of the other signals might be switched

  PinIn  CLKREQ;       // top center port PORTC_00: -> ABOL (an inverter) -> BATE. Something about "cpu ready". clock request?
  PinIn  CPU_RAW_RD;   // top right port PORTA_00: -> P07.UJYV, P08.LAGU, P08.LAVO
  PinIn  CPU_RAW_WR;   // top right port PORTA_01: -> P01.AREV, P08.LAGU. This is almost definitely "raw write"
  PinIn  ADDR_VALIDn;   // top right port PORTA_06: -> P01.AGUT, P08.TEX0. This is almost definitely "address valid"
  PinIn  FROM_CPU5;    // PORTD_05: -> FROM_CPU5
  PinIn  FROM_CPU6;    // top left port PORTD_00: -> P07.LEXY, doesn't do anything

  PinIn  A00;          // bottom right port PORTB_00: -> A00
  PinIn  A01;          // bottom right port PORTB_04: -> A01
  PinIn  A02;          // bottom right port PORTB_08: -> A02
  PinIn  A03;          // bottom right port PORTB_12: -> A03
  PinIn  A04;          // bottom right port PORTB_16: -> A04
  PinIn  A05;          // bottom right port PORTB_20: -> A05
  PinIn  A06;          // bottom right port PORTB_24: -> A06
  PinIn  A07;          // bottom right port PORTB_28: -> A07
  PinIn  A08;          // bottom right port PORTB_02: -> A08
  PinIn  A09;          // bottom right port PORTB_06: -> A09
  PinIn  A10;          // bottom right port PORTB_10: -> A10
  PinIn  A11;          // bottom right port PORTB_14: -> A11
  PinIn  A12;          // bottom right port PORTB_18: -> A12
  PinIn  A13;          // bottom right port PORTB_22: -> A13
  PinIn  A14;          // bottom right port PORTB_26: -> A14
  PinIn  A15;          // bottom right port PORTB_30: -> A15

  PinIn  ACK_VBLANK;   // bottom right port PORTB_01: -> P02.LETY, vblank int ack
  PinIn  ACK_STAT;     // bottom right port PORTB_05: -> P02.LEJA, stat int ack
  PinIn  ACK_TIMER;    // bottom right port PORTB_09: -> P02.LESA, timer int ack
  PinIn  ACK_SERIAL;   // bottom right port PORTB_13: -> P02.LUFE, serial int ack
  PinIn  ACK_JOYPAD;   // bottom right port PORTB_17: -> P02.LAMO, joypad int ack

  //----------

  PinOut AFER;         // top center port PORTC_01: <- P01.AFER , reset related reg
  PinOut PIN_RESET;    // top center port PORTC_02: <- PIN_RESET directly connected to the pad
  PinOut CLK_GOOD;     // top center port PORTC_03: <- chip.CLKIN_A top wire on PAD_XI,
  PinOut CPU_RESET;    // top center port PORTC_04: <- P01.CPU_RESET
  PinOut T1nT2;        // top right port PORTA_02: <- P07.T1nT2
  PinOut T1T2n;        // top right port PORTA_05: <- P07.T1T2n

  PinOut BOWA_xBCDEFGH; // top left port PORTD_01: <- P01.BOWA
  PinOut BEDO_Axxxxxxx; // top left port PORTD_02: <- P01.BEDO
  PinOut BEKO_ABCDxxxx;         // top left port PORTD_03: <- P01.BEKO connection not indicated on P01
  PinOut BUDE_xxxxEFGH;         // top left port PORTD_04: <- P01.BUDE
  PinOut BUKE_AxxxxxGH;         // PORTD_06: <- P01.BUKE _____f__
  PinOut BOMA_Axxxxxxx;         // PORTD_07: <- P01.RESET_CLK _____fgh
  PinOut BOGA_xBCDEFGH;         // PORTD_08: <- P01.BOGA abcde___

  PinOut TO_CPU2;      // top right wire by itself <- P02.AWOB
  PinOut SYRO;         // top right port PORTA_03: <- P25.SYRO

  // TUTU-> ->YULA ->SOBY
  PinOut READ_BOOTROM; // top right port PORTA_04: <- P07.READ_BOOTROM tutu?

  PinOut INT_VBLANK;   // bottom right port PORTB_03: <- P02.LOPE, vblank int
  PinOut INT_STAT;     // bottom right port PORTB_07: <- P02.LALU, stat int
  PinOut INT_TIMER;    // bottom right port PORTB_11: <- P02.NYBO, timer int
  PinOut INT_SERIAL;   // bottom right port PORTB_15: <- P02.UBUL, serial int
  PinOut INT_JOYPAD;   // bottom right port PORTB_19: <- P02.ULAK, joypad int

  // FROM_CPU5 controls driving the external data pins onto the internal data
  // bus and other stuff. is this actually a clock, or like OE?
  // if this is low, writes to the APU don't happen and writes to TIMA don't
  // actually load TIMA (I think).
  
  //----------
  // bottom left port, tristate data bus

  Tribuf D0;
  Tribuf D1;
  Tribuf D2;
  Tribuf D3;
  Tribuf D4;
  Tribuf D5;
  Tribuf D6;
  Tribuf D7;
};

//-----------------------------------------------------------------------------
// Clock/reset/debug

struct SysPins {

  void dump_pins(TextPainter& text) {
    text.dprintf("----- SYS_PINS -----\n");
    text.dprintf("RST      %d\n", RST.a.val);
    text.dprintf("CLK_GOOD %d\n", CLK_GOOD.a.val);
    text.dprintf("CLK_IN   %d\n", CLK_IN.a.val);
    text.dprintf("T1       %d\n", T1.a.val);
    text.dprintf("T2       %d\n", T2.a.val);
    text.newline();
  }

  /* PIN_71 */ PinIn RST;
  /* PIN_74 */ PinIn CLK_GOOD;
  /* PIN_74 */ PinIn CLK_IN;
  /* PIN_76 */ PinIn T2;
  /* PIN_77 */ PinIn T1;
};

//-----------------------------------------------------------------------------

struct VramPins {

  void dump_pins(TextPainter& text) {
    text.dprintf("----- VRAM_PINS -----\n");
    text.dprintf("MCS  %d:x:%d:%d\n", MCS_A.a.val, MCS_C.a.val, MCS_D.a.val);
    text.dprintf("MOE  %d:x:%d:%d\n", MOE_A.a.val, MOE_C.a.val, MOE_D.a.val);
    text.dprintf("MWR  %d:x:%d:%d\n", MWR_A.a.val, MWR_C.a.val, MWR_D.a.val);
    text.dprintf("MAxx 0x%04x\n", pack(MA00_D, MA01_D, MA02_D, MA03_D, MA04_D, MA05_D, MA06_D,
                                       MA07_D, MA08_D, MA09_D, MA10_D, MA11_D, MA12_D));

    text.dprintf("MDx_A 0x%02x\n", pack(MD0_A, MD1_A, MD2_A, MD3_A, MD4_A, MD5_A, MD6_A, MD7_A));
    text.dprintf("MDx_B 0x%02x\n", pack(MD0_B, MD1_B, MD2_B, MD3_B, MD4_B, MD5_B, MD6_B, MD7_B));
    text.dprintf("MDx_C 0x%02x\n", pack(MD0_C, MD1_C, MD2_C, MD3_C, MD4_C, MD5_C, MD6_C, MD7_C));
    text.dprintf("MDx_D 0x%02x\n", pack(MD0_D, MD1_D, MD2_D, MD3_D, MD4_D, MD5_D, MD6_D, MD7_D));
    text.newline();
  }

  //----------
  // VRAM control pins

  /* PIN_43 */ PinOut MCS_A;   // <- P25.SOKY
  /* PIN_43 */ PinIn  MCS_C;   // -> P25.TEFY
  /* PIN_43 */ PinOut MCS_D;   // <- P25.SETY

  /* PIN_45 */ PinOut MOE_A;   // <- P25.REFO
  /* PIN_45 */ PinIn  MOE_C;   // -> P25.TAVY
  /* PIN_45 */ PinOut MOE_D;   // <- P25.SAHA
                             
  /* PIN_49 */ PinOut MWR_A;   // <- P25.SYSY
  /* PIN_49 */ PinIn  MWR_C;   // -> P25.SUDO
  /* PIN_49 */ PinOut MWR_D;   // <- P25.RAGU

  //----------
  // VRAM address pins

  /* PIN_34 */ PinOut MA00_D;  // <- P04.ECAL
  /* PIN_35 */ PinOut MA01_D;  // <- P04.EGEZ
  /* PIN_36 */ PinOut MA02_D;  // <- P04.FUHE
  /* PIN_37 */ PinOut MA03_D;  // <- P04.FYZY
  /* PIN_38 */ PinOut MA04_D;  // <- P04.DAMU
  /* PIN_39 */ PinOut MA05_D;  // <- P04.DAVA
  /* PIN_40 */ PinOut MA06_D;  // <- P04.ETEG
  /* PIN_41 */ PinOut MA07_D;  // <- P04.EREW
  /* PIN_42 */ PinOut MA12_D;  // <- P04.EXYF
  /* PIN_44 */ PinOut MA10_D;  // <- P04.ERAF
  /* PIN_46 */ PinOut MA11_D;  // <- P04.FUSY
  /* PIN_47 */ PinOut MA09_D;  // <- P04.DUVE
  /* PIN_48 */ PinOut MA08_D;  // <- P04.EVAX

  //----------
  // VRAM data pins

  /* PIN_33 */ PinOut MD0_A;   // <- P25.REGE
  /* PIN_31 */ PinOut MD1_A;   // <- P25.RYKY
  /* PIN_30 */ PinOut MD2_A;   // <- P25.RAZO
  /* PIN_29 */ PinOut MD3_A;   // <- P25.RADA
  /* PIN_28 */ PinOut MD4_A;   // <- P25.RYRO
  /* PIN_27 */ PinOut MD5_A;   // <- P25.REVU
  /* PIN_26 */ PinOut MD6_A;   // <- P25.REKU
  /* PIN_25 */ PinOut MD7_A;   // <- P25.RYZE

  /* PIN_33 */ PinOut MD0_B;   // <- P25.ROFA
  /* PIN_31 */ PinOut MD1_B;   // <- P25.ROFA
  /* PIN_30 */ PinOut MD2_B;   // <- P25.ROFA
  /* PIN_29 */ PinOut MD3_B;   // <- P25.ROFA
  /* PIN_28 */ PinOut MD4_B;   // <- P25.ROFA
  /* PIN_27 */ PinOut MD5_B;   // <- P25.ROFA
  /* PIN_26 */ PinOut MD6_B;   // <- P25.ROFA
  /* PIN_25 */ PinOut MD7_B;   // <- P25.ROFA

  /* PIN_33 */ PinIn  MD0_C;   // -> P25.RODY
  /* PIN_31 */ PinIn  MD1_C;   // -> P25.REBA
  /* PIN_30 */ PinIn  MD2_C;   // -> P25.RYDO
  /* PIN_29 */ PinIn  MD3_C;   // -> P25.REMO
  /* PIN_28 */ PinIn  MD4_C;   // -> P25.ROCE
  /* PIN_27 */ PinIn  MD5_C;   // -> P25.ROPU
  /* PIN_26 */ PinIn  MD6_C;   // -> P25.RETA
  /* PIN_25 */ PinIn  MD7_C;   // -> P25.RAKU

  /* PIN_33 */ PinOut MD0_D;   // <- P25.RURA
  /* PIN_31 */ PinOut MD1_D;   // <- P25.RULY
  /* PIN_30 */ PinOut MD2_D;   // <- P25.RARE
  /* PIN_29 */ PinOut MD3_D;   // <- P25.RODU
  /* PIN_28 */ PinOut MD4_D;   // <- P25.RUBE
  /* PIN_27 */ PinOut MD5_D;   // <- P25.RUMU
  /* PIN_26 */ PinOut MD6_D;   // <- P25.RYTY
  /* PIN_25 */ PinOut MD7_D;   // <- P25.RADY
};

//-----------------------------------------------------------------------------

struct SerialPins {
  void dump_pins(TextPainter& text) {
    text.dprintf("----- SER_PINS -----\n");
    text.dprintf("SCK  %d:%d:%d:%d\n", SCK_A.a.val, SCK_B.a.val, SCK_C.a.val, SCK_D.a.val);
    text.dprintf("SIN  %d:%d:%d:%d\n", SIN_A.a.val, SIN_B.a.val, SIN_C.a.val, SIN_D.a.val);
    text.dprintf("SOUT %d\n", SOUT.a.val);
    text.newline();
  }

  //----------
  // Serial pins

  /* PIN_68 */ PinOut SCK_A;   // <- P06.KEXU
  /* PIN_68 */ PinOut SCK_B;   // <- P06.CULY
  /* PIN_68 */ PinIn  SCK_C;   // -> P06.CAVE
  /* PIN_68 */ PinOut SCK_D;   // <- P06.KUJO

  /* PIN_69 */ PinOut SIN_A;   // nc?
  /* PIN_69 */ PinOut SIN_B;   // nc?
  /* PIN_69 */ PinIn  SIN_C;   // -> P06.CAGE
  /* PIN_69 */ PinOut SIN_D;   // nc?

  /* PIN_70 */ PinOut SOUT;    // <- P05.KENA
};

//-----------------------------------------------------------------------------

struct LcdPins {
  void dump_pins(TextPainter& text) {
    text.dprintf("----- LCD_PINS -----\n");
    LD1.dump(text, "LD1 ");
    LD0.dump(text, "LD0 ");
    CPG.dump(text, "CPG ");
    CP .dump(text, "CP  ");
    ST .dump(text, "ST  ");
    CPL.dump(text, "CPL ");
    FR .dump(text, "FR  ");
    S  .dump(text, "S   ");
    text.newline();
  }

  /* PIN_50 */ PinOut LD1;
  /* PIN_51 */ PinOut LD0;
  /* PIN_52 */ PinOut CPG;
  /* PIN_53 */ PinOut CP;
  /* PIN_54 */ PinOut ST;
  /* PIN_55 */ PinOut CPL;
  /* PIN_56 */ PinOut FR;
  /* PIN_57 */ PinOut S;
};

//-----------------------------------------------------------------------------

struct JoypadPins {

  void dump_pins(TextPainter& text) {
    text.dprintf("----- JOY_PINS -----\n");
    text.dprintf("P10 %d:%d:%d:%d\n", P10_A.a.val, P10_B.a.val, P10_C.a.val, P10_D.a.val);
    text.dprintf("P11 %d:%d:%d:%d\n", P11_A.a.val, P11_B.a.val, P11_C.a.val, P11_D.a.val);
    text.dprintf("P12 %d:%d:%d:%d\n", P12_A.a.val, P12_B.a.val, P12_C.a.val, P12_D.a.val);
    text.dprintf("P13 %d:%d:%d:%d\n", P13_A.a.val, P13_B.a.val, P13_C.a.val, P13_D.a.val);
    text.dprintf("P14 %d:x:x:%d\n", P14_A.a.val, P14_D.a.val);
    text.dprintf("P15 %d:x:x:%d\n", P15_A.a.val, P15_D.a.val);
    text.newline();
  }

  // The B connections on the joypad pins are werid.
  // They seem to be used as an input, or at least I can't find the driver
  // PESU
  // RARU ROWE RYKE RYNE RASE REJY REKA ROMY
  // RUNY VYPO TOMY? SEZU? RAWU? PUTE? MYDE RUGO? NYLU WYMO?
  // WEFE WUWE GEFY WYGA? FABY ECAB? DYSO ERUC GEZE GUVA 
  // ARAR ATAJ ASUZ AJEC AKAJ ANOC BENU BEDA
  // BEKU

  /* PIN_67 */ PinOut P10_A;   // <- P05.KOLE
  /* PIN_67 */ PinOut P10_B;   
  /* PIN_67 */ PinIn  P10_C;   // -> P02.KERY, P05.KEVU
  /* PIN_67 */ PinOut P10_D;   // <- P05.KYBU

  /* PIN_66 */ PinOut P11_A;   // <- P05.KYTO
  /* PIN_66 */ PinOut P11_B;   
  /* PIN_66 */ PinIn  P11_C;   // -> P02.KERY, P05.KAPA
  /* PIN_66 */ PinOut P11_D;   // <- P05.KABU

  /* PIN_65 */ PinOut P12_A;   // <- P05.KYHU
  /* PIN_65 */ PinOut P12_B;   
  /* PIN_65 */ PinIn  P12_C;   // -> P02.KERY, P05.KEJA
  /* PIN_65 */ PinOut P12_D;   // <- P05.KASY
                        
  /* PIN_64 */ PinOut P13_A;   // <- P05.KORY
  /* PIN_64 */ PinOut P13_B;   
  /* PIN_64 */ PinIn  P13_C;   // -> P02.KERY, P05.KOLO
  /* PIN_64 */ PinOut P13_D;   // <- P05.KALE
                         
  /* PIN_63 */ PinOut P14_A;   // <- p05.KARU
  /* PIN_63 */ PinOut P14_D;   // <- p05.KELY

  /* PIN_62 */ PinOut P15_A;   // <- p05.CELA
  /* PIN_62 */ PinOut P15_D;   // <- p05.COFY
};

//-----------------------------------------------------------------------------

struct ExtPins {

  inline void dump_pins(TextPainter& text, const PinOut& a, const PinOut& d) {
    dump_pin(text, a.a, d.a);
  }

  inline void dump_pins(TextPainter& text, const PinOut& a, const PinOut& b, const PinIn& c, const PinOut& d) {
    dump_pin(text, a.a, b.a, c.a, d.a);
  }

  void dump_pins(TextPainter& text) {
    text.dprintf("----- EXT_PINS -----\n");

    text.dprintf("PHI %d\n", PHI.a.val);
    text.dprintf("WR  %d\n", WR_A.a.val);
    text.dprintf("RD  %d\n", RD_A.a.val);
    text.dprintf("CS  %d\n", CS_A.a.val);

    text.add_text("Axx ");
    dump_pins(text, A15_A, A15_D);
    dump_pins(text, A14_A, A14_D);
    dump_pins(text, A13_A, A13_D);
    dump_pins(text, A12_A, A12_D);
    text.add_char(':');
    dump_pins(text, A11_A, A11_D);
    dump_pins(text, A10_A, A10_D);
    dump_pins(text, A09_A, A09_D);
    dump_pins(text, A08_A, A08_D);
    text.add_char(':');
    dump_pins(text, A07_A, A07_D);
    dump_pins(text, A06_A, A06_D);
    dump_pins(text, A05_A, A05_D);
    dump_pins(text, A04_A, A04_D);
    text.add_char(':');
    dump_pins(text, A03_A, A03_D);
    dump_pins(text, A02_A, A02_D);
    dump_pins(text, A01_A, A01_D);
    dump_pins(text, A00_A, A00_D);
    text.newline();

    text.add_text("Dxx ");
    dump_pins(text, D7_A, D7_B, D7_C, D7_D);
    dump_pins(text, D6_A, D6_B, D6_C, D6_D);
    dump_pins(text, D5_A, D5_B, D5_C, D5_D);
    dump_pins(text, D4_A, D4_B, D4_C, D4_D);
    dump_pins(text, D3_A, D3_B, D3_C, D3_D);
    dump_pins(text, D2_A, D2_B, D2_C, D2_D);
    dump_pins(text, D1_A, D1_B, D1_C, D1_D);
    dump_pins(text, D0_A, D0_B, D0_C, D0_D);
    text.newline();
  }

  //----------
  // Cart pins

  /* PIN_75 */ PinOut PHI;     // <- P01.BUDE/BEVA

  /* PIN_78 */ PinOut WR_A;   // <- P08.UVER
  /* PIN_78 */ PinIn  WR_C;   // -> P07.UBAL
  /* PIN_78 */ PinOut WR_D;   // <- P08.USUF

  /* PIN_79 */ PinOut RD_A;   // <- P08.UGAC
  /* PIN_79 */ PinIn  RD_C;   // -> P07.UJYV
  /* PIN_79 */ PinOut RD_D;   // <- P08.URUN

  /* PIN_80 */ PinOut CS_A;   // <- P08.TYHO

  //----------
  // Address pins

  /* PIN_01 */ PinOut A00_A;   // <- P08.KUPO
  /* PIN_01 */ PinIn  A00_C;   // -> P08.KOVA
  /* PIN_01 */ PinOut A00_D;   // <- P08.KOTY
                             
  /* PIN_02 */ PinOut A01_A;   // <- P08.CABA
  /* PIN_02 */ PinIn  A01_C;   // -> P08.CAMU
  /* PIN_02 */ PinOut A01_D;   // <- P08.COTU
                             
  /* PIN_03 */ PinOut A02_A;   // <- P08.BOKU
  /* PIN_03 */ PinIn  A02_C;   // -> P08.BUXU
  /* PIN_03 */ PinOut A02_D;   // <- P08.BAJO
                             
  /* PIN_04 */ PinOut A03_A;   // <- P08.BOTY
  /* PIN_04 */ PinIn  A03_C;   // -> P08.BASE
  /* PIN_04 */ PinOut A03_D;   // <- P08.BOLA
                             
  /* PIN_05 */ PinOut A04_A;   // <- P08.BYLA
  /* PIN_05 */ PinIn  A04_C;   // -> P08.AFEC
  /* PIN_05 */ PinOut A04_D;   // <- P08.BEVO
                             
  /* PIN_06 */ PinOut A05_A;   // <- P08.BADU
  /* PIN_06 */ PinIn  A05_C;   // -> P08.ABUP
  /* PIN_06 */ PinOut A05_D;   // <- P08.AJAV
                             
  /* PIN_07 */ PinOut A06_A;   // <- P08.CEPU
  /* PIN_07 */ PinIn  A06_C;   // -> P08.CYGU
  /* PIN_07 */ PinOut A06_D;   // <- P08.CYKA
                             
  /* PIN_08 */ PinOut A07_A;   // <- P08.DEFY
  /* PIN_08 */ PinIn  A07_C;   // -> P08.COGO
  /* PIN_08 */ PinOut A07_D;   // <- P08.COLO
                             
  /* PIN_09 */ PinOut A08_A;   // <- P08.MYNY
  /* PIN_09 */ PinIn  A08_C;   // -> P08.MUJY
  /* PIN_09 */ PinOut A08_D;   // <- P08.MEGO
                             
  /* PIN_10 */ PinOut A09_A;   // <- P08.MUNE
  /* PIN_10 */ PinIn  A09_C;   // -> P08.NENA
  /* PIN_10 */ PinOut A09_D;   // <- P08.MENY
                             
  /* PIN_11 */ PinOut A10_A;   // <- P08.ROXU
  /* PIN_11 */ PinIn  A10_C;   // -> P08.SURA
  /* PIN_11 */ PinOut A10_D;   // <- P08.RORE
                             
  /* PIN_12 */ PinOut A11_A;   // <- P08.LEPY
  /* PIN_12 */ PinIn  A11_C;   // -> P08.MADY
  /* PIN_12 */ PinOut A11_D;   // <- P08.LYNY
                             
  /* PIN_13 */ PinOut A12_A;   // <- P08.LUCE
  /* PIN_13 */ PinIn  A12_C;   // -> P08.LAHE
  /* PIN_13 */ PinOut A12_D;   // <- P08.LOSO
                             
  /* PIN_14 */ PinOut A13_A;   // <- P08.LABE
  /* PIN_14 */ PinIn  A13_C;   // -> P08.LURA
  /* PIN_14 */ PinOut A13_D;   // <- P08.LEVA
                             
  /* PIN_15 */ PinOut A14_A;   // <- P08.PUHE
  /* PIN_15 */ PinIn  A14_C;   // -> P08.PEVO
  /* PIN_15 */ PinOut A14_D;   // <- P08.PAHY
                             
  /* PIN_16 */ PinOut A15_A;   // <- P08.SUZE
  /* PIN_16 */ PinIn  A15_C;   // -> P08.RAZA
  /* PIN_16 */ PinOut A15_D;   // <- P08.RULO

  //----------
  // Data pins

  /* PIN_17 */ PinOut D0_A;    // <- P08.RUXA
  /* PIN_17 */ PinOut D0_B;    // <- P08.LULA
  /* PIN_17 */ PinIn  D0_C;    // -> P08.TOVO,SOMA
  /* PIN_17 */ PinOut D0_D;    // <- P08.RUNE
                             
  /* PIN_18 */ PinOut D1_A;    // <- P08.RUJA
  /* PIN_18 */ PinOut D1_B;    // <- P08.LULA
  /* PIN_18 */ PinIn  D1_C;    // -> P08.RUZY,RONY
  /* PIN_18 */ PinOut D1_D;    // <- P08.RYPU
                             
  /* PIN_19 */ PinOut D2_A;    // <- P08.RABY
  /* PIN_19 */ PinOut D2_B;    // <- P08.LULA
  /* PIN_19 */ PinIn  D2_C;    // -> P08.ROME,RAXY
  /* PIN_19 */ PinOut D2_D;    // <- P08.SULY
                             
  /* PIN_20 */ PinOut D3_A;    // <- P08.RERA
  /* PIN_20 */ PinOut D3_B;    // <- P08.LULA
  /* PIN_20 */ PinIn  D3_C;    // -> P08.SAZA,SELO
  /* PIN_20 */ PinOut D3_D;    // <- P08.SEZE
                             
  /* PIN_21 */ PinOut D4_A;    // <- P08.RORY
  /* PIN_21 */ PinOut D4_B;    // <- P08.LULA
  /* PIN_21 */ PinIn  D4_C;    // -> P08.TEHE,SODY
  /* PIN_21 */ PinOut D4_D;    // <- P08.RESY
                             
  /* PIN_22 */ PinOut D5_A;    // <- P08.RYVO
  /* PIN_22 */ PinOut D5_B;    // <- P08.LULA
  /* PIN_22 */ PinIn  D5_C;    // -> P08.RATU,SAGO
  /* PIN_22 */ PinOut D5_D;    // <- P08.TAMU
                             
  /* PIN_23 */ PinOut D6_A;    // <- P08.RAFY
  /* PIN_23 */ PinOut D6_B;    // <- P08.LULA
  /* PIN_23 */ PinIn  D6_C;    // -> P08.SOCA,RUPA
  /* PIN_23 */ PinOut D6_D;    // <- P08.ROGY
                             
  /* PIN_24 */ PinOut D7_A;    // <- P08.RAVU
  /* PIN_24 */ PinOut D7_B;    // <- P08.LULA
  /* PIN_24 */ PinIn  D7_C;    // -> P08.RYBA,SAZY
  /* PIN_24 */ PinOut D7_D;    // <- P08.RYDA
};

//-----------------------------------------------------------------------------

};