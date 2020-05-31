# Crc
Algorithm of CRC



 https://en.wikipedia.org/wiki/Cyclic_redundancy_check

| name    |                              | Polynomial        | Initial value     | XOR value         |
| ------- | ---------------------------- | ----------------- | ----------------- | ----------------- |
| CRC8    | SAE-1850                     | 1Dh               | FFh               | FFh               |
| CRC8H2F | AUTOSAR                      | 2Fh               | FFh               | FFh               |
| CRC16   | CCITT                        | 1021h             | FFFFh             | 0000h             |
| CRC32   | IEEE-802.3 (Ethernet)        | 04C11DB7h         | FFFFFFFFh         | FFFFFFFFh         |
| CRC32   | CRC32 0x1F4ACFB13 polynomial | F4ACFB13h         | FFFFFFFFh         | FFFFFFFFh         |
| CRC64   | ECMA                         | 42F0E1EBA9EA3693h | FFFFFFFFFFFFFFFFh | FFFFFFFFFFFFFFFFh |

