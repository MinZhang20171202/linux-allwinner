/*
********************************************************************************************************************
*                                              usb controller
*
*                              (c) Copyright 2007-2009, 
*										All	Rights Reserved
*
* File Name 	: usbc_phy.c
*
* Author 		: daniel
*
* Version 		: 1.0
*
* Date 			: 2009.10.21
*
* Description 	: ������suniiƽ̨��USB������������
*
* History 		: 
*
********************************************************************************************************************
*/

#include  "usbc_i.h"


/*
 ***************************************************************************
 *
 * ����USB PHY���ƼĴ���λ
 *
 ***************************************************************************
 */

//Common Control Bits for Both PHYs
#define  USBC_PHY_PLL_BW				0x03
#define  USBC_PHY_RES45_CAL_EN			0x0c

//Private Control Bits for Each PHY
#define  USBC_PHY_TX_AMPLITUDE_TUNE		0x20
#define  USBC_PHY_TX_SLEWRATE_TUNE		0x22
#define  USBC_PHY_VBUSVALID_TH_SEL		0x25
#define  USBC_PHY_PULLUP_RES_SEL		0x27
#define  USBC_PHY_OTG_FUNC_EN			0x28
#define  USBC_PHY_VBUS_DET_EN			0x29
#define  USBC_PHY_DISCON_TH_SEL			0x2a
		
#if 0
/*
 ***************************************************************************
 *
 * read out one bit of USB PHY register
 *
 ***************************************************************************
 */
static __u32 __USBC_PHY_REG_READ(__u32 usbc_base_addr, __u32 usbc_phy_reg_addr)
{
  	__u32 reg_val = 0;
  	__u32 i = 0;
  	
  	USBC_Writeb(usbc_phy_reg_addr, USBC_REG_PHYCTL(USBC0_REGS_BASE) + 1);
  	for(i=0; i<0x4; i++);
  	reg_val = USBC_Readb(USBC_REG_PHYCTL(USBC0_REGS_BASE) + 2);
  	if(usbc_base_addr == USBC0_REGS_BASE)
  		return (reg_val & 0x1);
  	else
  		return ((reg_val >> 1) & 0x1);
}

/*
 ***************************************************************************
 *
 * Write one bit of USB PHY register
 *
 ***************************************************************************
 */
static void __USBC_PHY_REG_WRITE(__u32 usbc_base_addr, __u32 usbc_phy_reg_addr, __u32 usbc_phy_reg_data)
{
  	__u32 reg_val = 0;
  	
  	USBC_Writeb(usbc_phy_reg_addr, USBC_REG_PHYCTL(USBC0_REGS_BASE) + 1);
  	reg_val = USBC_Readb(USBC_REG_PHYCTL(USBC0_REGS_BASE));
  	reg_val &= ~(0x1 << 7);
  	reg_val |= (usbc_phy_reg_data & 0x1) << 7;
  	if(usbc_base_addr == USBC0_REGS_BASE){
  		reg_val &= ~0x1;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  		reg_val |= 0x1;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  		reg_val &= ~0x1;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  	}else{
  		reg_val &= ~0x2;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  		reg_val |= 0x2;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  		reg_val &= ~0x2;
  		USBC_Writeb(reg_val, USBC_REG_PHYCTL(USBC0_REGS_BASE));
  	} 
}


/*
 ***************************************************************************
 *
 * Set USB PLL BandWidth, val = 0~3, defualt = 0x2
 *
 ***************************************************************************
 */
/*
static void __USBC_PHY_SET_PLL_BW(__u32 val)
{
    __USBC_PHY_REG_WRITE(USBC0_REGS_BASE, USBC_PHY_PLL_BW, val);
    __USBC_PHY_REG_WRITE(USBC0_REGS_BASE, USBC_PHY_PLL_BW + 1, val >> 1);    
}
*/

/*
 ***************************************************************************
 *
 * Enable/Disable USB res45 Calibration, val = 0--Disable��1--Enable, default = 0
 *
 ***************************************************************************
 */
static void __USBC_PHY_RES45_CALIBRATION_ENABLE(__u32 val)
{
    __USBC_PHY_REG_WRITE(USBC0_REGS_BASE, USBC_PHY_RES45_CAL_EN, val);
}

/*
 ***************************************************************************
 *
 * Set USB TX Signal Amplitude, val = 0~3, default = 0x0
 *
 ***************************************************************************
 */
static void __USBC_PHY_SET_TX_AMPLITUDE(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_TX_AMPLITUDE_TUNE, val);
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_TX_AMPLITUDE_TUNE + 1, val >> 1);    
}

/*
 ***************************************************************************
 *
 * Set USB TX Signal Slew Rate, val = 0~7, default = 0x5
 *
 ***************************************************************************
 */
static void __USBC_PHY_SET_TX_SLEWRATE(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_TX_SLEWRATE_TUNE, val);
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_TX_SLEWRATE_TUNE + 1, val >> 1); 
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_TX_SLEWRATE_TUNE + 2, val >> 2);      
}

/*
 ***************************************************************************
 *
 * Set USB VBUS Valid Threshold, val = 0~3, default = 2
 *
 ***************************************************************************
 */
/*
static void __USBC_PHY_SET_VBUS_VALID_THRESHOLD(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_VBUSVALID_TH_SEL, val);
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_VBUSVALID_TH_SEL + 1, val >> 1);    
}
*/

/*
 ***************************************************************************
 *
 * Enable/Diasble USB OTG Function, val = 0--Disable��1--Enable, default = 1
 *
 ***************************************************************************
 */
/*
static void __USBC_PHY_OTG_FUNC_ENABLE(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_OTG_FUNC_EN, val);
}
*/

/*
 ***************************************************************************
 *
 * Enable/Diasble USB VBUS Detect Function, val = 0--Disable��1--Enable, default = 1
 *
 ***************************************************************************
 */
/*
static void __USBC_PHY_VBUS_DET_ENABLE(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_VBUS_DET_EN, val);
}
*/

/*
 ***************************************************************************
 *
 * Set USB Disconnect Detect Threshold, val = 0~3, default = 1
 *
 ***************************************************************************
 */
static void __USBC_PHY_SET_DISCON_DET_THRESHOLD(__u32 usbc_base_addr, __u32 val)
{
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_DISCON_TH_SEL, val);
    __USBC_PHY_REG_WRITE(usbc_base_addr, USBC_PHY_DISCON_TH_SEL + 1, val >> 1);    
}
#endif

/*
***********************************************************************************
*                     USBC_PHY_SetCommonConfig
*
* Description:
*    Phy�Ĺ������ã�����USB PHY�Ĺ�����ʼ��
*
* Arguments:
*    NULL
*
* Returns:
*    NULL
*
* note:
*    ��
*
***********************************************************************************
*/
void USBC_PHY_SetCommonConfig(void)
{
    //__USBC_PHY_RES45_CALIBRATION_ENABLE(1);    
}

/*
***********************************************************************************
*                     USBC_PHY_SetPrivateConfig
*
* Description:
*    USB PHY�ĸ�������
*
* Arguments:
*    hUSB       :  input.  USBC_open_otg��õľ��, ��¼��USBC����Ҫ��һЩ�ؼ�����
*
* Returns:
*    NULL
*
* note:
*    ��
*
***********************************************************************************
*/
void USBC_PHY_SetPrivateConfig(__hdle hUSB)
{
//    __usbc_otg_t *usbc_otg = (__usbc_otg_t *)hUSB;
//    
//	if(usbc_otg == NULL){
//		return ;
//	}
//    
//    USBC_REG_set_bit_l(0, USBC_REG_PHYTUNE(usbc_otg->base_addr));
//    USBC_REG_set_bit_l(7, USBC_REG_PHYTUNE(usbc_otg->base_addr));
//    USBC_REG_set_bit_l(6, USBC_REG_PHYTUNE(usbc_otg->base_addr));
//    USBC_REG_set_bit_l(5, USBC_REG_PHYTUNE(usbc_otg->base_addr));
//    USBC_REG_set_bit_l(4, USBC_REG_PHYTUNE(usbc_otg->base_addr));
//    //__USBC_PHY_SET_TX_AMPLITUDE(usbc_otg->base_addr, 2);
//    //__USBC_PHY_SET_TX_SLEWRATE(usbc_otg->base_addr, 6);
//    //__USBC_PHY_SET_DISCON_DET_THRESHOLD(usbc_otg->base_addr, 3);    
}

/*
***********************************************************************************
*                     USBC_PHY_GetCommonConfig
*
* Description:
*    ��ȡPhy�Ĺ������ã���Ҫ����Debug����Phy�������Ƿ���ȷ
*
* Arguments:
*    NULL
*
* Returns:
*    32bits��USB PHY��������ֵ
*
* note:
*    ��
*
***********************************************************************************
*/
__u32 USBC_PHY_GetCommonConfig(void)
{
    __u32 reg_val = 0;
/*
    __u32 i = 0;
    
    reg_val = 0;
	for(i=0; i<0x20; i++)
	{
		reg_val = reg_val << 1;
		reg_val |= __USBC_PHY_REG_READ(USBC0_REGS_BASE, (0x1f - i)) & 0x1;
	}
*/
	return reg_val;
}


/* usb phy control*/
EXPORT_SYMBOL(USBC_PHY_SetCommonConfig);
EXPORT_SYMBOL(USBC_PHY_SetPrivateConfig);
EXPORT_SYMBOL(USBC_PHY_GetCommonConfig);


