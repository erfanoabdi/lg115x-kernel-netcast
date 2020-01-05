/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/


#ifndef __CTOP_REGS_H__
#define __CTOP_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0010 ctr00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	core_clk_div_sel                : 2,	//  0: 1
	peri_apb1_clk_5_off             : 1,	//     2
	peri_apb1_clk_4_off             : 1,	//     3
	peri_apb1_clk_3_off             : 1,	//     4
	peri_apb1_clk_2_off             : 1,	//     5
	peri_apb1_clk_1_off             : 1,	//     6
	peri_apb1_clk_0_off             : 1,	//     7
	peri_apb0_clk_7_off             : 1,	//     8
	peri_apb0_clk_6_off             : 1,	//     9
	peri_apb0_clk_5_off             : 1,	//    10
	peri_apb0_clk_4_off             : 1,	//    11
	peri_apb0_clk_3_off             : 1,	//    12
	peri_apb0_clk_2_off             : 1,	//    13
	peri_apb0_clk_1_off             : 1,	//    14
	peri_apb0_clk_0_off             : 1,	//    15
	peri_ahb_clk_30_off             : 1,	//    16
	peri_ahb_clk_28_off             : 1,	//    17
	peri_ahb_clk_26_off             : 1,	//    18
	peri_ahb_clk_25_off             : 1,	//    19
	peri_ahb_clk_24_off             : 1,	//    20
	peri_ahb_clk_22_off             : 1,	//    21
	peri_ahb_clk_19_off             : 1,	//    22
	peri_ahb_clk_14_off             : 1,	//    23
	peri_ahb_clk_9_off              : 1,	//    24
	peri_ahb_clk_8_off              : 1,	//    25
	peri_ahb_clk_7_off              : 1,	//    26
	peri_ahb_clk_6_off              : 1,	//    27
	peri_ahb_clk_5_off              : 1,	//    28
	peri_ahb_clk_4_off              : 1,	//    29
	peri_ahb_clk_3_off              : 1,	//    30
	peri_ahb_clk_2_off              : 1;	//    31
} CTR00;

/*-----------------------------------------------------------------------------
	0x0014 ctr01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :21,	//  0:20 reserved
	peri_ahb_clk_1_off              : 1,	//    21
	peri_ahb_clk_0_off              : 1,	//    22
	peri_apb1_clk_14_off            : 1,	//    23
	peri_apb1_clk_13_off            : 1,	//    24
	peri_apb1_clk_12_off            : 1,	//    25
	peri_apb1_clk_11_off            : 1,	//    26
	peri_apb1_clk_10_off            : 1,	//    27
	peri_apb1_clk_9_off             : 1,	//    28
	peri_apb1_clk_8_off             : 1,	//    29
	peri_apb1_clk_7_off             : 1,	//    30
	peri_apb1_clk_6_off             : 1;	//    31
} CTR01;

/*-----------------------------------------------------------------------------
	0x0018 ctr02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :12,	//  0:11 reserved
	peri_ahb_clk_29_sel             : 3,	// 12:14
	psel_l2_sel                     : 1,	//    15
	bus_clk_4_sel                   : 2,	// 16:17
	pclken_sel                      : 2,	// 18:19
	bus_clk_1_sel                   : 2,	// 20:21
	peri_ahb_clk_27_sel             : 3,	// 22:24
	peri_ahb_clk_23_off             : 1,	//    25
	peri_ahb_clk_21_sel             : 3,	// 26:28
	peri_ahb_clk_20_sel             : 3;	// 29:31
} CTR02;

/*-----------------------------------------------------------------------------
	0x001c ctr03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	uart2_sel                       : 2,	//  0: 1
	uart1_sel                       : 2,	//  2: 3
	uart0_sel                       : 2,	//  4: 5
	                                : 1,	//     6 reserved
	rx_sel_de                       : 1,	//     7
	rx_sel_led                      : 1,	//     8
	rx_sel_sp                       : 2,	//  9:10
	rx_sel_cpu0                     : 1,	//    11
	                                : 3,	// 12:14 reserved
	rst_mm1_phy_n                   : 1,	//    15
	                                : 7,	// 16:22 reserved
	rst_mm0_phy_n                   : 1,	//    23
	                                : 7,	// 24:30 reserved
	rst_frc_m_phy_n                 : 1;	//    31
} CTR03_B0;

/*-----------------------------------------------------------------------------
	0x0020 ctr04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mip_mon                         ;   	// 31: 0
} CTR04_B0;

/*-----------------------------------------------------------------------------
	0x0024 ctr05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	flip_en_0                       : 1,	//     0
	flip_en_1                       : 1,	//     1
	flip_en_2                       : 1,	//     2
	flip_en_3                       : 1,	//     3
	flip_en_4                       : 1,	//     4
	flip_en_5                       : 1,	//     5
	flip_en_6                       : 1,	//     6
	flip_en_7                       : 1,	//     7
	flip_en_8                       : 1,	//     8
	flip_en_9                       : 1,	//     9
	flip_en_10                      : 1,	//    10
	flip_en_11                      : 1,	//    11
	flip_en_12                      : 1,	//    12
	flip_en_13                      : 1,	//    13
	flip_en_14                      : 1,	//    14
	flip_en_15                      : 1,	//    15
	flip_en_16                      : 1,	//    16
	flip_en_17                      : 1,	//    17
	flip_en_18                      : 1,	//    18
	flip_en_19                      : 1,	//    19
	flip_en_20                      : 1,	//    20
	flip_en_21                      : 1,	//    21
	flip_en_22                      : 1,	//    22
	flip_en_23                      : 1,	//    23
	                                : 7,	// 24:30 reserved
	tun_i2c_direct_en               : 1;	//    31
} CTR05_B0;

/*-----------------------------------------------------------------------------
	0x0028 ctr06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri_apb0_rstn_1                : 1,	//     0
	peri_apb0_rstn_0                : 1,	//     1
	bus_rstn_8                      : 1,	//     2
	peri_ahb_rstn_27                : 1,	//     3
	peri_ahb_rstn_26                : 1,	//     4
	peri_ahb_rstn_25                : 1,	//     5
	peri_ahb_rstn_24                : 1,	//     6
	peri_ahb_rstn_23                : 1,	//     7
	peri_ahb_rstn_22                : 1,	//     8
	peri_ahb_rstn_21                : 1,	//     9
	peri_ahb_rstn_20                : 1,	//    10
	peri_ahb_rstn_19                : 1,	//    11
	peri_ahb_rstn_18                : 1,	//    12
	peri_ahb_rstn_17                : 1,	//    13
	peri_ahb_rstn_16                : 1,	//    14
	peri_ahb_rstn_15                : 1,	//    15
	peri_ahb_rstn_14                : 1,	//    16
	peri_ahb_rstn_13                : 1,	//    17
	peri_ahb_rstn_12                : 1,	//    18
	peri_ahb_rstn_11                : 1,	//    19
	peri_ahb_rstn_10                : 1,	//    20
	peri_ahb_rstn_9                 : 1,	//    21
	peri_ahb_rstn_8                 : 1,	//    22
	peri_ahb_rstn_7                 : 1,	//    23
	peri_ahb_rstn_6                 : 1,	//    24
	peri_ahb_rstn_5                 : 1,	//    25
	peri_ahb_rstn_4                 : 1,	//    26
	peri_ahb_rstn_3                 : 1,	//    27
	peri_ahb_rstn_2                 : 1,	//    28
	bus_rstn_7                      : 1,	//    29
	bus_rstn_6                      : 1,	//    30
	bus_rstn_5                      : 1;	//    31
} CTR06;

/*-----------------------------------------------------------------------------
	0x002c ctr07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 3,	//  0: 2 reserved
	bus_rstn_4                      : 1,	//     3
	bus_rstn_3                      : 1,	//     4
	bus_rstn_2                      : 1,	//     5
	bus_rstn_1                      : 1,	//     6
	bus_rstn_0                      : 1,	//     7
	peri_ahb_rstn_1                 : 1,	//     8
	peri_ahb_rstn_0                 : 1,	//     9
	peri_apb1_rstn_14               : 1,	//    10
	peri_apb1_rstn_13               : 1,	//    11
	peri_apb1_rstn_12               : 1,	//    12
	peri_apb1_rstn_11               : 1,	//    13
	peri_apb1_rstn_10               : 1,	//    14
	peri_apb1_rstn_9                : 1,	//    15
	peri_apb1_rstn_8                : 1,	//    16
	peri_apb1_rstn_7                : 1,	//    17
	peri_apb1_rstn_6                : 1,	//    18
	peri_apb1_rstn_5                : 1,	//    19
	peri_apb1_rstn_4                : 1,	//    20
	peri_apb1_rstn_3                : 1,	//    21
	peri_apb1_rstn_2                : 1,	//    22
	peri_apb1_rstn_1                : 1,	//    23
	peri_apb1_rstn_0                : 1,	//    24
	bus_rstn_9                      : 1,	//    25
	peri_apb0_rstn_7                : 1,	//    26
	peri_apb0_rstn_6                : 1,	//    27
	peri_apb0_rstn_5                : 1,	//    28
	peri_apb0_rstn_4                : 1,	//    29
	peri_apb0_rstn_3                : 1,	//    30
	peri_apb0_rstn_2                : 1;	//    31
} CTR07;

/*-----------------------------------------------------------------------------
	0x0030 ctr08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bt_usb_por_ctr                  : 1,	//     0
	usb_por_ctr                     : 1,	//     1
	peri_ahb_rstn_37                : 1,	//     2
	peri_ahb_rstn_36                : 1,	//     3
	peri_ahb_rstn_35                : 1,	//     4
	peri_ahb_rstn_34                : 1,	//     5
	peri_ahb_rstn_33                : 1,	//     6
	peri_ahb_rstn_32                : 1,	//     7
	peri_ahb_rstn_31                : 1,	//     8
	peri_ahb_rstn_30                : 1,	//     9
	                                :12,	// 10:21 reserved
	peri_ahb_rstn_29                : 1,	//    22
	peri_ahb_rstn_28                : 1,	//    23
	                                : 3,	// 24:26 reserved
	wdreset_n                       : 1,	//    27
	poreset_n                       : 1,	//    28
	cpureset_n                      : 1,	//    29
	reset_l2_n                      : 1,	//    30
	scurst_n                        : 1;	//    31
} CTR08_A0;

typedef struct {
	UINT32
	bt_usb_por_ctr                  : 1,	//     0
	usb_por_ctr                     : 1,	//     1
	peri_ahb_rstn_37                : 1,	//     2
	peri_ahb_rstn_36                : 1,	//     3
	peri_ahb_rstn_35                : 1,	//     4
	peri_ahb_rstn_34                : 1,	//     5
	peri_ahb_rstn_33                : 1,	//     6
	peri_ahb_rstn_32                : 1,	//     7
	peri_ahb_rstn_31                : 1,	//     8
	peri_ahb_rstn_30                : 1,	//     9
	                                : 1,	//    10 reserved
	sc_ext_clock_src                : 1,	//    11
	                                : 1,	//    12 reserved
	sc_ext_divide_val               : 3,	// 13:15
	                                : 5,	// 16:20 reserved
	smart_card_clock_sel            : 1,	//    21
	peri_ahb_rstn_29                : 1,	//    22
	peri_ahb_rstn_28                : 1,	//    23
	                                : 3,	// 24:26 reserved
	wdreset_n                       : 1,	//    27
	poreset_n                       : 1,	//    28
	cpureset_n                      : 1,	//    29
	reset_l2_n                      : 1,	//    30
	scurst_n                        : 1;	//    31
} CTR08_B0;

/*-----------------------------------------------------------------------------
	0x0034 ctr09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	frc_tcon_apb_sel                : 2,	//  2: 3
	led_cpuclk_off                  : 1,	//     4
	led_cpu_clk                     : 2,	//  5: 6
	vdclk_sel                       : 1,	//     7
	vdclk_off                       : 1,	//     8
	gpuclk_sel                      : 2,	//  9:10
	gpuclk_off                      : 1,	//    11
	tcon_aclk_off                   : 1,	//    12
	vp_aclk_off                     : 1,	//    13
	frc_aclk_off                    : 1,	//    14
	de_aclk_off                     : 1,	//    15
	aud_dsp1aclk_off                : 1,	//    16
	aud_dsp0aclk_off                : 1,	//    17
	aud_aclk_off                    : 1,	//    18
	vd_aclk_off                     : 1,	//    19
	ve_aclk_off                     : 1,	//    20
	te_aclk_off                     : 1,	//    21
	gfx_aclk_off                    : 1,	//    22
	gpu_aclk_off                    : 1,	//    23
	coreclock_sel                   : 2,	// 24:25
	frc_mclk_sel                    : 2,	// 26:27
	m_mclk_sel                      : 2,	// 28:29
	frcclk_sel                      : 1,	//    30
	pll_sel                         : 1;	//    31
} CTR09;

/*-----------------------------------------------------------------------------
	0x0038 ctr10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :22,	//  0:21 reserved
	vpclk_off                       : 1,	//    22
	gfxclk_off                      : 1,	//    23
	teclk_off                       : 1,	//    24
	frcclk_off                      : 1,	//    25
	de270clk_off                    : 1,	//    26
	ve270clk_off                    : 1,	//    27
	te_ah270clk_off                 : 1,	//    28
	declk_off                       : 1,	//    29
	veclk_off                       : 1,	//    30
	te_ahclk_off                    : 1;	//    31
} CTR10;

/*-----------------------------------------------------------------------------
	0x003c ctr11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	rst_frc_n                       : 1,	//     1
	rst_de_vd_n                     : 1,	//     2
	rst_de_de_n                     : 1,	//     3
	rst_gfx_n                       : 1,	//     4
	rst_ve_n                        : 1,	//     5
	rst_teah_n                      : 1,	//     6
	rst_te_te_n                     : 1,	//     7
	rst_te_ve_n                     : 1,	//     8
	rst_te_vd_n                     : 1,	//     9
	rst_vd_n                        : 1,	//    10
	rst_tcona_n                     : 1,	//    11
	rst_vpa_n                       : 1,	//    12
	rst_frca_n                      : 1,	//    13
	rst_dea_n                       : 1,	//    14
	rst_vda_n                       : 1,	//    15
	rst_gpu_n                       : 1,	//    16
	rst_vea_n                       : 1,	//    17
	rst_tea_n                       : 1,	//    18
	rst_gfxa_n                      : 1,	//    19
	rst_gpua_n                      : 1,	//    20
	rst_apb_frc_n                   : 1,	//    21
	rst_apb_gfx_n                   : 1,	//    22
	rst_apb_gpu_n                   : 1,	//    23
	rst_apb_de_n                    : 1,	//    24
	rst_apb_te_n                    : 1,	//    25
	rst_apb_ve_n                    : 1,	//    26
	rst_apb_vd_n                    : 1,	//    27
	rst_apb_n                       : 1,	//    28
	rst_axi_n                       : 1,	//    29
	rst_frc_m_n                     : 1,	//    30
	rst_mm_n                        : 1;	//    31
} CTR11;

/*-----------------------------------------------------------------------------
	0x0040 ctr12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rst_frc_m_half_n                : 1,	//     0
	rst_mm_half_n                   : 1,	//     1
	rst_axi2_n_10                   : 1,	//     2
	rst_axi2_n_9                    : 1,	//     3
	rst_axi2_n_8                    : 1,	//     4
	rst_axi2_n_7                    : 1,	//     5
	rst_axi2_n_6                    : 1,	//     6
	rst_axi2_n_5                    : 1,	//     7
	rst_axi2_n_4                    : 1,	//     8
	rst_axi2_n_3                    : 1,	//     9
	rst_axi2_n_2                    : 1,	//    10
	rst_axi2_n_1                    : 1,	//    11
	rst_axi1_n_10                   : 1,	//    12
	rst_axi1_n_9                    : 1,	//    13
	rst_axi1_n_8                    : 1,	//    14
	rst_axi1_n_7                    : 1,	//    15
	rst_axi1_n_6                    : 1,	//    16
	rst_axi1_n_5                    : 1,	//    17
	rst_axi1_n_4                    : 1,	//    18
	rst_axi1_n_3                    : 1,	//    19
	rst_axi1_n_2                    : 1,	//    20
	rst_axi1_n_1                    : 1,	//    21
	rst_axi0_n_10                   : 1,	//    22
	rst_axi0_n_9                    : 1,	//    23
	rst_axi0_n_8                    : 1,	//    24
	rst_axi0_n_7                    : 1,	//    25
	rst_axi0_n_6                    : 1,	//    26
	rst_axi0_n_5                    : 1,	//    27
	rst_axi0_n_4                    : 1,	//    28
	rst_axi0_n_3                    : 1,	//    29
	rst_axi0_n_2                    : 1,	//    30
	rst_axi0_n_1                    : 1;	//    31
} CTR12;

/*-----------------------------------------------------------------------------
	0x0044 ctr13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rst_vp_n                        : 1,	//     0
	rst_apb_tcon_n                  : 1,	//     1
	rst_apb_oif_n                   : 1,	//     2
	rst_apb_led_n                   : 1,	//     3
	rst_led_cpu_n                   : 1,	//     4
	rst_tcon_pix_n                  : 1,	//     5
	rst_frc_pix_n                   : 1,	//     6
	rst_led_pix_n                   : 1,	//     7
	rst_oif_pix_n                   : 1,	//     8
	lvds_pix_clk                    : 1,	//     9
	tcon_pix_clk_off                : 1,	//    10
	tcon_pix_clk_sel                : 1,	//    11
	frc_pix_clk_off                 : 1,	//    12
	led_pix_clk_off                 : 1,	//    13
	oif_pix_clk_sel                 : 1,	//    14
	dispclk_sel                     : 1,	//    15
	rst_dea_dp_n                    : 1,	//    16
	rst_disp_dp_n                   : 1,	//    17
	rst_de_dp_n                     : 1,	//    18
	rst_se_n                        : 1,	//    19
	rst_s_te_n                      : 1,	//    20
	rst_s_de_n                      : 1,	//    21
	                                : 1,	//    22 reserved
	rst_disp_frc_n                  : 1,	//    23
	rst_disp_de_n                   : 1,	//    24
	rst_chb_n                       : 1,	//    25
	rst_cha_n                       : 1,	//    26
	chbclk_sel                      : 2,	// 27:28
	chaclk_sel                      : 2,	// 29:30
	dco_sel                         : 1;	//    31
} CTR13_A0;

typedef struct {
	UINT32
	rst_vp_n                        : 1,	//     0
	rst_apb_tcon_n                  : 1,	//     1
	rst_apb_oif_n                   : 1,	//     2
	rst_apb_led_n                   : 1,	//     3
	rst_led_cpu_n                   : 1,	//     4
	rst_lvds_pix_n                  : 1,	//     5
	rst_frc_pix_n                   : 1,	//     6
	rst_led_pix_n                   : 1,	//     7
	rst_oif_pix_n                   : 1,	//     8
	lvds_pix_clk                    : 1,	//     9
	tcon_pix_clk_off                : 1,	//    10
	tcon_pix_clk_sel                : 1,	//    11
	frc_pix_clk_off                 : 1,	//    12
	led_pix_clk_off                 : 1,	//    13
	oif_pix_clk_sel                 : 1,	//    14
	dispclk_sel                     : 1,	//    15
	rst_dea_dp_n                    : 1,	//    16
	rst_disp_dp_n                   : 1,	//    17
	rst_de_dp_n                     : 1,	//    18
	rst_se_n                        : 1,	//    19
	rst_s_te_n                      : 1,	//    20
	rst_s_de_n                      : 1,	//    21
	                                : 1,	//    22 reserved
	rst_disp_frc_n                  : 1,	//    23
	rst_disp_de_n                   : 1,	//    24
	rst_chb_n                       : 1,	//    25
	rst_cha_n                       : 1,	//    26
	chbclk_sel                      : 2,	// 27:28
	chaclk_sel                      : 2,	// 29:30
	dco_sel                         : 1;	//    31
} CTR13_B0;

/*-----------------------------------------------------------------------------
	0x0048 ctr14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	adto_loop_val                   :16;	//  0:15
} CTR14;

/*-----------------------------------------------------------------------------
	0x004c ctr15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	adto_add_val                    :29;	//  0:28
} CTR15;

/*-----------------------------------------------------------------------------
	0x0050 ctr16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	adto_err_val                    : 6;	//  0: 5
} CTR16;

/*-----------------------------------------------------------------------------
	0x0054 ctr17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :14,	//  0:13 reserved
	audio_sel8                      : 2,	// 14:15
	audio_sel7                      : 2,	// 16:17
	audio_sel6                      : 2,	// 18:19
	audio_sel5                      : 2,	// 20:21
	audio_sel4                      : 2,	// 22:23
	audio_sel3                      : 2,	// 24:25
	audio_sel2                      : 2,	// 26:27
	audio_sel1                      : 2,	// 28:29
	audio_sel0                      : 2;	// 30:31
} CTR17_A0;

typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	audio_sel7                      : 2,	//  2: 3
	                                : 2,	//  4: 5 reserved
	audio_sel6                      : 2,	//  6: 7
	                                : 2,	//  8: 9 reserved
	audio_sel5                      : 2,	// 10:11
	                                : 2,	// 12:13 reserved
	audio_sel4                      : 2,	// 14:15
	                                : 2,	// 16:17 reserved
	audio_sel3                      : 2,	// 18:19
	                                : 2,	// 20:21 reserved
	audio_sel2                      : 2,	// 22:23
	                                : 2,	// 24:25 reserved
	audio_sel1                      : 2,	// 26:27
	                                : 2,	// 28:29 reserved
	audio_sel0                      : 2;	// 30:31
} CTR17_B0;

/*-----------------------------------------------------------------------------
	0x0058 ctr18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fs23clk_lsb_sel                 : 1,	//     0
	ext_en                          : 1,	//     1
	                                : 3,	//  2: 4 reserved
	fs23clk_sel                     : 2,	//  5: 6
	fs22clk_sel                     : 3,	//  7: 9
	fs21clk_sel                     : 3,	// 10:12
	fs20clk_sel                     : 3,	// 13:15
	fs12clk_sel                     : 3,	// 16:18
	fs11clk_sel                     : 3,	// 19:21
	fs10clk_sel                     : 4,	// 22:25
	fs04clk_sel                     : 3,	// 26:28
	fs03clk_sel                     : 3;	// 29:31
} CTR18_A0;

typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	ext_en                          : 1,	//     1
	                                : 3,	//  2: 4 reserved
	scart_bypass_dac0               : 1,	//     5
	scart_bypass_dac1               : 1,	//     6
	scart_bypass_dac2               : 1,	//     7
	                                : 7,	//  8:14 reserved
	audio_sel9                      : 1,	//    15
	                                :14,	// 16:29 reserved
	audio_sel8                      : 2;	// 30:31
} CTR18_B0;

/*-----------------------------------------------------------------------------
	0x005c ctr19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	de_mon                          ;   	// 31: 0
} CTR19;

/*-----------------------------------------------------------------------------
	0x0060 ctr20 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpu_gpu_mon                     ;   	// 31: 0
} CTR20;

/*-----------------------------------------------------------------------------
	0x0064 ctr21 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	frc_mon_0                       :16,	//  0:15
	gfx_mon                         :16;	// 16:31
} CTR21;

/*-----------------------------------------------------------------------------
	0x0068 ctr22 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	aud_mon                         ;   	// 31: 0
} CTR22;

/*-----------------------------------------------------------------------------
	0x006c ctr23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	aad_mon                         :22;	//  0:21
} CTR23_A0;

typedef struct {
	UINT32
	aad_mon                         :24,	//  0:23
	                                : 1,	//    24 reserved
	aad_mon2                        : 7;	// 25:31
} CTR23_B0;

/*-----------------------------------------------------------------------------
	0x0070 ctr24 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	gpio7_en                        : 8,	//  0: 7
	gpio6_en                        : 8,	//  8:15
	gpio5_en                        : 8,	// 16:23
	gpio4_en                        : 8;	// 24:31
} CTR24;

/*-----------------------------------------------------------------------------
	0x0074 ctr25 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	gpio11_en                       : 7,	//  1: 7
	gpio10_en                       : 8,	//  8:15
	gpio9_en                        : 8,	// 16:23
	gpio8_en                        : 8;	// 24:31
} CTR25;

/*-----------------------------------------------------------------------------
	0x0078 ctr26 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cvbsout_en                      :10,	//  0: 9
	sdhc_pull_ctr                   : 1,	//    10
	                                : 4,	// 11:14 reserved
	i2c_sel                         : 1,	//    15
	frc_mon_1                       :16;	// 16:31
} CTR26;

/*-----------------------------------------------------------------------------
	0x007c ctr27 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	ddc_ck_pull_ctr                 : 1,	//     2
	ddc_da_pull_ctr                 : 1,	//     3
	tun_pull_ctr                    : 1,	//     4
	led_pull_ctr                    : 1,	//     5
	frame_lr_pull_ctr               : 1,	//     6
	lcd_pull_ctr                    : 1,	//     7
	                                : 1,	//     8 reserved
	cam_pull_ctr                    : 1,	//     9
	eb_data_pull_ctr1               : 1,	//    10
	eb_data_pull_ctr0               : 1,	//    11
	eb_cs_pull_ctr                  : 1,	//    12
	nand_pull_ctr                   : 1,	//    13
	rmii_pull_ctr                   : 1,	//    14
	ext_intr_pull_ctr               : 1,	//    15
	pwm_pull_ctr                    : 1,	//    16
	i2c_pull_ctr                    : 1,	//    17
	uart_pull_ctr                   : 1,	//    18
	smc_pull_ctr                    : 1,	//    19
	audio_pull_ctr2                 : 1,	//    20
	audio_pull_ctr1                 : 1,	//    21
	audio_pull_ctr0                 : 1,	//    22
	                                : 1,	//    23 reserved
	spi1_pull_ctr                   : 1,	//    24
	spi0_pull_ctr                   : 1,	//    25
	tpo_data_ctr                    : 1,	//    26
	tpo_pull_ctr                    : 1,	//    27
	tpi_data_ctr                    : 1,	//    28
	tpi_pull_ctr                    : 1,	//    29
	spto_pull_ctr                   : 1,	//    30
	stpi_pull_ctr                   : 1;	//    31
} CTR27;

/*-----------------------------------------------------------------------------
	0x0080 ctr28 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	pix_clk_div                     : 2,	//  1: 2
	probe_hmrasd0                   : 1,	//     3
	probe_hmralrck                  : 1,	//     4
	probe_hmrabck                   : 1,	//     5
	linkapll_clk_div                : 2,	//  6: 7
	                                : 6,	//  8:13 reserved
	stat_acr_n                      : 2,	// 14:15
	                                : 6,	// 16:21 reserved
	sda5_ctr                        : 1,	//    22
	scl5_ctr                        : 1,	//    23
	                                : 6,	// 24:29 reserved
	sda4_ctr                        : 1,	//    30
	scl4_ctr                        : 1;	//    31
} CTR28_B0;

/*-----------------------------------------------------------------------------
	0x0084 ctr29 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 7,	//  0: 6 reserved
	cam_vccen_pol_sel               : 1,	//     7
	                                : 4,	//  8:11 reserved
	ext_intr_pol_sel                : 4,	// 12:15
	                                : 7,	// 16:22 reserved
	lower_eb_data_sel               : 1,	//    23
	                                : 7,	// 24:30 reserved
	upper_eb_data_sel               : 1;	//    31
} CTR29_B0;

/*-----------------------------------------------------------------------------
	0x0088 ctr30 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :29,	//  0:28 reserved
	fs05_sel                        : 3;	// 29:31
} CTR30_B0;

/*-----------------------------------------------------------------------------
	0x008c ctr31 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :14,	//  0:13 reserved
	fs12clk_sel                     : 2,	// 14:15
	fs11aclk_sel                    : 2,	// 16:17
	fs11clk_sel                     : 2,	// 18:19
	fs10clk_sel                     : 2,	// 20:21
	fs24clk_sel                     : 1,	//    22
	fs23clk_sel                     : 3,	// 23:25
	fs21clk_sel                     : 2,	// 26:27
	fs20clk_sel                     : 2,	// 28:29
	fs04clk_sel                     : 1,	//    30
	fs03clk_sel                     : 1;	//    31
} CTR31_B0;

/*-----------------------------------------------------------------------------
	0x0090 ctr32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	en                              :24,	//  0:23
	sw_4sd_0_135_l_0_off            : 1,	//    24
	rmlvds_en                       : 1,	//    25
	mini_flip_en                    : 1,	//    26
	mini_en                         : 1,	//    27
	sw_4sd_0_135_l_1_off            : 1,	//    28
	sw_4sd_0_135_l_2_off            : 1,	//    29
	rf                              : 1,	//    30
	pdb                             : 1;	//    31
} CTR32_A0;

typedef struct {
	UINT32
	en                              :24,	//  0:23
	sw_4sd_0_135_l_0_off            : 1,	//    24
	rmlvds_en                       : 1,	//    25
	                                : 1,	//    26
	mini_en                         : 1,	//    27
	sw_4sd_0_135_l_1_off            : 1,	//    28
	sw_4sd_0_135_l_2_off            : 1,	//    29
	rf                              : 1,	//    30
	pdb                             : 1;	//    31
} CTR32_B0;

/*-----------------------------------------------------------------------------
	0x0094 ctr33 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	enpemp_h                        : 8,	//  0: 7
	rs                              :24;	//  8:31
} CTR33;

/*-----------------------------------------------------------------------------
	0x0098 ctr34 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ovdrv                           :16,	//  0:15
	enpemp_l                        :16;	// 16:31
} CTR34;

/*-----------------------------------------------------------------------------
	0x009c ctr35 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vsb_inck_sel                    : 1,	//     0
	                                : 3,	//  1: 3 reserved
	aad_dco_lpfon                   : 2,	//  4: 5
	aad_dco_fcw                     :22,	//  6:27
	aad_dco_resetb                  : 1,	//    28
	aad_dco_rtest                   : 1,	//    29
	aad_adc_sifsel                  : 1,	//    30
	aad_adc_pdb                     : 1;	//    31
} CTR35;

/*-----------------------------------------------------------------------------
	0x00a0 ctr36 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 6,	//  0: 5 reserved
	aad_btscclk_sel                 : 1,	//     6
	aad_fs02clk_sel                 : 2,	//  7: 8
	aad_fs01clk_sel                 : 2,	//  9:10
	aad_fs00clk_sel                 : 1,	//    11
	aad_adcclk_test                 : 1,	//    12
	aad_spllclk_test                : 1,	//    13
	aad_spll_pdb                    : 1,	//    14
	aad_spll_sel                    : 1,	//    15
	aad_spll_cvs                    : 2,	// 16:17
	aad_spll_cvl                    : 2,	// 18:19
	aad_spll_ci                     : 2,	// 20:21
	aad_spll_od                     : 2,	// 22:23
	aad_spll_n                      : 6,	// 24:29
	aad_spll_m                      : 2;	// 30:31
} CTR36;

/*-----------------------------------------------------------------------------
	0x00a4 ctr37 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hp_test1                        : 2,	//  0: 1
	hp_slop_dig                     : 3,	//  2: 4
	auda_bci                        : 3,	//  5: 7
	aud_lin_drv_ch_mute             : 1,	//     8
	aud_pdb_ldrv_in                 : 1,	//     9
	auad_rec_ch_mute                : 1,	//    10
	auad_pdb_in                     : 1,	//    11
	aud_lindrv0_ch_sel              : 3,	// 12:14
	aud_lindrv1_ch_sel              : 3,	// 15:17
	auad_dc_sel                     : 1,	//    18
	auad_ch_sel                     : 3,	// 19:21
	auad_gcon                       : 4,	// 22:25
	auad_ccon                       : 3,	// 26:28
	auda_pdb                        : 3;	// 29:31
} CTR37_A0;

typedef struct {
	UINT32
	hp_test1                        : 2,	//  0: 1
	hp_slop_dig                     : 3,	//  2: 4
	auda_bci                        : 3,	//  5: 7
	aud_lin_drv_ch_mute             : 1,	//     8
	                                : 1,	//     9
	auad_rec_ch_mute                : 1,	//    10
	auad_pdb_in                     : 1,	//    11
	aud_lindrv0_ch_sel              : 3,	// 12:14
	aud_lindrv1_ch_sel              : 3,	// 15:17
	auad_dc_sel                     : 1,	//    18
	auad_ch_sel                     : 3,	// 19:21
	auad_gcon                       : 4,	// 22:25
	auad_ccon                       : 3,	// 26:28
	                                : 2;	// 29:30
} CTR37_B0;

/*-----------------------------------------------------------------------------
	0x00a8 ctr38 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ovdrv                           : 8,	//  0: 7
	hp_pdb                          : 1,	//     8
	hp_ssp_n                        : 8,	//  9:16
	hp_ssp_m                        : 2,	// 17:18
	hp_ssp_od                       : 2,	// 19:20
	hp_ssp_ms                       : 3,	// 21:23
	hp_ssp_sr                       : 4,	// 24:27
	hp_ssp_cih                      : 3,	// 28:30
	hp_ssp_cv                       : 1;	//    31
} CTR38;

/*-----------------------------------------------------------------------------
	0x00ac ctr39 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sw_4sd_90_45_r_0_off            : 1,	//     0
	sw_4sd_90_45_r_1_off            : 1,	//     1
	sw_4sd_90_45_r_2_off            : 1,	//     2
	sw_4sd_90_45_l_0_off            : 1,	//     3
	sw_4sd_90_45_l_1_off            : 1,	//     4
	sw_4sd_90_45_l_2_off            : 1,	//     5
	sw_4sd_0_135_r_0_off            : 1,	//     6
	sw_4sd_0_135_r_1_off            : 1,	//     7
	sw_4sd_0_135_r_2_off            : 1,	//     8
	sel_90_45_r                     : 1,	//     9
	sel_90_45_l                     : 1,	//    10
	sel_0_135_r                     : 1,	//    11
	sel_0_135_l                     : 1,	//    12
	mini_en135d                     : 1,	//    13
	mini_en90d                      : 1,	//    14
	mini_en45d                      : 1,	//    15
	mini_en0d                       : 1,	//    16
	                                : 1,	//    17 reserved
	aumi_pop                        : 1,	//    18
	aumi_pdb_in                     : 1,	//    19
	aumi_ccon                       : 3,	// 20:22
	aumi_cont                       : 4,	// 23:26
	aumi_cnt                        : 5;	// 27:31
} CTR39;

/*-----------------------------------------------------------------------------
	0x00b0 ctr40 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	out_sel                         : 3,	//  8:10
	sgm_zero_sel                    : 3,	// 11:13
	test1                           : 3,	// 14:16
	test0                           : 3,	// 17:19
	dif1                            : 3,	// 20:22
	dif0                            : 3,	// 23:25
	dem0                            : 3,	// 26:28
	tdi                             : 3;	// 29:31
} CTR40_A0;

typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	out_sel                         : 2,	//  8: 9
	                                : 1,	//    10 reserved
	sgm_zero_sel                    : 2,	// 11:12
	                                : 1,	//    13 reserved
	test1                           : 2,	// 14:15
	                                : 1,	//    16 reserved
	test0                           : 2,	// 17:18
	                                : 1,	//    19 reserved
	dif1                            : 2,	// 20:21
	                                : 1,	//    22 reserved
	dif0                            : 2,	// 23:24
	                                : 1,	//    25 reserved
	dem0                            : 2,	// 26:27
	                                : 1,	//    28 reserved
	tdi                             : 2;	// 29:30
} CTR40_B0;

/*-----------------------------------------------------------------------------
	0x00b4 ctr41 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :23,	//  0:22 reserved
	pwm_sel                         : 1,	//    23
	dif                             : 2,	// 24:25
	dat_hp_vol_con                  : 6;	// 26:31
} CTR41;

/*-----------------------------------------------------------------------------
	0x00b8 ctr42 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :14,	//  0:13 reserved
	testinr                         : 1,	//    14
	testinl                         : 1,	//    15
	testr                           : 1,	//    16
	testl                           : 1,	//    17
	dig_sel                         : 2,	// 18:19
	vol_gain                        : 6,	// 20:25
	bm_20                           : 1,	//    26
	pol_con                         : 2,	// 27:28
	cont                            : 3;	// 29:31
} CTR42_A0;

typedef struct {
	UINT32
	                                :14,	//  0:13 reserved
	testinr                         : 1,	//    14
	testinl                         : 1,	//    15
	testr                           : 1,	//    16
	testl                           : 1,	//    17
	dig_sel                         : 2,	// 18:19
	vol_gain                        : 6,	// 20:25
	bm_20                           : 1,	//    26
	pol_con                         : 2,	// 27:28
	cont                            : 2;	// 29:30
} CTR42_B0;

/*-----------------------------------------------------------------------------
	0x00bc ctr43 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	testin_mic                      : 1,	//    16
	test_mic                        : 1,	//    17
	dig_sel_mic                     : 2,	// 18:19
	vol_gain_mic                    : 6,	// 20:25
	bm_20_mic                       : 1,	//    26
	pol_con_mic                     : 2,	// 27:28
	cont_mic                        : 3;	// 29:31
} CTR43_A0;

typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	testin_mic                      : 1,	//    16
	test_mic                        : 1,	//    17
	dig_sel_mic                     : 2,	// 18:19
	vol_gain_mic                    : 6,	// 20:25
	bm_20_mic                       : 1,	//    26
	pol_con_mic                     : 2,	// 27:28
	cont_mic                        : 2;	// 29:30
} CTR43_B0;

/*-----------------------------------------------------------------------------
	0x00c0 ctr44 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dr3p_dtrsel                     : 3,	//  0: 2
	dr3p_od_cvdclk                  : 3,	//  3: 5
	dr3p_nsc                        : 4,	//  6: 9
	dr3p_npc                        : 6,	// 10:15
	dr3p_msex                       : 9,	// 16:24
	dr3p_m                          : 3,	// 25:27
	dr3p_lf                         : 1,	//    28
	dr3p_cih                        : 3;	// 29:31
} CTR44;

/*-----------------------------------------------------------------------------
	0x00c4 ctr45 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :21,	//  0:20 reserved
	dr3p_udex                       : 5,	// 21:25
	dr3p_ps23c                      : 1,	//    26
	dr3p_pdb                        : 1,	//    27
	dr3p_od_recclk                  : 4;	// 28:31
} CTR45;

/*-----------------------------------------------------------------------------
	0x00c8 ctr46 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dr3p_dtrsel                     : 3,	//  0: 2
	dr3p_od_cvdclk                  : 3,	//  3: 5
	dr3p_nsc                        : 4,	//  6: 9
	dr3p_npc                        : 6,	// 10:15
	dr3p_msex                       : 9,	// 16:24
	dr3p_m                          : 3,	// 25:27
	dr3p_lf                         : 1,	//    28
	dr3p_cih                        : 3;	// 29:31
} CTR46;

/*-----------------------------------------------------------------------------
	0x00cc ctr47 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :21,	//  0:20 reserved
	dr3p_udex                       : 5,	// 21:25
	dr3p_ps23c                      : 1,	//    26
	dr3p_pdb                        : 1,	//    27
	dr3p_od_recclk                  : 4;	// 28:31
} CTR47;

/*-----------------------------------------------------------------------------
	0x00d0 ctr48 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dr3p_dtrsel                     : 3,	//  0: 2
	dr3p_od_cvdclk                  : 3,	//  3: 5
	dr3p_nsc                        : 4,	//  6: 9
	dr3p_npc                        : 6,	// 10:15
	dr3p_msex                       : 9,	// 16:24
	dr3p_m                          : 3,	// 25:27
	dr3p_lf                         : 1,	//    28
	dr3p_cih                        : 3;	// 29:31
} CTR48;

/*-----------------------------------------------------------------------------
	0x00d4 ctr49 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :21,	//  0:20 reserved
	dr3p_udex                       : 5,	// 21:25
	dr3p_ps23c                      : 1,	//    26
	dr3p_pdb                        : 1,	//    27
	dr3p_od_recclk                  : 4;	// 28:31
} CTR49;

/*-----------------------------------------------------------------------------
	0x00d8 ctr50 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 4,	//  0: 3 reserved
	dpll_n                          :13,	//  4:16
	dpll_m                          : 9,	// 17:25
	dpll_mode                       : 4,	// 26:29
	dpll_en_edge                    : 1,	//    30
	dpll_mode_en                    : 1;	//    31
} CTR50;

/*-----------------------------------------------------------------------------
	0x00dc ctr51 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :18,	//  0:17 reserved
	dpll_cvs                        : 2,	// 18:19
	dpll_cvl                        : 2,	// 20:21
	dpll_ci                         : 2,	// 22:23
	dpll_pdb                        : 1,	//    24
	dpll_sel                        : 1,	//    25
	dpll_od                         : 6;	// 26:31
} CTR51;

/*-----------------------------------------------------------------------------
	0x00e0 ctr52 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 4,	//  0: 3 reserved
	dpll_n                          :13,	//  4:16
	dpll_m                          : 9,	// 17:25
	dpll_mode                       : 4,	// 26:29
	dpll_en_edge                    : 1,	//    30
	dpll_mode_en                    : 1;	//    31
} CTR52;

/*-----------------------------------------------------------------------------
	0x00e4 ctr53 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :18,	//  0:17 reserved
	dpll_cvs                        : 2,	// 18:19
	dpll_cvl                        : 2,	// 20:21
	dpll_ci                         : 2,	// 22:23
	dpll_pdb                        : 1,	//    24
	dpll_sel                        : 1,	//    25
	dpll_od                         : 6;	// 26:31
} CTR53;

/*-----------------------------------------------------------------------------
	0x00e8 ctr54 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 9,	//  0: 8 reserved
	disp_pdb                        : 1,	//     9
	disp_bypass                     : 1,	//    10
	disp_ms                         : 3,	// 11:13
	disp_sr                         : 4,	// 14:17
	disp_od                         : 3,	// 18:20
	disp_n                          : 8,	// 21:28
	disp_m                          : 3;	// 29:31
} CTR54;

/*-----------------------------------------------------------------------------
	0x00ec ctr55 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dco_fcw                         :22,	//  0:21
	dco_rtest                       : 1,	//    22
	dco_resetb                      : 1,	//    23
	dco_lpfon                       : 2;	// 24:25
} CTR55;

/*-----------------------------------------------------------------------------
	0x00f0 ctr56 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dco_rtest                       : 1,	//     0
	dco_resetb                      : 1,	//     1
	dco_lpfon                       : 2;	//  2: 3
} CTR56;

/*-----------------------------------------------------------------------------
	0x00f4 ctr57 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	testdataoutsel0                 : 1,	//     0
	testclk0                        : 1,	//     1
	txpreemphasistune0              : 1,	//     2
	txrisetune0                     : 1,	//     3
	txvreftune0                     : 4,	//  4: 7
	txfslstune0                     : 4,	//  8:11
	vregtune0                       : 1,	//    12
	txhsxvtune0                     : 2,	// 13:14
	sqrxtune0                       : 3,	// 15:17
	compdistune0                    : 3,	// 18:20
	loopbackenb0                    : 1,	//    21
	otgdisable0                     : 1,	//    22
	portreset0                      : 1,	//    23
	commononn                       : 1,	//    24
	refclksel                       : 2,	// 25:26
	refclkdiv                       : 2,	// 27:28
	testen                          : 1,	//    29
	vatestenb                       : 1,	//    30
	siddq                           : 1;	//    31
} CTR57;

/*-----------------------------------------------------------------------------
	0x00f8 ctr58 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	testdataout1_0_en               : 1,	//     1
	testdataout1_1_en               : 1,	//     2
	testdataout1_2_en               : 1,	//     3
	testdataout1_3_en               : 1,	//     4
	testdataout0_0_en               : 1,	//     5
	testdataout0_1_en               : 1,	//     6
	testdataout0_2_en               : 1,	//     7
	testdataout0_3_en               : 1,	//     8
	vregtune1                       : 1,	//     9
	txhsxvtune1                     : 2,	// 10:11
	sqrxtune1                       : 3,	// 12:14
	compdistune1                    : 3,	// 15:17
	loopbackenb1                    : 1,	//    18
	portreset1                      : 1,	//    19
	testaddr0                       : 4,	// 20:23
	testdatain0                     : 8;	// 24:31
} CTR58;

/*-----------------------------------------------------------------------------
	0x00fc ctr59 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bt_testdataout1_0_en            : 1,	//     0
	bt_testdataout1_1_en            : 1,	//     1
	bt_testdataout1_2_en            : 1,	//     2
	bt_testdataout1_3_en            : 1,	//     3
	bt_testdataout0_0_en            : 1,	//     4
	bt_testdataout0_1_en            : 1,	//     5
	bt_testdataout0_2_en            : 1,	//     6
	bt_testdataout0_3_en            : 1,	//     7
	testaddr1                       : 4,	//  8:11
	testdatain1                     : 8,	// 12:19
	testdataoutsel1                 : 1,	//    20
	testclk1                        : 1,	//    21
	txpreemphasistune1              : 1,	//    22
	txrisetune1                     : 1,	//    23
	txvreftune1                     : 4,	// 24:27
	txfslstune1                     : 4;	// 28:31
} CTR59;

/*-----------------------------------------------------------------------------
	0x0100 ctr60 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	testdataoutsel0                 : 1,	//     0
	testclk0                        : 1,	//     1
	txpreemphasistune0              : 1,	//     2
	txrisetune0                     : 1,	//     3
	txvreftune0                     : 4,	//  4: 7
	txfslstune0                     : 4,	//  8:11
	vregtune0                       : 1,	//    12
	txhsxvtune0                     : 2,	// 13:14
	sqrxtune0                       : 3,	// 15:17
	compdistune0                    : 3,	// 18:20
	loopbackenb0                    : 1,	//    21
	otgdisable0                     : 1,	//    22
	portreset0                      : 1,	//    23
	commononn                       : 1,	//    24
	refclksel                       : 2,	// 25:26
	refclkdiv                       : 2,	// 27:28
	testen                          : 1,	//    29
	vatestenb                       : 1,	//    30
	tsiddq                          : 1;	//    31
} CTR60;

/*-----------------------------------------------------------------------------
	0x0104 ctr61 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	demod_reset_sel                 : 1,	//     0
	bbmode_sel                      : 2,	//  1: 2
	uart0_sel                       : 2,	//  3: 4
	uart_rx_sel                     : 1,	//     5
	                                : 1,	//     6 reserved
	cvbs_input_mux                  : 1,	//     7
	                                : 1,	//     8 reserved
	vregtune1                       : 1,	//     9
	txhsxvtune1                     : 2,	// 10:11
	sqrxtune1                       : 3,	// 12:14
	compdistune1                    : 3,	// 15:17
	loopbackenb1                    : 1,	//    18
	portreset1                      : 1,	//    19
	testaddr0                       : 4,	// 20:23
	testdatain0                     : 8;	// 24:31
} CTR61_A0;

typedef struct {
	UINT32
	demod_reset_sel                 : 1,	//     0
	bbmode_sel                      : 2,	//  1: 2
	uar0_sel                        : 3,	//  3: 5
	                                : 1,	//     6 reserved
	cvbs_input_mux                  : 1,	//     7
	                                : 1,	//     8 reserved
	vregtune1                       : 1,	//     9
	txhsxvtune1                     : 2,	// 10:11
	sqrxtune1                       : 3,	// 12:14
	compdistune1                    : 3,	// 15:17
	loopbackenb1                    : 1,	//    18
	portreset1                      : 1,	//    19
	testaddr0                       : 4,	// 20:23
	testdatain0                     : 8;	// 24:31
} CTR61_B0;

/*-----------------------------------------------------------------------------
	0x0108 ctr62 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	jtag_sel                        : 3,	//  0: 2
	uart2_sel                       : 2,	//  3: 4
	uart1_sel                       : 1,	//     5
	                                : 2,	//  6: 7 reserved
	testaddr1                       : 4,	//  8:11
	testdatain1                     : 8,	// 12:19
	testdataoutsel1                 : 1,	//    20
	testclk1                        : 1,	//    21
	txpreemphasistune1              : 1,	//    22
	txrisetune1                     : 1,	//    23
	txvreftune1                     : 4,	// 24:27
	txfslstune1                     : 4;	// 28:31
} CTR62_A0;

typedef struct {
	UINT32
	jtag_sel                        : 3,	//  0: 2
	                                : 2,	//  3: 4
	                                : 1,	//     5
	                                : 2,	//  6: 7 reserved
	testaddr1                       : 4,	//  8:11
	testdatain1                     : 8,	// 12:19
	testdataoutsel1                 : 1,	//    20
	testclk1                        : 1,	//    21
	txpreemphasistune1              : 1,	//    22
	txrisetune1                     : 1,	//    23
	txvreftune1                     : 4,	// 24:27
	txfslstune1                     : 4;	// 28:31
} CTR62_B0;


/*-----------------------------------------------------------------------------
	0x010c ctr63 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	gpo_probe_0_en                  : 1,	//     0
	gpo_probe_1_en                  : 1,	//     1
	gpo_probe_2_en                  : 1,	//     2
	gpo_probe_3_en                  : 1,	//     3
	gpo_probe_4_en                  : 1,	//     4
	gpo_probe_5_en                  : 1,	//     5
	gpo_probe_6_en                  : 1,	//     6
	gpo_probe_7_en                  : 1,	//     7
	gpo_probe_8_en                  : 1,	//     8
	gpo_probe_9_en                  : 1,	//     9
	gpo_probe_10_en                 : 1,	//    10
	gpo_probe_11_en                 : 1,	//    11
	q_probe_0_en                    : 1,	//    12
	q_probe_1_en                    : 1,	//    13
	q_probe_2_en                    : 1,	//    14
	q_probe_3_en                    : 1,	//    15
	q_probe_4_en                    : 1,	//    16
	q_probe_5_en                    : 1,	//    17
	q_probe_6_en                    : 1,	//    18
	q_probe_7_en                    : 1,	//    19
	q_probe_8_en                    : 1,	//    20
	q_probe_9_en                    : 1,	//    21
	i_probe_0_en                    : 1,	//    22
	i_probe_1_en                    : 1,	//    23
	i_probe_2_en                    : 1,	//    24
	i_probe_3_en                    : 1,	//    25
	i_probe_4_en                    : 1,	//    26
	i_probe_5_en                    : 1,	//    27
	i_probe_6_en                    : 1,	//    28
	i_probe_7_en                    : 1,	//    29
	i_probe_8_en                    : 1,	//    30
	i_probe_9_en                    : 1;	//    31
} CTR63;


/*-----------------------------------------------------------------------------
	0x0110 usb0_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb0_ohci_0_scanmode_i_n        : 1,	//     0
	usb0_endian_ahbms_ehci_bufacc   : 1,	//     1
	usb0_endian_ahbms_ohci_bufacc   : 1,	//     2
	usb0_app_start_clk_i            : 1,	//     3
	usb0_ohci_susp_lgcy_i           : 1,	//     4
	usb0_ss_simulation_mode_i       : 1,	//     5
	usb0_ss_word_if_i               : 1,	//     6
	usb0_ss_utmi_backward_enb_i     : 1,	//     7
	usb0_ss_fladj_val_host_i        : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb0_ss_fladj_val_i             : 6,	// 16:21
	usb0_ss_resume_utmi_pls_dis_i   : 1,	//    22
	usb0_ss_autoppd_on_overcur_en_i : 1,	//    23
	usb0_ss_ena_incr16_i            : 1,	//    24
	usb0_ss_ena_incr8_i             : 1,	//    25
	usb0_ss_ena_incr4_i             : 1,	//    26
	usb0_ss_ena_incrx_align_i       : 1,	//    27
	usb0_app_prt_ovrcur_i           : 1,	//    28
	usb0_endian_ahbsl               : 1,	//    29
	usb0_endian_ahbms_ehci          : 1,	//    30
	usb0_endian_ahbms_ohci          : 1;	//    31
} USB0_CTRL;

/*-----------------------------------------------------------------------------
	0x0114 usb0_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb0_ohci_0_globalsuspend_o     : 1,	//     0
	usb0_ohci_0_drwe_o              : 1,	//     1
	usb0_ohci_0_rwe_o               : 1,	//     2
	usb0_ohci_0_rmtwkp_o            : 1,	//     3
	usb0_ohci_0_smi_o_n             : 1,	//     4
	usb0_ohci_0_sof_o_n             : 1,	//     5
	usb0_ohci_0_bufacc_o            : 1,	//     6
	usb0_ehci_prt_pwr_o             : 1,	//     7
	usb0_ehci_xfer_cnt_o            :11,	//  8:18
	                                : 1,	//    19 reserved
	usb0_ehci_xfer_prdc_o           : 1,	//    20
	usb0_ehci_bufacc_o              : 1,	//    21
	usb0_ehci_pme_status_o          : 1,	//    22
	usb0_ehci_power_state_ack_o     : 1,	//    23
	usb0_ohci_0_ccs_o               : 1;	//    24
} USB0_STATUS0;

/*-----------------------------------------------------------------------------
	0x0118 usb0_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb0_ehci_usbsts_o              : 6,	//  0: 5
	                                : 2,	//  6: 7 reserved
	usb0_ehci_lpsmc_state_o         : 4;	//  8:11
} USB0_STATUS1;

/*-----------------------------------------------------------------------------
	0x011c usb1_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb1_ohci_0_scanmode_i_n        : 1,	//     0
	usb1_endian_ahbms_ehci_bufacc   : 1,	//     1
	usb1_endian_ahbms_ohci_bufacc   : 1,	//     2
	usb1_app_start_clk_i            : 1,	//     3
	usb1_ohci_susp_lgcy_i           : 1,	//     4
	usb1_ss_simulation_mode_i       : 1,	//     5
	usb1_ss_word_if_i               : 1,	//     6
	usb1_ss_utmi_backward_enb_i     : 1,	//     7
	usb1_ss_fladj_val_host_i        : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb1_ss_fladj_val_i             : 6,	// 16:21
	usb1_ss_resume_utmi_pls_dis_i   : 1,	//    22
	usb1_ss_autoppd_on_overcur_en_i : 1,	//    23
	usb1_ss_ena_incr16_i            : 1,	//    24
	usb1_ss_ena_incr8_i             : 1,	//    25
	usb1_ss_ena_incr4_i             : 1,	//    26
	usb1_ss_ena_incrx_align_i       : 1,	//    27
	usb1_app_prt_ovrcur_i           : 1,	//    28
	usb1_endian_ahbsl               : 1,	//    29
	usb1_endian_ahbms_ehci          : 1,	//    30
	usb1_endian_ahbms_ohci          : 1;	//    31
} USB1_CTRL;

/*-----------------------------------------------------------------------------
	0x0120 usb1_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb1_ohci_0_globalsuspend_o     : 1,	//     0
	usb1_ohci_0_drwe_o              : 1,	//     1
	usb1_ohci_0_rwe_o               : 1,	//     2
	usb1_ohci_0_rmtwkp_o            : 1,	//     3
	usb1_ohci_0_smi_o_n             : 1,	//     4
	usb1_ohci_0_sof_o_n             : 1,	//     5
	usb1_ohci_0_bufacc_o            : 1,	//     6
	usb1_ehci_prt_pwr_o             : 1,	//     7
	usb1_ehci_xfer_cnt_o            :11,	//  8:18
	                                : 1,	//    19 reserved
	usb1_ehci_xfer_prdc_o           : 1,	//    20
	usb1_ehci_bufacc_o              : 1,	//    21
	usb1_ehci_pme_status_o          : 1,	//    22
	usb1_ehci_power_state_ack_o     : 1,	//    23
	usb1_ohci_0_ccs_o               : 1;	//    24
} USB1_STATUS0;

/*-----------------------------------------------------------------------------
	0x0124 usb1_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb1_ehci_usbsts_o              : 6,	//  0: 5
	                                : 2,	//  6: 7 reserved
	usb1_ehci_lpsmc_state_o         : 4;	//  8:11
} USB1_STATUS1;

/*-----------------------------------------------------------------------------
	0x0128 io_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ci_en                           : 1,	//     0
	nfc_intr_sel                    : 1,	//     1
	                                : 2,	//  2: 3 reserved
	monitor_sig_sel                 : 4,	//  4: 7
	                                : 8,	//  8:15 reserved
	ahb_port_sel                    :14;	// 16:29
} IO_CTRL;

/*-----------------------------------------------------------------------------
	0x012c sd_reg40_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sd_reg40_dt                     ;   	// 31: 0
} SD_REG40_CTRL;

/*-----------------------------------------------------------------------------
	0x0130 sd_reg48_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sd_reg48_dt                     ;   	// 31: 0
} SD_REG48_CTRL;

/*-----------------------------------------------------------------------------
	0x0134 sd_regfe_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sd_regfe_dt                     :16;	//  0:15
} SD_REGFE_CTRL;

/*-----------------------------------------------------------------------------
	0x0138 apb_time_out_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	tout_en                         : 1,	//     0
	tout_intr_clr                   : 1,	//     1
	                                :14,	//  2:15 reserved
	tout_cnt                        :16;	// 16:31
} APB_TIME_OUT_CTRL;

/*-----------------------------------------------------------------------------
	0x013c apb_time_out_source31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pselxx_tout                     ;   	// 31: 0
} APB_TIME_OUT_SOURCE31_0;

/*-----------------------------------------------------------------------------
	0x0140 apb_time_out_sourcexx_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pselxx_tout                     ;   	// 31: 0
} APB_TIME_OUT_SOURCEXX_32;

/*-----------------------------------------------------------------------------
	0x0144 version ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	version                         ;   	// 31: 0
} VERSION;

/*-----------------------------------------------------------------------------
	0x0148 stcc_ref_time_stamp_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_ref_time_stamp_high        : 1;	//     0
} STCC_REF_TIME_STAMP_32;

/*-----------------------------------------------------------------------------
	0x014c stcc_ref_time_stamp_31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_ref_time_stamp_low         ;   	// 31: 0
} STCC_REF_TIME_STAMP_31_0;

/*-----------------------------------------------------------------------------
	0x0150 stcc_real_time_stamp_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_real_time_stamp_high       : 1;	//     0
} STCC_REAL_TIME_STAMP_32;

/*-----------------------------------------------------------------------------
	0x0154 stcc_real_time_stamp_31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_real_time_stamp_low        ;   	// 31: 0
} STCC_REAL_TIME_STAMP_31_0;

/*-----------------------------------------------------------------------------
	0x0158 flush_done_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_flush_done                   : 1,	//     0
	sp_flush_done                   : 1,	//     1
	gpu_flush_done                  : 1,	//     2
	frc_flush_done                  : 1,	//     3
	tcon_flush_done                 : 1,	//     4
	de_dp_flush_done                : 1,	//     5
	de_flush_done                   : 1,	//     6
	cvd_flush_done                  : 1,	//     7
	aud_dsp1_flush_done             : 1,	//     8
	aud_dsp0_flush_done             : 1,	//     9
	gfx_flush_done                  : 1,	//    10
	vd_flush_done                   : 1,	//    11
	te_flush_done                   : 1,	//    12
	ve_flush_done                   : 1;	//    13
} FLUSH_DONE_STATUS;

/*-----------------------------------------------------------------------------
	0x015c flush_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sp_flush_en                     : 1,	//     0
	sc_flush_en                     : 1,	//     1
	gpu_flush_en                    : 1,	//     2
	frc_flush_en                    : 1,	//     3
	tcon_flush_en                   : 1,	//     4
	de_dp_flush_en                  : 1,	//     5
	de_flush_en                     : 1,	//     6
	cvd_flush_en                    : 1,	//     7
	aud_dsp1_flush_en               : 1,	//     8
	aud_dsp0_flush_en               : 1,	//     9
	gfx_flush_en                    : 1,	//    10
	vd_flush_en                     : 1,	//    11
	te_flush_en                     : 1,	//    12
	ve_flush_en                     : 1;	//    13
} FLUSH_REQ;

/*-----------------------------------------------------------------------------
	0x0160 se_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sp_statvector_sel               : 1,	//     0
	sp_runstall                     : 1,	//     1
	se_ctrl                         :30;	//  2:31
} SE_CTRL;

/*-----------------------------------------------------------------------------
	0x0164 bandwidth_limiter_platform0_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_platform0_raxi_dly_cnt       :16,	//  0:15
	bw_platform0_waxi_dly_cnt       :16;	// 16:31
} BANDWIDTH_LIMITER_PLATFORM0_DLY_CNT;

/*-----------------------------------------------------------------------------
	0x0168 bandwidth_limiter_platform1_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_platform1_raxi_dly_cnt       :16,	//  0:15
	bw_platform1_waxi_dly_cnt       :16;	// 16:31
} BANDWIDTH_LIMITER_PLATFORM1_DLY_CNT;

/*-----------------------------------------------------------------------------
	0x016c bandwidth_limiter_cpu_axi0_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_cpu_raxi0_dly_cnt            :16,	//  0:15
	bw_cpu_waxi0_dly_cnt            :16;	// 16:31
} BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT;

/*-----------------------------------------------------------------------------
	0x0170 bandwidth_limiter_cpu_axi1_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_cpu_raxi1_dly_cnt            :16,	//  0:15
	bw_cpu_waxi1_dly_cnt            :16;	// 16:31
} BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT;

/*-----------------------------------------------------------------------------
	0x0174 gpio_interrupt_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	gpioxx_intr                     :12;	//  0:11
} GPIO_INTERRUPT_STATUS;

/*-----------------------------------------------------------------------------
	0x0178 axi_user_signal_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mp0_user_id                     : 3,	//  0: 2
	                                : 5,	//  3: 7 reserved
	mp1_user_id                     : 3,	//  8:10
	                                : 5,	// 11:15 reserved
	ahb0_user_id                    : 3,	// 16:18
	                                : 5,	// 19:23 reserved
	ahb1_user_id                    : 3;	// 24:26
} AXI_USER_SIGNAL_CTRL;

/*-----------------------------------------------------------------------------
	0x017c l2_cache_drreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_drreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DRREQ_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0180 l2_cache_drhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_drhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DRHIT_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0184 l2_cache_dwreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DWREQ_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0188 l2_cache_dwtreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwtreq_evnt_cnt              ;   	// 31: 0
} L2_CACHE_DWTREQ_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x018c l2_cache_dwhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DWHIT_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0190 l2_cache_irreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_irreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_IRREQ_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0194 l2_cache_irhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_irhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_IRHIT_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x0198 l2_cache_wa_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_wa_evnt_cnt                  ;   	// 31: 0
} L2_CACHE_WA_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x019c l2_cache_co_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_co_evnt_cnt                  ;   	// 31: 0
} L2_CACHE_CO_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x01a0 l2_cache_pf_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_pf_evnt_cnt                  ;   	// 31: 0
} L2_CACHE_PF_EVENT_CNT;

/*-----------------------------------------------------------------------------
	0x01a4 l2_cache_event_monitor_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	evnt_en                         : 1,	//     0
	evnt_cnt_reset                  : 1;	//     1
} L2_CACHE_EVENT_MONITOR_CTRL;

/*-----------------------------------------------------------------------------
	0x01a8 usb_bt_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb_bt_ohci_0_scanmode_i_n      : 1,	//     0
	usb_bt_endian_ahbms_ehci_bufacc : 1,	//     1
	usb_bt_endian_ahbms_ohci_bufacc : 1,	//     2
	usb_bt_app_start_clk_i          : 1,	//     3
	usb_bt_ohci_susp_lgcy_i         : 1,	//     4
	usb_bt_ss_simulation_mode_i     : 1,	//     5
	usb_bt_ss_word_if_i             : 1,	//     6
	usb_bt_ss_utmi_backward_enb_i   : 1,	//     7
	usb_bt_ss_fladj_val_host_i      : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb_bt_ss_fladj_val_i           : 6,	// 16:21
	usb_bt_ss_resume_utmi_pls_dis_i : 1,	//    22
	usb_bt_ss_autoppd_on_overcur_en_: 1,	//    23
	usb_bt_ss_ena_incr16_i          : 1,	//    24
	usb_bt_ss_ena_incr8_i           : 1,	//    25
	usb_bt_ss_ena_incr4_i           : 1,	//    26
	usb_bt_ss_ena_incrx_align_i     : 1,	//    27
	usb_bt_app_prt_ovrcur_i         : 1,	//    28
	usb_bt_endian_ahbsl             : 1,	//    29
	usb_bt_endian_ahbms_ehci        : 1,	//    30
	usb_bt_endian_ahbms_ohci        : 1;	//    31
} USB_BT_CTRL;

/*-----------------------------------------------------------------------------
	0x01ac usb_bt_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb_bt_ohci_0_globalsuspend_o   : 1,	//     0
	usb_bt_ohci_0_drwe_o            : 1,	//     1
	usb_bt_ohci_0_rwe_o             : 1,	//     2
	usb_bt_ohci_0_rmtwkp_o          : 1,	//     3
	usb_bt_ohci_0_smi_o_n           : 1,	//     4
	usb_bt_ohci_0_sof_o_n           : 1,	//     5
	usb_bt_ohci_0_bufacc_o          : 1,	//     6
	usb_bt_ehci_prt_pwr_o           : 1,	//     7
	usb_bt_ehci_xfer_cnt_o          :11,	//  8:18
	                                : 1,	//    19 reserved
	usb_bt_ehci_xfer_prdc_o         : 1,	//    20
	usb_bt_ehci_bufacc_o            : 1,	//    21
	usb_bt_ehci_pme_status_o        : 1,	//    22
	usb_bt_ehci_power_state_ack_o   : 1,	//    23
	usb_bt_ohci_0_ccs_o             : 1;	//    24
} USB_BT_STATUS0;

/*-----------------------------------------------------------------------------
	0x01b0 usb_bt_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb_bt_ehci_usbsts_o            : 6,	//  0: 5
	                                : 2,	//  6: 7 reserved
	usb_bt_ehci_lpsmc_state_o       : 4;	//  8:11
} USB_BT_STATUS1;

/*-----------------------------------------------------------------------------
	0x01b4 usb_bt_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb_bt_ohci_1_scanmode_i_n      : 1,	//     0
	                                : 1,	//     1 reserved
	usb_bt_endian_ahbms_ohci_1_bufac: 1,	//     2
	                                :13,	//  3:15 reserved
	usb_bt_ss_fladj_val_i_p1        : 6,	// 16:21
	                                : 6,	// 22:27 reserved
	usb_bt_app_prt_ovrcur_i_p1      : 1,	//    28
	                                : 2,	// 29:30 reserved
	usb_bt_endian_ahbms_ohci_1      : 1;	//    31
} USB_BT_CTRL1;

/*-----------------------------------------------------------------------------
	0x01b8 usb_bt_status2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb_bt_ohci_1_globalsuspend_o   : 1,	//     0
	usb_bt_ohci_1_drwe_o            : 1,	//     1
	usb_bt_ohci_1_rwe_o             : 1,	//     2
	usb_bt_ohci_1_rmtwkp_o          : 1,	//     3
	usb_bt_ohci_1_smi_o_n           : 1,	//     4
	usb_bt_ohci_1_sof_o_n           : 1,	//     5
	usb_bt_ohci_1_bufacc_o          : 1,	//     6
	usb_bt_ehci_prt_pwr_o_p1        : 1,	//     7
	                                :16,	//  8:23 reserved
	usb_bt_ohci_1_ccs_o             : 1;	//    24
} USB_BT_STATUS2;

/*-----------------------------------------------------------------------------
	0x01bc ctr64 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dac0_rate_cont_mute             : 9,	//  0: 8
	dac0_rate_cont                  : 9,	//  9:17
	dac0_vol_con                    :14;	// 18:31
} CTR64_B0;

/*-----------------------------------------------------------------------------
	0x01c0 ctr65 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dac0_pop_con_rate               :14,	//  0:13
	                                : 9,	// 14:22 reserved
	dac0_pop_dc_on_control          : 1,	//    23
	                                : 7,	// 24:30 reserved
	dac0_mute_ena                   : 1;	//    31
} CTR65_B0;

/*-----------------------------------------------------------------------------
	0x01c4 ctr66 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dac1_rate_cont_mute             : 9,	//  0: 8
	dac1_rate_cont                  : 9,	//  9:17
	dac1_vol_con                    :14;	// 18:31
} CTR66_B0;

/*-----------------------------------------------------------------------------
	0x01c8 ctr67 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	dac1_pop_con_rate               :14,	//  0:13
	                                : 9,	// 14:22 reserved
	dac1_pop_dc_on_control          : 1,	//    23
	                                : 7,	// 24:30 reserved
	dac1_mute_ena                   : 1;	//    31
} CTR67_B0;

/*-----------------------------------------------------------------------------
	0x01cc ctr68 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 6,	//  0: 5 reserved
	hpdrv_pwm_sel                   : 2,	//  6: 7
	                                : 2,	//  8: 9 reserved
	dac_pop_invert                  : 1,	//    10
	                                :19,	// 11:29 reserved
	dac1_dc_setup_byps              : 1,	//    30
	dac0_dc_setup_byps              : 1;	//    31
} CTR68_B0;

/*-----------------------------------------------------------------------------
	0x01d0 ctr69 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 5,	//  0: 4 reserved
	aud_pdb_ldrv_in                 : 1,	//     5
	auda_pdb_dse                    : 2,	//  6: 7
	                                : 6,	//  8:13 reserved
	auda_pdb                        : 2,	// 14:15
	                                : 7,	// 16:22 reserved
	hpdrv_inverter_sel              : 1;	//    23
} CTR69_B0;

/*-----------------------------------------------------------------------------
	0x01d4 ctr70 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hp_rate_cont_mute               : 9,	//  0: 8
	hp_rate_cont                    : 9,	//  9:17
	hp_vol_con                      :14;	// 18:31
} CTR70_B0;

/*-----------------------------------------------------------------------------
	0x01d8 ctr71 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hp_pop_con_rate                 :14,	//  0:13
	                                : 9,	// 14:22 reserved
	hp_pop_dc_on_control            : 1,	//    23
	                                : 7,	// 24:30 reserved
	hp_mute_ena                     : 1;	//    31
} CTR71_B0;

/*-----------------------------------------------------------------------------
	0x01dc ctr72 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ladc_vol_con                    :14,	//  0:13
	                                : 9,	// 14:22 reserved
	twos_com                        : 1,	//    23
	                                : 6,	// 24:29 reserved
	pol_con                         : 2;	// 30:31
} CTR72_B0;

/*-----------------------------------------------------------------------------
	0x01e0 ctr73 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ladc_mute_ena                   : 1,	//     0
	                                : 6,	//  1: 6 reserved
	ladc_rate_cont_mute             : 9,	//  7:15
	                                : 7,	// 16:22 reserved
	ladc_rate_cont                  : 9;	// 23:31
} CTR73_B0;

/*-----------------------------------------------------------------------------
	0x01e4 ctr74 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vol_con_mic                     :14,	//  0:13
	                                : 9,	// 14:22 reserved
	twos_com_mic                    : 1,	//    23
	                                : 6,	// 24:29 reserved
	pol_con_mic                     : 2;	// 30:31
} CTR74_B0;

/*-----------------------------------------------------------------------------
	0x01e8 ctr75 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mute_ena_mic                    : 1,	//     0
	                                : 6,	//  1: 6 reserved
	rate_cont_mute_mic              : 9,	//  7:15
	                                : 7,	// 16:22 reserved
	rate_cont_mic                   : 9;	// 23:31
} CTR75_B0;

typedef struct {
	UINT32                           	resrvd[4]                       ;	// 0x0000 : ''
	CTR00                           	ctr00                           ;	// 0x0010 : ''
	CTR01                           	ctr01                           ;	// 0x0014 : ''
	CTR02                           	ctr02                           ;	// 0x0018 : ''
	UINT32                          	ctr03                           ;	// 0x001c : ''
	UINT32                          	ctr04                           ;	// 0x0020 : ''
	UINT32                          	ctr05                           ;	// 0x0024 : ''
	CTR06                           	ctr06                           ;	// 0x0028 : ''
	CTR07                           	ctr07                           ;	// 0x002c : ''
	CTR08_A0                           	ctr08                           ;	// 0x0030 : ''
	CTR09                           	ctr09                           ;	// 0x0034 : ''
	CTR10                           	ctr10                           ;	// 0x0038 : ''
	CTR11                           	ctr11                           ;	// 0x003c : ''
	CTR12                           	ctr12                           ;	// 0x0040 : ''
	CTR13_A0                           	ctr13                           ;	// 0x0044 : ''
	CTR14                           	ctr14                           ;	// 0x0048 : ''
	CTR15                           	ctr15                           ;	// 0x004c : ''
	CTR16                           	ctr16                           ;	// 0x0050 : ''
	CTR17_A0                           	ctr17                           ;	// 0x0054 : ''
	CTR18_A0                           	ctr18                           ;	// 0x0058 : ''
	CTR19                           	ctr19                           ;	// 0x005c : ''
	CTR20                           	ctr20                           ;	// 0x0060 : ''
	CTR21                           	ctr21                           ;	// 0x0064 : ''
	CTR22                           	ctr22                           ;	// 0x0068 : ''
	CTR23_A0                           	ctr23                           ;	// 0x006c : ''
	CTR24                           	ctr24                           ;	// 0x0070 : ''
	CTR25                           	ctr25                           ;	// 0x0074 : ''
	CTR26                           	ctr26                           ;	// 0x0078 : ''
	CTR27                           	ctr27                           ;	// 0x007c : ''
	UINT32                          	ctr28                           ;	// 0x0080 : ''
	UINT32                          	ctr29                           ;	// 0x0084 : ''
	UINT32                          	ctr30                           ;	// 0x0088 : ''
	UINT32                          	ctr31                           ;	// 0x008c : ''
	CTR32_A0                           	ctr32                           ;	// 0x0090 : ''
	CTR33                           	ctr33                           ;	// 0x0094 : ''
	CTR34                           	ctr34                           ;	// 0x0098 : ''
	CTR35                           	ctr35                           ;	// 0x009c : ''
	CTR36                           	ctr36                           ;	// 0x00a0 : ''
	CTR37_A0                           	ctr37                           ;	// 0x00a4 : ''
	CTR38                           	ctr38                           ;	// 0x00a8 : ''
	CTR39                           	ctr39                           ;	// 0x00ac : ''
	CTR40_A0                           	ctr40                           ;	// 0x00b0 : ''
	CTR41                           	ctr41                           ;	// 0x00b4 : ''
	CTR42_A0                           	ctr42                           ;	// 0x00b8 : ''
	CTR43_A0                           	ctr43                           ;	// 0x00bc : ''
	CTR44                           	ctr44                           ;	// 0x00c0 : ''
	CTR45                           	ctr45                           ;	// 0x00c4 : ''
	CTR46                           	ctr46                           ;	// 0x00c8 : ''
	CTR47                           	ctr47                           ;	// 0x00cc : ''
	CTR48                              	ctr48                           ;	// 0x00d0 : ''
	CTR49                           	ctr49                           ;	// 0x00d4 : ''
	CTR50                           	ctr50                           ;	// 0x00d8 : ''
	CTR51                           	ctr51                           ;	// 0x00dc : ''
	CTR52                           	ctr52                           ;	// 0x00e0 : ''
	CTR53                           	ctr53                           ;	// 0x00e4 : ''
	CTR54                           	ctr54                           ;	// 0x00e8 : ''
	CTR55                           	ctr55                           ;	// 0x00ec : ''
	CTR56                           	ctr56                           ;	// 0x00f0 : ''
	CTR57                           	ctr57                           ;	// 0x00f4 : ''
	CTR58                           	ctr58                           ;	// 0x00f8 : ''
	CTR59                           	ctr59                           ;	// 0x00fc : ''
	CTR60                           	ctr60                           ;	// 0x0100 : ''
	CTR61_A0                           	ctr61                           ;	// 0x0104 : ''
	CTR62_A0                           	ctr62                           ;	// 0x0108 : ''
	CTR63                           	ctr63                           ;	// 0x010c : ''
	USB0_CTRL                       	usb0_ctrl                       ;	// 0x0110 : ''
	USB0_STATUS0                    	usb0_status0                    ;	// 0x0114 : ''
	USB0_STATUS1                    	usb0_status1                    ;	// 0x0118 : ''
	USB1_CTRL                       	usb1_ctrl                       ;	// 0x011c : ''
	USB1_STATUS0                    	usb1_status0                    ;	// 0x0120 : ''
	USB1_STATUS1                    	usb1_status1                    ;	// 0x0124 : ''
	IO_CTRL                         	io_ctrl                         ;	// 0x0128 : ''
	SD_REG40_CTRL                   	sd_reg40_ctrl                   ;	// 0x012c : ''
	SD_REG48_CTRL                   	sd_reg48_ctrl                   ;	// 0x0130 : ''
	SD_REGFE_CTRL                   	sd_regfe_ctrl                   ;	// 0x0134 : ''
	APB_TIME_OUT_CTRL               	apb_time_out_ctrl               ;	// 0x0138 : ''
	APB_TIME_OUT_SOURCE31_0         	apb_time_out_source31_0         ;	// 0x013c : ''
	APB_TIME_OUT_SOURCEXX_32        	apb_time_out_sourcexx_32        ;	// 0x0140 : ''
	VERSION                         	version                         ;	// 0x0144 : ''
	STCC_REF_TIME_STAMP_32          	stcc_ref_time_stamp_32          ;	// 0x0148 : ''
	STCC_REF_TIME_STAMP_31_0        	stcc_ref_time_stamp_31_0        ;	// 0x014c : ''
	STCC_REAL_TIME_STAMP_32         	stcc_real_time_stamp_32         ;	// 0x0150 : ''
	STCC_REAL_TIME_STAMP_31_0       	stcc_real_time_stamp_31_0       ;	// 0x0154 : ''
	FLUSH_DONE_STATUS               	flush_done_status               ;	// 0x0158 : ''
	FLUSH_REQ                       	flush_req                       ;	// 0x015c : ''
	SE_CTRL                         	se_ctrl                         ;	// 0x0160 : ''
	BANDWIDTH_LIMITER_PLATFORM0_DLY_CNT	bandwidth_limiter_platform0_dly_cnt;	// 0x0164 : ''
	BANDWIDTH_LIMITER_PLATFORM1_DLY_CNT	bandwidth_limiter_platform1_dly_cnt;	// 0x0168 : ''
	BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT	bandwidth_limiter_cpu_axi0_dly_cnt;	// 0x016c : ''
	BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT	bandwidth_limiter_cpu_axi1_dly_cnt;	// 0x0170 : ''
	GPIO_INTERRUPT_STATUS           	gpio_interrupt_status           ;	// 0x0174 : ''
	AXI_USER_SIGNAL_CTRL            	axi_user_signal_ctrl            ;	// 0x0178 : ''
	L2_CACHE_DRREQ_EVENT_CNT        	l2_cache_drreq_event_cnt        ;	// 0x017c : ''
	L2_CACHE_DRHIT_EVENT_CNT        	l2_cache_drhit_event_cnt        ;	// 0x0180 : ''
	L2_CACHE_DWREQ_EVENT_CNT        	l2_cache_dwreq_event_cnt        ;	// 0x0184 : ''
	L2_CACHE_DWTREQ_EVENT_CNT       	l2_cache_dwtreq_event_cnt       ;	// 0x0188 : ''
	L2_CACHE_DWHIT_EVENT_CNT        	l2_cache_dwhit_event_cnt        ;	// 0x018c : ''
	L2_CACHE_IRREQ_EVENT_CNT        	l2_cache_irreq_event_cnt        ;	// 0x0190 : ''
	L2_CACHE_IRHIT_EVENT_CNT        	l2_cache_irhit_event_cnt        ;	// 0x0194 : ''
	L2_CACHE_WA_EVENT_CNT           	l2_cache_wa_event_cnt           ;	// 0x0198 : ''
	L2_CACHE_CO_EVENT_CNT           	l2_cache_co_event_cnt           ;	// 0x019c : ''
	L2_CACHE_PF_EVENT_CNT           	l2_cache_pf_event_cnt           ;	// 0x01a0 : ''
	L2_CACHE_EVENT_MONITOR_CTRL     	l2_cache_event_monitor_ctrl     ;	// 0x01a4 : ''
} CTOP_CTRL_REG_A0_T;

typedef struct {
	UINT32                          	                 __rsvd_00[   4];	// 0x0000 ~ 0x000c
	CTR00                           	ctr00                           ;	// 0x0010 : ''
	CTR01                           	ctr01                           ;	// 0x0014 : ''
	CTR02                           	ctr02                           ;	// 0x0018 : ''
	CTR03_B0                           	ctr03                           ;	// 0x001c : ''
	CTR04_B0                           	ctr04                           ;	// 0x0020 : ''
	CTR05_B0                           	ctr05                           ;	// 0x0024 : ''
	CTR06                           	ctr06                           ;	// 0x0028 : ''
	CTR07                           	ctr07                           ;	// 0x002c : ''
	CTR08_B0                           	ctr08                           ;	// 0x0030 : ''
	CTR09                           	ctr09                           ;	// 0x0034 : ''
	CTR10                           	ctr10                           ;	// 0x0038 : ''
	CTR11                           	ctr11                           ;	// 0x003c : ''
	CTR12                           	ctr12                           ;	// 0x0040 : ''
	CTR13_B0                           	ctr13                           ;	// 0x0044 : ''
	CTR14                           	ctr14                           ;	// 0x0048 : ''
	CTR15                           	ctr15                           ;	// 0x004c : ''
	CTR16                           	ctr16                           ;	// 0x0050 : ''
	CTR17_B0                           	ctr17                           ;	// 0x0054 : ''
	CTR18_B0                           	ctr18                           ;	// 0x0058 : ''
	CTR19                           	ctr19                           ;	// 0x005c : ''
	CTR20                           	ctr20                           ;	// 0x0060 : ''
	CTR21                           	ctr21                           ;	// 0x0064 : ''
	CTR22                           	ctr22                           ;	// 0x0068 : ''
	CTR23_B0                           	ctr23                           ;	// 0x006c : ''
	CTR24                           	ctr24                           ;	// 0x0070 : ''
	CTR25                           	ctr25                           ;	// 0x0074 : ''
	CTR26                           	ctr26                           ;	// 0x0078 : ''
	CTR27                           	ctr27                           ;	// 0x007c : ''
	CTR28_B0                           	ctr28                           ;	// 0x0080 : ''
	CTR29_B0                           	ctr29                           ;	// 0x0084 : ''
	CTR30_B0                           	ctr30                           ;	// 0x0088 : ''
	CTR31_B0                           	ctr31                           ;	// 0x008c : ''
	CTR32_B0                           	ctr32                           ;	// 0x0090 : ''
	CTR33                           	ctr33                           ;	// 0x0094 : ''
	CTR34                           	ctr34                           ;	// 0x0098 : ''
	CTR35                           	ctr35                           ;	// 0x009c : ''
	CTR36                           	ctr36                           ;	// 0x00a0 : ''
	CTR37_B0                           	ctr37                           ;	// 0x00a4 : ''
	CTR38                           	ctr38                           ;	// 0x00a8 : ''
	CTR39                           	ctr39                           ;	// 0x00ac : ''
	CTR40_B0                           	ctr40                           ;	// 0x00b0 : ''
	CTR41                           	ctr41                           ;	// 0x00b4 : ''
	CTR42_B0                           	ctr42                           ;	// 0x00b8 : ''
	CTR43_B0                           	ctr43                           ;	// 0x00bc : ''
	CTR44                           	ctr44                           ;	// 0x00c0 : ''
	CTR45                           	ctr45                           ;	// 0x00c4 : ''
	CTR46                           	ctr46                           ;	// 0x00c8 : ''
	CTR47                           	ctr47                           ;	// 0x00cc : ''
	CTR48                           	ctr48                           ;	// 0x00d0 : ''
	CTR49                           	ctr49                           ;	// 0x00d4 : ''
	CTR50                           	ctr50                           ;	// 0x00d8 : ''
	CTR51                           	ctr51                           ;	// 0x00dc : ''
	CTR52                           	ctr52                           ;	// 0x00e0 : ''
	CTR53                           	ctr53                           ;	// 0x00e4 : ''
	CTR54                           	ctr54                           ;	// 0x00e8 : ''
	CTR55                           	ctr55                           ;	// 0x00ec : ''
	CTR56                           	ctr56                           ;	// 0x00f0 : ''
	CTR57                           	ctr57                           ;	// 0x00f4 : ''
	CTR58                           	ctr58                           ;	// 0x00f8 : ''
	CTR59                           	ctr59                           ;	// 0x00fc : ''
	CTR60                           	ctr60                           ;	// 0x0100 : ''
	CTR61_B0                           	ctr61                           ;	// 0x0104 : ''
	CTR62_B0                           	ctr62                           ;	// 0x0108 : ''
	CTR63                           	ctr63                           ;	// 0x010c : ''
	USB0_CTRL                       	usb0_ctrl                       ;	// 0x0110 : ''
	USB0_STATUS0                    	usb0_status0                    ;	// 0x0114 : ''
	USB0_STATUS1                    	usb0_status1                    ;	// 0x0118 : ''
	USB1_CTRL                       	usb1_ctrl                       ;	// 0x011c : ''
	USB1_STATUS0                    	usb1_status0                    ;	// 0x0120 : ''
	USB1_STATUS1                    	usb1_status1                    ;	// 0x0124 : ''
	IO_CTRL                         	io_ctrl                         ;	// 0x0128 : ''
	SD_REG40_CTRL                   	sd_reg40_ctrl                   ;	// 0x012c : ''
	SD_REG48_CTRL                   	sd_reg48_ctrl                   ;	// 0x0130 : ''
	SD_REGFE_CTRL                   	sd_regfe_ctrl                   ;	// 0x0134 : ''
	APB_TIME_OUT_CTRL               	apb_time_out_ctrl               ;	// 0x0138 : ''
	APB_TIME_OUT_SOURCE31_0         	apb_time_out_source31_0         ;	// 0x013c : ''
	APB_TIME_OUT_SOURCEXX_32        	apb_time_out_sourcexx_32        ;	// 0x0140 : ''
	VERSION                         	version                         ;	// 0x0144 : ''
	STCC_REF_TIME_STAMP_32          	stcc_ref_time_stamp_32          ;	// 0x0148 : ''
	STCC_REF_TIME_STAMP_31_0        	stcc_ref_time_stamp_31_0        ;	// 0x014c : ''
	STCC_REAL_TIME_STAMP_32         	stcc_real_time_stamp_32         ;	// 0x0150 : ''
	STCC_REAL_TIME_STAMP_31_0       	stcc_real_time_stamp_31_0       ;	// 0x0154 : ''
	FLUSH_DONE_STATUS               	flush_done_status               ;	// 0x0158 : ''
	FLUSH_REQ                       	flush_req                       ;	// 0x015c : ''
	SE_CTRL                         	se_ctrl                         ;	// 0x0160 : ''
	BANDWIDTH_LIMITER_PLATFORM0_DLY_CNT	bandwidth_limiter_platform0_dly_cnt;	// 0x0164 : ''
	BANDWIDTH_LIMITER_PLATFORM1_DLY_CNT	bandwidth_limiter_platform1_dly_cnt;	// 0x0168 : ''
	BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT	bandwidth_limiter_cpu_axi0_dly_cnt;	// 0x016c : ''
	BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT	bandwidth_limiter_cpu_axi1_dly_cnt;	// 0x0170 : ''
	GPIO_INTERRUPT_STATUS           	gpio_interrupt_status           ;	// 0x0174 : ''
	AXI_USER_SIGNAL_CTRL            	axi_user_signal_ctrl            ;	// 0x0178 : ''
	L2_CACHE_DRREQ_EVENT_CNT        	l2_cache_drreq_event_cnt        ;	// 0x017c : ''
	L2_CACHE_DRHIT_EVENT_CNT        	l2_cache_drhit_event_cnt        ;	// 0x0180 : ''
	L2_CACHE_DWREQ_EVENT_CNT        	l2_cache_dwreq_event_cnt        ;	// 0x0184 : ''
	L2_CACHE_DWTREQ_EVENT_CNT       	l2_cache_dwtreq_event_cnt       ;	// 0x0188 : ''
	L2_CACHE_DWHIT_EVENT_CNT        	l2_cache_dwhit_event_cnt        ;	// 0x018c : ''
	L2_CACHE_IRREQ_EVENT_CNT        	l2_cache_irreq_event_cnt        ;	// 0x0190 : ''
	L2_CACHE_IRHIT_EVENT_CNT        	l2_cache_irhit_event_cnt        ;	// 0x0194 : ''
	L2_CACHE_WA_EVENT_CNT           	l2_cache_wa_event_cnt           ;	// 0x0198 : ''
	L2_CACHE_CO_EVENT_CNT           	l2_cache_co_event_cnt           ;	// 0x019c : ''
	L2_CACHE_PF_EVENT_CNT           	l2_cache_pf_event_cnt           ;	// 0x01a0 : ''
	L2_CACHE_EVENT_MONITOR_CTRL     	l2_cache_event_monitor_ctrl     ;	// 0x01a4 : ''
	USB_BT_CTRL                     	usb_bt_ctrl                     ;	// 0x01a8 : ''
	USB_BT_STATUS0                  	usb_bt_status0                  ;	// 0x01ac : ''
	USB_BT_STATUS1                  	usb_bt_status1                  ;	// 0x01b0 : ''
	USB_BT_CTRL1                    	usb_bt_ctrl1                    ;	// 0x01b4 : ''
	USB_BT_STATUS2                  	usb_bt_status2                  ;	// 0x01b8 : ''
	CTR64_B0                           	ctr64                           ;	// 0x01bc : ''
	CTR65_B0                           	ctr65                           ;	// 0x01c0 : ''
	CTR66_B0                           	ctr66                           ;	// 0x01c4 : ''
	CTR67_B0                           	ctr67                           ;	// 0x01c8 : ''
	CTR68_B0                           	ctr68                           ;	// 0x01cc : ''
	CTR69_B0                           	ctr69                           ;	// 0x01d0 : ''
	CTR70_B0                           	ctr70                           ;	// 0x01d4 : ''
	CTR71_B0                           	ctr71                           ;	// 0x01d8 : ''
	CTR72_B0                           	ctr72                           ;	// 0x01dc : ''
	CTR73_B0                           	ctr73                           ;	// 0x01e0 : ''
	CTR74_B0                           	ctr74                           ;	// 0x01e4 : ''
	CTR75_B0                           	ctr75                           ;	// 0x01e8 : ''
} CTOP_CTRL_REG_B0_T;



typedef struct
{
	union {
		UINT32				*addr;
		CTOP_CTRL_REG_A0_T	*a0;
		CTOP_CTRL_REG_B0_T	*b0;
	} shadow;

	union {
		volatile UINT32				*addr;
		volatile CTOP_CTRL_REG_A0_T	*a0;
		volatile CTOP_CTRL_REG_B0_T *b0;
	} phys;
} CTOP_CTRL_T;


/*
 * @{
 * Naming for register pointer.
 * gpRealRegCTOP_CTRL : real register of CTOP_CTRL.
 * gpRegCTOP_CTRL     : shadow register.
 *
 * @def CTOP_CTRL_RdFL: Read  FLushing : Shadow <- Real.
 * @def CTOP_CTRL_WrFL: Write FLushing : Shadow -> Real.
 * @def CTOP_CTRL_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def CTOP_CTRL_Wr  : Write whole register(UINT32) from Shadow register.
 * @def CTOP_CTRL_Rd01 ~ CTOP_CTRL_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def CTOP_CTRL_Wr01 ~ CTOP_CTRL_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define CTOP_CTRL_CHIP_RdFL(_shadow,_phys,_r)		((_shadow->_r)=(_phys->_r))
#define CTOP_CTRL_CHIP_WrFL(_shadow,_phys,_r)		((_phys->_r)=(_shadow->_r))

#define CTOP_CTRL_CHIP_Rd(_shadow, _r)				*((UINT32*)(&(_shadow->_r)))
#define CTOP_CTRL_CHIP_Wr(_shadow, _r,_v)			((CTOP_CTRL_CHIP_Rd(_shadow,_r))=((UINT32)(_v)))

#define CTOP_CTRL_CHIP_Rd01(_shadow,_r,_f01,_v01)								\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd02(_shadow,_r,_f01,_v01,_f02,_v02)						\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd03(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03)			\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd04(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd05(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05)													\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd06(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd07(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd08(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd09(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd10(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd11(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd12(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
									(_v12) = (_shadow->_r._f12);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd13(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
									(_v12) = (_shadow->_r._f12);				\
									(_v13) = (_shadow->_r._f13);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd14(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
									(_v12) = (_shadow->_r._f12);				\
									(_v13) = (_shadow->_r._f13);				\
									(_v14) = (_shadow->_r._f14);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd15(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
									(_v12) = (_shadow->_r._f12);				\
									(_v13) = (_shadow->_r._f13);				\
									(_v14) = (_shadow->_r._f14);				\
									(_v15) = (_shadow->_r._f15);				\
								} while(0)

#define CTOP_CTRL_CHIP_Rd16(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (_shadow->_r._f01);				\
									(_v02) = (_shadow->_r._f02);				\
									(_v03) = (_shadow->_r._f03);				\
									(_v04) = (_shadow->_r._f04);				\
									(_v05) = (_shadow->_r._f05);				\
									(_v06) = (_shadow->_r._f06);				\
									(_v07) = (_shadow->_r._f07);				\
									(_v08) = (_shadow->_r._f08);				\
									(_v09) = (_shadow->_r._f09);				\
									(_v10) = (_shadow->_r._f10);				\
									(_v11) = (_shadow->_r._f11);				\
									(_v12) = (_shadow->_r._f12);				\
									(_v13) = (_shadow->_r._f13);				\
									(_v14) = (_shadow->_r._f14);				\
									(_v15) = (_shadow->_r._f15);				\
									(_v16) = (_shadow->_r._f16);				\
								} while(0)


#define CTOP_CTRL_CHIP_Wr01(_shadow,_r,_f01,_v01)								\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr02(_shadow,_r,_f01,_v01,_f02,_v02)						\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr03(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03)			\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr04(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr05(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05)													\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr06(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr07(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr08(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr09(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr10(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr11(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr12(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
									(_shadow->_r._f12) = (_v12);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr13(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
									(_shadow->_r._f12) = (_v12);				\
									(_shadow->_r._f13) = (_v13);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr14(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
									(_shadow->_r._f12) = (_v12);				\
									(_shadow->_r._f13) = (_v13);				\
									(_shadow->_r._f14) = (_v14);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr15(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
									(_shadow->_r._f12) = (_v12);				\
									(_shadow->_r._f13) = (_v13);				\
									(_shadow->_r._f14) = (_v14);				\
									(_shadow->_r._f15) = (_v15);				\
								} while(0)

#define CTOP_CTRL_CHIP_Wr16(_shadow,_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,	\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_shadow->_r._f01) = (_v01);				\
									(_shadow->_r._f02) = (_v02);				\
									(_shadow->_r._f03) = (_v03);				\
									(_shadow->_r._f04) = (_v04);				\
									(_shadow->_r._f05) = (_v05);				\
									(_shadow->_r._f06) = (_v06);				\
									(_shadow->_r._f07) = (_v07);				\
									(_shadow->_r._f08) = (_v08);				\
									(_shadow->_r._f09) = (_v09);				\
									(_shadow->_r._f10) = (_v10);				\
									(_shadow->_r._f11) = (_v11);				\
									(_shadow->_r._f12) = (_v12);				\
									(_shadow->_r._f13) = (_v13);				\
									(_shadow->_r._f14) = (_v14);				\
									(_shadow->_r._f15) = (_v15);				\
									(_shadow->_r._f16) = (_v16);				\
								} while(0)




#define CTOP_SHADOW_A0			(gCTOP_CTRL.shadow.a0)
#define CTOP_SHADOW_B0			(gCTOP_CTRL.shadow.b0)

#define CTOP_REAL_A0			(gCTOP_CTRL.phys.a0)
#define CTOP_REAL_B0			(gCTOP_CTRL.phys.b0)


/*
L8 A0
*/
#define CTOP_CTRL_A0_RdFL(_r)													\
			CTOP_CTRL_CHIP_RdFL(CTOP_SHADOW_A0, CTOP_REAL_A0, _r)

#define CTOP_CTRL_A0_WrFL(_r)													\
			CTOP_CTRL_CHIP_WrFL(CTOP_SHADOW_A0, CTOP_REAL_A0, _r)

#define CTOP_CTRL_A0_Rd(_r)														\
			CTOP_CTRL_CHIP_Rd(CTOP_SHADOW_A0,_r)

#define CTOP_CTRL_A0_Wr(_r,_v)													\
			CTOP_CTRL_CHIP_Wr(CTOP_SHADOW_A0, _r,_v)


#define CTOP_CTRL_A0_Rd01(_r,_f01,_v01)											\
			CTOP_CTRL_CHIP_Rd01(CTOP_SHADOW_A0,_r,_f01,_v01)

#define CTOP_CTRL_A0_Rd02(_r,_f01,_v01,_f02,_v02) 								\
			CTOP_CTRL_CHIP_Rd02(CTOP_SHADOW_A0, _r,_f01,_v01,_f02,_v02)

#define CTOP_CTRL_A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) 					\
			CTOP_CTRL_CHIP_Rd03(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03)

#define CTOP_CTRL_A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04) 			\
			CTOP_CTRL_CHIP_Rd04(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04)

#define CTOP_CTRL_A0_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05)	\
			CTOP_CTRL_CHIP_Rd05(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05)

#define CTOP_CTRL_A0_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05,	\
							_f06,_v06)											\
			CTOP_CTRL_CHIP_Rd06(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06)

#define CTOP_CTRL_A0_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07)						\
			CTOP_CTRL_CHIP_Rd07(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07)

#define CTOP_CTRL_A0_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)			\
			CTOP_CTRL_CHIP_Rd08(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08)

#define CTOP_CTRL_A0_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09)											\
			CTOP_CTRL_CHIP_Rd09(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09)

#define CTOP_CTRL_A0_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10)								\
			CTOP_CTRL_CHIP_Rd10(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10)

#define CTOP_CTRL_A0_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11)						\
			CTOP_CTRL_CHIP_Rd11(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11)

#define CTOP_CTRL_A0_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)			\
			CTOP_CTRL_CHIP_Rd12(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12)

#define CTOP_CTRL_A0_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13)											\
			CTOP_CTRL_CHIP_Rd13(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13)

#define CTOP_CTRL_A0_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14)								\
			CTOP_CTRL_CHIP_Rd14(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14)

#define CTOP_CTRL_A0_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15)						\
			CTOP_CTRL_CHIP_Rd15(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15)

#define CTOP_CTRL_A0_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)			\
			CTOP_CTRL_CHIP_Rd16(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15,_f16,_v16)


#define CTOP_CTRL_A0_Wr01(_r,_f01,_v01)											\
			CTOP_CTRL_CHIP_Wr01(CTOP_SHADOW_A0,_r,_f01,_v01)

#define CTOP_CTRL_A0_Wr02(_r,_f01,_v01,_f02,_v02)								\
			CTOP_CTRL_CHIP_Wr02(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02)

#define CTOP_CTRL_A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)						\
			CTOP_CTRL_CHIP_Wr03(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03)

#define CTOP_CTRL_A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)			\
			CTOP_CTRL_CHIP_Wr04(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04)

#define CTOP_CTRL_A0_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05)	\
			CTOP_CTRL_CHIP_Wr05(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05)

#define CTOP_CTRL_A0_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06)								\
			CTOP_CTRL_CHIP_Wr06(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06)

#define CTOP_CTRL_A0_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07)						\
			CTOP_CTRL_CHIP_Wr07(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07)

#define CTOP_CTRL_A0_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)			\
			CTOP_CTRL_CHIP_Wr08(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08)


#define CTOP_CTRL_A0_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09)											\
			CTOP_CTRL_CHIP_Wr09(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09)

#define CTOP_CTRL_A0_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10)								\
			CTOP_CTRL_CHIP_Wr10(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10)

#define CTOP_CTRL_A0_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11)						\
			CTOP_CTRL_CHIP_Wr11(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11)

#define CTOP_CTRL_A0_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)			\
			CTOP_CTRL_CHIP_Wr12(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12)

#define CTOP_CTRL_A0_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13)											\
			CTOP_CTRL_CHIP_Wr13(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13)

#define CTOP_CTRL_A0_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14)								\
			CTOP_CTRL_CHIP_Wr14(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14)


#define CTOP_CTRL_A0_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15)						\
			CTOP_CTRL_CHIP_Wr15(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15)

#define CTOP_CTRL_A0_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)			\
			CTOP_CTRL_CHIP_Wr16(CTOP_SHADOW_A0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15,_f16,_v16)


/*
L8 B0
*/
#define CTOP_CTRL_B0_RdFL(_r)													\
			CTOP_CTRL_CHIP_RdFL(CTOP_SHADOW_B0, CTOP_REAL_B0, _r)

#define CTOP_CTRL_B0_WrFL(_r)													\
			CTOP_CTRL_CHIP_WrFL(CTOP_SHADOW_B0, CTOP_REAL_B0, _r)

#define CTOP_CTRL_B0_Rd(_r)														\
			CTOP_CTRL_CHIP_Rd(CTOP_SHADOW_B0,_r)

#define CTOP_CTRL_B0_Wr(_r,_v)													\
			CTOP_CTRL_CHIP_Wr(CTOP_SHADOW_B0, _r,_v)


#define CTOP_CTRL_B0_Rd01(_r,_f01,_v01)											\
			CTOP_CTRL_CHIP_Rd01(CTOP_SHADOW_B0,_r,_f01,_v01)

#define CTOP_CTRL_B0_Rd02(_r,_f01,_v01,_f02,_v02) 								\
			CTOP_CTRL_CHIP_Rd02(CTOP_SHADOW_B0, _r,_f01,_v01,_f02,_v02)

#define CTOP_CTRL_B0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) 					\
			CTOP_CTRL_CHIP_Rd03(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03)

#define CTOP_CTRL_B0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04) 			\
			CTOP_CTRL_CHIP_Rd04(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04)

#define CTOP_CTRL_B0_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05)	\
			CTOP_CTRL_CHIP_Rd05(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05)

#define CTOP_CTRL_B0_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05,	\
							_f06,_v06)											\
			CTOP_CTRL_CHIP_Rd06(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06)

#define CTOP_CTRL_B0_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07)						\
			CTOP_CTRL_CHIP_Rd07(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07)

#define CTOP_CTRL_B0_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)			\
			CTOP_CTRL_CHIP_Rd08(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08)

#define CTOP_CTRL_B0_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09)											\
			CTOP_CTRL_CHIP_Rd09(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09)

#define CTOP_CTRL_B0_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10)								\
			CTOP_CTRL_CHIP_Rd10(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10)

#define CTOP_CTRL_B0_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11)						\
			CTOP_CTRL_CHIP_Rd11(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11)

#define CTOP_CTRL_B0_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)			\
			CTOP_CTRL_CHIP_Rd12(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12)

#define CTOP_CTRL_B0_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13)											\
			CTOP_CTRL_CHIP_Rd13(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13)

#define CTOP_CTRL_B0_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14)								\
			CTOP_CTRL_CHIP_Rd14(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14)

#define CTOP_CTRL_B0_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15)						\
			CTOP_CTRL_CHIP_Rd15(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15)

#define CTOP_CTRL_B0_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)			\
			CTOP_CTRL_CHIP_Rd16(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15,_f16,_v16)


#define CTOP_CTRL_B0_Wr01(_r,_f01,_v01)											\
			CTOP_CTRL_CHIP_Wr01(CTOP_SHADOW_B0,_r,_f01,_v01)

#define CTOP_CTRL_B0_Wr02(_r,_f01,_v01,_f02,_v02)								\
			CTOP_CTRL_CHIP_Wr02(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02)

#define CTOP_CTRL_B0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)						\
			CTOP_CTRL_CHIP_Wr03(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03)

#define CTOP_CTRL_B0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)			\
			CTOP_CTRL_CHIP_Wr04(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04)

#define CTOP_CTRL_B0_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,_f05,_v05)	\
			CTOP_CTRL_CHIP_Wr05(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05)

#define CTOP_CTRL_B0_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06)								\
			CTOP_CTRL_CHIP_Wr06(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06)

#define CTOP_CTRL_B0_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07)						\
			CTOP_CTRL_CHIP_Wr07(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07)

#define CTOP_CTRL_B0_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)			\
			CTOP_CTRL_CHIP_Wr08(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08)


#define CTOP_CTRL_B0_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09)											\
			CTOP_CTRL_CHIP_Wr09(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09)

#define CTOP_CTRL_B0_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10)								\
			CTOP_CTRL_CHIP_Wr10(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10)

#define CTOP_CTRL_B0_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11)						\
			CTOP_CTRL_CHIP_Wr11(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11)

#define CTOP_CTRL_B0_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)			\
			CTOP_CTRL_CHIP_Wr12(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12)

#define CTOP_CTRL_B0_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13)											\
			CTOP_CTRL_CHIP_Wr13(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13)

#define CTOP_CTRL_B0_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14)								\
			CTOP_CTRL_CHIP_Wr14(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14)


#define CTOP_CTRL_B0_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15)						\
			CTOP_CTRL_CHIP_Wr15(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15)

#define CTOP_CTRL_B0_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,			\
							_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,			\
							_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,			\
							_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)			\
			CTOP_CTRL_CHIP_Wr16(CTOP_SHADOW_B0,_r,_f01,_v01,_f02,_v02,			\
								_f03,_v03,_f04,_v04,_f05,_v05,_f06,_v06,		\
								_f07,_v07,_f08,_v08,_f09,_v09,_f10,_v10,		\
								_f11,_v11,_f12,_v12,_f13,_v13,_f14,_v14,		\
								_f15,_v15,_f16,_v16)




#define CTOP_CTRL_RdFL		CTOP_CTRL_B0_RdFL
#define CTOP_CTRL_WrFL		CTOP_CTRL_B0_WrFL
#define CTOP_CTRL_Rd		CTOP_CTRL_B0_Rd
#define CTOP_CTRL_Wr		CTOP_CTRL_B0_Wr


#define CTOP_CTRL_Rd01		CTOP_CTRL_B0_Rd01
#define CTOP_CTRL_Rd02		CTOP_CTRL_B0_Rd02
#define CTOP_CTRL_Rd03		CTOP_CTRL_B0_Rd03
#define CTOP_CTRL_Rd04		CTOP_CTRL_B0_Rd04
#define CTOP_CTRL_Rd05		CTOP_CTRL_B0_Rd05
#define CTOP_CTRL_Rd06		CTOP_CTRL_B0_Rd06
#define CTOP_CTRL_Rd07		CTOP_CTRL_B0_Rd07
#define CTOP_CTRL_Rd08		CTOP_CTRL_B0_Rd08
#define CTOP_CTRL_Rd09		CTOP_CTRL_B0_Rd09
#define CTOP_CTRL_Rd10		CTOP_CTRL_B0_Rd10
#define CTOP_CTRL_Rd11		CTOP_CTRL_B0_Rd11
#define CTOP_CTRL_Rd12		CTOP_CTRL_B0_Rd12
#define CTOP_CTRL_Rd13		CTOP_CTRL_B0_Rd13
#define CTOP_CTRL_Rd14		CTOP_CTRL_B0_Rd14
#define CTOP_CTRL_Rd15		CTOP_CTRL_B0_Rd15
#define CTOP_CTRL_Rd16		CTOP_CTRL_B0_Rd16

#define CTOP_CTRL_Wr01		CTOP_CTRL_B0_Wr01
#define CTOP_CTRL_Wr02		CTOP_CTRL_B0_Wr02
#define CTOP_CTRL_Wr03		CTOP_CTRL_B0_Wr03
#define CTOP_CTRL_Wr04		CTOP_CTRL_B0_Wr04
#define CTOP_CTRL_Wr05		CTOP_CTRL_B0_Wr05
#define CTOP_CTRL_Wr06		CTOP_CTRL_B0_Wr06
#define CTOP_CTRL_Wr07		CTOP_CTRL_B0_Wr07
#define CTOP_CTRL_Wr08		CTOP_CTRL_B0_Wr08
#define CTOP_CTRL_Wr09		CTOP_CTRL_B0_Wr09
#define CTOP_CTRL_Wr10		CTOP_CTRL_B0_Wr10
#define CTOP_CTRL_Wr11		CTOP_CTRL_B0_Wr11
#define CTOP_CTRL_Wr12		CTOP_CTRL_B0_Wr12
#define CTOP_CTRL_Wr13		CTOP_CTRL_B0_Wr13
#define CTOP_CTRL_Wr14		CTOP_CTRL_B0_Wr14
#define CTOP_CTRL_Wr15		CTOP_CTRL_B0_Wr15
#define CTOP_CTRL_Wr16		CTOP_CTRL_B0_Wr16


extern CTOP_CTRL_T	gCTOP_CTRL;


static inline UINT32 CTOP_CTRL_READ(UINT32 offset)
{
	UINT32 value;
	offset >>= 2;
	value = *(gCTOP_CTRL.phys.addr + offset);
	*(gCTOP_CTRL.shadow.addr + offset) = value;
	return value;
}

static inline void CTOP_CTRL_WRITE(UINT32 offset, UINT32 value)
{
	offset >>= 2;
	*(gCTOP_CTRL.phys.addr + offset) = value;
	*(gCTOP_CTRL.shadow.addr + offset) = value;
}

#ifdef __cplusplus
}
#endif

#endif	/* #ifndef __CTOP_REGS_H__ */
