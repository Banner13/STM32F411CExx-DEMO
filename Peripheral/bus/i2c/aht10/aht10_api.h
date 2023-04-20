
/* *****************************************************************************
 *
 *  AHT10 driver
 *  author: huke
 *  date:   2023-4-2
 *  description: Application Interface
 * 
 * ***************************************************************************/
#ifndef AHT10_API_H
#define AHT10_API_H

/*                              User API define                              */
/* if use gpio-i2c */
void AHT10_SCL_Low(void);
void AHT10_SCL_High(void);
void AHT10_SDA_Low(void);
void AHT10_SDA_High(void);
void AHT10_SDA_Mode_R(void);
void AHT10_SDA_Mode_W(void);
void AHT10_UsDelay(unsigned int);
void AHT10_MsDelay(unsigned int);
char AHT10_SDA_Read(void);

#endif  // AHT10_API_H

