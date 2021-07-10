/**
  ******************************************************************************
  * @file    usb_bot.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   BOT State Machine management
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_scsi.h"
#include "usb_bot.h"

#include "ch554_platform.h"
#include "usb_mal.h"

#include "usb_endp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
xdata uint8_t Bot_State = BOT_IDLE;
xdata Bulk_Only_CBW CBW;
xdata uint16_t dataResidue;
xdata uint32_t SCSI_LBA;
xdata uint16_t SCSI_BlkLen;
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// Bulk-Only Mass Storage Reset
void Bot_MSR(void) {
	//BOT_EP_Tx_RTOG();
	//BOT_EP_Rx_RTOG();
	//CBW.dSignature0 = BOT_CBW_SIGNATURE0;
	//CBW.dSignature1 = BOT_CBW_SIGNATURE1;
	//CBW.dSignature2 = BOT_CBW_SIGNATURE2;
	//CBW.dSignature3 = BOT_CBW_SIGNATURE3;
	//Bot_State = BOT_IDLE;
}

uint8_t Bot_Get_Max_Lun(void) {
	return MAL_MAX_LUN;
}

/*******************************************************************************
* Function Name  : Mass_Storage_In
* Description    : Mass Storage IN transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Mass_Storage_In (void) {
	switch (Bot_State) {
    	case BOT_CSW_Send:
    	case BOT_ERROR:
    		Bot_State = BOT_IDLE;

    		// Enable the Endpoint to receive the next cmd
    		// SetEPRxStatus(ENDP2, EP_RX_VALID);
			BOT_EP_Rx_Valid();
			break;
    	case BOT_DATA_IN:
    		if (CBW.CB[0] == SCSI_READ10) {
    			SCSI_Read10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
			}
    		break;
    	case BOT_DATA_IN_LAST:
    		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
    		// SetEPRxStatus(ENDP2, EP_RX_VALID);
			BOT_EP_Rx_Valid();
			break;
		case BOT_DATA_IN_LAST_FAIL:
			Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);

			// SetEPRxStatus(ENDP2, EP_RX_VALID);
			BOT_EP_Rx_Valid();
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name  : Mass_Storage_Out
* Description    : Mass Storage OUT transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Mass_Storage_Out (void) {
	if (!U_TOG_OK)
		return;	// Discard unsychronized packets
	
	switch (Bot_State) {
		case BOT_IDLE:
			CBW_Decode();
			break;
		case BOT_DATA_OUT:
			if (CBW.CB[0] == SCSI_WRITE10) {
				SCSI_Write10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
			} else {
				Bot_Abort(DIR_OUT);
				Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
				Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);				
			}
			break;
		default:
			Bot_Abort(BOTH_DIR);
			Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
			Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
	} // switch (Bot_State)
}

/*******************************************************************************
* Function Name  : CBW_Decode
* Description    : Decode the received CBW and call the related SCSI command
*                 routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CBW_Decode(void) {
	uint8_t i;

	// Copy CBW from Endpoint Rx Buffer
	for (i = 0; i < BOT_EP_Rx_Length; i++)
		((uint8_t*)(&CBW))[i] = BOT_Rx_Buf[i];
	
	U32_XLittle(&CBW.dDataLength, &BOT_Rx_Buf[8]);
	dataResidue = CBW.dDataLength;
	
	// NOTE: CH554 seems receive incorrect packet length!
	// This needs to be confirmed! Might be a hardware problem
	//if (BOT_EP_Rx_Length != BOT_CBW_PACKET_LENGTH) {
    //Bot_Abort(BOTH_DIR);
    // Clear the CBW.dSignature to disable the clear feature until receiving a Mass storage reset
	//CBW.dSignature0 = 0;
	//CBW.dSignature1 = 0;
	//CBW.dSignature2 = 0;
	//CBW.dSignature3 = 0;
    //Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, PARAMETER_LIST_LENGTH_ERROR);
    //Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    //return;
	//}
	
	if ((CBW.CB[0] == SCSI_READ10 ) || (CBW.CB[0] == SCSI_WRITE10 )) {
		// Calculate Logical Block Address
		U32_XBig(&SCSI_LBA, &CBW.CB[2]);

		// Calculate the Number of Blocks to transfer
		U16_XBig(&SCSI_BlkLen, &CBW.CB[7]);
	}
	
	if (
		  CBW.dSignature0 == BOT_CBW_SIGNATURE0 &&
		  CBW.dSignature1 == BOT_CBW_SIGNATURE1 &&
		  CBW.dSignature2 == BOT_CBW_SIGNATURE2 &&
		  CBW.dSignature3 == BOT_CBW_SIGNATURE3 ){

		if ((CBW.bLUN > MAL_MAX_LUN) || (CBW.bCBLength < 1) || (CBW.bCBLength > 16)) {
			Bot_Abort(BOTH_DIR);
			Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
			Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
		} else {
			// Valid CBW
			switch (CBW.CB[0]) {
				case SCSI_REQUEST_SENSE:
					SCSI_RequestSense_Cmd (CBW.bLUN);
					break;
				case SCSI_INQUIRY:
					SCSI_Inquiry_Cmd(CBW.bLUN);
					break;
				case SCSI_START_STOP_UNIT:
					SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
					break;
				case SCSI_ALLOW_MEDIUM_REMOVAL:
					SCSI_Allow_Medium_Removal_Cmd(CBW.bLUN);
				  break;
				case SCSI_MODE_SENSE6:
					SCSI_ModeSense6_Cmd (CBW.bLUN);
					break;
				case SCSI_MODE_SENSE10:
					SCSI_ModeSense10_Cmd (CBW.bLUN);
					break;
				case SCSI_READ_FORMAT_CAPACITIES:
					SCSI_ReadFormatCapacity_Cmd(CBW.bLUN);
					break;
				case SCSI_READ_CAPACITY10:
					SCSI_ReadCapacity10_Cmd(CBW.bLUN);
					break;
				case SCSI_TEST_UNIT_READY:
					SCSI_TestUnitReady_Cmd(CBW.bLUN);
					break;
				case SCSI_READ10:
					SCSI_Read10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
					break;
				case SCSI_WRITE10:
					SCSI_Write10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
					break;
				case SCSI_VERIFY10:
					SCSI_Verify10_Cmd(CBW.bLUN);
					break;
				case SCSI_FORMAT_UNIT:
					SCSI_Format_Cmd(CBW.bLUN);
					break;
				  /*Unsupported command*/
				case SCSI_MODE_SELECT10:
					SCSI_Mode_Select10_Cmd(CBW.bLUN);
					break;
				case SCSI_MODE_SELECT6:
					SCSI_Mode_Select6_Cmd(CBW.bLUN);
					break;

				case SCSI_SEND_DIAGNOSTIC:
					SCSI_Send_Diagnostic_Cmd(CBW.bLUN);
					break;
				case SCSI_READ6:
					SCSI_Read6_Cmd(CBW.bLUN);
					break;
				case SCSI_READ12:
					SCSI_Read12_Cmd(CBW.bLUN);
					break;
				case SCSI_READ16:
					SCSI_Read16_Cmd(CBW.bLUN);
					break;
				case SCSI_READ_CAPACITY16:
					SCSI_READ_CAPACITY16_Cmd(CBW.bLUN);
					break;
				case SCSI_WRITE6:
					SCSI_Write6_Cmd(CBW.bLUN);
					break;
				case SCSI_WRITE12:
					SCSI_Write12_Cmd(CBW.bLUN);
					break;
				case SCSI_WRITE16:
					SCSI_Write16_Cmd(CBW.bLUN);
					break;
				case SCSI_VERIFY12:
					SCSI_Verify12_Cmd(CBW.bLUN);
					break;
				case SCSI_VERIFY16:
					SCSI_Verify16_Cmd(CBW.bLUN);
					break;

				default:
					Bot_Abort(BOTH_DIR);
					Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
					Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
			} // switch (CBW.CB[0])
		}
	} else { // End of checking signature
		// Invalid CBW
		Bot_Abort(BOTH_DIR);
		Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
		Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
	}
}

/*******************************************************************************
* Function Name  : Transfer_Data_Request
* Description    : Send the request response to the PC HOST.
* Input          : uint8_t* Data_Address : point to the data to transfer.
*                  uint16_t Data_Length : the number of Bytes to transfer.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Transfer_Data_Request(uint8_t* Data_Pointer, uint8_t Data_Len) {
	dataResidue -= Data_Len;
	
  // USB_SIL_Write(EP1_IN, Data_Pointer, Data_Len);
	BOT_EP_Tx_Count(Data_Len);
	while (Data_Len--)
		BOT_Tx_Buf[Data_Len] = Data_Pointer[Data_Len];
	
	// SetEPTxStatus(ENDP1, EP_TX_VALID);
	BOT_EP_Tx_Valid();	// Enable Tx
	
	Bot_State = BOT_DATA_IN_LAST;
}

void Reply_Request(uint8_t Data_Len) {
	dataResidue -= Data_Len;
	BOT_EP_Tx_Count(Data_Len);
	BOT_EP_Tx_Valid();	// Enable Tx	

	Bot_State = BOT_DATA_IN_LAST;
}

void Transfer_Failed_ReadWrite(void) {
	BOT_EP_Tx_Count(0);	// Send an empty packet
	BOT_EP_Tx_Valid();	// Enable Tx	
	
	Bot_State = BOT_DATA_IN_LAST_FAIL;
}

/*******************************************************************************
* Function Name  : Set_CSW
* Description    : Set the SCW with the needed fields.
* Input          : uint8_t CSW_Status this filed can be CSW_CMD_PASSED,CSW_CMD_FAILED,
*                  or CSW_PHASE_ERROR.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_CSW (uint8_t CSW_Status, uint8_t Send_Permission)
{
	// Make CSW
	BOT_EP_Tx_Count(CSW_DATA_LENGTH);
	// CSW.dSignature
	BOT_Tx_Buf[0] = BOT_CSW_SIGNATURE0;
	BOT_Tx_Buf[1] = BOT_CSW_SIGNATURE1;
	BOT_Tx_Buf[2] = BOT_CSW_SIGNATURE2;
	BOT_Tx_Buf[3] = BOT_CSW_SIGNATURE3;
	
	// CSW.dTag
	BOT_Tx_Buf[4] = CBW.dTag0;
	BOT_Tx_Buf[5] = CBW.dTag1;
	BOT_Tx_Buf[6] = CBW.dTag2;
	BOT_Tx_Buf[7] = CBW.dTag3;
	
	// CSW.dDataResidue (little-endian)
	U16_XLittle(&BOT_Tx_Buf[8], &dataResidue);
	BOT_Tx_Buf[10] = 0;
	BOT_Tx_Buf[11] = 0;
	
	// CSW.bStatus
	BOT_Tx_Buf[12] = CSW_Status;
	
	Bot_State = BOT_ERROR;
	if (Send_Permission) {
		Bot_State = BOT_CSW_Send;
		// SetEPTxStatus(ENDP1, EP_TX_VALID);
		BOT_EP_Tx_Valid();	// Enable Tx
	}
}

/*******************************************************************************
* Function Name  : Bot_Abort
* Description    : Stall the needed Endpoint according to the selected direction.
* Input          : Endpoint direction IN, OUT or both directions
* Output         : None.
* Return         : None.
*******************************************************************************/
void Bot_Abort(uint8_t Direction) {
	switch (Direction) {
    	case DIR_IN :
    		// SetEPTxStatus(ENDP1, EP_TX_STALL);
			BOT_EP_Tx_Stall();
			break;
    	case DIR_OUT :
    		// SetEPRxStatus(ENDP2, EP_RX_STALL);
			BOT_EP_Rx_Stall();
			break;
    	case BOTH_DIR :
    		// SetEPTxStatus(ENDP1, EP_TX_STALL);
			BOT_EP_Tx_Stall();
			// SetEPRxStatus(ENDP2, EP_RX_STALL);
			BOT_EP_Rx_Stall();
			break;
    	default:
    		break;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
