/**
 * \file MCP2515.h
 * \brief Header file for instructions and registers for the spi to can mcp2515 controller
 * \author Tim Robbins
*/
#ifndef _MCP2515_H_
#define _MCP2515_H_ 1

#ifdef __AVR

#include <avr/io.h>

#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */

#endif

/*
CAN CONTROLLER REGISTER MAP

Lower
Address     Higher Order Address Bits
Bits        0000xxxx 0001xxxx 0010xxxx 0011xxxx 0100xxxx 0101xxxx 0110xxxx 0111xxxx
0000        RXF0SIDH RXF3SIDH RXM0SIDH TXB0CTRL TXB1CTRL TXB2CTRL RXB0CTRL RXB1CTRL
0001        RXF0SIDL RXF3SIDL RXM0SIDL TXB0SIDH TXB1SIDH TXB2SIDH RXB0SIDH RXB1SIDH
0010        RXF0EID8 RXF3EID8 RXM0EID8 TXB0SIDL TXB1SIDL TXB2SIDL RXB0SIDL RXB1SIDL
0011        RXF0EID0 RXF3EID0 RXM0EID0 TXB0EID8 TXB1EID8 TXB2EID8 RXB0EID8 RXB1EID8
0100        RXF1SIDH RXF4SIDH RXM1SIDH TXB0EID0 TXB1EID0 TXB2EID0 RXB0EID0 RXB1EID0
0101        RXF1SIDL RXF4SIDL RXM1SIDL TXB0DLC  TXB1DLC  TXB2DLC  RXB0DLC  RXB1DLC
0110        RXF1EID8 RXF4EID8 RXM1EID8 TXB0D0   TXB1D0   TXB2D0   RXB0D0   RXB1D0
0111        RXF1EID0 RXF4EID0 RXM1EID0 TXB0D1   TXB1D1   TXB2D1   RXB0D1   RXB1D1
1000        RXF2SIDH RXF5SIDH CNF3     TXB0D2   TXB1D2   TXB2D2   RXB0D2   RXB1D2
1001        RXF2SIDL RXF5SIDL CNF2     TXB0D3   TXB1D3   TXB2D3   RXB0D3   RXB1D3
1010        RXF2EID8 RXF5EID8 CNF1     TXB0D4   TXB1D4   TXB2D4   RXB0D4   RXB1D4
1011        RXF2EID0 RXF5EID0 CANINTE  TXB0D5   TXB1D5   TXB2D5   RXB0D5   RXB1D5
1100        BFPCTRL   TEC     CANINTF  TXB0D6   TXB1D6   TXB2D6   RXB0D6   RXB1D6
1101        TXRTSCTRL REC     EFLG     TXB0D7   TXB1D7   TXB2D7   RXB0D7   RXB1D7
1110        CANSTAT  CANSTAT  CANSTAT  CANSTAT  CANSTAT  CANSTAT  CANSTAT  CANSTAT
1111        CANCTRL  CANCTRL  CANCTRL  CANCTRL  CANCTRL  CANCTRL  CANCTRL  CANCTRL

CONTROL REGISTER SUMMARY

#define MCP2515_BFPCTRL     0x0C
#define MCP2515_TXRTSCTRL   0x0D
#define MCP2515_CANSTAT     0x0E
#define MCP2515_CANCTRL     0x0F
#define MCP2515_TEC         0x1C
#define MCP2515_REC         0x1D
#define MCP2515_CNF3        0x28
#define MCP2515_CNF2        0x29
#define MCP2515_CNF1        0x2A
#define MCP2515_CANINTE     0x2B
#define MCP2515_CANINTF     0x2C
#define MCP2515_EFLG        0x2D
#define MCP2515_TXB0CTRL    0x30
#define MCP2515_TXB1CTRL    0x40
#define MCP2515_TXB2CTRL    0x50
#define MCP2515_RXB0CTRL    0x60
#define MCP2515_RXB1CTRL    0x70


*/

/*
    BIT MODIFYABLE Can use bit modify command
*/
#define MCP2515_BFPCTRL     0x0C
#define MCP2515_BFPCTRL_B1BFS 5 
#define MCP2515_BFPCTRL_B0BFS 4 
#define MCP2515_BFPCTRL_B1BFE 3 
#define MCP2515_BFPCTRL_B0BFE 2 
#define MCP2515_BFPCTRL_B1BFM 1 
#define MCP2515_BFPCTRL_B0BFM 0

#define MCP2515_TXRTSCTRL   0x0D

///: TX2RTS Pin State bit
#define MCP2515_TXRTSCTRL_B2RTS 5 

///: TX1RTS Pin State bit
#define MCP2515_TXRTSCTRL_B1RTS 4 

///TX0RTS Pin State bit
#define MCP2515_TXRTSCTRL_B0RTS 3 

///: TX2RTS Pin mode bit
#define MCP2515_TXRTSCTRL_B2RTSM 2 

///: TX1RTS Pin mode bit
#define MCP2515_TXRTSCTRL_B1RTSM 1 

///TX0RTS Pin mode bit
#define MCP2515_TXRTSCTRL_B0RTSM 0

#define MCP2515_CANCTRL0    0x0F
#define MCP2515_CANCTRL1    0x1F
#define MCP2515_CANCTRL2    0x2F
#define MCP2515_CANCTRL3    0x3F
#define MCP2515_CANCTRL4    0x4F
#define MCP2515_CANCTRL5    0x5F
#define MCP2515_CANCTRL6    0x6F
#define MCP2515_CANCTRL7    0x7F
#define MCP2515_CANCTRL_REQOP2  7 
#define MCP2515_CANCTRL_REQOP1  6 
#define MCP2515_CANCTRL_REQOP0  5 
#define MCP2515_CANCTRL_ABAT    4 
#define MCP2515_CANCTRL_OSM     3 
#define MCP2515_CANCTRL_CLKEN   2 
#define MCP2515_CANCTRL_CLKPRE1 1 
#define MCP2515_CANCTRL_CLKPRE0 0


#define MCP2515_CNF3        0x28
#define MCP2515_CNF3_SOF 7 
#define MCP2515_CNF3_WAKFIL 6 
#define MCP2515_CNF3_PHSEG22 2 
#define MCP2515_CNF3_PHSEG21 1 
#define MCP2515_CNF3_PHSEG20 0

#define MCP2515_CNF2        0x29
#define MCP2515_CNF2_BTLMODE 7 
#define MCP2515_CNF2_SAM 6 
#define MCP2515_CNF2_PHSEG12 5 
#define MCP2515_CNF2_PHSEG11 4 
#define MCP2515_CNF2_PHSEG10 3 
#define MCP2515_CNF2_PRSEG2 2 
#define MCP2515_CNF2_PRSEG1 1 
#define MCP2515_CNF2_PRSEG0 0

#define MCP2515_CNF1        0x2A
#define MCP2515_CNF1_SJW1 7 
#define MCP2515_CNF1_SJW0 6 
#define MCP2515_CNF1_BRP5 5 
#define MCP2515_CNF1_BRP4 4 
#define MCP2515_CNF1_BRP3 3 
#define MCP2515_CNF1_BRP2 2 
#define MCP2515_CNF1_BRP1 1 
#define MCP2515_CNF1_BRP0 0

#define MCP2515_CANINTE     0x2B

///Message Error Interrupt Enable bit
#define MCP2515_CANINTE_MERRE 7 

///: Wake-up Interrupt Enable bit
#define MCP2515_CANINTE_WAKIE 6 

/// Error Interrupt Enable bit (multiple sources in EFLG register)
#define MCP2515_CANINTE_ERRIE 5 

///Transmit Buffer 2 Empty Interrupt Enable bit
#define MCP2515_CANINTE_TX2IE 4 

///Transmit Buffer 1 Empty Interrupt Enable bit
#define MCP2515_CANINTE_TX1IE 3 

///Transmit Buffer 0 Empty Interrupt Enable bit
#define MCP2515_CANINTE_TX0IE 2 

///: Receive Buffer 1 Full Interrupt Enable bit
#define MCP2515_CANINTE_RX1IE 1 

///: Receive Buffer 0 Full Interrupt Enable bit
#define MCP2515_CANINTE_RX0IE 0

#define MCP2515_CANINTF     0x2C



///Message Error Interrupt Flag bit
#define MCP2515_CANINTF_MERRF 7 

///Wake-up Interrupt Flag bit
#define MCP2515_CANINTF_WAKIF 6 

///Error Interrupt Flag bit (multiple sources in EFLG register)
#define MCP2515_CANINTF_ERRIF 5 

///: Transmit Buffer 2 Empty Interrupt Flag bit
#define MCP2515_CANINTF_TX2IF 4 

///Transmit Buffer 1 Empty Interrupt Flag bit
#define MCP2515_CANINTF_TX1IF 3 

/// Transmit Buffer 0 Empty Interrupt Flag bit
#define MCP2515_CANINTF_TX0IF 2 

///: Receive Buffer 1 Full Interrupt Flag bit
#define MCP2515_CANINTF_RX1IF 1 

///Receive Buffer 0 Full Interrupt Flag bit
#define MCP2515_CANINTF_RX0IF 0

#define MCP2515_EFLG        0x2D
#define MCP2515_EFLG_RX1OVR 7 
#define MCP2515_EFLG_RX0OVR 6 
#define MCP2515_EFLG_TXBO 5 
#define MCP2515_EFLG_TXEP 4 
#define MCP2515_EFLG_RXEP 3 
#define MCP2515_EFLG_TXWAR 2 
#define MCP2515_EFLG_RXWAR 1 
#define MCP2515_EFLG_EWARN 0


#define MCP2515_TXB0CTRL    0x30
#define MCP2515_TXB1CTRL    0x40
#define MCP2515_TXB2CTRL    0x50

///Message Aborted Flag bit
#define MCP2515_TXBCTRL_ABTF 6 

/// Message Lost Arbitration bit
#define MCP2515_TXBCTRL_MLOA 5 

///Transmission Error Detected bit
#define MCP2515_TXBCTRL_TXERR 4 

/// Message Transmit Request bit
#define MCP2515_TXBCTRL_TXREQ 3 

///Transmit Buffer Priority bit 1
#define MCP2515_TXBCTRL_TXP1 1 

///Transmit Buffer Priority bit 0
#define MCP2515_TXBCTRL_TXP0 0



#define MCP2515_RXB0CTRL    0x60

/// Receive Buffer Operating mode bits
#define MCP2515_RXB0CTRL_RXM1 6 

///Received Remote Transfer Request bit
#define MCP2515_RXB0CTRL_RXM0 5 

///Received remote transfer request
#define MCP2515_RXB0CTRL_RXRTR 3 

///Rollover Enable bit
#define MCP2515_RXB0CTRL_BUKT 2 

///Read-Only Copy of BUKT bit (used internally by the MCP2515)
#define MCP2515_RXB0CTRL_BUKT1 1 

///Filter Hit bit (indicates which acceptance filter enabled reception of message)(1)
#define MCP2515_RXB0CTRL_FILHIT0 0



#define MCP2515_RXB1CTRL    0x70

///Receive Buffer Operating mode bit 1
#define MCP2515_RXB1CTRL_RXM1 6 

///Receive Buffer Operating mode bit 0
#define MCP2515_RXB1CTRL_RXM0 5 

///Received Remote Transfer Request bit
#define MCP2515_RXB1CTRL_RXRTR 3 


///Filter Hit bits (indicates which acceptance filter enabled reception of message)
#define MCP2515_RXB1CTRL_FILHIT2 2 
#define MCP2515_RXB1CTRL_FILHIT1 1 
#define MCP2515_RXB1CTRL_FILHIT0 0



/*

    Can not use bit modify command

*/


#define MCP2515_CANSTAT_OPMOD2 7 
#define MCP2515_CANSTAT_OPMOD1 6 
#define MCP2515_CANSTAT_OPMOD0 5 
#define MCP2515_CANSTAT_ICOD2  3 
#define MCP2515_CANSTAT_ICOD1  2 
#define MCP2515_CANSTAT_ICOD0  1

#define MCP2515_CANSTAT0        0x0E
#define MCP2515_CANSTAT_OPMOD02 7 
#define MCP2515_CANSTAT_OPMOD01 6 
#define MCP2515_CANSTAT_OPMOD00 5 
#define MCP2515_CANSTAT_ICOD02  3 
#define MCP2515_CANSTAT_ICOD01  2 
#define MCP2515_CANSTAT_ICOD00  1
#define MCP2515_CANSTAT1        0x1E
#define MCP2515_CANSTAT_OPMOD12 7 
#define MCP2515_CANSTAT_OPMOD11 6 
#define MCP2515_CANSTAT_OPMOD10 5 
#define MCP2515_CANSTAT_ICOD12  3 
#define MCP2515_CANSTAT_ICOD11  2 
#define MCP2515_CANSTAT_ICOD10  1
#define MCP2515_CANSTAT2        0x2E
#define MCP2515_CANSTAT_OPMOD22 7 
#define MCP2515_CANSTAT_OPMOD21 6 
#define MCP2515_CANSTAT_OPMOD20 5 
#define MCP2515_CANSTAT_ICOD22  3 
#define MCP2515_CANSTAT_ICOD21  2 
#define MCP2515_CANSTAT_ICOD20  1
#define MCP2515_CANSTAT3        0x3E
#define MCP2515_CANSTAT_OPMOD32 7 
#define MCP2515_CANSTAT_OPMOD31 6 
#define MCP2515_CANSTAT_OPMOD30 5 
#define MCP2515_CANSTAT_ICOD32  3 
#define MCP2515_CANSTAT_ICOD31  2 
#define MCP2515_CANSTAT_ICOD30  1
#define MCP2515_CANSTAT4        0x4E
#define MCP2515_CANSTAT_OPMOD42 7 
#define MCP2515_CANSTAT_OPMOD41 6 
#define MCP2515_CANSTAT_OPMOD40 5 
#define MCP2515_CANSTAT_ICOD42  3 
#define MCP2515_CANSTAT_ICOD41  2 
#define MCP2515_CANSTAT_ICOD40  1
#define MCP2515_CANSTAT5        0x5E
#define MCP2515_CANSTAT_OPMOD52 7 
#define MCP2515_CANSTAT_OPMOD51 6 
#define MCP2515_CANSTAT_OPMOD50 5 
#define MCP2515_CANSTAT_ICOD52  3 
#define MCP2515_CANSTAT_ICOD51  2 
#define MCP2515_CANSTAT_ICOD50  1
#define MCP2515_CANSTAT6        0x6E
#define MCP2515_CANSTAT_OPMOD62 7 
#define MCP2515_CANSTAT_OPMOD61 6 
#define MCP2515_CANSTAT_OPMOD60 5 
#define MCP2515_CANSTAT_ICOD62  3 
#define MCP2515_CANSTAT_ICOD61  2 
#define MCP2515_CANSTAT_ICOD60  1
#define MCP2515_CANSTAT7        0x7E
#define MCP2515_CANSTAT_OPMOD72 7 
#define MCP2515_CANSTAT_OPMOD71 6 
#define MCP2515_CANSTAT_OPMOD70 5 
#define MCP2515_CANSTAT_ICOD72  3 
#define MCP2515_CANSTAT_ICOD71  2 
#define MCP2515_CANSTAT_ICOD70  1

#define MCP2515_RXF0SIDH    0x00
#define MCP2515_RXF0SIDL    0x01
#define MCP2515_RXF0EID8    0x02
#define MCP2515_RXF0EID0    0x03
#define MCP2515_RXF1SIDH    0x04
#define MCP2515_RXF1SIDL    0x05
#define MCP2515_RXF1EID8    0x06
#define MCP2515_RXF1EID0    0x07
#define MCP2515_RXF2SIDH    0x08
#define MCP2515_RXF2SIDL    0x09
#define MCP2515_RXF2EID8    0x0A
#define MCP2515_RXF2EID0    0x0B

#define MCP2515_RXF3SIDH    0x10
#define MCP2515_RXF3SIDL    0x11
#define MCP2515_RXF3EID8    0x12
#define MCP2515_RXF3EID0    0x13
#define MCP2515_RXF4SIDH    0x14
#define MCP2515_RXF4SIDL    0x15
#define MCP2515_RXF4EID8    0x16
#define MCP2515_RXF4EID0    0x17
#define MCP2515_RXF5SIDH    0x18
#define MCP2515_RXF5SIDL    0x19
#define MCP2515_RXF5EID8    0x1A
#define MCP2515_RXF5EID0    0x1B

// Transmit Error Counter (TEC) 
#define MCP2515_TEC         0x1C

// Receive Error Counter (REC)
#define MCP2515_REC         0x1D

#define MCP2515_RXM0SIDH    0x20
#define MCP2515_RXM0SIDL    0x21
#define MCP2515_RXM0EID8    0x22
#define MCP2515_RXM0EID0    0x23
#define MCP2515_RXM1SIDH    0x24
#define MCP2515_RXM1SIDL    0x25
#define MCP2515_RXM1EID8    0x26
#define MCP2515_RXM1EID0    0x27

#define MCP2515_TXB0SIDH    0x31
#define MCP2515_TXB0SIDL    0x32
#define MCP2515_TXB0EID8    0x33
#define MCP2515_TXB0EID0    0x34
#define MCP2515_TXB0DLC     0x35
#define MCP2515_TXB0D0      0x36
#define MCP2515_TXB0D1      0x37
#define MCP2515_TXB0D2      0x38
#define MCP2515_TXB0D3      0x39
#define MCP2515_TXB0D4      0x3A
#define MCP2515_TXB0D5      0x3B
#define MCP2515_TXB0D6      0x3C
#define MCP2515_TXB0D7      0x3D

#define MCP2515_TXB1SIDH    0x41
#define MCP2515_TXB1SIDL    0x42
#define MCP2515_TXB1EID8    0x43
#define MCP2515_TXB1EID0    0x44
#define MCP2515_TXB1DLC     0x45
#define MCP2515_TXB1D0      0x46
#define MCP2515_TXB1D1      0x47
#define MCP2515_TXB1D2      0x48
#define MCP2515_TXB1D3      0x49
#define MCP2515_TXB1D4      0x4A
#define MCP2515_TXB1D5      0x4B
#define MCP2515_TXB1D6      0x4C
#define MCP2515_TXB1D7      0x4D

#define MCP2515_TXB2SIDH    0x51
#define MCP2515_TXB2SIDL    0x52
#define MCP2515_TXB2EID8    0x53
#define MCP2515_TXB2EID0    0x54
#define MCP2515_TXB2DLC     0x55
#define MCP2515_TXB2D0      0x56
#define MCP2515_TXB2D1      0x57
#define MCP2515_TXB2D2      0x58
#define MCP2515_TXB2D3      0x59
#define MCP2515_TXB2D4      0x5A
#define MCP2515_TXB2D5      0x5B
#define MCP2515_TXB2D6      0x5C
#define MCP2515_TXB2D7      0x5D

#define MCP2515_RXB0SIDH    0x61
#define MCP2515_RXB0SIDL    0x62
#define MCP2515_RXB0EID8    0x63
#define MCP2515_RXB0EID0    0x64
#define MCP2515_RXB0DLC     0x65
#define MCP2515_RXB0D0      0x66
#define MCP2515_RXB0D1      0x67
#define MCP2515_RXB0D2      0x68
#define MCP2515_RXB0D3      0x69
#define MCP2515_RXB0D4      0x6A
#define MCP2515_RXB0D5      0x6B
#define MCP2515_RXB0D6      0x6C
#define MCP2515_RXB0D7      0x6D

#define MCP2515_RXB1SIDH    0x71
#define MCP2515_RXB1SIDL    0x72
#define MCP2515_RXB1EID8    0x73
#define MCP2515_RXB1EID0    0x74
#define MCP2515_RXB1DLC     0x75
#define MCP2515_RXB1D0      0x76
#define MCP2515_RXB1D1      0x77
#define MCP2515_RXB1D2      0x78
#define MCP2515_RXB1D3      0x79
#define MCP2515_RXB1D4      0x7A
#define MCP2515_RXB1D5      0x7B
#define MCP2515_RXB1D6      0x7C
#define MCP2515_RXB1D7      0x7D





///Resets internal registers to the default state, sets Configuration mode.
#define MCP2515_RESET_CMD                   0b11000000

///Reads data from the register beginning at selected address
#define MCP2515_READ_CMD                    0b00000011

///Writes data to the register beginning at the selected address.
#define MCP2515_WRITE_CMD                   0b00000010

///Quick polling command that reads several status bits for transmit and receive functions.
#define MCP2515_READ_STATUS_CMD             0b10100000

///Quick polling command that indicates filter match and message type (standard, extended and/or remote) of received message
#define MCP2515_READ_RX_STATUS_CMD          0b10110000

#define MCP2515_NORMAL_OPERATION_MODE       (0x00 << MCP2515_CANCTRL_REQOP0)
#define MCP2515_SLEEP_MODE                  (1 << MCP2515_CANCTRL_REQOP0)
#define MCP2515_LOOPBACK_MODE               (1 << MCP2515_CANCTRL_REQOP1)
#define MCP2515_LISTEN_ONLY_MODE            ((1 << MCP2515_CANCTRL_REQOP0) | (1 << MCP2515_CANCTRL_REQOP1))
#define MCP2515_CONFIGURATION_MODE          (1 << MCP2515_CANCTRL_REQOP2)

#define MCP2515_REQUEST_ABORT               (1 << MCP2515_CANCTRL_ABAT)
#define MCP2515_CLEAR_ABORT_REQUEST         (1 << MCP2515_CANCTRL_ABAT)

#define MCP2515_ONE_SHOT_ENABLED            (1 << MCP2515_CANCTRL_OSM)
#define MCP2515_ONE_SHOT_DISABLED           (0 << MCP2515_CANCTRL_OSM)
#define MCP2515_RETRY_TX                    (0 << MCP2515_CANCTRL_OSM)

#define MCP2515_ENABLE_CLK_OUT              (1 << MCP2515_ENABLE_CLK_OUT)
#define MCP2515_DISABLE_CLK_OUT             (0 << MCP2515_ENABLE_CLK_OUT)

#define MCP2515_CLKOUT_DIV_1                (0b00 << MCP2515_CANCTRL_CLKPRE0)
#define MCP2515_CLKOUT_DIV_2                (0b01 << MCP2515_CANCTRL_CLKPRE0)
#define MCP2515_CLKOUT_DIV_4                (0b10 << MCP2515_CANCTRL_CLKPRE0)
#define MCP2515_CLKOUT_DIV_8                (0b11 << MCP2515_CANCTRL_CLKPRE0)

 
#define MCP2515_READ_FROM_RX_BUFF_0_START_RXB0SIDH       0b10010000
#define MCP2515_READ_FROM_RX_BUFF_0_START_RXB0D0         0b10010010
#define MCP2515_READ_FROM_RX_BUFF_1_START_RXB1SIDH       0b10010100
#define MCP2515_READ_FROM_RX_BUFF_1_START_RXB1D0         0b10010110

#define MCP2515_LOAD_TX_BUFF_0_START_TXB0SIDH            0b01000000
#define MCP2515_LOAD_TX_BUFF_0_START_TXB0D0              0b01000001
#define MCP2515_LOAD_TX_BUFF_1_START_TXB1SIDH            0b01000010   
#define MCP2515_LOAD_TX_BUFF_1_START_TXB1D0              0b01000011
#define MCP2515_LOAD_TX_BUFF_2_START_TXB2SIDH            0b01000100   
#define MCP2515_LOAD_TX_BUFF_2_START_TXB2D0              0b01000101

#define MCP2515_RECEIVED_MSG_MASK                        0xC0
#define MCP2515_MSG_TYPE_MASK                            0x18
#define MCP2515_FILTER_MATCH_MASK                        0x07
#define Mcp2515CheckForMessageInRxb0(rxVal)              (rxVal & 0x40) ? 1 : 0
#define Mcp2515CheckForMessageInRxb1(rxVal)              (rxVal & 0x80) ? 1 : 0



typedef enum Mcp2515RxMessageTypes
{
    StandardFrame=0x00,
    StandardRemoteFrame=0x08,
    ExtendedDataFrame=0x10,
    ExtendedRemoteDataFrame=0x18
};


typedef enum Mcp2515FilterMatchTypes
{
    
    RXF0,
    RXF1,
    RXF2,
    RXF3,
    RXF4,
    RXF5,
    RXF0RolloverRXB1,
    RXF1RolloverRXB1
};



/**
 *  Allows the user to set or clear individual bits in a particular
    register.
    Note: Not all registers can be bit modified with this command.
    Executing this command on registers that are not bit
    modifiable will force the mask to FFh. See the register
    map in Section 11.0 “Register Map” for a list of the
    registers that apply.
*/
#define MCP2515_BIT_MODIFY_CMD              0b00000101

///0B1001_0NM0 : Reduces the overhead of the normal read command by using the address pointer at one of four locations, indicated by N and M. Clears the RX flag bit when bringing CS high
___attribute__((always_inline)) inline unsigned char Mcp2515CreateReadRxBufferCommand(unsigned char address)
{
    return (0b10010000 | ((address & 0x03) << 1));
}


///0B0100_0ABC : When loading a transmit buffer, reduces the overhead of a normal WRITE command by placing the Address Pointer at one of six locations, as indicated by ‘a,b,c’. 
___attribute__((always_inline)) inline unsigned char Mcp2515CreateLoadTxBufferCommand(unsigned char address)
{
    return (0b01000000 | ((address & 0x07)));
}


///0b10000nnn : Instructs controller to begin message transmission sequence for any of the transmit buffers.
___attribute__((always_inline)) inline unsigned char Mcp2515CreateRequestToSendCommand(unsigned char requestTxB2, unsigned char requestTxB1, unsigned char requestTxB0)
{

    return (0b10000000 | (requestTxB2 ? 0b100 : 0) | (requestTxB1 ? 0b010 : 0) | (requestTxB0 ? 0b001 : 0) );
}





#endif