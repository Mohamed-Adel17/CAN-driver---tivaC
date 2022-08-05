/*

	Author : Mohamed Adel
  
	Date : 01/09/2021
	
	Project : CAN driver for tivaC - TM4C123GH6PM

*/

#ifndef CAN_H_
#define CAN_H_

#include "CAN_RegMap.h"
#include "BIT_math.h"

/*****************************************************************************/

#define CAN_MAX_STANDARD_ID  0x7FF  				//as standard 11-bit id range[0:0x7FF]
#define CAN_MAX_EXTENDED_ID  0x1FFFFFFF   //as standard 29-bit id range[0:0x1FFFFFFF]

#define CAN_MAX_DATA_BYTES   8

/*****************************************************************************/

/*MACROS to pecify which can channel/base is used*/
#define CAN0     24
#define CAN1     25
/*****************************************************************************/


/*Required values to be put in the XTAL section to configure the CLOCK*/
#define CLK_4MHZ  0x06
#define CLK_8MHZ  0x0E
#define CLK_16MHZ 0x15
#define CLK_25MHZ 0x1A
/*****************************************************************************/



/*some  bits/sections  values with it's length if required */

#define XTAL_BIT 0x06
#define XTAL_LEN 0x1F
/*****************************************************************************/

#define INIT_BIT 0
#define CCE_BIT  6
/*****************************************************************************/

#define BUSY_BIT 15
/*****************************************************************************/

#define BRP_LEN   0x3F
#define BRP_BIT   0
/*****************************************************************************/

#define SJW_LEN   0x03
#define SJW_BIT   6
/*****************************************************************************/

#define TSEG1_LEN 0x0F
#define TSEG1_BIT 8
/*****************************************************************************/

#define TSEG2_LEN 0x07
#define TSEG2_BIT 12
/*****************************************************************************/

#define MXTD_BIT   15
#define MDIR_BIT   14
/*****************************************************************************/

#define MSGVAL_BIT 15
/*****************************************************************************/

#define XTD_BIT    14
/*****************************************************************************/

#define DIR_BIt    13
/*****************************************************************************/

#define EOB_BIT    7
/*****************************************************************************/

#define DLC_BIT 0x00
#define DLC_LEN 0x0F
/*****************************************************************************/

#define ID_BIT  0x00
/*****************************************************************************/

#define MNUM_BIT 0x00
#define MNUM_LEN 0x3F
/*****************************************************************************/

#define WRNRD_BIT   0x07
#define ARB_BIT     0x05
#define CONTROL_BIT 0x04
#define DATAA_BIT   0x01
#define DATAB_BIT   0x00
/*****************************************************************************/


#define UMASK_BIT 12
#define MASK_BIT  6
/*****************************************************************************/

#define TEST_BIT    0x07
#define LBACK_BIT   0x04
#define SILENT_BIT  0x03
/*****************************************************************************/



/*message length in bytes enum*/
typedef enum {
	ZERO_B  = 0,
	ONE_B   = 1,
	TWO_B   = 2,
	THREE_B = 3,
	FOUR_B  = 4,
	FIVE_B  = 5,
	SIX_B   = 6,
	SEVEN_B = 7,
	EIGHT_B = 8,
	
}msgLEN_Bytes;
/*****************************************************************************/


/*message object number which will be assigned in the MNUM section*/
typedef enum {
	
	MsgNum1  = 0x01,
	MsgNum2  = 0x02,
	MsgNum3  = 0x03,
	MsgNum4  = 0x04,
	MsgNum5  = 0x05,
	MsgNum6  = 0x06,
	MsgNum7  = 0x07,
	MsgNum8  = 0x08,
	MsgNum9  = 0x09,
	MsgNum10 = 0x0A,
	MsgNum11 = 0x0B,
	MsgNum12 = 0x0C,
	MsgNum13 = 0x0D,
	MsgNum14 = 0x0E,
	MsgNum15 = 0x0F,
	MsgNum16 = 0x10,
	MsgNum17 = 0x11,
	MsgNum18 = 0x12,
	MsgNum19 = 0x13,
	MsgNum20 = 0x14,
	MsgNum21 = 0x15,
	MsgNum22 = 0x16,
	MsgNum23 = 0x17,
	MsgNum24 = 0x18,
	MsgNum25 = 0x19,
	MsgNum26 = 0x1A,
	MsgNum27 = 0x1B,
	MsgNum28 = 0x1C,
	MsgNum29 = 0x1D,
	MsgNum30 = 0x1E,
	MsgNum31 = 0x1F,
	MsgNum32 = 0x20,
	
}MsgObjNum;
/*****************************************************************************/



/*Frame type (standard or extended) enum*/
typedef enum{
	
	Standard_Frame = 0,
	Extended_Frame = 1,
	
}tFrame_Type;
/*****************************************************************************/

/*Flags enum for using/not-using Mask filtering in the recieve process*/
typedef enum{

	Msg_Dont_use_MaskID = 0,
	Msg_Use_MaskID      = 1,
	
}tMask_Flag;
/*****************************************************************************/


/*CAN modes enum to choose the mode of operation if required*/
typedef enum{
	Silent_Mode,
	LoopBack_Mode,
	Compined_Silent_LoopBack_Mode,
	
}tCAN_Mode;
/*****************************************************************************/


/*This structure for all configurations and data of the message object*/
/*The pragma technique to avoid the padding in memory*/
#pragma pack(push, 1)
typedef struct{
	
	u32 msgID;
	u32 msgIDMSK;
	tMask_Flag msgFlag;
	
	msgLEN_Bytes msgLEN;
	
	u8 ptrMsgData[CAN_MAX_DATA_BYTES];

}CAN_msgStruct;
#pragma pack(pop)
/*****************************************************************************/


/*Fuctions required prototypes for CAN driver*/

void CAN_Init(u8 Type,u8 CLK, CANBIT_Reg_Struct *ptrCANBIT, tCAN_Mode Mode);
/*****************************************************************************/

void CAN_msgSend(u8 Type, CAN_msgStruct *ptrMsgObj, MsgObjNum Num);
/*****************************************************************************/

void CAN_msgRead(u8 Type, CAN_msgStruct *ptrMsgObj, MsgObjNum Num);
/*****************************************************************************/

void iCANsetCLK(u8 CLK);
/*****************************************************************************/

void iCAN_setBitTiming(u8 Type, CANBIT_Reg_Struct *ptrCANBIT);
/*****************************************************************************/

#endif
