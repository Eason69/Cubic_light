/**
  ******************************************************************************
  * @file    key.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   按键检测模板
  ******************************************************************************
  一,使用说明:检测引脚(PB5)
		1,把以下程序放在1ms定时器中断中
			if(Key1_IN[1])
				Key1_IN[5]++;
			else
				Key1_IN[5]=0;

			if(Key1_IN[2])
				Key1_IN[6]++;
			else
				Key1_IN[6]=0;

		2,主循环调用使用
			while(1)
			{
				SmartConfigKey();

				//例1:检测到按键按下执行某段代码
				if(Key1_IN[3] == 1)
				{
					Key1_IN[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
					//执行的代码
				}

				//例2:检测到按键按下,然后根据按下时间执行某段代码
				if(Key1_IN[3] == 1)
				{
					if(Key1_IN[5]>=3000)//按下时间大于3S
					{
						Key1_IN[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
						//执行的代码
					}
				}

				//例3:检测到按键松开执行某段代码
				if(Key1_IN[4] == 1)
				{
					Key1_IN[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
					//执行的代码
				}

				//例4:检测到按键松开,然后根据松开时间执行某段代码
				if(Key1_IN[4] == 1)
				{
					if(Key1_IN[6]>=3000)//松开时间大于3S
					{
						Key1_IN[4] = 0;//清零以后,只有按键按下再松开的时候才会进入
						//执行的代码
					}
				}
			}
  ******************************************************************************
  */
#include "key.h"

int16_t Key1_IN[7] = {0,0,0,0,0,0,0};
bsp_io_level_t p_port_value_port_000;

/**
* @brief  按键处理
* @param
* @param  None
* @param  None
* @retval None
* @example
**/
void SmartConfigKey(void)
{
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, &p_port_value_port_000);

	//key1
  if(p_port_value_port_000 == BSP_IO_LEVEL_LOW)
	{
		if(Key1_IN[1] == 0)
		{
			Key1_IN[0]++;
			if(Key1_IN[0]>=80)//按下以后进入
			{
				Key1_IN[0] = 0;//Cnt
				Key1_IN[2] = 0;//UP
				Key1_IN[1] = 1;//Down
				Key1_IN[3] = 1;//DownCopy
				Key1_IN[4] = 0;//UpCopy
			}
		}
	}
	else
	{
		Key1_IN[0]++;
		if(Key1_IN[0]>10)
		{
			Key1_IN[0]=0;
			if(Key1_IN[1]==1)//按下后松开后进入
			{
				Key1_IN[2] = 1;//UP
				Key1_IN[1] = 0;//Down
				Key1_IN[3] = 0;//DownCopy
				Key1_IN[4] = 1;//UpCopy
			}
		}
	}

}

