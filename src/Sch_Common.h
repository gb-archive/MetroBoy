#pragma once
#include "TextPainter.h"

namespace Schematics {

#pragma warning(disable:4201)

struct SchematicTop;
struct ClockSignals;
struct DebugSignals;
struct ResetSignals;
struct CpuBusSignals;

struct ClockRegisters;

struct CpuBus;

//typedef const bool wire;
typedef bool wire;

//-----------------------------------------------------------------------------

struct pwire;
struct nwire;

struct pwire {
  pwire(wire x) : v(x) {}
  wire operator==(nwire n) const;

  operator wire() const { return v; }

  wire  as_wire()  const { return v; }
  nwire as_nwire() const;

private:
  pwire(nwire x);
  const bool v;
};

struct nwire {
  nwire(wire x) : v(x) {}
  wire operator==(pwire p) const;

  operator wire() const { return v; }

  wire  as_wire()  const { return v; }
  pwire as_pwire() const;
private:
  nwire(pwire x);
  const bool v;
};

inline nwire pwire::as_nwire() const { return (nwire)v; }
inline pwire nwire::as_pwire() const { return (pwire)v; }

inline bool nwire::operator==(pwire p) const { return v == p.as_wire(); }
inline bool pwire::operator==(nwire n) const { return v == n.as_wire(); }

//-----------------------------------------------------------------------------

inline pwire not(nwire a) { return !a.as_wire(); }
inline nwire not(pwire a) { return !a.as_wire(); }

inline wire not (wire a) { return !a; }

inline wire and (wire a) { return a; }
inline wire and (wire a, wire b) { return a & b; }
inline wire and (wire a, wire b, wire c) { return  (a & b & c); }
inline wire and (wire a, wire b, wire c, wire d) { return  (a & b & c & d); }
inline wire and (wire a, wire b, wire c, wire d, wire e) { return  (a & b & c & d & e); }
inline wire and (wire a, wire b, wire c, wire d, wire e, wire f) { return  (a & b & c & d & e & f); }
inline wire and (wire a, wire b, wire c, wire d, wire e, wire f, wire g) { return  (a & b & c & d & e & f & g); }

inline wire or  (wire a) { return a; }
inline wire or  (wire a, wire b) { return a | b; }
inline wire or  (wire a, wire b, wire c) { return  (a | b | c); }
inline wire or  (wire a, wire b, wire c, wire d) { return  (a | b | c | d); }
inline wire or  (wire a, wire b, wire c, wire d, wire e) { return  (a | b | c | d | e); }

inline wire xor (wire a, wire b) { return a ^ b; }
inline wire xnor(wire a, wire b) { return a == b; }

inline wire nor (wire a) { return !a; }
inline wire nor (wire a, wire b) { return !(a | b); }
inline wire nor (wire a, wire b, wire c) { return !(a | b | c); }
inline wire nor (wire a, wire b, wire c, wire d) { return !(a | b | c | d); }
inline wire nor (wire a, wire b, wire c, wire d, wire e) { return !(a | b | c | d | e); }
inline wire nor (wire a, wire b, wire c, wire d, wire e, wire f) { return !(a | b | c | d | e | f); }
inline wire nor (wire a, wire b, wire c, wire d, wire e, wire f, wire g, wire h) { return !(a | b | c | d | e | f | g | h); }

inline wire nand(wire a) { return !a; }
inline wire nand(wire a, wire b) { return !(a & b); }
inline wire nand(wire a, wire b, wire c) { return !(a & b & c); }
inline wire nand(wire a, wire b, wire c, wire d) { return !(a & b & c & d); }
inline wire nand(wire a, wire b, wire c, wire d, wire e) { return !(a & b & c & d & e); }
inline wire nand(wire a, wire b, wire c, wire d, wire e, wire f) { return !(a & b & c & d & e & f); }
inline wire nand(wire a, wire b, wire c, wire d, wire e, wire f, wire g) { return !(a & b & c & d & e & f & g); }

//-----------------------------------------------------------------------------

// Six-rung mux cells are _non_inverting_. m = 1 selects input _ZERO_
inline const wire mux2_p(wire a, wire b, wire m) {
  return m ? a : b;
}

// Five-rung mux cells are _inverting_. m = 1 selects input _ZERO_
inline const wire mux2_n(wire a, wire b, wire m) {
  return !(m ? a : b);
}

inline wire amux2(wire a0, wire b0, wire a1, wire b1) {
  return (b0 & a0) | (b1 & a1);
}

inline wire amux3(wire a0, wire b0, wire a1, wire b1, wire a2, wire b2) {
  return (b0 & a0) | (b1 & a1) | (b2 & a2);
}

inline wire amux4(wire a0, wire b0, wire a1, wire b1, wire a2, wire b2, wire a3, wire b3) {
  return (b0 & a0) | (b1 & a1) | (b2 & a2) | (b3 & a3);
}

inline wire amux6(wire a0, wire b0, wire a1, wire b1, wire a2, wire b2, wire a3, wire b3, wire a4, wire b4, wire a5, wire b5) {
  return (b0 & a0) | (b1 & a1) | (b2 & a2) | (b3 & a3) | (b4 & a4) | (b5 & a5);
}

//-----------------------------------------------------------------------------

inline wire add_c(wire a, wire b, wire c) {
  return (a + b + c) & 2;
}

inline wire add_s(wire a, wire b, wire c) {
  return (a + b + c) & 1;
}

//-----------------------------------------------------------------------------

inline const uint32_t pack(wire b) {
  return (uint32_t)b;
}

template<typename... Args> const uint32_t pack(const wire first, Args... args) {
  return (pack(args...) << 1) | (uint32_t)first;
}

inline void unpack(uint32_t x, bool& b) {
  b = (bool)x;
}

template<typename... Args> void unpack(uint32_t x, bool& first, Args&... args) {
  first = bool(x & 1);
  unpack(x >> 1, args...);
}

//-----------------------------------------------------------------------------

union SignalState;
struct RegisterBase;

void dump_long(TextPainter& text_painter, const char* label, SignalState a);
void dump2(TextPainter& text_painter, SignalState a);
void dump_pin(TextPainter& text_painter, SignalState a, SignalState d);
void dump_pin(TextPainter& text_painter, SignalState a, SignalState b, SignalState c, SignalState d);

void dump(TextPainter& text_painter, const char* label,
          RegisterBase a, RegisterBase b, RegisterBase c, RegisterBase d,
          RegisterBase e, RegisterBase f, RegisterBase g);

void dump(TextPainter& text_painter, const char* label,
          RegisterBase a, RegisterBase b, RegisterBase c, RegisterBase d,
          RegisterBase e, RegisterBase f, RegisterBase g, RegisterBase h);


//-----------------------------------------------------------------------------

enum SignalFlags {
  SET_0   = 0b00000000,
  SET_1   = 0b00000001,

  VAL     = 0b00000001,
  HIZ     = 0b00000010,
  CLK     = 0b00000100,
  SET     = 0b00001000,
  RST     = 0b00010000,
  ERROR   = 0b00100000,
};

union SignalState {
  uint8_t state;
  struct {
    bool val     : 1;
    bool hiz     : 1;
    bool clk     : 1;
    bool set     : 1;
    bool rst     : 1;
    bool error   : 1;
  };

  SignalState(SignalFlags s) : state(uint8_t(s)) {}
  bool operator != (SignalState s) const { return state != s.state; }

  SignalState operator!() const {
    SignalState c = SET_0;
    c.val     = !val;
    c.hiz     = hiz;
    c.clk     = clk;
    c.set     = set;
    c.rst     = rst;
    c.error   = error;
    return c;
  }

  void dump(TextPainter& text_painter, const char* label) {
    dump_long(text_painter, label, *this);
  }
};

//-----------------------------------------------------------------------------

struct SignalHash {
  operator uint64_t() const { return h; }
  void operator << (SignalState s) { h ^= s.state; mix(); }
  void operator << (SignalHash h2) { h ^= h2.h;    mix(); }
  bool operator == (SignalHash h2) { return h = h2.h; }

  void mix() {
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccd;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53;
    h ^= h >> 33;
  }

  uint64_t h = 0x12345678;
};

static_assert(sizeof(SignalState) == 1, "SignalState size != 1");

//-----------------------------------------------------------------------------

struct Signal {

  Signal() : a(ERROR) {}

  operator wire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  void operator = (wire val) {
    if (!a.error) __debugbreak();
    a = val ? SET_1 : SET_0;
  }

  SignalState reset() {
    auto old_a = a;
    a = ERROR;
    return old_a;
  }

private:
  SignalState a;
};

//----------------------------------------

struct PSignal {

  PSignal() : a(ERROR) {}

  operator pwire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  wire as_wire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  nwire as_nwire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  void operator = (pwire val) {
    if (!a.error) __debugbreak();
    a = val.as_wire() ? SET_1 : SET_0;
  }

  SignalState reset() {
    auto old_a = a;
    a = ERROR;
    return old_a;
  }

private:
  //operator const nwire() const;
  SignalState a;
};

inline nwire not(PSignal p) { return not(p.as_wire()); }

//----------------------------------------

struct NSignal {

  NSignal() : a(ERROR) {}

  operator nwire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  wire as_wire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  pwire as_pwire() const {
    if (a.error) __debugbreak();
    return a.val;
  }

  void operator = (nwire val) {
    if (!a.error) __debugbreak();
    a = val.as_wire() ? SET_1 : SET_0;
  }

  SignalState reset() {
    auto old_a = a;
    a = ERROR;
    return old_a;
  }

private:
  //operator const pwire() const;
  SignalState a;
};

inline pwire not(NSignal n) { return not(n.as_wire()); }

//-----------------------------------------------------------------------------
// I think that reading a Z pin can't be an error; D0_C goes directly to RALO.
// Not sure how that doesn't break in harware, but whatev.

struct PinIn {

  operator const bool() const {
    if (a.error) __debugbreak();
    if (a.hiz)   __debugbreak();
    return a.val;
  }

  void preset(bool c) {
    preset(c ? SET_1 : SET_0);
  }
  void preset(SignalFlags c) {
    preset(SignalState(c));
  }
  void preset(SignalState c) {
    if (!a.error) __debugbreak();
    a = c;
  }

  SignalState clear_preset() {
    SignalState old_a = a;
    if (a.error) __debugbreak();
    a = ERROR;
    return old_a;
  }

  SignalState a = ERROR;
};

//-----------------------------------------------------------------------------

struct RegisterBase {

  operator const bool() const {
    if (a.error)  __debugbreak();
    if (a.hiz)    __debugbreak();
    if (!b.error) __debugbreak();

    //if (a.hiz) return 1;
    return a.val;
  }

  SignalState prev() const { return a; }
  
  bool q()  const { return  bool(); }
  bool qn() const { return !bool(); }

  void dump(TextPainter& text_painter, const char* label) {
    a.dump(text_painter, label);
  }

protected:
  SignalState a = SET_0;
  SignalState b = ERROR;
};

static_assert(sizeof(RegisterBase) == 2, "RegisterBase size != 2");

//-----------------------------------------------------------------------------

struct PinOut : public RegisterBase {

  void set(wire val) {
    if (!b.error) __debugbreak();
    b.val = val;
    b.hiz = 0;
    b.clk = 0;
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  SignalState commit_pinout() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();
    a = b;
    b = ERROR;
    return a;
  }
};

//-----------------------------------------------------------------------------

// RYMA 6-rung green tribuf

// TRIBUF_01
// TRIBUF_02 NC
// TRIBUF_03 NC
// TRIBUF_04
// TRIBUF_05 NC
// TRIBUF_06

struct Tribuf : public RegisterBase {

  Tribuf() {
    a = HIZ;
    b = ERROR;
  }

  void preset(SignalFlags f) {
    a.state = uint8_t(f);
    b.state = uint8_t(f);
  }

  void preset(bool x) {
    a = x ? SET_1 : SET_0;
    b = x ? SET_1 : SET_0;
  }

  void set_tribuf(pwire OEp, bool val) {
    if (!b.error && !b.hiz) {
      if (OEp.as_wire()) __debugbreak();
      return;
    }

    b.val = val && OEp.as_wire();
    b.hiz = OEp.as_wire();
    b.clk = 0;
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  // top rung tadpole facing second rung dot
  void set_tribuf_6p(pwire OEp, bool val) {
    if (!b.error && !b.hiz) {
      if (OEp.as_wire()) __debugbreak();
      return;
    }

    b.val = val && OEp.as_wire();
    b.hiz = OEp.as_wire();
    b.clk = 0;
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  // top rung tadpole not facing second rung dot
  void set_tribuf_6n(nwire OEn, bool val) {
    if (!b.error && !b.hiz) {
      if (!OEn.as_wire()) __debugbreak();
      return;
    }

    b.val = val && !OEn.as_wire();
    b.hiz = !OEn.as_wire();
    b.clk = 0;
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  void set_tribuf_10(nwire OEn, bool val) {
    if (!b.error && !b.hiz) {
      if (!OEn.as_wire()) __debugbreak();
      return;
    }

    b.val = val && (!OEn.as_wire());
    b.hiz = !OEn.as_wire();
    b.clk = 0;
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  SignalState commit_tribuf() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();
    a = b;
    b = ERROR;
    return a;
  }
};

//-----------------------------------------------------------------------------
// Persistent gate, used for nand latches

struct Gate : public RegisterBase {

  void preset(bool val) {
    if (!b.error) __debugbreak();
    a = val ? SET_1 : SET_0;
    b = ERROR;
  }

  void operator = (wire val) {
    if ( a.error) __debugbreak();
    if (!b.error) __debugbreak();
    b = val ? SET_1 : SET_0;
  }

  SignalState commit_gate() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();
    a = b;
    b = ERROR;
    return a;
  }
};

//-----------------------------------------------------------------------------
// 8-rung register with no reset and dual outputs
// Two or three vias in center column

// Used by sprite store, bg pix a, spr pix a/b, dma hi, bus mux sprite temp

// |o------O | CLKp
///|====O====| D
// |  -----  |
// |O-------o| CLKn
// |  -----  |
// |==     ==|
// |xxx-O-xxx| Q
// |xxx-O-xxx| Qn or this rung can be empty

// REG8_01 << CLKp
// REG8_02 << D
// REG8_03 nc
// REG8_04 << CLKn
// REG8_05 nc
// REG8_06 nc
// REG8_07 >> Q
// REG8_08 >> Qn

///*p32.NEFO*/ NEFO_BG_PIX_A7.set(LOMA_LATCH_BG_PIX_Ap, vram_bus.CPU_TRI_D7);

// NEFO_01 << LOMA_02    (clk)
// NEFO_02 << CPU_TRI_D7     (d)
// NEFO_03 nc
// NEFO_04 << COMP_CLOCK (clkn)
// NEFO_05 nc
// NEFO_06 nc
// NEFO_07 >> NAJA_02    (Q)
// NEFO_08 nc

struct Reg8 : public RegisterBase {

  void set(pwire CLKp, nwire CLKn, bool val) {
    if (CLKp == CLKn) __debugbreak();
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = val;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = 0;
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }

  /*
  private:
  operator const bool() const;
  */
};

//-----------------------------------------------------------------------------
// 9-rung register with reset and dual outputs. Looks like Reg8 with a hat and a belt.
// Four vias in center column

// The cell layout looks pretty much identical to Reg9Duo - so probably dual-edge?

// Used by clock phase (CHECK), LYC, BGP, OBP0, OBP1, stat int enable, sprite
// store, SCY, SCX, LCDC, WX, WY

// | O===--o | 
// |==--O====| CLKp
// | ------- | D
// |o-------O| CLKn
// |  -----  | 
// |--xxOxx--| RSTn
// |o-------o| 
// |xxx-O-xxx| Q
// |xxx-O-xxx| Qn?

// REG9_01 NC
// REG9_02 << CLKp
// REG9_03 << D
// REG9_04 << CLKn
// REG9_05 NC
// REG9_06 << RSTp - THIS MUST BE POSITIVE RESET - UPOJ_MODE_PROD is active-low
// REG9_07 NC
// REG9_08 >> Q
// REG9_09 >> QN

///*p31.XEPE*/ STORE0_X0   .set(FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, ZAGO_SPRITE_X0);

// XEPE_01 nc
// XEPE_02 << FUXU_02  (clk)
// XEPE_03 << ZAGO_02  (d)
// XEPE_04 << COMP_CLK (clkn)
// XEPE_05 nc
// XEPE_06 << DYNA02   (rst)
// XEPE_07 nc
// XEPE_08 >> ZOGY_02  (q)
// XEPE_09 >> nc

struct Reg9p : public RegisterBase {

  void set(pwire CLKp, nwire CLKn, pwire RSTp, bool D) {
    if (CLKp == CLKn) __debugbreak();
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = D;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = RSTp.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};


struct Reg9 : public RegisterBase {

  void set(pwire CLKp, nwire CLKn, nwire RSTn, bool D) {
    if (CLKp == CLKn) __debugbreak();
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = D;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = !RSTn.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------
// Reg11 is used by the background pixel temp reg
// Not sure why it's special. Could be dual-edge.

///*p32.RAWU*/ top.RAWU_BG_PIX_B0.set(LABU_LATCH_BG_PIX_Bp, top.VYPO_GND, top.VRM_TRI_D0);

// wire LUVE_MATCH_BG_PIX_Bn = not(LESO_LATCH_BG_PIX_Bp); // Schematic wrong, was labeled AJAR
// wire LABU_LATCH_BG_PIX_Bp = not(LUVE_MATCH_BG_PIX_Bn);

// RAWU_01 nc
// RAWU_02 << VYPO_02 (RSTp?)
// RAWU_03 << VRM_TRI_D0
// RAWU_04 nc
// RAWU_05 << LABU_03 (CLKp?)
// RAWU_06 nc
// RAWU_07 nc
// RAWU_08 << LUVE_03 (CLKn?)
// RAWU_09 << VYPO_02 (RSTp?)
// RAWU_10 nc
// RAWU_11 >> TUXE_02

// LUVE = not(LESO)
// 


/*p32.RAWU*/
/*p32.POZO*/
/*p32.PYZO*/
/*p32.POXA*/
/*p32.PULO*/
/*p32.POJU*/
/*p32.POWY*/
/*p32.PYJU*/

struct Reg11 : public RegisterBase {

  void setQ(pwire CLKp, nwire CLKn, pwire RSTp, wire D) {
    if (CLKp == CLKn) __debugbreak();
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = D;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = RSTp.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};


//-----------------------------------------------------------------------------
// Reg13
// Could be dual-edge. Not sure.
// Could be pos-reset. Not sure.

// REG13_01 nc
// REG13_02 << RSTp?
// REG13_03 << D
// REG13_04 nc
// REG13_05 << CLKp?
// REG13_06 nc
// REG13_07 nc
// REG13_08 << CLKn?
// REG13_09 << RSTp?
// REG13_10 nc
// REG13_11 nc
// REG13_12 >> Qn
// REG13_13 >> Q

/*p01.AFER*/ // out on 13
/*p30.XADU*/ // out on 12
/*p30.XEDY*/ // out on 12
/*p30.ZUZE*/ // out on 12
/*p30.XOBE*/ // out on 12
/*p30.YDUF*/ // out on 12
/*p30.XECU*/ // out on 12

///*p01.AFER*/ AFER_RSTp.set(BOMA_xBxxxxxx, UPOJ_MODE_PRODn, ASOL_RST_LATCHp);
///*p30.XADU*/ XADU_SPRITE_IDX0.set(clk_reg.WUDA_xBCxxFGx, top.WEFE_GND, bus_sig.YFOT_OAM_A2p);

// AFER_01 nc
// AFER_02 << UPOJ_04 (RSTp?)
// AFER_03 << ASOL_03 (D)
// AFER_04 nc
// AFER_05 << BOGA_07 (CLKp?)
// AFER_06 nc
// AFER_07 nc
// AFER_08 << BOMA_07 (CLKn?)
// AFER_09 << UPOJ_04 (RSTp?)
// AFER_10 nc
// AFER_11 nc
// AFER_12 >> nc
// AFER_13 >> AVOR_01

// XADU_01 nc
// XADU_02 << WEFE_02 (RSTp?)
// XADU_03 << YFOT_02 (D)
// XADU_04 nc
// XADU_05 << WUDA_03 (CLKp?)
// XADU_06 nc
// XADU_07 nc
// XADU_08 << CYKE_02 (CLKn?)
// XADU_09 << WEFE_02 (RSTp?)
// XADU_10 nc
// XADU_11 nc
// XADU_12 >> WUZY_04 (Q)    // might have these switched, but there's not many of these regs
// XADU_13 >> nc      (QN)

struct Reg13 : public RegisterBase {

  void set(pwire CLKp, nwire CLKn, pwire RSTp, bool D) {
    if (CLKp == CLKn) __debugbreak();
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = D;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = RSTp.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------
// set and reset must be async (see interrupts)
// reset must take priority over set (see interrupts ALUR_RSTn)

// This reg is really 3 pieces - clock edge detector, latch, and output buffer.

// REG17_01 == REG17_12
// REG17_02 << CLKp
// REG17_03 == REG17_09
// REG17_04 NC
// REG17_05 NC
// REG17_06 << RSTn
// REG17_07 << D
// REG17_08 NC
// REG17_09 == REG17_03
// REG17_10 NC
// REG17_11 NC
// REG17_12 == REG17_01
// REG17_13 << RSTn
// REG17_14 NC
// REG17_15 NC
// REG17_16 >> QN
// REG17_17 >> Q

struct Reg17 : public RegisterBase {

  // must be RSTn, see WUVU/VENA/WOSU

  void set(pwire CLKp, nwire RSTn, bool val) {
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = val;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = 0;
    b.rst = RSTn.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------

// REG22_01 SC
// REG22_02 NC
// REG22_03 NC
// REG22_04 NC
// REG22_05 SC
// REG22_06 SC
// REG22_07 << D
// REG22_08 NC
// REG22_09 SC
// REG22_10 NC
// REG22_11 SC
// REG22_12 NC
// REG22_13 NC
// REG22_14 << SETn
// REG22_15 >> Qn
// REG22_16 >> Q
// REG22_17 << RSTn
// REG22_18 NC
// REG22_19 SC
// REG22_20 SC
// REG22_21 SC
// REG22_22 << CLKp

// /*p02.UBUL*/ UBUL_FF0F_3.set(CALY_INT_SERIALp, TOME_FF0F_SET3n, TUNY_FF0F_RST3n, PESU_FF0F_INp);

// UBUL_01 == UBUL_14
// UBUL_02 NC
// UBUL_03 NC
// UBUL_04 NC
// UBUL_05 == UBUL_11 == UBUL_19
// UBUL_06 == UBUL_21
// UBUL_07 << PESU_FF0F_INp
// UBUL_08 NC
// UBUL_09 == UBUL_20
// UBUL_10 NC
// UBUL_11 == UBUL_05 == UBUL_19
// UBUL_12 NC
// UBUL_13 NC
// UBUL_14 << TOME_FF0F_SET3n, >> UBUL_01
// UBUL_15 >> NC
// UBUL_16 >> CPU_PIN_INT_SERIAL
// UBUL_17 << TUNY_FF0F_RST3n
// UBUL_18 NC
// UBUL_19 == UBUL_05 == UBUL_11
// UBUL_20 == UBUL_09
// UBUL_21 == UBUL_06
// UBUL_22 << CALY_INT_SERIALp

struct Reg22 : public RegisterBase {

  void set(pwire CLKp, nwire SETn, nwire RSTn, bool val) {
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = val;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = !SETn.as_wire();
    b.rst = !RSTn.as_wire();
    b.error = 0;
  }

  SignalState commit_reg() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------
// 6-rung cell, "arms" on ground side

// ASOL seems to break this pattern, it looks like it has to be nand or have
// an inverted output.

// NORLATCH_01 << SET
// NORLATCH_01 NC
// NORLATCH_01 >> QN
// NORLATCH_01 >> Q
// NORLATCH_01 NC
// NORLATCH_01 << RST

struct NorLatch : public RegisterBase {

  void dbg_set(bool val) {
    b.val = 0;
    b.hiz = 0;
    b.clk = 0;
    b.set = val;
    b.rst = !val;
    b.error = 0;
  }

  void nor_latch(pwire SETp, pwire RSTp) {
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = 0;
    b.hiz = 0;
    b.clk = 0;
    b.set = SETp.as_wire();
    b.rst = RSTp.as_wire();
    b.error = 0;
  }

  SignalState commit_latch() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------
// 6-rung cell, "arms" on VCC side

// Only TAKA/LONY seem to use this cell

// NANDLATCH_01 << SETn
// NANDLATCH_01 NC
// NANDLATCH_01 >> Q
// NANDLATCH_01 >> QN
// NANDLATCH_01 NC
// NANDLATCH_01 << RSTn

struct NandLatch : public RegisterBase {

  void nand_latch(nwire SETn, nwire RSTn) {
    if (a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = 0;
    b.hiz = 0;
    b.clk = 0;
    b.set = !SETn.as_wire();
    b.rst = !RSTn.as_wire();
    b.error = 0;
  }

  SignalState commit_latch() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------
// Yellow 10-rung cells on die. Implementation might be wrong.

// TPLATCH_01
// TPLATCH_02 NC
// TPLATCH_03
// TPLATCH_04 NC
// TPLATCH_05 NC
// TPLATCH_06 NC
// TPLATCH_07 NC
// TPLATCH_08
// TPLATCH_09 NC
// TPLATCH_10


///*p08.RUPA*/ TpLatch RUPA_EXT_DATA_LATCH_06;
// RUPA_01 << LAVO
// RUPA_02 NC
// RUPA_03 << D6_C
// RUPA_04 NC
// RUPA_05 NC
// RUPA_06 NC
// RUPA_07 NC
// RUPA_08 >> SEVU
// RUPA_09 NC
// RUPA_10 ?? NC

///*p02.MATY*/ TpLatch MATY_FF0F_L0;
// MATY_01 << ROLO_05
// MATY_02 nc
// MATY_03 << CPU_PIN_INT_VBLANK
// MATY_04 nc
// MATY_05 nc
// MATY_06 nc
// MATY_07 nc
// MATY_08 ?? nc
// MATY_09 nc
// MATY_10 >> NELA_04

///*p08.ALOR*/ TpLatch CPU_ADDR_LATCH_00;
// ALOR_01 << MATE_02
// ALOR_02 nc
// ALOR_03 << CPU_PIN_A00
// ALOR_04 nc
// ALOR_05 nc
// ALOR_06 nc
// ALOR_07 nc
// ALOR_08 >> AMET_03
// ALOR_09 nc
// ALOR_10

///*p31.WYNO*/ TpLatch WYNO_LATCH_OAM_A4;
///*p31.WYNO*/ WYNO_LATCH_OAM_A4.tp_latch(BODE_OAM_LATCH, top.OAM_PIN_DA4);

// WYNO_01 << BODE_02
// WYNO_02 NC
// WYNO_03 << OAM_PIN_DA4
// WYNO_04 NC
// WYNO_05 NC
// WYNO_06 NC
// WYNO_07 NC
// WYNO_08 >> GOMO_02
// WYNO_09 NC
// WYNO_10 >> XUNA_01

struct TpLatch : public RegisterBase {

  void tp_latch(nwire LATCHp, bool val) {
    if (a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = 0;
    b.hiz = 0;
    b.clk = 0;
    b.set = LATCHp.as_wire() && val;
    b.rst = LATCHp.as_wire() && !val;
    b.error = 0;
  }

  SignalState commit_latch() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};


//-----------------------------------------------------------------------------
// FIXME ticks on the NEGATIVE EDGE of the clock (see timer.cpp)

// 20-rung

// REGA_TIMA_0.clk_n(SOGY_TIMA_CLK,   MEXU_TIMA_LOAD, PUXY_TIMA_LD_0);

// REGA_01 >> POVY_20
// REGA_02 nc
// REGA_03 << PUXY_03
// REGA_04 << MEXU_04
// REGA_05 nc
// REGA_06 <> REGA_18
// REGA_07 nc
// REGA_08 nc
// REGA_09 nc
// REGA_10 nc
// REGA_11 <> REGA_19
// REGA_12 nc
// REGA_13 nc
// REGA_14 << MEXU_04
// REGA_15 nc
// REGA_16 << PUXY_03
// REGA_17 >> SOKU_04
// REGA_18 <> REGA_06
// REGA_19 <> REGA_11
// REGA_20 << SOGU_03

struct Counter : public RegisterBase {

  void clk_n(pwire CLKp, pwire LOADp, bool val) {
    if ( a.error)  __debugbreak();
    if (!b.error) __debugbreak();
    b.val = val;
    b.hiz = 0;
    b.clk = CLKp.as_wire();
    b.set = LOADp.as_wire() && val;
    b.rst = LOADp.as_wire() && !val;
    b.error = 0;
  }

  SignalState commit_counter() {
    if (a.error) __debugbreak();
    if (b.error) __debugbreak();

    bool new_a = (!a.clk && b.clk) ? b.val : a.val;

    if (b.set) new_a = 1;
    if (b.rst) new_a = 0;

    a.val = new_a;
    a.hiz = 0;
    a.clk = b.clk;
    a.set = b.set;
    a.rst = b.rst;
    a.error = 0;

    b = ERROR;

    return a;
  }
};

//-----------------------------------------------------------------------------

};