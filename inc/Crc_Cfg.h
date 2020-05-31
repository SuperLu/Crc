#ifndef CRC_CFG_H_
#define CRC_CFG_H_

#define CRC_8_HARDWARE (0x01) /* Not supported */
#define CRC_8_RUNTIME  (0x02)
#define CRC_8_TABLE    (0x04) /* Default value */


#define Crc_8_Mode			CRC_8_RUNTIME


/* CRC 8H2F Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_8H2F_HARDWARE (0x01) /* Not supported */
#define CRC_8H2F_RUNTIME  (0x02)
#define CRC_8H2F_TABLE    (0x04) /* Default value */


#define Crc_8_8H2FMode		CRC_8H2F_RUNTIME


/* CRC 16 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_16_HARDWARE (0x01) /* Not supported */
#define CRC_16_RUNTIME  (0x02)
#define CRC_16_TABLE    (0x04) /* Default value */


#define Crc_16_Mode			CRC_16_RUNTIME


/* CRC 32 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_32_HARDWARE (0x01)  /* Not supported */
#define CRC_32_RUNTIME  (0x02)
#define CRC_32_TABLE    (0x04)  /* Default value */


#define Crc_32_Mode      CRC_32_RUNTIME


/* CRC 32P4 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_32P4_HARDWARE (0x01)  /* Not supported */
#define CRC_32P4_RUNTIME  (0x02)
#define CRC_32P4_TABLE    (0x04)  /* Default value */


#define Crc_32P4_Mode      CRC_32P4_RUNTIME

/* CRC 64 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_64_HARDWARE (0x01)  /* Not supported */
#define CRC_64_RUNTIME  (0x02)
#define CRC_64_TABLE    (0x04)  /* Default value */


#define Crc_64_Mode      CRC_64_RUNTIME


#endif /* CRC_CFG_H_ */

