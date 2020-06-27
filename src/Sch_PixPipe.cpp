#include "Sch_PixPipe.h"

#include "TestGB.h"

using namespace Schematics;

void PixelPipeRegisters::tick(TestGB& gb) {
  auto& ppu_reg = gb.ppu_reg;
  auto& joy_pin = gb.joy_pin;
  auto& cfg_reg = gb.cfg_reg;

  auto& vram_bus = gb.vram_bus;
  auto& cpu_bus = gb.cpu_bus;
  auto& oam_bus = gb.oam_bus;

  auto cpu_sig = gb.cpu_reg.sig(gb);
  auto adr_sig = gb.adr_reg.sig(gb.cpu_bus);
  auto clk_sig = gb.clk_reg.sig(gb);
  auto win_sig = gb.win_reg.sig(gb);
  auto dbg_sig = gb.dbg_reg.sig(gb);
  auto ppu_sig = gb.ppu_reg.sig(gb);
  auto sst_sig = gb.sst_reg.sig(gb);

  //----------------------------------------

  /*p27.LAXE*/ wire _LAXE_FETCH_S0n = not(ppu_reg.LAXU_BFETCH_S0.q());
  /*p27.MYSO*/ wire _MYSO_BG_TRIGn = nor(ppu_sig.LOBY_RENDERINGn, _LAXE_FETCH_S0n, ppu_reg.LYZU_BFETCH_S0_DELAY.q());

  //----------
  // PPU VRAM read

  // Background/window tile read B handler
  {
    // Clock polarity wrong? Check regs on die.

    // BFETCH_000 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_001 - LABU_BG_PIX_B_CLKp = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q())
    // BFETCH_010 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_011 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_100 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_101 - LABU_BG_PIX_B_CLKp = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q())

    /*p27.MOFU*/ wire _MOFU_CLKn = and (_MYSO_BG_TRIGn, ppu_sig.NAKO_FETCH_S1n);
    /*p32.LESO*/ wire _LESO_CLKp = not(_MOFU_CLKn);
    /*p32.AJAR*/ wire _AJAR_CLKn = not(_LESO_CLKp);
    /*p32.LABU*/ wire _LABU_CLKp = not(_AJAR_CLKn);

    /*p32.RAWU*/ BG_PIX_B0.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD0);
    /*p32.POZO*/ BG_PIX_B1.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD1);
    /*p32.PYZO*/ BG_PIX_B2.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD2);
    /*p32.POXA*/ BG_PIX_B3.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD3);
    /*p32.PULO*/ BG_PIX_B4.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD4);
    /*p32.POJU*/ BG_PIX_B5.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD5);
    /*p32.POWY*/ BG_PIX_B6.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD6);
    /*p32.PYJU*/ BG_PIX_B7.set(_LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TS_MD7);
  }

  // Sprite tile read handler
  {
    // SFETCH_000 - TOPU_SPRITE_PIX_LATCH_A = 0, 
    // SFETCH_001
    // SFETCH_010
    // SFETCH_011
    // SFETCH_100
    // SFETCH_101
    // SFETCH_110
    // SFETCH_111

    /*p29.SYCU*/ wire _SYCU = nor(ppu_sig.TYTU_SFETCH_S0_D0n, ppu_sig.LOBY_RENDERINGn, ppu_reg.TYFO_SFETCH_S0_D1);
    /*p29.TOPU*/ wire _TOPU_SPRITE_PIX_LATCH_A = and (ppu_reg.TULY_SFETCH_S1, _SYCU);
    /*p29.RACA*/ wire _RACA_SPRITE_PIX_LATCH_B = and (ppu_reg.VONU_SFETCH_S1_D4, _SYCU);

    /*p29.XONO*/ wire _XONO_FLIP_X = and (oam_bus.BAXO_SPRITE_X5, ppu_sig.TEXY_SPRITE_READp);
    /*p33.POBE*/ wire _SPR_PIX_FLIP0 = mux2_p(vram_bus.TS_MD7, vram_bus.TS_MD0, _XONO_FLIP_X);
    /*p33.PACY*/ wire _SPR_PIX_FLIP1 = mux2_p(vram_bus.TS_MD6, vram_bus.TS_MD1, _XONO_FLIP_X);
    /*p33.PONO*/ wire _SPR_PIX_FLIP2 = mux2_p(vram_bus.TS_MD5, vram_bus.TS_MD2, _XONO_FLIP_X);
    /*p33.PUGU*/ wire _SPR_PIX_FLIP3 = mux2_p(vram_bus.TS_MD4, vram_bus.TS_MD3, _XONO_FLIP_X);
    /*p33.PUTE*/ wire _SPR_PIX_FLIP4 = mux2_p(vram_bus.TS_MD3, vram_bus.TS_MD4, _XONO_FLIP_X);
    /*p33.PULY*/ wire _SPR_PIX_FLIP5 = mux2_p(vram_bus.TS_MD2, vram_bus.TS_MD5, _XONO_FLIP_X);
    /*p33.PELO*/ wire _SPR_PIX_FLIP6 = mux2_p(vram_bus.TS_MD1, vram_bus.TS_MD6, _XONO_FLIP_X);
    /*p33.PAWE*/ wire _SPR_PIX_FLIP7 = mux2_p(vram_bus.TS_MD0, vram_bus.TS_MD7, _XONO_FLIP_X);

    /*p29.VYWA*/ wire _VYWA_CLKp = not(_TOPU_SPRITE_PIX_LATCH_A);
    /*p29.WENY*/ wire _WENY_CLKn = not(_VYWA_CLKp);
    /*p29.XADO*/ wire _XADO_CLKp = not(_WENY_CLKn);

    /*p33.PEFO*/ SPR_PIX_A0.set(_XADO_CLKp, _SPR_PIX_FLIP0);
    /*p33.ROKA*/ SPR_PIX_A1.set(_XADO_CLKp, _SPR_PIX_FLIP1);
    /*p33.MYTU*/ SPR_PIX_A2.set(_XADO_CLKp, _SPR_PIX_FLIP2);
    /*p33.RAMU*/ SPR_PIX_A3.set(_XADO_CLKp, _SPR_PIX_FLIP3);
    /*p33.SELE*/ SPR_PIX_A4.set(_XADO_CLKp, _SPR_PIX_FLIP4);
    /*p33.SUTO*/ SPR_PIX_A5.set(_XADO_CLKp, _SPR_PIX_FLIP5);
    /*p33.RAMA*/ SPR_PIX_A6.set(_XADO_CLKp, _SPR_PIX_FLIP6);
    /*p33.RYDU*/ SPR_PIX_A7.set(_XADO_CLKp, _SPR_PIX_FLIP7);

    /*p29.PEBY*/ wire _PEBY_CLKp = not(_RACA_SPRITE_PIX_LATCH_B);
    /*p29.NYBE*/ wire _NYBE_CLKn = not(_PEBY_CLKp);
    /*p29.PUCO*/ wire _PUCO_CLKb = not(_NYBE_CLKn);

    /*p33.REWO*/ SPR_PIX_B0.set(_PUCO_CLKb, _SPR_PIX_FLIP0);
    /*p33.PEBA*/ SPR_PIX_B1.set(_PUCO_CLKb, _SPR_PIX_FLIP1);
    /*p33.MOFO*/ SPR_PIX_B2.set(_PUCO_CLKb, _SPR_PIX_FLIP2);
    /*p33.PUDU*/ SPR_PIX_B3.set(_PUCO_CLKb, _SPR_PIX_FLIP3);
    /*p33.SAJA*/ SPR_PIX_B4.set(_PUCO_CLKb, _SPR_PIX_FLIP4);
    /*p33.SUNY*/ SPR_PIX_B5.set(_PUCO_CLKb, _SPR_PIX_FLIP5);
    /*p33.SEMO*/ SPR_PIX_B6.set(_PUCO_CLKb, _SPR_PIX_FLIP6);
    /*p33.SEGA*/ SPR_PIX_B7.set(_PUCO_CLKb, _SPR_PIX_FLIP7);
  }


  // Background pipe A
  {
    // Hax

    // BFETCH_000 - LOMA_BG_LATCHn = 1;
    // BFETCH_001 - LOMA_BG_LATCHn = 1;
    // BFETCH_010 - LOMA_BG_LATCHn = 1;
    // BFETCH_011 - LOMA_BG_LATCHn = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q());
    // BFETCH_100 - LOMA_BG_LATCHn = 1;
    // BFETCH_101 - LOMA_BG_LATCHn = 1;

    // Original
    /*p27.NYDY*/ wire _NYDY_BG_LATCHn = nand(_MYSO_BG_TRIGn, ppu_reg.MESU_BFETCH_S1.q(), ppu_sig.NOFU_FETCH_S2n);
    /*p32.METE*/ wire _METE_BG_LATCHp = not(_NYDY_BG_LATCHn);
    /*p32.LOMA*/ wire _LOMA_BG_LATCHn = not(_METE_BG_LATCHp);

    // LEGU01 << LOMA02
    // LEGU02 << ????? could be TEME?
    // LEGU03 nc
    // LEGU04 << "comp clock"
    // LEGU05 nc
    // LEGU06 nc
    // LEGU07 >> LAKY02, LUHE01
    // LEGU08 nc

    // "comp clock" == not(LOMA02) - so it's just an inverted clock signal

    /*p32.LEGU*/ BG_PIX_A0.set(_LOMA_BG_LATCHn, vram_bus.TS_MD0);
    /*p32.NUDU*/ BG_PIX_A1.set(_LOMA_BG_LATCHn, vram_bus.TS_MD1);
    /*p32.MUKU*/ BG_PIX_A2.set(_LOMA_BG_LATCHn, vram_bus.TS_MD2);
    /*p32.LUZO*/ BG_PIX_A3.set(_LOMA_BG_LATCHn, vram_bus.TS_MD3);
    /*p32.MEGU*/ BG_PIX_A4.set(_LOMA_BG_LATCHn, vram_bus.TS_MD4);
    /*p32.MYJY*/ BG_PIX_A5.set(_LOMA_BG_LATCHn, vram_bus.TS_MD5);
    /*p32.NASA*/ BG_PIX_A6.set(_LOMA_BG_LATCHn, vram_bus.TS_MD6);
    /*p32.NEFO*/ BG_PIX_A7.set(_LOMA_BG_LATCHn, vram_bus.TS_MD7);

    /*p32.LOZE*/ wire _LOZE_PIPE_A_LOAD = not(ppu_sig.NYXU_BFETCH_RSTn);

    /*p32.LAKY*/ wire _BG_PIPE_A_SET0 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A0);
    /*p32.NYXO*/ wire _BG_PIPE_A_SET1 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A1);
    /*p32.LOTO*/ wire _BG_PIPE_A_SET2 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A2);
    /*p32.LYDU*/ wire _BG_PIPE_A_SET3 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A3);
    /*p32.MYVY*/ wire _BG_PIPE_A_SET4 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A4);
    /*p32.LODO*/ wire _BG_PIPE_A_SET5 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A5);
    /*p32.NUTE*/ wire _BG_PIPE_A_SET6 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A6);
    /*p32.NAJA*/ wire _BG_PIPE_A_SET7 = nand(_LOZE_PIPE_A_LOAD, BG_PIX_A7);

    /*p32.LUHE*/ wire _BG_PIX_A0n = not(BG_PIX_A0);
    /*p32.NOLY*/ wire _BG_PIX_A1n = not(BG_PIX_A1);
    /*p32.LEKE*/ wire _BG_PIX_A2n = not(BG_PIX_A2);
    /*p32.LOMY*/ wire _BG_PIX_A3n = not(BG_PIX_A3);
    /*p32.LALA*/ wire _BG_PIX_A4n = not(BG_PIX_A4);
    /*p32.LOXA*/ wire _BG_PIX_A5n = not(BG_PIX_A5);
    /*p32.NEZE*/ wire _BG_PIX_A6n = not(BG_PIX_A6);
    /*p32.NOBO*/ wire _BG_PIX_A7n = not(BG_PIX_A7);

    /*p32.LOTY*/ wire _BG_PIPE_A_RST0 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A0n);
    /*p32.NEXA*/ wire _BG_PIPE_A_RST1 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A1n);
    /*p32.LUTU*/ wire _BG_PIPE_A_RST2 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A2n);
    /*p32.LUJA*/ wire _BG_PIPE_A_RST3 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A3n);
    /*p32.MOSY*/ wire _BG_PIPE_A_RST4 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A4n);
    /*p32.LERU*/ wire _BG_PIPE_A_RST5 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A5n);
    /*p32.NYHA*/ wire _BG_PIPE_A_RST6 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A6n);
    /*p32.NADY*/ wire _BG_PIPE_A_RST7 = nand(_LOZE_PIPE_A_LOAD, _BG_PIX_A7n);

    /*p32.MYDE*/ BG_PIPE_A0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET0, _BG_PIPE_A_RST0, joy_pin.P10_B);
    /*p32.NOZO*/ BG_PIPE_A1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET1, _BG_PIPE_A_RST1, BG_PIPE_A0);
    /*p32.MOJU*/ BG_PIPE_A2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET2, _BG_PIPE_A_RST2, BG_PIPE_A1);
    /*p32.MACU*/ BG_PIPE_A3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET3, _BG_PIPE_A_RST3, BG_PIPE_A2);
    /*p32.NEPO*/ BG_PIPE_A4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET4, _BG_PIPE_A_RST4, BG_PIPE_A3);
    /*p32.MODU*/ BG_PIPE_A5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET5, _BG_PIPE_A_RST5, BG_PIPE_A4);
    /*p32.NEDA*/ BG_PIPE_A6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET6, _BG_PIPE_A_RST6, BG_PIPE_A5);
    /*p32.PYBO*/ BG_PIPE_A7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_A_SET7, _BG_PIPE_A_RST7, BG_PIPE_A6);
  }

  // Background pipe B
  {
    /*p32.LUXA*/ wire _LUXA_PIPE_B_LOAD = not(ppu_sig.NYXU_BFETCH_RSTn);
    /*p32.TUXE*/ wire _BG_PIPE_B_SET0 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B0);
    /*p32.SOLY*/ wire _BG_PIPE_B_SET1 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B1);
    /*p32.RUCE*/ wire _BG_PIPE_B_SET2 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B2);
    /*p32.RYJA*/ wire _BG_PIPE_B_SET3 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B3);
    /*p32.RUTO*/ wire _BG_PIPE_B_SET4 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B4);
    /*p32.RAJA*/ wire _BG_PIPE_B_SET5 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B5);
    /*p32.RAJO*/ wire _BG_PIPE_B_SET6 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B6);
    /*p32.RAGA*/ wire _BG_PIPE_B_SET7 = nand(_LUXA_PIPE_B_LOAD, !BG_PIX_B7);

    /*p32.SEJA*/ wire _BG_PIPE_B_RST0 = nand(_LUXA_PIPE_B_LOAD, /*p32.TOSA*/ not(!BG_PIX_B0));
    /*p32.SENO*/ wire _BG_PIPE_B_RST1 = nand(_LUXA_PIPE_B_LOAD, /*p32.RUCO*/ not(!BG_PIX_B1));
    /*p32.SURE*/ wire _BG_PIPE_B_RST2 = nand(_LUXA_PIPE_B_LOAD, /*p32.TYCE*/ not(!BG_PIX_B2));
    /*p32.SEBO*/ wire _BG_PIPE_B_RST3 = nand(_LUXA_PIPE_B_LOAD, /*p32.REVY*/ not(!BG_PIX_B3));
    /*p32.SUCA*/ wire _BG_PIPE_B_RST4 = nand(_LUXA_PIPE_B_LOAD, /*p32.RYGA*/ not(!BG_PIX_B4));
    /*p32.SYWE*/ wire _BG_PIPE_B_RST5 = nand(_LUXA_PIPE_B_LOAD, /*p32.RYLE*/ not(!BG_PIX_B5));
    /*p32.SUPU*/ wire _BG_PIPE_B_RST6 = nand(_LUXA_PIPE_B_LOAD, /*p32.RAPU*/ not(!BG_PIX_B6));
    /*p32.RYJY*/ wire _BG_PIPE_B_RST7 = nand(_LUXA_PIPE_B_LOAD, /*p32.SOJA*/ not(!BG_PIX_B7));

    /*p32.TOMY*/ BG_PIPE_B0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET0, _BG_PIPE_B_RST0, joy_pin.P10_B);
    /*p32.TACA*/ BG_PIPE_B1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET1, _BG_PIPE_B_RST1, BG_PIPE_B0);
    /*p32.SADY*/ BG_PIPE_B2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET2, _BG_PIPE_B_RST2, BG_PIPE_B1);
    /*p32.RYSA*/ BG_PIPE_B3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET3, _BG_PIPE_B_RST3, BG_PIPE_B2);
    /*p32.SOBO*/ BG_PIPE_B4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET4, _BG_PIPE_B_RST4, BG_PIPE_B3);
    /*p32.SETU*/ BG_PIPE_B5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET5, _BG_PIPE_B_RST5, BG_PIPE_B4);
    /*p32.RALU*/ BG_PIPE_B6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET6, _BG_PIPE_B_RST6, BG_PIPE_B5);
    /*p32.SOHU*/ BG_PIPE_B7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _BG_PIPE_B_SET7, _BG_PIPE_B_RST7, BG_PIPE_B6);
  }

  {
    /*p29.XEFY*/ wire _XEPY_SPRITE_DONEn = not(ppu_sig.WUTY_SPRITE_DONE);
    /*p34.MEFU*/ wire _SPRITE_MASK0 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A0, SPR_PIPE_B0);
    /*p34.MEVE*/ wire _SPRITE_MASK1 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A1, SPR_PIPE_B1);
    /*p34.MYZO*/ wire _SPRITE_MASK2 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A2, SPR_PIPE_B2);
    /*p34.RUDA*/ wire _SPRITE_MASK3 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A3, SPR_PIPE_B3);
    /*p34.VOTO*/ wire _SPRITE_MASK4 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A4, SPR_PIPE_B4);
    /*p34.VYSA*/ wire _SPRITE_MASK5 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A5, SPR_PIPE_B5);
    /*p34.TORY*/ wire _SPRITE_MASK6 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A6, SPR_PIPE_B6);
    /*p34.WOPE*/ wire _SPRITE_MASK7 = or(_XEPY_SPRITE_DONEn, SPR_PIPE_A7, SPR_PIPE_B7);

    /*p34.LESY*/ wire _SPRITE_MASK0n = not(_SPRITE_MASK0);
    /*p34.LOTA*/ wire _SPRITE_MASK1n = not(_SPRITE_MASK1);
    /*p34.LYKU*/ wire _SPRITE_MASK2n = not(_SPRITE_MASK2);
    /*p34.ROBY*/ wire _SPRITE_MASK3n = not(_SPRITE_MASK3);
    /*p34.TYTA*/ wire _SPRITE_MASK4n = not(_SPRITE_MASK4);
    /*p34.TYCO*/ wire _SPRITE_MASK5n = not(_SPRITE_MASK5);
    /*p34.SOKA*/ wire _SPRITE_MASK6n = not(_SPRITE_MASK6);
    /*p34.XOVU*/ wire _SPRITE_MASK7n = not(_SPRITE_MASK7);

    // Sprite pipe A
    {
      /*p33.MEZU*/ wire _SPR_PIX_A_SET0 = nand(_SPRITE_MASK0n, SPR_PIX_A0);
      /*p33.RUSY*/ wire _SPR_PIX_A_SET1 = nand(_SPRITE_MASK1n, SPR_PIX_A1);
      /*p33.MYXA*/ wire _SPR_PIX_A_SET2 = nand(_SPRITE_MASK2n, SPR_PIX_A2);
      /*p33.RANO*/ wire _SPR_PIX_A_SET3 = nand(_SPRITE_MASK3n, SPR_PIX_A3);
      /*p33.TYGA*/ wire _SPR_PIX_A_SET4 = nand(_SPRITE_MASK4n, SPR_PIX_A4);
      /*p33.VUME*/ wire _SPR_PIX_A_SET5 = nand(_SPRITE_MASK5n, SPR_PIX_A5);
      /*p33.TAPO*/ wire _SPR_PIX_A_SET6 = nand(_SPRITE_MASK6n, SPR_PIX_A6);
      /*p33.TESO*/ wire _SPR_PIX_A_SET7 = nand(_SPRITE_MASK7n, SPR_PIX_A7);

      /*p33.MOFY*/ wire _SPR_PIX_A_RST0 = nand(_SPRITE_MASK0n, /*p33.LOZA*/ not(SPR_PIX_A0));
      /*p33.RUCA*/ wire _SPR_PIX_A_RST1 = nand(_SPRITE_MASK1n, /*p33.SYBO*/ not(SPR_PIX_A1));
      /*p33.MAJO*/ wire _SPR_PIX_A_RST2 = nand(_SPRITE_MASK2n, /*p33.LUMO*/ not(SPR_PIX_A2));
      /*p33.REHU*/ wire _SPR_PIX_A_RST3 = nand(_SPRITE_MASK3n, /*p33.SOLO*/ not(SPR_PIX_A3));
      /*p33.WAXO*/ wire _SPR_PIX_A_RST4 = nand(_SPRITE_MASK4n, /*p33.VOBY*/ not(SPR_PIX_A4));
      /*p33.XOLE*/ wire _SPR_PIX_A_RST5 = nand(_SPRITE_MASK5n, /*p33.WYCO*/ not(SPR_PIX_A5));
      /*p33.TABY*/ wire _SPR_PIX_A_RST6 = nand(_SPRITE_MASK6n, /*p33.SERY*/ not(SPR_PIX_A6));
      /*p33.TULA*/ wire _SPR_PIX_A_RST7 = nand(_SPRITE_MASK7n, /*p33.SELU*/ not(SPR_PIX_A7));

      /*p33.NYLU*/ SPR_PIPE_A0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET0, _SPR_PIX_A_RST0, joy_pin.P10_B);
      /*p33.PEFU*/ SPR_PIPE_A1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET1, _SPR_PIX_A_RST1, SPR_PIPE_A0);
      /*p33.NATY*/ SPR_PIPE_A2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET2, _SPR_PIX_A_RST2, SPR_PIPE_A1);
      /*p33.PYJO*/ SPR_PIPE_A3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET3, _SPR_PIX_A_RST3, SPR_PIPE_A2);
      /*p33.VARE*/ SPR_PIPE_A4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET4, _SPR_PIX_A_RST4, SPR_PIPE_A3);
      /*p33.WEBA*/ SPR_PIPE_A5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET5, _SPR_PIX_A_RST5, SPR_PIPE_A4);
      /*p33.VANU*/ SPR_PIPE_A6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET6, _SPR_PIX_A_RST6, SPR_PIPE_A5);
      /*p33.VUPY*/ SPR_PIPE_A7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_A_SET7, _SPR_PIX_A_RST7, SPR_PIPE_A6);
    }

    // Sprite pipe B
    {
      /*p33.PABE*/ wire _SPR_PIX_B_SET0 = nand(_SPRITE_MASK0n, SPR_PIX_B0);
      /*p33.MYTO*/ wire _SPR_PIX_B_SET1 = nand(_SPRITE_MASK1n, SPR_PIX_B1);
      /*p33.LELA*/ wire _SPR_PIX_B_SET2 = nand(_SPRITE_MASK2n, SPR_PIX_B2);
      /*p33.MAME*/ wire _SPR_PIX_B_SET3 = nand(_SPRITE_MASK3n, SPR_PIX_B3);
      /*p33.VEXU*/ wire _SPR_PIX_B_SET4 = nand(_SPRITE_MASK4n, SPR_PIX_B4);
      /*p33.VABY*/ wire _SPR_PIX_B_SET5 = nand(_SPRITE_MASK5n, SPR_PIX_B5);
      /*p33.TUXA*/ wire _SPR_PIX_B_SET6 = nand(_SPRITE_MASK6n, SPR_PIX_B6);
      /*p33.VUNE*/ wire _SPR_PIX_B_SET7 = nand(_SPRITE_MASK7n, SPR_PIX_B7);

      /*p33.PYZU*/ wire _SPR_PIX_B_RST0 = nand(_SPRITE_MASK0n, /*p33.RATA*/ not(SPR_PIX_B0));
      /*p33.MADA*/ wire _SPR_PIX_B_RST1 = nand(_SPRITE_MASK1n, /*p33.NUCA*/ not(SPR_PIX_B1));
      /*p33.LYDE*/ wire _SPR_PIX_B_RST2 = nand(_SPRITE_MASK2n, /*p33.LASE*/ not(SPR_PIX_B2));
      /*p33.LUFY*/ wire _SPR_PIX_B_RST3 = nand(_SPRITE_MASK3n, /*p33.LUBO*/ not(SPR_PIX_B3));
      /*p33.XATO*/ wire _SPR_PIX_B_RST4 = nand(_SPRITE_MASK4n, /*p33.WERY*/ not(SPR_PIX_B4));
      /*p33.XEXU*/ wire _SPR_PIX_B_RST5 = nand(_SPRITE_MASK5n, /*p33.WURA*/ not(SPR_PIX_B5));
      /*p33.TUPE*/ wire _SPR_PIX_B_RST6 = nand(_SPRITE_MASK6n, /*p33.SULU*/ not(SPR_PIX_B6));
      /*p33.XYVE*/ wire _SPR_PIX_B_RST7 = nand(_SPRITE_MASK7n, /*p33.WAMY*/ not(SPR_PIX_B7));

      /*p33.NURO*/ SPR_PIPE_B0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET0, _SPR_PIX_B_RST0, joy_pin.P10_B);
      /*p33.MASO*/ SPR_PIPE_B1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET1, _SPR_PIX_B_RST1, SPR_PIPE_B0);
      /*p33.LEFE*/ SPR_PIPE_B2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET2, _SPR_PIX_B_RST2, SPR_PIPE_B1);
      /*p33.LESU*/ SPR_PIPE_B3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET3, _SPR_PIX_B_RST3, SPR_PIPE_B2);
      /*p33.WYHO*/ SPR_PIPE_B4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET4, _SPR_PIX_B_RST4, SPR_PIPE_B3);
      /*p33.WORA*/ SPR_PIPE_B5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET5, _SPR_PIX_B_RST5, SPR_PIPE_B4);
      /*p33.VAFO*/ SPR_PIPE_B6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET6, _SPR_PIX_B_RST6, SPR_PIPE_B5);
      /*p33.WUFY*/ SPR_PIPE_B7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPR_PIX_B_SET7, _SPR_PIX_B_RST7, SPR_PIPE_B6);
    }

    // Palette pipe
    {
      /*p34.PUME*/ wire _SPRITE_PAL_PIPE_SET0n = nand(_SPRITE_MASK0n, oam_bus.GOMO_SPRITE_X4);
      /*p34.SORO*/ wire _SPRITE_PAL_PIPE_SET1n = nand(_SPRITE_MASK1n, oam_bus.GOMO_SPRITE_X4);
      /*p34.PAMO*/ wire _SPRITE_PAL_PIPE_SET2n = nand(_SPRITE_MASK2n, oam_bus.GOMO_SPRITE_X4);
      /*p34.SUKY*/ wire _SPRITE_PAL_PIPE_SET3n = nand(_SPRITE_MASK3n, oam_bus.GOMO_SPRITE_X4);
      /*p34.RORA*/ wire _SPRITE_PAL_PIPE_SET4n = nand(_SPRITE_MASK4n, oam_bus.GOMO_SPRITE_X4);
      /*p34.MENE*/ wire _SPRITE_PAL_PIPE_SET5n = nand(_SPRITE_MASK5n, oam_bus.GOMO_SPRITE_X4);
      /*p34.LUKE*/ wire _SPRITE_PAL_PIPE_SET6n = nand(_SPRITE_MASK6n, oam_bus.GOMO_SPRITE_X4);
      /*p34.LAMY*/ wire _SPRITE_PAL_PIPE_SET7n = nand(_SPRITE_MASK7n, oam_bus.GOMO_SPRITE_X4);

      /*p34.SUCO*/ wire _SPRITE_PAL_PIPE_RST0n = nand(_SPRITE_MASK0n, /*p34.SYPY*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.TAFA*/ wire _SPRITE_PAL_PIPE_RST1n = nand(_SPRITE_MASK1n, /*p34.TOTU*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.PYZY*/ wire _SPRITE_PAL_PIPE_RST2n = nand(_SPRITE_MASK2n, /*p34.NARO*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.TOWA*/ wire _SPRITE_PAL_PIPE_RST3n = nand(_SPRITE_MASK3n, /*p34.WEXY*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.RUDU*/ wire _SPRITE_PAL_PIPE_RST4n = nand(_SPRITE_MASK4n, /*p34.RYZY*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.PAZO*/ wire _SPRITE_PAL_PIPE_RST5n = nand(_SPRITE_MASK5n, /*p34.RYFE*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.LOWA*/ wire _SPRITE_PAL_PIPE_RST6n = nand(_SPRITE_MASK6n, /*p34.LADY*/ not(oam_bus.GOMO_SPRITE_X4));
      /*p34.LUNU*/ wire _SPRITE_PAL_PIPE_RST7n = nand(_SPRITE_MASK7n, /*p34.LAFY*/ not(oam_bus.GOMO_SPRITE_X4));

      /*p34.RUGO*/ PAL_PIPE_0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET0n, _SPRITE_PAL_PIPE_RST0n, joy_pin.P10_B);
      /*p34.SATA*/ PAL_PIPE_1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET1n, _SPRITE_PAL_PIPE_RST1n, PAL_PIPE_0);
      /*p34.ROSA*/ PAL_PIPE_2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET2n, _SPRITE_PAL_PIPE_RST2n, PAL_PIPE_1);
      /*p34.SOMY*/ PAL_PIPE_3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET3n, _SPRITE_PAL_PIPE_RST3n, PAL_PIPE_2);
      /*p34.PALU*/ PAL_PIPE_4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET4n, _SPRITE_PAL_PIPE_RST4n, PAL_PIPE_3);
      /*p34.NUKE*/ PAL_PIPE_5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET5n, _SPRITE_PAL_PIPE_RST5n, PAL_PIPE_4);
      /*p34.MODA*/ PAL_PIPE_6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET6n, _SPRITE_PAL_PIPE_RST6n, PAL_PIPE_5);
      /*p34.LYME*/ PAL_PIPE_7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _SPRITE_PAL_PIPE_SET7n, _SPRITE_PAL_PIPE_RST7n, PAL_PIPE_6);
    }

    // Background mask pipe
    {
      /*p26.TEDE*/ wire _MASK_PIPE_SET0 = nand(_SPRITE_MASK0n, oam_bus.DEPO_SPRITE_X7);
      /*p26.XALA*/ wire _MASK_PIPE_SET1 = nand(_SPRITE_MASK1n, oam_bus.DEPO_SPRITE_X7);
      /*p26.TYRA*/ wire _MASK_PIPE_SET2 = nand(_SPRITE_MASK2n, oam_bus.DEPO_SPRITE_X7);
      /*p26.XYRU*/ wire _MASK_PIPE_SET3 = nand(_SPRITE_MASK3n, oam_bus.DEPO_SPRITE_X7);
      /*p26.XUKU*/ wire _MASK_PIPE_SET4 = nand(_SPRITE_MASK4n, oam_bus.DEPO_SPRITE_X7);
      /*p26.XELY*/ wire _MASK_PIPE_SET5 = nand(_SPRITE_MASK5n, oam_bus.DEPO_SPRITE_X7);
      /*p26.TYKO*/ wire _MASK_PIPE_SET6 = nand(_SPRITE_MASK6n, oam_bus.DEPO_SPRITE_X7);
      /*p26.TUWU*/ wire _MASK_PIPE_SET7 = nand(_SPRITE_MASK7n, oam_bus.DEPO_SPRITE_X7);

      /*p26.WOKA*/ wire _MASK_PIPE_RST0 = nand(_SPRITE_MASK0n, /*p26.XOGA*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.WEDE*/ wire _MASK_PIPE_RST1 = nand(_SPRITE_MASK1n, /*p26.XURA*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.TUFO*/ wire _MASK_PIPE_RST2 = nand(_SPRITE_MASK2n, /*p26.TAJO*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.WEVO*/ wire _MASK_PIPE_RST3 = nand(_SPRITE_MASK3n, /*p26.XENU*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.WEDY*/ wire _MASK_PIPE_RST4 = nand(_SPRITE_MASK4n, /*p26.XYKE*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.WUJA*/ wire _MASK_PIPE_RST5 = nand(_SPRITE_MASK5n, /*p26.XABA*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.TENA*/ wire _MASK_PIPE_RST6 = nand(_SPRITE_MASK6n, /*p26.TAFU*/ not(oam_bus.DEPO_SPRITE_X7));
      /*p26.WUBU*/ wire _MASK_PIPE_RST7 = nand(_SPRITE_MASK7n, /*p26.XUHO*/ not(oam_bus.DEPO_SPRITE_X7));

      /*p26.VEZO*/ MASK_PIPE_0.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET0, _MASK_PIPE_RST0, joy_pin.P10_B);
      /*p26.WURU*/ MASK_PIPE_1.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET1, _MASK_PIPE_RST1, MASK_PIPE_0);
      /*p26.VOSA*/ MASK_PIPE_2.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET2, _MASK_PIPE_RST2, MASK_PIPE_1);
      /*p26.WYFU*/ MASK_PIPE_3.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET3, _MASK_PIPE_RST3, MASK_PIPE_2);
      /*p26.XETE*/ MASK_PIPE_4.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET4, _MASK_PIPE_RST4, MASK_PIPE_3);
      /*p26.WODA*/ MASK_PIPE_5.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET5, _MASK_PIPE_RST5, MASK_PIPE_4);
      /*p26.VUMO*/ MASK_PIPE_6.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET6, _MASK_PIPE_RST6, MASK_PIPE_5);
      /*p26.VAVA*/ MASK_PIPE_7.set(ppu_sig.SACU_CLKPIPE_AxCxExGx, _MASK_PIPE_SET7, _MASK_PIPE_RST7, MASK_PIPE_6);
    }
  }

  //----------
  // Pixel merge, this is _all_ combi logic. :/
  
  {
    /*p35.RAJY*/ wire _PIX_BG0  = and(cfg_reg.VYXE_LCDC_BGEN, BG_PIPE_A7);
    /*p35.TADE*/ wire _PIX_BG1  = and(cfg_reg.VYXE_LCDC_BGEN, BG_PIPE_B7);

    /*p35.WOXA*/ wire _PIX_SP0  = and(cfg_reg.XYLO_LCDC_SPEN, SPR_PIPE_A7);
    /*p35.XULA*/ wire _PIX_SP1  = and(cfg_reg.XYLO_LCDC_SPEN, SPR_PIPE_B7);

    /*p35.NULY*/ wire _PIX_SPn  = nor(_PIX_SP0, _PIX_SP1);

    /*p35.RYFU*/ wire _MASK_BG0 = and(_PIX_BG0, MASK_PIPE_7);
    /*p35.RUTA*/ wire _MASK_BG1 = and(_PIX_BG1, MASK_PIPE_7);
    /*p35.POKA*/ wire _BGPIXELn = nor(_PIX_SPn, _MASK_BG0, _MASK_BG1);

    /*p34.LOME*/ wire _SPRITE_PAL_PIPE_7n = not(PAL_PIPE_7);
    /*p34.LAFU*/ wire _OBP0PIXELn = nand(_SPRITE_PAL_PIPE_7n, _BGPIXELn);
    /*p34.LEKA*/ wire _OBP1PIXELn = nand(_SPRITE_PAL_PIPE_7n, _BGPIXELn);

    //----------
    // Sprite palette 0 lookup

    /*p35.VUMU*/ wire _PIX_SP0n = not(_PIX_SP0);
    /*p35.WYRU*/ wire _PIX_SP0a = not(_PIX_SP0n);
    /*p35.WELE*/ wire _PIX_SP1n = not(_PIX_SP1);
    /*p35.WOLO*/ wire _PIX_SP1a = not(_PIX_SP1n);

    /*p35.LAVA*/ wire _MASK_OPB0  = not(_OBP0PIXELn);
    /*p35.VYRO*/ wire _PAL_OBP0D = and(_PIX_SP0a, _PIX_SP1a, _MASK_OPB0);
    /*p35.VATA*/ wire _PAL_OBP0C = and(_PIX_SP0a, _PIX_SP1n, _MASK_OPB0);
    /*p35.VOLO*/ wire _PAL_OBP0B = and(_PIX_SP0n, _PIX_SP1a, _MASK_OPB0);
    /*p35.VUGO*/ wire _PAL_OBP0A = and(_PIX_SP0n, _PIX_SP1n, _MASK_OPB0);
    

    /*p35.WUFU*/ wire _COL_OBP00 = amux4(cfg_reg.OBP07, _PAL_OBP0D,
                                         cfg_reg.OBP05, _PAL_OBP0C,
                                         cfg_reg.OBP03, _PAL_OBP0B,
                                         cfg_reg.OBP01, _PAL_OBP0A);

    /*p35.WALY*/ wire _COL_OBP01 = amux4(cfg_reg.OBP06, _PAL_OBP0D,
                                         cfg_reg.OBP04, _PAL_OBP0C,
                                         cfg_reg.OBP02, _PAL_OBP0B,
                                         cfg_reg.OBP00, _PAL_OBP0A);

    //----------
    // Sprite palette 1 lookup

    /*p35.MEXA*/ wire _PIX_SP0o = not(_PIX_SP0);
    /*p35.LOZO*/ wire _PIX_SP0b = not(_PIX_SP0o);
    /*p35.MABY*/ wire _PIX_SP1o = not(_PIX_SP1);
    /*p35.LYLE*/ wire _PIX_SP1b = not(_PIX_SP1o);

    /*p35.LUKU*/ wire _MASK_OBP1  = not(_OBP1PIXELn);
    /*p35.LEDO*/ wire _PAL_OBP1D = and(_PIX_SP1b, _PIX_SP0b, _MASK_OBP1);
    /*p35.LYKY*/ wire _PAL_OBP1C = and(_PIX_SP1b, _PIX_SP0o, _MASK_OBP1);
    /*p35.LARU*/ wire _PAL_OBP1B = and(_PIX_SP1o, _PIX_SP0b, _MASK_OBP1);
    /*p35.LOPU*/ wire _PAL_OBP1A = and(_PIX_SP1o, _PIX_SP0o, _MASK_OBP1);

    /*p35.MOKA*/ wire _COL_OBP10 = amux4(cfg_reg.OBP17, _PAL_OBP1D,
                                         cfg_reg.OBP15, _PAL_OBP1C,
                                         cfg_reg.OBP13, _PAL_OBP1B,
                                         cfg_reg.OBP11, _PAL_OBP1A);

    /*p35.MUFA*/ wire _COL_OBP11 = amux4(cfg_reg.OBP16, _PAL_OBP1D,
                                         cfg_reg.OBP14, _PAL_OBP1C,
                                         cfg_reg.OBP12, _PAL_OBP1B,
                                         cfg_reg.OBP10, _PAL_OBP1A);

    //----------
    // Background/window palette lookup

    /*p35.SOBA*/ wire _PIX_BG0n = not(_PIX_BG0);
    /*p35.VYCO*/ wire _PIX_BG1n = not(_PIX_BG1);
    /*p35.NUPO*/ wire _PIX_BG0a = not(_PIX_BG0n);
    /*p35.NALE*/ wire _PIX_BG1a = not(_PIX_BG1n);

    /*p35.MUVE*/ wire _MASK_BGP = not(_BGPIXELn);
    /*p35.POBU*/ wire _PAL_BGPA = and(_PIX_BG1n, _PIX_BG0n, _MASK_BGP);
    /*p35.NUMA*/ wire _PAL_BGPB = and(_PIX_BG1a, _PIX_BG0n, _MASK_BGP);
    /*p35.NUXO*/ wire _PAL_BGPC = and(_PIX_BG1n, _PIX_BG0a, _MASK_BGP);
    /*p35.NYPO*/ wire _PAL_BGPD = and(_PIX_BG1a, _PIX_BG0a, _MASK_BGP);

    /*p35.NURA*/ wire _COL_BGP1 = amux4(cfg_reg.BGP7, _PAL_BGPD,
                                         cfg_reg.BGP5, _PAL_BGPC,
                                         cfg_reg.BGP3, _PAL_BGPB,
                                         cfg_reg.BGP1, _PAL_BGPA);

    /*p35.NELO*/ wire _COL_BGP0 = amux4(cfg_reg.BGP6, _PAL_BGPD,
                                         cfg_reg.BGP4, _PAL_BGPC,
                                         cfg_reg.BGP2, _PAL_BGPB,
                                         cfg_reg.BGP0, _PAL_BGPA);

    //----------
    // Pixel merge and send

    // bits 0 and 1 swapped somewhere...

    /*p35.PATY*/ wire PATY_PIX_OUT_LO = or(_COL_BGP1, _COL_OBP00, _COL_OBP10);
    /*p35.PERO*/ wire PERO_PIX_OUT_HI = or(_COL_BGP0, _COL_OBP01, _COL_OBP11);
    /*p35.REMY*/ wire _REMY_LD0n = not(PATY_PIX_OUT_LO);
    /*p35.RAVO*/ wire _RAVO_LD1n = not(PERO_PIX_OUT_HI);

    LD0.set(not(_REMY_LD0n));
    LD1.set(not(_RAVO_LD1n));
  }

  // FF47
  {
    /*p22.WYBO*/ wire FF47n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.WADO_A00, adr_sig.WESA_A01, adr_sig.WALO_A02, adr_sig.XERA_A03n);
    /*p22.WERA*/ wire FF47 = not(FF47n);
    /*p36.VELY*/ wire FF47_WR = and (cpu_sig.CUPA_CPU_WR_xxxxxFGH, FF47);
    /*p36.TEPO*/ wire FF47_WRn = not(FF47_WR);

    /*p36.PAVO*/ cfg_reg.BGP0.set(FF47_WRn, 1, cpu_bus.TS_D0);
    /*p36.NUSY*/ cfg_reg.BGP1.set(FF47_WRn, 1, cpu_bus.TS_D1);
    /*p36.PYLU*/ cfg_reg.BGP2.set(FF47_WRn, 1, cpu_bus.TS_D2);
    /*p36.MAXY*/ cfg_reg.BGP3.set(FF47_WRn, 1, cpu_bus.TS_D3);
    /*p36.MUKE*/ cfg_reg.BGP4.set(FF47_WRn, 1, cpu_bus.TS_D4);
    /*p36.MORU*/ cfg_reg.BGP5.set(FF47_WRn, 1, cpu_bus.TS_D5);
    /*p36.MOGY*/ cfg_reg.BGP6.set(FF47_WRn, 1, cpu_bus.TS_D6);
    /*p36.MENA*/ cfg_reg.BGP7.set(FF47_WRn, 1, cpu_bus.TS_D7);
  }

  // FF48
  {
    /*p22.WETA*/ wire FF48n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.XOLA_A00n, adr_sig.XENO_A01n, adr_sig.XUSY_A02n, adr_sig.WEPO_A03);
    /*p22.XAYO*/ wire FF48 = not(FF48n);
    /*p36.XOMA*/ wire FF48_WR = and (cpu_sig.CUPA_CPU_WR_xxxxxFGH, FF48);
    /*p36.XELO*/ wire FF48_WRn = not(FF48_WR);

    /*p36.XUFU*/ cfg_reg.OBP00.set(FF48_WRn, 1, cpu_bus.TS_D0);
    /*p36.XUKY*/ cfg_reg.OBP01.set(FF48_WRn, 1, cpu_bus.TS_D1);
    /*p36.XOVA*/ cfg_reg.OBP02.set(FF48_WRn, 1, cpu_bus.TS_D2);
    /*p36.XALO*/ cfg_reg.OBP03.set(FF48_WRn, 1, cpu_bus.TS_D3);
    /*p36.XERU*/ cfg_reg.OBP04.set(FF48_WRn, 1, cpu_bus.TS_D4);
    /*p36.XYZE*/ cfg_reg.OBP05.set(FF48_WRn, 1, cpu_bus.TS_D5);
    /*p36.XUPO*/ cfg_reg.OBP06.set(FF48_WRn, 1, cpu_bus.TS_D6);
    /*p36.XANA*/ cfg_reg.OBP07.set(FF48_WRn, 1, cpu_bus.TS_D7);
  }

  // FF49
  {
    /*p22.VAMA*/ wire FF49n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.WADO_A00, adr_sig.XENO_A01n, adr_sig.XUSY_A02n, adr_sig.WEPO_A03);
    /*p22.TEGO*/ wire FF49 = not(FF49n);
    /*p36.MYXE*/ wire FF49_WR = and (cpu_sig.CUPA_CPU_WR_xxxxxFGH, FF49);
    /*p36.LEHO*/ wire FF49_WRn = not(FF49_WR);

    /*p36.MOXY*/ cfg_reg.OBP10.set(FF49_WRn, 1, cpu_bus.TS_D0);
    /*p36.LAWO*/ cfg_reg.OBP11.set(FF49_WRn, 1, cpu_bus.TS_D1);
    /*p36.MOSA*/ cfg_reg.OBP12.set(FF49_WRn, 1, cpu_bus.TS_D2);
    /*p36.LOSE*/ cfg_reg.OBP13.set(FF49_WRn, 1, cpu_bus.TS_D3);
    /*p36.LUNE*/ cfg_reg.OBP14.set(FF49_WRn, 1, cpu_bus.TS_D4);
    /*p36.LUGU*/ cfg_reg.OBP15.set(FF49_WRn, 1, cpu_bus.TS_D5);
    /*p36.LEPU*/ cfg_reg.OBP16.set(FF49_WRn, 1, cpu_bus.TS_D6);
    /*p36.LUXO*/ cfg_reg.OBP17.set(FF49_WRn, 1, cpu_bus.TS_D7);
  }

  // FF47
  {
    /*p22.WYBO*/ wire FF47n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.WADO_A00, adr_sig.WESA_A01, adr_sig.WALO_A02, adr_sig.XERA_A03n);
    /*p22.WERA*/ wire FF47 = not(FF47n);
    /*p36.VUSO*/ wire FF47_RD = and (cpu_sig.ASOT_CPU_RD, FF47);
    /*p36.TEPY*/ wire FF47_RDn = not(FF47_RD);

    /*p36.RARO*/ cpu_bus.TS_D0.set_tribuf(!FF47_RDn, cfg_reg.BGP0.q());
    /*p36.PABA*/ cpu_bus.TS_D1.set_tribuf(!FF47_RDn, cfg_reg.BGP1.q());
    /*p36.REDO*/ cpu_bus.TS_D2.set_tribuf(!FF47_RDn, cfg_reg.BGP2.q());
    /*p36.LOBE*/ cpu_bus.TS_D3.set_tribuf(!FF47_RDn, cfg_reg.BGP3.q());
    /*p36.LACE*/ cpu_bus.TS_D4.set_tribuf(!FF47_RDn, cfg_reg.BGP4.q());
    /*p36.LYKA*/ cpu_bus.TS_D5.set_tribuf(!FF47_RDn, cfg_reg.BGP5.q());
    /*p36.LODY*/ cpu_bus.TS_D6.set_tribuf(!FF47_RDn, cfg_reg.BGP6.q());
    /*p36.LARY*/ cpu_bus.TS_D7.set_tribuf(!FF47_RDn, cfg_reg.BGP7.q());
  }

  // FF48
  {
    /*p22.WETA*/ wire FF48n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.XOLA_A00n, adr_sig.XENO_A01n, adr_sig.XUSY_A02n, adr_sig.WEPO_A03);
    /*p22.XAYO*/ wire FF48 = not(FF48n);
    /*p36.XUFY*/ wire FF48_RD = and (cpu_sig.ASOT_CPU_RD, FF48);
    /*p36.XOZY*/ wire FF48_RDn = not(FF48_RD);

    /*p36.XARY*/ cpu_bus.TS_D0.set_tribuf(!FF48_RDn, cfg_reg.OBP00.q());
    /*p36.XOKE*/ cpu_bus.TS_D1.set_tribuf(!FF48_RDn, cfg_reg.OBP01.q());
    /*p36.XUNO*/ cpu_bus.TS_D2.set_tribuf(!FF48_RDn, cfg_reg.OBP02.q());
    /*p36.XUBY*/ cpu_bus.TS_D3.set_tribuf(!FF48_RDn, cfg_reg.OBP03.q());
    /*p36.XAJU*/ cpu_bus.TS_D4.set_tribuf(!FF48_RDn, cfg_reg.OBP04.q());
    /*p36.XOBO*/ cpu_bus.TS_D5.set_tribuf(!FF48_RDn, cfg_reg.OBP05.q());
    /*p36.XAXA*/ cpu_bus.TS_D6.set_tribuf(!FF48_RDn, cfg_reg.OBP06.q());
    /*p36.XAWO*/ cpu_bus.TS_D7.set_tribuf(!FF48_RDn, cfg_reg.OBP07.q());
  }

  // FF49
  {
    /*p22.VAMA*/ wire FF49n = nand(adr_sig.WERO_FF40_FF4Fp, adr_sig.WADO_A00, adr_sig.XENO_A01n, adr_sig.XUSY_A02n, adr_sig.WEPO_A03);
    /*p22.TEGO*/ wire FF49 = not(FF49n);
    /*p36.MUMY*/ wire FF49_RD = and (cpu_sig.ASOT_CPU_RD, FF49);
    /*p36.LOTE*/ wire FF49_RDn = not(FF49_RD); // where does this go?

    /*p36.LAJU*/ cpu_bus.TS_D0.set_tribuf(!FF49_RDn, cfg_reg.OBP10.q());
    /*p36.LEPA*/ cpu_bus.TS_D1.set_tribuf(!FF49_RDn, cfg_reg.OBP11.q());
    /*p36.LODE*/ cpu_bus.TS_D2.set_tribuf(!FF49_RDn, cfg_reg.OBP12.q());
    /*p36.LYZA*/ cpu_bus.TS_D3.set_tribuf(!FF49_RDn, cfg_reg.OBP13.q());
    /*p36.LUKY*/ cpu_bus.TS_D4.set_tribuf(!FF49_RDn, cfg_reg.OBP14.q());
    /*p36.LUGA*/ cpu_bus.TS_D5.set_tribuf(!FF49_RDn, cfg_reg.OBP15.q());
    /*p36.LEBA*/ cpu_bus.TS_D6.set_tribuf(!FF49_RDn, cfg_reg.OBP16.q());
    /*p36.LELU*/ cpu_bus.TS_D7.set_tribuf(!FF49_RDn, cfg_reg.OBP17.q());
  }

}

bool PixelPipeRegisters::commit() {
  bool changed = false;
  /* PIN_50 */ changed |= LD1.commit_pinout();
  /* PIN_51 */ changed |= LD0.commit_pinout();

  /*p32.LEGU*/ changed |= BG_PIX_A0.commit_reg();
  /*p32.NUDU*/ changed |= BG_PIX_A1.commit_reg();
  /*p32.MUKU*/ changed |= BG_PIX_A2.commit_reg();
  /*p32.LUZO*/ changed |= BG_PIX_A3.commit_reg();
  /*p32.MEGU*/ changed |= BG_PIX_A4.commit_reg();
  /*p32.MYJY*/ changed |= BG_PIX_A5.commit_reg();
  /*p32.NASA*/ changed |= BG_PIX_A6.commit_reg();
  /*p32.NEFO*/ changed |= BG_PIX_A7.commit_reg();
  /*p32.RAWU*/ changed |= BG_PIX_B0.commit_reg();
  /*p32.POZO*/ changed |= BG_PIX_B1.commit_reg();
  /*p32.PYZO*/ changed |= BG_PIX_B2.commit_reg();
  /*p32.POXA*/ changed |= BG_PIX_B3.commit_reg();
  /*p32.PULO*/ changed |= BG_PIX_B4.commit_reg();
  /*p32.POJU*/ changed |= BG_PIX_B5.commit_reg();
  /*p32.POWY*/ changed |= BG_PIX_B6.commit_reg();
  /*p32.PYJU*/ changed |= BG_PIX_B7.commit_reg();
  /*p33.PEFO*/ changed |= SPR_PIX_A0.commit_reg();
  /*p33.ROKA*/ changed |= SPR_PIX_A1.commit_reg();
  /*p33.MYTU*/ changed |= SPR_PIX_A2.commit_reg();
  /*p33.RAMU*/ changed |= SPR_PIX_A3.commit_reg();
  /*p33.SELE*/ changed |= SPR_PIX_A4.commit_reg();
  /*p33.SUTO*/ changed |= SPR_PIX_A5.commit_reg();
  /*p33.RAMA*/ changed |= SPR_PIX_A6.commit_reg();
  /*p33.RYDU*/ changed |= SPR_PIX_A7.commit_reg();
  /*p33.REWO*/ changed |= SPR_PIX_B0.commit_reg();
  /*p33.PEBA*/ changed |= SPR_PIX_B1.commit_reg();
  /*p33.MOFO*/ changed |= SPR_PIX_B2.commit_reg();
  /*p33.PUDU*/ changed |= SPR_PIX_B3.commit_reg();
  /*p33.SAJA*/ changed |= SPR_PIX_B4.commit_reg();
  /*p33.SUNY*/ changed |= SPR_PIX_B5.commit_reg();
  /*p33.SEMO*/ changed |= SPR_PIX_B6.commit_reg();
  /*p33.SEGA*/ changed |= SPR_PIX_B7.commit_reg();
  /*p32.MYDE*/ changed |= BG_PIPE_A0.commit_reg();
  /*p32.NOZO*/ changed |= BG_PIPE_A1.commit_reg();
  /*p32.MOJU*/ changed |= BG_PIPE_A2.commit_reg();
  /*p32.MACU*/ changed |= BG_PIPE_A3.commit_reg();
  /*p32.NEPO*/ changed |= BG_PIPE_A4.commit_reg();
  /*p32.MODU*/ changed |= BG_PIPE_A5.commit_reg();
  /*p32.NEDA*/ changed |= BG_PIPE_A6.commit_reg();
  /*p32.PYBO*/ changed |= BG_PIPE_A7.commit_reg();
  /*p32.TOMY*/ changed |= BG_PIPE_B0.commit_reg();
  /*p32.TACA*/ changed |= BG_PIPE_B1.commit_reg();
  /*p32.SADY*/ changed |= BG_PIPE_B2.commit_reg();
  /*p32.RYSA*/ changed |= BG_PIPE_B3.commit_reg();
  /*p32.SOBO*/ changed |= BG_PIPE_B4.commit_reg();
  /*p32.SETU*/ changed |= BG_PIPE_B5.commit_reg();
  /*p32.RALU*/ changed |= BG_PIPE_B6.commit_reg();
  /*p32.SOHU*/ changed |= BG_PIPE_B7.commit_reg();
  /*p33.NURO*/ changed |= SPR_PIPE_B0.commit_reg();
  /*p33.MASO*/ changed |= SPR_PIPE_B1.commit_reg();
  /*p33.LEFE*/ changed |= SPR_PIPE_B2.commit_reg();
  /*p33.LESU*/ changed |= SPR_PIPE_B3.commit_reg();
  /*p33.WYHO*/ changed |= SPR_PIPE_B4.commit_reg();
  /*p33.WORA*/ changed |= SPR_PIPE_B5.commit_reg();
  /*p33.VAFO*/ changed |= SPR_PIPE_B6.commit_reg();
  /*p33.WUFY*/ changed |= SPR_PIPE_B7.commit_reg();
  /*p33.NYLU*/ changed |= SPR_PIPE_A0.commit_reg();
  /*p33.PEFU*/ changed |= SPR_PIPE_A1.commit_reg();
  /*p33.NATY*/ changed |= SPR_PIPE_A2.commit_reg();
  /*p33.PYJO*/ changed |= SPR_PIPE_A3.commit_reg();
  /*p33.VARE*/ changed |= SPR_PIPE_A4.commit_reg();
  /*p33.WEBA*/ changed |= SPR_PIPE_A5.commit_reg();
  /*p33.VANU*/ changed |= SPR_PIPE_A6.commit_reg();
  /*p33.VUPY*/ changed |= SPR_PIPE_A7.commit_reg();
  /*p34.RUGO*/ changed |= PAL_PIPE_0.commit_reg();
  /*p34.SATA*/ changed |= PAL_PIPE_1.commit_reg();
  /*p34.ROSA*/ changed |= PAL_PIPE_2.commit_reg();
  /*p34.SOMY*/ changed |= PAL_PIPE_3.commit_reg();
  /*p34.PALU*/ changed |= PAL_PIPE_4.commit_reg();
  /*p34.NUKE*/ changed |= PAL_PIPE_5.commit_reg();
  /*p34.MODA*/ changed |= PAL_PIPE_6.commit_reg();
  /*p34.LYME*/ changed |= PAL_PIPE_7.commit_reg();
  /*p26.VEZO*/ changed |= MASK_PIPE_0.commit_reg();
  /*p26.WURU*/ changed |= MASK_PIPE_1.commit_reg();
  /*p26.VOSA*/ changed |= MASK_PIPE_2.commit_reg();
  /*p26.WYFU*/ changed |= MASK_PIPE_3.commit_reg();
  /*p26.XETE*/ changed |= MASK_PIPE_4.commit_reg();
  /*p26.WODA*/ changed |= MASK_PIPE_5.commit_reg();
  /*p26.VUMO*/ changed |= MASK_PIPE_6.commit_reg();
  /*p26.VAVA*/ changed |= MASK_PIPE_7.commit_reg();

  return changed;
}