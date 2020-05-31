#include <stdio.h>
#include <Crc.h>
#include <stdint.h>

#define Crc_8_Polynomial            0x1D
#define Crc_8_8H2FPolynomial        0x2F
#define Crc_16_CCITTPolynomial      0x1021U
#define Crc_32_Polynomial           0x04C11DB7U
#define Crc_32P4_Polynomial         0xF4ACFB13U
#define CRC_64_Polynomial           0x42F0E1EBA9EA3693U
#define Crc_8_Xor               0xFFU
#define Crc_8_8H2FXor           0xFFU
#define Crc_16_CCITTXor           0x0000U
#define Crc_32_Xor           0xFFFFFFFFU
#define Crc_32P4_Xor           0xFFFFFFFFU
#define CRC_64_Xor           0xFFFFFFFFFFFFFFFFU


typedef struct crc_data_s
{
	uint8_t data[128];
	uint8_t data_len;
	uint64_t data_crc;
}CRC_DATA_S;

void Crc_CalculateCRC8_test()
{
	uint8_t crc;
    uint8_t check;
    uint8_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0x59},
	{{0xf2,0x01,0x83},								3,0x37},
	{{0x0f,0xaa,0x00,0x55}, 						4,0x79},
	{{0x00,0xff,0x55,0x11}, 						4,0xb8},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0xcb},
	{{0x92,0x6b,0x55},								3,0x8c},
	{{0xff,0xff,0xff,0xff},							4,0x74}
	};
	printf("Crc_CalculateCRC8 test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC8(crc_test_data[i].data,crc_test_data[i].data_len,0xff,1);
        crc_test_data[i].data[crc_test_data[i].data_len] = crc;
        check = Crc_CalculateCRC8(crc_test_data[i].data,crc_test_data[i].data_len+1,0xff,1);
        magiccheck = check ^ Crc_8_Xor;
		printf("result[%d] check[0x%x,0x%0x] crc=0x%x,0x%x\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
	
}
void Crc_CalculateCRC8H2F_test()
{
	uint8_t crc;
    uint8_t check;
    uint8_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0x12},
	{{0xf2,0x01,0x83},								3,0xc2},
	{{0x0f,0xaa,0x00,0x55}, 						4,0xc6},
	{{0x00,0xff,0x55,0x11}, 						4,0x77},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0x11},
	{{0x92,0x6b,0x55},								3,0x33},
	{{0xff,0xff,0xff,0xff},							4,0x6c}
	};
	printf("Crc_CalculateCRC8H2F test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC8H2F(crc_test_data[i].data,crc_test_data[i].data_len,0xff,1);
        crc_test_data[i].data[crc_test_data[i].data_len] = crc;
        check = Crc_CalculateCRC8H2F(crc_test_data[i].data,crc_test_data[i].data_len+1,0xff,1);
        magiccheck = check ^ Crc_8_8H2FXor;
		printf("result[%d] check[0x%x,0x%x] crc=0x%x,0x%x\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
}

void Crc_CalculateCRC16_test()
{
	uint16_t crc;
    uint16_t check;
    uint16_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0x84c0},
	{{0xf2,0x01,0x83},								3,0xd374},
	{{0x0f,0xaa,0x00,0x55}, 						4,0x2023},
	{{0x00,0xff,0x55,0x11}, 						4,0xb8f9},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0xf53f},
	{{0x92,0x6b,0x55},								3,0x0745},
	{{0xff,0xff,0xff,0xff},							4,0x1d0f}
	};
	printf("Crc_CalculateCRC16 test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC16(crc_test_data[i].data,crc_test_data[i].data_len,0xffff,1);
        for(int j=0;j<sizeof(crc);j++)
            crc_test_data[i].data[crc_test_data[i].data_len + j] = (crc >> j*8) & 0xff;
        check = Crc_CalculateCRC16(crc_test_data[i].data,crc_test_data[i].data_len+sizeof(crc),0xffff,1);
        magiccheck = check ^ Crc_16_CCITTXor;
		printf("result[%d] check[0x%x,0x%x] crc=0x%x,0x%x\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
}

void Crc_CalculateCRC32_test()
{
	uint32_t crc;
    uint32_t check;
    uint32_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0x2144df1c},
	{{0xf2,0x01,0x83},								3,0x24ab9d77},
	{{0x0f,0xaa,0x00,0x55}, 						4,0xb6c9b287},
	{{0x00,0xff,0x55,0x11}, 						4,0x32a06212},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0xb0ae863d},
	{{0x92,0x6b,0x55},								3,0x9cdea29b},
	{{0xff,0xff,0xff,0xff},							4,0xffffffff}
	};
	printf("Crc_CalculateCRC32 test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC32(crc_test_data[i].data,crc_test_data[i].data_len,0xffffffff,1);
        for(int j=0;j<sizeof(crc);j++)
            crc_test_data[i].data[crc_test_data[i].data_len + j] = (crc >> j*8) & 0xff;
        check = Crc_CalculateCRC32(crc_test_data[i].data,crc_test_data[i].data_len+sizeof(crc),0xffffffff,1);
        magiccheck = check ^ Crc_32_Xor;
		printf("result[%d] check[0x%x,0x%x] crc=0x%x,0x%x\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
}

void Crc_CalculateCRC32P4_test()
{
	uint32_t crc;
    uint32_t check;
    uint32_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0x6fb32240},
	{{0xf2,0x01,0x83},								3,0x4f721a25},
	{{0x0f,0xaa,0x00,0x55}, 						4,0x20662df8},
	{{0x00,0xff,0x55,0x11}, 						4,0x9bd7966e},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0xa65a343d},
	{{0x92,0x6b,0x55},								3,0xee688a78},
	{{0xff,0xff,0xff,0xff},							4,0xffffffff}
	};
	printf("Crc_CalculateCRC32P4 test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC32P4(crc_test_data[i].data,crc_test_data[i].data_len,0xffffffff,1);
        for(int j=0;j<sizeof(crc);j++)
            crc_test_data[i].data[crc_test_data[i].data_len + j] = (crc >> j*8) & 0xff;
        check = Crc_CalculateCRC32P4(crc_test_data[i].data,crc_test_data[i].data_len+sizeof(crc),0xffffffff,1);
        magiccheck = check ^ Crc_32P4_Xor;
        printf("result[%d] check[0x%x,0x%x] crc=0x%x,0x%x\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
}

void Crc_CalculateCRC64_test()
{
	uint64_t crc;
    uint64_t check;
    uint64_t magiccheck;
	CRC_DATA_S crc_test_data[7] = {
	{{0,0,0,0},										4,0xF4A586351E1B9F4B},
	{{0xf2,0x01,0x83},								3,0x319C27668164F1C6},
	{{0x0f,0xaa,0x00,0x55}, 						4,0x54C5D0F7667C1575},
	{{0x00,0xff,0x55,0x11}, 						4,0xA63822BE7E0704E6},
	{{0x33,0x22,0x55,0xaa,0xbb,0xcc,0xdd,0xee,0xff},9,0x701ECEB219A8E5D5},
	{{0x92,0x6b,0x55},								3,0x5FAA96A9B59F3E4E},
	{{0xff,0xff,0xff,0xff},							4,0xFFFFFFFF00000000}
	};
	printf("Crc_CalculateCRC64 test start:\n");
	for(int i=0;i<sizeof(crc_test_data)/sizeof(CRC_DATA_S);i++)
	{
		crc = Crc_CalculateCRC64(crc_test_data[i].data,crc_test_data[i].data_len,0xffffffffffffffff,1);
        for(int j=0;j<sizeof(crc);j++)
            crc_test_data[i].data[crc_test_data[i].data_len + j] = (crc >> j*8) & 0xff;
        check = Crc_CalculateCRC64(crc_test_data[i].data,crc_test_data[i].data_len+sizeof(crc),0xffffffffffffffff,1);
        magiccheck = check ^ CRC_64_Xor;
		printf("result[%d] check[0x%lx,0x%lx] crc=0x%lx,0x%lx\n",crc==crc_test_data[i].data_crc,check,magiccheck,crc,crc_test_data[i].data_crc);
	}
}

uint8_t reflected(uint8_t b)
{
    uint8_t c;
    for(uint32_t i=0; i<8; i++)
    {
        c <<= 1;
        if (b&1)
            c|=1;
        b >>= 1;
    }
    return c;
}

uint32_t reflected_32bit(uint32_t d)
{
    uint32_t c = 0;
    for(uint32_t i=0; i<32;i++)
    {
        c <<= 1;
        if (d&1) c|=1;
        d >>= 1;
    }
    return c;
}

uint64_t reflected_64bit(uint64_t d)
{
    uint64_t c = 0;
    for(uint64_t i=0; i<64;i++)
    {
        c <<= 1;
        if (d&1) c|=1;
        d >>= 1;
    }
    return c;
}


#define TABLE_SIZE 256


void CRC8Table_Gen()
{
    uint8_t crc8_table[TABLE_SIZE]={0};
    uint8_t data;
    uint8_t crcReg;
    printf("################genrate CRC8 table##################\n");
    for (uint32_t i = 0; i < 256; i++ )
    {
        data =  i;
        crcReg = 0;
        for (uint32_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x80 )
                crcReg = ( crcReg << 1 ) ^ Crc_8_Polynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        crc8_table[i] = crcReg;
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%02dx ",crc8_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
    printf("##################################################\n");
}

void CRC8H2FTable_Gen()
{
    uint8_t crc8_table[TABLE_SIZE]={0};
    uint8_t data;
    uint8_t crcReg;
    printf("################genrate CRC8H2F table##################\n");
    for (uint32_t i = 0; i < 256; i++ )
    {
        data =  i;
        crcReg = 0;
        for (uint32_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x80 )
                crcReg = ( crcReg << 1 ) ^ Crc_8_8H2FPolynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        crc8_table[i] = crcReg;
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%02dx ",crc8_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
    printf("##################################################\n");
}


void CRC16Table_Gen()
{
    uint16_t crc16_table[TABLE_SIZE]={0};
    uint16_t data;
    uint16_t crcReg;
    printf("###############genrate CRC16 table##################\n");
    for (uint32_t i = 0; i < 256; i++ )
    {
        data = ( uint16_t )( i << 8 );
        crcReg = 0;
        for (uint32_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x8000 )
                crcReg = ( crcReg << 1 ) ^ Crc_16_CCITTPolynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        crc16_table[i] = crcReg;
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%04dx ",crc16_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
    printf("#####################################\n");
}


void CRC32Table_Gen()
{
    uint32_t temp_table[TABLE_SIZE]={0};
    uint32_t crc32_table[TABLE_SIZE]={0};
    uint32_t data;
    uint32_t crcReg;
    printf("###############genrate CRC32 table##################\n");
    for (uint32_t i = 0; i < 256; i++ )
    {
        data = ( uint32_t )( i << 24 );
        crcReg = 0;
        for (uint32_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x80000000 )
                crcReg = ( crcReg << 1 ) ^ Crc_32_Polynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        temp_table[i] = crcReg;
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        crc32_table[i]= reflected_32bit(temp_table[reflected(i)]);
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%08dx ",crc32_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
}

void CRC32P4Table_Gen()
{
    uint32_t temp_table[TABLE_SIZE]={0};
    uint32_t crc32_table[TABLE_SIZE]={0};
    uint32_t data;
    uint32_t crcReg;
    printf("###############genrate CRC32P4 table##################\n");
    for (uint32_t i = 0; i < 256; i++ )
    {
        data = ( uint32_t )( i << 24 );
        crcReg = 0;
        for (uint32_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x80000000 )
                crcReg = ( crcReg << 1 ) ^ Crc_32P4_Polynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        temp_table[i] = crcReg;
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        crc32_table[i]= reflected_32bit(temp_table[reflected(i)]);
    }

    for(uint32_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%08dx ",crc32_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
}

void CRC64Table_Gen()
{
    uint64_t temp_table[TABLE_SIZE]={0};
    uint64_t crc64_table[TABLE_SIZE]={0};
    uint64_t data;
    uint64_t crcReg;
    printf("###############genrate CRC64 table##################\n");
    for (uint64_t i = 0; i < 256; i++ )
    {
        data = ( uint64_t )( i << 56 );
        crcReg = 0;
        for (uint64_t j = 0; j < 8; j++ )
        {
            if ( ( data ^ crcReg ) & 0x8000000000000000 )
                crcReg = ( crcReg << 1 ) ^ CRC_64_Polynomial;
            else
                crcReg <<= 1;
            data <<= 1;
        }
        temp_table[i] = crcReg;
    }

    for(uint64_t i=0;i<TABLE_SIZE;i++)
    {
        crc64_table[i]= reflected_64bit(temp_table[reflected(i)]);
    }

    for(uint64_t i=0;i<TABLE_SIZE;i++)
    {
        printf("0x%016lx ",crc64_table[i]);
        if(i%8 == 7)
            printf("\n");
    }
}


void main()
{
#if 1
	Crc_CalculateCRC8_test();
	Crc_CalculateCRC8H2F_test();
	Crc_CalculateCRC16_test();
	Crc_CalculateCRC32_test();
	Crc_CalculateCRC32P4_test();
	Crc_CalculateCRC64_test();
#else
    CRC8Table_Gen();
    CRC8H2FTable_Gen();
    CRC16Table_Gen();
    CRC32Table_Gen();
    CRC32P4Table_Gen();
    CRC64Table_Gen();
#endif
}
