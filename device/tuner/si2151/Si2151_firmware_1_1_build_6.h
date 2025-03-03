#ifndef _SI2151_FIRMWARE_1_1_BUILD_6_H_
#define _SI2151_FIRMWARE_1_1_BUILD_6_H_

#define FIRMWARE_MAJOR        1
#define FIRMWARE_MINOR        1
#define BUILD_VERSION         6

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

firmware_struct Si2151_FW_1_1b6[] = {
{ 8 , { 0x05,0x11,0xC6,0x3B,0x2C,0xE5,0x01,0xC7 } },
{ 16 , { 0x0C,0x79,0xF5,0x17,0x90,0x34,0xD9,0x3B,0x0C,0x14,0x9A,0x06,0x9F,0x1B,0x1C,0x29 } },
{ 14 , { 0x42,0x70,0xFC,0x0C,0x88,0x22,0x54,0x4E,0xE8,0xF0,0xEF,0x42,0xAB,0x7F } },
{ 11 , { 0x0C,0x0B,0xA8,0x23,0xBC,0x87,0x46,0x21,0x42,0x07,0x10 } },
{ 16 , { 0x08,0x67,0xE3,0x03,0x84,0x47,0x27,0x66,0x0C,0x9E,0x29,0x79,0xC5,0xA7,0xC5,0xF2 } },
{ 14 , { 0x4A,0xAD,0x98,0x0C,0x82,0x65,0x89,0xEB,0x26,0xA9,0x43,0x4A,0x1D,0x4D } },
{ 11 , { 0x0C,0x74,0xA3,0x27,0x37,0xC8,0xE4,0x72,0x4A,0x36,0x55 } },
{ 8 , { 0x0C,0xAE,0x69,0x86,0xCB,0x8D,0x97,0xCB } },
{ 16 , { 0x3F,0x81,0xCC,0x70,0x6F,0xBF,0x03,0x3A,0x22,0x15,0xB0,0xBB,0x55,0x80,0xC1,0x88 } },
{ 16 , { 0x3F,0xD3,0x2E,0x13,0x7A,0x8D,0x78,0xEC,0xC1,0x48,0x79,0x5D,0x63,0x4F,0x43,0x75 } },
{ 16 , { 0x3F,0xE1,0x12,0x7E,0xD5,0xAE,0x87,0x5F,0x32,0xB5,0x9E,0x5D,0xF8,0x7D,0xBC,0x6F } },
{ 12 , { 0x43,0xE4,0x9D,0xF1,0x08,0xBA,0x94,0xB1,0xE3,0xA4,0xA6,0x2D } },
{ 8 , { 0x08,0x34,0x66,0x39,0xDA,0x02,0x43,0x51 } },
{ 16 , { 0x37,0x8C,0x20,0x90,0xCE,0xFA,0x21,0xC8,0xAF,0xE5,0x40,0xE5,0x35,0x67,0xCA,0xCD } },
{ 16 , { 0x3F,0x42,0x51,0x3B,0x84,0xEC,0x02,0xB7,0x38,0x13,0x8E,0x9A,0xBC,0x0F,0xD3,0x9E } },
{ 16 , { 0x37,0x3A,0xEC,0x4A,0xC1,0x9A,0xF6,0x3F,0xE5,0x43,0x9F,0xF2,0x55,0x85,0xFB,0x69 } },
{ 16 , { 0x3F,0x28,0x21,0x9B,0xE5,0x04,0x4A,0xB1,0x6C,0x7F,0x0A,0xDE,0x49,0x70,0x89,0x31 } },
{ 16 , { 0x37,0x0F,0x42,0x2B,0xCA,0x18,0xD5,0xA3,0xC3,0x32,0xBB,0x85,0xF2,0xF6,0x6E,0xB6 } },
{ 16 , { 0x3F,0x9C,0x20,0xC3,0x04,0xDA,0x79,0x9C,0x15,0x19,0x1A,0x43,0x26,0x68,0x1E,0x5D } },
{ 16 , { 0x3F,0xC9,0xA4,0x5E,0x09,0x81,0xC7,0xC6,0x37,0xDB,0xD4,0xAF,0x66,0x3B,0x7F,0xA1 } },
{ 15 , { 0x46,0x7B,0xB3,0x9B,0xD9,0x0F,0xF6,0x08,0xA2,0xD8,0xB6,0x76,0x7B,0x61,0xCE } },
{ 12 , { 0x4B,0xAE,0xC8,0xB7,0x09,0x16,0x1E,0xE8,0x9A,0x41,0xBB,0x81 } },
{ 16 , { 0x37,0x98,0xA2,0xC7,0x3A,0x12,0x7B,0xC3,0x73,0xA9,0xAF,0xDF,0xEB,0xDD,0x60,0x85 } },
{ 16 , { 0x3F,0x51,0x7D,0xFA,0x6D,0xD0,0xA2,0x33,0xFF,0x7B,0x28,0xEC,0xD9,0x33,0x73,0x58 } },
{ 16 , { 0x37,0xBD,0x4C,0xFF,0xF6,0x60,0xA2,0x97,0x0D,0x9B,0xFE,0xB5,0xB7,0xC6,0x42,0x63 } },
{ 16 , { 0x47,0xAE,0x99,0x1C,0xB4,0x4D,0xFE,0xC3,0x09,0x65,0xF4,0x7E,0xBE,0x35,0x2C,0xA7 } },
{ 16 , { 0x37,0xD7,0x80,0xEC,0x5C,0xD5,0x92,0xD6,0x0C,0x1E,0x86,0xDD,0x0C,0x8F,0xF1,0x25 } },
{ 13 , { 0x3C,0x99,0x14,0xD5,0x16,0xAE,0x73,0xCB,0xA0,0x10,0xD9,0x02,0x85 } },
{ 8 , { 0x08,0xD4,0xF7,0x87,0xDE,0x03,0x11,0xF9 } },
{ 16 , { 0x3F,0xFE,0x67,0x93,0x84,0x9C,0xE9,0xD7,0x43,0x1B,0x1D,0x14,0xA4,0x11,0x4F,0x6C } },
{ 16 , { 0x3F,0xC7,0x05,0x2D,0xA2,0x04,0x01,0x26,0x06,0x89,0x10,0xF3,0xC6,0x8D,0xE1,0xEC } },
{ 16 , { 0x3F,0x54,0x60,0xE9,0x64,0x2C,0x54,0xE3,0x7E,0x27,0x78,0x6C,0xE6,0xB4,0x94,0xC8 } },
{ 11 , { 0x3A,0x5A,0x29,0xE0,0x9D,0xF5,0x3F,0x05,0x3E,0x17,0x2F } },
{ 16 , { 0x09,0x84,0x7D,0x2E,0x3E,0xEA,0x07,0x47,0x0C,0x0A,0x5C,0x4F,0xA4,0x03,0xA1,0xF6 } },
{ 16 , { 0x3F,0x35,0xCD,0x77,0x8A,0xD4,0x9E,0xA9,0xFA,0x8B,0x89,0xD4,0xB5,0x93,0x8F,0x5F } },
{ 16 , { 0x37,0xF2,0xED,0xF2,0xCF,0xC0,0xB9,0xB3,0x84,0xC5,0x22,0x69,0x2A,0x69,0xF0,0x50 } },
{ 10 , { 0x31,0xB7,0x08,0xA5,0x49,0xB8,0x78,0x6B,0x62,0x1F } },
{ 8 , { 0x08,0x16,0x0C,0x88,0x12,0xDE,0x81,0x73 } },
{ 14 , { 0x35,0x45,0xC3,0x3C,0x41,0x90,0x2E,0xDE,0xA2,0x44,0x39,0xB9,0x19,0x68 } },
{ 8 , { 0x08,0x74,0xEB,0xD9,0x52,0xD2,0xB7,0xA5 } },
{ 16 , { 0x37,0xBC,0x41,0x26,0x62,0x01,0xEF,0xFF,0xF4,0xD4,0x66,0x25,0x85,0xA3,0xDA,0x0A } },
{ 16 , { 0x3F,0xD8,0xC8,0x57,0xFB,0x70,0xAE,0x2F,0x2A,0x2A,0xF9,0x51,0xE3,0xBE,0x50,0x52 } },
{ 16 , { 0x3F,0x12,0x32,0x1F,0x5F,0xC3,0x71,0x43,0x1F,0x02,0x07,0xEB,0xB7,0xC5,0x54,0x7D } },
{ 16 , { 0x37,0xF5,0xBC,0xB2,0xE0,0xDC,0x0C,0x3E,0x26,0x5B,0xF4,0xA1,0xD4,0xE9,0xA0,0xE1 } },
{ 13 , { 0x44,0x2D,0xE9,0xAE,0xAC,0x09,0x79,0x7F,0x7B,0xB5,0xD7,0xBF,0x04 } },
{ 16 , { 0x37,0x9E,0xBF,0x76,0x55,0x09,0x49,0x9A,0x40,0x44,0xEE,0x94,0x15,0xD3,0x26,0xD2 } },
{ 8 , { 0x09,0xEE,0x93,0xCB,0x41,0x7B,0x1A,0x14 } },
{ 16 , { 0x3F,0xFE,0x08,0xBD,0xFE,0xE6,0xEB,0x83,0x16,0x1A,0xE9,0x78,0xEA,0x69,0x9E,0x9B } },
{ 16 , { 0x3F,0xD1,0x9E,0x63,0x69,0x66,0x91,0x42,0xF6,0x93,0x0B,0xD6,0x85,0x4F,0xA4,0x6E } },
{ 13 , { 0x3C,0x7B,0xBE,0x1C,0x3A,0xFF,0x64,0xDB,0x5E,0x43,0x8C,0xCC,0xAA } },
{ 16 , { 0x09,0x3D,0x21,0xC7,0x67,0x9A,0x24,0x76,0x09,0xA0,0x2F,0x16,0xD4,0x8C,0xCC,0x20 } },
{ 8 , { 0x09,0xFF,0x3A,0xBE,0xBD,0x76,0x72,0x76 } },
{ 16 , { 0x3F,0xB8,0x85,0x3F,0x44,0xC6,0xCD,0x8E,0x40,0x0B,0xF1,0x67,0xE4,0x26,0x51,0xF1 } },
{ 10 , { 0x31,0x1C,0xA7,0x60,0x30,0x49,0x21,0xB6,0x38,0xB4 } },
{ 8 , { 0x09,0x9D,0xD8,0x3D,0x0B,0x95,0xB9,0x54 } },
{ 10 , { 0x31,0xB4,0x25,0xBC,0xC9,0x68,0x8E,0xF0,0x67,0x11 } },
{ 8 , { 0x09,0xBE,0x0E,0x26,0x91,0x06,0x55,0x85 } },
{ 16 , { 0x3F,0x76,0xB3,0x7D,0xAF,0x52,0x1F,0x4E,0x4C,0x9B,0xFB,0x36,0xB8,0x81,0x4C,0xFD } },
{ 16 , { 0x3F,0x80,0xF9,0xC4,0x55,0x70,0x47,0xDD,0xB9,0xC1,0xFC,0x05,0x02,0x68,0x38,0x70 } },
{ 15 , { 0x46,0x93,0x7B,0x0D,0x93,0xA5,0x64,0x09,0xE5,0x92,0xEF,0x43,0xD4,0x2B,0xDC } },
{ 13 , { 0x34,0x3D,0xF3,0xB3,0xB8,0x9D,0xAD,0xE0,0x19,0x77,0x85,0xD6,0xDF } },
{ 12 , { 0x0C,0x10,0x85,0x94,0x57,0x6E,0xF3,0x2D,0x43,0x93,0xEE,0x13 } },
{ 16 , { 0x08,0x71,0xB3,0xF7,0x6E,0x7A,0xDF,0x7A,0x0C,0xEC,0xF5,0x71,0xB1,0x7D,0x13,0xF8 } },
{ 12 , { 0x43,0x67,0x1C,0xD5,0x09,0x4F,0xA6,0xEC,0x8C,0xA6,0x0C,0xEB } },
{ 11 , { 0x0C,0xDA,0x1D,0x7E,0x85,0x5E,0x15,0x6B,0x4A,0xFC,0xC2 } },
{ 12 , { 0x0C,0x00,0x14,0x70,0x18,0x9D,0xB7,0xF4,0x4B,0x88,0xCF,0x0B } },
{ 16 , { 0x08,0xD1,0x16,0x8D,0x69,0x14,0x3B,0xEF,0x0C,0x09,0xEE,0xC0,0x45,0x42,0xC6,0x5D } }
};

#define FIRMWARE_LINES_1_1b6 (sizeof(Si2151_FW_1_1b6)/(sizeof(firmware_struct)))
#define RAM_SIG_1_1b6 0x8015C347
#define RAM_CRC_1_1b6 0x31A1

#endif /* _SI2151_FIRMWARE_1_1_BUILD_6_H_ */
