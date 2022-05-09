
#include "ws2812.h"

static uint8_t spidate[SPIBUFL] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8,  \

                                    0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8, 0xf8,  \
                                    0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xf8, 0xf8, 0xf8
                                };

void ws2812Init(void)
{
    R_SCI_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
}

void show(void)
{
    R_SCI_SPI_Write(&g_spi0_ctrl, spidate, SPIBUFL, SPI_BIT_WIDTH_8_BITS);
}

void clear(void)
{
    memset(& spidate[NUMRES], 0xc0, (NUMPIXELS) * 3 * 8);
}

void setPixelColor(uint16_t n, uint8_t g, uint8_t r, uint8_t b)
{
    if (n < NUMPIXELS) {
      uint8_t *p;
      p = &spidate[NUMRES + n * 24];
      for(uint8_t i = 0; i < 8; i++)
      {
          *(p + i) = (0 == (g & (1 << (7 - i)))) ? 0xc0 : 0xf8;
      }
      for(uint8_t i = 0; i < 8; i++)
      {
          *(p + i + 8) = (0 == (r & (1 << (7 - i)))) ? 0xc0 : 0xf8;
      }
      for(uint8_t i = 0; i < 8; i++)
      {
          *(p + i + 16) = (0 == (b & (1 << (7 - i)))) ? 0xc0 : 0xf8;
      }
    }
}


float min(float a, float b, float c)
{
  float m;
  m = a < b ? a : b;
  return (m < c ? m : c);
}

float max(float a, float b, float c)
{
  float m;
  m = a > b ? a : b;
  return (m > c ? m : c);
}

void rgb2hsv(uint8_t g, uint8_t r, uint8_t b, float *h, float *s, float *v)
{
  float red, green ,blue;
  float cmax, cmin, delta;

  red =   (float)r / 255;
  green = (float)g / 255;
  blue =  (float)b / 255;

  cmax = max(red, green, blue);
  cmin = min(red, green, blue);
  delta = cmax - cmin;

  /* H */
  if(delta == 0)
  {
    *h = 0;
  }
  else
  {
    if(cmax == red)
    {
      if(green >= blue)
      {
        *h = 60 * ((green - blue) / delta);
      }
      else
      {
        *h = 60 * ((green - blue) / delta) + 360;
      }
    }
    else if(cmax == green)
    {
      *h = 60 * ((blue - red) / delta + 2);
    }
    else if(cmax == blue)
    {
      *h = 60 * ((red - green) / delta + 4);
    }
  }

  /* S */
  if(cmax == 0)
  {
    *s = 0;
  }
  else
  {
    *s = delta / cmax;
  }

  /* V */
  *v = cmax;
}

void hsv2rgb(float h, float s, float v, uint8_t *g, uint8_t *r, uint8_t *b)
{
  if(s == 0)
  {
    *r=*g=*b=v;
  }
  else
  {
    float H = h / 60;
    int hi = (int)H;
    float f = H - hi;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1- (1 - f) * s);
    switch (hi){
      case 0:
        *r = (int)(v * 255.0 + 0.5);
        *g = (int)(t * 255.0 + 0.5);
        *b = (int)(p * 255.0 + 0.5);
        break;
      case 1:
        *r = (int)(q * 255.0 + 0.5);
        *g = (int)(v * 255.0 + 0.5);
        *b = (int)(p * 255.0 + 0.5);
        break;
      case 2:
        *r = (int)(p * 255.0 + 0.5);
        *g = (int)(v * 255.0 + 0.5);
        *b = (int)(t * 255.0 + 0.5);
        break;
      case 3:
        *r = (int)(p * 255.0 + 0.5);
        *g = (int)(q * 255.0 + 0.5);
        *b = (int)(v * 255.0 + 0.5);
        break;
      case 4:
        *r = (int)(t * 255.0 + 0.5);
        *g = (int)(p * 255.0 + 0.5);
        *b = (int)(v * 255.0 + 0.5);
        break;
      case 5:
        *r = (int)(v * 255.0 + 0.5);
        *g = (int)(p * 255.0 + 0.5);
        *b = (int)(q * 255.0 + 0.5);
        break;
            default:
                break;
    }
  }
}




void sci_spi_callback(spi_callback_args_t *p_args)
{

}


