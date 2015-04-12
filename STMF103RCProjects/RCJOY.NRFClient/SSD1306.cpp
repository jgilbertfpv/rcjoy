#include "SSD1306.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "SysTimer.h"

#define SSD_SPI	SPI2
#define OLED_CMD    0
#define OLED_DAT    1

#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64

#define BLENGTH SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8

#define SSD1306_CS_Set()     GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET)
#define SSD1306_CS_Clr()     GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET)

#define SSD1306_RES_Set()    GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_SET)
#define SSD1306_RES_Clr()    GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_RESET)

#define SSD1306_DC_Set()     GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET)
#define SSD1306_DC_Clr()     GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET)

uint8_t OLED_GRAM[128][8];
/*
static uint8_t buffer[BLENGTH] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
	0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x8C, 0x8E, 0x84, 0x00, 0x00, 0x80, 0xF8,
	0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80,
	0x00, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xC7, 0x01, 0x01,
	0x01, 0x01, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF,
	0xFF, 0xFF, 0x00, 0x38, 0xFE, 0xC7, 0x83, 0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF, 0xFF, 0x00, 0x00,
	0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x7F, 0xFF,
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xFF,
	0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x8F,
	0x8F, 0x9F, 0xBF, 0xFF, 0xFF, 0xC3, 0xC0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x01, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
	0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00,
	0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03,
	0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
	0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
	0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
	0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
	0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
	0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
	0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
	0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
	0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
	0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
	0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
	0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
	0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
*/

static void SPIx_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;      // MOSI & CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                     // Chip select
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;      // RESET & D/C
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SSD1306_CS_Set();//RES  
	SSD1306_DC_Clr();//D/C
	SSD1306_RES_Clr();//CS 

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}

//Define the layer1 functions
static unsigned char SPI_Send_Byte(SPI_TypeDef *SPI, u8 TxData)
{
	uint8_t Retry = 0;

	while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_TXE) == RESET)
	{
		if (++Retry > 200)
			return 0;
	}
	SPI_I2S_SendData(SPI, TxData);
	Retry = 0;

	while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{
		if (++Retry > 200)
			return 0;
	}
	return SPI_I2S_ReceiveData(SPI);
}

static void OLED_WriteByte(uint8_t Data, uint8_t Cmd)
{

	SSD1306_CS_Clr();

	if (Cmd)
		SSD1306_DC_Set();
	else
		SSD1306_DC_Clr();

	SPI_Send_Byte(SSD_SPI, Data);

	SSD1306_DC_Set();
	SSD1306_CS_Set();
}


/**
* @brief   sets the positions of the character that will  be displayed.
*
* @param  X: specifies the X position.
* @param Y: specifies the Y position.
* @retval  None
**/

void OLED_SetPos(uint8_t X, uint8_t Y)
{
	OLED_WriteByte(0xb0 + Y, OLED_CMD);
	OLED_WriteByte(((X & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WriteByte((X & 0x0f) | 0x01, OLED_CMD);
}


/**
* @brief  Enables the Display
*
* @param  None
*
* @retval  None
**/
void OLED_DisplayOn(void)
{
	OLED_WriteByte(0X8D, OLED_CMD);
	OLED_WriteByte(0X14, OLED_CMD);
	OLED_WriteByte(0XAF, OLED_CMD);
}

/**
* @brief  Disables the Display
*
* @param  None
*
* @retval  None
**/
void OLED_DisplayOff(void)
{
	OLED_WriteByte(0X8D, OLED_CMD);
	OLED_WriteByte(0X10, OLED_CMD);
	OLED_WriteByte(0XAE, OLED_CMD);
}


void OLED_Refresh_Gram(void)
{
	uint8_t i, n;

	for (i = 0; i < 8; i++)
	{
		OLED_WriteByte(0xb0 + i, OLED_CMD);
		OLED_WriteByte(0x00, OLED_CMD);
		OLED_WriteByte(0x10, OLED_CMD);
		for (n = 0; n < 128; n++)
		{
			OLED_WriteByte(OLED_GRAM[n][i], OLED_DAT);
		}
	}
}


void OLED_ClearDisplay(void)
{
	uint8_t i, n;

	for (i = 0; i < 8; i++)
	{
		for (n = 0; n < 128; n++)
		{
			OLED_GRAM[n][i] = 0x00;
		}
	}
	OLED_Refresh_Gram();
}


/**
* @brief  Displays a pixel.
*
* @param  X: pixel x.
* @param  X: pixel y.
* @param  Fill: wheher recerses the point.
*  This paramter can ba one of following value;
*  @arg Fill: where Fill can be 0 or 1
*
* @retval None
**/

void OLED_DrawPoint(uint8_t X, uint8_t Y, uint8_t Fill)
{
	uint8_t Pos, Bx, Temp = 0;

	if (X > 127 || Y > 63)
		return;
	Pos = 7 - Y / 8;
	Bx = Y % 8;
	Temp = 1 << (7 - Bx);
	if (Fill)
	{
		OLED_GRAM[X][Pos] |= Temp;
	}
	else
	{
		OLED_GRAM[X][Pos] &= ~Temp;
	}
}

void OLED_DrawChar(uint8_t x, uint8_t row, char c, uint8_t* font)
{
	if (x > 127) return;
	if (row > 7) return;

	uint32_t idx = (c - 32) * 5;

	for (u8 i = 0; i < 5 && x + i < 128; i++)
		OLED_GRAM[x + i][row] = *(font + idx + i);
}

void OLED_DrawString(uint8_t x, uint8_t row, char* str, uint8_t* font)
{
	for (u8 i = 0; *(str + i); i++)
		OLED_DrawChar(x + i * 6, row, *(str + i), font);
}

/**
* @brief  Dispalys a full rectangle.
*
* @param  X1: specifies the upper left corner X position of the rectangle
* @param  Y1: specifies the upper left corner Y position of the rectangle
* @param  X2: specifies the lower right corner X positon of the rectangle
* @param  Y2: specifies the lower right corner Y positon of the rectangle
*
* @retval  None
**/
void OLED_Fill(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t Dot)
{
	uint8_t X, Y;

	for (X = X1; X <= X2; X++)
	{
		for (Y = Y1; Y <= Y2; Y++)
			OLED_DrawPoint(X, Y, Dot);
	}
	OLED_Refresh_Gram();
}

void OLED_Init(void)
{
	SPIx_Init();

	SSD1306_RES_Set();

	OLED_WriteByte(0xAE, OLED_CMD);//--turn off oled panel
	OLED_WriteByte(0x00, OLED_CMD);//---set low column address
	OLED_WriteByte(0x10, OLED_CMD);//---set high column address
	OLED_WriteByte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteByte(0x81, OLED_CMD);//--set contrast control register
	OLED_WriteByte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WriteByte(0xA1, OLED_CMD);//--Set SEG/Column Mapping     
	OLED_WriteByte(0xC0, OLED_CMD);//Set COM/Row Scan Direction   
	OLED_WriteByte(0xA6, OLED_CMD);//--set normal display
	OLED_WriteByte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WriteByte(0x3f, OLED_CMD);//--1/64 duty
	OLED_WriteByte(0xD3, OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteByte(0x00, OLED_CMD);//-not offset
	OLED_WriteByte(0xd5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WriteByte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteByte(0xD9, OLED_CMD);//--set pre-charge period
	OLED_WriteByte(0xF1, OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteByte(0xDA, OLED_CMD);//--set com pins hardware configuration
	OLED_WriteByte(0x12, OLED_CMD);
	OLED_WriteByte(0xDB, OLED_CMD);//--set vcomh
	OLED_WriteByte(0x40, OLED_CMD);//Set VCOM Deselect Level
	OLED_WriteByte(0x20, OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteByte(0x02, OLED_CMD);//
	OLED_WriteByte(0x8D, OLED_CMD);//--set Charge Pump enable/disable
	OLED_WriteByte(0x14, OLED_CMD);//--set(0x10) disable
	OLED_WriteByte(0xA4, OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteByte(0xA6, OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteByte(0xAF, OLED_CMD);//--turn on oled panel

	OLED_ClearDisplay();
}


