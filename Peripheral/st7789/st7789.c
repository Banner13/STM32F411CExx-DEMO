
/* *****************************************************************************
 *
 *  st7789v3-1.47inch driver
 *  author: huke
 *  date:   2023-1-27
 *  description: st7789 code
 * 
 * ***************************************************************************/

#include "st7789.h"

/* 			     st7789 private define              */
#define RES_ENABLE                  ST7789_RES_RESET;
#define RES_DISABLE                 ST7789_RES_SET;
#define DC_DATA                     ST7789_DC_SET;
#define DC_CMD                      ST7789_DC_RESET;
#define CS_ENABLE                   ST7789_CS_RESET;
#define CS_DISABLE                  ST7789_CS_SET;
#define BLK_ENABLE                  ST7789_BLK_SET;
#define BLK_DISABLE                 ST7789_BLK_RESET;
#define Delay_ms(t)                 ST7789_MS_DELAY(t);
#define SPI_Write(data_ptr,size)    ST7789_SPI_Write(data_ptr,size)
#define CMD_SIZE                    0x01

int ST7789_IOCTL(ST7789_CMD cmd, char *data, size_t size)
{
    CS_ENABLE;

    if (cmd != WRITE_DATA)
    {
        DC_CMD;
        SPI_Write(&cmd, CMD_SIZE);
    }

    if (size && (data != NULL))
    {
        DC_DATA;
        SPI_Write(data, size);
    }

    CS_DISABLE;

	return 0;
}

static void LCD_Address_Set(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{
    unsigned short X1, X2, Y1, Y2;
    char data[4] = {};

    if ((USE_HORIZONTAL == 0) || (USE_HORIZONTAL == 1))
    {
        X1 = x1+34;
        X2 = x2+34;
        Y1 = y1;
        Y2 = y2;
    }
    else
    {
        X1 = x1;
        X2 = x2;
        Y1 = y1+34;
        Y2 = y2+34;
    }
    data[0] = X1>>8;
    data[1] = X1&0xFF;
    data[2] = X2>>8;
    data[3] = X2&0xFF;
    ST7789_IOCTL(CASET, data, sizeof(data));

    data[0] = Y1>>8;
    data[1] = Y1&0xFF;
    data[2] = Y2>>8;
    data[3] = Y2&0xFF;
    ST7789_IOCTL(RASET, data, sizeof(data));

    ST7789_IOCTL(RAMWR, NULL, 0);
}

// api
void ST7789Init(void)
{
    char data[8] = {0};
    RES_DISABLE;
    DC_DATA;
    CS_DISABLE;
    BLK_DISABLE;

#if ST7789_USING_SPI
    // nothing to do
#else
    ST7789_SCK_H;
    ST7789_SDA_H;
#endif

    // reset
    RES_ENABLE;
    Delay_ms(30);
    RES_DISABLE;
    Delay_ms(100);

    // open blk
    BLK_ENABLE;
    Delay_ms(100);

    ST7789_IOCTL(SLPOUT, NULL, 0);

#if ST7789_CONFIG
    data[0] = 0;
    data[0] |= PageAddressOrder            << 7;
    data[0] |= ColumnAddressOrder          << 6;
    data[0] |= Page_ColumnOrder            << 5;
    data[0] |= LineAddressOrder            << 4;
    data[0] |= RGB_BGROrder                << 3;
    data[0] |= DisplayDataLatchDataOrder   << 2;
#else
	if(USE_HORIZONTAL == 0) data[1] = 0x00;
	else if(USE_HORIZONTAL == 1) data[1] = 0xC0;
	else if(USE_HORIZONTAL == 2) data[1] = 0x70;
	else data[1] = 0xA0;
#endif
    char MADCTL_data[] = {data[0], data[1]};
    ST7789_IOCTL(MADCTL, MADCTL_data, sizeof(MADCTL_data));

#if ST7789_CONFIG && ControlInterfaceColorFormat
    data[0] = ControlInterfaceColorFormat;
#else
	data[0] = 0x05;
#endif
    char COLMOD_data[] = {data[0]};
    ST7789_IOCTL(COLMOD, COLMOD_data, sizeof(COLMOD_data));

    /* Default
    char PORCTRL_data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
    ST7789_IOCTL(PORCTRL, PORCTRL_data, sizeof(PORCTRL_data));

    char GCTRL_data[] = {0x35};
    ST7789_IOCTL(GCTRL, GCTRL_data, sizeof(GCTRL_data));

    char LCMCTRL_data[] = {0x2C};
    ST7789_IOCTL(LCMCTRL, LCMCTRL_data, sizeof(LCMCTRL_data));

    char VDVVRHEN_data[] = {0x01};
    ST7789_IOCTL(VDVVRHEN, VDVVRHEN_data, sizeof(VDVVRHEN_data));
    */

    char VRHS_data[] = {0x13};
    ST7789_IOCTL(VRHS, VRHS_data, sizeof(VRHS_data));

#if ST7789_CONFIG
    #ifdef LCD_FrameRate
        char FRCTRL2_data[] = {RTNA_V};
        ST7789_IOCTL(FRCTRL2, FRCTRL2_data, sizeof(FRCTRL2_data));
    #endif
#endif

    /* Default
    char PWCTRL1_data[] = {0xA4, 0xA1};
    ST7789_IOCTL(PWCTRL1, PWCTRL1_data, sizeof(PWCTRL1_data));
    */
    char Unknown1_data[] = {0xA1};
    ST7789_IOCTL(Unknown1, Unknown1_data, sizeof(Unknown1_data));

    char PVGAMCTRL_data[] = {0xF0, 0x00, 0x04, 0x04, 0x04, 0x05, 0x29, 
                            0x33, 0x3E, 0x38, 0x12, 0x12, 0x28, 0x30};
    ST7789_IOCTL(PVGAMCTRL, PVGAMCTRL_data, sizeof(PVGAMCTRL_data));

    char NVGAMCTRL_data[] = {0xF0, 0x07, 0x0A, 0x0D, 0x0B, 0x07, 0x28, 
                            0x33, 0x3E, 0x36, 0x14, 0x14, 0x29, 0x32};
    ST7789_IOCTL(NVGAMCTRL, NVGAMCTRL_data, sizeof(NVGAMCTRL_data));

#if ST7789_CONFIG
    #ifdef DisplayInversion
        ST7789_IOCTL(INVOFF, NULL, 0);
    #endif
#else
    ST7789_IOCTL(INVON, NULL, 0);
#endif

    ST7789_IOCTL(SLPOUT, NULL, 0);

    Delay_ms(120);

    ST7789_IOCTL(DISPON, NULL, 0);
}

void LCD_Fill(unsigned short xsta,unsigned short ysta,unsigned short xend,unsigned short yend,unsigned short color)
{
   char x,y;
   int i,j;
   x= color>>8;
   y= color&0xFF;
   char ddata[] = {x,y};
   LCD_Address_Set(xsta,ysta,xend-1,yend-1);

   for(i=ysta;i<yend;i++)
   {                                                           
       for(j=xsta;j<xend;j++)
       {
           ST7789_IOCTL(WRITE_DATA, ddata, sizeof(ddata));
       }
   } 

}
