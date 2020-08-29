#include "GateBoyLib/Sch_Joypad.h"

#include "GateBoyLib/Sch_Top.h"

using namespace Schematics;

//-----------------------------------------------------------------------------

void Joypad::dump(Dumper& d) const {
  d("----------  Joypad  ----------\n");
  d("ASOK_INT_JOYp %c\n", ASOK_INT_JOYp.c());
  d("AWOB_WAKE_CPU %c\n", AWOB_WAKE_CPU.c());
  d("CPU_PIN_WAKE  %c\n", CPU_PIN_WAKE .c()); 
  d("\n");

  d("BATU_JP_GLITCH0  %c\n", BATU_JP_GLITCH0  .c());
  d("ACEF_JP_GLITCH1  %c\n", ACEF_JP_GLITCH1  .c());
  d("AGEM_JP_GLITCH2  %c\n", AGEM_JP_GLITCH2  .c());
  d("APUG_JP_GLITCH3  %c\n", APUG_JP_GLITCH3  .c());
  d("JUTE_JOYP_RA     %c\n", JUTE_JOYP_RA     .c());
  d("KECY_JOYP_LB     %c\n", KECY_JOYP_LB     .c());
  d("JALE_JOYP_UC     %c\n", JALE_JOYP_UC     .c());
  d("KYME_JOYP_DS     %c\n", KYME_JOYP_DS     .c());
  d("KELY_JOYP_UDLR   %c\n", KELY_JOYP_UDLR   .c());
  d("COFY_JOYP_ABCS   %c\n", COFY_JOYP_ABCS   .c());
  d("KUKO_DBG_FF00_D6 %c\n", KUKO_DBG_FF00_D6 .c());
  d("KERU_DBG_FF00_D7 %c\n", KERU_DBG_FF00_D7 .c());
  d("KEVU_JOYP_L0     %c\n", KEVU_JOYP_L0     .c());
  d("KAPA_JOYP_L1     %c\n", KAPA_JOYP_L1     .c());
  d("KEJA_JOYP_L2     %c\n", KEJA_JOYP_L2     .c());
  d("KOLO_JOYP_L3     %c\n", KOLO_JOYP_L3     .c());
  d("\n");

  d("JOY_PIN_P10 %c\n", JOY_PIN_P10.c());
  d("JOY_PIN_P11 %c\n", JOY_PIN_P11.c());
  d("JOY_PIN_P12 %c\n", JOY_PIN_P12.c());
  d("JOY_PIN_P13 %c\n", JOY_PIN_P13.c());
  d("JOY_PIN_P14 %c\n", JOY_PIN_P14.c());
  d("JOY_PIN_P15 %c\n", JOY_PIN_P15.c());
  d("\n");
}

//-----------------------------------------------------------------------------

void Joypad::preset_buttons(uint8_t buttons) {
  // Pressing a button pulls the corresponding pin _down_.

  JOY_PIN_P10 = DELTA_TRIZ;
  JOY_PIN_P11 = DELTA_TRIZ;
  JOY_PIN_P12 = DELTA_TRIZ;
  JOY_PIN_P13 = DELTA_TRIZ;

  if (JOY_PIN_P14.qp()) {
    if (buttons & 0x01) JOY_PIN_P10 = DELTA_TRI0;
    if (buttons & 0x02) JOY_PIN_P11 = DELTA_TRI0;
    if (buttons & 0x04) JOY_PIN_P12 = DELTA_TRI0;
    if (buttons & 0x08) JOY_PIN_P13 = DELTA_TRI0;
  }

  if (JOY_PIN_P15.qp()) {
    if (buttons & 0x10) JOY_PIN_P10 = DELTA_TRI0;
    if (buttons & 0x20) JOY_PIN_P11 = DELTA_TRI0;
    if (buttons & 0x40) JOY_PIN_P12 = DELTA_TRI0;
    if (buttons & 0x80) JOY_PIN_P13 = DELTA_TRI0;
  }
}
//------------------------------------------------------------------------------

void Joypad::tick(const SchematicTop& /*top*/) {
  /*p02.ASOK*/ ASOK_INT_JOYp = and2(APUG_JP_GLITCH3.qp(), BATU_JP_GLITCH0.qp());
}

//------------------------------------------------------------------------------

void Joypad::tock(const SchematicTop& top, CpuBus& cpu_bus) {

  /*p10.AMUS*/ wire AMUS_XX_0xx00000 = nor6(top.cpu_bus.CPU_BUS_A00.tp(), top.cpu_bus.CPU_BUS_A01.tp(), top.cpu_bus.CPU_BUS_A02.tp(), top.cpu_bus.CPU_BUS_A03.tp(), top.cpu_bus.CPU_BUS_A04.tp(), top.cpu_bus.CPU_BUS_A07.tp());
  /*p10.ANAP*/ wire ANAP_FF_0xx00000 = and2(AMUS_XX_0xx00000, top.cpu_bus.SYKE_FF00_FFFFp());
  /*p10.AKUG*/ wire AKUG_A06n = not1(top.cpu_bus.CPU_BUS_A06.tp());
  /*p10.BYKO*/ wire BYKO_A05n = not1(top.cpu_bus.CPU_BUS_A05.tp());

  /*p02.KERY*/ wire KERY_ANY_BUTTONp = or4(JOY_PIN_P13.qn(), JOY_PIN_P12.qn(), JOY_PIN_P11.qn(), JOY_PIN_P10.qn());

  /*p01.BOGA*/ wire BOGA_xBCDEFGH = not1(top.clk_reg.BALY_Axxxxxxx);
  {
    /*p02.AWOB*/ AWOB_WAKE_CPU = tp_latch_A(BOGA_xBCDEFGH, KERY_ANY_BUTTONp);
    CPU_PIN_WAKE = AWOB_WAKE_CPU.tp();
  }

  {
    /*p02.BATU*/ BATU_JP_GLITCH0 = dff17_B(BOGA_xBCDEFGH, top.clk_reg.ALUR_SYS_RSTn, KERY_ANY_BUTTONp);
    /*p02.ACEF*/ ACEF_JP_GLITCH1 = dff17_B(BOGA_xBCDEFGH, top.clk_reg.ALUR_SYS_RSTn, BATU_JP_GLITCH0.qp());
    /*p02.AGEM*/ AGEM_JP_GLITCH2 = dff17_B(BOGA_xBCDEFGH, top.clk_reg.ALUR_SYS_RSTn, ACEF_JP_GLITCH1.qp());
    /*p02.APUG*/ APUG_JP_GLITCH3 = dff17_B(BOGA_xBCDEFGH, top.clk_reg.ALUR_SYS_RSTn, AGEM_JP_GLITCH2.qp());
  }

  {
    /*p10.ATOZ*/ wire ATOZ_FF00_WRn = nand4(top.TAPU_CPU_WRp_xxxxEFGx, ANAP_FF_0xx00000, AKUG_A06n, BYKO_A05n);
    /*p05.JUTE*/ JUTE_JOYP_RA     = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D0p.tp());
    /*p05.KECY*/ KECY_JOYP_LB     = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D1p.tp());
    /*p05.JALE*/ JALE_JOYP_UC     = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D2p.tp());
    /*p05.KYME*/ KYME_JOYP_DS     = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D3p.tp());
    /*p05.KELY*/ KELY_JOYP_UDLR   = dff17_A(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D4p.tp());
    /*p05.COFY*/ COFY_JOYP_ABCS   = dff17_A(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D5p.tp());
    /*p05.KUKO*/ KUKO_DBG_FF00_D6 = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D6p.tp());
    /*p05.KERU*/ KERU_DBG_FF00_D7 = dff17_B(ATOZ_FF00_WRn, top.clk_reg.ALUR_SYS_RSTn, top.cpu_bus.CPU_BUS_D7p.tp());

    /*p10.ACAT*/ wire ACAT_FF00_RDp = and4(top.TEDO_CPU_RDp, ANAP_FF_0xx00000, AKUG_A06n, BYKO_A05n);
    /*p05.BYZO*/ wire BYZO_FF00_RDn = not1(ACAT_FF00_RDp);
    /*p05.KEVU*/ KEVU_JOYP_L0 = tp_latch_A(BYZO_FF00_RDn, JOY_PIN_P10.qn());
    /*p05.KAPA*/ KAPA_JOYP_L1 = tp_latch_A(BYZO_FF00_RDn, JOY_PIN_P11.qn());
    /*p05.KEJA*/ KEJA_JOYP_L2 = tp_latch_A(BYZO_FF00_RDn, JOY_PIN_P12.qn());
    /*p05.KOLO*/ KOLO_JOYP_L3 = tp_latch_A(BYZO_FF00_RDn, JOY_PIN_P13.qn());

    // JOYP should read as 0xCF at reset? So the RegQPs reset to 1 and the RegQNs reset to 0?
    // That also means that _both_ P14 and P15 are selected at reset :/

    /*p05.KEMA*/ cpu_bus.CPU_BUS_D0p = tribuf_6nn(BYZO_FF00_RDn, KEVU_JOYP_L0.tp());
    /*p05.KURO*/ cpu_bus.CPU_BUS_D1p = tribuf_6nn(BYZO_FF00_RDn, KAPA_JOYP_L1.tp());
    /*p05.KUVE*/ cpu_bus.CPU_BUS_D2p = tribuf_6nn(BYZO_FF00_RDn, KEJA_JOYP_L2.tp());
    /*p05.JEKU*/ cpu_bus.CPU_BUS_D3p = tribuf_6nn(BYZO_FF00_RDn, KOLO_JOYP_L3.tp());
    /*p05.KOCE*/ cpu_bus.CPU_BUS_D4p = tribuf_6nn(BYZO_FF00_RDn, KELY_JOYP_UDLR.qn());
    /*p05.CUDY*/ cpu_bus.CPU_BUS_D5p = tribuf_6nn(BYZO_FF00_RDn, COFY_JOYP_ABCS.qn());
    /*p??.????*/ cpu_bus.CPU_BUS_D6p = tribuf_6nn(BYZO_FF00_RDn, KUKO_DBG_FF00_D6.qp());
    /*p??.????*/ cpu_bus.CPU_BUS_D7p = tribuf_6nn(BYZO_FF00_RDn, KERU_DBG_FF00_D7.qp());
  }

  {
    
#if 0
    // non-debug-mode

    JOY_PIN_P10 = io_pin(1, 0);
    JOY_PIN_P11 = io_pin(1, 0);
    JOY_PIN_P12 = io_pin(1, 0);
    JOY_PIN_P13 = io_pin(1, 0);

    JOY_PIN_P14 = io_pin(1, KELY_JOYP_UDLR.qn());
    JOY_PIN_P15 = io_pin(1, COFY_JOYP_ABCS.qn());
#endif

    wire BURO_FF60_0p = 0; // FIXME hacking out debug stuff
    /*p05.KURA*/ wire KURA = not1(BURO_FF60_0p);

    /*p05.KOLE*/ wire KOLE = nand2(JUTE_JOYP_RA.qp(), BURO_FF60_0p);
    /*p05.KYBU*/ wire KYBU = nor2 (JUTE_JOYP_RA.qp(), KURA);
    /*p05.KYTO*/ wire KYTO = nand2(KECY_JOYP_LB.qp(), BURO_FF60_0p);
    /*p05.KABU*/ wire KABU = nor2 (KECY_JOYP_LB.qp(), KURA);
    /*p05.KYHU*/ wire KYHU = nand2(JALE_JOYP_UC.qp(), BURO_FF60_0p);
    /*p05.KASY*/ wire KASY = nor2 (JALE_JOYP_UC.qp(), KURA);
    /*p05.KORY*/ wire KORY = nand2(KYME_JOYP_DS.qp(), BURO_FF60_0p);
    /*p05.KALE*/ wire KALE = nor2 (KYME_JOYP_DS.qp(), KURA);

    JOY_PIN_P10 = io_pin(KOLE, KYBU);
    JOY_PIN_P11 = io_pin(KYTO, KABU);
    JOY_PIN_P12 = io_pin(KYHU, KASY);
    JOY_PIN_P13 = io_pin(KORY, KALE);

    /*p05.KARU*/ wire KARU = or2(KELY_JOYP_UDLR.qn(), KURA);
    /*p05.CELA*/ wire CELA = or2(COFY_JOYP_ABCS.qn(), KURA);

    // FIXME inversion?
    // P14 and P15 are showing up as 0 on reset

    JOY_PIN_P14 = io_pin(KARU, !KELY_JOYP_UDLR.qn());
    JOY_PIN_P15 = io_pin(CELA, !COFY_JOYP_ABCS.qn());
  }
}

//------------------------------------------------------------------------------
