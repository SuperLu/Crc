#ifndef CRC_H_
#define CRC_H_

#include "Crc_Cfg.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef Crc_8_Mode
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
/* API for 8-bit SAE J1850 CRC Calculation */
uint8_t  Crc_CalculateCRC8(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint8_t Crc_StartValue8, bool Crc_IsFirstCall);
#endif


#ifdef Crc_8_8H2FMode
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
/* API for 8-bit 0x2F polynomial CRC Calculation */
uint8_t  Crc_CalculateCRC8H2F(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint8_t Crc_StartValue8H2F, bool Crc_IsFirstCall);
#endif


#ifdef Crc_16_Mode
/** @brief This service makes a CRC16 calculation on Crc_Length data bytes,
 *         using the polynomial 0x1021.
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue16 Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 16 bit result of CRC calculation.
 */
/* API for 16-bit CCITT-FALSE CRC16 */
uint16_t Crc_CalculateCRC16(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint16_t Crc_StartValue16, bool Crc_IsFirstCall);
#endif


#ifdef Crc_32_Mode
/** @brief This service makes a CRC32 calculation on Crc_Length data bytes,
 *         using the polynomial 0x04C11DB7.
 *
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue32 Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 32 bit result of CRC calculation.
 */
/* API for 32-bit Ethernet CRC Calculation */
uint32_t Crc_CalculateCRC32(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint32_t Crc_StartValue32, bool Crc_IsFirstCall);
#endif


#ifdef Crc_32P4_Mode
/** @brief This service makes a CRC32 calculation on Crc_Length data bytes,
 *         using the polynomial 0xF4ACFB13. This CRC routine is used by E2E Profile 4.
 *
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue32P4 Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 32 bit result of CRC calculation.
 */
/* API for 32-bit 0xF4ACFB13 polynomial CRC calculation */
uint32_t Crc_CalculateCRC32P4(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint32_t Crc_StartValue32P4, bool Crc_IsFirstCall);
#endif


#ifdef Crc_64_Mode
/** @brief This service makes a CRC32 calculation on Crc_Length data bytes,
 *         using the polynomial 0xF4ACFB13. This CRC routine is used by E2E Profile 4.
 *
 *  @param Crc_DataPtr Pointer to start address of data block to be calculated.
 *  @param Crc_Length Length of data block to be calculated in bytes.
 *  @param Crc_StartValue32P4 Start value when the algorithm starts.
 *  @param Crc_IsFirstCall TRUE: First call in a sequence or individual CRC calculation;
 *                         FALSE: Subsequent call in a call sequence.
 *  @return 64 bit result of CRC calculation.
 */
/* API for 64-bit 0xF4ACFB13 polynomial CRC calculation */
uint64_t Crc_CalculateCRC64(const uint8_t* Crc_DataPtr, uint32_t Crc_Length, uint64_t Crc_StartValue64, bool Crc_IsFirstCall);
#endif


#endif /* CRC_H_ */
