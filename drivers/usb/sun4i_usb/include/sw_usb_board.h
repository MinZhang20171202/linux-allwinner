/*
*************************************************************************************
*                         			      Linux
*					           USB Host Controller Driver
*
*				        (c) Copyright 2006-2010, All winners Co,Ld.
*							       All Rights Reserved
*
* File Name 	: sw_usb_board.h
*
* Author 		: javen
*
* Description 	: �弶����
*
* Notes         :
*
* History 		:
*      <author>    		<time>       	<version >    		<desc>
*       javen     	  2010-12-20           1.0          create this file
*
*************************************************************************************
*/
#ifndef  __SW_USB_BOARD_H__
#define  __SW_USB_BOARD_H__

//----------------------------------------------------------
//
//----------------------------------------------------------
#define  SET_USB_PARA				"usb_para"
#define  SET_USB0					"usbc0"
#define  SET_USB1					"usbc1"
#define  SET_USB2					"usbc2"

#define  KEY_USB_GLOBAL_ENABLE		"usb_global_enable"
#define  KEY_USBC_NUM				"usbc_num"

#define  KEY_USB_ENABLE				"usb_enable"
#define  KEY_USB_PORT_TYPE			"usb_port_type"
#define  KEY_USB_DETECT_TYPE		"usb_detect_type"
#define  KEY_USB_ID_GPIO			"usb_id_gpio"
#define  KEY_USB_DETVBUS_GPIO		"usb_det_vbus_gpio"
#define  KEY_USB_DRVVBUS_GPIO		"usb_drv_vbus_gpio"

//---------------------------------------------------------------
//
//---------------------------------------------------------------
enum usb_pio_group_type
{
    GROUP_TYPE_PIO = 0,
    GROUP_TYPE_POWER
};

enum usb_port_type
{
    USB_PORT_TYPE_DEVICE = 0,
    USB_PORT_TYPE_HOST,
    USB_PORT_TYPE_OTG
};

enum usb_detect_type
{
    USB_DETECT_TYPE_NULL = 0,
    USB_DETECT_TYPE_DP_DM,
    USB_DETECT_TYPE_VBUS_ID
};

/* pio��Ϣ */
typedef struct tag_borad_pio
{
	__u32 valid;          	/* pio�Ƿ���á� 0:��Ч, !0:��Ч	*/

	__u32 group_type;		/* pio����,	enum usb_pio_group_type	*/
	__u32 power_pin_no;		/* power pin number */
	user_gpio_set_t gpio_set;
}board_pio_t;

/* ������������Ϣ */
typedef struct tag_borad_usb_port{
	__u32 usb_enable;		/* port�Ƿ���á� 0:��Ч, !0:��Ч		*/
	__u32 usb_port_type;	/* usb�˿����͡�						*/
	__u32 usb_detect_type;	/* usb��ⷽʽ��						*/

	board_pio_t id;			/* usb id pin��Ϣ 						*/
	board_pio_t det_vbus;	/* usb vbus pin��Ϣ 					*/
	board_pio_t drv_vbus;	/* usb drv_vbus pin��Ϣ 				*/
}borad_usb_port_t;

typedef struct tag_usb_board_info{
	u32 usb_global_enable;	/* USB ʹ�ܿ��� */
	u32 usbc_num;			/* ʹ��USB �˿ڵĸ��� */

	borad_usb_port_t usb_port[USBC_MAX_CTL_NUM];
}usb_board_info_t;

#endif   //__SW_USB_BOARD_H__

