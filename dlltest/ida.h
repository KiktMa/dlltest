#define _BYTE  uint8_t
#define _WORD  uint16_t

#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define HIWORD(x)   (*((_WORD*)&(x)+1))

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define BYTE2(x)   BYTEn(x,  2)