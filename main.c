#include <stdint.h>

#define REG32(addr) (*(volatile uint32_t *)addr)

#define GPIOA_ENABLE REG32(0x40023830U)
#define GPIOA_MODER REG32(0x40020000U)
#define GPIOA_BSRR REG32(0x40020018U)
#define RCC_APB2ENR REG32(0x40023844)
#define SYSCFG_EXTICR2 REG32(0x4001380C)
#define EXTI_IMR REG32(0x40013C00)
#define EXTI_RTSR REG32(0x40013C08)
#define EXTI_FTSR REG32(0x40013C0C)
#define EXTI_PR REG32(0x40013C14)
#define NVIC_ISER0 REG32(0xE000E100)

void BlinkLED(int enable_blink)
{
    static unsigned int counter = 0;
    static int dim = 0;
    if (!(GPIOA_MODER & 0x1000) || (GPIOA_MODER & 0x2000))
    {
        /* printf("You have not enabled gpio  a6 pin"); */
        return;
    }
    if (enable_blink == 0)
    {
        GPIOA_BSRR = (1UL << 22);
        dim = 0;
        counter = 0;
        return;
    }

    switch (dim)
    {
        case 0:
            GPIOA_BSRR = (1UL << 22);
            break;
        case 1:
            GPIOA_BSRR = (1UL << 6);
            break;
        default:
            break;
    }

    if (counter++ >= 2000000)
    {
        dim ^= 1;
        counter = 0;
    }
}


static volatile int enable_blink = 0;

void EXTI9_5_IRQHandler()
{
    if (EXTI_PR & (1UL << 5))
    {
        enable_blink ^= 1;
        EXTI_PR = (1UL << 5);
    }
}

int main(void)
{
    //enable clock for a
    GPIOA_ENABLE |= 0x1U;
    //enable syscofg clock bit 14
    RCC_APB2ENR |= ( 1UL << 14 );

    //enable a5 as input for interrupts by clearing them and clearing a6 
    GPIOA_MODER &= ~(0x3C00U);

    //enable a6 as output gpio
    GPIOA_MODER |= 0x1000;

    //enable a5 channel for interrupts
    SYSCFG_EXTICR2 &= ~(0xF0);

    //allow m5 exti to generate request
    EXTI_IMR |= (1UL << 5);

    //allow rise and fall response for m5
    EXTI_RTSR |= (1UL << 5);
    EXTI_FTSR |= (1UL << 5);
    
    //config nvic so that we can request
    NVIC_ISER0 |= (1UL << 23);

    while (1)
    {
        BlinkLED(enable_blink);
    }
}

//ignore this two funtions 
void SystemInit(void)
{
    /* Use the STM32's default reset clock configuration. */
}

void __libc_init_array(void)
{
    /* No C++ constructors or initialization arrays are needed yet. */
}
