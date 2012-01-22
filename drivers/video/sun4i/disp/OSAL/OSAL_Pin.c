/*
*************************************************************************************
*                         			eBsp
*					   Operation System Adapter Layer
*
*				(c) Copyright 2006-2010, All winners Co,Ld.
*							All	Rights Reserved
*
* File Name 	: OSAL_Pin.h
*
* Author 		: javen
*
* Description 	: C�⺯��
*
* History 		:
*      <author>    		<time>       	<version >    		<desc>
*       javen     	   2010-09-07          1.0         create this word
*       holi     	   2010-12-02          1.1         ��Ӿ���Ľӿڣ�
*************************************************************************************
*/
#include "OSAL_Pin.h"

/*
****************************************************************************************************
*
*             OSAL_GPIO_Request
*
*  Description:
*       ����ĳ���߼��豸��PIN��������������ĳ���豸�Ĳ���PIN��
*
*  Parameters:
* 		gpio_list	    :	GPIO�����ݽṹ
*       group_count_max :   GPIO���ݽṹ��������
* Returns    :
*		�ɹ�                ���ؾ��
*       ʧ��                ���ؿ�
* Notes      :
*
****************************************************************************************************
*/

__hdle OSAL_GPIO_Request(user_gpio_set_t *gpio_list, __u32 group_count_max)
{
    gpio_request(gpio_list, group_count_max);
    
    return 0;
}


/*
****************************************************************************************************
*
*             OSAL_GPIO_Request_Ex
*
*  Description:
*       �������ýű��е�GPIO���ƣ����ú�����ƥ���GPIO����
*
*  Parameters:
* 		main_name	    :	���ýű���GPIO����
* Returns    :
*		�ɹ�                ���ؾ��
*       ʧ��                ���ؿ�
* Notes      :
*
****************************************************************************************************
*/
__hdle OSAL_GPIO_Request_Ex(char *main_name)
{
    return 0;
}
/*
****************************************************************************************************
*
*             OSAL_GPIO_Release
*
*  Description:
*       �ͷ�GPIO
*
*  Parameters:
* 		p_handler	:	handler
*       if_release_to_default_status   :  0����1   ���ͷź�GPIO��Ϊ����״̬
*                                              2   : �ͷź�GPIO״̬���ֲ���
*
* Returns    :
*		�ɹ�            ����0
*       ʧ��            ����-1
* Notes      :
*
****************************************************************************************************
*/
__s32 OSAL_GPIO_Release(__hdle p_handler, __s32 if_release_to_default_status)
{
    gpio_release(p_handler, if_release_to_default_status);
    
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevGetAllPins_Status
*
* Description:
*		��ȡ����GPIO����Ϣ
* Arguments  :
*		devpin  	           :	GPIO���
*		gpio_status	           :	���GPIO��Ϣ�����ݽṹ����ַ
*		gpio_count_max	       :	�û������ݽṹ��������
*		if_get_from_hardware   :	0 ��ȡ�û��������Ĳ���  1 ��ȡ��ǰӲ�����õĲ���
* Returns    :
*		                            �ɹ�����0, ʧ�ܷ���-1
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevGetAllPins_Status(__hdle devpin,  user_gpio_set_t  *gpio_status,  __u32 gpio_count_max , __u32 if_get_from_hardware)
{
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevGetONEPins_Status
*
* Description:
*		��ȡ����GPIO����Ϣ
* Arguments  :
*		devpin  	           :	GPIO���
*		gpio_status	           :	���GPIO��Ϣ�����ݽṹ����ַ
*		gpio_name   	       :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*		if_get_from_hardware   :	0 ��ȡ�û��������Ĳ���  1 ��ȡ��ǰӲ�����õĲ���
* Returns    :
*		�ɹ�����0, ʧ�ܷ���-1
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevGetONEPins_Status(__hdle devpin,    user_gpio_set_t  *gpio_status,  const char *gpio_name, __u32 if_get_from_hardware)
{
    return 0;
}



/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevSetONEPin_Status
*
* Description:
*		���õ���GPIO��״̬
* Arguments  :
*		devpin  	           :	GPIO���
*		gpio_status	           :	���GPIO��Ϣ�����ݽṹ����ַ
*		gpio_name   	       :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*		if_get_from_hardware   :	0 �����û��������Ĳ�������  1 ���յ�ǰ�û�����Ĳ�������
* Returns    :
*		�ɹ�����0, ʧ�ܷ���-1
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevSetONEPin_Status(__hdle devpin,    user_gpio_set_t  *gpio_status,  const char *gpio_name, __u32 if_set_to_current_input_status)
{
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevSetONEPIN_IO_STATUS
*
* Description:
*		���õ���GPIO��IO״̬
* Arguments  :
*		devpin  	                :	GPIO���
*		if_set_to_output_status	    :	0 ���ó�����״̬  1 ���ó�����״̬
*		gpio_name   	            :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*
* Returns    :
*		�ɹ�����0, ʧ�ܷ���-1
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevSetONEPIN_IO_STATUS(__hdle devpin,  __u32 if_set_to_output_status,  const char *gpio_name)
{
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevSetONEPIN_PULL_STATUS
*
* Description:
*		���õ���GPIO�����õ���״̬
* Arguments  :
*		devpin  	                :	GPIO���
*		if_set_to_output_status	    :	0 ���óɸ���  1 ���ó�����  2 ���ó�����
*		gpio_name   	            :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*
* Returns    :
*		�ɹ�����0, ʧ�ܷ���-1
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevSetONEPIN_PULL_STATUS(__hdle devpin,  __u32 if_set_to_output_status,  const char *gpio_name)
{
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevREAD_ONEPIN_DATA
*
* Description:
*		���õ���GPIO����������״̬
* Arguments  :
*		devpin  	                :	GPIO���
*		gpio_name   	            :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*
* Returns    :
*		��ȡGPIO��״̬   0���͵�ƽ  1���ߵ�ƽ  -1����ǰGPIO��������״̬���޷���ȡֵ
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevREAD_ONEPIN_DATA(__hdle devpin,  const char *gpio_name)
{
    gpio_read_one_pin_value(devpin, gpio_name);
    
    return 0;
}


/*
**********************************************************************************************************************
*                                               OSAL_GPIO_DevWRITE_ONEPIN_DATA
*
* Description:
*		���õ���GPIO����������״̬
* Arguments  :
*		devpin  	                :	GPIO���
*       value_to_gpio               :   �û����õĵ�ƽ  0���͵�ƽ  1���ߵ�ƽ
*		gpio_name   	            :	�û�Ҫ��ȡ��GPIO�����ƣ����������Դ�����ýű�
*
* Returns    :
*		�ɹ�����0   ʧ�ܷ���-1    �����ǰGPIO�������״̬���᷵��ʧ��
* Notes      :
*
**********************************************************************************************************************
*/
__s32 OSAL_GPIO_DevWRITE_ONEPIN_DATA(__hdle devpin, __u32 value_to_gpio, const char *gpio_name)
{
    gpio_write_one_pin_value(devpin, value_to_gpio, gpio_name);
    
    return 0;
}


