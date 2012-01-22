
#include "lcd_panel_cfg.h"

static __s32 LCD_open_flow(__u32 sel)
{
	LCD_OPEN_FUNC(sel, LCD_power_on, 10); //��LCD����,���ӳ�10ms
	LCD_OPEN_FUNC(sel, TCON_open, 200); //��LCD������,���ӳ�200ms
	LCD_OPEN_FUNC(sel, LCD_bl_open, 0); //�򿪱���,���ӳ�0ms

	return 0;
}

static __s32 LCD_close_flow(__u32 sel)
{	
	LCD_CLOSE_FUNC(sel, LCD_bl_close, 0); //�رձ���,���ӳ�0ms
	LCD_CLOSE_FUNC(sel, TCON_close, 0); //�ر�LCD ������,���ӳ�0ms
	LCD_CLOSE_FUNC(sel, LCD_power_off, 20); //�ر�LCD����,���ӳ�20ms

	return 0;
}

////////////////////////////////////////   POWER   ////////////////////////////////////////////////////////////////////
static void LCD_power_on(__u32 sel)
{
    LCD_POWER_EN(sel, 1);
}

static void LCD_power_off(__u32 sel)
{
    LCD_POWER_EN(sel, 0);
}

////////////////////////////////////////   back light   ////////////////////////////////////////////////////////////////////
static void LCD_bl_open(__u32 sel)
{
    LCD_BL_EN(sel, 1);
    LCD_PWM_EN(sel, 1);
}

static void LCD_bl_close(__u32 sel)
{
    LCD_BL_EN(sel, 0);
    LCD_PWM_EN(sel, 0);
}


void LCD_get_panel_funs_1(__lcd_panel_fun_t * fun)
{
    fun->cfg_open_flow = LCD_open_flow;
    fun->cfg_close_flow = LCD_close_flow;
}
