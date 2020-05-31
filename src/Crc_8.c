#include "Crc.h"


#ifndef Crc_8_Mode
#define Crc_8_Mode 0
#endif


#ifndef Crc_8_8H2FMode
#define Crc_8_8H2FMode 0
#endif



/* For CRC 8 SAE-1850, compare https://en.wikipedia.org/wiki/Cyclic_redundancy_check */
#if Crc_8_Mode == CRC_8_RUNTIME
#define Crc_8_Polynomial        0x1D
#endif


/* For CRC 8H2F, https://en.wikipedia.org/wiki/Cyclic_redundancy_check */
#if Crc_8_8H2FMode == CRC_8H2F_RUNTIME
#define Crc_8_8H2FPolynomial    0x2F
#endif


/* For CRC 8*/
#if (Crc_8_Mode == CRC_8_RUNTIME) || (Crc_8_Mode == CRC_8_TABLE)
#define Crc_8_StartValue        0xFFU
#define Crc_8_Xor               0xFFU
#endif


/* For CRC 8H2F */
#if (Crc_8_8H2FMode == CRC_8H2F_RUNTIME) || (Crc_8_8H2FMode == CRC_8H2F_TABLE)
#define Crc_8_8H2FStartValue    0xFFU
#define Crc_8_8H2FXor           0xFFU
#endif


#if (Crc_8_Mode == CRC_8_RUNTIME) || (Crc_8_8H2FMode == CRC_8H2F_RUNTIME)
/** @brief Calculation of 8-bit CRC, used to compare result with the table lookup in the actual implementation
 *         in the CRC module.
 *
 *  @param message Pointer to start address of data block to be calculated.
 *  @param nBytes Length of data block to be calculated in bytes.
 *  @param start Start value when the algorithm starts.
 *  @param poly Polynomial used for CRC calculation.
 *
 *  @return 8 bit result of CRC calculation.
 */
static uint8_t calculateCRC8(const uint8_t* message, uint32_t nBytes, uint8_t start, uint8_t poly)
{
    uint8_t  remainder = start;
    uint8_t  bit;
    const uint8_t topbit = 0x80;

	/* NULL pointer checking */
    if (message != NULL) {
        /* Perform modulo-2 division, a byte at a time. */
        for (uint32_t byte = 0; byte < nBytes; byte++) {
            /* Bring the next byte into the remainder. */
            remainder ^= *message;
            message++;

            /* Perform modulo-2 division, a bit at a time. */
            for (bit = 8; bit > 0; bit--) {

                /* Try to divide the current data bit. */
                if ((remainder & topbit) != 0u) {
                    remainder = (uint8_t)(remainder << 1u) ^ poly;
                }
                else {
                    remainder = (uint8_t)(remainder << 1u);
                }
            }
        }
    }

    return remainder;
}

#endif


/** @brief This service makes a CRC8 calculation on Crc_Length data bytes,
 *         using the polynomial 0x1D.
 *
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue8 Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 8 bit result of CRC calculation.
 */
#if (Crc_8_Mode == CRC_8_RUNTIME) || (Crc_8_Mode == CRC_8_TABLE)
uint8_t Crc_CalculateCRC8(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint8_t Crc_StartValue8, bool Crc_IsFirstCall) {

    uint8_t crc = 0;    /* Default return value if NULL pointer */
#if Crc_8_Mode == CRC_8_TABLE
    static const uint8_t Crc_8_Tab[256] = {0x0, 0x1d, 0x3a, 0x27, 0x74, 0x69, 0x4e, 0x53,
                                     0xe8, 0xf5, 0xd2, 0xcf, 0x9c, 0x81, 0xa6, 0xbb,
                                     0xcd, 0xd0, 0xf7, 0xea, 0xb9, 0xa4, 0x83, 0x9e,
                                     0x25, 0x38, 0x1f, 0x2, 0x51, 0x4c, 0x6b, 0x76,
                                     0x87, 0x9a, 0xbd, 0xa0, 0xf3, 0xee, 0xc9, 0xd4,
                                     0x6f, 0x72, 0x55, 0x48, 0x1b, 0x6, 0x21, 0x3c,
                                     0x4a, 0x57, 0x70, 0x6d, 0x3e, 0x23, 0x4, 0x19,
                                     0xa2, 0xbf, 0x98, 0x85, 0xd6, 0xcb, 0xec, 0xf1,
                                     0x13, 0xe, 0x29, 0x34, 0x67, 0x7a, 0x5d, 0x40,
                                     0xfb, 0xe6, 0xc1, 0xdc, 0x8f, 0x92, 0xb5, 0xa8,
                                     0xde, 0xc3, 0xe4, 0xf9, 0xaa, 0xb7, 0x90, 0x8d,
                                     0x36, 0x2b, 0xc, 0x11, 0x42, 0x5f, 0x78, 0x65,
                                     0x94, 0x89, 0xae, 0xb3, 0xe0, 0xfd, 0xda, 0xc7,
                                     0x7c, 0x61, 0x46, 0x5b, 0x8, 0x15, 0x32, 0x2f,
                                     0x59, 0x44, 0x63, 0x7e, 0x2d, 0x30, 0x17, 0xa,
                                     0xb1, 0xac, 0x8b, 0x96, 0xc5, 0xd8, 0xff, 0xe2,
                                     0x26, 0x3b, 0x1c, 0x1, 0x52, 0x4f, 0x68, 0x75,
                                     0xce, 0xd3, 0xf4, 0xe9, 0xba, 0xa7, 0x80, 0x9d,
                                     0xeb, 0xf6, 0xd1, 0xcc, 0x9f, 0x82, 0xa5, 0xb8,
                                     0x3, 0x1e, 0x39, 0x24, 0x77, 0x6a, 0x4d, 0x50,
                                     0xa1, 0xbc, 0x9b, 0x86, 0xd5, 0xc8, 0xef, 0xf2,
                                     0x49, 0x54, 0x73, 0x6e, 0x3d, 0x20, 0x7, 0x1a,
                                     0x6c, 0x71, 0x56, 0x4b, 0x18, 0x5, 0x22, 0x3f,
                                     0x84, 0x99, 0xbe, 0xa3, 0xf0, 0xed, 0xca, 0xd7,
                                     0x35, 0x28, 0xf, 0x12, 0x41, 0x5c, 0x7b, 0x66,
                                     0xdd, 0xc0, 0xe7, 0xfa, 0xa9, 0xb4, 0x93, 0x8e,
                                     0xf8, 0xe5, 0xc2, 0xdf, 0x8c, 0x91, 0xb6, 0xab,
                                     0x10, 0xd, 0x2a, 0x37, 0x64, 0x79, 0x5e, 0x43,
                                     0xb2, 0xaf, 0x88, 0x95, 0xc6, 0xdb, 0xfc, 0xe1,
                                     0x5a, 0x47, 0x60, 0x7d, 0x2e, 0x33, 0x14, 0x9,
                                     0x7f, 0x62, 0x45, 0x58, 0xb, 0x16, 0x31, 0x2c,
                                     0x97, 0x8a, 0xad, 0xb0, 0xe3, 0xfe, 0xd9, 0xc4};
#endif


	/* NULL pointer checking */
    if (Crc_DataPtr != NULL) {

        crc = (true == Crc_IsFirstCall) ? Crc_8_StartValue : (Crc_StartValue8 ^ Crc_8_Xor);

#if Crc_8_Mode == CRC_8_RUNTIME
        crc = calculateCRC8(Crc_DataPtr, Crc_Length, crc, Crc_8_Polynomial);
#elif Crc_8_Mode == CRC_8_TABLE
        for (uint32_t byte = 0; byte < Crc_Length; byte++) {
            crc = Crc_8_Tab[crc ^ *Crc_DataPtr];
            Crc_DataPtr++;
        }
#endif

        /* Only XOR value if any calculation was done */
        crc = crc ^ Crc_8_Xor;
    }

    return crc;
}

#endif


#if (Crc_8_8H2FMode == CRC_8H2F_RUNTIME) || (Crc_8_8H2FMode == CRC_8H2F_TABLE)
/** @brief This service makes a CRC8 calculation on Crc_Length data bytes,
 *         using the polynomial 0x2F.
 *
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue8H2F Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 8 bit result of CRC calculation.
 */
uint8_t Crc_CalculateCRC8H2F(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint8_t Crc_StartValue8H2F, bool Crc_IsFirstCall) {

    uint8_t crc = 0;
#if Crc_8_8H2FMode == CRC_8H2F_TABLE
    static const uint8_t Crc_8_8H2FTab[256] = {0x0, 0x2f, 0x5e, 0x71, 0xbc, 0x93, 0xe2, 0xcd,
                                         0x57, 0x78, 0x9, 0x26, 0xeb, 0xc4, 0xb5, 0x9a,
                                         0xae, 0x81, 0xf0, 0xdf, 0x12, 0x3d, 0x4c, 0x63,
                                         0xf9, 0xd6, 0xa7, 0x88, 0x45, 0x6a, 0x1b, 0x34,
                                         0x73, 0x5c, 0x2d, 0x2, 0xcf, 0xe0, 0x91, 0xbe,
                                         0x24, 0xb, 0x7a, 0x55, 0x98, 0xb7, 0xc6, 0xe9,
                                         0xdd, 0xf2, 0x83, 0xac, 0x61, 0x4e, 0x3f, 0x10,
                                         0x8a, 0xa5, 0xd4, 0xfb, 0x36, 0x19, 0x68, 0x47,
                                         0xe6, 0xc9, 0xb8, 0x97, 0x5a, 0x75, 0x4, 0x2b,
                                         0xb1, 0x9e, 0xef, 0xc0, 0xd, 0x22, 0x53, 0x7c,
                                         0x48, 0x67, 0x16, 0x39, 0xf4, 0xdb, 0xaa, 0x85,
                                         0x1f, 0x30, 0x41, 0x6e, 0xa3, 0x8c, 0xfd, 0xd2,
                                         0x95, 0xba, 0xcb, 0xe4, 0x29, 0x6, 0x77, 0x58,
                                         0xc2, 0xed, 0x9c, 0xb3, 0x7e, 0x51, 0x20, 0xf,
                                         0x3b, 0x14, 0x65, 0x4a, 0x87, 0xa8, 0xd9, 0xf6,
                                         0x6c, 0x43, 0x32, 0x1d, 0xd0, 0xff, 0x8e, 0xa1,
                                         0xe3, 0xcc, 0xbd, 0x92, 0x5f, 0x70, 0x1, 0x2e,
                                         0xb4, 0x9b, 0xea, 0xc5, 0x8, 0x27, 0x56, 0x79,
                                         0x4d, 0x62, 0x13, 0x3c, 0xf1, 0xde, 0xaf, 0x80,
                                         0x1a, 0x35, 0x44, 0x6b, 0xa6, 0x89, 0xf8, 0xd7,
                                         0x90, 0xbf, 0xce, 0xe1, 0x2c, 0x3, 0x72, 0x5d,
                                         0xc7, 0xe8, 0x99, 0xb6, 0x7b, 0x54, 0x25, 0xa,
                                         0x3e, 0x11, 0x60, 0x4f, 0x82, 0xad, 0xdc, 0xf3,
                                         0x69, 0x46, 0x37, 0x18, 0xd5, 0xfa, 0x8b, 0xa4,
                                         0x5, 0x2a, 0x5b, 0x74, 0xb9, 0x96, 0xe7, 0xc8,
                                         0x52, 0x7d, 0xc, 0x23, 0xee, 0xc1, 0xb0, 0x9f,
                                         0xab, 0x84, 0xf5, 0xda, 0x17, 0x38, 0x49, 0x66,
                                         0xfc, 0xd3, 0xa2, 0x8d, 0x40, 0x6f, 0x1e, 0x31,
                                         0x76, 0x59, 0x28, 0x7, 0xca, 0xe5, 0x94, 0xbb,
                                         0x21, 0xe, 0x7f, 0x50, 0x9d, 0xb2, 0xc3, 0xec,
                                         0xd8, 0xf7, 0x86, 0xa9, 0x64, 0x4b, 0x3a, 0x15,
                                         0x8f, 0xa0, 0xd1, 0xfe, 0x33, 0x1c, 0x6d, 0x42};
#endif
	/* NULL pointer checking */
    if (Crc_DataPtr != NULL) {
        crc = (true == Crc_IsFirstCall) ? Crc_8_8H2FStartValue : (Crc_StartValue8H2F ^ Crc_8_8H2FXor);

#if Crc_8_8H2FMode == CRC_8H2F_RUNTIME
        crc = calculateCRC8(Crc_DataPtr, Crc_Length, crc, Crc_8_8H2FPolynomial);
#elif Crc_8_8H2FMode == CRC_8H2F_TABLE
        for (uint32_t byte = 0; byte < Crc_Length; byte++) {
            crc = Crc_8_8H2FTab[crc ^ *Crc_DataPtr];
            Crc_DataPtr++;
        }
#endif

        crc = crc ^ Crc_8_8H2FXor;
    }

    return crc;
}

#endif
