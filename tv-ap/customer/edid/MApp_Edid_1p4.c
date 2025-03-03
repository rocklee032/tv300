
#if (ENABLE_HDMI_4K_2K)

#if 1 // 1.4 3D, 4K
static U8 EDID_DVI_0[256]=
{
           /*-------------------------------------------------------------------------------*/
    /*00*/ 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x36,0x74,0x30,0x00,0x01,0x00,0x00,0x00,
    /*10*/ 0x0A,0x16,0x01,0x03,0x80,0x73,0x41,0x78,0x0A,0xCF,0x74,0xA3,0x57,0x4C,0xB0,0x23,
    /*20*/ 0x09,0x48,0x4C,0x21,0x08,0x00,0x81,0x80,0x45,0x40,0x61,0x40,0x95,0x00,0x01,0x01,
    /*30*/ 0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    /*40*/ 0x45,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
    /*50*/ 0x40,0x70,0x36,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFC,0x00,0x4D,
    /*60*/ 0x53,0x74,0x61,0x72,0x20,0x44,0x65,0x6D,0x6F,0x0A,0x20,0x20,0x00,0x00,0x00,0xFD,
    /*70*/ 0x00,0x32,0x4B,0x1E,0x50,0x17,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0xF1,
    /*80*/ 0x02,0x03,0x30,0xF2,0x4D,0x01,0x03,0x04,0x05,0x07,0x90,0x12,0x13,0x14,0x16,0x9F,
    /*90*/ 0x20,0x22,0x26,0x09,0x07,0x07,0x11,0x17,0x50,0x83,0x01,0x00,0x00,0x72,0x03,0x0C,
    /*A0*/ 0x00,0x10,0x00,0xB8,0x44,0x20,0xC0,0x84,0x01,0x02,0x03,0x04,0x01,0x41,0x00,0x00,
    /*B0*/ 0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xC4,0x8E,0x21,0x00,
    /*C0*/ 0x00,0x18,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,0xC4,0x8E,
    /*D0*/0x21,0x00,0x00,0x18,0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,0x28,0x55,0x40,
    /*E0*/ 0xC4,0x8E,0x21,0x00,0x00,0x1E,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,
    /*F0*/ 0x25,0x80,0xC4,0x8E,0x21,0x00,0x00,0x9E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6F,

};
#define EDID_PA_POS         0xA1    //0xA1, 0xA2 is physical address
#endif

#elif( ENABLE_3D_PROCESS )

#if 1 // 3D, 1080p(No 4K)
static U8 EDID_DVI_0[256]=
{  /*    00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
       -------------------------------------------------------------------------------*/
/*00*/ 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x36,0x74,0x30,0x00,0x01,0x00,0x00,0x00,
/*10*/ 0x0A,0x16,0x01,0x03,0x80,0x73,0x41,0x78,0x0A,0xCF,0x74,0xA3,0x57,0x4C,0xB0,0x23,
/*20*/ 0x09,0x48,0x4C,0x21,0x08,0x00,0x81,0x80,0x45,0x40,0x61,0x40,0x95,0x00,0x01,0x01,
/*30*/ 0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
/*40*/ 0x45,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
/*50*/ 0x40,0x70,0x36,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFC,0x00,0x4D,
/*60*/ 0x53,0x74,0x61,0x72,0x20,0x44,0x65,0x6D,0x6F,0x0A,0x20,0x20,0x00,0x00,0x00,0xFD,
/*70*/ 0x00,0x32,0x4B,0x1E,0x50,0x17,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0xF1,
/*80*/ 0x02,0x03,0x2C,0xF2,0x4D,0x01,0x03,0x04,0x05,0x07,0x90,0x12,0x13,0x14,0x16,0x9F,
/*90*/ 0x20,0x22,0x26,0x09,0x07,0x07,0x11,0x17,0x50,0x83,0x01,0x00,0x00,0x6E,0x03,0x0C,
/*A0*/ 0x00,0x10,0x00,0xB8,0x2D,0x20,0xC0,0x04,0x01,0x41,0x00,0x00,0x8C,0x0A,0xD0,0x8A,
/*B0*/ 0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xC4,0x8E,0x21,0x00,0x00,0x18,0x8C,0x0A,
/*C0*/ 0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,0xC4,0x8E,0x21,0x00,0x00,0x18,
/*D0*/ 0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,0x28,0x55,0x40,0xC4,0x8E,0x21,0x00,
/*E0*/ 0x00,0x1E,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,0x25,0x80,0xC4,0x8E,
/*F0*/ 0x21,0x00,0x00,0x9E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
};
#define EDID_PA_POS         0xA1    //0xA1, 0xA2 is physical address
#endif

#else

#if 1 // 1.4 No 3D, No 4K
static U8 EDID_DVI_0[256]=
{  /*    00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
       -------------------------------------------------------------------------------*/
/*00*/ 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x36,0x74,0x30,0x00,0x01,0x00,0x00,0x00,
/*10*/ 0x0A,0x16,0x01,0x03,0x80,0x73,0x41,0x78,0x0A,0xCF,0x74,0xA3,0x57,0x4C,0xB0,0x23,
/*20*/ 0x09,0x48,0x4C,0x21,0x08,0x00,0x81,0x80,0x45,0x40,0x61,0x40,0x95,0x00,0x01,0x01,
/*30*/ 0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
/*40*/ 0x45,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x66,0x21,0x50,0xB0,0x51,0x00,0x1B,0x30,
/*50*/ 0x40,0x70,0x36,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFC,0x00,0x4D,
/*60*/ 0x53,0x74,0x61,0x72,0x20,0x44,0x65,0x6D,0x6F,0x0A,0x20,0x20,0x00,0x00,0x00,0xFD,
/*70*/ 0x00,0x32,0x4B,0x1E,0x50,0x17,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0xF1,
/*80*/ 0x02,0x03,0x25,0xF2,0x4D,0x01,0x03,0x04,0x05,0x07,0x90,0x12,0x13,0x14,0x16,0x9F,
/*90*/ 0x20,0x22,0x26,0x09,0x07,0x07,0x11,0x17,0x50,0x83,0x01,0x00,0x00,0x67,0x03,0x0C,
/*A0*/ 0x00,0x10,0x00,0xB8,0x2D,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,
/*B0*/ 0x00,0xC4,0x8E,0x21,0x00,0x00,0x18,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,
/*C0*/ 0x40,0x55,0x00,0xC4,0x8E,0x21,0x00,0x00,0x19,0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,
/*D0*/ 0x20,0xB8,0x28,0x55,0x40,0xC4,0x8E,0x21,0x00,0x00,0x1F,0x01,0x1D,0x80,0xD0,0x72,
/*E0*/ 0x1C,0x16,0x20,0x10,0x2C,0x25,0x80,0xC4,0x8E,0x21,0x00,0x00,0x9F,0x00,0x00,0x00,
/*F0*/ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x49,
};
#define EDID_PA_POS         0xA1    //0xA1, 0xA2 is physical address
#endif

#endif

