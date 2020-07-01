#pragma once
#include "Sch_Common.h"

namespace Schematics {

struct TestGB;

//-----------------------------------------------------------------------------

struct PixelPipeSignals {
  /*p35.REMY*/ Signal REMY_LD0n;
  /*p35.RAVO*/ Signal RAVO_LD1n;
};

//-----------------------------------------------------------------------------

struct PixelPipeRegisters {
  PixelPipeSignals sig(const TestGB& gb) const;
  void tick(TestGB& gb);
  bool commit();

private:

  /*p32.MYDE*/ Reg BG_PIPE_A0;
  /*p32.NOZO*/ Reg BG_PIPE_A1;
  /*p32.MOJU*/ Reg BG_PIPE_A2;
  /*p32.MACU*/ Reg BG_PIPE_A3;
  /*p32.NEPO*/ Reg BG_PIPE_A4;
  /*p32.MODU*/ Reg BG_PIPE_A5;
  /*p32.NEDA*/ Reg BG_PIPE_A6;
  /*p32.PYBO*/ Reg BG_PIPE_A7;

  /*p32.TOMY*/ Reg BG_PIPE_B0;
  /*p32.TACA*/ Reg BG_PIPE_B1;
  /*p32.SADY*/ Reg BG_PIPE_B2;
  /*p32.RYSA*/ Reg BG_PIPE_B3;
  /*p32.SOBO*/ Reg BG_PIPE_B4;
  /*p32.SETU*/ Reg BG_PIPE_B5;
  /*p32.RALU*/ Reg BG_PIPE_B6;
  /*p32.SOHU*/ Reg BG_PIPE_B7;

  /*p33.NURO*/ Reg SPR_PIPE_B0;
  /*p33.MASO*/ Reg SPR_PIPE_B1;
  /*p33.LEFE*/ Reg SPR_PIPE_B2;
  /*p33.LESU*/ Reg SPR_PIPE_B3;
  /*p33.WYHO*/ Reg SPR_PIPE_B4;
  /*p33.WORA*/ Reg SPR_PIPE_B5;
  /*p33.VAFO*/ Reg SPR_PIPE_B6;
  /*p33.WUFY*/ Reg SPR_PIPE_B7;

  /*p33.NYLU*/ Reg SPR_PIPE_A0;
  /*p33.PEFU*/ Reg SPR_PIPE_A1;
  /*p33.NATY*/ Reg SPR_PIPE_A2;
  /*p33.PYJO*/ Reg SPR_PIPE_A3;
  /*p33.VARE*/ Reg SPR_PIPE_A4;
  /*p33.WEBA*/ Reg SPR_PIPE_A5;
  /*p33.VANU*/ Reg SPR_PIPE_A6;
  /*p33.VUPY*/ Reg SPR_PIPE_A7;

  /*p34.RUGO*/ Reg PAL_PIPE_0;
  /*p34.SATA*/ Reg PAL_PIPE_1;
  /*p34.ROSA*/ Reg PAL_PIPE_2;
  /*p34.SOMY*/ Reg PAL_PIPE_3;
  /*p34.PALU*/ Reg PAL_PIPE_4;
  /*p34.NUKE*/ Reg PAL_PIPE_5;
  /*p34.MODA*/ Reg PAL_PIPE_6;
  /*p34.LYME*/ Reg PAL_PIPE_7;

  /*p26.VEZO*/ Reg MASK_PIPE_0;
  /*p26.WURU*/ Reg MASK_PIPE_1;
  /*p26.VOSA*/ Reg MASK_PIPE_2;
  /*p26.WYFU*/ Reg MASK_PIPE_3;
  /*p26.XETE*/ Reg MASK_PIPE_4;
  /*p26.WODA*/ Reg MASK_PIPE_5;
  /*p26.VUMO*/ Reg MASK_PIPE_6;
  /*p26.VAVA*/ Reg MASK_PIPE_7;

  // FF47 - BGP
  /*p36.PAVO*/ Reg BGP0;
  /*p36.NUSY*/ Reg BGP1;
  /*p36.PYLU*/ Reg BGP2;
  /*p36.MAXY*/ Reg BGP3;
  /*p36.MUKE*/ Reg BGP4;
  /*p36.MORU*/ Reg BGP5;
  /*p36.MOGY*/ Reg BGP6;
  /*p36.MENA*/ Reg BGP7;

  // FF48 - OBP0
  /*p36.XUFU*/ Reg OBP00;
  /*p36.XUKY*/ Reg OBP01;
  /*p36.XOVA*/ Reg OBP02;
  /*p36.XALO*/ Reg OBP03;
  /*p36.XERU*/ Reg OBP04;
  /*p36.XYZE*/ Reg OBP05;
  /*p36.XUPO*/ Reg OBP06;
  /*p36.XANA*/ Reg OBP07;

  // FF49 - OBP1
  /*p36.MOXY*/ Reg OBP10;
  /*p36.LAWO*/ Reg OBP11;
  /*p36.MOSA*/ Reg OBP12; // 9-rung, bottom rung is passthrough?
  /*p36.LOSE*/ Reg OBP13;
  /*p36.LUNE*/ Reg OBP14;
  /*p36.LUGU*/ Reg OBP15;
  /*p36.LEPU*/ Reg OBP16;
  /*p36.LUXO*/ Reg OBP17;
};

//-----------------------------------------------------------------------------

}; // namespace Schematics