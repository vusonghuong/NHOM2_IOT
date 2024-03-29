/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include <timer.h>
#include <Ucglib.h>


static ucg_t ucg;

int main(void)
{
    SystemCoreClockUpdate(); // Cấp clock
    TimerInit(); // Khởi tạo chức năng timer

    // Khởi tạo LCD
    Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
    ucg_ClearScreen(&ucg);

    ucg_SetFont(&ucg, ucg_font_courB12_tr); //Lựa chọn font và size chữ
    ucg_SetColor(&ucg, 0, 0, 255, 0); // Chọn màu chữ
    ucg_SetColor(&ucg, 1, 0, 0, 0); // Chọn màu background
    ucg_SetRotate180(&ucg); // Quay màn hình lại 180 độ
    ucg_DrawString(&ucg, 35, 52, 0, "Nhom 2");
    ucg_DrawString(&ucg, 50, 68, 0, "VIP ORO");

    while(1){
    	processTimerScheduler();
    }
}