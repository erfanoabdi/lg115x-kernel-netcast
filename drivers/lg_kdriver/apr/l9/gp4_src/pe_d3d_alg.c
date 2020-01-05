// 3D_format.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#ifdef PE_D3D_USE_LINE_DIFF_BY_SW

#define STEP_SIZE 3

#define DBGMSG	if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT)PE_PRINT
unsigned char line_buffer_left[PE_D3D_MAX_HSIZE] = { 0 };
unsigned char line_buffer_right[PE_D3D_MAX_HSIZE] = { 0 };
unsigned char line_buffer_top[PE_D3D_MAX_HSIZE] = { 0 };
unsigned char line_buffer_bottom[PE_D3D_MAX_HSIZE] = { 0 };
int hist_left[256];
int hist_right[256];

int hist_top[256];
int hist_bottom[256];

static int PE_D3D_MeasureLineDifference(PE_D3D_CAP_INFO_T *capture_info)
{
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;

	int i, j;


	char **tmpG;
	unsigned int height;
	unsigned int width;
	unsigned int line_num;

	unsigned int hist_ss;
	unsigned int hist_tb;

	int num_right_point;
	int num_left_point;
	int num_top_point;
	int num_bottom_point;

	unsigned int entropy_measure_ss = 0;
	unsigned int entropy_measure_tb = 0;

	int h_line;

	unsigned int line_ssd = 0;
	unsigned int line_ssd_inverse = 0;
	unsigned int line_ssd_motion1 = 0;
	unsigned int line_ssd_motion2 = 0;
	unsigned int line_ssd_tb1 = 0;
	unsigned int line_ssd_tb1_inverse = 0;
	unsigned int line_ssd_tb1_motion1 = 0;
	unsigned int line_ssd_tb1_motion2 = 0;
	unsigned int line_ssd_tb2 = 0;
	unsigned int line_ssd_tb2_inverse = 0;
	unsigned int line_ssd_tb2_motion1 = 0;
	unsigned int line_ssd_tb2_motion2 = 0;

	unsigned int max_line_ssd_ss;
	unsigned int max_line_ssd_ss_inverse;
	unsigned int max_line_ssd_tb;
	unsigned int max_line_ssd_tb_inverse;
	unsigned int max_line_ssd_ss_inverse_same_line;
	unsigned int max_line_ssd_tb_inverse_same_line;

	int sampling_size;
	int detection_threshold_ss;
	int detection_threshold_tb;

	int left_offset = 0;
	int right_offset = 32;

	int ss_flag = -1;

	int max_h_line;

	int max_part_tb;

	int hard_constraint_2D;
	int hard_constraint_3D;

	int high_entropy_th1;
	int high_entropy_th2;
	int very_low_entropy_th1;
	int very_low_entropy_th2;
	int very_low_entropy_th3;

	int special_hard_constraint;

	int low_line_entropy_th;

	int special_hist_condition;

	unsigned int diff_left;
	unsigned int diff_right;

	unsigned int max_diff_left_right;
	unsigned int max_diff_top_bottom;

	unsigned int between_line_diff;
	unsigned int max_between_line_diff;

	unsigned int max_hist_ss;
	unsigned int max_hist_tb;

	LX_PE_D3D_FORMAT_T tmp_fmt = pCfg->tmp_fmt;

	unsigned int ver_delta;
	unsigned int hor_delta;

	unsigned int left_inhomogenous_sample;
	unsigned int right_inhomogeneous_sample;
	unsigned int left_inhomogeneous_sample_ref;
	unsigned int right_inhomogeneous_sample_ref;

	unsigned int max_ver_delta = 0;
	unsigned int max_hor_delta = 0;

	int black_flag;
	int final_black_flag;

	int hard_constraint_2D_flag;

	int max_diff_plus_ss;
	int max_diff_minus_ss;

	int max_max_diff_plus_ss;
	int max_max_diff_minus_ss;

	int max_diff_plus_tb;
	int max_diff_minus_tb;

	int max_max_diff_plus_tb;
	int max_max_diff_minus_tb;

//	int diff_pixel = 0;

	int ver_delta_thres = 0;
	int hor_delta_thres = 0;

	int left_hist_mono_flag = -1;
	int right_hist_mono_flag = -1;
	int top_hist_mono_flag = -1;
	int bottom_hist_mono_flag = -1;

	int tpd_strong_2D_cond_ss = -1;
	int tpd_strong_2D_cond_tb = -1;

	int m1_false_alarm_threshold = 0;
	int src_type = 0;

	int M2_delta_th = 0;

	int tpd_entropy_threshold1;
	int tpd_entropy_threshold2;
	int tpd_entropy_threshold3;
	int tpd_entropy_threshold4;
	int tpd_entropy_threshold5;

	int tpd_ssd_threshold1;
	int tpd_ssd_threshold2;
	int tpd_ssd_threshold3;
	int tpd_ssd_threshold4;
	int tpd_ssd_threshold5;

	int tpd_th_for_low_line_diff;

	int tpd_inverse_ssd_threshold;
	int edge_thres_factor;
	int edge_thres_factor_high_line_diff;
	int edge_strong_thres_factor;
	int edge_thres_factor_tpd;

	int M1_recheck_threshold;

	if(pThr->tpd_thr == DEFAULT_D_TPD_THR)
		src_type = 0;	// HDMI, EMP
	else
		src_type = 1;	// Component

	num_right_point = 0;
	num_left_point = 0;
	num_top_point = 0;
	num_bottom_point = 0;

	ss_flag = -1;

	hist_ss = 0;
	hist_tb = 0;

	max_hist_ss = 0;
	max_hist_tb = 0;

	diff_left = 0;
	diff_right = 0;

	for(j = 0; j < 256; j++)
	{
		hist_left[j] = 0;
		hist_right[j] = 0;
		hist_top[j] = 0;
		hist_bottom[j] = 0;
	}

	// frame buffer handling
	sampling_size = capture_info->h_pos_offset;
	line_num = capture_info->h_line_num;
	tmpG = (char**)capture_info->pHLine;
	height = capture_info->v_size;
	width = capture_info->h_size;

	if(src_type == 0)
	{
		ver_delta_thres = 75*line_num;
		hor_delta_thres = 75*width;

		detection_threshold_ss = 39*((width>>1) - 64);
		detection_threshold_tb = 33*((width>>1) - 64);
		m1_false_alarm_threshold = 60*((width>>1) - 64);

		hard_constraint_2D = 100*((width>>1) - 64);
		hard_constraint_3D = 31*((width>>1) - 64);
		special_hard_constraint = 20*((width>>1) - 64);

		high_entropy_th1 = ((((width>>1) - 64)*line_num)>>2)/10;
		high_entropy_th2 = ((((width>>1) - 64)*line_num)>>2)/4;		//1480
		very_low_entropy_th1 = ((((width>>1) - 64)*line_num)>>2)/10;	//592
		very_low_entropy_th2 = ((((width>>1) - 64)*line_num)>>2)/2;
		very_low_entropy_th3 = ((((width>>1) - 64)*line_num)>>2)/8;	//740
		low_line_entropy_th = 50*((((width>>1) - 64)*line_num));

		tpd_entropy_threshold1 = 50;
		tpd_entropy_threshold2 = 1000;// final_test : 2000->1080;
		tpd_entropy_threshold3 = 1000;// final_test : 1080->1000
		tpd_entropy_threshold4 = 60;
		tpd_entropy_threshold5 = 1000;

		tpd_ssd_threshold1 = 1000;
		tpd_ssd_threshold2 = 15000;
		tpd_ssd_threshold3 = 11000;
		tpd_ssd_threshold4 = 200;
		tpd_ssd_threshold5 = 11000;

		tpd_inverse_ssd_threshold = 2000;
		special_hist_condition = 10;//((((width>>1) - 64)*line_num)>>2)/500;

		edge_thres_factor = 30;
		edge_thres_factor_high_line_diff = 30;
		edge_thres_factor_tpd = 30;

		edge_strong_thres_factor = 6;
		tpd_th_for_low_line_diff = 100;

		M1_recheck_threshold = 8;
		M2_delta_th = 3;
	} else {
		ver_delta_thres = 75*line_num;
		hor_delta_thres = 75*width;

		detection_threshold_ss = 39*((width>>1) - 64);
		detection_threshold_tb = 33*((width>>1) - 64);
		m1_false_alarm_threshold = 60*((width>>1) - 64);

		hard_constraint_2D = 100*((width>>1) - 64);
		hard_constraint_3D = 29*((width>>1) - 64);
		special_hard_constraint = 20*((width>>1) - 64);

		high_entropy_th1 = ((((width>>1) - 64)*line_num)>>2)/10;
		high_entropy_th2 = ((((width>>1) - 64)*line_num)>>2)/4;
		very_low_entropy_th1 = ((((width>>1) - 64)*line_num)>>2)/10;
		very_low_entropy_th2 = ((((width>>1) - 64)*line_num)>>2)/2;
		very_low_entropy_th3 = ((((width>>1) - 64)*line_num)>>2)/9;	//740

		low_line_entropy_th = 50*((((width>>1) - 64)*line_num));

		tpd_entropy_threshold1 = 50;
		tpd_entropy_threshold2 = 1000;// final_test : 2000->1080;
		tpd_entropy_threshold3 = 1000;// final_test : 1080->1000
		tpd_entropy_threshold4 = 60;
		tpd_entropy_threshold5 = 1000;

		tpd_ssd_threshold1 = 1000;
		tpd_ssd_threshold2 = 15000;
		tpd_ssd_threshold3 = 11000;
		tpd_ssd_threshold4 = 200;
		tpd_ssd_threshold5 = 11000;

		tpd_inverse_ssd_threshold = 2000;
		special_hist_condition = 10;//((((width>>1) - 64)*line_num)>>2)/500;

		edge_thres_factor = 13;
		edge_thres_factor_high_line_diff = 25;
		edge_thres_factor_tpd = 30;

		edge_strong_thres_factor = 6;
		tpd_th_for_low_line_diff = 80;

		M1_recheck_threshold = 5;
		M2_delta_th = 2;
	}


	max_line_ssd_ss = 0;
	max_line_ssd_tb = 0;

	max_line_ssd_ss_inverse = 0;
	max_line_ssd_tb_inverse = 0;

	max_line_ssd_ss_inverse_same_line = 0;
	max_line_ssd_tb_inverse_same_line = 0;

	hard_constraint_2D_flag = -1;

	max_max_diff_plus_ss = 0;
	max_max_diff_minus_ss = 0;

	max_max_diff_plus_tb = 0;
	max_max_diff_minus_tb = 0;

//TB, SS select
//Top Line SS
	for(h_line = 0; h_line < line_num>>1 ; h_line++)
	{
		diff_left = 0;
		diff_right = 0;

		max_diff_plus_ss = 0;
		max_diff_minus_ss = 0;
		for(i = 32; i < (width>>1) - 32; i++)
		{
			line_buffer_left[i]=tmpG[h_line][i];
			line_buffer_right[i]=tmpG[h_line][(width>>1)+i];
		}

		line_ssd = 0;
		line_ssd_inverse = 0;
		line_ssd_motion1 = 0;
		line_ssd_motion2 = 0;
		right_inhomogeneous_sample = 0;
		right_inhomogeneous_sample_ref = 0;
		left_inhomogenous_sample = 0;
		left_inhomogeneous_sample_ref = 0;

		for(i = 32; i < (width>>1) - 32; i++)
		{
			line_ssd += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i])));//*(abs(line_buffer_left[i] - line_buffer_right[i])));
			line_ssd_inverse += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[(width>>1) - i])));
			line_ssd_motion1 += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i+16])));
			line_ssd_motion2 += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i+32])));
/*
			diff_pixel = line_buffer_left[i] - line_buffer_right[i];
			if(diff_pixel < 0)
			{
				if(max_diff_minus_ss > abs(diff_pixel))
				{
					max_diff_minus_ss = abs(diff_pixel);
				}
			}
			else
			{
				if(max_diff_plus_ss > abs(diff_pixel))
				{
					max_diff_plus_ss = abs(diff_pixel);
				}
			}
*/
			if(abs(line_buffer_left[i] - line_buffer_left[i+1] ) > 10)
			{
				left_inhomogenous_sample++;
				if(i < (width>>1) - 64 && abs(line_buffer_left[i] - line_buffer_left[i+1]) > 10)
				{
					left_inhomogeneous_sample_ref++;
				}
			}
			if(abs(line_buffer_right[i] - line_buffer_right[i+1]) > 10)
			{
				right_inhomogeneous_sample++;
				if(i >= 64 && abs(line_buffer_right[i] - line_buffer_right[i+1]) > 10)
				{
					right_inhomogeneous_sample_ref++;
				}
			}
		}

		if(left_inhomogenous_sample == 0)
		{
		//	printk("Homogeneous Line\n");
			if(right_inhomogeneous_sample_ref != 0)
			{
				hard_constraint_2D_flag = 1;
			}
		}

		if(right_inhomogeneous_sample == 0)
		{
		//	printk("Homogeneous Line\n");
			if(left_inhomogeneous_sample_ref != 0)
			{
				hard_constraint_2D_flag = 1;
			}
		}

		if(line_ssd_motion1 < line_ssd)
		{
			line_ssd = line_ssd_motion1;
		}
		if(line_ssd_motion2 < line_ssd)
		{
			line_ssd = line_ssd_motion2;
		}
		if(line_ssd > max_line_ssd_ss)
		{
			max_line_ssd_ss = line_ssd;
			max_line_ssd_ss_inverse_same_line = line_ssd_inverse;
//			max_line_ssd_ss_inverse = line_ssd_inverse;
			max_h_line = h_line;
		}

		if(line_ssd_inverse > max_line_ssd_ss_inverse)
		{
			max_line_ssd_ss_inverse = line_ssd_inverse;
		}

/*
		if(max_diff_plus_ss > max_max_diff_plus_ss)
		{
			max_max_diff_plus_ss = max_diff_plus_ss;
		}
		if(max_diff_minus_ss > max_max_diff_minus_ss)
		{
			max_max_diff_minus_ss = max_diff_minus_ss;
		}	*/
	}
//Bottom Line SS
	for(h_line = line_num>>1; h_line < line_num ; h_line++)
	{
		for(i = 32; i < (width>>1) - 32; i++)
		{
			line_buffer_left[i]=tmpG[h_line][i];
			line_buffer_right[i]=tmpG[h_line][(width>>1)+i];
		}

		line_ssd = 0;
		line_ssd_inverse = 0;
		line_ssd_motion1 = 0;
		line_ssd_motion2 = 0;

		right_inhomogeneous_sample = 0;
		right_inhomogeneous_sample_ref = 0;
		left_inhomogenous_sample = 0;
		left_inhomogeneous_sample_ref = 0;

		max_diff_plus_ss = 0;
		max_diff_minus_ss = 0;

		for(i = 32; i < (width>>1) - 32; i++)
		{
			line_ssd += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i])));//*(abs(line_buffer_left[i] - line_buffer_right[i])));
			line_ssd_inverse += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[(width>>1) - i])));
			line_ssd_motion1 += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i+16])));
			line_ssd_motion2 += (unsigned int)((abs(line_buffer_left[i] - line_buffer_right[i+32])));
/*
			diff_pixel = line_buffer_left[i] - line_buffer_right[i];
			if(diff_pixel < 0)
			{
				if(max_diff_minus_ss > abs(diff_pixel))
				{
					max_diff_minus_ss = abs(diff_pixel);
				}
			}
			else {
				if(max_diff_plus_ss > abs(diff_pixel))
				{
					max_diff_plus_ss = abs(diff_pixel);
				}
			}
*/
			if(abs(line_buffer_left[i] - line_buffer_left[i+1] ) > 10)
			{
				left_inhomogenous_sample++;
				if(i < (width>>1) - 64 && abs(line_buffer_left[i] - line_buffer_left[i+1]) > 10)
				{
					left_inhomogeneous_sample_ref++;
				}
			}
			if(abs(line_buffer_right[i] - line_buffer_right[i+1]) > 10)
			{
				right_inhomogeneous_sample++;
				if(i >= 64 && abs(line_buffer_right[i] - line_buffer_right[i+1]) > 10)
				{
					right_inhomogeneous_sample_ref++;
				}
			}
		}

		if(left_inhomogenous_sample == 0)
		{
		//	printk("Homogeneous Line\n");
			if(right_inhomogeneous_sample_ref != 0)
			{
				hard_constraint_2D_flag = 1;
			}
		}

		if(right_inhomogeneous_sample == 0)
		{
		//	printk("Homogeneous Line\n");
			if(left_inhomogeneous_sample_ref != 0)
			{
				hard_constraint_2D_flag = 1;
			}
		}

		if(line_ssd_motion1 < line_ssd)
		{
			line_ssd = line_ssd_motion1;
		}
		if(line_ssd_motion2 < line_ssd)
		{
			line_ssd = line_ssd_motion2;
		}
		if(line_ssd > max_line_ssd_ss)
		{
			max_line_ssd_ss = line_ssd;
			max_line_ssd_ss_inverse_same_line = line_ssd_inverse;
//			max_line_ssd_ss_inverse = line_ssd_inverse;
			max_h_line = h_line;
		}

		if(line_ssd_inverse > max_line_ssd_ss_inverse)
		{
			max_line_ssd_ss_inverse = line_ssd_inverse;
		}

/*		if(max_diff_plus_ss > max_max_diff_plus_ss)
		{
			max_max_diff_plus_ss = max_diff_plus_ss;
		}
		if(max_diff_minus_ss > max_max_diff_minus_ss)
		{
			max_max_diff_minus_ss = max_diff_minus_ss;
		}		*/
	}


	max_part_tb = -1;
	max_between_line_diff = 0;
	max_diff_top_bottom = 0;

	for(h_line = 0; h_line < line_num>>1; h_line++)
	{
		max_diff_plus_tb = 0;
		max_diff_minus_tb = 0;

		for(i = 32; i < width -32; i++)
		{
			line_buffer_top[i] = tmpG[h_line][i];
			line_buffer_bottom[i] = tmpG[h_line+(line_num>>1)][i];
		}
		line_ssd_tb1 = 0;
		line_ssd_tb2 = 0;
		line_ssd_tb1_inverse = 0;
		line_ssd_tb2_inverse = 0;
		line_ssd_tb1_motion1 = 0;
		line_ssd_tb1_motion2 = 0;
		line_ssd_tb2_motion1 = 0;
		line_ssd_tb2_motion2 = 0;

		for(i = 32; i < (width>>1) - 32; i++)
		{
			line_ssd_tb1 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i])));//*(abs(line_buffer_left[i] - line_buffer_right[i]))); - (mean_left-mean_right)
			line_ssd_tb1_inverse += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[(width>>1) - i])));
			line_ssd_tb1_motion1 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i+16])));
			line_ssd_tb1_motion2 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i+32])));

/*
			diff_pixel = line_buffer_top[i] - line_buffer_bottom[i];
			if(diff_pixel < 0)
			{
				if(max_diff_minus_tb > abs(diff_pixel))
				{
					max_diff_minus_tb = abs(diff_pixel);
				}
			}
			else
			{
				if(max_diff_plus_tb > abs(diff_pixel))
				{
					max_diff_plus_tb = abs(diff_pixel);
				}
			}
*/
		}

		for(i =  ((width)>>1) + 32; i < width - 32; i++)
		{
			line_ssd_tb2 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i])));//*(abs(line_buffer_left[i] - line_buffer_right[i]))); - (mean_left-mean_right)
			line_ssd_tb2_inverse += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[width - i + ((width)>>1)])));//*(abs(line_buffer_left[i] - line_buffer_right[i]))); - (mean_left-mean_right)
			line_ssd_tb2_motion1 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i+16])));
			line_ssd_tb2_motion2 += (unsigned int)((abs(line_buffer_top[i] - line_buffer_bottom[i+32])));
/*
			diff_pixel = line_buffer_top[i] - line_buffer_bottom[i];
			if(diff_pixel < 0)
			{
				if(max_diff_minus_tb > abs(diff_pixel))
				{
					max_diff_minus_tb = abs(diff_pixel);
				}
			}
			else
			{
				if(max_diff_plus_tb > abs(diff_pixel))
				{
					max_diff_plus_tb = abs(diff_pixel);
				}
			}	*/
		}

		between_line_diff = abs(line_ssd_tb1 - line_ssd_tb2);


		if(line_ssd_tb1_motion1 < line_ssd_tb1)
		{
			line_ssd_tb1 = line_ssd_tb1_motion1;
		}
		if(line_ssd_tb1_motion2 < line_ssd_tb1)
		{
			line_ssd_tb1 = line_ssd_tb1_motion2;
		}

		if(line_ssd_tb1 > max_line_ssd_tb)
		{
			max_line_ssd_tb = line_ssd_tb1;
			max_line_ssd_tb_inverse_same_line = line_ssd_tb1_inverse;
//			max_line_ssd_tb_inverse = line_ssd_tb1_inverse;
			max_part_tb = 0;
			max_h_line = h_line;
		}

		if(line_ssd_tb1_inverse > max_line_ssd_tb_inverse)
		{
			max_line_ssd_tb_inverse = line_ssd_tb1_inverse;
		}

		if(line_ssd_tb2_motion1 < line_ssd_tb2)
		{
			line_ssd_tb2 = line_ssd_tb2_motion1;
		}
		if(line_ssd_tb2_motion2 < line_ssd_tb2)
		{
			line_ssd_tb2 = line_ssd_tb2_motion2;
		}

		if(line_ssd_tb2 > max_line_ssd_tb)
		{
			max_line_ssd_tb = line_ssd_tb2;
			max_line_ssd_tb_inverse_same_line = line_ssd_tb2_inverse;
//			max_line_ssd_tb_inverse = line_ssd_tb2_inverse;
			max_part_tb = 1;
			max_h_line = h_line;
		}

		if(line_ssd_tb2_inverse > max_line_ssd_tb_inverse)
		{
			max_line_ssd_tb_inverse = line_ssd_tb2_inverse;
		}

		if(between_line_diff > max_between_line_diff)
		{
			max_between_line_diff = between_line_diff;
		}
/*
		if(max_diff_plus_tb > max_max_diff_plus_tb)
		{
			max_max_diff_plus_tb = max_diff_plus_tb;
		}
		if(max_diff_minus_tb > max_max_diff_minus_tb)
		{
			max_max_diff_minus_tb = max_diff_minus_tb;
		}	*/
	}

	if(pData->tpd > pThr->tpd_thr)
	{
		if(max_line_ssd_ss > max_line_ssd_tb)
		{
			ss_flag = 1;
		} else {
			ss_flag = 0;
		}
	} else {
		if(max_line_ssd_ss > max_line_ssd_tb + 3*((width>>1) - 64))	//10*
		{
			ss_flag = 1;
		} else if(max_line_ssd_tb > max_line_ssd_ss + 3*((width>>1) - 64)) {	//10*
			ss_flag = 0;
		} else {
			if(tmp_fmt == LX_PE_D3D_FMT_3D_SS)
			{
				ss_flag = 0;
			} else if(tmp_fmt == LX_PE_D3D_FMT_3D_TB)
			{
				ss_flag = 1;
			} else {
				if((pData->ssr > pData->tbr))// && (pData->lr_diff < pData->tb_diff))
					ss_flag = 0;
				else if((pData->ssr < pData->tbr))// && (pData->lr_diff > pData->tb_diff))
					ss_flag = 1;
				else
					ss_flag = 0;
			}
		}
	}

	final_black_flag = 0;
	if(ss_flag == 1)
	{
		for(i = 0; i < 7; i++)
		{
			ver_delta = 0;
			black_flag = 1;
			for(j = 0; j < width; j++)
			{
				ver_delta += (abs(capture_info->pHLineCenter[i][j] - capture_info->pHLineCenter[i+1][j]));
			}

			if(ver_delta > max_ver_delta)
			{
				max_ver_delta = ver_delta;
			}
		}
	} else {
		for(i = 0; i < 9; i++)
		{
			hor_delta = 0;
			for(j = 0; j < line_num; j++)
			{
				hor_delta += (abs(tmpG[j][(width>>1)-4+i] - tmpG[j][(width>>1)-3+i]));
			}
			if(hor_delta > max_hor_delta)
			{
				max_hor_delta = hor_delta;
			}
		}
	}
	max_diff_left_right = 0;

	if (ss_flag == 0)
	{
		for(h_line = 0; h_line < line_num >> 1; h_line++)
		{
			for(j = 32; j < width >> 2; j++)
			{
				hist_left[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_right[((tmpG[h_line][j+(width>>1)])>>STEP_SIZE)]++;
			}
		}

		hist_ss = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_left[i] == (line_num>>1)*((width>>2) - 32))
				{
					left_hist_mono_flag = 1;
				}
				if(hist_right[i] == (line_num>>1)*((width>>2) - 32))
				{
					right_hist_mono_flag = 1;
				}
				if(left_hist_mono_flag == 1)
				{
					if(right_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
				if(right_hist_mono_flag == 1)
				{
					if(left_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
			}
			hist_ss += (unsigned int)abs(hist_left[i] - hist_right[i]);
			hist_left[i] = 0;
			hist_right[i] = 0;
		}

		left_hist_mono_flag = -1;
		right_hist_mono_flag = -1;

		if(max_hist_ss < hist_ss)
		{
			max_hist_ss = hist_ss;
		}

		for(h_line = 0; h_line < line_num >> 1; h_line++)
		{
			for(j = width >> 2; j < (width >> 1) - 32; j++)
			{
				hist_left[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_right[((tmpG[h_line][j+(width>>1)])>>STEP_SIZE)]++;
			}
		}

		hist_ss = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_left[i] == (line_num>>1)*((width>>2) - 32))
				{
					left_hist_mono_flag = 1;
				}
				if(hist_right[i] == (line_num>>1)*((width>>2) - 32))
				{
					right_hist_mono_flag = 1;
				}
				if(left_hist_mono_flag == 1)
				{
					if(right_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
				if(right_hist_mono_flag == 1)
				{
					if(left_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
			}
			hist_ss += (unsigned int)abs(hist_left[i] - hist_right[i]);
			hist_left[i] = 0;
			hist_right[i] = 0;
		}

		left_hist_mono_flag = -1;
		right_hist_mono_flag = -1;

		if(max_hist_ss < hist_ss)
		{
			max_hist_ss = hist_ss;
		}

		for(h_line = (line_num >> 1); h_line < line_num; h_line++)
		{
			for(j = 32; j < width >> 2; j++)
			{
				hist_left[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_right[((tmpG[h_line][j+(width>>1)])>>STEP_SIZE)]++;
			}
		}

		hist_ss = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_left[i] == (line_num>>1)*((width>>2) - 32))
				{
					left_hist_mono_flag = 1;
				}
				if(hist_right[i] == (line_num>>1)*((width>>2) - 32))
				{
					right_hist_mono_flag = 1;
				}
				if(left_hist_mono_flag == 1)
				{
					if(right_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
				if(right_hist_mono_flag == 1)
				{
					if(left_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
			}
			hist_ss += (unsigned int)abs(hist_left[i] - hist_right[i]);
			hist_left[i] = 0;
			hist_right[i] = 0;
		}


		left_hist_mono_flag = -1;
		right_hist_mono_flag = -1;

		if(max_hist_ss < hist_ss)
		{
			max_hist_ss = hist_ss;
		}

		for(h_line = (line_num >> 1); h_line < line_num; h_line++)
		{
			for(j = width >> 2; j < (width >> 1) - 32; j++)
			{
				hist_left[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_right[((tmpG[h_line][j+(width>>1)])>>STEP_SIZE)]++;
			}
		}

		hist_ss = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_left[i] == (line_num>>1)*((width>>2) - 32))
				{
					left_hist_mono_flag = 1;
				}
				if(hist_right[i] == (line_num>>1)*((width>>2) - 32))
				{
					right_hist_mono_flag = 1;
				}
				if(left_hist_mono_flag == 1)
				{
					if(right_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
				if(right_hist_mono_flag == 1)
				{
					if(left_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_ss = 1;
					}
				}
			}
			hist_ss += (unsigned int)abs(hist_left[i] - hist_right[i]);
			hist_left[i] = 0;
			hist_right[i] = 0;
		}

		left_hist_mono_flag = -1;
		right_hist_mono_flag = -1;

		if(max_hist_ss < hist_ss)
		{
			max_hist_ss = hist_ss;
		}

		if (max_hist_ss == 0)
		{
			entropy_measure_ss = 0;
		} else {
			entropy_measure_ss = max_hist_ss;
		}

	}
	else
	{
		for(h_line = 0; h_line < (line_num>>2); h_line++)
		{
			for(j = 32; j < (width >> 1) - 32; j++)
			{
				hist_top[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_bottom[((tmpG[(line_num>>1)+h_line][j])>>STEP_SIZE)]++;
			}
		}

		hist_tb = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_top[i] == (line_num>>2)*((width>>1) - 64))
				{
					top_hist_mono_flag = 1;
				}
				if(hist_bottom[i] == (line_num>>2)*((width>>1) - 64))
				{
					bottom_hist_mono_flag = 1;
				}
				if(top_hist_mono_flag == 1)
				{
					if(bottom_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
				if(bottom_hist_mono_flag == 1)
				{
					if(top_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
			}
			hist_tb += (unsigned int)abs(hist_top[i] - hist_bottom[i]);
			hist_top[i] = 0;
			hist_bottom[i] = 0;
		}

		top_hist_mono_flag = -1;
		bottom_hist_mono_flag = -1;

		if(hist_tb > max_hist_tb)
		{
			max_hist_tb = hist_tb;
		}

		for(h_line = 0; h_line < (line_num>>2); h_line++)
		{
			for(j = (width >> 1) + 32; j < width - 32; j++)
			{
				hist_top[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_bottom[((tmpG[(line_num>>1)+h_line][j])>>STEP_SIZE)]++;
			}
		}

		hist_tb = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_top[i] == (line_num>>2)*((width>>1) - 64))
				{
					top_hist_mono_flag = 1;
				}
				if(hist_bottom[i] == (line_num>>2)*((width>>1) - 64))
				{
					bottom_hist_mono_flag = 1;
				}
				if(top_hist_mono_flag == 1)
				{
					if(bottom_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
				if(bottom_hist_mono_flag == 1)
				{
					if(top_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
			}
			hist_tb += (unsigned int)abs(hist_top[i] - hist_bottom[i]);
			hist_top[i] = 0;
			hist_bottom[i] = 0;
		}

		top_hist_mono_flag = -1;
		bottom_hist_mono_flag = -1;

		if(hist_tb > max_hist_tb)
		{
			max_hist_tb = hist_tb;
		}

		for(h_line = (line_num>>2); h_line < (line_num>>1); h_line++)
		{
			for(j = 32; j < (width >> 1) - 32; j++)
			{
				hist_top[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_bottom[((tmpG[(line_num>>1)+h_line][j])>>STEP_SIZE)]++;
			}
		}

		hist_tb = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_top[i] == (line_num>>2)*((width>>1) - 64))
				{
					top_hist_mono_flag = 1;
				}
				if(hist_bottom[i] == (line_num>>2)*((width>>1) - 64))
				{
					bottom_hist_mono_flag = 1;
				}
				if(top_hist_mono_flag == 1)
				{
					if(bottom_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
				if(bottom_hist_mono_flag == 1)
				{
					if(top_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
			}
			hist_tb += (unsigned int)abs(hist_top[i] - hist_bottom[i]);
			hist_top[i] = 0;
			hist_bottom[i] = 0;
		}

		top_hist_mono_flag = -1;
		bottom_hist_mono_flag = -1;

		if(hist_tb > max_hist_tb)
		{
			max_hist_tb = hist_tb;
		}

		for(h_line = (line_num>>2); h_line < (line_num>>1); h_line++)
		{
			for(j = (width >> 1) + 32; j < width - 32; j++)
			{
				hist_top[((tmpG[h_line][j])>>STEP_SIZE)]++;
				hist_bottom[((tmpG[(line_num>>1)+h_line][j])>>STEP_SIZE)]++;
			}
		}

		hist_tb = 0;

		for(i = left_offset; i < right_offset; i++)
		{
			if(pData->tpd > pThr->tpd_thr)
			{
				if(hist_top[i] == (line_num>>2)*((width>>1) - 64))
				{
					top_hist_mono_flag = 1;
				}
				if(hist_bottom[i] == (line_num>>2)*((width>>1) - 64))
				{
					bottom_hist_mono_flag = 1;
				}
				if(top_hist_mono_flag == 1)
				{
					if(bottom_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
				if(bottom_hist_mono_flag == 1)
				{
					if(top_hist_mono_flag == -1)
					{
						tpd_strong_2D_cond_tb = 1;
					}
				}
			}
			hist_tb += (unsigned int)abs(hist_top[i] - hist_bottom[i]);
			hist_top[i] = 0;
			hist_bottom[i] = 0;
		}

		top_hist_mono_flag = -1;
		bottom_hist_mono_flag = -1;

		if(hist_tb > max_hist_tb)
		{
			max_hist_tb = hist_tb;
		}

//		DBGMSG("SS_POINT %f\n", value_ss_point1);

		if (max_hist_tb == 0)
		{
			entropy_measure_tb = 0;
		} else {
			entropy_measure_tb = max_hist_tb;
		}
	}


	if(tmp_fmt == LX_PE_D3D_FMT_3D_SS || tmp_fmt == LX_PE_D3D_FMT_3D_TB)
	{
		if(tmp_fmt == LX_PE_D3D_FMT_3D_SS && ss_flag == 0)
		{
			if(pData->ssr > M1_recheck_threshold)
			{
				if(max_line_ssd_ss > (9*max_line_ssd_ss_inverse_same_line) >> 3)
				{
					DBGMSG("[D3DM2] %d - 2D False Alaram in M1 SS case by Inverse LineDiff : %d\t%d\n", __L__, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else if(max_line_ssd_ss > hard_constraint_2D) {
					DBGMSG("[D3DM2] %d - 2D False Alaram in M1 SS case by LineDiff %d\t%d\n", __L__, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else if(max_line_ssd_ss > m1_false_alarm_threshold) {
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else {
					DBGMSG("[D3DM2] %d - 3D SS in M1 %d\t%d\n", __L__, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_3D_SS;
				}
			} else {
				DBGMSG("[D3DM2] %d - 3D SS in M1 with Low Delta%d\t%d\n", __L__, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line);
				tmp_fmt = LX_PE_D3D_FMT_3D_SS;
			}

		} else if(tmp_fmt == LX_PE_D3D_FMT_3D_TB && ss_flag == 1) {
			if(pData->tbr > M1_recheck_threshold)
			{
				if(max_line_ssd_tb > (9*max_line_ssd_tb_inverse_same_line) >> 3)
				{
					DBGMSG("[D3DM2] %d - 2D False Alaram in M1 TB case by Inverse LineDiff %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else if(max_line_ssd_tb > hard_constraint_2D) {
					DBGMSG("[D3DM2] %d - 2D False Alaram in M1 TB case by LineDiff %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else if(max_line_ssd_tb > m1_false_alarm_threshold) {
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else {
					DBGMSG("[D3DM2] %d - 3D TB in M1 %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line);
					tmp_fmt = LX_PE_D3D_FMT_3D_TB;
				}
			} else {
				DBGMSG("[D3DM2] %d - 3D TB in M1 with Low Delta %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line);
				tmp_fmt = LX_PE_D3D_FMT_3D_TB;
			}
		} else {
			DBGMSG("[D3DM2] %d - 2D Unknown By Different Decision Between M1 and M2 \n", __L__);
			tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
		}
	}
/*
	if(pData->tpd <= 182 && tmp_fmt == LX_PE_D3D_FMT_2D_2D)
	{
		if((max_line_ssd_ss < 1600) && (max_line_ssd_tb < 1600))
		{
			tmp_fmt = LX_PE_D3D_FMT_2D_2D;
		} else {
			if(ss_flag == 0)
			{
				if(entropy_measure_ss < special_hist_condition)
				{
				} else {
					if(max_line_ssd_ss_inverse > ((7*max_line_ssd_ss)>>2))
					{
						DBGMSG("[D3DM2] %d - 3D SS in M2 by Inverse LineDiff %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse);
						tmp_fmt = LX_PE_D3D_FMT_3D_SS;
					}
				}
			} else {
				if(entropy_measure_tb < special_hist_condition)
				{
				} else {
					if(max_line_ssd_tb_inverse > ((7*max_line_ssd_tb)>>2))
					{
						DBGMSG("[D3DM2] %d - 3D TB in M2 by Inverse LineDiff %d\t%d\n", __L__, max_line_ssd_tb, max_line_ssd_tb_inverse);
						tmp_fmt = LX_PE_D3D_FMT_3D_TB;
					}
				}
			}
		}
	}	*/
	if(tmp_fmt == LX_PE_D3D_FMT_UNKNOWN || tmp_fmt == LX_PE_D3D_FMT_2D_2D)
	{
		if(pData->tpd > pThr->tpd_thr)
		{
			if(ss_flag == 0)
			{
				if(tpd_strong_2D_cond_ss == 1)
				{
					DBGMSG("[D3DM2] %d - 2D TPD MONO_INVALID_SS %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else {
					if((entropy_measure_ss > tpd_entropy_threshold1 || max_line_ssd_ss > tpd_ssd_threshold1) && (max_line_ssd_ss_inverse > (3*max_line_ssd_ss)>>1))
					{
						if(entropy_measure_ss > tpd_entropy_threshold2 || max_line_ssd_ss > tpd_ssd_threshold2)
						{
							DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta, max_line_ssd_ss_inverse);
							tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
						} else {
							DBGMSG("[D3DM2] %d - 3D TPD SS BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta, max_line_ssd_ss_inverse);
							tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						}
					} else if(max_line_ssd_ss > (3*max_line_ssd_ss_inverse) >> 1)
					{
						DBGMSG("[D3DM2] %d - 2D TPD SS UNKNOWN BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta, max_line_ssd_ss_inverse);
						tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
					} else if(entropy_measure_ss == 0 && max_line_ssd_ss == 0)
					{
						if(max_line_ssd_ss_inverse > tpd_inverse_ssd_threshold)
						{
							DBGMSG("[D3DM2] %d - 3D TPD Side_By_Side For No Depth %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
							tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						} else {
							DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
							tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
						}
					} else {
						if(max_hor_delta > edge_thres_factor_tpd*line_num)
						{
							if(entropy_measure_ss > tpd_entropy_threshold3 || max_line_ssd_ss > tpd_ssd_threshold3)
							{
								DBGMSG("[D3DM2] %d - 2D TPD %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
								tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							} else {
								if(entropy_measure_ss == 0 || max_line_ssd_ss == 0)
								{
									DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
								} else {
									DBGMSG("[D3DM2] %d - 3D TPD Side_By_Side %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_SS;
								}
							}
						} else {
							if(max_line_ssd_ss_inverse > (3*max_line_ssd_ss))
							{
								if(entropy_measure_ss > tpd_entropy_threshold4 || max_line_ssd_ss > tpd_ssd_threshold4)
								{
									if(entropy_measure_ss < tpd_entropy_threshold5)
									{
										if(max_line_ssd_ss > tpd_ssd_threshold5)
										{
											DBGMSG("[D3DM2] %d - 2D TPD %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD Side_By_Side %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_3D_SS;
										}
									} else {
										if(entropy_measure_ss > tpd_entropy_threshold2 || max_line_ssd_ss > tpd_ssd_threshold2)
										{
											DBGMSG("[D3DM2] %d - 2D SS %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD Side_By_Side %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_3D_SS;
										}
									}
								} else {
									if(entropy_measure_ss == 0 || max_line_ssd_ss == 0)
									{
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									} else {
										DBGMSG("[D3DM2] %d - 2D TPD Side_By_Side %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_3D_SS;
									}
								}
							} else {
								if(entropy_measure_ss > tpd_entropy_threshold4 || max_line_ssd_ss > tpd_ssd_threshold4)
								{
									if(entropy_measure_ss < tpd_entropy_threshold5)
									{
										if(max_line_ssd_ss > tpd_ssd_threshold5)
										{
											DBGMSG("[D3DM2] %d - 2D TPD %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									} else {
										if(entropy_measure_ss > tpd_entropy_threshold2 || max_line_ssd_ss > tpd_ssd_threshold2)
										{
											DBGMSG("[D3DM2] %d - 2D SS %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									}
								} else {
									if(entropy_measure_ss == 0 || max_line_ssd_ss == 0)
									{
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									} else {
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									}
								}
							}

						}
					}
				}
			} else
			{
				if(tpd_strong_2D_cond_tb == 1)
				{
					DBGMSG("[D3DM2] %d - 2D TPD MONO_INVALID_TB %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
					tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				} else {
					if((entropy_measure_tb > tpd_entropy_threshold1 || max_line_ssd_tb > tpd_ssd_threshold1) && (max_line_ssd_tb_inverse > (3*max_line_ssd_tb)>>1))
					{
						if(entropy_measure_tb > tpd_entropy_threshold2 || max_line_ssd_tb > tpd_ssd_threshold2)
						{
							DBGMSG("[D3DM2] %d - 2D TPD TB UNKNOWN BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta, max_line_ssd_tb_inverse);
							tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
						} else {
							DBGMSG("[D3DM2] %d - 3D TPD TB BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta, max_line_ssd_tb_inverse);
							tmp_fmt = LX_PE_D3D_FMT_3D_TB;
						}
					} else if(max_line_ssd_tb > (3*max_line_ssd_tb_inverse) >> 1)
					{
						DBGMSG("[D3DM2] %d - 2D TPD TB UNKNOWN BY Inverse Check %d\t%d\t%d : %d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta, max_line_ssd_tb_inverse);
						tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
					} else if(entropy_measure_tb == 0 && max_line_ssd_tb == 0)
					{
						if(max_line_ssd_tb_inverse > tpd_inverse_ssd_threshold)
						{
							DBGMSG("[D3DM2] %d - 3D TPD TOP BOTTOM For No Depth %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
							tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						} else {
							DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
							tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
						}
					} else {
						if(max_ver_delta > edge_thres_factor_tpd*width)
						{
							if(entropy_measure_tb > tpd_entropy_threshold3 || max_line_ssd_tb > tpd_ssd_threshold3)
							{
								DBGMSG("[D3DM2] %d - 2D TPD  %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
								tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							} else {
								if(entropy_measure_tb == 0 || max_line_ssd_tb == 0)
								{
									DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
								} else {
									DBGMSG("[D3DM2] %d - 3D TPD TOP BOTTOM %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_TB;
								}
							}
						} else {
							if(max_line_ssd_tb_inverse > (3*max_line_ssd_tb))
							{
								if(entropy_measure_tb > tpd_entropy_threshold4 || max_line_ssd_tb > tpd_ssd_threshold4)
								{
									if(entropy_measure_tb < tpd_entropy_threshold5)
									{
										if(max_line_ssd_tb > tpd_ssd_threshold5)
										{
											DBGMSG("[D3DM2] %d - 2D TPD %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD TPD TOP BOTTOM %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_3D_TB;
										}
									} else {
										if(entropy_measure_tb > tpd_entropy_threshold2 || max_line_ssd_tb > tpd_ssd_threshold2)
										{
											DBGMSG("[D3DM2] %d - 2D TB %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD TPD TOP BOTTOM %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_3D_TB;
										}
									}
								} else {
									if(entropy_measure_tb == 0 || max_line_ssd_tb == 0)
									{
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									} else {
										DBGMSG("[D3DM2] %d - 2D TPD TPD TOP BOTTOM %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_3D_TB;
									}
								}
							} else {
								if(entropy_measure_tb > tpd_entropy_threshold4 || max_line_ssd_tb > tpd_ssd_threshold4)
								{
									if(entropy_measure_tb < tpd_entropy_threshold5)
									{
										if(max_line_ssd_tb > tpd_ssd_threshold5)
										{
											DBGMSG("[D3DM2] %d - 2D TPD %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									} else {
										if(entropy_measure_tb > tpd_entropy_threshold2 || max_line_ssd_tb > tpd_ssd_threshold2)
										{
											DBGMSG("[D3DM2] %d - 2D TB %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										} else {
											DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse, max_ver_delta);
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									}
								} else {
									if(entropy_measure_tb == 0 || max_line_ssd_tb == 0)
									{
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									} else {
										DBGMSG("[D3DM2] %d - 2D TPD UNKNOWN %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
									}
								}
							}
						}
					}
				}
			}
		} else {
			if((max_line_ssd_ss < 1600) && (max_line_ssd_tb < 1600))
			{
				DBGMSG("[D3DM2] %d -  2D REPEAT UNKNOWN: %d\t%d\t\n", __L__, max_line_ssd_ss, max_line_ssd_tb);
				tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
			} else
			{
				if(ss_flag == 0)
				{
					if(entropy_measure_ss < special_hist_condition)
					{
				//		DBGMSG("[D3DM2] %d -  2D : %d\t%d\t\n", __L__, entropy_measure_ss, max_line_ssd_ss);
						tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					} else {
						if(max_line_ssd_ss > detection_threshold_ss)
						{
							if(max_line_ssd_ss > hard_constraint_2D)
							{
					//			DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_ss,max_line_ssd_ss, max_hor_delta);
								tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							} else if (max_line_ssd_ss > ((14*detection_threshold_ss) >> 3))
							{
								if(((pData->ssr > M2_delta_th || max_hor_delta > line_num*edge_thres_factor_high_line_diff)) && (entropy_measure_ss < high_entropy_th1))
								{
					//				DBGMSG("[D3DM2] %d -  Side_By_Side 3D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_SS;
								} else {
					//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_2D_2D;
								}
							} else {
								if(((pData->ssr > M2_delta_th || max_hor_delta > line_num*edge_thres_factor_high_line_diff)) && (entropy_measure_ss < high_entropy_th2))
								{
					//				DBGMSG("[D3DM2] %d -  Side_By_Side 3D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_SS;
								} else {
					//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
									tmp_fmt = LX_PE_D3D_FMT_2D_2D;
								}
							}
						} else {
							if(max_line_ssd_ss < hard_constraint_3D)
							{
								if(pData->tpd < tpd_th_for_low_line_diff)
								{
									if(max_hor_delta < line_num * edge_strong_thres_factor)
									{
										if(entropy_measure_ss < very_low_entropy_th1)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_SS;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else if(max_hor_delta < line_num*edge_thres_factor)
									{
										if(entropy_measure_ss < very_low_entropy_th2)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_SS;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else {
										tmp_fmt = LX_PE_D3D_FMT_3D_SS;
									}
								} else {
									if(max_hor_delta < line_num * edge_strong_thres_factor)
									{
										if(entropy_measure_ss < very_low_entropy_th1)
										{
											if(max_line_ssd_ss_inverse_same_line > (3*max_line_ssd_ss)>>1)
											{
												tmp_fmt = LX_PE_D3D_FMT_3D_SS;
											} else {
												tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
											}
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else if(max_hor_delta < line_num*edge_thres_factor)
									{
										if(entropy_measure_ss < very_low_entropy_th2)
										{
											if(max_line_ssd_ss_inverse_same_line > (3*max_line_ssd_ss)>>1)
											{
												tmp_fmt = LX_PE_D3D_FMT_3D_SS;
											} else {
												tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
											}
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else {
										tmp_fmt = LX_PE_D3D_FMT_3D_SS;
									}
								}
							} else {
								if(pData->tpd < tpd_th_for_low_line_diff)
								{
									if(((pData->ssr > M2_delta_th || max_hor_delta > line_num*edge_thres_factor_high_line_diff || entropy_measure_ss < very_low_entropy_th3)) && ((line_num*max_line_ssd_ss + 40*entropy_measure_ss) < low_line_entropy_th))
									{
						//				DBGMSG("[D3DM2] %d -  Side_By_Side 3D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_3D_SS;
									} else {
						//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_2D_2D;
									}
								} else {
									if(((pData->ssr > M2_delta_th || max_hor_delta > line_num*edge_thres_factor_high_line_diff)) && ((line_num*max_line_ssd_ss + 40*entropy_measure_ss) < low_line_entropy_th))
									{
						//				DBGMSG("[D3DM2] %d -  Side_By_Side 3D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										if(max_line_ssd_ss_inverse_same_line > (3*max_line_ssd_ss)>>1)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_SS;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									} else {
						//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
										tmp_fmt = LX_PE_D3D_FMT_2D_2D;
									}
								}

							}
						}
					}
				}
				else if(ss_flag == 1)
				{
					if(entropy_measure_tb < special_hist_condition)
					{
				//		DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
						tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					} else {
						if(max_line_ssd_tb > detection_threshold_tb)
						{
							if(max_line_ssd_tb > hard_constraint_2D)
							{
				//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
								tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							} else if(max_line_ssd_tb > (14*(detection_threshold_tb) >> 3))
							{
								if(((pData->tbr > M2_delta_th || max_ver_delta > width*edge_thres_factor_high_line_diff)) && (entropy_measure_tb < high_entropy_th1))
								{
				//					DBGMSG("[D3DM2] %d -  TOPBOTTOM 3D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_TB;
								} else {
				//					DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_2D_2D;
								}
							} else {
								if(((pData->tbr > M2_delta_th || max_ver_delta > width*edge_thres_factor_high_line_diff)) && (entropy_measure_tb < high_entropy_th2))
								{
				//					DBGMSG("[D3DM2] %d -  TOPBOTTOM 3D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_3D_TB;
								} else {
				//					DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
									tmp_fmt = LX_PE_D3D_FMT_2D_2D;
								}
							}
						} else {
							if(max_line_ssd_tb < hard_constraint_3D)
							{
								if(pData->tpd < tpd_th_for_low_line_diff)
								{
									if(max_ver_delta < width * edge_strong_thres_factor)
									{
										if(entropy_measure_tb < very_low_entropy_th1)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_TB;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else if(max_ver_delta < width*edge_thres_factor)
									{
										if(entropy_measure_tb < very_low_entropy_th2)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_TB;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else {
										tmp_fmt = LX_PE_D3D_FMT_3D_TB;
									}
								} else {
									if(max_ver_delta < width * edge_strong_thres_factor)
									{
										if(entropy_measure_tb < very_low_entropy_th1)
										{
											if(max_line_ssd_tb_inverse_same_line > (3*max_line_ssd_tb)>>1)
											{
												tmp_fmt = LX_PE_D3D_FMT_3D_TB;
											} else {
												tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
											}
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else if(max_ver_delta < width*edge_thres_factor)
									{
										if(entropy_measure_tb < very_low_entropy_th2)
										{
											if(max_line_ssd_tb_inverse_same_line > (3*max_line_ssd_tb)>>1)
											{
												tmp_fmt = LX_PE_D3D_FMT_3D_TB;
											} else {
												tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
											}
										} else {
											tmp_fmt = LX_PE_D3D_FMT_2D_2D;
										}
									} else {
										tmp_fmt = LX_PE_D3D_FMT_3D_TB;
									}
								}
							} else {
								if(pData->tpd < tpd_th_for_low_line_diff)
								{
									if((pData->tbr > M2_delta_th || (max_ver_delta > width*edge_thres_factor_high_line_diff)|| entropy_measure_tb < very_low_entropy_th3) && ((line_num*max_line_ssd_tb + 40*entropy_measure_tb) < low_line_entropy_th))
									{
						//				DBGMSG("[D3DM2] %d -  TOPBOTTOM 3D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_3D_TB;
									} else {
						//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_2D_2D;
									}
								} else {
									if((pData->tbr > M2_delta_th || (max_ver_delta > width*edge_thres_factor_high_line_diff)) && ((line_num*max_line_ssd_tb + 40*entropy_measure_tb) < low_line_entropy_th))
									{
						//				DBGMSG("[D3DM2] %d -  TOPBOTTOM 3D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										if(max_line_ssd_tb_inverse_same_line > (3*max_line_ssd_tb)>>1)
										{
											tmp_fmt = LX_PE_D3D_FMT_3D_TB;
										} else {
											tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
										}
									} else {
						//				DBGMSG("[D3DM2] %d -  2D : %d\t%d\t%d\n", __L__, entropy_measure_tb, max_line_ssd_tb, max_ver_delta);
										tmp_fmt = LX_PE_D3D_FMT_2D_2D;
									}
								}
							}
						}
					}
				}
				else
				{
					DBGMSG("Error\n");
				}
			}

		}

	}

	if(tpd_strong_2D_cond_ss == 1 || tpd_strong_2D_cond_tb == 1)
	{
		DBGMSG("[D3DM2] %d - 2D MONO_INVALID %d\t%d\t%d\n", __L__, entropy_measure_ss, max_line_ssd_ss, max_hor_delta);
		tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
	}

	if(pData->tpd <= pThr->tpd_thr)
	{
		if(tmp_fmt == LX_PE_D3D_FMT_3D_TB || tmp_fmt == LX_PE_D3D_FMT_3D_SS)
		{
			if(ss_flag == 0)
			{
			//	if(max_line_ssd_ss > ((3*max_line_ssd_ss_inverse_same_line)>>1))
			//	{
			//		DBGMSG("[D3DM2] %d - 2D SS in M2 by Inverse LineDiff [%d]\t%d\t%d\n", __L__, pData->tpd, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line);
			//		tmp_fmt = LX_PE_D3D_FMT_2D_2D;
			//	} else {
					DBGMSG("[D3DM2] %d - Side_By_Side 3D : [%d]\t%d\t%d\t%d\t%d\n", __L__, pData->tpd, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line, max_hor_delta);
					tmp_fmt = LX_PE_D3D_FMT_3D_SS;
			//	}
			} else {
			//	if(max_line_ssd_tb > ((3*max_line_ssd_tb_inverse_same_line)>>1))
			//	{
			//		DBGMSG("[D3DM2] %d - 2D TB in M2 by Inverse LineDiff [%d]%d\t%d\n", __L__, pData->tpd, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line);
			//		tmp_fmt = LX_PE_D3D_FMT_2D_2D;
			//	} else {
					DBGMSG("[D3DM2] %d - TOPBOTTOM 3D : [%d]\t%d\t%d\t%d\t%d\n", __L__, pData->tpd, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line, max_ver_delta);
					tmp_fmt = LX_PE_D3D_FMT_3D_TB;
			//	}
			}
		} else {

			if(tmp_fmt == LX_PE_D3D_FMT_UNKNOWN)
			{
				DBGMSG("[D3DM2] %d - 2D UNKNOWN BY Repeat : [%d]\t%d\t%d\n", __L__, pData->tpd, max_line_ssd_ss, max_line_ssd_tb);
			} else {
				if(ss_flag == 0)
				{
					DBGMSG("[D3DM2] %d - 2D SS : [%d]\t%d\t%d\t%d\t%d\n", __L__, pData->tpd, entropy_measure_ss, max_line_ssd_ss, max_line_ssd_ss_inverse_same_line, max_hor_delta);
				} else {
					DBGMSG("[D3DM2] %d - 2D TB : [%d]\t%d\t%d\t%d\t%d\n", __L__, pData->tpd, entropy_measure_tb, max_line_ssd_tb, max_line_ssd_tb_inverse_same_line, max_ver_delta);
				}
			}

		}
	}

	pCfg->tmp_fmt = tmp_fmt;

	//DBGMSG("line ssd : %d %d\n", (unsigned int)max_line_ssd_ss, (unsigned int)max_line_ssd_tb);
	return 0;
}

#endif // #ifdef PE_D3D_USE_LINE_DIFF_BY_SW

