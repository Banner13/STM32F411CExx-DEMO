
/* *****************************************************************************
 *
 *  st7789v3-1.47inch driver
 *  author: huke
 *  date:   2023-1-27
 *  description: st7789 headfile
 * 
 * ***************************************************************************/
#ifndef ST7789_H
#define ST7789_H

#include "st7789_api.h"

/* *************************************
 * Reg List
 * ************************************/
typedef enum {
    WRITE_DATA  = 0x00,
    SLPOUT      = 0x11,
    INVOFF      = 0x20,
    INVON       = 0x21,
    DISPON      = 0x29,
    CASET       = 0x2A,
    RASET       = 0x2B,
    RAMWR       = 0x2C,
    MADCTL      = 0x36,
    COLMOD      = 0x3A,
    // PORCTRL     = 0xB2,
    // GCTRL       = 0xB7,
    // LCMCTRL     = 0xC0,
    // VDVVRHEN    = 0xC2,
    VRHS        = 0xC3,
    // VDVS        = 0xC4,
    FRCTRL2     = 0xC6,
    // PWCTRL1     = 0xD0,
    Unknown1    = 0xD6,
    PVGAMCTRL   = 0xE0,
    NVGAMCTRL   = 0xE1,
} ST7789_CMD;

#endif  // ST7789_H
