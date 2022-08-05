/*

	Author : Mohamed Adel
  
	Date : 01/09/2021
	
	Project : CAN driver for tivaC - TM4C123GH6PM

*/





#include "CAN.h"


/*CAN_Init--> a function that initialize CAN module for this tivaC (tm4c123x)
  It configures the required registers, sets the clock, bit timing and the operation mode if chosed. 
	All configurations are processed dependent the type of CAN module; CAN0 or CAN1
*/
void CAN_Init(u8 Type,u8 CLK,CANBIT_Reg_Struct *ptrCANBIT,tCAN_Mode Mode)
{
	
	
/*calling this function to set the system with the required clock*/
	iCANsetCLK(CLK);
	
	
	
	/*enable the clock and configure the bit timing for CAN depending on Type*/
	switch(Type)
	{
		case CAN0 : 
								SET_BIT(RCGC0_R,CAN0);  /*enable clock for CAN0*/
								SET_BIT(CAN0_CONTROL_REGs->CANCTL,INIT_BIT);
								//SET_BIT(CAN0_CONTROL_REGs->CANCTL,CCE_BIT);
		
								while(GET_BIT(CAN0_IF1_REGs->CANIF1CRQ,BUSY_BIT));	//wait for the busy flag while CAN0 is busy 
		
								iCAN_setBitTiming(Type,ptrCANBIT);
							
								break;
		
	
//the same process for CAN1 module		
		case CAN1 : 
								SET_BIT(RCGC0_R,CAN1);  										        /*enable clock for CAN1*/
							  SET_BIT(CAN1_CONTROL_REGs->CANCTL,INIT_BIT);        /*set the init bit*/
								//SET_BIT(CAN1_CONTROL_REGs->CANCTL,CCE_BIT);
		
								while(GET_BIT(CAN1_IF1_REGs->CANIF1CRQ,BUSY_BIT));	//wait for the busy flag while CAN1 is busy
		
								iCAN_setBitTiming(Type,ptrCANBIT);

		break;
	
	}
	

	/*Clearing the INIT bit to finish the initialization process*/
	switch(Type)
	{
		case CAN0 : 
			CLEAR_BIT(CAN0_CONTROL_REGs->CANCTL,INIT_BIT); break;
		
//the same process for CAN1 module
		case CAN1 :
			CLEAR_BIT(CAN1_CONTROL_REGs->CANCTL,INIT_BIT); break;
		
	}
	
	
/*Check for the required mode, if not one of these modes then skip this part*/	
	switch(Mode)
	{
		case Silent_Mode :
			switch(Type)
			{
				case CAN0 : 
					SET_BIT(CAN0_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN0_CONTROL_REGs->CANTST,SILENT_BIT);
				break;
				case CAN1 :
					SET_BIT(CAN1_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN1_CONTROL_REGs->CANTST,SILENT_BIT);
				break;		
			}
			break;
			
		case LoopBack_Mode :
			switch(Type)
			{
				case CAN0 : 
					SET_BIT(CAN0_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN0_CONTROL_REGs->CANTST,LBACK_BIT);
				break;
				case CAN1 :
					SET_BIT(CAN1_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN1_CONTROL_REGs->CANTST,LBACK_BIT);
				break;		
			}
		break;

		case Compined_Silent_LoopBack_Mode :
			switch(Type)
			{
				case CAN0 : 
					SET_BIT(CAN0_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN0_CONTROL_REGs->CANTST,SILENT_BIT);
					SET_BIT(CAN0_CONTROL_REGs->CANTST,LBACK_BIT);
				
				break;
				case CAN1 :
					SET_BIT(CAN1_CONTROL_REGs->CANCTL,TEST_BIT);
					SET_BIT(CAN1_CONTROL_REGs->CANTST,SILENT_BIT);
					SET_BIT(CAN1_CONTROL_REGs->CANTST,LBACK_BIT);
				break;		
			}	
		break;

	}			

}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


/*this function resposable for setting the system with the required clock*/
void iCANsetCLK(u8 CLK)
{
	switch(CLK)
	{
		case CLK_4MHZ :
			CLEAR_SEC_REG(RCC_R,XTAL_LEN,XTAL_BIT);
			WRITE_SEC_REG(RCC_R,CLK_4MHZ,XTAL_BIT);
			break;
		case CLK_8MHZ :
			CLEAR_SEC_REG(RCC_R,XTAL_LEN,XTAL_BIT);
			WRITE_SEC_REG(RCC_R,CLK_8MHZ,XTAL_BIT);
		  break;
		case CLK_16MHZ :
			CLEAR_SEC_REG(RCC_R,XTAL_LEN,XTAL_BIT);
			WRITE_SEC_REG(RCC_R,CLK_16MHZ,XTAL_BIT);
		  break;
		case CLK_25MHZ :
			CLEAR_SEC_REG(RCC_R,XTAL_LEN,XTAL_BIT);
			WRITE_SEC_REG(RCC_R,CLK_25MHZ,XTAL_BIT);
		  break;		
	}	
}



/*This function configures CANBIT register with required bit timing configurations*/
void iCAN_setBitTiming(u8 Type,CANBIT_Reg_Struct *ptrCANBIT)
{
switch(Type)
	{
		case CAN0 : 	
								CLEAR_SEC_REG(CAN0_CONTROL_REGs->CANBIT,BRP_LEN,BRP_BIT);
								WRITE_SEC_REG(CAN0_CONTROL_REGs->CANBIT,ptrCANBIT->BRP,BRP_BIT);
		
								CLEAR_SEC_REG(CAN0_CONTROL_REGs->CANBIT,SJW_LEN,SJW_BIT);
								WRITE_SEC_REG(CAN0_CONTROL_REGs->CANBIT,ptrCANBIT->SJW,SJW_BIT);
		
								CLEAR_SEC_REG(CAN0_CONTROL_REGs->CANBIT,TSEG1_LEN,TSEG1_BIT);
								WRITE_SEC_REG(CAN0_CONTROL_REGs->CANBIT,ptrCANBIT->TSEG1,TSEG1_BIT);
		
								CLEAR_SEC_REG(CAN0_CONTROL_REGs->CANBIT,TSEG2_LEN,TSEG2_BIT);
								WRITE_SEC_REG(CAN0_CONTROL_REGs->CANBIT,ptrCANBIT->TSEG2,TSEG2_BIT);
							
								break;
		

//the same process for CAN1 module		
		case CAN1 : 
								CLEAR_SEC_REG(CAN1_CONTROL_REGs->CANBIT,BRP_LEN,BRP_BIT);
								WRITE_SEC_REG(CAN1_CONTROL_REGs->CANBIT,ptrCANBIT->BRP,BRP_BIT);
		
								CLEAR_SEC_REG(CAN1_CONTROL_REGs->CANBIT,SJW_LEN,SJW_BIT);
								WRITE_SEC_REG(CAN1_CONTROL_REGs->CANBIT,ptrCANBIT->SJW,SJW_BIT);
		
								CLEAR_SEC_REG(CAN1_CONTROL_REGs->CANBIT,TSEG1_LEN,TSEG1_BIT);
								WRITE_SEC_REG(CAN1_CONTROL_REGs->CANBIT,ptrCANBIT->TSEG1,TSEG1_BIT);
		
								CLEAR_SEC_REG(CAN1_CONTROL_REGs->CANBIT,TSEG2_LEN,TSEG2_BIT);
								WRITE_SEC_REG(CAN1_CONTROL_REGs->CANBIT,ptrCANBIT->TSEG2,TSEG2_BIT);		
								
								break;
									
	}
	

}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



/*This function sets the message object configurations, assignd data to it and starts the transimition process*/
void CAN_msgSend(u8 Type,CAN_msgStruct *ptrMsgObj,MsgObjNum Num)
{
	u8 xtd_value=0;
	
	tFrame_Type Frame_t;
	
	//by default frame is in standard type
	Frame_t = Standard_Frame;
	
	switch(Type)
	{
		case CAN0 : xtd_value = GET_BIT(CAN0_IF1_REGs->CANIF1ARB2,XTD_BIT); break;
		case CAN1 : xtd_value = GET_BIT(CAN1_IF1_REGs->CANIF1ARB2,XTD_BIT); break;
	}
	
	
	if(((ptrMsgObj->msgID > CAN_MAX_STANDARD_ID)&&(ptrMsgObj->msgID < CAN_MAX_EXTENDED_ID))||(xtd_value==1))
		{
			//it means this is an extended frame
				Frame_t = Extended_Frame;
		
		}else if (ptrMsgObj->msgID > CAN_MAX_EXTENDED_ID)
		{
			//it means not valid message
			return;
		}
	
	
	
	switch(Type)
	{
		case CAN0 :
			SET_BIT(CAN0_IF1_REGs->CANIF1CMSK,WRNRD_BIT);   //set the WRNRD bit for CAN0
			SET_BIT(CAN0_IF1_REGs->CANIF1CMSK,CONTROL_BIT); //set the CONTROL bit for CAN0
		  SET_BIT(CAN0_IF1_REGs->CANIF1CMSK,ARB_BIT);		  //set the ARB bit for CAN0
			SET_BIT(CAN0_IF1_REGs->CANIF1CMSK,DATAA_BIT);   //set the DATRAA bit for CAN0
			SET_BIT(CAN0_IF1_REGs->CANIF1CMSK,DATAB_BIT);   //set the DATAB bit for CAN0
		
		break;
		
//the same process for CAN1 module		
		case CAN1 :
			SET_BIT(CAN1_IF1_REGs->CANIF1CMSK,WRNRD_BIT);   //set the WRNRD bit for CAN1
			SET_BIT(CAN1_IF1_REGs->CANIF1CMSK,CONTROL_BIT); //set the CONTROL bit for CAN1
		  SET_BIT(CAN1_IF1_REGs->CANIF1CMSK,ARB_BIT);     //set the ARB bit for CAN1
			SET_BIT(CAN1_IF1_REGs->CANIF1CMSK,DATAA_BIT);   //set the DATRAA bit for CAN1
			SET_BIT(CAN1_IF1_REGs->CANIF1CMSK,DATAB_BIT);		//set the DATAB bit for CAN1
		
		break;
		
	}
	
	
	
	if(Frame_t == Standard_Frame)
	{
		switch(Type)
		{
			case CAN0 :
				CLEAR_BIT(CAN0_IF1_REGs->CANIF1ARB2,XTD_BIT);
				CLEAR_BIT(CAN0_IF1_REGs->CANIF1MSK2,MXTD_BIT);
			
			
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1ARB2,0x1FFF,0x00);
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1ARB2,ptrMsgObj->msgID,0x02);
			
			break;
			
//the same process for CAN1 module			
			case CAN1 :
				CLEAR_BIT(CAN1_IF1_REGs->CANIF1ARB2,XTD_BIT);
				CLEAR_BIT(CAN1_IF1_REGs->CANIF1MSK2,MXTD_BIT);
			
			
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1ARB2,0x1FFF,0x00);
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1ARB2,ptrMsgObj->msgID,0x02);
			
			break;				

		}
		
		
	}else if(Frame_t == Extended_Frame)
	{	
		switch(Type)
		{
			case CAN0 :
				SET_BIT(CAN0_IF1_REGs->CANIF1ARB2,XTD_BIT);    //set the XTD bit as it's extended frame
				CLEAR_BIT(CAN0_IF1_REGs->CANIF1MSK2,MXTD_BIT); 
			
			//we write the first part of ID in CANIF1ARB1 reg
			//and we clear it first
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1ARB1,0xFFFF,0x00);
			
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1ARB1,ptrMsgObj->msgID & 0x0000FFFF ,0x00);
			
			
			//now we write the second part of the ID
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1ARB2,0x1FFF,0x00);
			
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1ARB2,(ptrMsgObj->msgID & 0x1FFF0000) >> 16 ,0x00);
			
			break;
		
//the same process for CAN1 module
			case CAN1 :
				SET_BIT(CAN1_IF1_REGs->CANIF1ARB2,XTD_BIT);    //set the XTD bit as it's extended frame
				CLEAR_BIT(CAN0_IF1_REGs->CANIF1MSK2,MXTD_BIT); 
			
			//we write the first part of ID in CANIF1ARB1 reg
			//and we clear it first
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1ARB1,0xFFFF,0x00);
			
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1ARB1,ptrMsgObj->msgID & 0x0000FFFF ,0x00);
			
			
			//now we write the second part of the ID
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1ARB2,0x1FFF,0x00);
			
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1ARB2,(ptrMsgObj->msgID & 0x1FFF0000) >> 16 ,0x00);
			
			break;			

		}
	
	}
		
		
	switch(Type)
	{
			case CAN0 :
				SET_BIT(CAN0_IF1_REGs->CANIF1ARB2, DIR_BIt);    //set the direction as transmition
			  SET_BIT(CAN0_IF1_REGs->CANIF1ARB2, MSGVAL_BIT); //as message is valid
			
				SET_BIT(CAN0_IF1_REGs->CANIF1MCTL, EOB_BIT);    //for single message object
			
			//configure the DLC section for the msg data length
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1MCTL, ptrMsgObj->msgLEN, DLC_BIT);
				
			
			break;
			
	
//the same process for CAN1 module			
			case CAN1 :
				SET_BIT(CAN1_IF1_REGs->CANIF1ARB2, DIR_BIt);    //set the direction as transmition
			  SET_BIT(CAN1_IF1_REGs->CANIF1ARB2, MSGVAL_BIT); //as message is valid
			
				SET_BIT(CAN1_IF1_REGs->CANIF1MCTL, EOB_BIT);    //for single message object
			
			//configure the DLC section for the msg data length
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1MCTL, ptrMsgObj->msgLEN, DLC_BIT);


			break;
			
	}
	
		
/*now we are going to load the date into the message object through data registers*/
	
	switch(Type)
	{
		case CAN0 :
			//for each register : write in first part, then shift for the next part
			CAN0_IF1_REGs->CANIF1DA1 |=  ptrMsgObj->ptrMsgData[0] ;
		  CAN0_IF1_REGs->CANIF1DA1 |= (ptrMsgObj->ptrMsgData[1]<<8); 
		
			CAN0_IF1_REGs->CANIF1DA2 |=  ptrMsgObj->ptrMsgData[2] ;
		  CAN0_IF1_REGs->CANIF1DA2 |= (ptrMsgObj->ptrMsgData[3]<<8);

			CAN0_IF1_REGs->CANIF1DB1 |=  ptrMsgObj->ptrMsgData[4] ;
		  CAN0_IF1_REGs->CANIF1DB1 |= (ptrMsgObj->ptrMsgData[5]<<8);

			CAN0_IF1_REGs->CANIF1DB2 |=  ptrMsgObj->ptrMsgData[6] ;
		  CAN0_IF1_REGs->CANIF1DB2 |= (ptrMsgObj->ptrMsgData[7]<<8);		
		
		break;

		
//the same process for CAN1 module		
		case CAN1 :
			//for each register : write in first part, then shift for the next part
			CAN1_IF1_REGs->CANIF1DA1 |=  ptrMsgObj->ptrMsgData[0] ;
		  CAN1_IF1_REGs->CANIF1DA1 |= (ptrMsgObj->ptrMsgData[1]<<8); 
		
			CAN1_IF1_REGs->CANIF1DA2 |=  ptrMsgObj->ptrMsgData[2] ;
		  CAN1_IF1_REGs->CANIF1DA2 |= (ptrMsgObj->ptrMsgData[3]<<8);

			CAN1_IF1_REGs->CANIF1DB1 |=  ptrMsgObj->ptrMsgData[4] ;
		  CAN1_IF1_REGs->CANIF1DB1 |= (ptrMsgObj->ptrMsgData[5]<<8);

			CAN1_IF1_REGs->CANIF1DB2 |=  ptrMsgObj->ptrMsgData[6] ;
		  CAN1_IF1_REGs->CANIF1DB2 |= (ptrMsgObj->ptrMsgData[7]<<8);		
		
		break;		
		
	}

//set the NEWDAT and TXRQST	bits at the same time to prevent clearing TXRQST during a transmition
	
	
	switch(Type)
	{
		case CAN0 :
			CAN0_IF1_REGs->CANIF1MCTL |= (1<<15) | (1<<8) ;
		break;
	
//the same process for CAN1 module		
		case CAN1 :
			CAN1_IF1_REGs->CANIF1MCTL |= (1<<15) | (1<<8) ;
		break;		
		
		
		
	}

	
//write the message object number into the MNUM section to start the transfer process
	switch(Type)
	{
		case CAN0 :
			
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1CRQ, MNUM_LEN, MNUM_BIT);
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1CRQ, Num, MNUM_BIT);
		
			//setting the data length (through msg obj struct) to the DLC section
				CLEAR_SEC_REG(CAN0_IF1_REGs->CANIF1MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN0_IF1_REGs->CANIF1MCTL, ptrMsgObj->msgLEN, DLC_BIT);		
		
				
		
		break;
		
//the same process for CAN1 module		
		case CAN1 :
			
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1CRQ, MNUM_LEN, MNUM_BIT);
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1CRQ, Num, MNUM_BIT);
		
		
			//setting the data length (through msg obj struct) to the DLC section
				CLEAR_SEC_REG(CAN1_IF1_REGs->CANIF1MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN1_IF1_REGs->CANIF1MCTL, ptrMsgObj->msgLEN, DLC_BIT);				

		break;
	}	
		
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



/*This function sets configurations for the recieve process, recieves data from mailbox with all required settings*/
void CAN_msgRead(u8 Type,CAN_msgStruct *ptrMsgObj,MsgObjNum Num)
{
	u8 xtd_value=0;
	
	tFrame_Type Frame_t;
	
	//by default frame is in standard type
	Frame_t = Standard_Frame;
	
	switch(Type)
	{
		case CAN0 : xtd_value = GET_BIT(CAN0_IF2_REGs->CANIF2ARB2,XTD_BIT); break;
		case CAN1 : xtd_value = GET_BIT(CAN1_IF2_REGs->CANIF2ARB2,XTD_BIT); break;
	}
	
	
	if(((ptrMsgObj->msgID > CAN_MAX_STANDARD_ID)&&(ptrMsgObj->msgID < CAN_MAX_EXTENDED_ID))||(xtd_value==1))
		{
			//it means this is an extended frame
				Frame_t = Extended_Frame;
		
		}else if (ptrMsgObj->msgID > CAN_MAX_EXTENDED_ID)
		{
			//it means not valid message
			return;
		}

	
	switch(Type)
	{
		case CAN0 :
			CLEAR_BIT(CAN0_IF2_REGs->CANIF2CMSK,WRNRD_BIT); //clear the WRNRD bit for CAN0
			SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,CONTROL_BIT); //set the CONTROL bit for CAN0
		  SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,ARB_BIT);		  //set the ARB bit for CAN0
			SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,DATAA_BIT);   //set the DATRAA bit for CAN0
			SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,DATAB_BIT);   //set the DATAB bit for CAN0
		
		break;
		
//the same process for CAN1 module		
		case CAN1 :
			CLEAR_BIT(CAN1_IF2_REGs->CANIF2CMSK,WRNRD_BIT); //clear the WRNRD bit for CAN1
			SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,CONTROL_BIT); //set the CONTROL bit for CAN1
		  SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,ARB_BIT);     //set the ARB bit for CAN1
			SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,DATAA_BIT);   //set the DATRAA bit for CAN1
			SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,DATAB_BIT);		//set the DATAB bit for CAN1
		
		break;
		
	}
		
	
	if(Frame_t == Standard_Frame)
	{
		switch(Type)
		{
			case CAN0 :
				//clear bits of extended frame process
				CLEAR_BIT(CAN0_IF2_REGs->CANIF2ARB2,XTD_BIT);
				CLEAR_BIT(CAN0_IF2_REGs->CANIF2MSK2,MXTD_BIT);
		
	     //check if we use MaskID or not,if so we write the mask sec in CANIF2MSK2 reg 	
			  if(ptrMsgObj->msgFlag == Msg_Use_MaskID)
				{
					//first we set UMASK and MASK bits
					SET_BIT(CAN0_IF2_REGs->CANIF2MCTL,UMASK_BIT);
					SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,MASK_BIT);
					
					//then we write the MaskID from the msg obj structure
					CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
					WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,ptrMsgObj->msgIDMSK,0x02);
				}
			
			//we write the first part of ID in CANIF1ARB2 reg
			//and we clear it first			
				CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2ARB2,0x1FFF,0x00);
				WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2ARB2,ptrMsgObj->msgID,0x02);
			
			break;
			
//the same process for CAN1 module			
			case CAN1 :
				//clear bits of extended frame process
				CLEAR_BIT(CAN0_IF2_REGs->CANIF2ARB2,XTD_BIT);
				CLEAR_BIT(CAN0_IF2_REGs->CANIF2MSK2,MXTD_BIT);
		
		  //check if we use MaskID or not,if so we write the mask sec in CANIF2MSK2 reg 	
			  if(ptrMsgObj->msgFlag == Msg_Use_MaskID)
				{
					//first we set UMASK and MASK bits
					SET_BIT(CAN1_IF2_REGs->CANIF2MCTL,UMASK_BIT);
					SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,MASK_BIT);
					
					//then we write the MaskID from the msg obj structure
					CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
					WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,ptrMsgObj->msgIDMSK,0x02);
				}
			
			//we write the first part of ID in CANIF1ARB2 reg
			//and we clear it first			
				CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2ARB2,0x1FFF,0x00);
				WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2ARB2,ptrMsgObj->msgID,0x02);
			break;				

		}
		
		
	}else if(Frame_t == Extended_Frame)
	{	
		switch(Type)
		{
			case CAN0 :
				SET_BIT(CAN0_IF2_REGs->CANIF2ARB2,XTD_BIT);    //set the XTD bit as it's extended frame
		 
			//check if we use MaskID or not,if so we write the mask sec in CANIF2MSK1 and CANIF2MSK2 Regs	
			  if(ptrMsgObj->msgFlag == Msg_Use_MaskID)
				{
					//first we set UMASK and MASK bits
					SET_BIT(CAN0_IF2_REGs->CANIF2MCTL,UMASK_BIT);
					SET_BIT(CAN0_IF2_REGs->CANIF2CMSK,MASK_BIT);				
					
					
				//we write the first part of MaskID in CANIF2MSK1 reg
				//and we clear it first
					CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2MSK1,0xFFFF,0x00);
			
					WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2MSK1,ptrMsgObj->msgIDMSK & 0x0000FFFF ,0x00);
			
			
				//now we write the second part of the MaskID
					CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
			
					WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,(ptrMsgObj->msgIDMSK & 0x1FFF0000) >> 16 ,0x00);							
								
				//then we write the MaskID from the msg obj structure
					CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
					WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2MSK2,ptrMsgObj->msgIDMSK,0x02);
					
				//set the MXTD and MDIR bit to use XTD in acceptance filtering
				  SET_BIT(CAN0_IF2_REGs->CANIF2MSK2,MXTD_BIT);  
					SET_BIT(CAN0_IF2_REGs->CANIF2MSK2,MDIR_BIT);
				}			
			
						
			//we write the first part of ID in CANIF1ARB1 reg
			//and we clear it first
				CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2ARB1,0xFFFF,0x00);
		
				WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2ARB1,ptrMsgObj->msgID & 0x0000FFFF ,0x00);
			
			
			//now we write the second part of the ID
				CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2ARB2,0x1FFF,0x00);
			
				WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2ARB2,(ptrMsgObj->msgID & 0x1FFF0000) >> 16 ,0x00);
			
			break;
		
//the same process for CAN1 module
			case CAN1 :
				SET_BIT(CAN1_IF2_REGs->CANIF2ARB2,XTD_BIT);    //set the XTD bit as it's extended frame
		 
			//check if we use MaskID or not,if so we write the mask sec in CANIF2MSK1 and CANIF2MSK2 Regs	
			  if(ptrMsgObj->msgFlag == Msg_Use_MaskID)
				{
					//first we set UMASK and MASK bits
					SET_BIT(CAN1_IF2_REGs->CANIF2MCTL,UMASK_BIT);
					SET_BIT(CAN1_IF2_REGs->CANIF2CMSK,MASK_BIT);				
					
					
				//we write the first part of MaskID in CANIF2MSK1 reg
				//and we clear it first
					CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2MSK1,0xFFFF,0x00);
			
					WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2MSK1,ptrMsgObj->msgIDMSK & 0x0000FFFF ,0x00);
			
			
				//now we write the second part of the MaskID
					CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
			
					WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,(ptrMsgObj->msgIDMSK & 0x1FFF0000) >> 16 ,0x00);							
								
				//then we write the MaskID from the msg obj structure
					CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,0x1FFF,0x00);
					WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2MSK2,ptrMsgObj->msgIDMSK,0x02);
					
				//set the MXTD and MDIR bit to use XTD in acceptance filtering
				  SET_BIT(CAN1_IF2_REGs->CANIF2MSK2,MXTD_BIT);  
					SET_BIT(CAN1_IF2_REGs->CANIF2MSK2,MDIR_BIT);
				}			
			
			
			//we write the first part of ID in CANIF1ARB1 reg
			//and we clear it first
				CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2ARB1,0xFFFF,0x00);
			
				WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2ARB1,ptrMsgObj->msgID & 0x0000FFFF ,0x00);
			
			
			//now we write the second part of the ID
				CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2ARB2,0x1FFF,0x00);
			
				WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2ARB2,(ptrMsgObj->msgID & 0x1FFF0000) >> 16 ,0x00);
			
			break;			

		}
	
	}
		
		
	switch(Type)
	{
			case CAN0 :
				CLEAR_BIT(CAN0_IF2_REGs->CANIF2ARB2, DIR_BIt);    //set the direction as Recieve
			  SET_BIT(CAN0_IF2_REGs->CANIF2ARB2, MSGVAL_BIT);  //as message is valid
			
				SET_BIT(CAN0_IF2_REGs->CANIF2MCTL, EOB_BIT);    //for single message object
			
			//configure the DLC section for the msg data length
				CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2MCTL, ptrMsgObj->msgLEN, DLC_BIT);
				
			
			break;
			
	
//the same process for CAN1 module			
			case CAN1 :
				CLEAR_BIT(CAN1_IF2_REGs->CANIF2ARB2, DIR_BIt);    //set the direction as Recieve
			  SET_BIT(CAN1_IF2_REGs->CANIF2ARB2, MSGVAL_BIT);  //as message is valid
				
				SET_BIT(CAN1_IF2_REGs->CANIF2MCTL, EOB_BIT);    //for single message object
			
			//configure the DLC section for the msg data length
				CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2MCTL, DLC_LEN, DLC_BIT);
				WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2MCTL, ptrMsgObj->msgLEN, DLC_BIT);
				

			break;
			
	}
	
	
//write the message object number into the MNUM section and clear WRNRD
	switch(Type)
	{
		case CAN0 :
				CLEAR_BIT(CAN1_IF2_REGs->CANIF2CMSK,WRNRD_BIT); //clear the WRNRD bit for CAN0
			
				CLEAR_SEC_REG(CAN0_IF2_REGs->CANIF2CRQ, MNUM_LEN, MNUM_BIT);
				WRITE_SEC_REG(CAN0_IF2_REGs->CANIF2CRQ, Num, DLC_BIT);
		
		break;
		
//the same process for CAN1 module		
		case CAN1 :
        CLEAR_BIT(CAN1_IF2_REGs->CANIF2CMSK,WRNRD_BIT); //clear the WRNRD bit for CAN1
		
				CLEAR_SEC_REG(CAN1_IF2_REGs->CANIF2CRQ, MNUM_LEN, MNUM_BIT);
				WRITE_SEC_REG(CAN1_IF2_REGs->CANIF2CRQ, Num, DLC_BIT);

		break;
	}			
	
		
/*now we are going to load the date into the message object through data registers*/
	
	switch(Type)
	{
		case CAN0 :
			//for each register : write in first part, then shift for the next part
			ptrMsgObj->ptrMsgData[0]  |=   CAN0_IF2_REGs->CANIF2DA1;
		  ptrMsgObj->ptrMsgData[1]  |= ((CAN0_IF2_REGs->CANIF2DA1) <<8); 
		
			ptrMsgObj->ptrMsgData[2]  |=   CAN0_IF2_REGs->CANIF2DA2;
		  ptrMsgObj->ptrMsgData[3]  |= ((CAN0_IF2_REGs->CANIF2DA2) <<8); 

			ptrMsgObj->ptrMsgData[4]  |=   CAN0_IF2_REGs->CANIF2DB1;
		  ptrMsgObj->ptrMsgData[5]  |= ((CAN0_IF2_REGs->CANIF2DB1) <<8); 

			ptrMsgObj->ptrMsgData[6]  |=   CAN0_IF2_REGs->CANIF2DB2;
		  ptrMsgObj->ptrMsgData[7]  |= ((CAN0_IF2_REGs->CANIF2DB2) <<8); 		
		
		break;

		
//the same process for CAN1 module		
		case CAN1 :
			//for each register : write in first part, then shift for the next part
			ptrMsgObj->ptrMsgData[0]  |=   CAN0_IF2_REGs->CANIF2DA1;
		  ptrMsgObj->ptrMsgData[1]  |= ((CAN0_IF2_REGs->CANIF2DA1) <<8); 
		
			ptrMsgObj->ptrMsgData[2]  |=   CAN0_IF2_REGs->CANIF2DA2;
		  ptrMsgObj->ptrMsgData[3]  |= ((CAN0_IF2_REGs->CANIF2DA2) <<8); 

			ptrMsgObj->ptrMsgData[4]  |=   CAN0_IF2_REGs->CANIF2DB1;
		  ptrMsgObj->ptrMsgData[5]  |= ((CAN0_IF2_REGs->CANIF2DB1) <<8); 

			ptrMsgObj->ptrMsgData[6]  |=   CAN0_IF2_REGs->CANIF2DB2;
		  ptrMsgObj->ptrMsgData[7]  |= ((CAN0_IF2_REGs->CANIF2DB2) <<8); 				
		
		break;		
		
	}
	
//geting the message data Length from the DLC section into msgLen in msg obj
	switch(Type)
	{
		case CAN0 :
				ptrMsgObj->msgLEN = (CAN0_IF2_REGs->CANIF2MCTL &0xF);	
			break;
		
//the same process for CAN1 module		
		case CAN1 :
				ptrMsgObj->msgLEN = (CAN0_IF2_REGs->CANIF2MCTL &0xF);	
			break;
	}		
	
}


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



