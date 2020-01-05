static const CVD_REG_PARAM_T cvd_av_secam_l_default[] = 
{
    {0x42B4, 0x00000202},   // Peak
    {0x42B8, 0x00020011},   // Auto SECAM Level
    {0x42EC, 0x00008FF4},   // Dr Freq
    {0x42C0, 0x00000010},   // Db Freq
    {0x4650, 0x02700041},   // CTA    
    {0x46A0, 0x00001080},   // SECAM DCR
    {0x46A4, 0x00000000},
    {0x46A8, 0x0C030A08},
    {0x46AC, 0x10080014},
    {0x4768, 0x08000003},   // Cordic
    {0x476C, 0x08000003},   // Cordic
    {0x4770, 0x08000003},   // Cordic
    {0x4678, 0x00000000},
    {0x4654, 0x00000000},
    {0x45CC, 0x00000000},
    {0x4414, 0x00000017},
    {0x46D4, 0x40000000},
    {0x4620, 0x00010903}, // 0x00000902},
    {0x4624, 0x00000100},
    {0x45C8, 0x00000000},   // *
    {0x45B0, 0x00000000},
    {0x469C, 0x00000000},
    {0x4570, 0x00000000},
    {0x4588, 0x00000000},
    {0x4560, 0x00000000},
    {0x4544, 0x00000000},
    {0x45E8, 0x00000000},
    {0x456C, 0x00000000},
    {0x45B8, 0x00000000},
    {0x4598, 0x00000000},
    {0x4574, 0x00000000},
    {0x4578, 0x00000000},
    {0x457C, 0x00000000},
    {0x4580, 0x00000000},
    {0x4584, 0x00000000},
    {0x458C, 0x00000000},
    {0x4630, 0x00000000},
    {0x4718, 0x00000000},
    {0x4734, 0x00000000},
    {0x471C, 0x00000000},
    {0x4720, 0x00000000},
    {0x4724, 0x00000000},
    {0x4728, 0x00000000},
    {0x47C8, 0x00000000},
    {0x47BC, 0x00000000},
    {0x47CC, 0x00000000},
    {0x47C0, 0x00000000},
    {0x47C4, 0x00000000},   //*
    {0x45F4, 0x00000031}, // 0x00000030},
    {0x45F8, 0x00000000},
    {0x46D0, 0x00000000},   //* *//
    {0x45FC, 0x00800080},    
    {0x4600, 0x00000000},
    {0x4604, 0x00000000},
    {0x4608, 0x00000000},
    {0x4634, 0x00000000},
    {0x4638, 0x00000000},
    {0x4250, 0x00000000},
    {0x455C, 0x00000000},   //*
    {0x4548, 0x00000000},
    {0x46D8, 0x00000000},
    {0x454C, 0x00000000},
    {0x4554, 0x00000000},
    {0x46DC, 0x00000000},
    {0x4550, 0x00000000},
    {0x4558, 0x00000000},
    {0x4568, 0x00000000},
    {0x45B4, 0x00000000},
    {0x46EC, 0x00000000},
    {0x46E8, 0x00000000},
    {0x46F0, 0x00000000},
    {0x45D8, 0x00000000},
    {0x45DC, 0x00000000},
    {0x45E0, 0x00000000},
    {0x45E4, 0x00000000},
    {0x45C0, 0x00000000},
    {0x45C4, 0x00000000},
    {0x4640, 0x00000000},
    {0x4644, 0x00000000},
    {0x46BC, 0x00000000},
    {0x4740, 0x00000000},
    {0x4744, 0x00000000},
    {0x4748, 0x00000000},
    {0x474C, 0x00000000},
    {0x4764, 0x00000000},
    {0x4750, 0x00000000},
    {0x4788, 0x00000000},
    {0x4784, 0x00000000},
    {0x4758, 0x00000000},
    {0x475C, 0x00000000},
    {0x4760, 0x00000000},
    {0x45BC, 0x00000000},
    {0x46F8, 0x00000000},
    {0x46FC, 0x00000000},
    {0x470C, 0x00000000},
    {0x4704, 0x00000000},
    {0x4700, 0x00000000},
    {0x4708, 0x00000000},
    {0x45EC, 0x00000000},
    {0x45F0, 0x00000000},
    {0x4590, 0x00000000},
    {0x4594, 0x00000000},
    {0x459C, 0x00000000},
    {0x472C, 0x00000000},
    {0x4730, 0x00000000},
    {0x45A0, 0x00000000},
    {0x45A4, 0x00000000},
    {0x45AC, 0x00000000},
    {0x4738, 0x00000000},
    {0x473C, 0x00000000},
    {0x45A8, 0x00000000},   //*
    {0x4418, 0x00001130},
    {0x4410, 0x00000000},
    {0x441C, 0x00010000},   // AAF_9p0_F_K5
    {0x4420, 0xFEF5FD1D},
    {0x4424, 0x00000DA2},
    {0x4428, 0x21092A86},
    {0x439C, 0x0011038A},
    {0x43A0, 0x01031F8F},
    {0x43A4, 0x1FD00010},
    {0x43A8, 0x00000003},
    {0x43AC, 0x00010380},
    {0x43B0, 0x00EE1FA9},
    {0x43B4, 0x1FE60003},
    {0x43B8, 0x00000000},
    {0x43BC, 0x00010100},
    {0x43C0, 0x0077E77C},
    {0x43C4, 0x0000077C},
    {0x43C8, 0x0077C000},
    {0x43CC, 0x0077C77E},
    {0x43D0, 0x00020020},
    {0x43D4, 0x00002000},
    {0x43D8, 0x00030000},
    {0x460C, 0x007FF00C},
    {0x4610, 0x007C0135},
    {0x4614, 0x001357C0},
    {0x4618, 0x0000C7FF},
    {0x43DC, 0x0F000001},   // OADJ
    {0x43E0, 0x00001014},
    {0x43E4, 0x006001FF},	
    {0x43E8, 0x131F0DE4},	
    {0x43EC, 0x06001FF0}
};
