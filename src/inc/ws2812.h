

#ifndef WS2812_H_
#define WS2812_H_
#include "hal_data.h"

#define NUMPIXELS   (40)
#define NUMRES      (60)
#define SPIBUFL     ((NUMPIXELS) * 3 * 8 + NUMRES)

static const uint32_t rainbow[] = {0x7d0000,0x7d5200,0x7d7d00,0x007d00,0x003f7d,0x00007d,0x45007d};// 7色彩虹 50%亮度

void show(void);
void clear(void);
void setPixelColor(uint16_t n, uint8_t g, uint8_t r, uint8_t b);
float min(float a, float b, float c);
float max(float a, float b, float c);
void rgb2hsv(uint8_t g, uint8_t r, uint8_t b, float *h, float *s, float *v);
void hsv2rgb(float h, float s, float v, uint8_t *g, uint8_t *r, uint8_t *b);

#endif /* WS2812_H_ */
