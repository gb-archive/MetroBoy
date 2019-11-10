#pragma once

struct P23_VideoRegs {
  bool FF40_D0,FF40_D1,FF40_D2,FF40_D3,FF40_D4,FF40_D5,FF40_D6,FF40_D7; // FF40 LCDC
  bool FF42_D0,FF42_D1,FF42_D2,FF42_D3,FF42_D4,FF42_D5,FF42_D6,FF42_D7; // FF42 SCY
  bool FF43_D0,FF43_D1,FF43_D2,FF43_D3,FF43_D4,FF43_D5,FF43_D6,FF43_D7; // FF43 SCX
  bool FF45_D0,FF45_D1,FF45_D2,FF45_D3,FF45_D4,FF45_D5,FF45_D6,FF45_D7; // FF45 LYC
  bool FF4A_D0,FF4A_D1,FF4A_D2,FF4A_D3,FF4A_D4,FF4A_D5,FF4A_D6,FF4A_D7; // FF4A WY
  bool FF4B_D0,FF4B_D1,FF4B_D2,FF4B_D3,FF4B_D4,FF4B_D5,FF4B_D6,FF4B_D7; // FF4B WX
};