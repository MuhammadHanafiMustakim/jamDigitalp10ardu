
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#define BIGNUMBER_WIDTH 6
#define BIGNUMBER_HEIGHT -16

const static uint8_t BigNumber[] PROGMEM = {
    0x03, 0xD0, 
    0x06, 
    0x10, 
    0x30, 
	0x0B,
    //0x0A, 
    
   
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x01,
    
   
    /*0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, // 48/0
    0x08, 0x0C, 0xFE, 0xFE, 0x00, 0x00, 0x40, 0x40, 0x7F, 0x7F, 0x40, 0x40, // 49/1
    0x0C, 0x0E, 0x02, 0xC2, 0xFE, 0x3C, 0x70, 0x7C, 0x6F, 0x63, 0x60, 0x60, // 50/2
    0x0C, 0x8E, 0x82, 0x82, 0xFE, 0x7C, 0x30, 0x71, 0x41, 0x41, 0x7F, 0x3E, // 51/3
    0x80, 0xE0, 0x78, 0xFE, 0xFE, 0x00, 0x0F, 0x0F, 0x48, 0x7F, 0x7F, 0x48, // 52/4
    0x7E, 0x7E, 0x22, 0x22, 0xE2, 0xC2, 0x30, 0x70, 0x40, 0x40, 0x7F, 0x3F, // 53/5
    0xF0, 0xF8, 0x4C, 0x46, 0xC2, 0x82, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, // 54/6
    0x02, 0x02, 0x02, 0xE2, 0xFE, 0x1E, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, // 55/7
    0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, // 56/8
    0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x41, 0x43, 0x62, 0x32, 0x1F, 0x0F, // 57/9
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x41,0x00, 0x00, 0x00, 0x00, 0x00 // :*/
    //=====================================================
	252,254,2,2,254,252,63,127,64,64,127,63,  //0
	8,12,254,254,0,0,64,64,127,127,64,64,  //1
	12,14,2,194,254,124,112,124,111,99,96,96,  //2
	12,142,130,130,254,124,48,113,65,65,127,62,  //3
	128,224,120,254,254,0,15,15,72,127,127,72,  //4
	126,126,34,34,226,194,48,112,64,64,127,63,  //5
	240,248,76,70,194,130,63,127,64,64,127,63,  //6
	2,2,2,226,254,30,0,0,127,127,0,0,  //7
	124,254,130,130,254,124,62,127,65,65,127,62,  //8
	252,254,2,2,254,252,65,67,98,50,31,15,  //9
	0,0,48,48,0,0,0,0,12,12,0,0,  //:
	//======================================================

};

#endif
