#include "touch_task.h"
#include "qe_touch_config.h"
#include "inc/key.h"
/* Touch entry function */
/* pvParameters contains TaskHandle_t */
void touch_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    while (1)
    {
        //qe_touch_main();
        /* TODO: add your own code here */
        vTaskDelay (1);
    }
}
