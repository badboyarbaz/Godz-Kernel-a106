
/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	extern void Tinno_set_HS_read();
	extern void Tinno_restore_HS_read();
	extern void DSI_clk_HS_mode(bool enter);
	extern void DSI_clk_ULP_mode(bool enter);
typedef enum
{	
	DSI_STATUS_OK = 0,

	DSI_STATUS_ERROR,
} DSI_STATUS;	

   // extern BOOL is_early_suspended;
	extern DSI_STATUS DSI_Reset();
	extern DSI_STATUS DSI_DumpRegisters(void);
    extern DSI_STATUS DSI_StartTransfer(bool isMutexLocked);
    extern DSI_STATUS DSI_Deinit(void);
	extern DSI_STATUS DSI_Init(bool isDsiPoweredOn);
	extern DSI_STATUS DSI_PowerOff(void);
	#include <mach/mt_gpio.h>
#endif

#ifdef BUILD_LK
#define LCM_PRINT printf
#else
#if defined(BUILD_UBOOT)
#define LCM_PRINT printf
#else
#define LCM_PRINT printk
#endif
#endif

#define LCM_DBG(fmt, arg...) \
	LCM_PRINT ("[LCM-HX8394A-HD720-DSI-VDO-TCL] %s (line:%d) :" fmt "\r\n", __func__, __LINE__, ## arg)


// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define LCM_ID_HX8394 (0x94)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   

#define   LCM_DSI_CMD_MODE							0

static void init_lcm_registers(void)
{

	/*
		Note :
	
		Data ID will depends on the following rule.
		
			count of parameters > 1 => Data ID = 0x39
			count of parameters = 1 => Data ID = 0x15
			count of parameters = 0 => Data ID = 0x05
	
		Structure Format :
	
		{DCS command, count of parameters, {parameter list}}
		{REGFLAG_DELAY, milliseconds of time, {}},
	
		...
	
		Setting ending by predefined flag
		
		{REGFLAG_END_OF_TABLE, 0x00, {}}
		*/


	unsigned int data_array[16];
	
	//data_array[0] = 0x00110500; // Sleep Out
	//dsi_set_cmdq(data_array, 1, 1);
	//MDELAY(200);

	//PacketHeader[39 04 00 xx] // Set EXTC 
	//Payload[B9 FF 83 94] 
      data_array[0] = 0x00043902;                          
      data_array[1] = 0x9483ffb9;                 
      dsi_set_cmdq(&data_array, 2, 1);	
	MDELAY(1);
      //PacketHeader[39 11 00 xx] // Set MIPI 
      //Payload[BA 13 82 00 16 C5 00 10 FF 0F 24 03 21 24 25 20 08] 
      data_array[0] = 0x00113902;                          
      data_array[1] = 0x008213ba;      
      data_array[2] = 0x1000c516;   
      data_array[3] = 0x04340fff;   // 20131031 adj   03 24 0f ff
      data_array[4] = 0x2c252421;   
      data_array[5] = 0x00000008;   	  
      dsi_set_cmdq(&data_array, 4, 1);	
	MDELAY(1);
      //PacketHeader[39 11 00 xx] // Set Power 
      //Payload[B1 01 00 04 87 01 11 11 2F 37 3F 3F 47 12 01 E6 E2] 
      data_array[0] = 0x00113902;                          
      data_array[1] = 0x040001b1;      
      data_array[2] = 0x11110187;   
      data_array[3] = 0x3f3f352d;     // 37  2f
      data_array[4] = 0xe6010a47;     // 20131031 adj   e6 01 02 47
	  data_array[5] = 0x000000e2;  
      dsi_set_cmdq(&data_array, 6, 1);	
	MDELAY(1);
	//PacketHeader[39 07 00 xx] // Set Display 
       //Payload[B2 00 C8 08 04 00 22] 
      data_array[0] = 0x00073902;   
      data_array[1] = 0x08c800b2;      
      data_array[2] = 0x00220004;   
	dsi_set_cmdq(&data_array, 3, 1);	
	MDELAY(1);

	//PacketHeader[39 17 00 xx] // Set CYC 
       //Payload[B4 80 06 32; 10 03 32 15; 08 32 10 08; 33 04 43 05; 37 04 43 06; 61 61 06] 
	data_array[0] = 0x00173902;   
       data_array[1] = 0x320600b4;	  
	data_array[2] = 0x15320310;
	data_array[3] = 0x08103208;  
	data_array[4] = 0x05430433; 
	data_array[5] = 0x06430437;      // 06   adj 20131031
	data_array[6] = 0x00066161;        // 00 06 61 61 adj 20131031
	dsi_set_cmdq(&data_array, 7, 1);	
	MDELAY(1);
	//PacketHeader[39 05 00 xx] // Set PTBA 
	//Payload[BF 06 00 10 04] 
	data_array[0] = 0x00053902;   
    data_array[1] = 0x100006bf;	  
	data_array[2] = 0x00000004;
	dsi_set_cmdq(&data_array, 3, 1);	
	MDELAY(1);
	//PacketHeader[39 03 00 xx] // Set STBA 
	//Payload[C0 0C 17] 
	data_array[0] = 0x00033902;   
       data_array[1] = 0x00170cc0;
      dsi_set_cmdq(&data_array, 2, 1);
	 //PacketHeader[39 02 00 xx] // Set VCOM 
	 //Payload[B6 0B] 
	data_array[0] = 0x00023902;   
	data_array[1] = 0x000002b6;
       dsi_set_cmdq(&data_array, 2, 1);	
	MDELAY(1);
	//PacketHeader[39 21 00 xx] // Set GIP, Forward ONLY 
       //Payload[D5 00 00 00; 00 0A 00 01; 00 CC 00 00; 00 88 88 88; 88 88 88 88; 88 88 88 01; 67 45 23 01; 23 88 88 88 88] 
      data_array[0] = 0x00213902;   
      data_array[1] = 0x000000d5;
      data_array[2] = 0x01000a00;
      data_array[3] = 0x0000cc00;
      data_array[4] = 0x88888800;
      data_array[5] = 0x88888888;
      data_array[6] = 0x01888888;
      data_array[7] = 0x01234567;
      data_array[8] = 0x88888823;
      data_array[9] = 0x00000088;
      dsi_set_cmdq(&data_array, 10, 1);	
	MDELAY(1);
	//PacketHeader[39 02 00 xx] // Set Panel 
	//Payload[CC 01] 
	data_array[0] = 0x00023902;   
	data_array[1] = 0x000009cc;           // 01 cc
	dsi_set_cmdq(&data_array, 2, 1);	
	MDELAY(1);
	//PacketHeader[39 05 00 xx] // Set TCON OPT 
       //Payload[C7 00 10 00 10] 
       data_array[0] = 0x00053902;   
	data_array[1] = 0x001000C7;
	data_array[2] = 0x00000010;
	dsi_set_cmdq(&data_array, 3, 1);	
	MDELAY(1);
	
	//PacketHeader[39 2B 00 xx] // Set Gamma 
       //Payload[E0 00 04 06 2B 33 3F 13 34 0A 0E 0D 11 13 11 13 10 17 00 04 06 2B 33 3F 13 34 0A 0E 0D 11 13 11 13 10 17 0B 17 07 11 0B 17 07 11] 
	data_array[0] = 0x002b3902;   
	data_array[1] = 0x060400e0;
	data_array[2] = 0x133f332b;
	data_array[3] = 0x0d0e0a34 ;
	data_array[4] = 0x13111311;
	data_array[5] = 0x04001710;
      data_array[6] =  0x3f332b06;
      data_array[7] =  0x0e0a3413;
	data_array[8] = 0x1113110d;
	data_array[9] = 0x0b171013;
	data_array[10] = 0x0b110717;
	data_array[11] = 0x00110717;
	dsi_set_cmdq(data_array, 12, 1);	  // tttttttttttttttttttttttttttttttttttttttttttttttt
	MDELAY(1);
	//PacketHeader[39 02 00 xx] // Enhance EMI performance                                 Optional 
       //Payload[D4 32] 
       data_array[0] = 0x00023902;   
	data_array[1] = 0x000032d4;
	dsi_set_cmdq(&data_array, 2, 1);
	MDELAY(1);
	//PacketHeader[05 11 00 xx] // Sleep Out 
       //Delay 200ms 
	data_array[0] = 0x00110500; // Sleep Out
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(150);
       //PacketHeader[05 29 00 xx] // Display On 
       //Delay 10ms 
       data_array[0] = 0x00290500; // Sleep Out
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(10);

	  
}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type   = LCM_TYPE_DSI;
	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	params->dsi.mode   					= SYNC_PULSE_VDO_MODE;   //BURST_VDO_MODE;  // SYNC_PULSE_VDO_MODE
	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM				= LCM_FOUR_LANE;//LCM_FOUR_LANE;
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

	// Highly depends on LCD driver capability.
	// Not support in MT6573
	params->dsi.packet_size=256;
	
	
	
	
	
	
	// Video mode setting
	params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage
	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.word_count=720*3;

		params->dsi.vertical_sync_active				= 2;	//2;
		params->dsi.vertical_backporch					= 8;	//14;
		params->dsi.vertical_frontporch					= 6;	//16;
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 
		
		params->dsi.horizontal_sync_active				= 10;	//2;
		params->dsi.horizontal_backporch				= 160;	//60;	//42;
		params->dsi.horizontal_frontporch				= 160;	//60;	//44;
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

		// Bit rate calculation
		//1 Every lane speed
		//params->dsi.pll_div1=0;		// div1=0,1,2,3;div1_real=1,2,4,4 ----0: 546Mbps  1:273Mbps
		//params->dsi.pll_div2=0;		// div2=0,1,2,3;div1_real=1,2,4,4	
		//params->dsi.fbk_div =0x12;    // fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)	
		
		// zhangxiaofei add for test
		params->dsi.PLL_CLOCK = 265;	// 265
		
		//params->dsi.ssc_range=2;
		//params->dsi.ssc_disable=0;
		
				params->dsi.noncont_clock = TRUE;	
				params->dsi.noncont_clock_period = 2;
}
static unsigned int lcm_compare_id(void);
static void lcm_init(void)
{
	SET_RESET_PIN(1);
	MDELAY(5);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(120);      

	init_lcm_registers();

}



static void lcm_suspend(void)
{
	unsigned int data_array[16];

	data_array[0] = 0x00100500; // Sleep In
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(120);
	
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(120);    
}


static void lcm_resume(void)
{
   //1 do lcm init again to solve some display issue

	SET_RESET_PIN(1);
    MDELAY(5);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(20);      

	init_lcm_registers();  // test esd del 

}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	/*data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);

	data_array[0]= 0x00290508; //HW bug, so need send one HS packet
	dsi_set_cmdq(&data_array, 1, 1);
	
	data_array[0]= 0x002c3909;
	dsi_set_cmdq(&data_array, 1, 0);
*/
}
#endif


//BEGIN <add for lcm> <DATE20140307> <dd for lcm>> zhangxiaofei
#if defined(BUILD_UBOOT) || defined(BUILD_LK)
#include "cust_adc.h"
#define LCM_MAX_VOLTAGE 100 
#define LCM_MIN_VOLTAGE 0 
#define AUXADC_LCD_ID_CHANNEL	0
extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata);

static unsigned int lcm_adc_read_chip_id()
{
	int data[4] = {0, 0, 0, 0};
	int tmp = 0, rc = 0, iVoltage = 0;
	rc = IMM_GetOneChannelValue(AUXADC_LCD_ID_CHANNEL, data, &tmp);
	if(rc < 0) {
		LCM_DBG("read LCD_ID vol error");
		return 0;
	}
	else {
		iVoltage = (data[0]*1000) + (data[1]*10) + (data[2]);
		LCM_DBG("read LCD_ID success, data[0]=%d, data[1]=%d, data[2]=%d, data[3]=%d, iVoltage=%d\n", 
			data[0], data[1], data[2], data[3], iVoltage);
		if(	LCM_MIN_VOLTAGE <= iVoltage && iVoltage <= LCM_MAX_VOLTAGE)
			return 1;
		else
			return 0;
	}
	return 0;
}
#endif	
//END <add for lcm> <DATE20140307> <dd for lcm>> zhangxiaofei

static unsigned int lcm_compare_id(void)
{
	unsigned int id0,id1,id=0;
	unsigned char buffer[2];
	unsigned int array[16];
	  
    LCM_DBG();
	 
	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(1);
	SET_RESET_PIN(1);
	MDELAY(20); 

	array[0] = 0x00043902;                          
	array[1] = 0x9483ffb9;                 
	dsi_set_cmdq(&array, 2, 1);

	  
	MDELAY(20);
	memset(buffer, 0, sizeof(buffer));
	array[0] = 0x00023700;// return byte number
	dsi_set_cmdq(&array, 1, 1);
	//MDELAY(5);

	read_reg_v2(0xf4, buffer, 1);
	id=buffer[0];

	LCM_DBG("id0 = 0x%08x\n", id0);
	LCM_DBG("id1 = 0x%08x\n" , id1);
	LCM_DBG("id  = 0x%08x\n", id);
	
	#if defined(BUILD_UBOOT) || defined(BUILD_LK)
	return ((LCM_ID_HX8394 == id) && (lcm_adc_read_chip_id()))?1:0;
	#else
	return (LCM_ID_HX8394 == id)?1:0;
	#endif
	
	//return (LCM_ID_HX8394 == id)?1:0;
}

static unsigned int lcm_esd_check(void)
{
	unsigned int ret=FALSE;
#ifndef BUILD_LK	
	char  buffer[6];
	int   array[4];
	char esd1,esd2,esd3,esd4;
        if(lcm_esd_test)
        {
            lcm_esd_test = FALSE;
            return TRUE;
        }
        
    //Tinno_set_HS_read();
    
    array[0] = 0x00200500;
	dsi_set_cmdq(array, 1, 1);
    
#if 1
	array[0] = 0x00033700;
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0x09, buffer, 3);
	esd1=buffer[0];	
	esd2=buffer[1];
	esd3=buffer[2];
	//esd4=buffer[3];
	//LCM_DBG("esd1 = 0x%x, esd2 = 0x%x,esd3 = 0x%x", esd1, esd2, esd3);
	
	//Tinno_restore_HS_read();

	if(esd1==0x80 && esd2==0x73)
	{
		ret=FALSE;
	}
	else
	{			 
		ret=TRUE;
	}
#endif

	
#endif
	return ret;
}

static unsigned int lcm_esd_recover(void)
{
	LCM_DBG();

	//MDELAY(10);
	//DSI_Init(1);
	//MDELAY(10);

    //DSI_DumpRegisters();

	//DSI_Reset();

	
	
	DSI_clk_ULP_mode(1);
	MDELAY(10);
	DSI_clk_ULP_mode(0);
	MDELAY(10);
	DSI_clk_HS_mode(1);
	MDELAY(10);
	//* */
    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(120);
	init_lcm_registers();
    return TRUE;
}

LCM_DRIVER hx8394a_hd720_dsi_vdo_tcl_lcm_drv = 
{
    .name	         = "hx8394a_hd720_dsi_vdo_tcl",
	.set_util_funcs  = lcm_set_util_funcs,
	.get_params      = lcm_get_params,
	.init            = lcm_init,
	.suspend         = lcm_suspend,
	.resume          = lcm_resume,
	.compare_id    = lcm_compare_id,
	.esd_check = lcm_esd_check,
	.esd_recover = lcm_esd_recover,
    #if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
    #endif
    };
