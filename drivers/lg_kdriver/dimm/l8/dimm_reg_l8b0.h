#ifndef _REG_DIMM_L8B0_h
#define _REG_DIMM_L8B0_h

typedef struct { // 0x0000
	UINT32
	vsb                 : 11,  //  0:10
	                    : 5,   // 11:15
	hsb                 : 11;  // 16:26
} LED_L8B0_HSB_VSB_T;

typedef struct { // 0x0004
	UINT32
	hnb                 : 6,   //  0: 5
	                    : 2,   //  6: 7
	vnb                 : 5;   //  8:12
} LED_L8B0_HNB_VNB_T;

typedef struct { // 0x0008
	UINT32
	pb_en               : 1,   //     0
	demo_en             : 1,   //     1
	apf_en              : 1,   //     2
	sbi2rgb_en          : 1,   //     3
	sbi_dis             : 1,   //     4
	mark_en             : 1,   //     5
	gain_map_disp       : 1,   //     6
	gain_map_demo       : 1;   //     7
} LED_L8B0_DBG_CTRL_T;

typedef struct { // 0x000c
	UINT32
	pat_en              : 8;   //  0: 7
} LED_L8B0_PAT_EN_T;

typedef struct { // 0x0010
	UINT32
	pat_val_b           : 10,  //  0: 9
	pat_val_g           : 10,  // 10:19
	pat_val_r           : 10;  // 20:29
} LED_L8B0_PAT_VALUE_T;

typedef struct { // 0x0014
	UINT32
	pat_h_min           : 10,  //  0: 9
	                    : 6,   // 10:15
	pat_h_max           : 10;  // 16:25
} LED_L8B0_PAT_H_MIN_MAX_T;

typedef struct { // 0x0018
	UINT32
	pat_v_min           : 11,  //  0:10
	                    : 5,   // 11:15
	pat_v_max           : 11;  // 16:26
} LED_L8B0_PAT_V_MIN_MAX_T;

typedef struct { // 0x001c
	UINT32
	pat_h_ppf           : 8,   //  0: 7
	pat_v_ppf           : 8;   //  8:15
} LED_L8B0_PAT_HV_PPF_T;

typedef struct { // 0x0020
	UINT32
	wavg_en             : 1;   //     0
} LED_L8B0_WAVG_EN_T;

typedef struct { // 0x0024
	UINT32
	max_opt             : 8;   //  0: 7
} LED_L8B0_MAX_OPT_T;

typedef struct { // 0x0028
	UINT32
	blk_max_mode        : 1;   //     0
} LED_L8B0_BLK_MAX_MODE_T;

typedef struct { // 0x002c
	UINT32
	nlf_th              : 10,  //  0: 9
	                    : 6,   // 10:15
	limit               : 10;  // 16:25
} LED_L8B0_NLF_TH_T;

typedef struct { // 0x0030
	UINT32
	a_para              : 9;   //  0: 8
} LED_L8B0_A_PARA_T;

typedef struct { // 0x0034
	UINT32
	tf_opmode           : 3;   //  0: 2
} LED_L8B0_TF_OPMODE_T;

typedef struct { // 0x0038
	UINT32
	sc_mag_th           : 10,  //  0: 9
	                    : 6,   // 10:15
	sc_mag_gn           : 8;   // 16:23
} LED_L8B0_SC_MAG_GN_TH_T;

typedef struct { // 0x003c
	UINT32
	sc_mag_info         : 10;  //  0: 9
} LED_L8B0_SC_MAG_INFO_T;

typedef struct { // 0x0040
	UINT32
	sc_adj_en           : 1;   //     0
} LED_L8B0_SC_ADJ_EN_T;

typedef struct { // 0x0044
	UINT32
	md_adj_en           : 1;   //     0
} LED_L8B0_MD_ADJ_EN_T;

typedef struct { // 0x0048
	UINT32
	sc_tdif_th          : 10,  //  0: 9
	                    : 6,   // 10:15
	sc_tdif_gn          : 8;   // 16:23
} LED_L8B0_SC_TDIF_GN_TH_T;

typedef struct { // 0x004c
	UINT32
	hist_mode           : 2;   //  0: 1
} LED_L8B0_HIST_MODE_T;

typedef struct { // 0x0050
	UINT32
	lrz_offset          : 8,   //  0: 7
	lrz_gain            : 8;   //  8:15
} LED_L8B0_LRZ_GAIN_OFFSET_T;

typedef struct { // 0x0054
	UINT32
	bv_dly_ble          : 2,   //  0: 1
	bv_dly_blu          : 2;   //  2: 3
} LED_L8B0_BV_DELAY_T;

typedef struct { // 0x0058
	UINT32
	wb_en               : 1;   //     0
} LED_L8B0_WB_EN_T;

typedef struct { // 0x005c
	UINT32
	iwb_r_gain          : 11,  //  0:10
	                    : 5,   // 11:15
	iwb_r_offset        : 10;  // 16:25
} LED_L8B0_IWB_R_OFFSET_GAIN_T;

typedef struct { // 0x0060
	UINT32
	iwb_g_gain          : 11,  //  0:10
	                    : 5,   // 11:15
	iwb_g_offset        : 10;  // 16:25
} LED_L8B0_IWB_G_OFFSET_GAIN_T;

typedef struct { // 0x0064
	UINT32
	iwb_b_gain          : 11,  //  0:10
	                    : 5,   // 11:15
	iwb_b_offset        : 10;  // 16:25
} LED_L8B0_IWB_B_OFFSET_GAIN_T;

typedef struct { // 0x0068
	UINT32
	dsp_bv_end          : 1;   //     0
} LED_L8B0_DSP_BV_END_T;

typedef struct { // 0x006c
	UINT32
	bvout_mode          : 4,   //  0: 3
	vsout_mode          : 4,   //  4: 7
	bdout_mode          : 4,   //  8:11
	                    : 4,   // 12:15
	tfout_mode          : 4;   // 16:19
} LED_L8B0_BV_RCTRL_MODE_T;

typedef struct { // 0x0070
	UINT32
	pic_attr            : 1,   //     0
	black_mask          : 1,   //     1
	tf_pic_attr         : 1;   //     2
} LED_L8B0_PIC_ATTR_T;

typedef struct { // 0x0074
	UINT32
	nlf_mode            : 1;   //     0
} LED_L8B0_NLF_MODE_T;

typedef struct { // 0x0078
	UINT32
	htab_en             : 2,   //  0: 1
	vtab_en             : 2;   //  2: 3
} LED_L8B0_NLF_TAB_EN_T;

typedef struct { // 0x007c
	UINT32
	apl                 : 10;  //  0: 9
} LED_L8B0_APL_T;

typedef struct { // 0x0080
	UINT32
	bv_sel              : 1;   //     0
} LED_L8B0_BLU_BV_SEL_T;

typedef struct { // 0x0084
	UINT32
	max_opt_mode        : 1;   //     0
} LED_L8B0_MAX_OPT_MODE_T;

typedef struct { // 0x0088
	UINT32
	max_opt_1           : 8,   //  0: 7
	max_opt_0           : 8;   //  8:15
} LED_L8B0_MAX_OPT_0_1_T;

typedef struct { // 0x008c
	UINT32
	level_th            : 10;  //  0: 9
} LED_L8B0_LEVEL_TH_T;

typedef struct { // 0x0090
	UINT32
	num_th              : 12,  //  0:11
	                    : 4,   // 12:15
	num_bit_sel         : 3;   // 16:18
} LED_L8B0_NUMBER_TH_T;

typedef struct { // 0x0094
	UINT32
	gbl                 : 10;  //  0: 9
} LED_L8B0_GBL_T;

typedef struct { // 0x0098
	UINT32
	comp_en             : 1;   //     0
} LED_L8B0_PC_EN_T;

typedef struct { // 0x009c
	UINT32
	gain_prec_nor       : 4,   //  0: 3
	gain_prec_demo      : 4,   //  4: 7
	gain_p5             : 2;   //  8: 9
} LED_L8B0_PC_GAIN_PREC_T;

typedef struct { // 0x00a0
	UINT32
	pc_in_sel           : 2;   //  0: 1
} LED_L8B0_PC_MODE_SEL_T;

typedef struct { // 0x00a4
	UINT32
	pc_sbi_in_sel       : 1;   //     0
} LED_L8B0_PC_SBI_IN_SEL_T;

typedef struct { // 0x00a8
	UINT32
	sbi_i2c             : 10;  //  0: 9
} LED_L8B0_PC_SBI_IN_VALUE_T;

typedef struct { // 0x00ac
	UINT32
	wb_r_gain           : 16,  //  0:15
	wb_r_offset         : 16;  // 16:31
} LED_L8B0_WB_R_GAIN_OFFSET_T;

typedef struct { // 0x00b0
	UINT32
	vsync_neg           : 1,   //     0
	hsync_neg           : 1;   //     1
} LED_L8B0_OUT_SYNC_POL_T;

typedef struct { // 0x00b4
	UINT32
	lum_demo            : 10;  //  0: 9
} LED_L8B0_LUM_DEMO_T;

typedef struct { // 0x00b8
	UINT32
	dithe_en            : 1,   //     0
	temp_en             : 1;   //     1
} LED_L8B0_DITHER_T;

typedef struct { // 0x00bc
	UINT32
	dual_lvds           : 1,   //     0
	add_pixel           : 1;   //     1
} LED_L8B0_VIN_CONF_T;

typedef struct { // 0x00c0
	UINT32
	abv_cmp_value       : 10;  //  0: 9
} LED_L8B0_SCAN_TH_T;

typedef struct { // 0x00c4
	UINT32
	bv_mux_ctrl         : 3;   //  0: 2
} LED_L8B0_BV_MUX_CTRL_T;

typedef struct { // 0x00c8
	UINT32
	edge_type           : 1,   //     0
	edge_lit            : 1,   //     1
	edge_mode           : 2,   //  2: 3
	umask_bypass        : 1,   //     4
	nlf_bypass          : 1;   //     5
} LED_L8B0_BLU_TYPE_T;

typedef struct { // 0x00cc
	UINT32
	minl                : 10;  //  0: 9
} LED_L8B0_MINL_T;

typedef struct { // 0x00d0
	UINT32
	lut_mode            : 2;   //  0: 1
} LED_L8B0_LUT_MODE_T;

typedef struct { // 0x00d4
	UINT32
	ex_abv              : 10;  //  0: 9
} LED_L8B0_EX_ABV_T;

typedef struct { // 0x00d8
	UINT32
	sg_l                : 8,   //  0: 7
	sg_h                : 8;   //  8:15
} LED_L8B0_SG_L_H_T;

typedef struct { // 0x00dc
	UINT32
	wb_g_gain           : 16,  //  0:15
	wb_g_offset         : 16;  // 16:31
} LED_L8B0_WB_G_GAIN_OFFSET_T;

typedef struct { // 0x00e0
	UINT32
	umask_coeff         : 12;  //  0:11
} LED_L8B0_UMASK_COEFF_T;

typedef struct { // 0x00e4
	UINT32
	sf_5x5_en           : 1,   //     0
	umask_en            : 1;   //     1
} LED_L8B0_SF_EN_T;

typedef struct { // 0x00e8
	UINT32
	coaring_n           : 10,  //  0: 9
	                    : 6,   // 10:15
	coaring_p           : 10;  // 16:25
} LED_L8B0_UMASK_COARING_T;

typedef struct { // 0x00ec
	UINT32
	wb_b_gain           : 16,  //  0:15
	wb_b_offset         : 16;  // 16:31
} LED_L8B0_WB_B_GAIN_OFFSET_T;

typedef struct { // 0x00f4
	UINT32
	gain_n              : 12,  //  0:11
	                    : 4,   // 12:15
	gain_p              : 12;  // 16:27
} LED_L8B0_UMASK_GAIN_T;

typedef struct { // 0x00f8
	UINT32
	bv_i2c_wdata        : 10,  //  0: 9
	                    : 6,   // 10:15
	bv_i2c_waddr        : 11,  // 16:26
	                    : 4,   // 27:30
	bv_i2c_wen          : 1;   //    31
} LED_L8B0_BV_I2C_W_EN_DATA_T;

typedef struct { // 0x00fc
	UINT32
	hist_intr_clr       : 1;   //     0
} LED_L8B0_HIST_INTR_CLR_T;

typedef struct { // 0x0100
	UINT32
	hsb                 : 10,  //  0: 9
	                    : 6,   // 10:15
	vsb                 : 10;  // 16:25
} LED_L8B0_HSB_VSB_B1_T;

typedef struct { // 0x0104
	UINT32
	hnb                 : 6,   //  0: 5
	                    : 2,   //  6: 7
	vnb                 : 5;   //  8:12
} LED_L8B0_HNB_VNB_B1_T;

typedef struct { // 0x0108
	UINT32
	pwm_value           : 10;  //  0: 9
} LED_L8B0_PWM_VALUE_T;

typedef struct { // 0x010c
	UINT32
	sclk_t1             : 9;   //  0: 8
} LED_L8B0_SCLK_T1_T;

typedef struct { // 0x0110
	UINT32
	sclk_t2             : 9;   //  0: 8
} LED_L8B0_SCLK_T2_T;

typedef struct { // 0x0114
	UINT32
	sclk_t3             : 9;   //  0: 8
} LED_L8B0_SCLK_T3_T;

typedef struct { // 0x0118
	UINT32
	sclk_t4             : 9;   //  0: 8
} LED_L8B0_SCLK_T4_T;

typedef struct { // 0x011c
	UINT32
	cpha                : 1,   //     0
	cpol                : 1,   //     1
	spi_data_size       : 2;   //  2: 3
} LED_L8B0_SPI_MASTER_CFG0_T;

typedef struct { // 0x0124
	UINT32
	spi_idc0            : 16,  //  0:15
	spi_idc1            : 16;  // 16:31
} LED_L8B0_SPI_IDC01_T;

typedef struct { // 0x0128
	UINT32
	spi_idc2            : 16,  //  0:15
	spi_idc3            : 16;  // 16:31
} LED_L8B0_SPI_IDC23_T;

typedef struct { // 0x012c
	UINT32
	spi_cmd0            : 16,  //  0:15
	spi_cmd1            : 16;  // 16:31
} LED_L8B0_SPI_CMD01_T;

typedef struct { // 0x0130
	UINT32
	spi_cmd2            : 16,  //  0:15
	spi_cmd3            : 16;  // 16:31
} LED_L8B0_SPI_CMD23_T;

typedef struct { // 0x0134
	UINT32
	spi_cmd_mode        : 2;   //  0: 1
} LED_L8B0_SPI_CMD_NUM_T;

typedef struct { // 0x0138
	UINT32
	sclk_t5             : 8;   //  0: 7
} LED_L8B0_VSYNC_T5_T;

typedef struct { // 0x0144
	UINT32
	m0_sp               : 11;  //  0:10
} LED_L8B0_M0_SP_T;

typedef struct { // 0x0148
	UINT32
	m1_sp               : 11;  //  0:10
} LED_L8B0_M1_SP_T;

typedef struct { // 0x014c
	UINT32
	m2_sp               : 11;  //  0:10
} LED_L8B0_M2_SP_T;

typedef struct { // 0x0150
	UINT32
	m3_sp               : 11;  //  0:10
} LED_L8B0_M3_SP_T;

typedef struct { // 0x0154
	UINT32
	m0_hnb              : 6;   //  0: 5
} LED_L8B0_M0_HNB_T;

typedef struct { // 0x0158
	UINT32
	m1_hnb              : 6;   //  0: 5
} LED_L8B0_M1_HNB_T;

typedef struct { // 0x015c
	UINT32
	m2_hnb              : 6;   //  0: 5
} LED_L8B0_M2_HNB_T;

typedef struct { // 0x0160
	UINT32
	m3_hnb              : 6;   //  0: 5
} LED_L8B0_M3_HNB_T;

typedef struct { // 0x0164
	UINT32
	m0_vnb              : 5;   //  0: 4
} LED_L8B0_M0_VNB_T;

typedef struct { // 0x0168
	UINT32
	m1_vnb              : 5;   //  0: 4
} LED_L8B0_M1_VNB_T;

typedef struct { // 0x016c
	UINT32
	m2_vnb              : 5;   //  0: 4
} LED_L8B0_M2_VNB_T;

typedef struct { // 0x0170
	UINT32
	m3_vnb              : 5;   //  0: 4
} LED_L8B0_M3_VNB_T;

typedef struct { // 0x0174
	UINT32
	spi_ch_mask         : 4;   //  0: 3
} LED_L8B0_SPI_CH_MASK_T;

typedef struct { // 0x0178
	UINT32
	reverse_mode_en     : 1;   //     0
} LED_L8B0_REVERSE_MODE_T;

typedef struct { // 0x0184
	UINT32
	scan_status         : 1;   //     0
} LED_L8B0_SCANNING_STATUS_T;

typedef struct { // 0x0188
	UINT32
	bv_i2c_rd_en        : 1;   //     0
} LED_L8B0_BV_I2C_RD_EN_T;

typedef struct { // 0x018c
	UINT32
	bv_i2c_rd_addr      : 12;  //  0:11
} LED_L8B0_BV_I2C_RD_ADDR_T;

typedef struct { // 0x0190
	UINT32
	bv_i2c_rd_data      : 10;  //  0: 9
} LED_L8B0_BV_I2C_RD_DATA_T;

typedef struct { // 0x0194
	UINT32
	blu_if_mode         : 1;   //     0
} LED_L8B0_BLU_IF_MODE_T;

typedef struct { // 0x0198
	UINT32
	ble_hsb             : 11,  //  0:10
	                    : 5,   // 11:15
	ble_vsb             : 11;  // 16:26
} LED_L8B0_BLE_HSB_VSB_T;

typedef struct { // 0x019c
	UINT32
	ble_hnb             : 6,   //  0: 5
	                    : 2,   //  6: 7
	ble_vnb             : 5;   //  8:12
} LED_L8B0_BLE_HNB_VNB_T;

typedef struct { // 0x01ac
	UINT32
	spi_vs_delay        : 24;  //  0:23
} LED_L8B0_SPI_VS_DELAY_T;

typedef struct { // 0x01b0
	UINT32
	vs_mode             : 2,   //  0: 1
	vs_in_pol           : 1,   //     2
	vs_mode_en          : 1;   //     3
} LED_L8B0_BLU_VS_MODE_T;

typedef struct { // 0x01b4
	UINT32
	i2c_slv_addr        : 8;   //  0: 7
} LED_L8B0_I2C_SLAVE_ADDR_T;

typedef struct { // 0x0200
	UINT32
	vsb                 : 11,  //  0:10
	                    : 5,   // 11:15
	hsb                 : 11;  // 16:26
} LED_L8B0_HSB_VSB_B2_T;

typedef struct { // 0x0204
	UINT32
	hnb                 : 6,   //  0: 5
	                    : 2,   //  6: 7
	vnb                 : 5;   //  8:12
} LED_L8B0_HNB_VNB_B2_T;

typedef struct { // 0x0208
	UINT32
	version             : 32;  //  0:31
} LED_L8B0_VERSION_T;

typedef struct { // 0x0210
	UINT32
	run_stall           : 1,   //     0
	auto_boot           : 1;   //     1
} LED_L8B0_RUN_STALL_T;

typedef struct { // 0x0214
	UINT32
	mem_addr_clr        : 1;   //     0
} LED_L8B0_CMEM_ADDR_CLR_T;

typedef struct { // 0x0218
	UINT32
	wavg_hcoeff         : 8;   //  0: 7
} LED_L8B0_WAVG_HCOEFF_T;

typedef struct { // 0x021c
	UINT32
	wavg_vcoeff         : 8;   //  0: 7
} LED_L8B0_WAVG_VCOEFF_T;

typedef struct { // 0x0220
	UINT32
	sbi_hcoeff          : 10;  //  0: 9
} LED_L8B0_SBI_HCOEFF_T;

typedef struct { // 0x0224
	UINT32
	sbi_vcoeff          : 10;  //  0: 9
} LED_L8B0_SBI_VCOEFF_T;

typedef struct { // 0x0228
	UINT32
	pc_coeff_a          : 10;  //  0: 9
} LED_L8B0_PC_LUT_A_T;

typedef struct { // 0x022c
	UINT32
	pc_lut_b            : 10;  //  0: 9
} LED_L8B0_PC_LUT_B_T;

typedef struct { // 0x0230
	UINT32
	pc_lut_c            : 10;  //  0: 9
} LED_L8B0_PC_LUT_C_T;

typedef struct { // 0x0234
	UINT32
	pc_lut_d            : 10;  //  0: 9
} LED_L8B0_PC_LUT_D_T;

typedef struct { // 0x0238
	UINT32
	bv_upper_lut        : 10;  //  0: 9
} LED_L8B0_BV_UPPER_LUT_T;

typedef struct { // 0x023c
	UINT32
	bv_lower_lut        : 10;  //  0: 9
} LED_L8B0_BV_LOWER_LUT_T;

typedef struct { // 0x0240
	UINT32
	int_mask            : 14;  //  0:13
} LED_L8B0_INT_MASK_T;

typedef struct { // 0x0244
	UINT32
	pdebug_en           : 1;   //     0
} LED_L8B0_PDEBUG_EN_T;

typedef struct { // 0x0248
	UINT32
	pdebug_status       : 8;   //  0: 7
} LED_L8B0_PDEBUG_STATUS_T;

typedef struct { // 0x024c
	UINT32
	pdebug_pc           : 32;  //  0:31
} LED_L8B0_PDEBUG_PC_T;

typedef struct { // 0x0250
	UINT32
	pdebug_data         : 32;  //  0:31
} LED_L8B0_PDEBUG_DATA_T;

typedef struct { // 0x0254
	UINT32
	bv_intr_clr         : 1;   //     0
} LED_L8B0_BV_INTR_CLR_T;

typedef struct { // 0x0258
	UINT32
	line_intr_clr       : 1;   //     0
} LED_L8B0_LINE_INTR_CLR_T;

typedef struct { // 0x025c
	UINT32
	line_inter_counter  : 11;  //  0:10
} LED_L8B0_LINE_INTR_COUNTER_T;

typedef struct { // 0x0260
	UINT32
	de_intr_pol         : 1,   //     0
	hs_intr_pol         : 1,   //     1
	vs_intr_pol         : 1;   //     2
} LED_L8B0_SYNC_INT_POL_T;

typedef struct { // 0x0264
	UINT32
	bv_intr_clr         : 1;   //     0
} LED_L8B0_BLU_BV_INTR_CLR_T;

typedef struct { // 0x0268
	UINT32
	ipc_int_en          : 32;  //  0:31
} LED_L8B0_IPC_INT_EN_T;

typedef struct { // 0x026c
	UINT32
	ipc_int_status      : 32;  //  0:31
} LED_L8B0_IPC_INT_STATUS_T;

typedef struct { // 0x0270
	UINT32
	ipc_int_raw_status  : 32;  //  0:31
} LED_L8B0_IPC_INT_RAW_STATUS_T;

typedef struct { // 0x0274
	UINT32
	ipc_int_clr         : 32;  //  0:31
} LED_L8B0_IPC_INT_CLR_T;

typedef struct { // 0x0278
	UINT32
	general_reg         : 32;  //  0:31
} LED_L8B0_GENERAL_REG_T;

typedef struct { // 0x0370
	UINT32
	ext_intr_en         : 32;  //  0:31
} LED_L8B0_EXT_INTR_EN_T;

typedef struct { // 0x0374
	UINT32
	ext_intr_status     : 32;  //  0:31
} LED_L8B0_EXT_INTR_STATUS_T;

typedef struct { // 0x0378
	UINT32
	ext_intr_raw_status : 32;  //  0:31
} LED_L8B0_EXT_INTR_RAW_STATUS_T;

typedef struct { // 0x037c
	UINT32
	ext_intr_clr        : 32;  //  0:31
} LED_L8B0_EXT_INTR_CLR_T;

typedef struct { // 0x0380
	UINT32
	ipc_mem_rw          : 32;  //  0:31
} LED_L8B0_IPC_MEM_T;

typedef struct {
    LED_L8B0_HSB_VSB_T               hsb_vsb;                 // 0x0000
    LED_L8B0_HNB_VNB_T               hnb_vnb;                 // 0x0004
    LED_L8B0_DBG_CTRL_T              dbg_ctrl;                // 0x0008
    LED_L8B0_PAT_EN_T                pat_en;                  // 0x000c
    LED_L8B0_PAT_VALUE_T             pat_value;               // 0x0010
    LED_L8B0_PAT_H_MIN_MAX_T         pat_h_min_max;           // 0x0014
    LED_L8B0_PAT_V_MIN_MAX_T         pat_v_min_max;           // 0x0018
    LED_L8B0_PAT_HV_PPF_T            pat_hv_ppf;              // 0x001c
    LED_L8B0_WAVG_EN_T               wavg_en;                 // 0x0020
    LED_L8B0_MAX_OPT_T               max_opt;                 // 0x0024
    LED_L8B0_BLK_MAX_MODE_T          blk_max_mode;            // 0x0028
    LED_L8B0_NLF_TH_T                nlf_th;                  // 0x002c
    LED_L8B0_A_PARA_T                a_para;                  // 0x0030
    LED_L8B0_TF_OPMODE_T             tf_opmode;               // 0x0034
    LED_L8B0_SC_MAG_GN_TH_T          sc_mag_gn_th;            // 0x0038
    LED_L8B0_SC_MAG_INFO_T           sc_mag_info;             // 0x003c
    LED_L8B0_SC_ADJ_EN_T             sc_adj_en;               // 0x0040
    LED_L8B0_MD_ADJ_EN_T             md_adj_en;               // 0x0044
    LED_L8B0_SC_TDIF_GN_TH_T         sc_tdif_gn_th;           // 0x0048
    LED_L8B0_HIST_MODE_T             hist_mode;               // 0x004c
    LED_L8B0_LRZ_GAIN_OFFSET_T       lrz_gain_offset;         // 0x0050
    LED_L8B0_BV_DELAY_T              bv_delay;                // 0x0054
    LED_L8B0_WB_EN_T                 wb_en;                   // 0x0058
    LED_L8B0_IWB_R_OFFSET_GAIN_T     iwb_r_offset_gain;       // 0x005c
    LED_L8B0_IWB_G_OFFSET_GAIN_T     iwb_g_offset_gain;       // 0x0060
    LED_L8B0_IWB_B_OFFSET_GAIN_T     iwb_b_offset_gain;       // 0x0064
    LED_L8B0_DSP_BV_END_T            dsp_bv_end;              // 0x0068
    LED_L8B0_BV_RCTRL_MODE_T         bv_rctrl_mode;           // 0x006c
    LED_L8B0_PIC_ATTR_T              pic_attr;                // 0x0070
    LED_L8B0_NLF_MODE_T              nlf_mode;                // 0x0074
    LED_L8B0_NLF_TAB_EN_T            nlf_tab_en;              // 0x0078
    LED_L8B0_APL_T                   apl;                     // 0x007c
    LED_L8B0_BLU_BV_SEL_T            blu_bv_sel;              // 0x0080
    LED_L8B0_MAX_OPT_MODE_T          max_opt_mode;            // 0x0084
    LED_L8B0_MAX_OPT_0_1_T           max_opt_0_1;             // 0x0088
    LED_L8B0_LEVEL_TH_T              level_th;                // 0x008c
    LED_L8B0_NUMBER_TH_T             number_th;               // 0x0090
    LED_L8B0_GBL_T                   gbl;                     // 0x0094
    LED_L8B0_PC_EN_T                 pc_en;                   // 0x0098
    LED_L8B0_PC_GAIN_PREC_T          pc_gain_prec;            // 0x009c
    LED_L8B0_PC_MODE_SEL_T           pc_mode_sel;             // 0x00a0
    LED_L8B0_PC_SBI_IN_SEL_T         pc_sbi_in_sel;           // 0x00a4
    LED_L8B0_PC_SBI_IN_VALUE_T       pc_sbi_in_value;         // 0x00a8
    LED_L8B0_WB_R_GAIN_OFFSET_T      wb_r_gain_offset;        // 0x00ac
    LED_L8B0_OUT_SYNC_POL_T          out_sync_pol;            // 0x00b0
    LED_L8B0_LUM_DEMO_T              lum_demo;                // 0x00b4
    LED_L8B0_DITHER_T                dither;                  // 0x00b8
    LED_L8B0_VIN_CONF_T              vin_conf;                // 0x00bc
    LED_L8B0_SCAN_TH_T               scan_th;                 // 0x00c0
    LED_L8B0_BV_MUX_CTRL_T           bv_mux_ctrl;             // 0x00c4
    LED_L8B0_BLU_TYPE_T              blu_type;                // 0x00c8
    LED_L8B0_MINL_T                  minl;                    // 0x00cc
    LED_L8B0_LUT_MODE_T              lut_mode;                // 0x00d0
    LED_L8B0_EX_ABV_T                ex_abv;                  // 0x00d4
    LED_L8B0_SG_L_H_T                sg_l_h;                  // 0x00d8
    LED_L8B0_WB_G_GAIN_OFFSET_T      wb_g_gain_offset;        // 0x00dc
    LED_L8B0_UMASK_COEFF_T           umask_coeff;             // 0x00e0
    LED_L8B0_SF_EN_T                 sf_en;                   // 0x00e4
    LED_L8B0_UMASK_COARING_T         umask_coaring;           // 0x00e8
    LED_L8B0_WB_B_GAIN_OFFSET_T      wb_b_gain_offset;        // 0x00ec
    UINT32                  reserved0;               // 0x00f0
    LED_L8B0_UMASK_GAIN_T            umask_gain;              // 0x00f4
    LED_L8B0_BV_I2C_W_EN_DATA_T      bv_i2c_w_en_data;        // 0x00f8
    LED_L8B0_HIST_INTR_CLR_T         hist_intr_clr;           // 0x00fc
    LED_L8B0_HSB_VSB_B1_T            hsb_vsb_b1;              // 0x0100
    LED_L8B0_HNB_VNB_B1_T            hnb_vnb_b1;              // 0x0104
    LED_L8B0_PWM_VALUE_T             pwm_value;               // 0x0108
    LED_L8B0_SCLK_T1_T               sclk_t1;                 // 0x010c
    LED_L8B0_SCLK_T2_T               sclk_t2;                 // 0x0110
    LED_L8B0_SCLK_T3_T               sclk_t3;                 // 0x0114
    LED_L8B0_SCLK_T4_T               sclk_t4;                 // 0x0118
    LED_L8B0_SPI_MASTER_CFG0_T       spi_master_cfg0;         // 0x011c
    UINT32                  reserved1;               // 0x0120
    LED_L8B0_SPI_IDC01_T             spi_idc01;               // 0x0124
    LED_L8B0_SPI_IDC23_T             spi_idc23;               // 0x0128
    LED_L8B0_SPI_CMD01_T             spi_cmd01;               // 0x012c
    LED_L8B0_SPI_CMD23_T             spi_cmd23;               // 0x0130
    LED_L8B0_SPI_CMD_NUM_T           spi_cmd_num;             // 0x0134
    LED_L8B0_VSYNC_T5_T              vsync_t5;                // 0x0138
    UINT32                  reserved2[2];            // 0x013c~0x0140
    LED_L8B0_M0_SP_T                 m0_sp;                   // 0x0144
    LED_L8B0_M1_SP_T                 m1_sp;                   // 0x0148
    LED_L8B0_M2_SP_T                 m2_sp;                   // 0x014c
    LED_L8B0_M3_SP_T                 m3_sp;                   // 0x0150
    LED_L8B0_M0_HNB_T                m0_hnb;                  // 0x0154
    LED_L8B0_M1_HNB_T                m1_hnb;                  // 0x0158
    LED_L8B0_M2_HNB_T                m2_hnb;                  // 0x015c
    LED_L8B0_M3_HNB_T                m3_hnb;                  // 0x0160
    LED_L8B0_M0_VNB_T                m0_vnb;                  // 0x0164
    LED_L8B0_M1_VNB_T                m1_vnb;                  // 0x0168
    LED_L8B0_M2_VNB_T                m2_vnb;                  // 0x016c
    LED_L8B0_M3_VNB_T                m3_vnb;                  // 0x0170
    LED_L8B0_SPI_CH_MASK_T           spi_ch_mask;             // 0x0174
    LED_L8B0_REVERSE_MODE_T          reverse_mode;            // 0x0178
    UINT32                  reserved3[2];            // 0x017c~0x0180
    LED_L8B0_SCANNING_STATUS_T       scanning_status;         // 0x0184
    LED_L8B0_BV_I2C_RD_EN_T          bv_i2c_rd_en;            // 0x0188
    LED_L8B0_BV_I2C_RD_ADDR_T        bv_i2c_rd_addr;          // 0x018c
    LED_L8B0_BV_I2C_RD_DATA_T        bv_i2c_rd_data;          // 0x0190
    LED_L8B0_BLU_IF_MODE_T           blu_if_mode;             // 0x0194
    LED_L8B0_BLE_HSB_VSB_T           ble_hsb_vsb;             // 0x0198
    LED_L8B0_BLE_HNB_VNB_T           ble_hnb_vnb;             // 0x019c
    UINT32                  reserved4[3];            // 0x01a0~0x01a8
    LED_L8B0_SPI_VS_DELAY_T          spi_vs_delay;            // 0x01ac
    LED_L8B0_BLU_VS_MODE_T           blu_vs_mode;             // 0x01b0
    LED_L8B0_I2C_SLAVE_ADDR_T        i2c_slave_addr;          // 0x01b4
    UINT32                  reserved5[18];           // 0x01b8~0x01fc
    LED_L8B0_HSB_VSB_B2_T            hsb_vsb_b2;              // 0x0200
    LED_L8B0_HNB_VNB_B2_T            hnb_vnb_b2;              // 0x0204
    LED_L8B0_VERSION_T               version;                 // 0x0208
    UINT32                  reserved6;               // 0x020c
    LED_L8B0_RUN_STALL_T             run_stall;               // 0x0210
    LED_L8B0_CMEM_ADDR_CLR_T         cmem_addr_clr;           // 0x0214
    LED_L8B0_WAVG_HCOEFF_T           wavg_hcoeff;             // 0x0218
    LED_L8B0_WAVG_VCOEFF_T           wavg_vcoeff;             // 0x021c
    LED_L8B0_SBI_HCOEFF_T            sbi_hcoeff;              // 0x0220
    LED_L8B0_SBI_VCOEFF_T            sbi_vcoeff;              // 0x0224
    LED_L8B0_PC_LUT_A_T              pc_lut_a;                // 0x0228
    LED_L8B0_PC_LUT_B_T              pc_lut_b;                // 0x022c
    LED_L8B0_PC_LUT_C_T              pc_lut_c;                // 0x0230
    LED_L8B0_PC_LUT_D_T              pc_lut_d;                // 0x0234
    LED_L8B0_BV_UPPER_LUT_T          bv_upper_lut;            // 0x0238
    LED_L8B0_BV_LOWER_LUT_T          bv_lower_lut;            // 0x023c
    LED_L8B0_INT_MASK_T              int_mask;                // 0x0240
    LED_L8B0_PDEBUG_EN_T             pdebug_en;               // 0x0244
    LED_L8B0_PDEBUG_STATUS_T         pdebug_status;           // 0x0248
    LED_L8B0_PDEBUG_PC_T             pdebug_pc;               // 0x024c
    LED_L8B0_PDEBUG_DATA_T           pdebug_data;             // 0x0250
    LED_L8B0_BV_INTR_CLR_T           bv_intr_clr;             // 0x0254
    LED_L8B0_LINE_INTR_CLR_T         line_intr_clr;           // 0x0258
    LED_L8B0_LINE_INTR_COUNTER_T     line_intr_counter;       // 0x025c
    LED_L8B0_SYNC_INT_POL_T          sync_int_pol;            // 0x0260
    LED_L8B0_BLU_BV_INTR_CLR_T       blu_bv_intr_clr;         // 0x0264
    LED_L8B0_IPC_INT_EN_T            ipc_int_en;              // 0x0268
    LED_L8B0_IPC_INT_STATUS_T        ipc_int_status;          // 0x026c
    LED_L8B0_IPC_INT_RAW_STATUS_T    ipc_int_raw_status;      // 0x0270
    LED_L8B0_IPC_INT_CLR_T           ipc_int_clr;             // 0x0274
    LED_L8B0_GENERAL_REG_T           general_reg;             // 0x0278
    UINT32                  reserved7[61];           // 0x027c~0x036c
    LED_L8B0_EXT_INTR_EN_T           ext_intr_en;             // 0x0370
    LED_L8B0_EXT_INTR_STATUS_T       ext_intr_status;         // 0x0374
    LED_L8B0_EXT_INTR_RAW_STATUS_T   ext_intr_raw_status;     // 0x0378
    LED_L8B0_EXT_INTR_CLR_T          ext_intr_clr;            // 0x037c
    LED_L8B0_IPC_MEM_T               ipc_mem[32];             // 0x0380~0x03fc
} LED_L8B0_REG_T;

/*
 * @{
 * Naming for register pointer.
 * gpRealRegLED_L8B0 : real register of LED.
 * gpRegLED_L8B0     : shadow register.
 *
 * @def LED_L8B0_RdFL: Read  FLushing : Shadow <- Real.
 * @def LED_L8B0_WrFL: Write FLushing : Shadow -> Real.
 * @def LED_L8B0_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def LED_L8B0_Wr  : Write whole register(UINT32) from Shadow register.
 * @def LED_L8B0_Rd01 ~ LED_L8B0_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def LED_L8B0_Wr01 ~ LED_L8B0_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define LED_L8B0_RdFL(_r)			((gpRegLED_L8B0->_r)=(gpRealRegLED_L8B0->_r))
#define LED_L8B0_WrFL(_r)			((gpRealRegLED_L8B0->_r)=(gpRegLED_L8B0->_r))

#define LED_L8B0_Rd(_r)				*((UINT32*)(&(gpRegLED_L8B0->_r)))
#define LED_L8B0_Wr(_r,_v)			((LED_L8B0_Rd(_r))=((UINT32)(_v)))

#define LED_L8B0_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
								} while(0)

#define LED_L8B0_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
								} while(0)

#define LED_L8B0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
								} while(0)

#define LED_L8B0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
								} while(0)

#define LED_L8B0_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
								} while(0)

#define LED_L8B0_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
								} while(0)

#define LED_L8B0_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
								} while(0)

#define LED_L8B0_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
								} while(0)

#define LED_L8B0_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
								} while(0)

#define LED_L8B0_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
								} while(0)

#define LED_L8B0_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
								} while(0)

#define LED_L8B0_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
									(_v12) = (gpRegLED_L8B0->_r._f12);				\
								} while(0)

#define LED_L8B0_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
									(_v12) = (gpRegLED_L8B0->_r._f12);				\
									(_v13) = (gpRegLED_L8B0->_r._f13);				\
								} while(0)

#define LED_L8B0_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
									(_v12) = (gpRegLED_L8B0->_r._f12);				\
									(_v13) = (gpRegLED_L8B0->_r._f13);				\
									(_v14) = (gpRegLED_L8B0->_r._f14);				\
								} while(0)

#define LED_L8B0_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
									(_v12) = (gpRegLED_L8B0->_r._f12);				\
									(_v13) = (gpRegLED_L8B0->_r._f13);				\
									(_v14) = (gpRegLED_L8B0->_r._f14);				\
									(_v15) = (gpRegLED_L8B0->_r._f15);				\
								} while(0)

#define LED_L8B0_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (gpRegLED_L8B0->_r._f01);				\
									(_v02) = (gpRegLED_L8B0->_r._f02);				\
									(_v03) = (gpRegLED_L8B0->_r._f03);				\
									(_v04) = (gpRegLED_L8B0->_r._f04);				\
									(_v05) = (gpRegLED_L8B0->_r._f05);				\
									(_v06) = (gpRegLED_L8B0->_r._f06);				\
									(_v07) = (gpRegLED_L8B0->_r._f07);				\
									(_v08) = (gpRegLED_L8B0->_r._f08);				\
									(_v09) = (gpRegLED_L8B0->_r._f09);				\
									(_v10) = (gpRegLED_L8B0->_r._f10);				\
									(_v11) = (gpRegLED_L8B0->_r._f11);				\
									(_v12) = (gpRegLED_L8B0->_r._f12);				\
									(_v13) = (gpRegLED_L8B0->_r._f13);				\
									(_v14) = (gpRegLED_L8B0->_r._f14);				\
									(_v15) = (gpRegLED_L8B0->_r._f15);				\
									(_v16) = (gpRegLED_L8B0->_r._f16);				\
								} while(0)


#define LED_L8B0_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
								} while(0)

#define LED_L8B0_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
								} while(0)

#define LED_L8B0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
								} while(0)

#define LED_L8B0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
								} while(0)

#define LED_L8B0_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
								} while(0)

#define LED_L8B0_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
								} while(0)

#define LED_L8B0_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
								} while(0)

#define LED_L8B0_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
								} while(0)

#define LED_L8B0_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
								} while(0)

#define LED_L8B0_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
								} while(0)

#define LED_L8B0_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
								} while(0)

#define LED_L8B0_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
									(gpRegLED_L8B0->_r._f12) = (_v12);				\
								} while(0)

#define LED_L8B0_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
									(gpRegLED_L8B0->_r._f12) = (_v12);				\
									(gpRegLED_L8B0->_r._f13) = (_v13);				\
								} while(0)

#define LED_L8B0_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
									(gpRegLED_L8B0->_r._f12) = (_v12);				\
									(gpRegLED_L8B0->_r._f13) = (_v13);				\
									(gpRegLED_L8B0->_r._f14) = (_v14);				\
								} while(0)

#define LED_L8B0_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
									(gpRegLED_L8B0->_r._f12) = (_v12);				\
									(gpRegLED_L8B0->_r._f13) = (_v13);				\
									(gpRegLED_L8B0->_r._f14) = (_v14);				\
									(gpRegLED_L8B0->_r._f15) = (_v15);				\
								} while(0)

#define LED_L8B0_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(gpRegLED_L8B0->_r._f01) = (_v01);				\
									(gpRegLED_L8B0->_r._f02) = (_v02);				\
									(gpRegLED_L8B0->_r._f03) = (_v03);				\
									(gpRegLED_L8B0->_r._f04) = (_v04);				\
									(gpRegLED_L8B0->_r._f05) = (_v05);				\
									(gpRegLED_L8B0->_r._f06) = (_v06);				\
									(gpRegLED_L8B0->_r._f07) = (_v07);				\
									(gpRegLED_L8B0->_r._f08) = (_v08);				\
									(gpRegLED_L8B0->_r._f09) = (_v09);				\
									(gpRegLED_L8B0->_r._f10) = (_v10);				\
									(gpRegLED_L8B0->_r._f11) = (_v11);				\
									(gpRegLED_L8B0->_r._f12) = (_v12);				\
									(gpRegLED_L8B0->_r._f13) = (_v13);				\
									(gpRegLED_L8B0->_r._f14) = (_v14);				\
									(gpRegLED_L8B0->_r._f15) = (_v15);				\
									(gpRegLED_L8B0->_r._f16) = (_v16);				\
								} while(0)

/* Indexed Register Access.
 *
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed register
 * can hold several data for a 'field_name' specifed by 'index' field of indexed register.
 * When writing an 3rd data for given 'field_name' register, you need to set 'rw' = 0, 'index' = 2,
 * and 'load' = 0.
 *
 * ASSUMPTION
 * For Writing indexed register load bit
 *
 * parameter list
 * _r     : name of register
 * _lname : name of load  bit field	: shall be 0 after macro executed.
 * _rwname: name of rw    bit field : shall be 0 after LED_L8B0_Wind(), 1 for LED_L8B0_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * LED_L8B0_Rind : General indexed register Read.(
 * LED_L8B0_Wind : General indexed register Read.
 *
 * LED_L8B0_Ridx : For 'index', 'rw', 'load' field name
 * LED_L8B0_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define LED_L8B0_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								LED_L8B0_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								LED_L8B0_WrFL(_r);									\
								LED_L8B0_RdFL(_r);									\
								LED_L8B0_Rd01(_r,_fname,_fval);						\
							} while (0)

#define LED_L8B0_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				LED_L8B0_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define LED_L8B0_Ridx(_r, _ival, _fname, _fval)	LED_L8B0_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define LED_L8B0_Widx(_r, _ival, _fname, _fval)	LED_L8B0_Wind(_r,load,rw,index,_ival,_fname,_fval)

#endif
/* from 'LG1150-LED-MAN-01 v0.8(Register Manual -20100127).csv' 20100311 00:54:19   대한민국 표준시 by getregs v2.3 */
