/*

	Author : Mohamed Adel
  
	Date : 01/09/2021
	
	Project : CAN driver for tivaC - TM4C123GH6PM

*/



#ifndef CAN_RegMap_H
#define CAN_RegMap_H

#include "STD_TYPES.h"

/*NOTE : using s32 (signed integer) instead of u32 (unsigned integer) because of implicit conversion warning when setting or clearing bits in these registers */


typedef struct {
	
   volatile   s32   CANCTL ;    /*CAN Control 					           */
   volatile   u32   CANSTS ;    /*CAN Status                       */
   volatile   u32   CANERR ;    /*CAN Error Counter                */
   volatile   s32   CANBIT ;    /*CAN Bit Timing                   */
   volatile   u32   CANINT ;    /*CAN Interrupt                    */
   volatile   u32   CANTST ;    /*CAN Test                         */
   volatile   u32   CANBRPE;    /*CAN Baud Rate Prescaler Extension*/
	
}CAN_ctrl_struct;

/***********************************************************/

typedef struct {
	
   volatile   s32   CANIF1CRQ ;     /*CAN IF1 Command Request          */
   volatile   u32   CANIF1CMSK;     /*CAN IF1 Command Mask             */
   volatile   u32   CANIF1MSK1;     /*CAN IF1 Mask 1                   */
   volatile   s32   CANIF1MSK2;     /*CAN IF1 Mask 2                   */
   volatile   s32   CANIF1ARB1;     /*CAN IF1 Arbitration 1            */
   volatile   s32   CANIF1ARB2;     /*CAN IF1 Arbitration 2            */
   volatile   s32   CANIF1MCTL;     /*CAN IF1 Message Control          */
   volatile   s32   CANIF1DA1 ;     /*CAN IF1 Data A1                  */
   volatile   s32   CANIF1DA2 ;     /*CAN IF1 Data A2                  */
   volatile   s32   CANIF1DB1 ;     /*CAN IF1 Data B1                  */
   volatile   s32   CANIF1DB2 ;     /*CAN IF1 Data B2                  */
   
}CAN_IF1_struct;

/***********************************************************/

typedef struct {
	
   volatile   s32   CANIF2CRQ ;     /*CAN IF2 Command Request          */
   volatile   s32   CANIF2CMSK;     /*CAN IF2 Command Mask             */
   volatile   s32   CANIF2MSK1;     /*CAN IF2 Mask 1                   */
   volatile   s32   CANIF2MSK2;     /*CAN IF2 Mask 2                   */
   volatile   s32   CANIF2ARB1;     /*CAN IF2 Arbitration 1            */
   volatile   s32   CANIF2ARB2;     /*CAN IF2 Arbitration 2            */
   volatile   s32   CANIF2MCTL;     /*CAN IF2 Message Control          */
   volatile   u32   CANIF2DA1 ;     /*CAN IF2 Data A1                  */
   volatile   u32   CANIF2DA2 ;     /*CAN IF2 Data A2                  */
   volatile   u32   CANIF2DB1 ;     /*CAN IF2 Data B1                  */
   volatile   u32   CANIF2DB2 ;     /*CAN IF2 Data B2                  */
   
}CAN_IF2_struct;



typedef struct{
	
	volatile s8 BRP;
	volatile s8 SJW;
	volatile s8 TSEG1;
	volatile s8 TSEG2;
	
}CANBIT_Reg_Struct;



/***********************************************************/

/*Macros to point to above reg structs*/

#define CAN0_CONTROL_REGs   ((volatile CAN_ctrl_struct*)0x40040000)

#define CAN0_IF1_REGs       ((volatile CAN_IF1_struct*) 0x40040020)

#define CAN0_IF2_REGs       ((volatile CAN_IF2_struct*) 0x40040080)

#define CAN1_CONTROL_REGs   ((volatile CAN_ctrl_struct*)0x40041000)

#define CAN1_IF1_REGs       ((volatile CAN_IF1_struct*) 0x40041020)

#define CAN1_IF2_REGs       ((volatile CAN_IF2_struct*) 0x40041080)

/***********************************************************/

/*Message Object Regs for CAN0*/

#define	 CAN0_CANTXRQ1_R      *((volatile u32*) 0x40040100)     /*CAN Transmission Request 1       */
#define	 CAN0_CANTXRQ2_R      *((volatile u32*) 0x40040104)     /*CAN Transmission Request 2       */
#define	 CAN0_CANNWDA1_R      *((volatile u32*) 0x40040120)     /*CAN New Data 1                   */
#define	 CAN0_CANNWDA2_R      *((volatile u32*) 0x40040124)     /*CAN New Data 2                   */
#define	 CAN0_CANMSG1INT_R    *((volatile u32*) 0x40040140)     /*CAN Message 1 Interrupt Pending  */
#define	 CAN0_CANMSG2INT_R    *((volatile u32*) 0x40040144)     /*CAN Message 2 Interrupt Pending  */
#define	 CAN0_CANMSG1VAL_R    *((volatile u32*) 0x40040160)     /*CAN Message 1 Valid 1098         */
#define	 CAN0_CANMSG2VAL_R    *((volatile u32*) 0x40040164)     /*CAN Message 2 Valid               */

/***********************************************************/

/*Message Object Regs for CAN1*/

#define	 CAN1_CANTXRQ1_R      *((volatile u32*) 0x40041100)     /*CAN Transmission Request 1       */
#define	 CAN1_CANTXRQ2_R      *((volatile u32*) 0x40041104)     /*CAN Transmission Request 2       */
#define	 CAN1_CANNWDA1_R      *((volatile u32*) 0x40041120)     /*CAN New Data 1                   */
#define	 CAN1_CANNWDA2_R      *((volatile u32*) 0x40041124)     /*CAN New Data 2                   */
#define	 CAN1_CANMSG1INT_R    *((volatile u32*) 0x40041140)     /*CAN Message 1 Interrupt Pending  */
#define	 CAN1_CANMSG2INT_R    *((volatile u32*) 0x40041144)     /*CAN Message 2 Interrupt Pending  */
#define	 CAN1_CANMSG1VAL_R    *((volatile u32*) 0x40041160)     /*CAN Message 1 Valid 1098         */
#define	 CAN1_CANMSG2VAL_R    *((volatile u32*) 0x40041164)     /*CAN Message 2 Valid              */

/***********************************************************/


/*Run Clock Gating Control Register, to enable the clock for CAN*/
#define  RCGC0_R              *((volatile u32*) 0x400FE100)     
	

/*Run Clock Control Register, to configure the clock Fsys*/
#define RCC_R                 *((volatile s32*) 0x400FE060)



#endif
