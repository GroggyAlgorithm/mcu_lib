///**
 //* \file ssd1322.c
 //* \author Tim Robbins - R&D Engineer, Atech Training
 //*/ 
//
//
//#ifndef __SSD1322_H__
//#define __SSD1322_H__			1
//
//#define __INCLUDED_SSD1322__	1
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include <avr/io.h>
//#include "config.h"
//
//#define SSD1322_6080_PARALLEL	1
//#define SSD1322_8080_PARALLEL	1
//#define SSD1322_3_WIRE_SERIAL	1
//#define SSD1322_4_WIRE_SERIAL	1
//
//#define SSD1322_USE_SPI			1
//
//
//
//
//#define SSD1322_CMD_ENABLE_GRAY_SCALE				0x00
//#define SSD1322_CMD_SET_COLUMN_ADDRESS				0x15
//#define SSD1322_CMD_WRITE_RAM						0x5C
//#define SSD1322_CMD_READ_RAM						0x5D
//#define SSD1322_CMD_SET_ROW_ADDRESS					0x75
//#define SSD1322_CMD_SET_REMAP						0xA0
//#define SSD1322_CMD_SET_DISPLAY_START_LINE			0xA1
//#define SSD1322_CMD_SET_DISPLAY_OFFSET				0xA2
//#define SSD1322_CMD_SET_DIPLAY_MODE					0xA4
//#define SSD1322_CMD_SET_DIPLAY_MODE_FULL_OFF		0xA4
//#define SSD1322_CMD_SET_DIPLAY_MODE_FULL_ON			0xA5
//#define SSD1322_CMD_SET_DIPLAY_MODE_NORMAL			0xA6
//#define SSD1322_CMD_SET_DISPLAY_MODE_INVERSE		0xA7
//#define SSD1322_CMD_ENABLE_PARTIAL_DISPLAY			0xA8
//#define SSD1322_CMD_EXIT_PARTIAL_DISPLAY			0xA9
//#define SSD1322_CMD_FUNCTION_SELECT					0xAB
//#define SSD1322_CMD_SET_DISPLAY_OFF					0xAE
//#define SSD1322_CMD_ENABLE_SLEEP					0xAE
//#define SSD1322_CMD_SET_DISPLAY_ON					0xAF
//#define SSD1322_CMD_DISABLE_SLEEP					0xAF
//#define SSD1322_CMD_SET_PHASE_LENGTH				0xB1
//#define SSD1322_CMD_PHASE_1_LENGTH_5_DCLKS			0x02
//#define SSD1322_CMD_PHASE_1_LENGTH_7_DCLKS			0x03
//#define SSD1322_CMD_PHASE_1_LENGTH_9_DCLKS			0x04
//#define SSD1322_CMD_PHASE_1_LENGTH_31_DCLKS			0x0F
//#define SSD1322_CMD_PHASE_2_LENGTH_3_DCLKS			0x30
//#define SSD1322_CMD_PHASE_2_LENGTH_7_DCLKS			0x70
//#define SSD1322_CMD_PHASE_2_LENGTH_15_DCLKS			0xF0
//#define SSD1322_CMD_SET_FRONT_CLOCK_DIV				0xB3
//#define SSD1322_CMD_FRONT_CLK_DIV_1					0x00
//#define SSD1322_CMD_FRONT_CLK_DIV_2					0x01
//#define SSD1322_CMD_FRONT_CLK_DIV_4					0x02
//#define SSD1322_CMD_FRONT_CLK_DIV_8					0x03
//#define SSD1322_CMD_FRONT_CLK_DIV_16				0x04
//#define SSD1322_CMD_FRONT_CLK_DIV_32				0x05
//#define SSD1322_CMD_FRONT_CLK_DIV_64				0x06
//#define SSD1322_CMD_FRONT_CLK_DIV_128				0x07
//#define SSD1322_CMD_FRONT_CLK_DIV_256				0x08
//#define SSD1322_CMD_FRONT_CLK_DIV_512				0x09
//#define SSD1322_CMD_FRONT_CLK_DIV_1024				0x0A
//#define SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_A		0xB4
//#define SSD1322_CMD_ENHANCEMENT_A_EXTERNAL_VSL		(0xA0 | 0b00)
//#define SSD1322_CMD_ENHANCEMENT_A_INTERNAL_VSL		(0xA0 | 0b00)
//#define SSD1322_CMD_ENHANCEMENT_A_ENHANCED_LOW_GS	(0x05 | 0b11111000)
//#define SSD1322_CMD_ENHANCEMENT_A_NORMAL			(0x05 | 0b10110000)
//#define SSD1322_CMD_SET_GPIO						0xB5
//#define SSD1322_CMD_SET_2ND_PRECHARGE_PERIOD		0xB6
//#define SSD1322_CMD_SET_GRAY_SCALE					0xB8
//#define SSD1322_CMD_USE_DEFAULT_GRAY_SCALE			0xB9
//#define SSD1322_CMD_SET_PRECHARGE_VOLTAGE			0xBB
//#define SSD1322_CMD_SET_VCOMH						0xBE
//#define SSD1322_CMD_SET_CONTRAST_CURRENT			0xC1
//#define SSD1322_CMD_SET_MASTER_CONTRAST_CURRENT_CONTROL	0xC7
//#define SSD1322_CMD_SET_MUX_RATIO					0xCA
//#define SSD1322_CMD_SET_DISPLAY_ENHANCEMENT_B		0xD1
//#define SSD1322_CMD_DISPLAY_ENHANCEMENT_B_NORMAL	0b10100010
//#define SSD1322_CMD_DISPLAY_ENHANCEMENT_B_END		0x20
//#define SSD1322_CMD_SET_COMMAND_LOCK				0xFD
//#define SSD1322_CMD_UNLOCK_COMMANDS					0x12
//#define SSD1322_CMD_LOCK_COMMANDS					0x16
//
//
//
//
//
//
//
//
//
//
//
//#if defined(SSD1322_USE_SPI) && SSD1322_USE_SPI == 1
//
//#define SSD1322_TRANSMIT		SpiTransmit
//
//#endif
//
//
//
//#if defined(SSD1322_6080_PARALLEL) && SSD1322_6080_PARALLEL == 1
//
//
//
//#if !defined(SSD1322_DATA_PORT) || !defined(SSD1322_CMD_PORT) || !defined(SSD1322_DATA_READ) || !defined(SSD1322_DATA_DIR) || !defined(SSD1322_E_PIN_POS) || !defined(SSD1322_RW_PIN_POS) || !defined(SSD1322_CS_PIN_POS) || !defined(SSD1322_DC_PIN_POS)
//
//#undef __INCLUDED_SSD1322__
//#define __INCLUDED_SSD1322__ -1
//
//#endif
//
//
//
//#elif defined(SSD1322_8080_PARALLEL) && SSD1322_8080_PARALLEL == 1
//
//
//
//#if !defined(SSD1322_DATA_PORT) || !defined(SSD1322_CMD_PORT) || !defined(SSD1322_DATA_READ) || !defined(SSD1322_DATA_DIR) || !defined(SSD1322_RD_PIN_POS) || !defined(SSD1322_WR_PIN_POS) || !defined(SSD1322_CS_PIN_POS) || !defined(SSD1322_DC_PIN_POS)
//
//#undef __INCLUDED_SSD1322__
//#define __INCLUDED_SSD1322__ -1
//
//#endif
//
//#elif defined(SSD1322_3_WIRE_SERIAL) && SSD1322_3_WIRE_SERIAL == 1
//
//
//#if !defined(SSD1322_CMD_PORT) || !defined(SSD1322_CS_PIN_POS)
//
//#undef __INCLUDED_SSD1322__
//#define __INCLUDED_SSD1322__ -1
//
//#endif
//
//
//
//#elif defined(SSD1322_4_WIRE_SERIAL) && SSD1322_4_WIRE_SERIAL == 1
//
//
//#if !defined(SSD1322_CMD_PORT) || !defined(SSD1322_CS_PIN_POS) || !defined(SSD1322_DC_PIN_POS)
//
//#undef __INCLUDED_SSD1322__
//#define __INCLUDED_SSD1322__ -1
//
//#endif
//
//
//
//#else
//
//#undef __INCLUDED_SSD1322__
//#define __INCLUDED_SSD1322__ -1
//#endif
//
//
//void SSD1322WriteCommand(uint8_t cmd);
//void SSD1322WriteData(uint8_t data);
//void SSD1322WriteCommandArray(uint8_t cmds[], uint16_t cmdLen);
//void SSD1322WriteDataArray(uint8_t datas[], uint16_t dataLen);
//void SSD1322SetCommandLock(uint8_t val);
//void SSD1322SetDisplayOnOff(uint8_t val);
//void SSD1322SetDisplaySleep(uint8_t isSleeping);
//void SSD1322SetColumnAddress(uint8_t val1 ,uint8_t val2);
//void SSD1322SetRowAddress(uint8_t val1,uint8_t val2);
//void SSD1322SetWriteRam();
//void SSD1322SetDisplayClock(uint8_t val);
//void SSD1322SetMultiplexRatio(uint8_t val);
//void SSD1322SetDisplayOffset(uint8_t val);
//void SSD1322SetStartLine(uint8_t val);
//void SSD1322SetRemapFormat(uint8_t val);
//void SSD1322SetGPIO(uint8_t val);
//void SSD1322SetFunctionSelection(uint8_t val);
//void SSD1322SetDisplayEnhancementA(uint8_t val1, uint8_t val2);
//void SSD1322SetContrastCurrent(uint8_t val);
//void SSD1322SetMasterCurrent(uint8_t val);
//void SSD1322SetGrayScaleTable();
//void SSD1322SetLinearGrayScaleTable();
//void SSD1322SetPhaseLength(uint8_t val);
//void SSD1322SetDisplayEnhancementB(uint8_t val);
//void SSD1322SetPrechargeVoltage(uint8_t val);
//void SSD1322SetPrechargePeriod(uint8_t val);
//void SSD1322SetVCOMH(uint8_t val);
//void SSD1322SetDisplayMode(uint8_t val);
//void SSD1322SetPartialDisplay(uint8_t val1 ,uint8_t val2 ,uint8_t val3);
//void SSD1322SetDisplayOnOff(uint8_t val1);
//void SSD1322Init();
//
//
//
//
//
//
//#ifdef __cplusplus
//}
//#endif
//
//#endif /* __SSD1322_H__ */