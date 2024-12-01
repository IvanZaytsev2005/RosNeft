#include "app.h"

void app()
{
    while(1){
        HAL_GPIO_TogglePin(Led_GPIO_Port, Led_Pin);
        HAL_Delay(500);
    }
}