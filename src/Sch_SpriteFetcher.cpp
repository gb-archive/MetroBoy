#include "Sch_SpriteFetcher.h"
#include "Sch_Top.h"

using namespace Schematics;

//------------------------------------------------------------------------------

void SpriteFetcher::tick(SchematicTop& /*top*/) {
}

//------------------------------------------------------------------------------

void SpriteFetcher::tock(SchematicTop& top) {

  /*p01.LAPE*/ wire _LAPE_AxCxExGx = not(top.ALET_xBxDxFxH());
  /*p27.TAVA*/ wire _TAVA_xBxDxFxH = not(_LAPE_AxCxExGx);


  //----------------------------------------
  // So this is def the chunk that watches FEPO_STORE_MATCHp and triggers a sprite fetch...
  // Maybe we should annotate phase starting with the phase 0 = FEPO_MATCH_SYNC goes high?

  {

    /*p27.TUKU*/ wire _TUKU_WIN_HITn = not(top.TOMU_WIN_HITp());
    /*p27.SOWO*/ wire _SOWO_SFETCH_RUNNINGn = not(TAKA_SFETCH_RUNNINGp.q());
    /*p27.TEKY*/ wire _TEKY_SPRITE_FETCH = and (top.FEPO_STORE_MATCHp(), _TUKU_WIN_HITn, top.LYRY_BFETCH_DONEp(), _SOWO_SFETCH_RUNNINGn);

    /*p27.SOBU*/ SOBU_SPRITE_FETCH_A.set(_TAVA_xBxDxFxH, top.VYPO_GND, _TEKY_SPRITE_FETCH);
    /*p27.SUDA*/ SUDA_SPRITE_FETCH_B.set(_LAPE_AxCxExGx, top.VYPO_GND, SOBU_SPRITE_FETCH_A.q());
    /*p27.RYCE*/ wire _RYCE_SPRITE_FETCHpe = and (SOBU_SPRITE_FETCH_A.q(),  SUDA_SPRITE_FETCH_B.qn());
    /*p01.ROSY*/ wire _ROSY_VID_RSTp = not(top.XAPO_VID_RSTn());
    /*p27.SECA*/ wire _SECA_SPRITE_FETCHne = nor(_RYCE_SPRITE_FETCHpe, _ROSY_VID_RSTp, top.BYHA_VID_LINE_TRIG_d4()); // def nor

    /*p27.TAKA*/ TAKA_SFETCH_RUNNINGp.nand_latch(_SECA_SPRITE_FETCHne, top.VEKU_SFETCH_RUNNING_RSTn());

    /*p29.TAME*/ wire _TAME_SFETCH_CLK_GATE = nand(TESE_SFETCH_S2.q(), TOXE_SFETCH_S0.q());
    /*p29.TOMA*/ wire _TOMA_SFETCH_CLK_xBxDxFxH = nand(_LAPE_AxCxExGx, _TAME_SFETCH_CLK_GATE);

    /*p29.TOXE*/ TOXE_SFETCH_S0.set(_TOMA_SFETCH_CLK_xBxDxFxH, _SECA_SPRITE_FETCHne, TOXE_SFETCH_S0.qn());
    /*p29.TULY*/ TULY_SFETCH_S1.set(TOXE_SFETCH_S0.qn(),      _SECA_SPRITE_FETCHne, TULY_SFETCH_S1.qn());
    /*p29.TESE*/ TESE_SFETCH_S2.set(TULY_SFETCH_S1.qn(),      _SECA_SPRITE_FETCHne, TESE_SFETCH_S2.qn());

    /*p29.TOBU*/ TOBU_SFETCH_S1_D2.set(_TAVA_xBxDxFxH, top.XYMU_RENDERINGp(), TULY_SFETCH_S1.q());    // note input is seq 1 not 2
    /*p29.VONU*/ VONU_SFETCH_S1_D4.set(_TAVA_xBxDxFxH, top.XYMU_RENDERINGp(), TOBU_SFETCH_S1_D2.q());
    /*p29.SEBA*/ SEBA_SFETCH_S1_D5.set(_LAPE_AxCxExGx, top.XYMU_RENDERINGp(), VONU_SFETCH_S1_D4.q());
  }

  {
    /*p29.XONO*/ wire _XONO_FLIP_X = and(top.BAXO_SPRITE_X5(), top.TEXY_SPR_READ_VRAMp());
    /*p33.POBE*/ wire _POBE_FLIP0 = mux2_p(top.VRM_TRI_D7, top.VRM_TRI_D0, _XONO_FLIP_X);
    /*p33.PACY*/ wire _PACY_FLIP1 = mux2_p(top.VRM_TRI_D6, top.VRM_TRI_D1, _XONO_FLIP_X);
    /*p33.PONO*/ wire _PONO_FLIP2 = mux2_p(top.VRM_TRI_D5, top.VRM_TRI_D2, _XONO_FLIP_X);
    /*p33.PUGU*/ wire _PUGU_FLIP3 = mux2_p(top.VRM_TRI_D4, top.VRM_TRI_D3, _XONO_FLIP_X);
    /*p33.PUTE*/ wire _PUTE_FLIP4 = mux2_p(top.VRM_TRI_D3, top.VRM_TRI_D4, _XONO_FLIP_X);
    /*p33.PULY*/ wire _PULY_FLIP5 = mux2_p(top.VRM_TRI_D2, top.VRM_TRI_D5, _XONO_FLIP_X);
    /*p33.PELO*/ wire _PELO_FLIP6 = mux2_p(top.VRM_TRI_D1, top.VRM_TRI_D6, _XONO_FLIP_X);
    /*p33.PAWE*/ wire _PAWE_FLIP7 = mux2_p(top.VRM_TRI_D0, top.VRM_TRI_D7, _XONO_FLIP_X);


    /*p29.TYFO*/ TYFO_SFETCH_S0_D1.set(_LAPE_AxCxExGx, top.VYPO_GND, TOXE_SFETCH_S0.q());
    /*p29.SYCU*/ wire _SYCU_SFETCH_S0pe = nor(top.TYTU_SFETCH_S0n(), top.LOBY_RENDERINGn(), TYFO_SFETCH_S0_D1.q());

    /*p29.RACA*/ wire _RACA_LATCH_SPPIXB = and(VONU_SFETCH_S1_D4.q(), _SYCU_SFETCH_S0pe);
    /*p29.PEBY*/ wire _PEBY_CLKp = not(_RACA_LATCH_SPPIXB);
    /*p29.NYBE*/ wire _NYBE_CLKn = not(_PEBY_CLKp);
    /*p29.PUCO*/ wire _PUCO_CLKb = not(_NYBE_CLKn);

    /*p33.PEFO*/ SPR_PIX_A0.set(_PUCO_CLKb, !_PUCO_CLKb, _POBE_FLIP0);
    /*p33.ROKA*/ SPR_PIX_A1.set(_PUCO_CLKb, !_PUCO_CLKb, _PACY_FLIP1);
    /*p33.MYTU*/ SPR_PIX_A2.set(_PUCO_CLKb, !_PUCO_CLKb, _PONO_FLIP2);
    /*p33.RAMU*/ SPR_PIX_A3.set(_PUCO_CLKb, !_PUCO_CLKb, _PUGU_FLIP3);
    /*p33.SELE*/ SPR_PIX_A4.set(_PUCO_CLKb, !_PUCO_CLKb, _PUTE_FLIP4);
    /*p33.SUTO*/ SPR_PIX_A5.set(_PUCO_CLKb, !_PUCO_CLKb, _PULY_FLIP5);
    /*p33.RAMA*/ SPR_PIX_A6.set(_PUCO_CLKb, !_PUCO_CLKb, _PELO_FLIP6);
    /*p33.RYDU*/ SPR_PIX_A7.set(_PUCO_CLKb, !_PUCO_CLKb, _PAWE_FLIP7);

    /*p29.TOPU*/ wire _TOPU_LATCH_SPPIXA = and(TULY_SFETCH_S1.q(), _SYCU_SFETCH_S0pe);
    /*p29.VYWA*/ wire _VYWA_CLKp = not(_TOPU_LATCH_SPPIXA);
    /*p29.WENY*/ wire _WENY_CLKn = not(_VYWA_CLKp);
    /*p29.XADO*/ wire _XADO_CLKp = not(_WENY_CLKn);

    /*p33.REWO*/ SPR_PIX_B0.set(_XADO_CLKp, !_XADO_CLKp, _POBE_FLIP0);
    /*p33.PEBA*/ SPR_PIX_B1.set(_XADO_CLKp, !_XADO_CLKp, _PACY_FLIP1);
    /*p33.MOFO*/ SPR_PIX_B2.set(_XADO_CLKp, !_XADO_CLKp, _PONO_FLIP2);
    /*p33.PUDU*/ SPR_PIX_B3.set(_XADO_CLKp, !_XADO_CLKp, _PUGU_FLIP3);
    /*p33.SAJA*/ SPR_PIX_B4.set(_XADO_CLKp, !_XADO_CLKp, _PUTE_FLIP4);
    /*p33.SUNY*/ SPR_PIX_B5.set(_XADO_CLKp, !_XADO_CLKp, _PULY_FLIP5);
    /*p33.SEMO*/ SPR_PIX_B6.set(_XADO_CLKp, !_XADO_CLKp, _PELO_FLIP6);
    /*p33.SEGA*/ SPR_PIX_B7.set(_XADO_CLKp, !_XADO_CLKp, _PAWE_FLIP7);
  }

  {
    /*p29.FUFO*/ wire _FUFO_LCDC_SPSIZEn = not(top.XYMO_LCDC_SPSIZE.q());
    /*p29.WUKY*/ wire _WUKY_FLIP_Y = not(top.YZOS_SPRITE_X6());

    /*p29.XUQU*/ wire _XUQU_SPRITE_AB = not(!VONU_SFETCH_S1_D4.q());
    /*p29.CYVU*/ wire _CYVU_SPRITE_Y0 = xor (_WUKY_FLIP_Y, top.SPR_TRI_LINE_1.q());
    /*p29.BORE*/ wire _BORE_SPRITE_Y1 = xor (_WUKY_FLIP_Y, top.SPR_TRI_LINE_2.q());
    /*p29.BUVY*/ wire _BUVY_SPRITE_Y2 = xor (_WUKY_FLIP_Y, top.SPR_TRI_LINE_3.q());

    /*p29.WAGO*/ wire _WAGO = xor (_WUKY_FLIP_Y, top.SPR_TRI_LINE_0.q());
    /*p29.GEJY*/ wire _GEJY_SPRITE_Y3 = amux2(_FUFO_LCDC_SPSIZEn, !top.XUSO_SPRITE_Y0(), top.XYMO_LCDC_SPSIZE.q(), _WAGO);

    /*p29.ABEM*/ top.VRM_TRI_A00.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), _XUQU_SPRITE_AB);
    /*p29.BAXE*/ top.VRM_TRI_A01.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), _CYVU_SPRITE_Y0);
    /*p29.ARAS*/ top.VRM_TRI_A02.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), _BORE_SPRITE_Y1);
    /*p29.AGAG*/ top.VRM_TRI_A03.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), _BUVY_SPRITE_Y2);
    /*p29.FAMU*/ top.VRM_TRI_A04.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), _GEJY_SPRITE_Y3);
    /*p29.FUGY*/ top.VRM_TRI_A05.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.XEGU_SPRITE_Y1());
    /*p29.GAVO*/ top.VRM_TRI_A06.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.YJEX_SPRITE_Y2());
    /*p29.WYGA*/ top.VRM_TRI_A07.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.XYJU_SPRITE_Y3());
    /*p29.WUNE*/ top.VRM_TRI_A08.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.YBOG_SPRITE_Y4());
    /*p29.GOTU*/ top.VRM_TRI_A09.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.WYSO_SPRITE_Y5());
    /*p29.GEGU*/ top.VRM_TRI_A10.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.XOTE_SPRITE_Y6());
    /*p29.XEHE*/ top.VRM_TRI_A11.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.YZAB_SPRITE_Y7());
    /*p29.DYSO*/ top.VRM_TRI_A12.set_tribuf_6n(top.ABON_SPR_VRM_RDn(), top.GND);   // sprites always in low half of tile store
  }
}

//------------------------------------------------------------------------------

SignalHash SpriteFetcher::commit() {
  SignalHash hash;

  /*p27.TAKA*/ hash << TAKA_SFETCH_RUNNINGp.commit();
  /*p27.SOBU*/ hash << SOBU_SPRITE_FETCH_A.commit();
  /*p27.SUDA*/ hash << SUDA_SPRITE_FETCH_B.commit();

  /*p29.TOXE*/ hash << TOXE_SFETCH_S0.commit();
  /*p29.TULY*/ hash << TULY_SFETCH_S1.commit();
  /*p29.TESE*/ hash << TESE_SFETCH_S2.commit();
  /*p29.TOBU*/ hash << TOBU_SFETCH_S1_D2.commit();
  /*p29.VONU*/ hash << VONU_SFETCH_S1_D4.commit();
  /*p29.SEBA*/ hash << SEBA_SFETCH_S1_D5.commit();
  /*p29.TYFO*/ hash << TYFO_SFETCH_S0_D1.commit();

  /*p33.PEFO*/ hash << SPR_PIX_A0.commit();
  /*p33.ROKA*/ hash << SPR_PIX_A1.commit();
  /*p33.MYTU*/ hash << SPR_PIX_A2.commit();
  /*p33.RAMU*/ hash << SPR_PIX_A3.commit();
  /*p33.SELE*/ hash << SPR_PIX_A4.commit();
  /*p33.SUTO*/ hash << SPR_PIX_A5.commit();
  /*p33.RAMA*/ hash << SPR_PIX_A6.commit();
  /*p33.RYDU*/ hash << SPR_PIX_A7.commit();
  /*p33.REWO*/ hash << SPR_PIX_B0.commit();
  /*p33.PEBA*/ hash << SPR_PIX_B1.commit();
  /*p33.MOFO*/ hash << SPR_PIX_B2.commit();
  /*p33.PUDU*/ hash << SPR_PIX_B3.commit();
  /*p33.SAJA*/ hash << SPR_PIX_B4.commit();
  /*p33.SUNY*/ hash << SPR_PIX_B5.commit();
  /*p33.SEMO*/ hash << SPR_PIX_B6.commit();
  /*p33.SEGA*/ hash << SPR_PIX_B7.commit();

  return hash;
}

//------------------------------------------------------------------------------
