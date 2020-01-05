#ifndef _DIMM_REG_h
#define _DIMM_REG_h

typedef struct { // 0x0000
	UINT32
	vsb                 : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	hsb                 : 10;  // 25:16   16
} LED_L8AX_HSB_VSB_T;

typedef struct { // 0x0004
	UINT32
	hnb                 :  6,  // 5:0     0
	                    :  2,  // 7:6     6
	vnb                 :  5;  // 12:8    8
} LED_L8AX_HNB_VNB_T;

typedef struct { // 0x0008
	UINT32
	pb_en               :  1,  // 0       0
	demo_en             :  1,  // 1       1
	apf_en              :  1,  // 2       2
	sbi2rgb_en          :  1,  // 3       3
	sbi_dis             :  1;  // 4       4
} LED_L8AX_DBG_CTRL_T;

typedef struct { // 0x000c
	UINT32
	pat_en              :  3;  // 2:0     0
} LED_L8AX_PAT_EN_T;

typedef struct { // 0x0010
	UINT32
	pat_val             : 10;  // 9:0     0
} LED_L8AX_PAT_VALUE_T;

typedef struct { // 0x0014
	UINT32
	pat_h_min           : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	pat_h_max           : 10;  // 25:16   16
} LED_L8AX_PAT_H_MIN_MAX_T;

typedef struct { // 0x0018
	UINT32
	pat_v_min           : 11,  // 10:0    0
	                    :  5,  // 15:11   11
	pat_v_max           : 11;  // 26:16   16
} LED_L8AX_PAT_V_MIN_MAX_T;

typedef struct { // 0x001c
	UINT32
	pat_h_ppf           :  8,  // 7:0     0
	pat_v_ppf           :  8;  // 15:8    8
} LED_L8AX_PAT_HV_PPF_T;

typedef struct { // 0x0020
	UINT32
	wavg_en             :  1;  // 0       0
} LED_L8AX_WAVG_EN_T;

typedef struct { // 0x0024
	UINT32
	wavg_opt            :  8;  // 7:0     0
} LED_L8AX_MAX_OPT_T;

typedef struct { // 0x0028
	UINT32
	blk_max_mode        :  1;  // 0       0
} LED_L8AX_BLK_MAX_MODE_T;

typedef struct { // 0x002c
	UINT32
	nlf_th              : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	limit               : 10;  // 25:16   16
} LED_L8AX_NLF_TH_T;

typedef struct { // 0x0030
	UINT32
	a_para              :  9;  // 8:0     0
} LED_L8AX_A_PARA_T;

typedef struct { // 0x0034
	UINT32
	sc_mag_th           : 10;  // 9:0     0
} LED_L8AX_SC_MAG_TH_T;

typedef struct { // 0x0038
	UINT32
	sc_mag_gn           :  8;  // 7:0     0
} LED_L8AX_SC_MAG_GN_T;

typedef struct { // 0x003c
	UINT32
	sc_mag_info         : 10;  // 9:0     0
} LED_L8AX_SC_MAG_INFO_T;

typedef struct { // 0x0040
	UINT32
	sc_adj_en           :  1;  // 0       0
} LED_L8AX_SC_ADJ_EN_T;

typedef struct { // 0x0044
	UINT32
	md_adj_en           :  1;  // 0       0
} LED_L8AX_MD_ADJ_EN_T;

typedef struct { // 0x0048
	UINT32
	sc_tdif_th          : 10;  // 9:0     0
} LED_L8AX_SC_TDIF_TH_T;

typedef struct { // 0x004c
	UINT32
	sc_tdif_gn          :  8;  // 7:0     0
} LED_L8AX_SC_TDIF_GN_T;

typedef struct { // 0x0050
	UINT32
	lrz_offset          :  8;  // 7:0     0
} LED_L8AX_LRZ_OFFSET_T;

typedef struct { // 0x0054
	UINT32
	lrz_gain            :  8;  // 7:0     0
} LED_L8AX_LRZ_GAIN_T;

typedef struct { // 0x0058
	UINT32
	pixel_gain_p5       :  2;  // 1:0     0
} LED_L8AX_PIXEL_GAIN_P5_T;

typedef struct { // 0x005c
	UINT32
	iwb_r_gain          : 11;  // 10:0    0
} LED_L8AX_IWB_R_GAIN_T;

typedef struct { // 0x0060
	UINT32
	iwb_g_gain          : 11;  // 10:0    0
} LED_L8AX_IWB_G_GAIN_T;

typedef struct { // 0x0064
	UINT32
	iwb_b_gain          : 11;  // 10:0    0
} LED_L8AX_IWB_B_GAIN_T;

typedef struct { // 0x0068
	UINT32
	iwb_r_offset        : 10;  // 9:0     0
} LED_L8AX_IWB_R_OFFSET_T;

typedef struct { // 0x006c
	UINT32
	iwb_g_offset        : 10;  // 9:0     0
} LED_L8AX_IWB_G_OFFSET_T;

typedef struct { // 0x0070
	UINT32
	iwb_b_offset        : 10;  // 9:0     0
} LED_L8AX_IWB_B_OFFSET_T;

typedef struct { // 0x0074
	UINT32
	nlf_mode            :  1;  // 0       0
} LED_L8AX_NLF_MODE_T;

typedef struct { // 0x0078
	UINT32
	htab_en             :  2,  // 1:0     0
	vtab_en             :  2;  // 3:2     2
} LED_L8AX_NLF_TAB_EN_T;

typedef struct { // 0x007c
	UINT32
	apl                 : 10;  // 9:0     0
} LED_L8AX_APL_T;

typedef struct { // 0x0080
	UINT32
	bv_sel              :  1;  // 0       0
} LED_L8AX_BLU_BV_SEL_T;

typedef struct { // 0x0084
	UINT32
	max_opt_mode        :  1;  // 0       0
} LED_L8AX_MAX_OPT_MODE_T;

typedef struct { // 0x0088
	UINT32
	max_opt_1           :  8,  // 7:0     0
	max_opt_0           :  8;  // 15:8    8
} LED_L8AX_MAX_OPT_0_1_T;

typedef struct { // 0x008c
	UINT32
	level_th            : 10;  // 9:0     0
} LED_L8AX_LEVEL_TH_T;

typedef struct { // 0x0090
	UINT32
	num_th              : 12,  // 11:0    0
	                    :  4,  // 15:12   12
	num_bit_sel         :  3;  // 18:16   16
} LED_L8AX_NUMBER_TH_T;

typedef struct { // 0x0094
	UINT32
	gbl                 : 10;  // 9:0     0
} LED_L8AX_GBL_T;

typedef struct { // 0x0098
	UINT32
	comp_en             :  1;  // 0       0
} LED_L8AX_PC_EN_T;

typedef struct { // 0x009c
	UINT32
	gain_prec_nor       :  4,  // 3:0     0
	gain_prec_demo      :  4;  // 7:4     4
} LED_L8AX_PC_GAIN_PREC_T;

typedef struct { // 0x00a0
	UINT32
	pc_in_sel           :  2;  // 1:0     0
} LED_L8AX_PC_MODE_SEL_T;

typedef struct { // 0x00a4
	UINT32
	pc_sbi_in_sel       :  1;  // 0       0
} LED_L8AX_PC_SBI_IN_SEL_T;

typedef struct { // 0x00a8
	UINT32
	sbi_i2c             : 10;  // 9:0     0
} LED_L8AX_PC_SBI_IN_VALUE_T;

typedef struct { // 0x00ac
	UINT32
	pc_gain_demo        :  2;  // 1:0     0
} LED_L8AX_PC_GAIN_DEMO_T;

typedef struct { // 0x00b0
	UINT32
	vsync_neg           :  1,  // 0       0
	hsync_neg           :  1;  // 1       1
} LED_L8AX_OUT_SYNC_POL_T;

typedef struct { // 0x00b4
	UINT32
	lum_demo            : 10;  // 9:0     0
} LED_L8AX_LUM_DEMO_T;

typedef struct { // 0x00b8
	UINT32
	dithe_en            :  1,  // 0       0
	temp_en             :  1;  // 1       1
} LED_L8AX_DITHER_T;

typedef struct { // 0x00bc
	UINT32
	dual_lvds           :  1,  // 0       0
	add_pixel           :  1;  // 1       1
} LED_L8AX_VIN_CONF_T;

typedef struct { // 0x00c0
	UINT32
	abv_cmp_value       : 10;  // 9:0     0
} LED_L8AX_SCAN_TH_T;

typedef struct { // 0x00c4
	UINT32
	bv_mux_ctrl         :  3;  // 2:0     0
} LED_L8AX_BV_MUX_CTRL_T;

typedef struct { // 0x00c8
	UINT32
	edge_type           :  1,  // 0       0
	edge_lit            :  1;  // 1       1
} LED_L8AX_BLU_TYPE_T;

typedef struct { // 0x00cc
	UINT32
	minl                : 10;  // 9:0     0
} LED_L8AX_MINL_T;

typedef struct { // 0x00d0
	UINT32
	lut_mode            :  2;  // 1:0     0
} LED_L8AX_LUT_MODE_T;

typedef struct { // 0x00d4
	UINT32
	ex_abv              : 10;  // 9:0     0
} LED_L8AX_EX_ABV_T;

typedef struct { // 0x00d8
	UINT32
	sg_l                :  8,  // 7:0     0
	sg_h                :  8;  // 15:8    8
} LED_L8AX_SG_L_H_T;

typedef struct { // 0x00dc
	UINT32
	mark_en             :  1;  // 0       0
} LED_L8AX_MARK_EN_T;

typedef struct { // 0x00e0
	UINT32
	umask_coeff         : 10;  // 9:0     0
} LED_L8AX_UMASK_COEFF_T;

typedef struct { // 0x00e4
	UINT32
	umask_en            :  1;  // 0       0
} LED_L8AX_UMASK_EN_T;

typedef struct { // 0x00e8
	UINT32
	coaring_n           : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	coaring_p           : 10;  // 25:16   16
} LED_L8AX_UMASK_COARING_T;

typedef struct { // 0x00f4
	UINT32
	gain_n              : 12,  // 11:0    0
	                    :  4,  // 15:12   12
	gain_p              : 12;  // 27:16   16
} LED_L8AX_UMASK_GAIN_T;

typedef struct { // 0x00f8
	UINT32
	blu_i2c_wr_en       :  1;  // 0       0
} LED_L8AX_BV_I2C_WR_EN_T;

typedef struct { // 0x00fc
	UINT32
	bv_wdata            : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	bv_addr             : 11;  // 26:16   16
} LED_L8AX_BV_I2C_WR_T;

typedef struct { // 0x0100
	UINT32
	hsb                 : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	vsb                 : 10;  // 25:16   16
} LED_L8AX_HSB_VSB_B1_T;

typedef struct { // 0x0104
	UINT32
	hnb                 :  6,  // 5:0     0
	                    :  2,  // 7:6     6
	vnb                 :  5;  // 12:8    8
} LED_L8AX_HNB_VNB_B1_T;

typedef struct { // 0x0108
	UINT32
	pwm_value           : 10;  // 9:0     0
} LED_L8AX_PWM_VALUE_T;

typedef struct { // 0x010c
	UINT32
	sclk_t1             :  9;  // 8:0     0
} LED_L8AX_SCLK_T1_T;

typedef struct { // 0x0110
	UINT32
	sclk_t2             :  9;  // 8:0     0
} LED_L8AX_SCLK_T2_T;

typedef struct { // 0x0114
	UINT32
	sclk_t3             :  9;  // 8:0     0
} LED_L8AX_SCLK_T3_T;

typedef struct { // 0x0118
	UINT32
	sclk_t4             :  9;  // 8:0     0
} LED_L8AX_SCLK_T4_T;

typedef struct { // 0x011c
	UINT32
	cpha                :  1,  // 0       0
	cpol                :  1,  // 1       1
	spi_width           :  2;  // 3:2     2
} LED_L8AX_SPI_MASTER_CFG_T;

typedef struct { // 0x0124
	UINT32
	m0_id               : 16;  // 15:0    0
} LED_L8AX_M0_ID_T;

typedef struct { // 0x0128
	UINT32
	m1_id               : 16;  // 15:0    0
} LED_L8AX_M1_ID_T;

typedef struct { // 0x012c
	UINT32
	m2_id               : 16;  // 15:0    0
} LED_L8AX_M2_ID_T;

typedef struct { // 0x0130
	UINT32
	m3_id               : 16;  // 15:0    0
} LED_L8AX_M3_ID_T;

typedef struct { // 0x0134
	UINT32
	spi_cmd             : 16;  // 15:0    0
} LED_L8AX_SPI_CMD_T;

typedef struct { // 0x0138
	UINT32
	sclk_t5             :  8;  // 7:0     0
} LED_L8AX_VSYNC_T5_T;

typedef struct { // 0x013c
	UINT32
	spi_device_id       :  8;  // 7:0     0
} LED_L8AX_SPI_SLAVE_ID_T;

typedef struct { // 0x0140
	UINT32
	cpha                :  1,  // 0       0
	cpol                :  1;  // 1       1
} LED_L8AX_SPI_SLAVE_CFG_T;

typedef struct { // 0x0144
	UINT32
	m0_sp               : 11;  // 10:0    0
} LED_L8AX_M0_SP_T;

typedef struct { // 0x0148
	UINT32
	m1_sp               : 11;  // 10:0    0
} LED_L8AX_M1_SP_T;

typedef struct { // 0x014c
	UINT32
	m2_sp               : 11;  // 10:0    0
} LED_L8AX_M2_SP_T;

typedef struct { // 0x0150
	UINT32
	m3_sp               : 11;  // 10:0    0
} LED_L8AX_M3_SP_T;

typedef struct { // 0x0154
	UINT32
	m0_hnb              :  6;  // 5:0     0
} LED_L8AX_M0_HNB_T;

typedef struct { // 0x0158
	UINT32
	m1_hnb              :  6;  // 5:0     0
} LED_L8AX_M1_HNB_T;

typedef struct { // 0x015c
	UINT32
	m2_hnb              :  6;  // 5:0     0
} LED_L8AX_M2_HNB_T;

typedef struct { // 0x0160
	UINT32
	m3_hnb              :  6;  // 5:0     0
} LED_L8AX_M3_HNB_T;

typedef struct { // 0x0164
	UINT32
	m0_vnb              :  5;  // 4:0     0
} LED_L8AX_M0_VNB_T;

typedef struct { // 0x0168
	UINT32
	m1_vnb              :  5;  // 4:0     0
} LED_L8AX_M1_VNB_T;

typedef struct { // 0x016c
	UINT32
	m2_vnb              :  5;  // 4:0     0
} LED_L8AX_M2_VNB_T;

typedef struct { // 0x0170
	UINT32
	m3_vnb              :  5;  // 4:0     0
} LED_L8AX_M3_VNB_T;

typedef struct { // 0x0174
	UINT32
	spi_ch_mask         :  4;  // 3:0     0
} LED_L8AX_SPI_CH_MASK_T;

typedef struct { // 0x0178
	UINT32
	reverse_mode_en     :  1;  // 0       0
} LED_L8AX_REVERSE_MODE_T;

typedef struct { // 0x017c
	UINT32
	calib_en            :  1;  // 0       0
} LED_L8AX_CALIB_EN_T;

typedef struct { // 0x0180
	UINT32
	calb_data_num       : 11,  // 10:0    0
	                    :  1,  // 11      11
	calib_rdy           :  1,  // 12      12
	calib_err           :  3;  // 15:13   13
} LED_L8AX_CALIB_STATUS_T;

typedef struct { // 0x0188
	UINT32
	bv_i2c_rd_en        :  1;  // 0       0
} LED_L8AX_BV_I2C_RD_EN_T;

typedef struct { // 0x018c
	UINT32
	bv_i2c_rd_addr      : 12;  // 11:0    0
} LED_L8AX_BV_I2C_RD_ADDR_T;

typedef struct { // 0x0190
	UINT32
	bv_i2c_rd_data      : 10;  // 9:0     0
} LED_L8AX_BV_I2C_RD_DATA_T;

typedef struct { // 0x01b0
	UINT32
	vs_mode             :  2,  // 1:0     0
	vs_in_pol           :  1,  // 2       2
	vs_mode_en          :  1;  // 3       3
} LED_L8AX_BLU_VS_MODE_T;

typedef struct { // 0x0200
	UINT32
	vsb                 : 10,  // 9:0     0
	                    :  6,  // 15:10   10
	hsb                 : 10;  // 25:16   16
} LED_L8AX_HSB_VSB_B2_T;

typedef struct { // 0x0204
	UINT32
	hnb                 :  6,  // 5:0     0
	                    :  2,  // 7:6     6
	vnb                 :  5;  // 12:8    8
} LED_L8AX_HNB_VNB_B2_T;

typedef struct { // 0x0208
	UINT32
	boot_rom_address_clr :  1;  // 0       0
} LED_L8AX_BOOT_ROM_ADDR_CLR_T;

typedef struct { // 0x020c
	UINT32
	boot_rom_data       : 32;  // 31:0    0
} LED_L8AX_BOOT_ROM_DATA_T;

typedef struct { // 0x0210
	UINT32
	run_stall           :  1;  // 0       0
} LED_L8AX_RUN_STALL_T;

typedef struct { // 0x0214
	UINT32
	mem_addr_clr        :  1;  // 0       0
} LED_L8AX_CMEM_ADDR_CLR_T;

typedef struct { // 0x0218
	UINT32
	wavg_hcoeff         :  8;  // 7:0     0
} LED_L8AX_WAVG_HCOEFF_T;

typedef struct { // 0x021c
	UINT32
	wavg_vcoeff         :  8;  // 7:0     0
} LED_L8AX_WAVG_VCOEFF_T;

typedef struct { // 0x0220
	UINT32
	sbi_hcoeff          : 10;  // 9:0     0
} LED_L8AX_SBI_HCOEFF_T;

typedef struct { // 0x0224
	UINT32
	sbi_vcoeff          : 10;  // 9:0     0
} LED_L8AX_SBI_VCOEFF_T;

typedef struct { // 0x0228
	UINT32
	pc_coeff_a          : 10;  // 9:0     0
} LED_L8AX_PC_LUT_A_T;

typedef struct { // 0x022c
	UINT32
	pc_lut_b            : 10;  // 9:0     0
} LED_L8AX_PC_LUT_B_T;

typedef struct { // 0x0230
	UINT32
	pc_lut_c            : 10;  // 9:0     0
} LED_L8AX_PC_LUT_C_T;

typedef struct { // 0x0234
	UINT32
	pc_lut_d            : 10;  // 9:0     0
} LED_L8AX_PC_LUT_D_T;

typedef struct { // 0x0238
	UINT32
	bv_upper_lut        : 10;  // 9:0     0
} LED_L8AX_BV_UPPER_LUT_T;

typedef struct { // 0x023c
	UINT32
	bv_lower_lut        : 10;  // 9:0     0
} LED_L8AX_BV_LOWER_LUT_T;

typedef struct { // 0x0240
	UINT32
	int_mask            : 11;  // 10:0    0
} LED_L8AX_INT_MASK_T;

typedef struct { // 0x0244
	UINT32
	pdebug_en           :  1;  // 0       0
} LED_L8AX_PDEBUG_EN_T;

typedef struct { // 0x0248
	UINT32
	pdebug_status       :  8;  // 7:0     0
} LED_L8AX_PDEBUG_STATUS_T;

typedef struct { // 0x024c
	UINT32
	pdebug_pc           : 32;  // 31:0    0
} LED_L8AX_PDEBUG_PC_T;

typedef struct { // 0x0250
	UINT32
	pdebug_data         : 32;  // 31:0    0
} LED_L8AX_PDEBUG_DATA_T;

typedef struct { // 0x0254
	UINT32
	bv_intr_clr         :  1;  // 0       0
} LED_L8AX_BV_INTR_CLR_T;

typedef struct { // 0x0258
	UINT32
	line_intr_clr       :  1;  // 0       0
} LED_L8AX_LINE_INTR_CLR_T;

typedef struct { // 0x025c
	UINT32
	line_inter_counter  : 11;  // 10:0    0
} LED_L8AX_LINE_INTR_COUNTER_T;

typedef struct { // 0x0370
	UINT32
	ext_intr_en         : 32;  // 31:0    0
} LED_L8AX_EXT_INTR_EN_T;

typedef struct { // 0x0374
	UINT32
	ext_intr_status     : 32;  // 31:0    0
} LED_L8AX_EXT_INTR_STATUS_T;

typedef struct { // 0x0378
	UINT32
	ext_intr_raw_status : 32;  // 31:0    0
} LED_L8AX_EXT_INTR_RAW_STATUS_T;

typedef struct { // 0x037c
	UINT32
	ext_intr_clr        : 32;  // 31:0    0
} LED_L8AX_EXT_INTR_CLR_T;

typedef struct { // 0x0380
	UINT32
	ipc_mem_rw          :  8,  // 7:0     0
	ipc_mem_ro          : 24;  // 31:8    8
} LED_L8AX_IPC_MEM_T;

typedef struct {
    LED_L8AX_HSB_VSB_T               hsb_vsb;                 // 0x0000
    LED_L8AX_HNB_VNB_T               hnb_vnb;                 // 0x0004
    LED_L8AX_DBG_CTRL_T              dbg_ctrl;                // 0x0008
    LED_L8AX_PAT_EN_T                pat_en;                  // 0x000c
    LED_L8AX_PAT_VALUE_T             pat_value;               // 0x0010
    LED_L8AX_PAT_H_MIN_MAX_T         pat_h_min_max;           // 0x0014
    LED_L8AX_PAT_V_MIN_MAX_T         pat_v_min_max;           // 0x0018
    LED_L8AX_PAT_HV_PPF_T            pat_hv_ppf;              // 0x001c
    LED_L8AX_WAVG_EN_T               wavg_en;                 // 0x0020
    LED_L8AX_MAX_OPT_T               max_opt;                 // 0x0024
    LED_L8AX_BLK_MAX_MODE_T          blk_max_mode;            // 0x0028
    LED_L8AX_NLF_TH_T                nlf_th;                  // 0x002c
    LED_L8AX_A_PARA_T                a_para;                  // 0x0030
    LED_L8AX_SC_MAG_TH_T             sc_mag_th;               // 0x0034
    LED_L8AX_SC_MAG_GN_T             sc_mag_gn;               // 0x0038
    LED_L8AX_SC_MAG_INFO_T           sc_mag_info;             // 0x003c
    LED_L8AX_SC_ADJ_EN_T             sc_adj_en;               // 0x0040
    LED_L8AX_MD_ADJ_EN_T             md_adj_en;               // 0x0044
    LED_L8AX_SC_TDIF_TH_T            sc_tdif_th;              // 0x0048
    LED_L8AX_SC_TDIF_GN_T            sc_tdif_gn;              // 0x004c
    LED_L8AX_LRZ_OFFSET_T            lrz_offset;              // 0x0050
    LED_L8AX_LRZ_GAIN_T              lrz_gain;                // 0x0054
    LED_L8AX_PIXEL_GAIN_P5_T         pixel_gain_p5;           // 0x0058
    LED_L8AX_IWB_R_GAIN_T            iwb_r_gain;              // 0x005c
    LED_L8AX_IWB_G_GAIN_T            iwb_g_gain;              // 0x0060
    LED_L8AX_IWB_B_GAIN_T            iwb_b_gain;              // 0x0064
    LED_L8AX_IWB_R_OFFSET_T          iwb_r_offset;            // 0x0068
    LED_L8AX_IWB_G_OFFSET_T          iwb_g_offset;            // 0x006c
    LED_L8AX_IWB_B_OFFSET_T          iwb_b_offset;            // 0x0070
    LED_L8AX_NLF_MODE_T              nlf_mode;                // 0x0074
    LED_L8AX_NLF_TAB_EN_T            nlf_tab_en;              // 0x0078
    LED_L8AX_APL_T                   apl;                     // 0x007c
    LED_L8AX_BLU_BV_SEL_T            blu_bv_sel;              // 0x0080
    LED_L8AX_MAX_OPT_MODE_T          max_opt_mode;            // 0x0084
    LED_L8AX_MAX_OPT_0_1_T           max_opt_0_1;             // 0x0088
    LED_L8AX_LEVEL_TH_T              level_th;                // 0x008c
    LED_L8AX_NUMBER_TH_T             number_th;               // 0x0090
    LED_L8AX_GBL_T                   gbl;                     // 0x0094
    LED_L8AX_PC_EN_T                 pc_en;                   // 0x0098
    LED_L8AX_PC_GAIN_PREC_T          pc_gain_prec;            // 0x009c
    LED_L8AX_PC_MODE_SEL_T           pc_mode_sel;             // 0x00a0
    LED_L8AX_PC_SBI_IN_SEL_T         pc_sbi_in_sel;           // 0x00a4
    LED_L8AX_PC_SBI_IN_VALUE_T       pc_sbi_in_value;         // 0x00a8
    LED_L8AX_PC_GAIN_DEMO_T          pc_gain_demo;            // 0x00ac
    LED_L8AX_OUT_SYNC_POL_T          out_sync_pol;            // 0x00b0
    LED_L8AX_LUM_DEMO_T              lum_demo;                // 0x00b4
    LED_L8AX_DITHER_T                dither;                  // 0x00b8
    LED_L8AX_VIN_CONF_T              vin_conf;                // 0x00bc
    LED_L8AX_SCAN_TH_T               scan_th;                 // 0x00c0
    LED_L8AX_BV_MUX_CTRL_T           bv_mux_ctrl;             // 0x00c4
    LED_L8AX_BLU_TYPE_T              blu_type;                // 0x00c8
    LED_L8AX_MINL_T                  minl;                    // 0x00cc
    LED_L8AX_LUT_MODE_T              lut_mode;                // 0x00d0
    LED_L8AX_EX_ABV_T                ex_abv;                  // 0x00d4
    LED_L8AX_SG_L_H_T                sg_l_h;                  // 0x00d8
    LED_L8AX_MARK_EN_T               mark_en;                 // 0x00dc
    LED_L8AX_UMASK_COEFF_T           umask_coeff;             // 0x00e0
    LED_L8AX_UMASK_EN_T              umask_en;                // 0x00e4
    LED_L8AX_UMASK_COARING_T         umask_coaring;           // 0x00e8
    UINT32                  reserved1[2];            // 0x00ec~0x00f0
    LED_L8AX_UMASK_GAIN_T            umask_gain;              // 0x00f4
    LED_L8AX_BV_I2C_WR_EN_T          bv_i2c_wr_en;            // 0x00f8
    LED_L8AX_BV_I2C_WR_T             bv_i2c_wr;               // 0x00fc
    LED_L8AX_HSB_VSB_B1_T            hsb_vsb_b1;              // 0x0100
    LED_L8AX_HNB_VNB_B1_T            hnb_vnb_b1;              // 0x0104
    LED_L8AX_PWM_VALUE_T             pwm_value;               // 0x0108
    LED_L8AX_SCLK_T1_T               sclk_t1;                 // 0x010c
    LED_L8AX_SCLK_T2_T               sclk_t2;                 // 0x0110
    LED_L8AX_SCLK_T3_T               sclk_t3;                 // 0x0114
    LED_L8AX_SCLK_T4_T               sclk_t4;                 // 0x0118
    LED_L8AX_SPI_MASTER_CFG_T        spi_master_cfg;          // 0x011c
    UINT32                  reserved2;               // 0x0120
    LED_L8AX_M0_ID_T                 m0_id;                   // 0x0124
    LED_L8AX_M1_ID_T                 m1_id;                   // 0x0128
    LED_L8AX_M2_ID_T                 m2_id;                   // 0x012c
    LED_L8AX_M3_ID_T                 m3_id;                   // 0x0130
    LED_L8AX_SPI_CMD_T               spi_cmd;                 // 0x0134
    LED_L8AX_VSYNC_T5_T              vsync_t5;                // 0x0138
    LED_L8AX_SPI_SLAVE_ID_T          spi_slave_id;            // 0x013c
    LED_L8AX_SPI_SLAVE_CFG_T         spi_slave_cfg;           // 0x0140
    LED_L8AX_M0_SP_T                 m0_sp;                   // 0x0144
    LED_L8AX_M1_SP_T                 m1_sp;                   // 0x0148
    LED_L8AX_M2_SP_T                 m2_sp;                   // 0x014c
    LED_L8AX_M3_SP_T                 m3_sp;                   // 0x0150
    LED_L8AX_M0_HNB_T                m0_hnb;                  // 0x0154
    LED_L8AX_M1_HNB_T                m1_hnb;                  // 0x0158
    LED_L8AX_M2_HNB_T                m2_hnb;                  // 0x015c
    LED_L8AX_M3_HNB_T                m3_hnb;                  // 0x0160
    LED_L8AX_M0_VNB_T                m0_vnb;                  // 0x0164
    LED_L8AX_M1_VNB_T                m1_vnb;                  // 0x0168
    LED_L8AX_M2_VNB_T                m2_vnb;                  // 0x016c
    LED_L8AX_M3_VNB_T                m3_vnb;                  // 0x0170
    LED_L8AX_SPI_CH_MASK_T           spi_ch_mask;             // 0x0174
    LED_L8AX_REVERSE_MODE_T          reverse_mode;            // 0x0178
    LED_L8AX_CALIB_EN_T              calib_en;                // 0x017c
    LED_L8AX_CALIB_STATUS_T          calib_status;            // 0x0180
    UINT32                  reserved3;               // 0x0184
    LED_L8AX_BV_I2C_RD_EN_T          bv_i2c_rd_en;            // 0x0188
    LED_L8AX_BV_I2C_RD_ADDR_T        bv_i2c_rd_addr;          // 0x018c
    LED_L8AX_BV_I2C_RD_DATA_T        bv_i2c_rd_data;          // 0x0190
    UINT32                  reserved4[7];            // 0x0194~0x01ac
    LED_L8AX_BLU_VS_MODE_T           blu_vs_mode;             // 0x01b0
    UINT32                  reserved5[19];           // 0x01b4~0x01fc
    LED_L8AX_HSB_VSB_B2_T            hsb_vsb_b2;              // 0x0200
    LED_L8AX_HNB_VNB_B2_T            hnb_vnb_b2;              // 0x0204
    LED_L8AX_BOOT_ROM_ADDR_CLR_T     boot_rom_addr_clr;       // 0x0208
    LED_L8AX_BOOT_ROM_DATA_T         boot_rom_data;           // 0x020c
    LED_L8AX_RUN_STALL_T             run_stall;               // 0x0210
    LED_L8AX_CMEM_ADDR_CLR_T         cmem_addr_clr;           // 0x0214
    LED_L8AX_WAVG_HCOEFF_T           wavg_hcoeff;             // 0x0218
    LED_L8AX_WAVG_VCOEFF_T           wavg_vcoeff;             // 0x021c
    LED_L8AX_SBI_HCOEFF_T            sbi_hcoeff;              // 0x0220
    LED_L8AX_SBI_VCOEFF_T            sbi_vcoeff;              // 0x0224
    LED_L8AX_PC_LUT_A_T              pc_lut_a;                // 0x0228
    LED_L8AX_PC_LUT_B_T              pc_lut_b;                // 0x022c
    LED_L8AX_PC_LUT_C_T              pc_lut_c;                // 0x0230
    LED_L8AX_PC_LUT_D_T              pc_lut_d;                // 0x0234
    LED_L8AX_BV_UPPER_LUT_T          bv_upper_lut;            // 0x0238
    LED_L8AX_BV_LOWER_LUT_T          bv_lower_lut;            // 0x023c
    LED_L8AX_INT_MASK_T              int_mask;                // 0x0240
    LED_L8AX_PDEBUG_EN_T             pdebug_en;               // 0x0244
    LED_L8AX_PDEBUG_STATUS_T         pdebug_status;           // 0x0248
    LED_L8AX_PDEBUG_PC_T             pdebug_pc;               // 0x024c
    LED_L8AX_PDEBUG_DATA_T           pdebug_data;             // 0x0250
    LED_L8AX_BV_INTR_CLR_T           bv_intr_clr;             // 0x0254
    LED_L8AX_LINE_INTR_CLR_T         line_intr_clr;           // 0x0258
    LED_L8AX_LINE_INTR_COUNTER_T     line_intr_counter;       // 0x025c
    UINT32                  reserved6[68];           // 0x0260~0x036c
    LED_L8AX_EXT_INTR_EN_T           ext_intr_en;             // 0x0370
    LED_L8AX_EXT_INTR_STATUS_T       ext_intr_status;         // 0x0374
    LED_L8AX_EXT_INTR_RAW_STATUS_T   ext_intr_raw_status;     // 0x0378
    LED_L8AX_EXT_INTR_CLR_T          ext_intr_clr;            // 0x037c
} LED_L8AX_REG_T;
/* 122 regs, 122 types */

/* 122 regs, 122 types in Total*/

/*
 * @{
 * Naming for register pointer.
 * gpRealRegLED_L8Ax : real register of LED.
 * gpRegLED_L8Ax     : shadow register.
 *
 * @def LED_L8AX_RdFL: Read  FLushing : Shadow <- Real.
 * @def LED_L8AX_WrFL: Write FLushing : Shadow -> Real.
 * @def LED_L8AX_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def LED_L8AX_Wr  : Write whole register(UINT32) from Shadow register.
 * @def LED_L8AX_Rd01 ~ LED_L8AX_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def LED_L8AX_Wr01 ~ LED_L8AX_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define LED_L8AX_RdFL(_r)			((gpRegLED_L8Ax->_r)=(gpRealRegLED_L8Ax->_r))
#define LED_L8AX_WrFL(_r)			((gpRealRegLED_L8Ax->_r)=(gpRegLED_L8Ax->_r))

#define LED_L8AX_Rd(_r)			    *((UINT32*)(&(gpRegLED_L8Ax->_r)))
#define LED_L8AX_Wr(_r,_v)			((LED_L8AX_Rd(_r))=((UINT32)(_v)))

#define LED_L8AX_Rd01(_r,_f01,_v01)													\
								do { 											    \
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
								} while(0)

#define LED_L8AX_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											    \
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
								} while(0)

#define LED_L8AX_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 												\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
								} while(0)

#define LED_L8AX_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 												\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
								} while(0)

#define LED_L8AX_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
								} while(0)

#define LED_L8AX_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
								} while(0)

#define LED_L8AX_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
								} while(0)

#define LED_L8AX_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
								} while(0)

#define LED_L8AX_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
								} while(0)

#define LED_L8AX_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
								} while(0)

#define LED_L8AX_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
								} while(0)

#define LED_L8AX_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
									(_v12) = (gpRegLED_L8Ax->_r._f12);				\
								} while(0)

#define LED_L8AX_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
									(_v12) = (gpRegLED_L8Ax->_r._f12);				\
									(_v13) = (gpRegLED_L8Ax->_r._f13);				\
								} while(0)

#define LED_L8AX_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
									(_v12) = (gpRegLED_L8Ax->_r._f12);				\
									(_v13) = (gpRegLED_L8Ax->_r._f13);				\
									(_v14) = (gpRegLED_L8Ax->_r._f14);				\
								} while(0)

#define LED_L8AX_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
									(_v12) = (gpRegLED_L8Ax->_r._f12);				\
									(_v13) = (gpRegLED_L8Ax->_r._f13);				\
									(_v14) = (gpRegLED_L8Ax->_r._f14);				\
									(_v15) = (gpRegLED_L8Ax->_r._f15);				\
								} while(0)

#define LED_L8AX_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (gpRegLED_L8Ax->_r._f01);				\
									(_v02) = (gpRegLED_L8Ax->_r._f02);				\
									(_v03) = (gpRegLED_L8Ax->_r._f03);				\
									(_v04) = (gpRegLED_L8Ax->_r._f04);				\
									(_v05) = (gpRegLED_L8Ax->_r._f05);				\
									(_v06) = (gpRegLED_L8Ax->_r._f06);				\
									(_v07) = (gpRegLED_L8Ax->_r._f07);				\
									(_v08) = (gpRegLED_L8Ax->_r._f08);				\
									(_v09) = (gpRegLED_L8Ax->_r._f09);				\
									(_v10) = (gpRegLED_L8Ax->_r._f10);				\
									(_v11) = (gpRegLED_L8Ax->_r._f11);				\
									(_v12) = (gpRegLED_L8Ax->_r._f12);				\
									(_v13) = (gpRegLED_L8Ax->_r._f13);				\
									(_v14) = (gpRegLED_L8Ax->_r._f14);				\
									(_v15) = (gpRegLED_L8Ax->_r._f15);				\
									(_v16) = (gpRegLED_L8Ax->_r._f16);				\
								} while(0)


#define LED_L8AX_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
								} while(0)

#define LED_L8AX_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
								} while(0)

#define LED_L8AX_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
								} while(0)

#define LED_L8AX_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
								} while(0)

#define LED_L8AX_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
								} while(0)

#define LED_L8AX_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
								} while(0)

#define LED_L8AX_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
								} while(0)

#define LED_L8AX_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
								} while(0)

#define LED_L8AX_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
								} while(0)

#define LED_L8AX_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
								} while(0)

#define LED_L8AX_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
								} while(0)

#define LED_L8AX_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
									(gpRegLED_L8Ax->_r._f12) = (_v12);				\
								} while(0)

#define LED_L8AX_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
									(gpRegLED_L8Ax->_r._f12) = (_v12);				\
									(gpRegLED_L8Ax->_r._f13) = (_v13);				\
								} while(0)

#define LED_L8AX_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
									(gpRegLED_L8Ax->_r._f12) = (_v12);				\
									(gpRegLED_L8Ax->_r._f13) = (_v13);				\
									(gpRegLED_L8Ax->_r._f14) = (_v14);				\
								} while(0)

#define LED_L8AX_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
									(gpRegLED_L8Ax->_r._f12) = (_v12);				\
									(gpRegLED_L8Ax->_r._f13) = (_v13);				\
									(gpRegLED_L8Ax->_r._f14) = (_v14);				\
									(gpRegLED_L8Ax->_r._f15) = (_v15);				\
								} while(0)

#define LED_L8AX_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(gpRegLED_L8Ax->_r._f01) = (_v01);				\
									(gpRegLED_L8Ax->_r._f02) = (_v02);				\
									(gpRegLED_L8Ax->_r._f03) = (_v03);				\
									(gpRegLED_L8Ax->_r._f04) = (_v04);				\
									(gpRegLED_L8Ax->_r._f05) = (_v05);				\
									(gpRegLED_L8Ax->_r._f06) = (_v06);				\
									(gpRegLED_L8Ax->_r._f07) = (_v07);				\
									(gpRegLED_L8Ax->_r._f08) = (_v08);				\
									(gpRegLED_L8Ax->_r._f09) = (_v09);				\
									(gpRegLED_L8Ax->_r._f10) = (_v10);				\
									(gpRegLED_L8Ax->_r._f11) = (_v11);				\
									(gpRegLED_L8Ax->_r._f12) = (_v12);				\
									(gpRegLED_L8Ax->_r._f13) = (_v13);				\
									(gpRegLED_L8Ax->_r._f14) = (_v14);				\
									(gpRegLED_L8Ax->_r._f15) = (_v15);				\
									(gpRegLED_L8Ax->_r._f16) = (_v16);				\
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
 * _rwname: name of rw    bit field : shall be 0 after LED_L8AX_Wind(), 1 for LED_L8AX_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * LED_L8AX_Rind : General indexed register Read.(
 * LED_L8AX_Wind : General indexed register Read.
 *
 * LED_L8AX_Ridx : For 'index', 'rw', 'load' field name
 * LED_L8AX_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define LED_L8AX_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								LED_L8AX_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								LED_L8AX_WrFL(_r);									\
								LED_L8AX_RdFL(_r);									\
								LED_L8AX_Rd01(_r,_fname,_fval);						\
							} while (0)

#define LED_L8AX_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				LED_L8AX_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define LED_L8AX_Ridx(_r, _ival, _fname, _fval)	LED_L8AX_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define LED_L8AX_Widx(_r, _ival, _fname, _fval)	LED_L8AX_Wind(_r,load,rw,index,_ival,_fname,_fval)

#endif
/* from 'LG1150-LED-MAN-01 v0.8(Register Manual -20100127).csv' 20100311 00:54:19   대한민국 표준시 by getregs v2.3 */
