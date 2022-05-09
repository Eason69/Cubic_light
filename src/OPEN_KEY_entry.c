#include "OPEN_KEY.h"
#include "inc/KEY.h"

bool open_flag = 0;
int16_t open_time=0;
uint8_t model = 0; //0开机 1呼吸灯  10关机
bsp_io_level_t p_port_value_port_000;


void OPEN_KEY_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    R_WDT_Open(&g_wdt0_ctrl, &g_wdt0_cfg); //看门狗

    while (1)
    {
        if(!open_flag) //开机通电2S，启动
        {
            open_time++;
            if(open_time>=2000)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_HIGH);
                open_flag = 1;
            }
        }
        else
        {
            SmartConfigKey();
            key_deal();
        }

        vTaskDelay (1);
        R_WDT_Refresh(&g_wdt0_ctrl); //喂狗
    }
}

void key_deal(void)
{
    key_scanning();

    if(Key1_IN[3] == 1)
    {
        if(Key1_IN[5]>=2000)//按下时间大于2S
        {
            Key1_IN[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
            model = 10;
            //执行的代码
        }
    }

    if(Key1_IN[4] == 1 && model != 10)
    {
        Key1_IN[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
        model++;
        if(model>5)
            model=1;
        //执行的代码
    }
}


void key_scanning(void)
{
    if(Key1_IN[1])
       Key1_IN[5]++;
   else
       Key1_IN[5]=0;

   if(Key1_IN[2])
       Key1_IN[6]++;
   else
       Key1_IN[6]=0;
}
