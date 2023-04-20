
/* *****************************************************************************
 *
 *  st7789v3-1.47inch driver
 *  author: huke
 *  date:   2023-1-27
 *  description: Application Interface
 * 
 * ***************************************************************************/
#ifndef ST7789_API_H
#define ST7789_API_H

#include "htime.h"
#include "board.h"

/*                              User API define                              */
#define ST7789_MS_DELAY(t)          DelayMs(t)

#define USE_HORIZONTAL              1  

#define ST7789_RES_RESET            GPIO_ResetBits(GPIOA, GPIO_Pin_1);
#define ST7789_RES_SET              GPIO_SetBits(GPIOA, GPIO_Pin_1);

#define ST7789_DC_SET               GPIO_SetBits(GPIOA, GPIO_Pin_2);
#define ST7789_DC_RESET             GPIO_ResetBits(GPIOA, GPIO_Pin_2);

#define ST7789_CS_RESET             GPIO_ResetBits(GPIOA, GPIO_Pin_3);
#define ST7789_CS_SET               GPIO_SetBits(GPIOA, GPIO_Pin_3);

#define ST7789_BLK_SET              GPIO_SetBits(GPIOA, GPIO_Pin_4);
#define ST7789_BLK_RESET            GPIO_ResetBits(GPIOA, GPIO_Pin_4);

/* if use gpio-spi */
#define ST7789_USING_SPI        1
#if ST7789_USING_SPI
    // nothing to do
    #define ST7789_SPI_Write(data_ptr,size) do { \
                                                    uint32_t index = 0; \
                                                    while (index < size) {  \
                                                        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); \
                                                        SPI_I2S_SendData(SPI1, *(uint8_t*)(data_ptr+index));  \
                                                        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);    \
                                                        SPI_I2S_ReceiveData(SPI1);  \
                                                        index++;} \
                                                } while(0);
#else
    #define ST7789_SCK_H        GPIO_SetBits(GPIOA, GPIO_Pin_5);
    #define ST7789_SCK_L        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    #define ST7789_SDA_H        GPIO_SetBits(GPIOA, GPIO_Pin_7);
    #define ST7789_SDA_L        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
    #define ST7789_SPI_Write(data_ptr,size) \
            do { \
                    uint32_t index = 0; \
                    while (index < size) {  \
                    for(int i = 0; i < 8; i++) {    \
                        ST7789_SCK_L;   \
                        if ((*(uint8_t*)(data_ptr + index) << i) & 0x80) {ST7789_SDA_H;}   \
                        else {ST7789_SDA_L;}  \
                        ST7789_SCK_H;}  \
                        index++;}    \
                } while(0);
#endif 
/*                              User API define end                           */

#if ((USE_HORIZONTAL == 0) || (USE_HORIZONTAL == 1))
    #define LCD_W 172	
    #define LCD_H 320
#else
    #define LCD_W 320
    #define LCD_H 172
#endif

/* Init Config */
#define ST7789_CONFIG 1

#if ST7789_CONFIG
/* Page Address Order */
    // #define TopToBottom
    // #define BottomToTop

/* Column Address Order */
    // #define LeftToRigh
    // #define RightToLeft

/* Page/Column Order */
    // #define NormalMode
    // #define ReverseMode

/* Line Address Order */
    // #define LCDRefreshTopToBottom
    // #define LCDRefreshBottomToTop

/* RGB/BGR Order */
    // #define RGB
    // #define BGR

/* Display Data Latch Data Order */
    // #define LCDRefreshLeftToRight
    // #define LCDRefreshRightToLeft

/* Control interface color format */
    // #define LCD_12bit_color 
    // #define LCD_16bit_color 
    // #define LCD_18bit_color

/* Frame rate (40--120Hz)  in Normal Mode */
    // #define LCD_FrameRate    80

/*  Display Inversion */
    //  #define DisplayInversion
#endif

/*                            color  define                                   */
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 
#define BRRED 			 0XFC07 
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458 
#define LIGHTGREEN     	 0X841F 
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

/*                            api  prototype                                  */
void ST7789Init(void);
void LCD_Fill(unsigned short xsta,unsigned short ysta,unsigned short xend,unsigned short yend,unsigned short color);
#endif  // ST7789_API_H



