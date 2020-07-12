#include "Sch_SpriteStore.h"

#include "Sch_Top.h"

using namespace Schematics;

// XECU01 nc
// XECU02 << WEFE02
// XECU03 << YZET02 (oam a7)
// XECU04 nc
// XECU05 << WUDA03
// XECU06 ==
// XECU07 ==
// XECU08 << CYKE01???? - is this a dual-edge ff? I guess that would make it latch the address every tcycle?
// XECU09 << WEFE02
// XECU10 ==
// XECU11 nc
// XECU12 >> WEZA04
// XECU13 >> nc

// BUZA04 = and(CENO16, XYMU03)

// WEZA01 << BUZA04
// WEZA02 ==
// WEZA03 ==
// WEZA04 << XECU12
// WEZA05 nc
// WEZA06 

//------------------------------------------------------------------------------

void SpriteStoreRegisters::tick_match(SchematicTop& top) {
  {
    /*p21.ACAM*/ wire _ACAM_X0n = not(top.XEHO_X0());
    /*p21.AZUB*/ wire _AZUB_X1n = not(top.SAVY_X1());
    /*p21.AMEL*/ wire _AMEL_X2n = not(top.XODU_X2());
    /*p21.AHAL*/ wire _AHAL_X3n = not(top.XYDO_X3());
    /*p21.APUX*/ wire _APUX_X4n = not(top.TUHU_X4());
    /*p21.ABEF*/ wire _ABEF_X5n = not(top.TUKY_X5());
    /*p21.ADAZ*/ wire _ADAZ_X6n = not(top.TAKO_X6());
    /*p21.ASAH*/ wire _ASAH_X7n = not(top.SYBE_X7());

    /*p31.ZOGY*/ wire STORE0_MATCH0n = xor (XEPE_STORE0_X0.q(), _ACAM_X0n);
    /*p31.ZEBA*/ wire STORE0_MATCH1n = xor (YLAH_STORE0_X1.q(), _AZUB_X1n);
    /*p31.ZAHA*/ wire STORE0_MATCH2n = xor (ZOLA_STORE0_X2.q(), _AMEL_X2n);
    /*p31.ZOKY*/ wire STORE0_MATCH3n = xor (ZULU_STORE0_X3.q(), _AHAL_X3n);
    /*p31.WOJU*/ wire STORE0_MATCH4n = xor (WELO_STORE0_X4.q(), _APUX_X4n);
    /*p31.YFUN*/ wire STORE0_MATCH5n = xor (XUNY_STORE0_X5.q(), _ABEF_X5n);
    /*p31.WYZA*/ wire STORE0_MATCH6n = xor (WOTE_STORE0_X6.q(), _ADAZ_X6n);
    /*p31.YPUK*/ wire STORE0_MATCH7n = xor (XAKO_STORE0_X7.q(), _ASAH_X7n);

    /*p31.EDYM*/ wire STORE1_MATCH0n = xor (STORE1_X0.q(), _ACAM_X0n);
    /*p31.EMYB*/ wire STORE1_MATCH1n = xor (STORE1_X1.q(), _AZUB_X1n);
    /*p31.EBEF*/ wire STORE1_MATCH2n = xor (STORE1_X2.q(), _AMEL_X2n);
    /*p31.EWOK*/ wire STORE1_MATCH3n = xor (STORE1_X3.q(), _AHAL_X3n);
    /*p31.COLA*/ wire STORE1_MATCH4n = xor (STORE1_X4.q(), _APUX_X4n);
    /*p31.BOBA*/ wire STORE1_MATCH5n = xor (STORE1_X5.q(), _ABEF_X5n);
    /*p31.COLU*/ wire STORE1_MATCH6n = xor (STORE1_X6.q(), _ADAZ_X6n);
    /*p31.BAHU*/ wire STORE1_MATCH7n = xor (STORE1_X7.q(), _ASAH_X7n);

    /*p31.FUZU*/ wire STORE2_MATCH0n = xor (STORE2_X0.q(), _ACAM_X0n);
    /*p31.FESO*/ wire STORE2_MATCH1n = xor (STORE2_X1.q(), _AZUB_X1n);
    /*p31.FOKY*/ wire STORE2_MATCH2n = xor (STORE2_X2.q(), _AMEL_X2n);
    /*p31.FYVA*/ wire STORE2_MATCH3n = xor (STORE2_X3.q(), _AHAL_X3n);
    /*p31.CEKO*/ wire STORE2_MATCH4n = xor (STORE2_X4.q(), _APUX_X4n);
    /*p31.DETY*/ wire STORE2_MATCH5n = xor (STORE2_X5.q(), _ABEF_X5n);
    /*p31.DOZO*/ wire STORE2_MATCH6n = xor (STORE2_X6.q(), _ADAZ_X6n);
    /*p31.CONY*/ wire STORE2_MATCH7n = xor (STORE2_X7.q(), _ASAH_X7n);

    /*p31.YHOK*/ wire STORE3_MATCH0n = xor (STORE3_X0.q(), _ACAM_X0n);
    /*p31.YCAH*/ wire STORE3_MATCH1n = xor (STORE3_X1.q(), _AZUB_X1n);
    /*p31.YDAJ*/ wire STORE3_MATCH2n = xor (STORE3_X2.q(), _AMEL_X2n);
    /*p31.YVUZ*/ wire STORE3_MATCH3n = xor (STORE3_X3.q(), _AHAL_X3n);
    /*p31.YVAP*/ wire STORE3_MATCH4n = xor (STORE3_X4.q(), _APUX_X4n);
    /*p31.XENY*/ wire STORE3_MATCH5n = xor (STORE3_X5.q(), _ABEF_X5n);
    /*p31.XAVU*/ wire STORE3_MATCH6n = xor (STORE3_X6.q(), _ADAZ_X6n);
    /*p31.XEVA*/ wire STORE3_MATCH7n = xor (STORE3_X7.q(), _ASAH_X7n);

    /*p31.XEJU*/ wire STORE4_MATCH0n = xor (STORE4_X0.q(), _ACAM_X0n);
    /*p31.ZATE*/ wire STORE4_MATCH1n = xor (STORE4_X1.q(), _AZUB_X1n);
    /*p31.ZAKU*/ wire STORE4_MATCH2n = xor (STORE4_X2.q(), _AMEL_X2n);
    /*p31.YBOX*/ wire STORE4_MATCH3n = xor (STORE4_X3.q(), _AHAL_X3n);
    /*p31.ZYKU*/ wire STORE4_MATCH4n = xor (STORE4_X4.q(), _APUX_X4n);
    /*p31.ZYPU*/ wire STORE4_MATCH5n = xor (STORE4_X5.q(), _ABEF_X5n);
    /*p31.XAHA*/ wire STORE4_MATCH6n = xor (STORE4_X6.q(), _ADAZ_X6n);
    /*p31.ZEFE*/ wire STORE4_MATCH7n = xor (STORE4_X7.q(), _ASAH_X7n);

    /*p31.GUZO*/ wire STORE5_MATCH0n = xor (STORE5_X0.q(), _ACAM_X0n);
    /*p31.GOLA*/ wire STORE5_MATCH1n = xor (STORE5_X1.q(), _AZUB_X1n);
    /*p31.GEVE*/ wire STORE5_MATCH2n = xor (STORE5_X2.q(), _AMEL_X2n);
    /*p31.GUDE*/ wire STORE5_MATCH3n = xor (STORE5_X3.q(), _AHAL_X3n);
    /*p31.BAZY*/ wire STORE5_MATCH4n = xor (STORE5_X4.q(), _APUX_X4n);
    /*p31.CYLE*/ wire STORE5_MATCH5n = xor (STORE5_X5.q(), _ABEF_X5n);
    /*p31.CEVA*/ wire STORE5_MATCH6n = xor (STORE5_X6.q(), _ADAZ_X6n);
    /*p31.BUMY*/ wire STORE5_MATCH7n = xor (STORE5_X7.q(), _ASAH_X7n);

    /*p31.XOSU*/ wire STORE6_MATCH0n = xor (STORE6_X0.q(), _ACAM_X0n);
    /*p31.ZUVU*/ wire STORE6_MATCH1n = xor (STORE6_X1.q(), _AZUB_X1n);
    /*p31.XUCO*/ wire STORE6_MATCH2n = xor (STORE6_X2.q(), _AMEL_X2n);
    /*p31.ZULO*/ wire STORE6_MATCH3n = xor (STORE6_X3.q(), _AHAL_X3n);
    /*p31.ZARE*/ wire STORE6_MATCH4n = xor (STORE6_X4.q(), _APUX_X4n);
    /*p31.ZEMU*/ wire STORE6_MATCH5n = xor (STORE6_X5.q(), _ABEF_X5n);
    /*p31.ZYGO*/ wire STORE6_MATCH6n = xor (STORE6_X6.q(), _ADAZ_X6n);
    /*p31.ZUZY*/ wire STORE6_MATCH7n = xor (STORE6_X7.q(), _ASAH_X7n);

    /*p31.DUSE*/ wire STORE7_MATCH0n = xor (STORE7_X0.q(), _ACAM_X0n);
    /*p31.DAGU*/ wire STORE7_MATCH1n = xor (STORE7_X1.q(), _AZUB_X1n);
    /*p31.DYZE*/ wire STORE7_MATCH2n = xor (STORE7_X2.q(), _AMEL_X2n);
    /*p31.DESO*/ wire STORE7_MATCH3n = xor (STORE7_X3.q(), _AHAL_X3n);
    /*p31.EJOT*/ wire STORE7_MATCH4n = xor (STORE7_X4.q(), _APUX_X4n);
    /*p31.ESAJ*/ wire STORE7_MATCH5n = xor (STORE7_X5.q(), _ABEF_X5n);
    /*p31.DUCU*/ wire STORE7_MATCH6n = xor (STORE7_X6.q(), _ADAZ_X6n);
    /*p31.EWUD*/ wire STORE7_MATCH7n = xor (STORE7_X7.q(), _ASAH_X7n);

    /*p31.DUZE*/ wire STORE8_MATCH0n = xor (STORE8_X0.q(), _APUX_X4n);
    /*p31.DAGA*/ wire STORE8_MATCH1n = xor (STORE8_X1.q(), _ABEF_X5n);
    /*p31.DAWU*/ wire STORE8_MATCH2n = xor (STORE8_X2.q(), _ADAZ_X6n);
    /*p31.EJAW*/ wire STORE8_MATCH3n = xor (STORE8_X3.q(), _ASAH_X7n);
    /*p31.GOHO*/ wire STORE8_MATCH4n = xor (STORE8_X4.q(), _ACAM_X0n);
    /*p31.GASU*/ wire STORE8_MATCH5n = xor (STORE8_X5.q(), _AZUB_X1n);
    /*p31.GABU*/ wire STORE8_MATCH6n = xor (STORE8_X6.q(), _AMEL_X2n);
    /*p31.GAFE*/ wire STORE8_MATCH7n = xor (STORE8_X7.q(), _AHAL_X3n);

    /*p31.YMAM*/ wire STORE9_MATCH0n = xor (STORE9_X0.q(), _ACAM_X0n);
    /*p31.YTYP*/ wire STORE9_MATCH1n = xor (STORE9_X1.q(), _AZUB_X1n);
    /*p31.YFOP*/ wire STORE9_MATCH2n = xor (STORE9_X2.q(), _AMEL_X2n);
    /*p31.YVAC*/ wire STORE9_MATCH3n = xor (STORE9_X3.q(), _AHAL_X3n);
    /*p31.ZYWU*/ wire STORE9_MATCH4n = xor (STORE9_X4.q(), _APUX_X4n);
    /*p31.ZUZA*/ wire STORE9_MATCH5n = xor (STORE9_X5.q(), _ABEF_X5n);
    /*p31.ZEJO*/ wire STORE9_MATCH6n = xor (STORE9_X6.q(), _ADAZ_X6n);
    /*p31.ZEDA*/ wire STORE9_MATCH7n = xor (STORE9_X7.q(), _ASAH_X7n);

    /*p31.ZAKO*/ wire STORE0_MATCHAp = nor(STORE0_MATCH0n, STORE0_MATCH1n, STORE0_MATCH2n, STORE0_MATCH3n);
    /*p31.XEBA*/ wire STORE0_MATCHBp = nor(STORE0_MATCH4n, STORE0_MATCH5n, STORE0_MATCH6n, STORE0_MATCH7n);
    /*p31.CYVY*/ wire STORE1_MATCHB = nor(STORE1_MATCH4n, STORE1_MATCH5n, STORE1_MATCH6n, STORE1_MATCH7n);
    /*p31.EWAM*/ wire STORE1_MATCHA = nor(STORE1_MATCH0n, STORE1_MATCH1n, STORE1_MATCH2n, STORE1_MATCH3n);
    /*p31.CEHU*/ wire STORE2_MATCHA = nor(STORE2_MATCH4n, STORE2_MATCH5n, STORE2_MATCH6n, STORE2_MATCH7n);
    /*p31.EKES*/ wire STORE2_MATCHB = nor(STORE2_MATCH0n, STORE2_MATCH1n, STORE2_MATCH2n, STORE2_MATCH3n);
    /*p31.ZURE*/ wire STORE3_MATCHA = nor(STORE3_MATCH0n, STORE3_MATCH1n, STORE3_MATCH2n, STORE3_MATCH3n);
    /*p31.YWOS*/ wire STORE3_MATCHB = nor(STORE3_MATCH4n, STORE3_MATCH5n, STORE3_MATCH6n, STORE3_MATCH7n);
    /*p31.YKOK*/ wire STORE4_MATCHA = nor(STORE4_MATCH0n, STORE4_MATCH1n, STORE4_MATCH2n, STORE4_MATCH3n);
    /*p31.YNAZ*/ wire STORE4_MATCHB = nor(STORE4_MATCH4n, STORE4_MATCH5n, STORE4_MATCH6n, STORE4_MATCH7n);
    /*p31.COGY*/ wire STORE5_MATCHA = nor(STORE5_MATCH4n, STORE5_MATCH5n, STORE5_MATCH6n, STORE5_MATCH7n);
    /*p31.FYMA*/ wire STORE5_MATCHB = nor(STORE5_MATCH0n, STORE5_MATCH1n, STORE5_MATCH2n, STORE5_MATCH3n);
    /*p31.YWAP*/ wire STORE6_MATCHA = nor(STORE6_MATCH4n, STORE6_MATCH5n, STORE6_MATCH6n, STORE6_MATCH7n);
    /*p31.YDOT*/ wire STORE6_MATCHB = nor(STORE6_MATCH0n, STORE6_MATCH1n, STORE6_MATCH2n, STORE6_MATCH3n);
    /*p31.CYCO*/ wire STORE7_MATCHA = nor(STORE7_MATCH0n, STORE7_MATCH1n, STORE7_MATCH2n, STORE7_MATCH3n);
    /*p31.DAJE*/ wire STORE7_MATCHB = nor(STORE7_MATCH4n, STORE7_MATCH5n, STORE7_MATCH6n, STORE7_MATCH7n);
    /*p31.DAMA*/ wire STORE8_MATCHA = nor(STORE8_MATCH0n, STORE8_MATCH1n, STORE8_MATCH2n, STORE8_MATCH3n);
    /*p31.FEHA*/ wire STORE8_MATCHB = nor(STORE8_MATCH4n, STORE8_MATCH5n, STORE8_MATCH6n, STORE8_MATCH7n);
    /*p31.YLEV*/ wire STORE9_MATCHA = nor(STORE9_MATCH0n, STORE9_MATCH1n, STORE9_MATCH2n, STORE9_MATCH3n);
    /*p31.YTUB*/ wire STORE9_MATCHB = nor(STORE9_MATCH4n, STORE9_MATCH5n, STORE9_MATCH6n, STORE9_MATCH7n);

    /*p29.BYJO*/ wire _BYJO_SCANNINGn = not(top.CEHA_SCANNINGp());
    /*p29.AZEM*/ wire _AZEM_RENDERINGp = and (_BYJO_SCANNINGn, top.XYMU_RENDERINGp());
    /*p29.AROR*/ wire _AROR_MATCH_ENp = and (_AZEM_RENDERINGp, top.XYLO_LCDC_SPEN.q());

    /*p29.YDUG*/ STORE0_MATCHn = nand(_AROR_MATCH_ENp, STORE0_MATCHBp, STORE0_MATCHAp);
    /*p29.DYDU*/ STORE1_MATCHn = nand(_AROR_MATCH_ENp, STORE1_MATCHA, STORE1_MATCHB);
    /*p29.DEGO*/ STORE2_MATCHn = nand(_AROR_MATCH_ENp, STORE2_MATCHB, STORE2_MATCHA);
    /*p29.YLOZ*/ STORE3_MATCHn = nand(_AROR_MATCH_ENp, STORE3_MATCHA, STORE3_MATCHB);
    /*p29.XAGE*/ STORE4_MATCHn = nand(_AROR_MATCH_ENp, STORE4_MATCHB, STORE4_MATCHA);
    /*p29.EGOM*/ STORE5_MATCHn = nand(_AROR_MATCH_ENp, STORE5_MATCHB, STORE5_MATCHA);
    /*p29.YBEZ*/ STORE6_MATCHn = nand(_AROR_MATCH_ENp, STORE6_MATCHB, STORE6_MATCHA);
    /*p29.DYKA*/ STORE7_MATCHn = nand(_AROR_MATCH_ENp, STORE7_MATCHA, STORE7_MATCHB);
    /*p29.EFYL*/ STORE8_MATCHn = nand(_AROR_MATCH_ENp, STORE8_MATCHB, STORE8_MATCHA);
    /*p29.YGEM*/ STORE9_MATCHn = nand(_AROR_MATCH_ENp, STORE9_MATCHA, STORE9_MATCHB);

    /*p29.FEFY*/ wire _FEFY = nand(STORE4_MATCHn, STORE3_MATCHn, STORE2_MATCHn, STORE1_MATCHn, STORE0_MATCHn);
    /*p29.FOVE*/ wire _FOVE = nand(STORE9_MATCHn, STORE8_MATCHn, STORE7_MATCHn, STORE6_MATCHn, STORE5_MATCHn);
    /*p29.FEPO*/ FEPO_STORE_MATCHp = or(_FEFY, _FOVE);
  }
}

  //------------------------------------------------------------------------------

void SpriteStoreRegisters::tock(SchematicTop& top) {

  /*p29.DYTY*/ wire _DYTY_STORE_ENn_xxCDxxGH = not(top.CARE_STORE_ENp_ABxxEFxx());

  /*p01.AMYG*/ wire _AMYG_VID_RSTp = not(top.XAPO_VID_RSTn());
  /*p28.ABAK*/ wire _ABAK_VID_LINE_TRIG_d4p = or (top.ATEJ_VID_LINE_TRIG_d4p(), _AMYG_VID_RSTp);
  /*p28.BYVA*/ wire _BYVA_VID_LINE_TRIG_d4n = not(_ABAK_VID_LINE_TRIG_d4p);
  /*p29.DYBA*/ wire _DYBA_VID_LINE_TRIG_d4p = not(_BYVA_VID_LINE_TRIG_d4n);

  //----------------------------------------
  // Sprite scan Y matcher

  {
    // Sprite store counter.
    // The sprite count clock stops ticking once we have 10 sprites.

    /*p29.BAKY*/ wire _BAKY_SPRITES_FULL = and (SPRITE_COUNT1.q(), SPRITE_COUNT3.q());
    /*p29.CAKE*/ wire _CAKE_CLKp = or (_BAKY_SPRITES_FULL, DEZY_STORE_ENn_SYNC.q());
    
    /*p28.AZYB*/ wire _AZYB_RST = not(top.BYHA_VID_LINE_TRIG_d4());
    /*p29.BESE*/ SPRITE_COUNT0.set(_CAKE_CLKp,         _AZYB_RST, SPRITE_COUNT0.qn());
    /*p29.CUXY*/ SPRITE_COUNT1.set(SPRITE_COUNT0.q(), _AZYB_RST, SPRITE_COUNT1.qn());
    /*p29.BEGO*/ SPRITE_COUNT2.set(SPRITE_COUNT1.q(), _AZYB_RST, SPRITE_COUNT2.qn());
    /*p29.DYBE*/ SPRITE_COUNT3.set(SPRITE_COUNT2.q(), _AZYB_RST, SPRITE_COUNT3.qn());
  }

  //----------------------------------------

  {
    // FEPO_STORE_MATCHp here is weird, I guess it's just an easy signal to use to mux the bus?
    /*p30.WENU*/ top.SPR_TRI_LINE_0.set_tribuf_6n(top.FEPO_STORE_MATCHp(), top.DEGE_SPRITE_DELTA0());
    /*p30.CUCU*/ top.SPR_TRI_LINE_1.set_tribuf_6n(top.FEPO_STORE_MATCHp(), top.DABY_SPRITE_DELTA1());
    /*p30.CUCA*/ top.SPR_TRI_LINE_2.set_tribuf_6n(top.FEPO_STORE_MATCHp(), top.DABU_SPRITE_DELTA2());
    /*p30.CEGA*/ top.SPR_TRI_LINE_3.set_tribuf_6n(top.FEPO_STORE_MATCHp(), top.GYSA_SPRITE_DELTA3());

    /*p29.DEZY*/ DEZY_STORE_ENn_SYNC.set(top.ZEME_AxCxExGx(), top.XAPO_VID_RSTn(), _DYTY_STORE_ENn_xxCDxxGH);
  }

  //----------------------------------------
  // Sprite store input driver.
  // Sprite store index comes from the OAM address bus.


  {
    /*p29.BUZA*/ wire _BUZA_STORE_SPRITE_INDX = and(top.CENO_SCANNINGqn(), top.XYMU_RENDERINGp());
    /*p30.WUZY*/ top.SPR_TRI_INDX_0.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.XADU_SPRITE_INDX0.q());
    /*p30.WYSE*/ top.SPR_TRI_INDX_1.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.XEDY_SPRITE_INDX1.q());
    /*p30.ZYSU*/ top.SPR_TRI_INDX_2.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.ZUZE_SPRITE_INDX2.q());
    /*p30.WYDA*/ top.SPR_TRI_INDX_3.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.XOBE_SPRITE_INDX3.q());
    /*p30.WUCO*/ top.SPR_TRI_INDX_4.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.YDUF_SPRITE_INDX4.q());
    /*p30.WEZA*/ top.SPR_TRI_INDX_5.set_tribuf_6n(_BUZA_STORE_SPRITE_INDX, top.XECU_SPRITE_INDX5.q());
  }

  //----------------------------------------
  // Sprite store getter

  {
    /*p29.WEFU*/ wire STORE0_MATCHp = not(STORE0_MATCHn);
    /*p29.GAJA*/ wire STORE1_MATCH = not(STORE1_MATCHn);
    /*p29.GUPO*/ wire STORE2_MATCH = not(STORE2_MATCHn);
    /*p29.WEBO*/ wire STORE3_MATCH = not(STORE3_MATCHn);
    /*p29.WUNA*/ wire STORE4_MATCH = not(STORE4_MATCHn);
    /*p29.GABA*/ wire STORE5_MATCH = not(STORE5_MATCHn);
    /*p29.WASE*/ wire STORE6_MATCH = not(STORE6_MATCHn);
    /*p29.GYTE*/ wire STORE7_MATCH = not(STORE7_MATCHn);
    /*p29.GEKE*/ wire STORE8_MATCH = not(STORE8_MATCHn);

    // Priority encoder so we fetch the first sprite that matches

    /*p29.GEZE*/ wire STORE0_MATCH_OUT = or(STORE0_MATCHp, top.GND);
    /*p29.FUMA*/ wire STORE1_MATCH_OUT = or(STORE1_MATCH, STORE0_MATCH_OUT);
    /*p29.GEDE*/ wire STORE2_MATCH_OUT = or(STORE2_MATCH, STORE1_MATCH_OUT);
    /*p29.WUTO*/ wire STORE3_MATCH_OUT = or(STORE3_MATCH, STORE2_MATCH_OUT);
    /*p29.XYLA*/ wire STORE4_MATCH_OUT = or(STORE4_MATCH, STORE3_MATCH_OUT);
    /*p29.WEJA*/ wire STORE5_MATCH_OUT = or(STORE5_MATCH, STORE4_MATCH_OUT);
    /*p29.WYLA*/ wire STORE6_MATCH_OUT = or(STORE6_MATCH, STORE5_MATCH_OUT);
    /*p29.FAVO*/ wire STORE7_MATCH_OUT = or(STORE7_MATCH, STORE6_MATCH_OUT);
    /*p29.GYGA*/ wire STORE8_MATCH_OUT = or(STORE8_MATCH, STORE7_MATCH_OUT);

    /*p29.GUVA*/ wire _GUVA_SPRITE0_GETp = nor(STORE0_MATCHn, top.GND);
    /*p29.ENUT*/ wire _ENUT_SPRITE1_GETp = nor(STORE1_MATCHn, STORE0_MATCH_OUT);
    /*p29.EMOL*/ wire _EMOL_SPRITE2_GETp = nor(STORE2_MATCHn, STORE1_MATCH_OUT);
    /*p29.GYFY*/ wire _GYFY_SPRITE3_GETp = nor(STORE3_MATCHn, STORE2_MATCH_OUT);
    /*p29.GONO*/ wire _GONO_SPRITE4_GETp = nor(STORE4_MATCHn, STORE3_MATCH_OUT);
    /*p29.GEGA*/ wire _GEGA_SPRITE5_GETp = nor(STORE5_MATCHn, STORE4_MATCH_OUT);
    /*p29.XOJA*/ wire _XOJA_SPRITE6_GETp = nor(STORE6_MATCHn, STORE5_MATCH_OUT);
    /*p29.GUTU*/ wire _GUTU_SPRITE7_GETp = nor(STORE7_MATCHn, STORE6_MATCH_OUT);
    /*p29.FOXA*/ wire _FOXA_SPRITE8_GETp = nor(STORE8_MATCHn, STORE7_MATCH_OUT);
    /*p29.GUZE*/ wire _GUZE_SPRITE9_GETp = nor(STORE9_MATCHn, STORE8_MATCH_OUT);

    // Delayed reset signal for the selected store
    /*p29.EBOJ*/ EBOJ_STORE0_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GUVA_SPRITE0_GETp);
    /*p29.CEDY*/ CEDY_STORE1_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _ENUT_SPRITE1_GETp);
    /*p29.EGAV*/ EGAV_STORE2_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _EMOL_SPRITE2_GETp);
    /*p29.GOTA*/ GOTA_STORE3_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GYFY_SPRITE3_GETp);
    /*p29.XUDY*/ XUDY_STORE4_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GONO_SPRITE4_GETp);
    /*p29.WAFY*/ WAFY_STORE5_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GEGA_SPRITE5_GETp);
    /*p29.WOMY*/ WOMY_STORE6_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _XOJA_SPRITE6_GETp);
    /*p29.WAPO*/ WAPO_STORE7_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GUTU_SPRITE7_GETp);
    /*p29.EXUQ*/ EXUQ_STORE8_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _FOXA_SPRITE8_GETp);
    /*p29.FONO*/ FONO_STORE9_RSTp.set(top.WUTY_SPRITE_DONEp(), _BYVA_VID_LINE_TRIG_d4n, _GUZE_SPRITE9_GETp);

    /*p29.FURO*/ wire FURO_SPRITE0_GETn = not(_GUVA_SPRITE0_GETp);
    /*p29.DYDO*/ wire DYDO_SPRITE1_GETn = not(_ENUT_SPRITE1_GETp);
    /*p29.FAME*/ wire FAME_SPRITE2_GETn = not(_EMOL_SPRITE2_GETp);
    /*p29.GYMA*/ wire GYMA_SPRITE3_GETn = not(_GYFY_SPRITE3_GETp);
    /*p29.GOWO*/ wire GOWO_SPRITE4_GETn = not(_GONO_SPRITE4_GETp);
    /*p29.GYGY*/ wire GYGY_SPRITE5_GETn = not(_GEGA_SPRITE5_GETp);
    /*p29.XYME*/ wire XYME_SPRITE6_GETn = not(_XOJA_SPRITE6_GETp);
    /*p29.GUGY*/ wire GUGY_SPRITE7_GETn = not(_GUTU_SPRITE7_GETp);
    /*p29.DENY*/ wire DENY_SPRITE8_GETn = not(_FOXA_SPRITE8_GETp);
    /*p29.FADO*/ wire FADO_SPRITE9_GETn = not(_GUZE_SPRITE9_GETp);

    /*p30.ZEDY*/ top.SPR_TRI_INDX_0.set_tribuf_6n(FURO_SPRITE0_GETn, YWAK_STORE0_INDX0.q());
    /*p30.ZUMU*/ top.SPR_TRI_INDX_1.set_tribuf_6n(FURO_SPRITE0_GETn, ZONY_STORE0_INDX1.q());
    /*p30.WOKO*/ top.SPR_TRI_INDX_2.set_tribuf_6n(FURO_SPRITE0_GETn, WYTE_STORE0_INDX2.q());
    /*p30.ZAVE*/ top.SPR_TRI_INDX_3.set_tribuf_6n(FURO_SPRITE0_GETn, YZEP_STORE0_INDX3.q());
    /*p30.ZECE*/ top.SPR_TRI_INDX_4.set_tribuf_6n(FURO_SPRITE0_GETn, YSOK_STORE0_INDX4.q());
    /*p30.ZETU*/ top.SPR_TRI_INDX_5.set_tribuf_6n(FURO_SPRITE0_GETn, YGUS_STORE0_INDX5.q());
    /*p30.GOFO*/ top.SPR_TRI_LINE_0.set_tribuf_6n(FURO_SPRITE0_GETn, FYHY_STORE0_LINE0.q());
    /*p30.WEHE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(FURO_SPRITE0_GETn, GYHO_STORE0_LINE1.q());
    /*p30.AJAL*/ top.SPR_TRI_LINE_2.set_tribuf_6n(FURO_SPRITE0_GETn, BOZU_STORE0_LINE2.q());
    /*p30.BUKY*/ top.SPR_TRI_LINE_3.set_tribuf_6n(FURO_SPRITE0_GETn, CUFO_STORE0_LINE3.q());

    /*p30.CUBO*/ top.SPR_TRI_INDX_0.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX5.q());
    /*p30.CELU*/ top.SPR_TRI_INDX_1.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX4.q());
    /*p30.CEGY*/ top.SPR_TRI_INDX_2.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX3.q());
    /*p30.BETY*/ top.SPR_TRI_INDX_3.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX2.q());
    /*p30.CYBY*/ top.SPR_TRI_INDX_4.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX1.q());
    /*p30.BEMO*/ top.SPR_TRI_INDX_5.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_INDX0.q());
    /*p30.BEFE*/ top.SPR_TRI_LINE_0.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_LINE0.q());
    /*p30.BYRO*/ top.SPR_TRI_LINE_1.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_LINE1.q());
    /*p30.BACO*/ top.SPR_TRI_LINE_2.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_LINE2.q());
    /*p30.AHUM*/ top.SPR_TRI_LINE_3.set_tribuf_6n(DYDO_SPRITE1_GETn, STORE1_LINE3.q());

    /*p30.AXEC*/ top.SPR_TRI_INDX_5.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX0.q());
    /*p30.CYRO*/ top.SPR_TRI_INDX_4.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX1.q());
    /*p30.CUVU*/ top.SPR_TRI_INDX_3.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX2.q());
    /*p30.APON*/ top.SPR_TRI_INDX_2.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX3.q());
    /*p30.AFOZ*/ top.SPR_TRI_INDX_1.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX4.q());
    /*p30.CUBE*/ top.SPR_TRI_INDX_0.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_INDX5.q());
    /*p30.ZABY*/ top.SPR_TRI_LINE_0.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_LINE0.q());
    /*p30.ZUKE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_LINE1.q());
    /*p30.WUXE*/ top.SPR_TRI_LINE_2.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_LINE2.q());
    /*p30.WERE*/ top.SPR_TRI_LINE_3.set_tribuf_6n(FAME_SPRITE2_GETn, STORE2_LINE3.q());

    /*p30.DEZU*/ top.SPR_TRI_INDX_5.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX0.q());
    /*p30.EFUD*/ top.SPR_TRI_INDX_4.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX1.q());
    /*p30.DONY*/ top.SPR_TRI_INDX_3.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX2.q());
    /*p30.DOWA*/ top.SPR_TRI_INDX_2.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX3.q());
    /*p30.DYGO*/ top.SPR_TRI_INDX_1.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX4.q());
    /*p30.ENAP*/ top.SPR_TRI_INDX_0.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_INDX5.q());
    /*p30.ZYPO*/ top.SPR_TRI_LINE_0.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_LINE0.q());
    /*p30.ZEXE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_LINE1.q());
    /*p30.YJEM*/ top.SPR_TRI_LINE_2.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_LINE2.q());
    /*p30.YWAV*/ top.SPR_TRI_LINE_3.set_tribuf_6n(GYMA_SPRITE3_GETn, STORE3_LINE4.q());

    /*p30.WAJA*/ top.SPR_TRI_INDX_5.set_tribuf_6n(GOWO_SPRITE4_GETn, XYNU.q());
    /*p30.WOXY*/ top.SPR_TRI_INDX_4.set_tribuf_6n(GOWO_SPRITE4_GETn, XEGE.q());
    /*p30.XYRE*/ top.SPR_TRI_INDX_3.set_tribuf_6n(GOWO_SPRITE4_GETn, XABO.q());
    /*p30.WERU*/ top.SPR_TRI_INDX_2.set_tribuf_6n(GOWO_SPRITE4_GETn, WANU.q());
    /*p30.WEPY*/ top.SPR_TRI_INDX_1.set_tribuf_6n(GOWO_SPRITE4_GETn, XEFE.q());
    /*p30.WUXU*/ top.SPR_TRI_INDX_0.set_tribuf_6n(GOWO_SPRITE4_GETn, XAVE.q());
    /*p30.BYDO*/ top.SPR_TRI_LINE_0.set_tribuf_6n(GOWO_SPRITE4_GETn, CUMU.q());
    /*p30.BUCE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(GOWO_SPRITE4_GETn, CAPO.q());
    /*p30.BOVE*/ top.SPR_TRI_LINE_2.set_tribuf_6n(GOWO_SPRITE4_GETn, CONO.q());
    /*p30.BEVY*/ top.SPR_TRI_LINE_3.set_tribuf_6n(GOWO_SPRITE4_GETn, CAJU.q());

    /*p30.DALO*/ top.SPR_TRI_INDX_5.set_tribuf_6n(GYGY_SPRITE5_GETn, EKAP.q());
    /*p30.DALY*/ top.SPR_TRI_INDX_4.set_tribuf_6n(GYGY_SPRITE5_GETn, ETAV.q());
    /*p30.DUZA*/ top.SPR_TRI_INDX_3.set_tribuf_6n(GYGY_SPRITE5_GETn, EBEX.q());
    /*p30.WAGA*/ top.SPR_TRI_INDX_2.set_tribuf_6n(GYGY_SPRITE5_GETn, GORU.q());
    /*p30.DYNY*/ top.SPR_TRI_INDX_1.set_tribuf_6n(GYGY_SPRITE5_GETn, ETYM.q());
    /*p30.DOBO*/ top.SPR_TRI_INDX_0.set_tribuf_6n(GYGY_SPRITE5_GETn, EKOP.q());
    /*p30.AWAT*/ top.SPR_TRI_LINE_0.set_tribuf_6n(GYGY_SPRITE5_GETn, ANED.q());
    /*p30.BACE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(GYGY_SPRITE5_GETn, ACEP.q());
    /*p30.BODU*/ top.SPR_TRI_LINE_2.set_tribuf_6n(GYGY_SPRITE5_GETn, ABUX.q());
    /*p30.BUJA*/ top.SPR_TRI_LINE_3.set_tribuf_6n(GYGY_SPRITE5_GETn, ABEG.q());

    /*p30.WOCY*/ top.SPR_TRI_INDX_5.set_tribuf_6n(XYME_SPRITE6_GETn, GECU.q());
    /*p30.ELYC*/ top.SPR_TRI_INDX_4.set_tribuf_6n(XYME_SPRITE6_GETn, FOXY.q());
    /*p30.WABO*/ top.SPR_TRI_INDX_3.set_tribuf_6n(XYME_SPRITE6_GETn, GOHU.q());
    /*p30.EZOC*/ top.SPR_TRI_INDX_2.set_tribuf_6n(XYME_SPRITE6_GETn, FOGO.q());
    /*p30.WYWY*/ top.SPR_TRI_INDX_1.set_tribuf_6n(XYME_SPRITE6_GETn, GACY.q());
    /*p30.WATO*/ top.SPR_TRI_INDX_0.set_tribuf_6n(XYME_SPRITE6_GETn, GABO.q());
    /*p30.ZUDO*/ top.SPR_TRI_LINE_0.set_tribuf_6n(XYME_SPRITE6_GETn, ZUBE.q());
    /*p30.YBUK*/ top.SPR_TRI_LINE_1.set_tribuf_6n(XYME_SPRITE6_GETn, ZUMY.q());
    /*p30.ZYTO*/ top.SPR_TRI_LINE_2.set_tribuf_6n(XYME_SPRITE6_GETn, ZEXO.q());
    /*p30.YKOZ*/ top.SPR_TRI_LINE_3.set_tribuf_6n(XYME_SPRITE6_GETn, ZAFU.q());

    /*p30.EVYT*/ top.SPR_TRI_INDX_5.set_tribuf_6n(GUGY_SPRITE7_GETn, FUZO.q());
    /*p30.WABA*/ top.SPR_TRI_INDX_4.set_tribuf_6n(GUGY_SPRITE7_GETn, GESY.q());
    /*p30.ETAD*/ top.SPR_TRI_INDX_3.set_tribuf_6n(GUGY_SPRITE7_GETn, FYSU.q());
    /*p30.ELEP*/ top.SPR_TRI_INDX_2.set_tribuf_6n(GUGY_SPRITE7_GETn, FEFA.q());
    /*p30.WYGO*/ top.SPR_TRI_INDX_1.set_tribuf_6n(GUGY_SPRITE7_GETn, GYNO.q());
    /*p30.WAKO*/ top.SPR_TRI_INDX_0.set_tribuf_6n(GUGY_SPRITE7_GETn, GULE.q());
    /*p30.WANA*/ top.SPR_TRI_LINE_0.set_tribuf_6n(GUGY_SPRITE7_GETn, XYGO.q());
    /*p30.WAXE*/ top.SPR_TRI_LINE_1.set_tribuf_6n(GUGY_SPRITE7_GETn, XYNA.q());
    /*p30.WABU*/ top.SPR_TRI_LINE_2.set_tribuf_6n(GUGY_SPRITE7_GETn, XAKU.q());
    /*p30.YPOZ*/ top.SPR_TRI_LINE_3.set_tribuf_6n(GUGY_SPRITE7_GETn, YGUM.q());

    /*p30.ADYB*/ top.SPR_TRI_INDX_5.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX5.q());
    /*p30.APOB*/ top.SPR_TRI_INDX_4.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX4.q());
    /*p30.APYV*/ top.SPR_TRI_INDX_3.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX3.q());
    /*p30.AFEN*/ top.SPR_TRI_INDX_2.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX2.q());
    /*p30.AKYH*/ top.SPR_TRI_INDX_1.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX1.q());
    /*p30.APOC*/ top.SPR_TRI_INDX_0.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_INDX0.q());
    /*p30.BUJY*/ top.SPR_TRI_LINE_0.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_LINE0.q());
    /*p30.BOSO*/ top.SPR_TRI_LINE_1.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_LINE1.q());
    /*p30.AHAC*/ top.SPR_TRI_LINE_2.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_LINE2.q());
    /*p30.BAZU*/ top.SPR_TRI_LINE_3.set_tribuf_6n(DENY_SPRITE8_GETn, STORE8_LINE3.q());

    /*p30.YHAL*/ top.SPR_TRI_INDX_5.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX0.q());
    /*p30.YRAD*/ top.SPR_TRI_INDX_4.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX1.q());
    /*p30.XYRA*/ top.SPR_TRI_INDX_3.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX2.q());
    /*p30.YNEV*/ top.SPR_TRI_INDX_2.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX3.q());
    /*p30.ZOJY*/ top.SPR_TRI_INDX_1.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX4.q());
    /*p30.ZARO*/ top.SPR_TRI_INDX_0.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_INDX5.q());
    /*p30.CAWO*/ top.SPR_TRI_LINE_0.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_LINE0.q());
    /*p30.BYME*/ top.SPR_TRI_LINE_1.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_LINE1.q());
    /*p30.COHO*/ top.SPR_TRI_LINE_2.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_LINE2.q());
    /*p30.GATE*/ top.SPR_TRI_LINE_3.set_tribuf_6n(FADO_SPRITE9_GETn, STORE9_LINE3.q());
  }

  //----------------------------------------
  // Sprite store setter

  {
    /*p29.DYWE*/ wire DYWE_STORE0_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, EBOJ_STORE0_RSTp.q());
    /*p29.EFEV*/ wire EFEV_STORE1_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, CEDY_STORE1_RSTp.q());
    /*p29.FOKO*/ wire FOKO_STORE2_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, EGAV_STORE2_RSTp.q());
    /*p29.GAKE*/ wire GAKE_STORE3_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, GOTA_STORE3_RSTp.q());
    /*p29.WOHU*/ wire WOHU_STORE4_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, XUDY_STORE4_RSTp.q());
    /*p29.FEVE*/ wire FEVE_STORE5_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, WAFY_STORE5_RSTp.q());
    /*p29.WACY*/ wire WACY_STORE6_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, WOMY_STORE6_RSTp.q());
    /*p29.GUKY*/ wire GUKY_STORE7_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, WAPO_STORE7_RSTp.q());
    /*p29.GORO*/ wire GORO_STORE8_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, EXUQ_STORE8_RSTp.q());
    /*p29.DUBU*/ wire DUBU_STORE9_RSTp = or(_DYBA_VID_LINE_TRIG_d4p, FONO_STORE9_RSTp.q());

    /*p29.DYNA*/ wire DYNA_STORE0_RSTn = not(DYWE_STORE0_RSTp);
    /*p29.DOKU*/ wire DOKU_STORE1_RSTn = not(EFEV_STORE1_RSTp);
    /*p29.GAMY*/ wire GAMY_STORE2_RSTn = not(FOKO_STORE2_RSTp);
    /*p29.WUPA*/ wire WUPA_STORE3_RSTn = not(GAKE_STORE3_RSTp);
    /*p29.WUNU*/ wire WUNU_STORE4_RSTn = not(WOHU_STORE4_RSTp);
    /*p29.EJAD*/ wire EJAD_STORE5_RSTn = not(FEVE_STORE5_RSTp);
    /*p29.XAHO*/ wire XAHO_STORE6_RSTn = not(WACY_STORE6_RSTp);
    /*p29.GAFY*/ wire GAFY_STORE7_RSTn = not(GUKY_STORE7_RSTp);
    /*p29.WUZO*/ wire WUZO_STORE8_RSTn = not(GORO_STORE8_RSTp);
    /*p29.DOSY*/ wire DOSY_STORE9_RSTn = not(DUBU_STORE9_RSTp);

    /*p29.EDEN*/ wire EDEN_SPRITE_COUNT0n = not(SPRITE_COUNT0.q());
    /*p29.CYPY*/ wire CYPY_SPRITE_COUNT1n = not(SPRITE_COUNT1.q());
    /*p29.CAPE*/ wire CAPE_SPRITE_COUNT2n = not(SPRITE_COUNT2.q());
    /*p29.CAXU*/ wire CAXU_SPRITE_COUNT3n = not(SPRITE_COUNT3.q());

    /*p29.FYCU*/ wire FYCU_SPRITE_COUNT0p = not(EDEN_SPRITE_COUNT0n);
    /*p29.FONE*/ wire FONE_SPRITE_COUNT1p = not(CYPY_SPRITE_COUNT1n);
    /*p29.EKUD*/ wire EKUD_SPRITE_COUNT2p = not(CAPE_SPRITE_COUNT2n);
    /*p29.ELYG*/ wire ELYG_SPRITE_COUNT3p = not(CAXU_SPRITE_COUNT3n);

    /*p29.DEZO*/ wire DEZO_STORE0_SELn = nand(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.CUVA*/ wire CUVA_STORE1_SELn = nand(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.GEBU*/ wire GEBU_STORE2_SELn = nand(EDEN_SPRITE_COUNT0n, FONE_SPRITE_COUNT1p, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.FOCO*/ wire FOCO_STORE3_SELn = nand(FYCU_SPRITE_COUNT0p, FONE_SPRITE_COUNT1p, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.CUPE*/ wire CUPE_STORE4_SELn = nand(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.CUGU*/ wire CUGU_STORE5_SELn = nand(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.WOMU*/ wire WOMU_STORE6_SELn = nand(EDEN_SPRITE_COUNT0n, FONE_SPRITE_COUNT1p, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.GUNA*/ wire GUNA_STORE7_SELn = nand(FYCU_SPRITE_COUNT0p, FONE_SPRITE_COUNT1p, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.DEWY*/ wire DEWY_STORE8_SELn = nand(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, ELYG_SPRITE_COUNT3p);
    /*p29.DOGU*/ wire DOGU_STORE9_SELn = nand(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, ELYG_SPRITE_COUNT3p);

    // Sprite stores latch their input when their SELn signal goes _high_
    /*p29.CEMY*/ wire CEMY_STORE0_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, DEZO_STORE0_SELn);
    /*p29.BYBY*/ wire BYBY_STORE1_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, CUVA_STORE1_SELn);
    /*p29.WYXO*/ wire WYXO_STORE2_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, GEBU_STORE2_SELn);
    /*p29.GUVE*/ wire GUVE_STORE3_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, FOCO_STORE3_SELn);
    /*p29.CECU*/ wire CECU_STORE4_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, CUPE_STORE4_SELn);
    /*p29.CADO*/ wire CADO_STORE5_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, CUGU_STORE5_SELn);
    /*p29.XUJO*/ wire XUJO_STORE6_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, WOMU_STORE6_SELn);
    /*p29.GAPE*/ wire GAPE_STORE7_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, GUNA_STORE7_SELn);
    /*p29.CAHO*/ wire CAHO_STORE8_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, DEWY_STORE8_SELn);
    /*p29.CATO*/ wire CATO_STORE9_CLKp = or(_DYTY_STORE_ENn_xxCDxxGH, DOGU_STORE9_SELn);

    /*p29.DYHU*/ wire DYHU_STORE0_CLKn = not(CEMY_STORE0_CLKp);
    /*p29.BUCO*/ wire BUCO_STORE1_CLKn = not(BYBY_STORE1_CLKp);
    /*p29.GYFO*/ wire GYFO_STORE2_CLKn = not(WYXO_STORE2_CLKp);
    /*p29.GUSA*/ wire GUSA_STORE3_CLKn = not(GUVE_STORE3_CLKp);
    /*p29.DUKE*/ wire DUKE_STORE4_CLKn = not(CECU_STORE4_CLKp);
    /*p29.BEDE*/ wire BEDE_STORE5_CLKn = not(CADO_STORE5_CLKp);
    /*p29.WEKA*/ wire WEKA_STORE6_CLKn = not(XUJO_STORE6_CLKp);
    /*p29.GYVO*/ wire GYVO_STORE7_CLKn = not(GAPE_STORE7_CLKp);
    /*p29.BUKA*/ wire BUKA_STORE8_CLKn = not(CAHO_STORE8_CLKp);
    /*p29.DECU*/ wire DECU_STORE9_CLKn = not(CATO_STORE9_CLKp);

    // 10 sprite stores

    /*p31.ZAGO*/ wire ZAGO_SPRITE_X0 = not(!top.YLOR_SPRITE_X0());
    /*p31.ZOCY*/ wire ZOCY_SPRITE_X1 = not(!top.ZYTY_SPRITE_X1());
    /*p31.YPUR*/ wire YPUR_SPRITE_X2 = not(!top.ZYVE_SPRITE_X2());
    /*p31.YVOK*/ wire YVOK_SPRITE_X3 = not(!top.ZEZY_SPRITE_X3());
    /*p31.COSE*/ wire COSE_SPRITE_X4 = not(!top.GOMO_SPRITE_X4());
    /*p31.AROP*/ wire AROP_SPRITE_X5 = not(!top.BAXO_SPRITE_X5());
    /*p31.XATU*/ wire XATU_SPRITE_X6 = not(!top.YZOS_SPRITE_X6());
    /*p31.BADY*/ wire BADY_SPRITE_X7 = not(!top.DEPO_SPRITE_X7());

    /*p29.GENY*/ wire GENY_STORE0_CLKp = not(DYHU_STORE0_CLKn);
    /*p29.ENOB*/ wire ENOB_STORE0_CLKp = not(DYHU_STORE0_CLKn);
    /*p29.FUXU*/ wire FUXU_STORE0_CLKp = not(DYHU_STORE0_CLKn);
    /*p30.YWAK*/ YWAK_STORE0_INDX0.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_0.q());
    /*p30.ZONY*/ ZONY_STORE0_INDX1.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_1.q());
    /*p30.WYTE*/ WYTE_STORE0_INDX2.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_2.q());
    /*p30.YZEP*/ YZEP_STORE0_INDX3.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_3.q());
    /*p30.YSOK*/ YSOK_STORE0_INDX4.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_4.q());
    /*p30.YGUS*/ YGUS_STORE0_INDX5.set(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, top.SPR_TRI_INDX_5.q());
    /*p30.FYHY*/ FYHY_STORE0_LINE0.set(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, top.SPR_TRI_LINE_0.q());
    /*p30.GYHO*/ GYHO_STORE0_LINE1.set(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, top.SPR_TRI_LINE_1.q());
    /*p30.BOZU*/ BOZU_STORE0_LINE2.set(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, top.SPR_TRI_LINE_2.q());
    /*p30.CUFO*/ CUFO_STORE0_LINE3.set(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, top.SPR_TRI_LINE_3.q());
    /*p31.XEPE*/ XEPE_STORE0_X0   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, ZAGO_SPRITE_X0);
    /*p31.YLAH*/ YLAH_STORE0_X1   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, ZOCY_SPRITE_X1);
    /*p31.ZOLA*/ ZOLA_STORE0_X2   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, YPUR_SPRITE_X2);
    /*p31.ZULU*/ ZULU_STORE0_X3   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, YVOK_SPRITE_X3);
    /*p31.WELO*/ WELO_STORE0_X4   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, COSE_SPRITE_X4);
    /*p31.XUNY*/ XUNY_STORE0_X5   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, AROP_SPRITE_X5);
    /*p31.WOTE*/ WOTE_STORE0_X6   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, XATU_SPRITE_X6);
    /*p31.XAKO*/ XAKO_STORE0_X7   .set(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, BADY_SPRITE_X7);

    /*p29.BYVY*/ wire BYVU_STORE1_CLKp = not(BUCO_STORE1_CLKn);
    /*p29.AHOF*/ wire AHOF_STORE1_CLKp = not(BUCO_STORE1_CLKn);
    /*p29.ASYS*/ wire ASYS_STORE1_CLKp = not(BUCO_STORE1_CLKn);
    /*p30.CAJY*/ STORE1_INDX0.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_5.q());
    /*p30.CUZA*/ STORE1_INDX1.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_4.q());
    /*p30.COMA*/ STORE1_INDX2.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_3.q());
    /*p30.CUFA*/ STORE1_INDX3.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_2.q());
    /*p30.CEBO*/ STORE1_INDX4.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_1.q());
    /*p30.CADU*/ STORE1_INDX5.set(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, top.SPR_TRI_INDX_0.q());
    /*p30.ABUG*/ STORE1_LINE0.set(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, top.SPR_TRI_LINE_0.q());
    /*p30.AMES*/ STORE1_LINE1.set(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, top.SPR_TRI_LINE_1.q());
    /*p30.ABOP*/ STORE1_LINE2.set(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, top.SPR_TRI_LINE_2.q());
    /*p30.AROF*/ STORE1_LINE3.set(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, top.SPR_TRI_LINE_3.q());
    /*p31.DANY*/ STORE1_X0   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, ZAGO_SPRITE_X0);
    /*p31.DUKO*/ STORE1_X1   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, ZOCY_SPRITE_X1);
    /*p31.DESU*/ STORE1_X2   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, YPUR_SPRITE_X2);
    /*p31.DAZO*/ STORE1_X3   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, YVOK_SPRITE_X3);
    /*p31.DAKE*/ STORE1_X4   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, COSE_SPRITE_X4);
    /*p31.CESO*/ STORE1_X5   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, AROP_SPRITE_X5);
    /*p31.DYFU*/ STORE1_X6   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, XATU_SPRITE_X6);
    /*p31.CUSY*/ STORE1_X7   .set(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, BADY_SPRITE_X7);

    /*p29.BUZY*/ wire BUZY_STORE2_CLKp = not(GYFO_STORE2_CLKn);
    /*p29.FUKE*/ wire FUKE_STORE2_CLKp = not(GYFO_STORE2_CLKn);
    /*p29.CACU*/ wire CACU_STORE2_CLKp = not(GYFO_STORE2_CLKn);
    /*p30.BOXA*/ STORE2_INDX0.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_5.q());
    /*p30.BUNA*/ STORE2_INDX1.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_4.q());
    /*p30.BULU*/ STORE2_INDX2.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_3.q());
    /*p30.BECA*/ STORE2_INDX3.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_2.q());
    /*p30.BYHU*/ STORE2_INDX4.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_1.q());
    /*p30.BUHE*/ STORE2_INDX5.set(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, top.SPR_TRI_INDX_0.q());
    /*p30.YKUK*/ STORE2_LINE0.set(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, top.SPR_TRI_LINE_0.q());
    /*p30.YLOV*/ STORE2_LINE1.set(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, top.SPR_TRI_LINE_1.q());
    /*p30.XAZY*/ STORE2_LINE2.set(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, top.SPR_TRI_LINE_2.q());
    /*p30.XOSY*/ STORE2_LINE3.set(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, top.SPR_TRI_LINE_3.q());
    /*p31.FOKA*/ STORE2_X0   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, ZAGO_SPRITE_X0);
    /*p31.FYTY*/ STORE2_X1   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, ZOCY_SPRITE_X1);
    /*p31.FUBY*/ STORE2_X2   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, YPUR_SPRITE_X2);
    /*p31.GOXU*/ STORE2_X3   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, YVOK_SPRITE_X3);
    /*p31.DUHY*/ STORE2_X4   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, COSE_SPRITE_X4);
    /*p31.EJUF*/ STORE2_X5   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, AROP_SPRITE_X5);
    /*p31.ENOR*/ STORE2_X6   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, XATU_SPRITE_X6);
    /*p31.DEPY*/ STORE2_X7   .set(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, BADY_SPRITE_X7);

    /*p29.FEKA*/ wire FEKA = not(GUSA_STORE3_CLKn);
    /*p29.XYHA*/ wire XYHA = not(GUSA_STORE3_CLKn);
    /*p29.YFAG*/ wire YFAG = not(GUSA_STORE3_CLKn);
    /*p30.DAFU*/ STORE3_INDX0.set(FEKA, !FEKA, top.SPR_TRI_INDX_5.q());
    /*p30.DEBA*/ STORE3_INDX1.set(FEKA, !FEKA, top.SPR_TRI_INDX_4.q());
    /*p30.DUHA*/ STORE3_INDX2.set(FEKA, !FEKA, top.SPR_TRI_INDX_3.q());
    /*p30.DUNY*/ STORE3_INDX3.set(FEKA, !FEKA, top.SPR_TRI_INDX_2.q());
    /*p30.DESE*/ STORE3_INDX4.set(FEKA, !FEKA, top.SPR_TRI_INDX_1.q());
    /*p30.DEVY*/ STORE3_INDX5.set(FEKA, !FEKA, top.SPR_TRI_INDX_0.q());
    /*p30.ZURY*/ STORE3_LINE0.set(XYHA, !XYHA, top.SPR_TRI_LINE_0.q());
    /*p30.ZURO*/ STORE3_LINE1.set(XYHA, !XYHA, top.SPR_TRI_LINE_1.q());
    /*p30.ZENE*/ STORE3_LINE2.set(XYHA, !XYHA, top.SPR_TRI_LINE_2.q());
    /*p30.ZYLU*/ STORE3_LINE4.set(XYHA, !XYHA, top.SPR_TRI_LINE_3.q());
    /*p31.XOLY*/ STORE3_X0   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, ZAGO_SPRITE_X0);
    /*p31.XYBA*/ STORE3_X1   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, ZOCY_SPRITE_X1);
    /*p31.XABE*/ STORE3_X2   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, YPUR_SPRITE_X2);
    /*p31.XEKA*/ STORE3_X3   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, YVOK_SPRITE_X3);
    /*p31.XOMY*/ STORE3_X4   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, COSE_SPRITE_X4);
    /*p31.WUHA*/ STORE3_X5   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, AROP_SPRITE_X5);
    /*p31.WYNA*/ STORE3_X6   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, XATU_SPRITE_X6);
    /*p31.WECO*/ STORE3_X7   .set(YFAG, !YFAG, WUPA_STORE3_RSTn, BADY_SPRITE_X7);

    /*p29.WOFO*/ wire WOFO = not(DUKE_STORE4_CLKn);
    /*p29.WYLU*/ wire WYLU = not(DUKE_STORE4_CLKn);
    /*p29.EWOT*/ wire EWOT = not(DUKE_STORE4_CLKn);
    /*p30.XYNU*/ XYNU     .set(WYLU, !WYLU, top.SPR_TRI_INDX_5.q());
    /*p30.XEGE*/ XEGE     .set(WYLU, !WYLU, top.SPR_TRI_INDX_4.q());
    /*p30.XABO*/ XABO     .set(WYLU, !WYLU, top.SPR_TRI_INDX_3.q());
    /*p30.WANU*/ WANU     .set(WYLU, !WYLU, top.SPR_TRI_INDX_2.q());
    /*p30.XEFE*/ XEFE     .set(WYLU, !WYLU, top.SPR_TRI_INDX_1.q());
    /*p30.XAVE*/ XAVE     .set(WYLU, !WYLU, top.SPR_TRI_INDX_0.q());
    /*p30.CUMU*/ CUMU     .set(EWOT, !EWOT, top.SPR_TRI_LINE_0.q());
    /*p30.CAPO*/ CAPO     .set(EWOT, !EWOT, top.SPR_TRI_LINE_1.q());
    /*p30.CONO*/ CONO     .set(EWOT, !EWOT, top.SPR_TRI_LINE_2.q());
    /*p30.CAJU*/ CAJU     .set(EWOT, !EWOT, top.SPR_TRI_LINE_3.q());
    /*p31.WEDU*/ STORE4_X0.set(WOFO, !WOFO, WUNU_STORE4_RSTn, ZAGO_SPRITE_X0);
    /*p31.YGAJ*/ STORE4_X1.set(WOFO, !WOFO, WUNU_STORE4_RSTn, ZOCY_SPRITE_X1);
    /*p31.ZYJO*/ STORE4_X2.set(WOFO, !WOFO, WUNU_STORE4_RSTn, YPUR_SPRITE_X2);
    /*p31.XURY*/ STORE4_X3.set(WOFO, !WOFO, WUNU_STORE4_RSTn, YVOK_SPRITE_X3);
    /*p31.YBED*/ STORE4_X4.set(WOFO, !WOFO, WUNU_STORE4_RSTn, COSE_SPRITE_X4);
    /*p31.ZALA*/ STORE4_X5.set(WOFO, !WOFO, WUNU_STORE4_RSTn, AROP_SPRITE_X5);
    /*p31.WYDE*/ STORE4_X6.set(WOFO, !WOFO, WUNU_STORE4_RSTn, XATU_SPRITE_X6);
    /*p31.XEPA*/ STORE4_X7.set(WOFO, !WOFO, WUNU_STORE4_RSTn, BADY_SPRITE_X7);

    /*p29.CYLA*/ wire CYLA = not(BEDE_STORE5_CLKn);
    /*p29.DYMO*/ wire DYMO = not(BEDE_STORE5_CLKn);
    /*p29.BUCY*/ wire BUCY = not(BEDE_STORE5_CLKn);
    /*p30.EKAP*/ EKAP     .set(DYMO, !DYMO, top.SPR_TRI_INDX_5.q());
    /*p30.ETAV*/ ETAV     .set(DYMO, !DYMO, top.SPR_TRI_INDX_4.q());
    /*p30.EBEX*/ EBEX     .set(DYMO, !DYMO, top.SPR_TRI_INDX_3.q());
    /*p30.GORU*/ GORU     .set(DYMO, !DYMO, top.SPR_TRI_INDX_2.q());
    /*p30.ETYM*/ ETYM     .set(DYMO, !DYMO, top.SPR_TRI_INDX_1.q());
    /*p30.EKOP*/ EKOP     .set(DYMO, !DYMO, top.SPR_TRI_INDX_0.q());
    /*p30.ANED*/ ANED     .set(BUCY, !BUCY, top.SPR_TRI_LINE_0.q());
    /*p30.ACEP*/ ACEP     .set(BUCY, !BUCY, top.SPR_TRI_LINE_1.q());
    /*p30.ABUX*/ ABUX     .set(BUCY, !BUCY, top.SPR_TRI_LINE_2.q());
    /*p30.ABEG*/ ABEG     .set(BUCY, !BUCY, top.SPR_TRI_LINE_3.q());
    /*p31.FUSA*/ STORE5_X0.set(CYLA, !CYLA, EJAD_STORE5_RSTn, ZAGO_SPRITE_X0);
    /*p31.FAXA*/ STORE5_X1.set(CYLA, !CYLA, EJAD_STORE5_RSTn, ZOCY_SPRITE_X1);
    /*p31.FOZY*/ STORE5_X2.set(CYLA, !CYLA, EJAD_STORE5_RSTn, YPUR_SPRITE_X2);
    /*p31.FESY*/ STORE5_X3.set(CYLA, !CYLA, EJAD_STORE5_RSTn, YVOK_SPRITE_X3);
    /*p31.CYWE*/ STORE5_X4.set(CYLA, !CYLA, EJAD_STORE5_RSTn, COSE_SPRITE_X4);
    /*p31.DYBY*/ STORE5_X5.set(CYLA, !CYLA, EJAD_STORE5_RSTn, AROP_SPRITE_X5);
    /*p31.DURY*/ STORE5_X6.set(CYLA, !CYLA, EJAD_STORE5_RSTn, XATU_SPRITE_X6);
    /*p31.CUVY*/ STORE5_X7.set(CYLA, !CYLA, EJAD_STORE5_RSTn, BADY_SPRITE_X7);

    /*p29.ZAPE*/ wire ZAPE = not(WEKA_STORE6_CLKn);
    /*p29.WUSE*/ wire WUSE = not(WEKA_STORE6_CLKn);
    /*p29.ZURU*/ wire ZURU = not(WEKA_STORE6_CLKn);
    /*p30.GECU*/ GECU     .set(WUSE, !WUSE, top.SPR_TRI_INDX_5.q());
    /*p30.FOXY*/ FOXY     .set(WUSE, !WUSE, top.SPR_TRI_INDX_4.q());
    /*p30.GOHU*/ GOHU     .set(WUSE, !WUSE, top.SPR_TRI_INDX_3.q());
    /*p30.FOGO*/ FOGO     .set(WUSE, !WUSE, top.SPR_TRI_INDX_2.q());
    /*p30.GACY*/ GACY     .set(WUSE, !WUSE, top.SPR_TRI_INDX_1.q());
    /*p30.GABO*/ GABO     .set(WUSE, !WUSE, top.SPR_TRI_INDX_0.q());
    /*p30.ZUBE*/ ZUBE     .set(ZURU, !ZURU, top.SPR_TRI_LINE_0.q());
    /*p30.ZUMY*/ ZUMY     .set(ZURU, !ZURU, top.SPR_TRI_LINE_1.q());
    /*p30.ZEXO*/ ZEXO     .set(ZURU, !ZURU, top.SPR_TRI_LINE_2.q());
    /*p30.ZAFU*/ ZAFU     .set(ZURU, !ZURU, top.SPR_TRI_LINE_3.q());
    /*p31.YCOL*/ STORE6_X0.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, ZAGO_SPRITE_X0);
    /*p31.YRAC*/ STORE6_X1.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, ZOCY_SPRITE_X1);
    /*p31.YMEM*/ STORE6_X2.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, YPUR_SPRITE_X2);
    /*p31.YVAG*/ STORE6_X3.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, YVOK_SPRITE_X3);
    /*p31.ZOLY*/ STORE6_X4.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, COSE_SPRITE_X4);
    /*p31.ZOGO*/ STORE6_X5.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, AROP_SPRITE_X5);
    /*p31.ZECU*/ STORE6_X6.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, XATU_SPRITE_X6);
    /*p31.ZESA*/ STORE6_X7.set(ZAPE, !ZAPE, XAHO_STORE6_RSTn, BADY_SPRITE_X7);

    /*p29.GECY*/ wire GECY = not(GYVO_STORE7_CLKn);
    /*p29.FEFO*/ wire FEFO = not(GYVO_STORE7_CLKn);
    /*p29.WABE*/ wire WABE = not(GYVO_STORE7_CLKn);
    /*p30.FUZO*/ FUZO     .set(FEFO, !FEFO, top.SPR_TRI_INDX_5.q());
    /*p30.GESY*/ GESY     .set(FEFO, !FEFO, top.SPR_TRI_INDX_4.q());
    /*p30.FYSU*/ FYSU     .set(FEFO, !FEFO, top.SPR_TRI_INDX_3.q());
    /*p30.FEFA*/ FEFA     .set(FEFO, !FEFO, top.SPR_TRI_INDX_2.q());
    /*p30.GYNO*/ GYNO     .set(FEFO, !FEFO, top.SPR_TRI_INDX_1.q());
    /*p30.GULE*/ GULE     .set(FEFO, !FEFO, top.SPR_TRI_INDX_0.q());
    /*p30.XYGO*/ XYGO     .set(WABE, !WABE, top.SPR_TRI_LINE_0.q());
    /*p30.XYNA*/ XYNA     .set(WABE, !WABE, top.SPR_TRI_LINE_1.q());
    /*p30.XAKU*/ XAKU     .set(WABE, !WABE, top.SPR_TRI_LINE_2.q());
    /*p30.YGUM*/ YGUM     .set(WABE, !WABE, top.SPR_TRI_LINE_3.q());
    /*p31.ERAZ*/ STORE7_X0.set(GECY, !GECY, GAFY_STORE7_RSTn, ZAGO_SPRITE_X0);
    /*p31.EPUM*/ STORE7_X1.set(GECY, !GECY, GAFY_STORE7_RSTn, ZOCY_SPRITE_X1);
    /*p31.EROL*/ STORE7_X2.set(GECY, !GECY, GAFY_STORE7_RSTn, YPUR_SPRITE_X2);
    /*p31.EHYN*/ STORE7_X3.set(GECY, !GECY, GAFY_STORE7_RSTn, YVOK_SPRITE_X3);
    /*p31.FAZU*/ STORE7_X4.set(GECY, !GECY, GAFY_STORE7_RSTn, COSE_SPRITE_X4);
    /*p31.FAXE*/ STORE7_X5.set(GECY, !GECY, GAFY_STORE7_RSTn, AROP_SPRITE_X5);
    /*p31.EXUK*/ STORE7_X6.set(GECY, !GECY, GAFY_STORE7_RSTn, XATU_SPRITE_X6);
    /*p31.FEDE*/ STORE7_X7.set(GECY, !GECY, GAFY_STORE7_RSTn, BADY_SPRITE_X7);

    /*p29.CEXU*/ wire CEXU = not(BUKA_STORE8_CLKn);
    /*p29.AKOL*/ wire AKOL = not(BUKA_STORE8_CLKn);
    /*p29.BYMY*/ wire BYMY = not(BUKA_STORE8_CLKn);
    /*p30.AXUV*/ STORE8_INDX5.set(AKOL, !AKOL, top.SPR_TRI_INDX_5.q());
    /*p30.BADA*/ STORE8_INDX4.set(AKOL, !AKOL, top.SPR_TRI_INDX_4.q());
    /*p30.APEV*/ STORE8_INDX3.set(AKOL, !AKOL, top.SPR_TRI_INDX_3.q());
    /*p30.BADO*/ STORE8_INDX2.set(AKOL, !AKOL, top.SPR_TRI_INDX_2.q());
    /*p30.BEXY*/ STORE8_INDX1.set(AKOL, !AKOL, top.SPR_TRI_INDX_1.q());
    /*p30.BYHE*/ STORE8_INDX0.set(AKOL, !AKOL, top.SPR_TRI_INDX_0.q());
    /*p30.AFYM*/ STORE8_LINE0.set(BYMY, !BYMY, top.SPR_TRI_LINE_0.q());
    /*p30.AZAP*/ STORE8_LINE1.set(BYMY, !BYMY, top.SPR_TRI_LINE_1.q());
    /*p30.AFUT*/ STORE8_LINE2.set(BYMY, !BYMY, top.SPR_TRI_LINE_2.q());
    /*p30.AFYX*/ STORE8_LINE3.set(BYMY, !BYMY, top.SPR_TRI_LINE_3.q());
    /*p31.GAVY*/ STORE8_X4   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, ZAGO_SPRITE_X0);
    /*p31.GYPU*/ STORE8_X5   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, ZOCY_SPRITE_X1);
    /*p31.GADY*/ STORE8_X6   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, YPUR_SPRITE_X2);
    /*p31.GAZA*/ STORE8_X7   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, YVOK_SPRITE_X3);
    /*p31.EZUF*/ STORE8_X0   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, COSE_SPRITE_X4);
    /*p31.ENAD*/ STORE8_X1   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, AROP_SPRITE_X5);
    /*p31.EBOW*/ STORE8_X2   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, XATU_SPRITE_X6);
    /*p31.FYCA*/ STORE8_X3   .set(CEXU, !CEXU, WUZO_STORE8_RSTn, BADY_SPRITE_X7);

    /*p29.WEME*/ wire STORE9_CLKa = not(DECU_STORE9_CLKn);
    /*p29.WUFA*/ wire STORE9_CLKb = not(DECU_STORE9_CLKn);
    /*p29.FAKA*/ wire STORE9_CLKc = not(DECU_STORE9_CLKn);
    /*p30.XUFO*/ STORE9_INDX0.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_5.q());
    /*p30.XUTE*/ STORE9_INDX1.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_4.q());
    /*p30.XOTU*/ STORE9_INDX2.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_3.q());
    /*p30.XYFE*/ STORE9_INDX3.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_2.q());
    /*p30.YZOR*/ STORE9_INDX4.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_1.q());
    /*p30.YBER*/ STORE9_INDX5.set(STORE9_CLKb, !STORE9_CLKb, top.SPR_TRI_INDX_0.q());
    /*p30.DEWU*/ STORE9_LINE0.set(STORE9_CLKc, !STORE9_CLKc, top.SPR_TRI_LINE_0.q());
    /*p30.CANA*/ STORE9_LINE1.set(STORE9_CLKc, !STORE9_CLKc, top.SPR_TRI_LINE_1.q());
    /*p30.DYSY*/ STORE9_LINE2.set(STORE9_CLKc, !STORE9_CLKc, top.SPR_TRI_LINE_2.q());
    /*p30.FOFO*/ STORE9_LINE3.set(STORE9_CLKc, !STORE9_CLKc, top.SPR_TRI_LINE_3.q());
    /*p31.XUVY*/ STORE9_X0   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, ZAGO_SPRITE_X0);
    /*p31.XERE*/ STORE9_X1   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, ZOCY_SPRITE_X1);
    /*p31.XUZO*/ STORE9_X2   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, YPUR_SPRITE_X2);
    /*p31.XEXA*/ STORE9_X3   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, YVOK_SPRITE_X3);
    /*p31.YPOD*/ STORE9_X4   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, COSE_SPRITE_X4);
    /*p31.YROP*/ STORE9_X5   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, AROP_SPRITE_X5);
    /*p31.YNEP*/ STORE9_X6   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, XATU_SPRITE_X6);
    /*p31.YZOF*/ STORE9_X7   .set(STORE9_CLKa, !STORE9_CLKa, DOSY_STORE9_RSTn, BADY_SPRITE_X7);
  }
}

//------------------------------------------------------------------------------

SignalHash SpriteStoreRegisters::commit(SchematicTop& top) {
  SignalHash hash;
  /*p29.FEPO*/ hash << FEPO_STORE_MATCHp.commit();

  /*p29.YDUG*/ hash << STORE0_MATCHn.commit();
  /*p29.DYDU*/ hash << STORE1_MATCHn.commit();
  /*p29.DEGO*/ hash << STORE2_MATCHn.commit();
  /*p29.YLOZ*/ hash << STORE3_MATCHn.commit();
  /*p29.XAGE*/ hash << STORE4_MATCHn.commit();
  /*p29.EGOM*/ hash << STORE5_MATCHn.commit();
  /*p29.YBEZ*/ hash << STORE6_MATCHn.commit();
  /*p29.DYKA*/ hash << STORE7_MATCHn.commit();
  /*p29.EFYL*/ hash << STORE8_MATCHn.commit();
  /*p29.YGEM*/ hash << STORE9_MATCHn.commit();

  /*p29.DEZY*/ hash << DEZY_STORE_ENn_SYNC.commit();
  /*p29.BESE*/ hash << SPRITE_COUNT0.commit();
  /*p29.CUXY*/ hash << SPRITE_COUNT1.commit();
  /*p29.BEGO*/ hash << SPRITE_COUNT2.commit();
  /*p29.DYBE*/ hash << SPRITE_COUNT3.commit();
  /*p29.EBOJ*/ hash << EBOJ_STORE0_RSTp.commit();
  /*p30.YGUS*/ hash << YGUS_STORE0_INDX5.commit();
  /*p30.YSOK*/ hash << YSOK_STORE0_INDX4.commit();
  /*p30.YZEP*/ hash << YZEP_STORE0_INDX3.commit();
  /*p30.WYTE*/ hash << WYTE_STORE0_INDX2.commit();
  /*p30.ZONY*/ hash << ZONY_STORE0_INDX1.commit();
  /*p30.YWAK*/ hash << YWAK_STORE0_INDX0.commit();
  /*p30.FYHY*/ hash << FYHY_STORE0_LINE0.commit();
  /*p30.GYHO*/ hash << GYHO_STORE0_LINE1.commit();
  /*p30.BOZU*/ hash << BOZU_STORE0_LINE2.commit();
  /*p30.CUFO*/ hash << CUFO_STORE0_LINE3.commit();
  /*p31.XEPE*/ hash << XEPE_STORE0_X0.commit();
  /*p31.YLAH*/ hash << YLAH_STORE0_X1.commit();
  /*p31.ZOLA*/ hash << ZOLA_STORE0_X2.commit();
  /*p31.ZULU*/ hash << ZULU_STORE0_X3.commit();
  /*p31.WELO*/ hash << WELO_STORE0_X4.commit();
  /*p31.XUNY*/ hash << XUNY_STORE0_X5.commit();
  /*p31.WOTE*/ hash << WOTE_STORE0_X6.commit();
  /*p31.XAKO*/ hash << XAKO_STORE0_X7.commit();
  /*p29.CEDY*/ hash << CEDY_STORE1_RSTp.commit();
  /*p30.CAJY*/ hash << STORE1_INDX0.commit();
  /*p30.CUZA*/ hash << STORE1_INDX1.commit();
  /*p30.COMA*/ hash << STORE1_INDX2.commit();
  /*p30.CUFA*/ hash << STORE1_INDX3.commit();
  /*p30.CEBO*/ hash << STORE1_INDX4.commit();
  /*p30.CADU*/ hash << STORE1_INDX5.commit();
  /*p30.ABUG*/ hash << STORE1_LINE0.commit();
  /*p30.AMES*/ hash << STORE1_LINE1.commit();
  /*p30.ABOP*/ hash << STORE1_LINE2.commit();
  /*p30.AROF*/ hash << STORE1_LINE3.commit();
  /*p31.DANY*/ hash << STORE1_X0.commit();
  /*p31.DUKO*/ hash << STORE1_X1.commit();
  /*p31.DESU*/ hash << STORE1_X2.commit();
  /*p31.DAZO*/ hash << STORE1_X3.commit();
  /*p31.DAKE*/ hash << STORE1_X4.commit();
  /*p31.CESO*/ hash << STORE1_X5.commit();
  /*p31.DYFU*/ hash << STORE1_X6.commit();
  /*p31.CUSY*/ hash << STORE1_X7.commit();
  /*p29.EGAV*/ hash << EGAV_STORE2_RSTp.commit();
  /*p30.BOXA*/ hash << STORE2_INDX0.commit();
  /*p30.BUNA*/ hash << STORE2_INDX1.commit();
  /*p30.BULU*/ hash << STORE2_INDX2.commit();
  /*p30.BECA*/ hash << STORE2_INDX3.commit();
  /*p30.BYHU*/ hash << STORE2_INDX4.commit();
  /*p30.BUHE*/ hash << STORE2_INDX5.commit();
  /*p30.YKUK*/ hash << STORE2_LINE0.commit();
  /*p30.YLOV*/ hash << STORE2_LINE1.commit();
  /*p30.XAZY*/ hash << STORE2_LINE2.commit();
  /*p30.XOSY*/ hash << STORE2_LINE3.commit();
  /*p31.FOKA*/ hash << STORE2_X0.commit();
  /*p31.FYTY*/ hash << STORE2_X1.commit();
  /*p31.FUBY*/ hash << STORE2_X2.commit();
  /*p31.GOXU*/ hash << STORE2_X3.commit();
  /*p31.DUHY*/ hash << STORE2_X4.commit();
  /*p31.EJUF*/ hash << STORE2_X5.commit();
  /*p31.ENOR*/ hash << STORE2_X6.commit();
  /*p31.DEPY*/ hash << STORE2_X7.commit();
  /*p29.GOTA*/ hash << GOTA_STORE3_RSTp.commit();
  /*p30.DAFU*/ hash << STORE3_INDX0.commit();
  /*p30.DEBA*/ hash << STORE3_INDX1.commit();
  /*p30.DUHA*/ hash << STORE3_INDX2.commit();
  /*p30.DUNY*/ hash << STORE3_INDX3.commit();
  /*p30.DESE*/ hash << STORE3_INDX4.commit();
  /*p30.DEVY*/ hash << STORE3_INDX5.commit();
  /*p30.ZURY*/ hash << STORE3_LINE0.commit();
  /*p30.ZURO*/ hash << STORE3_LINE1.commit();
  /*p30.ZENE*/ hash << STORE3_LINE2.commit();
  /*p30.ZYLU*/ hash << STORE3_LINE4.commit();
  /*p31.XOLY*/ hash << STORE3_X0.commit();
  /*p31.XYBA*/ hash << STORE3_X1.commit();
  /*p31.XABE*/ hash << STORE3_X2.commit();
  /*p31.XEKA*/ hash << STORE3_X3.commit();
  /*p31.XOMY*/ hash << STORE3_X4.commit();
  /*p31.WUHA*/ hash << STORE3_X5.commit();
  /*p31.WYNA*/ hash << STORE3_X6.commit();
  /*p31.WECO*/ hash << STORE3_X7.commit();
  /*p29.XUDY*/ hash << XUDY_STORE4_RSTp.commit();
  /*p31.WEDU*/ hash << STORE4_X0.commit();
  /*p31.YGAJ*/ hash << STORE4_X1.commit();
  /*p31.ZYJO*/ hash << STORE4_X2.commit();
  /*p31.XURY*/ hash << STORE4_X3.commit();
  /*p31.YBED*/ hash << STORE4_X4.commit();
  /*p31.ZALA*/ hash << STORE4_X5.commit();
  /*p31.WYDE*/ hash << STORE4_X6.commit();
  /*p31.XEPA*/ hash << STORE4_X7.commit();
  /*p30.XYNU*/ hash << XYNU.commit();
  /*p30.XEGE*/ hash << XEGE.commit();
  /*p30.XABO*/ hash << XABO.commit();
  /*p30.WANU*/ hash << WANU.commit();
  /*p30.XEFE*/ hash << XEFE.commit();
  /*p30.XAVE*/ hash << XAVE.commit();
  /*p30.CUMU*/ hash << CUMU.commit();
  /*p30.CAPO*/ hash << CAPO.commit();
  /*p30.CONO*/ hash << CONO.commit();
  /*p30.CAJU*/ hash << CAJU.commit();
  /*p29.WAFY*/ hash << WAFY_STORE5_RSTp.commit();
  /*p31.FUSA*/ hash << STORE5_X0.commit();
  /*p31.FAXA*/ hash << STORE5_X1.commit();
  /*p31.FOZY*/ hash << STORE5_X2.commit();
  /*p31.FESY*/ hash << STORE5_X3.commit();
  /*p31.CYWE*/ hash << STORE5_X4.commit();
  /*p31.DYBY*/ hash << STORE5_X5.commit();
  /*p31.DURY*/ hash << STORE5_X6.commit();
  /*p31.CUVY*/ hash << STORE5_X7.commit();
  /*p30.EKAP*/ hash << EKAP.commit();
  /*p30.ETAV*/ hash << ETAV.commit();
  /*p30.EBEX*/ hash << EBEX.commit();
  /*p30.GORU*/ hash << GORU.commit();
  /*p30.ETYM*/ hash << ETYM.commit();
  /*p30.EKOP*/ hash << EKOP.commit();
  /*p30.ANED*/ hash << ANED.commit();
  /*p30.ACEP*/ hash << ACEP.commit();
  /*p30.ABUX*/ hash << ABUX.commit();
  /*p30.ABEG*/ hash << ABEG.commit();
  /*p29.WOMY*/ hash << WOMY_STORE6_RSTp.commit();
  /*p31.YCOL*/ hash << STORE6_X0.commit();
  /*p31.YRAC*/ hash << STORE6_X1.commit();
  /*p31.YMEM*/ hash << STORE6_X2.commit();
  /*p31.YVAG*/ hash << STORE6_X3.commit();
  /*p31.ZOLY*/ hash << STORE6_X4.commit();
  /*p31.ZOGO*/ hash << STORE6_X5.commit();
  /*p31.ZECU*/ hash << STORE6_X6.commit();
  /*p31.ZESA*/ hash << STORE6_X7.commit();
  /*p30.GECU*/ hash << GECU.commit();
  /*p30.FOXY*/ hash << FOXY.commit();
  /*p30.GOHU*/ hash << GOHU.commit();
  /*p30.FOGO*/ hash << FOGO.commit();
  /*p30.GACY*/ hash << GACY.commit();
  /*p30.GABO*/ hash << GABO.commit();
  /*p30.ZUBE*/ hash << ZUBE.commit();
  /*p30.ZUMY*/ hash << ZUMY.commit();
  /*p30.ZEXO*/ hash << ZEXO.commit();
  /*p30.ZAFU*/ hash << ZAFU.commit();
  /*p29.WAPO*/ hash << WAPO_STORE7_RSTp.commit();
  /*p31.ERAZ*/ hash << STORE7_X0.commit();
  /*p31.EPUM*/ hash << STORE7_X1.commit();
  /*p31.EROL*/ hash << STORE7_X2.commit();
  /*p31.EHYN*/ hash << STORE7_X3.commit();
  /*p31.FAZU*/ hash << STORE7_X4.commit();
  /*p31.FAXE*/ hash << STORE7_X5.commit();
  /*p31.EXUK*/ hash << STORE7_X6.commit();
  /*p31.FEDE*/ hash << STORE7_X7.commit();
  /*p30.FUZO*/ hash << FUZO.commit();
  /*p30.GESY*/ hash << GESY.commit();
  /*p30.FYSU*/ hash << FYSU.commit();
  /*p30.FEFA*/ hash << FEFA.commit();
  /*p30.GYNO*/ hash << GYNO.commit();
  /*p30.GULE*/ hash << GULE.commit();
  /*p30.XYGO*/ hash << XYGO.commit();
  /*p30.XYNA*/ hash << XYNA.commit();
  /*p30.XAKU*/ hash << XAKU.commit();
  /*p30.YGUM*/ hash << YGUM.commit();
  /*p29.EXUQ*/ hash << EXUQ_STORE8_RSTp.commit();
  /*p31.GAVY*/ hash << STORE8_X4.commit();
  /*p31.GYPU*/ hash << STORE8_X5.commit();
  /*p31.GADY*/ hash << STORE8_X6.commit();
  /*p31.GAZA*/ hash << STORE8_X7.commit();
  /*p31.EZUF*/ hash << STORE8_X0.commit();
  /*p31.ENAD*/ hash << STORE8_X1.commit();
  /*p31.EBOW*/ hash << STORE8_X2.commit();
  /*p31.FYCA*/ hash << STORE8_X3.commit();
  /*p30.AXUV*/ hash << STORE8_INDX5.commit();
  /*p30.BADA*/ hash << STORE8_INDX4.commit();
  /*p30.APEV*/ hash << STORE8_INDX3.commit();
  /*p30.BADO*/ hash << STORE8_INDX2.commit();
  /*p30.BEXY*/ hash << STORE8_INDX1.commit();
  /*p30.BYHE*/ hash << STORE8_INDX0.commit();
  /*p30.AFYM*/ hash << STORE8_LINE0.commit();
  /*p30.AZAP*/ hash << STORE8_LINE1.commit();
  /*p30.AFUT*/ hash << STORE8_LINE2.commit();
  /*p30.AFYX*/ hash << STORE8_LINE3.commit();
  /*p29.FONO*/ hash << FONO_STORE9_RSTp.commit();
  /*p31.XUVY*/ hash << STORE9_X0.commit();
  /*p31.XERE*/ hash << STORE9_X1.commit();
  /*p31.XUZO*/ hash << STORE9_X2.commit();
  /*p31.XEXA*/ hash << STORE9_X3.commit();
  /*p31.YPOD*/ hash << STORE9_X4.commit();
  /*p31.YROP*/ hash << STORE9_X5.commit();
  /*p31.YNEP*/ hash << STORE9_X6.commit();
  /*p31.YZOF*/ hash << STORE9_X7.commit();
  /*p30.XUFO*/ hash << STORE9_INDX0.commit();
  /*p30.XUTE*/ hash << STORE9_INDX1.commit();
  /*p30.XOTU*/ hash << STORE9_INDX2.commit();
  /*p30.XYFE*/ hash << STORE9_INDX3.commit();
  /*p30.YZOR*/ hash << STORE9_INDX4.commit();
  /*p30.YBER*/ hash << STORE9_INDX5.commit();
  /*p30.DEWU*/ hash << STORE9_LINE0.commit();
  /*p30.CANA*/ hash << STORE9_LINE1.commit();
  /*p30.DYSY*/ hash << STORE9_LINE2.commit();
  /*p30.FOFO*/ hash << STORE9_LINE3.commit();

  //----------
  // Sprite store tribufs

  hash << top.SPR_TRI_INDX_0.commit();
  hash << top.SPR_TRI_INDX_1.commit();
  hash << top.SPR_TRI_INDX_2.commit();
  hash << top.SPR_TRI_INDX_3.commit();
  hash << top.SPR_TRI_INDX_4.commit();
  hash << top.SPR_TRI_INDX_5.commit();

  hash << top.SPR_TRI_LINE_0.commit();
  hash << top.SPR_TRI_LINE_1.commit();
  hash << top.SPR_TRI_LINE_2.commit();
  hash << top.SPR_TRI_LINE_3.commit();


  return hash;
}

//------------------------------------------------------------------------------