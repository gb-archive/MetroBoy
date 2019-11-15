#pragma once
#include <stdint.h>

typedef const bool wire;
typedef const uint8_t wire8;
typedef const uint16_t wire16;

//-----------------------------------------------------------------------------
// Sync or async reset? Probably async...

struct reg {

  reg() {
    val = 0;
    clk = 0;
  }

  wire q() const { return val; }
  wire c() const { return clk; }

  // returns the _old_ q
  wire tock(wire clk2, wire r, wire d) {
    wire old = val;
    if (clk && !clk2) val = d;
    if (!r) val = 0;
    clk = clk2;
    return old;
  }

  void tock(wire clk2, wire d) {
    if (clk && !clk2) val = d;
    clk = clk2;
  }

  // ticks on both clock edges, returns the _old_ q
  wire dtock(wire clk2, wire r, wire d) {
    wire old = val;
    if (!r) val = 0;
    else if (clk != clk2) val = d;
    clk = clk2;
    return old;
  }

  // ticks on both clock edges, returns the _old_ q
  void dtock2(wire clk1, wire clk2, wire d) {
    if (clk1 != clk2) val = d;
    clk = clk2;
  }

  // returns the _old_ q
  wire flip(bool clk2, bool r) {
    wire old = val;
    if (!r) val = 0;
    else if (clk && !clk2) val = !val;
    clk = clk2;
    return old;
  }

  // returns the _old_ q
  // FIXME set is 0-triggered?
  wire srtock(wire clk2, wire s, wire r, wire d) {
    wire old = val;
    if (!s) val = 1;
    if (!r) val = 0;
    else if (clk && !clk2) val = d;
    clk = clk2;
    return old;
  }

  // FIXME what sort of trigger?
  wire latch(wire clk2, wire d) {
    if (!clk2) val = d;
    return val;
  }

  wire count(wire clk2, wire load, wire d) {
    wire old = val;
    if (clk && !clk2) {
      if (load) val = d;
      else val = !val;
    }
    clk = clk2;
    return old;
  }

  wire count(wire clk2) {
    wire old = val;
    if (clk && !clk2) {
      val = !val;
    }
    clk = clk2;
    return old;
  }

  void set()        { val = 1; }
  void reset()      { val = 0; }
  void load(bool v) { val = v; }

//private:

  bool val;
  bool clk;
};

//-----------------------------------------------------------------------------

struct counter {

  counter() {
    b0 = 0;
    b1 = 0;
    clk = 0;
  }

  wire q()     const { return b0; }
  wire carry() const { return b1; }

  void count(wire clk2) {
    if (clk && !clk2) {
      if (b0) {
        b1 = 1;
        b0 = 0;
      } else {
        b0 = 1;
        b1 = 0;
      }
    }
    clk = clk2;
  }

  void set()        { b0 = 1; b1 = 0; }
  void reset()      { b0 = 0; b1 = 0; }
  void load(bool v) { b0 = v; b1 = 0; }

//private:

  bool b0;
  bool b1;
  bool clk;
};

//-----------------------------------------------------------------------------

struct count8 {
  void count(wire clk2) {
    if (clk && !clk2) {
      val++;
      carry = val == 0;
    }
    clk = clk2;
  }

  void reset() {
    val = 0x00;
    // double-check carry
    carry = 0;
  }
  void load(uint8_t v) {
    val = v;
    // carry might duplicate high bit after load?
    carry = 0;
  }

//private:

  uint8_t val;
  bool carry;
  bool clk;
};

//-----------------------------------------------------------------------------

struct reg8 {

  wire8 q() const  { return val; }

  // returns the _old_ q
  wire8 tock(wire clk2, bool r, wire8 d) {
    wire8 old = val;
    if (!r) val = 0;
    else if (clk && !clk2) val = d;
    clk = clk2;
    return old;
  }

  wire8 count(wire clk2, wire load, wire8 d) {
    wire8 old = val;
    if (clk && !clk2) {
      if (load) val = d;
      else val = val + 1;
    }
    clk = clk2;
    return old;
  }

  wire8 count(wire clk2) {
    wire8 old = val;
    if (clk && !clk2) {
      val = val + 1;
    }
    clk = clk2;
    return old;
  }

  void unpack(bool& d0, bool& d1, bool& d2, bool& d3, bool& d4, bool& d5, bool& d6, bool& d7) {
    d0 = val & 0x01;
    d1 = val & 0x02;
    d2 = val & 0x04;
    d3 = val & 0x08;
    d4 = val & 0x10;
    d5 = val & 0x20;
    d6 = val & 0x40;
    d7 = val & 0x80;
  }

  void set()        { val = 0xFF; }
  void reset()      { val = 0x00; }
  void load(bool v) { val = v; }

//private:

  uint8_t val;
  bool clk;
};

//-----------------------------------------------------------------------------

struct reg16 {

  wire16 q() const  { return val; }

  // returns the _old_ q
  wire16 tock(wire clk2, bool r, wire16 d) {
    wire16 old = val;
    if (!r) val = 0;
    else if (clk && !clk2) val = d;
    clk = clk2;
    return old;
  }

  wire16 count(wire clk2) {
    wire16 old = val;
    if (clk && !clk2) {
      val = val + 1;
    }
    clk = clk2;
    return old;
  }

  void reset() { val = 0; }

  void unpack(bool& d0, bool& d1, bool& d2, bool& d3, bool& d4, bool& d5, bool& d6, bool& d7) {
    d0 = val & 0x01;
    d1 = val & 0x02;
    d2 = val & 0x04;
    d3 = val & 0x08;
    d4 = val & 0x10;
    d5 = val & 0x20;
    d6 = val & 0x40;
    d7 = val & 0x80;
  }

//private:

  uint16_t val;
  bool clk;
};

//-----------------------------------------------------------------------------