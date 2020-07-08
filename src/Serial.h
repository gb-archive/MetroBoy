#pragma once
#include "Types.h"

//-----------------------------------------------------------------------------

struct Serial {
  void reset();
  
  void tock(int phase, const Req& req);
  void tick(const Req& req, Ack& ack) const;

  void dump(Dumper& dump) const;

private:
  uint8_t sb = 0;
  uint8_t sc = 0;
};

//-----------------------------------------------------------------------------
