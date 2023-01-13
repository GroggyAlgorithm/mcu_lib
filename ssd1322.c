///**
 //* \file ssd1322.c
 //* \author Tim Robbins - R&D Engineer, Atech Training
 //*/
//
//
//#include "ssd1322.h"
//
//
//#if !defined(SSD1322_C) && defined(__INCLUDED_SSD1322__)
//#define SSD1322_C	1
//
//#include <avr/io.h>
//#include "mcuDelays.h"
//#include "mcuUtils.h"
//#include "mcuUtils.h"
//
//#define SSD1322_CMD_PORT		PORTD
//#define SSD1322_CS_PIN_POS		0
//#define SSD1322_RW_PIN_POS		1
//#define SSD1322_E_PIN_POS		2
//#define SSD1322_DC_PIN_POS		3
//
//#define SSD1322_RD_PIN_POS		1
//#define SSD1322_WR_PIN_POS		2
//
//#define SSD1322_DATA_PORT		PORTB
//#define SSD1322_DATA_READ		PINB
//#define SSD1322_DATA_DIR		DDRB
//
//
//
//
//static uint8_t ssd1322CsPinPositions[] =
//{
	//SSD1322_CS_PIN_POS
//};
//
//static uint8_t currentSsd1322Display = 0;
//
//#if defined(SSD1322_USE_SPI) && SSD1322_USE_SPI == 1
//
//#include "spi.h"
//
//#endif
//
//
//#if defined(SSD1322_6080_PARALLEL) && SSD1322_6080_PARALLEL == 1
//
//
//void SSD1322WriteCommand(uint8_t cmd)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_RW_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display])|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_DATA_PORT = cmd;
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteData(uint8_t data)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS)|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_RW_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//SSD1322_DATA_PORT = data;
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteCommandArray(uint8_t cmds[], uint16_t cmdLen)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_RW_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display])|(1 << SSD1322_DC_PIN_POS));
	//for(uint16_t i = 0; i < cmdLen; i++)
	//{
		//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS));
		//SSD1322_DATA_PORT = cmds[i];
		//delayForMicroseconds(1);
		//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
		//delayForMicroseconds(1);
	//}
	//
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteDataArray(uint8_t datas[], uint16_t dataLen)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS)|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_RW_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//
	//for(uint16_t i = 0; i < dataLen; i++)
	//{
		//SSD1322_CMD_PORT |= ((1 << SSD1322_E_PIN_POS));
		//SSD1322_DATA_PORT = datas[i];
		//delayForMicroseconds(1);
		//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
		//delayForMicroseconds(1);
	//}
	//
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_E_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//#elif defined(SSD1322_8080_PARALLEL) && SSD1322_8080_PARALLEL == 1
//
//
//void SSD1322WriteCommand(uint8_t cmd)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_RD_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display])|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_DATA_PORT = cmd;
	//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteData(uint8_t data)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_RD_PIN_POS)|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//SSD1322_DATA_PORT = data;
	//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteCommandArray(uint8_t cmds[], uint16_t cmdLen)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_RD_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display])|(1 << SSD1322_DC_PIN_POS));
	//for(uint16_t i = 0; i < cmdLen; i++)
	//{
		//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS));
		//SSD1322_DATA_PORT = cmds[i];
		//delayForMicroseconds(1);
		//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
		//delayForMicroseconds(1);
	//}
	//
	//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteDataArray(uint8_t datas[], uint16_t dataLen)
//{
	//SSD1322_CMD_PORT |= ((1 << SSD1322_RD_PIN_POS)|(1 << SSD1322_DC_PIN_POS));
	//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS)|(1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//
	//for(uint16_t i = 0; i < dataLen; i++)
	//{
		//SSD1322_CMD_PORT &= ~((1 << SSD1322_WR_PIN_POS));
		//SSD1322_DATA_PORT = datas[i];
		//delayForMicroseconds(1);
		//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
		//delayForMicroseconds(1);
	//}
	//
	//SSD1322_CMD_PORT |= ((1 << SSD1322_WR_PIN_POS));
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//#elif defined(SSD1322_3_WIRE_SERIAL) && SSD1322_3_WIRE_SERIAL == 1
//
//
//void SSD1322WriteCommand(uint8_t cmd)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//SSD1322_TRANSMIT(cmd);
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteData(uint8_t data)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//SSD1322_TRANSMIT(data);
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//
//void SSD1322WriteCommandArray(uint8_t cmds[], uint16_t cmdLen)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//for(uint16_t i = 0; i < cmdLen; i++)
	//{
		//SSD1322_TRANSMIT(cmds[i]);
		//delayForMicroseconds(1);
	//}
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteDataArray(uint8_t datas[], uint16_t dataLen)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//for(uint16_t i = 0; i < dataLen; i++)
	//{
		//SSD1322_TRANSMIT(datas[i]);
		//delayForMicroseconds(1);
	//}
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//
//#elif defined(SSD1322_4_WIRE_SERIAL) && SSD1322_4_WIRE_SERIAL == 1
//
//
//void SSD1322WriteCommand(uint8_t cmd)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]) | (1 << SSD1322_DC_PIN_POS) );
	//SSD1322_TRANSMIT(cmd);
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteData(uint8_t data)
//{
	//SSD1322_CMD_PORT |= (1 << SSD1322_DC_PIN_POS);
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//SSD1322_TRANSMIT(data);
	//delayForMicroseconds(1);
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteCommandArray(uint8_t cmds[], uint16_t cmdLen)
//{
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]) | (1 << SSD1322_DC_PIN_POS) );
	//for(uint16_t i = 0; i < cmdLen; i++)
	//{
		//SSD1322_TRANSMIT(cmds[i]);
		//delayForMicroseconds(1);
	//}
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//
//void SSD1322WriteDataArray(uint8_t datas[], uint16_t dataLen)
//{
	//SSD1322_CMD_PORT |= (1 << SSD1322_DC_PIN_POS);
	//SSD1322_CMD_PORT &= ~((1 << ssd1322CsPinPositions[currentSsd1322Display]));
	//for(uint16_t i = 0; i < dataLen; i++)
	//{
		//SSD1322_TRANSMIT(datas[i]);
		//delayForMicroseconds(1);
	//}
	//SSD1322_CMD_PORT |= ((1 << ssd1322CsPinPositions[currentSsd1322Display]));
//}
//
//#endif
//
//
//
//
//
//void SSD1322SetCommandLock(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_COMMAND_LOCK);
	//SSD1322WriteData(0x12 | val);
//}
//void SSD1322SetDisplayOnOff(uint8_t isOn)
//{
	//if(isOn) SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_ON);
	//else  SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_OFF);
//}
//void SSD1322SetDisplaySleep(uint8_t isSleeping)
//{
	//if(isSleeping) SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_OFF);
	//else  SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_ON);
//}
//void SSD1322SetColumnAddress(uint8_t val1 ,uint8_t val2)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_COLUMN_ADDRESS);
	//SSD1322WriteData(val1);
	//SSD1322WriteData(val2);
//}
//void SSD1322SetRowAddress(uint8_t val1,uint8_t val2)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_ROW_ADDRESS);
	//SSD1322WriteData(val1);
	//SSD1322WriteData(val2);
//}
//void SSD1322SetWriteRam()
//{
	//SSD1322WriteCommand(SSD1322_CMD_WRITE_RAM);
//}
//void SSD1322SetDisplayClock(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_FRONT_CLOCK_DIV);
	//SSD1322WriteData(val);
//}
//void SSD1322SetMultiplexRatio(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_MUX_RATIO);
	//SSD1322WriteData(val);
//}
//void SSD1322SetDisplayOffset(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_OFFSET);
	//SSD1322WriteData(val);
//}
//void SSD1322SetStartLine(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_START_LINE);
	//SSD1322WriteData(val);
	//
//}
//void SSD1322SetRemapFormat(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_REMAP);
	//SSD1322WriteData(val);
	//SSD1322WriteData(0x11);
//}
//void SSD1322SetGPIO(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_GPIO);
	//SSD1322WriteData(val);
//}
//void SSD1322SetFunctionSelection(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_FUNCTION_SELECT);
	//SSD1322WriteData(val);
//}
//void SSD1322SetDisplayEnhancementA(uint8_t val1, uint8_t val2)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_A);
	//SSD1322WriteData(0xA0 | val1);
	//SSD1322WriteData(0x05 | val2);
//}
//void SSD1322SetContrastCurrent(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_CONTRAST_CURRENT);
	//SSD1322WriteData(val);
//}
//void SSD1322SetMasterCurrent(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_MASTER_CONTRAST_CURRENT_CONTROL);
	//SSD1322WriteData(val);
//}
//void SSD1322SetGrayScaleTable()
//{
	//SSD1322WriteCommand(0xB8);			// Set Gray Scale Table
	//SSD1322WriteData(0x0C);			//   Gray Scale Level 1
	//SSD1322WriteData(0x18);			//   Gray Scale Level 2
	//SSD1322WriteData(0x24);			//   Gray Scale Level 3
	//SSD1322WriteData(0x30);			//   Gray Scale Level 4
	//SSD1322WriteData(0x3C);			//   Gray Scale Level 5
	//SSD1322WriteData(0x48);			//   Gray Scale Level 6
	//SSD1322WriteData(0x54);			//   Gray Scale Level 7
	//SSD1322WriteData(0x60);			//   Gray Scale Level 8
	//SSD1322WriteData(0x6C);			//   Gray Scale Level 9
	//SSD1322WriteData(0x78);			//   Gray Scale Level 10
	//SSD1322WriteData(0x84);			//   Gray Scale Level 11
	//SSD1322WriteData(0x90);			//   Gray Scale Level 12
	//SSD1322WriteData(0x9C);			//   Gray Scale Level 13
	//SSD1322WriteData(0xA8);			//   Gray Scale Level 14
	//SSD1322WriteData(0xB4);			//   Gray Scale Level 15
	//SSD1322WriteCommand(0x00);			// Enable Gray Scale Table
//}
//void SSD1322SetLinearGrayScaleTable()
//{
	//SSD1322WriteCommand(SSD1322_CMD_USE_DEFAULT_GRAY_SCALE);
//}
//void SSD1322SetPhaseLength(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_PHASE_LENGTH);
	//SSD1322WriteData(val);
//}
//void SSD1322SetDisplayEnhancementB(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_B);
	//SSD1322WriteData(0x82 | val);
	//SSD1322WriteData(SSD1322_CMD_DISPLAY_ENHANCEMENT_B_END);
//}
//void SSD1322SetPrechargeVoltage(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_PRECHARGE_VOLTAGE);
	//SSD1322WriteData(val);
//}
//void SSD1322SetPrechargePeriod(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_2ND_PRECHARGE_PERIOD);
	//SSD1322WriteData(val);
//}
//void SSD1322SetVCOMH(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_VCOMH);
	//SSD1322WriteData(val);
//}
//void SSD1322SetDisplayMode(uint8_t val)
//{
	//SSD1322WriteCommand(SSD1322_CMD_SET_DIPLAY_MODE | val);
//}
//void SSD1322SetPartialDisplay(uint8_t val1 ,uint8_t val2 ,uint8_t val3)
//{
	//SSD1322WriteCommand(SSD1322_CMD_ENABLE_PARTIAL_DISPLAY | val1);
	//
	//if(val1 == 0)
	//{
		//SSD1322WriteData(val2);
		//SSD1322WriteData(val3);
	//}
//}
//
//
//
//void SSD1322Init()
//{
	////Initialize the displays init sequences
	//uint8_t init_sequence [] = {    // Initialization Sequence
		//,
		//SSD1322_CMD_UNLOCK_COMMANDS,
		//SSD1322_CMD_SET_DISPLAY_OFF,
		//SSD1322_CMD_SET_COLUMN_ADDRESS,
		//0x1c,0x3F,
		//SSD1322_CMD_SET_ROW_ADDRESS,
		//0x00,0x3F,
		//SSD1322_CMD_SET_FRONT_CLOCK_DIV,
		//0x91, //80 frames per sec
		//SSD1322_CMD_SET_MUX_RATIO,
		//0x3F,
		//SSD1322_CMD_SET_DISPLAY_OFFSET,
		//0x00,
		//,
		//0x00,
		//,
		//0x14,
		//SSD1322_CMD_SET_GPIO,
		//0x00,
		//SSD1322_CMD_FUNCTION_SELECT,
		//0x01,
		//SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_A,
		//0xA0, 0xFD,
		//SSD1322_CMD_SET_CONTRAST_CURRENT,
		//0x9F,
		//SSD1322_CMD_SET_MASTER_CONTRAST_CURRENT_CONTROL,
		//0x0F,
		//SSD1322_CMD_USE_DEFAULT_GRAY_SCALE,
		//SSD1322_CMD_SET_PHASE_LENGTH,
		//0xE2,
		//SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_B,
		//0x20,
		//SSD1322_CMD_SET_PRECHARGE_VOLTAGE,
		//0x1F,
		//SSD1322_CMD_SET_2ND_PRECHARGE_PERIOD,
		//0x08,
		//SSD1322_CMD_SET_VCOMH,
		//0x07,
		//SSD1322_CMD_SET_DIPLAY_MODE_NORMAL,
		//SSD1322_CMD_SET_PARTIAL_DISPLAY,
		//0x01,0x00,0x00,
		//SSD1322_CMD_DISABLE_SLEEP
		//
		//
	//};
//}
//
//
//
//
////void SSD1322DrawRectangle(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e)
//
//void SSD1322ClearPixel()
//{
	//unsigned int i, j;
	//
	//SSD1322SetColumnAddress(0x1C,0x5B);
	//SSD1322SetRowAddress(0x00,0x3F);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<64;i++) //Columns
	//{
		//for(j=0;j<128;j++) //Rows
		//{
			//SSD1322WriteData(0x00);
			//delayForMicroseconds(100);
		//}
	//}
//}
//
//void SSD1322FillPixel()
//{
	//unsigned int i, j;
	//
	//SSD1322SetColumnAddress(0x1C,0x5B); //1C & 5B = DISPLAY Start & End address.
	//SSD1322SetRowAddress(0x00,0x3F);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<32;i++) //Columns
	//{
		//for(j=0;j<64;j++) //Rows
		//{
			//SSD1322WriteData(0xFF);
			//delayForMicroseconds(100);
			//SSD1322WriteData(0x00);
			//delayForMicroseconds(100);
		//}
		//for(j=0;j<64;j++) //Rows
		//{
			//SSD1322WriteData(0x00);
			//delayForMicroseconds(100);
			//SSD1322WriteData(0xFF);
			//delayForMicroseconds(100);
		//}
	//}
//}
//
//
//void SSD1322ImageDisplay(unsigned char *image)
//{
	//unsigned int i, j, buff;
	//SSD1322SetRemapFormat(0x14,0x11);
	////SSD1322SetRemapFormat(0x06,0x11); // To Flip Orientation 180 Degrees
	//SSD1322SetColumnAddress(0x1C,0x5B);
	//SSD1322SetRowAddress(0x00,0x3F);
	//SSD1322SetWriteRam();
	//
	//for(i=0;i<64;i++) //Columns
	//{
		//for(j=0;j<32;j++) //Rows
		//{
			//buff = *image;
			//buff = ((buff >> 6) & 0x03);
			//if(buff == 0x03){SSD1322WriteData(0xFF);}
			//else if(buff == 0x02){SSD1322WriteData(0xF0);}
			//else if(buff == 0x01){SSD1322WriteData(0x0F);}
			//else SSD1322WriteData(0x00);
//
			//buff = *image;
			//buff = ((buff >> 4) & 0x03);
			//if(buff == 0x03){SSD1322WriteData(0xFF);}
			//else if(buff == 0x02){SSD1322WriteData(0xF0);}
			//else if(buff == 0x01){SSD1322WriteData(0x0F);}
			//else SSD1322WriteData(0x00);
//
			//buff = *image;
			//buff = ((buff >> 2) & 0x03);
			//if(buff == 0x03){SSD1322WriteData(0xFF);}
			//else if(buff == 0x02){SSD1322WriteData(0xF0);}
			//else if(buff == 0x01){SSD1322WriteData(0x0F);}
			//else SSD1322WriteData(0x00);
//
			//buff = *image;
			//buff = (buff & 0x03);
			//if(buff == 0x03){SSD1322WriteData(0xFF);}
			//else if(buff == 0x02){SSD1322WriteData(0xF0);}
			//else if(buff == 0x01){SSD1322WriteData(0x0F);}
			//else SSD1322WriteData(0x00);
//
			//image++;
		//}
	//}
//}
//
//
//void SSD1322DrawRectangle(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e)
//{
	//unsigned char i,j,k,l;
//
	//k=a%4;
	//if(k == 0)
	//{
		//l=(a/4)-1;
	//}
	//else
	//{
		//l=a/4;
	//}
//
	//
	//SSD1322SetColumnAddress(Shift+b,Shift+c);
	//SSD1322SetRowAddress(d,(d+a-1));
	//SSD1322SetWriteRam();
	//for(i=0;i<(c-b+1);i++)
	//{
		//for(j=0;j<a;j++)
		//{
			//SSD1322WriteData(Data);
			//SSD1322WriteData(Data);
		//}
	//}
//
	//SSD1322SetColumnAddress(Shift+(c-l),Shift+c);
	//SSD1322SetRowAddress(d+a,e-a);
	//SSD1322SetWriteRam();
	//for(i=0;i<(e-d+1);i++)
	//{
		//for(j=0;j<(l+1);j++)
		//{
			//if(j == 0)
			//{
				//switch(k)
				//{
					//case 0:
					//SSD1322WriteData(Data);
					//SSD1322WriteData(Data);
					//break;
					//case 1:
					//SSD1322WriteData(0x00);
					//SSD1322WriteData(Data&0x0F);
					//break;
					//case 2:
					//SSD1322WriteData(0x00);
					//SSD1322WriteData(Data);
					//break;
					//case 3:
					//SSD1322WriteData(Data&0x0F);
					//SSD1322WriteData(Data);
					//break;
				//}
			//}
			//else
			//{
				//SSD1322WriteData(Data);
				//SSD1322WriteData(Data);
			//}
		//}
	//}
//
	//SSD1322SetColumnAddress(Shift+b,Shift+c);
	//SSD1322SetRowAddress((e-a+1),e);
	//SSD1322SetWriteRam();
	//for(i=0;i<(c-b+1);i++)
	//{
		//for(j=0;j<a;j++)
		//{
			//SSD1322WriteData(Data);
			//SSD1322WriteData(Data);
		//}
	//}
//
	//SSD1322SetColumnAddress(Shift+b,Shift+(b+l));
	//SSD1322SetRowAddress(d+a,e-a);
	//SSD1322SetWriteRam();
	//for(i=0;i<(e-d+1);i++)
	//{
		//for(j=0;j<(l+1);j++)
		//{
			//if(j == l)
			//{
				//switch(k)
				//{
					//case 0:
					//SSD1322WriteData(Data);
					//SSD1322WriteData(Data);
					//break;
					//case 1:
					//SSD1322WriteData(Data&0xF0);
					//SSD1322WriteData(0x00);
					//break;
					//case 2:
					//SSD1322WriteData(Data);
					//SSD1322WriteData(0x00);
					//break;
					//case 3:
					//SSD1322WriteData(Data);
					//SSD1322WriteData(Data&0xF0);
					//break;
				//}
			//}
			//else
			//{
				//SSD1322WriteData(Data);
				//SSD1322WriteData(Data);
			//}
		//}
	//}
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Regular Pattern (Full Screen)
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322FillRAM(unsigned char Data)
//{
	//unsigned char i,j;
//
	//SSD1322SetColumnAddress(0x00,0x77);
	//SSD1322SetRowAddress(0x00,0x7F);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<128;i++)
	//{
		//for(j=0;j<120;j++)
		//{
			//SSD1322WriteData(Data);
			//SSD1322WriteData(Data);
		//}
	//}
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Regular Pattern (Partial or Full Screen)
////
////    a: Column Address of Start
////    b: Column Address of End (Total Columns Divided by 4)
////    c: Row Address of Start
////    d: Row Address of End
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322FillBlock(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
//{
	//unsigned char i,j;
	//
	//SSD1322SetColumnAddress(Shift+a,Shift+b);
	//SSD1322SetRowAddress(c,d);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<(d-c+1);i++)
	//{
		//for(j=0;j<(b-a+1);j++)
		//{
			//SSD1322WriteData(Data);
			//SSD1322WriteData(Data);
		//}
	//}
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Checkboard (Full Screen)
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322DisplayCheckerboard()
//{
	//unsigned char i,j;
	//
	//SSD1322SetColumnAddress(0x00,0x77);
	//SSD1322SetRowAddress(0x00,0x7F);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<64;i++)
	//{
		//for(j=0;j<120;j++)
		//{
			//SSD1322WriteData(0xF0);
			//SSD1322WriteData(0xF0);
		//}
		//for(j=0;j<120;j++)
		//{
			//SSD1322WriteData(0x0F);
			//SSD1322WriteData(0x0F);
		//}
	//}
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Gray Scale Bar (Full Screen)
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322DisplayGrayscaleBar()
//{
	//Max_Column = 0x3F;
	//Max_Row = 0x3F;
	//// Level 16 => Column 1~16
	//Fill_Block_25664(0xFF,0x00,0x03,0x00,Max_Row);
//
	//// Level 15 => Column 17~32
	//Fill_Block_25664(0xEE,0x04,0x07,0x00,Max_Row);
//
	//// Level 14 => Column 33~48
	//Fill_Block_25664(0xDD,0x08,0x0B,0x00,Max_Row);
//
	//// Level 13 => Column 49~64
	//Fill_Block_25664(0xCC,0x0C,0x0F,0x00,Max_Row);
//
	//// Level 12 => Column 65~80
	//Fill_Block_25664(0xBB,0x10,0x13,0x00,Max_Row);
//
	//// Level 11 => Column 81~96
	//Fill_Block_25664(0xAA,0x14,0x17,0x00,Max_Row);
//
	//// Level 10 => Column 97~112
	//Fill_Block_25664(0x99,0x18,0x1B,0x00,Max_Row);
//
	//// Level 9 => Column 113~128
	//Fill_Block_25664(0x88,0x1C,0x1F,0x00,Max_Row);
//
	//// Level 8 => Column 129~144
	//Fill_Block_25664(0x77,0x20,0x23,0x00,Max_Row);
//
	//// Level 7 => Column 145~160
	//Fill_Block_25664(0x66,0x24,0x27,0x00,Max_Row);
//
	//// Level 6 => Column 161~176
	//Fill_Block_25664(0x55,0x28,0x2B,0x00,Max_Row);
//
	//// Level 5 => Column 177~192
	//Fill_Block_25664(0x44,0x2C,0x2F,0x00,Max_Row);
//
	//// Level 4 => Column 193~208
	//Fill_Block_25664(0x33,0x30,0x33,0x00,Max_Row);
//
	//// Level 3 => Column 209~224
	//Fill_Block_25664(0x22,0x34,0x37,0x00,Max_Row);
//
	//// Level 2 => Column 225~240
	//Fill_Block_25664(0x11,0x38,0x3B,0x00,Max_Row);
//
	//// Level 1 => Column 241~256
	//Fill_Block_25664(0x00,0x3C,Max_Column,0x00,Max_Row);
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Character (5x7)
////
////    a: Database
////    b: Ascii
////    c: Start X Address
////    d: Start Y Address
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322ShowFont5x7(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
//{
	//unsigned char *Src_Pointer=0;
	//unsigned char i,Font,MSB_1,LSB_1,MSB_2,LSB_2;
//
	//switch(a)
	//{
		//case 1:
		//Src_Pointer=&Ascii_1[(b-1)][0];
		//break;
		//case 2:
		////Src_Pointer=&Ascii_2[(b-1)][0];
		//break;
	//}
//
	//Set_Remap_Format_25664(0x15);
	//for(i=0;i<=1;i++)
	//{
		//MSB_1=*Src_Pointer;
		//Src_Pointer++;
		//if(i == 1)
		//{
			//LSB_1=0x00;
			//MSB_2=0x00;
			//LSB_2=0x00;
		//}
		//else
		//{
			//LSB_1=*Src_Pointer;
			//Src_Pointer++;
			//MSB_2=*Src_Pointer;
			//Src_Pointer++;
			//LSB_2=*Src_Pointer;
			//Src_Pointer++;
		//}
		//SSD1322SetColumnAddress(Shift+c,Shift+c);
		//SSD1322SetRowAddress(d,d+7);
		//SSD1322SetWriteRam();
//
		//Font=((MSB_1&0x01)<<4)|(LSB_1&0x01);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x01)<<4)|(LSB_2&0x01);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x02)<<3)|((LSB_1&0x02)>>1);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x02)<<3)|((LSB_2&0x02)>>1);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x04)<<2)|((LSB_1&0x04)>>2);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x04)<<2)|((LSB_2&0x04)>>2);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x08)<<1)|((LSB_1&0x08)>>3);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x08)<<1)|((LSB_2&0x08)>>3);
		//Font=Font|(Font<<1)|(Font<<2)|(Font<<3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x10)<<3)|((LSB_1&0x10)>>1);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x10)<<3)|((LSB_2&0x10)>>1);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x20)<<2)|((LSB_1&0x20)>>2);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x20)<<2)|((LSB_2&0x20)>>2);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
//
		//Font=((MSB_1&0x40)<<1)|((LSB_1&0x40)>>3);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
		//Font=((MSB_2&0x40)<<1)|((LSB_2&0x40)>>3);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
//
		//Font=(MSB_1&0x80)|((LSB_1&0x80)>>4);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
		//Font=(MSB_2&0x80)|((LSB_2&0x80)>>4);
		//Font=Font|(Font>>1)|(Font>>2)|(Font>>3);
		//SSD1322WriteData(Font);
//
		//c++;
	//}
	//Set_Remap_Format_25664(0x14);
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show String
////
////    a: Database
////    b: Start X Address
////    c: Start Y Address
////    * Must write "0" in the end...
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322ShowString5x7(unsigned char a, unsigned char *Data_Pointer, unsigned char b, unsigned char c)
//{
	//unsigned char *Src_Pointer;
//
	//Src_Pointer=Data_Pointer;
	//Show_Font57_25664(1,96,b,c);			// No-Break Space
	////   Must be written first before the string start...
//
	//while(1)
	//{
		//Show_Font57_25664(a,*Src_Pointer,b,c);
		//Src_Pointer++;
		//b+=2;
		//if(*Src_Pointer == 0) break;
	//}
//}
//
//
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
////  Show Pattern (Partial or Full Screen)
////
////    a: Column Address of Start
////    b: Column Address of End (Total Columns Divided by 4)
////    c: Row Address of Start
////    d: Row Address of End
////-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//void SSD1322ShowPattern(unsigned char *Data_Pointer, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
//{
	//unsigned char *Src_Pointer;
	//unsigned char i,j;
	//
	//Src_Pointer=Data_Pointer;
	//SSD1322SetColumnAddress(a,b);
	//SSD1322SetRowAddress(c,d);
	//SSD1322SetWriteRam();
//
	//for(i=0;i<(d-c+1);i++)
	//{
		//for(j=0;j<(b-a+1);j++)
		//{
			//SSD1322WriteData(*Src_Pointer);
			//Src_Pointer++;
			//SSD1322WriteData(*Src_Pointer);
			//Src_Pointer++;
		//}
	//}
//}
//
//
//
//
//
//
//
//
//
//#endif