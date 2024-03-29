#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>
#include <typedefs.h>
#include <timer.h>
#include <Ucglib.h>

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

#define BTN_RELEASED						0
#define BTN_PRESSED							1

#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0

#define BUZZER_GPIO_PORT					GPIOC
#define BUZZER_GPIO_PIN						GPIO_Pin_9
#define BUZZERControl_SetClock				RCC_AHB1Periph_GPIOC

#define BUTTON_GPIO_PORT					GPIOB
#define BUTTON_GPIO_PIN						GPIO_Pin_5
#define BUTTONControl_SetClock				RCC_AHB1Periph_GPIOB

#define LEDRED_GPIO_PORT					GPIOB
#define LEDRED_GPIO_PIN						GPIO_Pin_13
#define LEDREDControl_SetClock				RCC_AHB1Periph_GPIOB

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static void_t buzzer_Init(void_t);
static void_t button_Init(void_t);
static void_t buzzerControlSetStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin, u8_t byStatus);
static u8_t buttonReadStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin);
static void_t LEDRED_init(void_t);
static void_t LEDREDControl_SetStatus(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN, uint8_t Status);
static void_t delay(void_t);
static ucg_t ucg;

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
void_t delay(void_t);

/******************************************************************************/


int main(void_t) {
    uint8_t buttonState = BTN_RELEASED;
    uint8_t ledState = GPIO_PIN_RESET;
    uint8_t buzzerState = GPIO_PIN_RESET;

    SystemCoreClockUpdate();
    TimerInit();
    Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
    ucg_ClearScreen(&ucg);
    ucg_SetFont(&ucg, ucg_font_courB12_tr);
    ucg_SetColor(&ucg, 0, 0, 255, 0);
    ucg_SetColor(&ucg, 1, 0, 0, 0);
    ucg_SetRotate180(&ucg);
    ucg_DrawString(&ucg, 35, 52, 0, "Nhom 2");
    ucg_DrawString(&ucg, 50, 68, 0, "VIP");

    LEDRED_init();
    buzzer_Init();
    button_Init();

    while (1) {
        processTimerScheduler();

        if (buttonReadStatus(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN) == BTN_PRESSED && buttonState == BTN_RELEASED) {
            delay();  // Chờ một lúc để chắc chắn rằng nút đã được thả
            buttonState = BTN_PRESSED;

            // Đảo trạng thái của đèn và còi
            ledState = (ledState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;
            buzzerState = (buzzerState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;

            // Điều khiển trạng thái của đèn và còi
            LEDREDControl_SetStatus(LEDRED_GPIO_PORT, LEDRED_GPIO_PIN, ledState);
            buzzerControlSetStatus(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, buzzerState);
        } else if (buttonReadStatus(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN) == BTN_RELEASED && buttonState == BTN_PRESSED) {
            delay();  // Chờ một lúc để chắc chắn rằng nút đã được thả
            buttonState = BTN_RELEASED;
        }
    }

    return 0;
}

/**
 * @func   delay
 * @brief  use when you want to delay
 * @param  None
 * @retval None
 */
void_t delay(void_t) {
    for (uint32_t i = 0; i < 500000; i++);
}

/**
 * @func   buzzer_Init
 * @brief  Initialize GPIO for buzzer
 * @param  None
 * @retval None
 */
static void_t buzzer_Init(void_t) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(BUZZERControl_SetClock, ENABLE);
    GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @func   button_Init
 * @brief  Initialize GPIO for button
 * @param  None
 * @retval None
 */
static void_t button_Init(void_t) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);
    GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @func   buzzerControlSetStatus
 * @brief  control status buzzer
 * @param  Port, pin
 * @retval None
 */
static void_t buzzerControlSetStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin,
        u8_t byStatus) {
    // SET bit in BSRR Registers

    if (byStatus == GPIO_PIN_SET) {
        pGPIOx->BSRRL = wGPIO_Pin;
    }
    if (byStatus == GPIO_PIN_RESET) {
        pGPIOx->BSRRH = wGPIO_Pin;
    }
}

/**
 * @func   buttonReadStatus
 * @brief  Read status of button
 * @param  Port, Pin
 * @retval u8_t
 */
static u8_t buttonReadStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin) {
    u8_t Read_Pin = GPIO_PIN_RESET;

    if ((pGPIOx->IDR & wGPIO_Pin) != GPIO_PIN_RESET) {
        Read_Pin = GPIO_PIN_SET;
    } else {
        Read_Pin = GPIO_PIN_RESET;
    }
    return Read_Pin;
}

/**
 * @func   LEDRED_init
 * @brief  Initialize GPIO for LED RED
 * @param  None
 * @retval None
 */
static void_t LEDRED_init(void_t) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(LEDREDControl_SetClock, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LEDRED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(LEDRED_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @func   LEDREDControl_SetStatus
 * @brief  control status LED RED
 * @param  GPIOx, GPIO_PIN, Status
 * @retval None
 */
static void_t LEDREDControl_SetStatus(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN, uint8_t Status) {
    if (Status == GPIO_PIN_SET) {
        GPIOx->BSRRL = GPIO_PIN;
    }
    if (Status == GPIO_PIN_RESET) {
        GPIOx->BSRRH = GPIO_PIN;
    }
}
