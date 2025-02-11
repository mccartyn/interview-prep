#ifndef BITWISE_H
#define BITWISE_H

// Macros
#define UINT16_MASK_L_BYTE(WORD) (WORD & 0xFF00)
#define UINT16_FLIP_LH_BYTE(WORD) ((WORD >> 8)) | ((WORD << 8));

#endif // BITWISE_H
