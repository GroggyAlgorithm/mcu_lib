/**
 * \file canNodeId.h
 * \author Timothy Robbins
 * \brief Header file containing Node id's and related macros
 */ 
#ifndef __CAN_NODE_ID_H__
#define __CAN_NODE_ID_H__

/*
    Message ID's. Must be less than 11 bit max(0x7fff) if using standard ID values
*/

///The ID to use if the node is the hub node
#define HUB_NODE_ID						0x100

///The ID to use if the node is the connecting through USB
#define USB_NODE_ID						0x200

///The ID to use if the node is the display node
#define DISPLAY_NODE_ID					0x300

///The ID to use if the node is the data input / data getter node
#define INPUT_NODE_ID					0x400

///The ID to use if the node is the data output / data setter node
#define OUTPUT_NODE_ID					0x500

///The ID to use if the node is a obd2 relayer node
#define OBD2_NODE                       0x600



///For getting just the nodes IDs.
#define CLEAR_NODE_ID_OFFSET			0xF00

///For getting the node without id 
#define CLEAR_NODE_ID					0xFF

///For getting just the nodes operation type offset
#define NODE_OPERATION_ID				0xF0

///For getting just the nodes operation type offset
#define NODE_OPERATION_TYPE				0x0F





//Commands and offsets for ID's

///Offset for everything needs to stop
#define NODE_ID_OFFSET_STOP_ALL			0xFF

///Offset for all input needs to stop
#define NODE_ID_OFFSET_STOP_ALL_INPUT	0xFE

///Offset for all output needs to stop
#define NODE_ID_OFFSET_STOP_ALL_OUTPUT	0xFD

///Offset for specific input needs to stop
#define NODE_ID_OFFSET_STOP_INPUT		0xFC

///Offset for specific output needs to stop
#define NODE_ID_OFFSET_STOP_OUTPUT		0xFB




///For requesting they send data
#define NODE_DATA_REQUEST_SEND          0xE0

///For requesting they get data
#define NODE_DATA_REQUEST_GET           0xD0

///For requesting they execute a command
#define NODE_DATA_REQUEST_EXE           0xC0

///For requesting they perform the command on a designated pin
#define NODE_DATA_REQUEST_PIN_OP        0xB0

///For requesting they perform a known operation of the type passed
#define NODE_DATA_REQUEST_KNOWN_OP      0xA0



///Offset for digital i/o commands
#define NODE_DATA_DIGITAL               0x01

///Offset for adc i/o commands
#define NODE_DATA_ADC                   0x02

///Offset for pwm i/o commands
#define NODE_DATA_PWM                   0x03

///Offset for dac i/o commands
#define NODE_DATA_DAC                   0x04

///Offset for spi i/o commands
#define NODE_DATA_SPI                   0x05

///Offset for serial i/o commands
#define NODE_DATA_USART                 0x06

///Offset for i2c i/o commands
#define NODE_DATA_I2C                   0x07

///Offset for display commands
#define NODE_DATA_DISPLAY               0x08




#endif /* __CAN_NODE_ID_H__ */