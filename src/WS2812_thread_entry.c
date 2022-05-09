#include "WS2812_thread.h"
#include "inc/key.h"
#include "inc/ws2812.h"
#include "inc/collect_ADC.h"

uint8_t LED_R =0;
uint8_t LED_G =0;
uint8_t LED_B =0;
float LED_H =0; //色调
float LED_S =0; //饱和度
float LED_V =0; //明度

uint8_t gears=0;
/* pvParameters contains TaskHandle_t */
void WS2812_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    ws2812Init();

    while (1)
    {
        if(open_flag)
        {
            switch(model)
            {
                case 0:
                    Boot_animation();//开机
                    model = 1;
                    break;

                case 1:
                    breathing_led();//呼吸灯
                    break;

                case 2:
                    Ribbon_color();//渐变灯
                    break;

                case 3:
                    serpentine();//逐个点亮
                    break;

                case 4:
                    rhythm_led();//音乐节奏灯
                    gears=0;
                    break;

                case 5:
                    electricity_led();//电池电量
                    break;

                case 10:
                    Shutdown_animation();//关机
                    break;

                default:
                break;
            }

            if(Low_electricity) //低电压警告
            {
                Low_electricity=0;
                Low_led();
            }
        }
        vTaskDelay(1);
    }
}

void breathing_led(void) //呼吸灯
{
    clear();
    for(uint8_t led_coloy=0; led_coloy<7; led_coloy++)
    {
        LED_R = (uint8_t)(rainbow[led_coloy] >> 16),
        LED_G = (uint8_t)(rainbow[led_coloy] >> 8),
        LED_B = (uint8_t)rainbow[led_coloy];
        //获取颜色的色调
        rgb2hsv(LED_G, LED_R, LED_B, &LED_H, &LED_S, &LED_V);
        LED_V = 0;
        for(uint16_t led_wawe=0; led_wawe<400; led_wawe++)
        {
            //改变亮度
            if(led_wawe<200)
                LED_V = LED_V + 0.002;
            else
                LED_V = LED_V - 0.002;

            hsv2rgb(LED_H, LED_S, LED_V, &LED_G, &LED_R, &LED_B);
            for (uint8_t led_num=0;led_num<NUMPIXELS;led_num++)
            {
                setPixelColor(led_num, LED_G, LED_R, LED_B);
            }
            //显示
            show();
            vTaskDelay(10);

            if(model!=1)
                break;
        }
    }
}

void Ribbon_color(void) //渐变灯
{
    LED_S=1;
    LED_V=0.3;
    for(LED_H=0; LED_H<400; LED_H=LED_H+0.1)
    {
        hsv2rgb(LED_H, LED_S, LED_V, &LED_G, &LED_R, &LED_B);
        for (uint8_t led_num=0;led_num<NUMPIXELS;led_num++)
        {
            setPixelColor(led_num, LED_G, LED_R, LED_B);
        }
        show();
        vTaskDelay(10);
        if(model!=2)
            break;
    }
}

void serpentine(void) //逐个点亮
{
    clear();
    for(uint8_t led_coloy=0; led_coloy<7; led_coloy++)
   {
       LED_R = (uint8_t)(rainbow[led_coloy] >> 16),
       LED_G = (uint8_t)(rainbow[led_coloy] >> 8),
       LED_B = (uint8_t)rainbow[led_coloy];
       clear();
       for(uint8_t led_num=0; led_num<8; led_num++)
       {
           setPixelColor(led_num, LED_G, LED_R, LED_B);
           setPixelColor(led_num+8, LED_G, LED_R, LED_B);
           setPixelColor(led_num+16, LED_G, LED_R, LED_B);
           setPixelColor(led_num+24, LED_G, LED_R, LED_B);
           setPixelColor(led_num+32, LED_G, LED_R, LED_B);
           show();
           vTaskDelay(100);

           if(model!=3)
               break;
       }
   }
}

void rhythm_led(void) //音乐节奏灯
{
    clear();
    if(differ>=400)
    {
        setPixelColor(39, 0, 125, 0);
        setPixelColor(38, 0, 125, 0);
        setPixelColor(37, 0, 125, 0);
        setPixelColor(36, 0, 125, 0);
        setPixelColor(35, 0, 125, 0);
        setPixelColor(34, 0, 125, 0);
        setPixelColor(33, 0, 125, 0);
        setPixelColor(32, 0, 125, 0);
    }
    if(differ>=300)
    {
        setPixelColor(5, 82, 125, 0);
        setPixelColor(6, 82, 125, 0);
        setPixelColor(7, 82, 125, 0);
        setPixelColor(13, 82, 125, 0);
        setPixelColor(14, 82, 125, 0);
        setPixelColor(15, 82, 125, 0);
        setPixelColor(21, 82, 125, 0);
        setPixelColor(22, 82, 125, 0);
        setPixelColor(23, 82, 125, 0);
        setPixelColor(29, 82, 125, 0);
        setPixelColor(30, 82, 125, 0);
        setPixelColor(31, 82, 125, 0);
    }
    if(differ>=200)
    {
        setPixelColor(3, 125, 125, 0);
        setPixelColor(4, 125, 125, 0);
        setPixelColor(11, 125, 125, 0);
        setPixelColor(12, 125, 125, 0);
        setPixelColor(19, 125, 125, 0);
        setPixelColor(20, 125, 125, 0);
        setPixelColor(27, 125, 125, 0);
        setPixelColor(28, 125, 125, 0);
    }
    if(differ>=100)
    {
        setPixelColor(0, 125, 0, 0);
        setPixelColor(1, 125, 0, 0);
        setPixelColor(2, 125, 0, 0);
        setPixelColor(8, 125, 0, 0);
        setPixelColor(9, 125, 0, 0);
        setPixelColor(10, 125, 0, 0);
        setPixelColor(16, 125, 0, 0);
        setPixelColor(17, 125, 0, 0);
        setPixelColor(18, 125, 0, 0);
        setPixelColor(24, 125, 0, 0);
        setPixelColor(25, 125, 0, 0);
        setPixelColor(26, 125, 0, 0);
    }
    show();
    vTaskDelay(50);
}

void electricity_led(void) //电池电量
{
    if(gears==0)
        clear();
    if(battery_voltage<=3.6) //25%
    {
        for(uint8_t led_num=0; led_num<3; led_num++)
        {
            setPixelColor(led_num, 0, 125, 0);
            setPixelColor(led_num+8, 0, 125, 0);
            setPixelColor(led_num+16, 0, 125, 0);
            setPixelColor(led_num+24, 0, 125, 0);
        }
    }
    else if(battery_voltage<=3.8 && battery_voltage>3.6) //50%
    {
        for(uint8_t led_num=0; led_num<5; led_num++)
        {
            setPixelColor(led_num, 80, 80, 0);
            setPixelColor(led_num+8, 80, 80, 0);
            setPixelColor(led_num+16, 80, 80, 0);
            setPixelColor(led_num+24, 80, 80, 0);
        }
    }
    else if(battery_voltage<=4 && battery_voltage>3.8) //75%
    {
        for(uint8_t led_num=0; led_num<8; led_num++)
        {
            setPixelColor(led_num, 80, 40, 0);
            setPixelColor(led_num+8, 80, 40, 0);
            setPixelColor(led_num+16, 80, 40, 0);
            setPixelColor(led_num+24, 80, 40, 0);
        }
    }
    else if(battery_voltage<=4.2 && battery_voltage>4) //100%
    {
        for(uint8_t led_num=0; led_num<40; led_num++)
        {
            setPixelColor(led_num, 100, 0, 0);
        }
    }
    else if(battery_voltage>4.5) //充电中
    {
        if(gears==0)
            gears++;
        else if(gears==1)
        {
            for(uint8_t led_num=0; led_num<3; led_num++)
            {
                setPixelColor(led_num, 0, 125, 0);
                setPixelColor(led_num+8, 0, 125, 0);
                setPixelColor(led_num+16, 0, 125, 0);
                setPixelColor(led_num+24, 0, 125, 0);
            }
            gears++;
        }
        else if(gears==2)
        {
            for(uint8_t led_num=3; led_num<5; led_num++)
            {
                setPixelColor(led_num, 80, 80, 0);
                setPixelColor(led_num+8, 80, 80, 0);
                setPixelColor(led_num+16, 80, 80, 0);
            }
            gears++;
        }
        else if(gears==3)
        {
            for(uint8_t led_num=5; led_num<8; led_num++)
            {
                setPixelColor(led_num, 80, 40, 0);
                setPixelColor(led_num+8, 80, 40, 0);
                setPixelColor(led_num+16, 80, 40, 0);
                setPixelColor(led_num+24, 80, 40, 0);
            }
            gears++;
        }
        else if(gears==4)
        {
            for(uint8_t led_num=32; led_num<40; led_num++)
            {
                setPixelColor(led_num, 100, 0, 0);
            }
            gears=0;
        }
    }
    show();
    vTaskDelay(500);
}

void Low_led(void) //低电警告
{
    for(uint8_t led_i=0; led_i<3; led_i++)
    {
        for(uint8_t led_num=0; led_num<40; led_num++)
        {
            setPixelColor(led_num, 0, 125, 0);
            setPixelColor(led_num+8, 0, 125, 0);
            setPixelColor(led_num+16, 0, 125, 0);
            setPixelColor(led_num+24, 0, 125, 0);
        }
        show();
        vTaskDelay(500);
        clear();
        show();
        vTaskDelay(500);
    }
}

void Boot_animation(void) //开机动画
{
    clear();
    setPixelColor(0, 0, 90, 125);
    setPixelColor(2, 0, 90, 125);
    setPixelColor(8, 0, 90, 125);
    setPixelColor(10, 0, 90, 125);
    setPixelColor(16, 0, 90, 125);
    setPixelColor(18, 0, 90, 125);
    setPixelColor(24, 0, 90, 125);
    setPixelColor(26, 0, 90, 125);
    show();
    vTaskDelay(300);
    setPixelColor(3, 0, 90, 125);
    setPixelColor(4, 0, 90, 125);
    setPixelColor(11, 0, 90, 125);
    setPixelColor(12, 0, 90, 125);
    setPixelColor(19, 0, 90, 125);
    setPixelColor(20, 0, 90, 125);
    setPixelColor(27, 0, 90, 125);
    setPixelColor(28, 0, 90, 125);
    show();
    vTaskDelay(300);
    setPixelColor(5, 0, 90, 125);
    setPixelColor(7, 0, 90, 125);
    setPixelColor(13, 0, 90, 125);
    setPixelColor(15, 0, 90, 125);
    setPixelColor(21, 0, 90, 125);
    setPixelColor(23, 0, 90, 125);
    setPixelColor(29, 0, 90, 125);
    setPixelColor(31, 0, 90, 125);
    show();
    vTaskDelay(300);
    setPixelColor(32, 0, 90, 125);
    setPixelColor(34, 0, 90, 125);
    setPixelColor(37, 0, 90, 125);
    setPixelColor(39, 0, 90, 125);
    show();
    vTaskDelay(300);
}

void Shutdown_animation(void) //关机动画
{
    clear();
    setPixelColor(39, 125, 60, 30);
    setPixelColor(37, 125, 60, 30);
    setPixelColor(34, 125, 60, 30);
    setPixelColor(32, 125, 60, 30);
    show();
    vTaskDelay(300);
    setPixelColor(31, 125, 60, 30);
    setPixelColor(29, 125, 60, 30);
    setPixelColor(23, 125, 60, 30);
    setPixelColor(21, 125, 60, 30);
    setPixelColor(15, 125, 60, 30);
    setPixelColor(13, 125, 60, 30);
    setPixelColor(7, 125, 60, 30);
    setPixelColor(5, 125, 60, 30);
    show();
    vTaskDelay(300);
    setPixelColor(28, 125, 60, 30);
    setPixelColor(27, 125, 60, 30);
    setPixelColor(20, 125, 60, 30);
    setPixelColor(19, 125, 60, 30);
    setPixelColor(12, 125, 60, 30);
    setPixelColor(11, 125, 60, 30);
    setPixelColor(4, 125, 60, 30);
    setPixelColor(3, 125, 60, 30);
    show();
    vTaskDelay(300);
    setPixelColor(26, 125, 60, 30);
    setPixelColor(24, 125, 60, 30);
    setPixelColor(18, 125, 60, 30);
    setPixelColor(16, 125, 60, 30);
    setPixelColor(10, 125, 60, 30);
    setPixelColor(8, 125, 60, 30);
    setPixelColor(2, 125, 60, 30);
    setPixelColor(0, 125, 60, 30);
    show();
    vTaskDelay(300);
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_LOW);
}
