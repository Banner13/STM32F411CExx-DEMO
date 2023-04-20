
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
#include <wchar.h>

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

/* *************************************
 * User Config
 * ************************************/
#ifdef BottomToTop
    #define PageAddressOrder 1
#else
    #define PageAddressOrder 0
#endif

#ifdef RightToLeft
    #define ColumnAddressOrder 1
#else
    #define ColumnAddressOrder 0
#endif

#ifdef ReverseMode
    #define Page_ColumnOrder 1
#else
    #define Page_ColumnOrder 0
#endif

#ifdef LCDRefreshBottomToTop
    #define LineAddressOrder 1
#else
    #define LineAddressOrder 0
#endif

#ifdef BGR
    #define RGB_BGROrder 1
#else
    #define RGB_BGROrder 0
#endif

#ifdef LCDRefreshRightToLeft
    #define DisplayDataLatchDataOrder 1
#else
    #define DisplayDataLatchDataOrder 0
#endif

#ifdef LCD_12bit_color
    #define ControlInterfaceColorFormat 0x53
#endif
#ifdef LCD_16bit_color
    #define ControlInterfaceColorFormat 0x55
#endif
#ifdef LCD_18bit_color
    #define ControlInterfaceColorFormat 0x66
#endif

#ifdef LCD_FrameRate
    // LCD_FrameRate = 10MHz/(344)*(250+RTNA[4:0]*16)).
    // so RTNA[4:0] = (((10MHz / LCD_FrameRate) / 344) - 250) / 16
    #define RTNA_V  ((10000000 / (LCD_FrameRate * 344) - 250) / 16)
#endif


#endif  // ST7789_H
