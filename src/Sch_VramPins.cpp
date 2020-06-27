#include "Sch_VramPins.h"

#include "TestGB.h"

using namespace Schematics;

// Die trace:
// TEFA = nor(SYRO, TEXO);         OK
// SOSE = and( A15, TEFA);         OK
// TUCA = and(SOSE, ABUZ);         OK
// TEGU = nand(SOSE, CPU_RAW_WR);  OK
// TAVY = not(MOE_C);              OK
// TEFY = not(MCS_C);              OK

// TUTO = and(TOVA, SOTO);         OK
// ROPY = not(XYMU);               OK

// TOLE = mux2(TUTO, TEFY, TUCA)   OK
// SERE = and(TOLE, ROPY)          OK
// SALE = mux2(TUTO, TAVY, TEGU)   OK
// RUVY = not(SALE);               OK
// SAZO = and(SERE, RUVY)          OK
// RYJE = not(SAZO)                OK
// REVO = not(RYJE)                OK
// ROCY = and(SAZO, REVO)          OK
// RAHU = not(ROCY)                OK, big inverter
// ROVE = not(RAHU)                OK
// RELA = or(REVO, SAZO)          OK
// RENA = not(RELA)                OK

// XAKY 6-rung tribuf, inputs on 1 and 4
// XAKY01
// XAKY02 nc
// XAKY03 nc
// XAKY04
// XAKY05 nc
// XAKY06

// How does DMA/PPU lock come into play here? Does it?
// PPU locks via RENDERING_LATCH, dma by...? well it doesn't have to lock since it's just reading.
// so really if the address is muxed right, we only need to block writes while vram's locked.
// oh there's also some locking down in the pin driver...

//---------------------------------------------------------------------------

void VramPins::tick(TestGB& gb) {
  auto clk_sig = gb.clk_reg.sig(gb);
  auto dbg_sig = gb.dbg_reg.sig(gb);
  auto adr_sig = gb.adr_reg.sig(gb.cpu_bus);
  auto dma_sig = gb.dma_reg.sig(gb);
  auto win_sig = gb.win_reg.sig(gb);
  auto cpu_sig = gb.cpu_reg.sig(gb);
  auto ppu_sig = gb.ppu_reg.sig(gb);

  auto& ppu_reg = gb.ppu_reg;

  auto& vram_bus = gb.vram_bus;

  auto& cpu_bus = gb.cpu_bus;
  auto& vram_pins = gb.vram_pins;

  //---------------------------------------------------------------------------

  /*p25.TAVY*/ wire TAVY_MOE_Cn = not(vram_pins.PIN_MOEn_C);
  /*p25.TEGU*/ wire TEGU_CPU_VRAM_WRn = nand(adr_sig.SOSE_8000_9FFFp, cpu_bus.PIN_CPU_RAW_WR); // Schematic wrong, second input is CPU_RAW_WR
  /*p25.SALE*/ wire SALE_VRAM_WRn = mux2_p(TAVY_MOE_Cn, TEGU_CPU_VRAM_WRn, dbg_sig.TUTO_DBG_VRAMp);

  //----------

  {
    /*p25.LEXE*/ vram_pins.PIN_MA00_AD.set(not(/*p25.MYFU*/ not(vram_bus.TS_MA00)));
    /*p25.LOZU*/ vram_pins.PIN_MA01_AD.set(not(/*p25.MASA*/ not(vram_bus.TS_MA01)));
    /*p25.LACA*/ vram_pins.PIN_MA02_AD.set(not(/*p25.MYRE*/ not(vram_bus.TS_MA02)));
    /*p25.LUVO*/ vram_pins.PIN_MA03_AD.set(not(/*p25.MAVU*/ not(vram_bus.TS_MA03)));
    /*p25.LOLY*/ vram_pins.PIN_MA04_AD.set(not(/*p25.MEPA*/ not(vram_bus.TS_MA04)));
    /*p25.LALO*/ vram_pins.PIN_MA05_AD.set(not(/*p25.MYSA*/ not(vram_bus.TS_MA05)));
    /*p25.LEFA*/ vram_pins.PIN_MA06_AD.set(not(/*p25.MEWY*/ not(vram_bus.TS_MA06)));
    /*p25.LUBY*/ vram_pins.PIN_MA07_AD.set(not(/*p25.MUME*/ not(vram_bus.TS_MA07)));
    /*p25.TUJY*/ vram_pins.PIN_MA08_AD.set(not(/*p25.VOVA*/ not(vram_bus.TS_MA08)));
    /*p25.TAGO*/ vram_pins.PIN_MA09_AD.set(not(/*p25.VODE*/ not(vram_bus.TS_MA09)));
    /*p25.NUVA*/ vram_pins.PIN_MA10_AD.set(not(/*p25.RUKY*/ not(vram_bus.TS_MA10)));
    /*p25.PEDU*/ vram_pins.PIN_MA11_AD.set(not(/*p25.RUMA*/ not(vram_bus.TS_MA11)));
    /*p25.PONY*/ vram_pins.PIN_MA12_AD.set(not(/*p25.REHO*/ not(vram_bus.TS_MA12)));
  }

  {
    /*p25.RUVY*/ wire RUVY_VRAM_WRp = not(SALE_VRAM_WRn);
    /*p25.SAZO*/ wire SAZO_VRAM_RD  = and (RUVY_VRAM_WRp, ppu_sig.SERE_VRAM_RD);

    /*p25.RYJE*/ wire RYJE_VRAM_RDn = not(SAZO_VRAM_RD);
    /*p25.REVO*/ wire REVO_VRAM_RDp = not(RYJE_VRAM_RDn);

    {
      /*p25.ROCY*/ wire ROCY_VBUS_TRISTATEn = and (REVO_VRAM_RDp, SAZO_VRAM_RD);
      /*p25.RAHU*/ wire RAHU_VBUS_TRISTATEp = not(ROCY_VBUS_TRISTATEn);
      /*p25.ROVE*/ wire ROVE_VBUS_TRISTATEn = not(RAHU_VBUS_TRISTATEp);

      /*p25.SEFA*/ wire SEFA = and (vram_bus.TS_MD0, ROVE_VBUS_TRISTATEn);
      /*p25.SOGO*/ wire SOGO = and (vram_bus.TS_MD1, ROVE_VBUS_TRISTATEn);
      /*p25.SEFU*/ wire SEFU = and (vram_bus.TS_MD2, ROVE_VBUS_TRISTATEn);
      /*p25.SUNA*/ wire SUNA = and (vram_bus.TS_MD3, ROVE_VBUS_TRISTATEn);
      /*p25.SUMO*/ wire SUMO = and (vram_bus.TS_MD4, ROVE_VBUS_TRISTATEn);
      /*p25.SAZU*/ wire SAZU = and (vram_bus.TS_MD5, ROVE_VBUS_TRISTATEn);
      /*p25.SAMO*/ wire SAMO = and (vram_bus.TS_MD6, ROVE_VBUS_TRISTATEn);
      /*p25.SUKE*/ wire SUKE = and (vram_bus.TS_MD7, ROVE_VBUS_TRISTATEn);

      /*p25.SYNU*/ wire SYNU = or (vram_bus.TS_MD0, RAHU_VBUS_TRISTATEp);
      /*p25.SYMA*/ wire SYMA = or (vram_bus.TS_MD1, RAHU_VBUS_TRISTATEp);
      /*p25.ROKO*/ wire ROKO = or (vram_bus.TS_MD2, RAHU_VBUS_TRISTATEp);
      /*p25.SYBU*/ wire SYBU = or (vram_bus.TS_MD3, RAHU_VBUS_TRISTATEp);
      /*p25.SAKO*/ wire SAKO = or (vram_bus.TS_MD4, RAHU_VBUS_TRISTATEp);
      /*p25.SEJY*/ wire SEJY = or (vram_bus.TS_MD5, RAHU_VBUS_TRISTATEp);
      /*p25.SEDO*/ wire SEDO = or (vram_bus.TS_MD6, RAHU_VBUS_TRISTATEp);
      /*p25.SAWU*/ wire SAWU = or (vram_bus.TS_MD7, RAHU_VBUS_TRISTATEp);

      /*p25.REGE*/ wire REGE = not(SEFA);
      /*p25.RYKY*/ wire RYKY = not(SOGO);
      /*p25.RAZO*/ wire RAZO = not(SEFU);
      /*p25.RADA*/ wire RADA = not(SUNA);
      /*p25.RYRO*/ wire RYRO = not(SUMO);
      /*p25.REVU*/ wire REVU = not(SAZU);
      /*p25.REKU*/ wire REKU = not(SAMO);
      /*p25.RYZE*/ wire RYZE = not(SUKE);

      /*p25.RURA*/ wire RURA = not(SYNU);
      /*p25.RULY*/ wire RULY = not(SYMA);
      /*p25.RARE*/ wire RARE = not(ROKO);
      /*p25.RODU*/ wire RODU = not(SYBU);
      /*p25.RUBE*/ wire RUBE = not(SAKO);
      /*p25.RUMU*/ wire RUMU = not(SEJY);
      /*p25.RYTY*/ wire RYTY = not(SEDO);
      /*p25.RADY*/ wire RADY = not(SAWU);

      PIN_MD0_A.set(REGE);
      PIN_MD1_A.set(RYKY);
      PIN_MD2_A.set(RAZO);
      PIN_MD3_A.set(RADA);
      PIN_MD4_A.set(RYRO);
      PIN_MD5_A.set(REVU);
      PIN_MD6_A.set(REKU);
      PIN_MD7_A.set(RYZE);

      PIN_MD0_D.set(RURA);
      PIN_MD1_D.set(RULY);
      PIN_MD2_D.set(RARE);
      PIN_MD3_D.set(RODU);
      PIN_MD4_D.set(RUBE);
      PIN_MD5_D.set(RUMU);
      PIN_MD6_D.set(RYTY);
      PIN_MD7_D.set(RADY);
    }

    {
      /*p25.RELA*/ wire RELA_MD_OEp = or (REVO_VRAM_RDp, SAZO_VRAM_RD);
      /*p25.RENA*/ wire RENA_MD_OEn = not(RELA_MD_OEp);
      /*p25.ROFA*/ wire ROFA_MD_OEp = not(RENA_MD_OEn);

      /*p25.ROFA*/ PIN_MD0_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD1_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD2_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD3_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD4_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD5_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD6_B.set(ROFA_MD_OEp);
      /*p25.ROFA*/ PIN_MD7_B.set(ROFA_MD_OEp);

      /*p25.RODY*/ vram_bus.TS_MD0.set_tribuf(RENA_MD_OEn, PIN_MD0_C);
      /*p25.REBA*/ vram_bus.TS_MD1.set_tribuf(RENA_MD_OEn, PIN_MD1_C);
      /*p25.RYDO*/ vram_bus.TS_MD2.set_tribuf(RENA_MD_OEn, PIN_MD2_C);
      /*p25.REMO*/ vram_bus.TS_MD3.set_tribuf(RENA_MD_OEn, PIN_MD3_C);
      /*p25.ROCE*/ vram_bus.TS_MD4.set_tribuf(RENA_MD_OEn, PIN_MD4_C);
      /*p25.ROPU*/ vram_bus.TS_MD5.set_tribuf(RENA_MD_OEn, PIN_MD5_C);
      /*p25.RETA*/ vram_bus.TS_MD6.set_tribuf(RENA_MD_OEn, PIN_MD6_C);
      /*p25.RAKU*/ vram_bus.TS_MD7.set_tribuf(RENA_MD_OEn, PIN_MD7_C);
    }
  }

  // Die trace
  // MYMA = not(LONY);
  // APAM = not(LUFA);
  // RACU = and(RYLU, RAWA, MYMA, APAM);

  {
    /*p25.RACO*/ wire _RACO_DBG_VRAMn = not(dbg_sig.TUTO_DBG_VRAMp);
    /*p29.ABON*/ wire ABON_SPR_VRAM_RDp1 = not(ppu_sig.TEXY_SPRITE_READp);

    /*p25.TUJA*/ wire _TUJA_CPU_VRAM_WR = and(adr_sig.SOSE_8000_9FFFp, cpu_sig.APOV_CPU_WR_xxxxxFGH);
    /*p25.SUDO*/ wire _SUDO_MWR_Cn = not(PIN_MWRn_C);
    /*p25.TYJY*/ wire _TYJY_DBG_VRAM_WR = mux2_p(_SUDO_MWR_Cn, _TUJA_CPU_VRAM_WR, dbg_sig.TUTO_DBG_VRAMp);
    /*p25.SOHY*/ wire _SOHY_MWR    = nand(_TYJY_DBG_VRAM_WR, ppu_sig.SERE_VRAM_RD);

    /*p25.XANE*/ wire _XANE_VRAM_LOCKn = nor(dma_sig.LUFA_DMA_READ_VRAMp, ppu_sig.XYMU_RENDERINGp); // def nor
    /*p25.SOHO*/ wire _SOHO_SPR_VRAM_RDp = and (ppu_sig.TACU_SPR_SEQ_5_TRIG, ABON_SPR_VRAM_RDp1);
    /*p25.RYLU*/ wire _RYLU_DBG_VRAM_RDn = nand(SALE_VRAM_WRn, _XANE_VRAM_LOCKn);
    /*p25.RAWA*/ wire _RAWA_SPR_VRAM_RDn = not(_SOHO_SPR_VRAM_RDp);
    /*p27.MYMA*/ wire _MYMA_BGW_VRAM_RDn = not(ppu_reg.LONY_BG_READ_VRAM_LATCHp.q()); // this should be correct
    /*p25.APAM*/ wire _APAM_DMA_VRAM_RDn = not(dma_sig.LUFA_DMA_READ_VRAMp);
    /*p25.RACU*/ wire _RACU_MOEn   = and (_RYLU_DBG_VRAM_RDn, _RAWA_SPR_VRAM_RDn, _MYMA_BGW_VRAM_RDn, _APAM_DMA_VRAM_RDn); // def and

    /*p27.LUSU*/ wire LUSU_BGW_VRAM_RDn = not(ppu_reg.LONY_BG_READ_VRAM_LATCHp.q());
    /*p27.LENA*/ wire LENA_BGW_VRAM_RD = not(LUSU_BGW_VRAM_RDn);
    /*p25.SUTU*/ wire _SUTU_MCSn = nor(LENA_BGW_VRAM_RD, dma_sig.LUFA_DMA_READ_VRAMp, ABON_SPR_VRAM_RDp1, ppu_sig.SERE_VRAM_RD);

    {
      /*p25.TAXY*/ wire _TAXY_MWR_An = and(_SOHY_MWR, _RACO_DBG_VRAMn);
      /*p25.SOFY*/ wire _SOFY_MWR_Dn = or (_SOHY_MWR, dbg_sig.TUTO_DBG_VRAMp);
      /*p25.SYSY*/ PIN_MWRn_A.set(not(_TAXY_MWR_An));
      /*p25.RAGU*/ PIN_MWRn_D.set(not(_SOFY_MWR_Dn));
    }

    {
      /*p25.SEMA*/ wire _SEMA_MOE_An = and(_RACU_MOEn, _RACO_DBG_VRAMn);
      /*p25.RUTE*/ wire _RUTE_MOE_Dn = or (_RACU_MOEn, dbg_sig.TUTO_DBG_VRAMp); // schematic wrong, second input is RACU
      /*p25.REFO*/ PIN_MOEn_A.set(not(_SEMA_MOE_An));
      /*p25.SAHA*/ PIN_MOEn_D.set(not(_RUTE_MOE_Dn));
    }

    {
      /*p25.TODE*/ wire _TODE_MCS_An = and(_SUTU_MCSn, _RACO_DBG_VRAMn);
      /*p25.SEWO*/ wire _SEWO_MCS_Dn = or (_SUTU_MCSn, dbg_sig.TUTO_DBG_VRAMp);
      /*p25.SOKY*/ PIN_MCSn_A.set(not(_TODE_MCS_An));
      /*p25.SETY*/ PIN_MCSn_D.set(not(_SEWO_MCS_Dn));
    }
  }
}