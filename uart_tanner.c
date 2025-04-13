///*
//*
//*   uart.c
//*
//*
//*
//*
//*
//*   @author
//*   @date
//*/
//
//#include "uart.h"
//#include "string.h"
//
//volatile char uart_data;
//volatile int flag;
//
//void uart_init(void){
//
//    SYSCTL_RCGCGPIO_R |= 0x02;
//    while ((SYSCTL_PRGPIO_R & 0x02) == 0){};
//
//    SYSCTL_RCGCUART_R |= 0x02;
//    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
//    while ((SYSCTL_PRUART_R & 0x02) == 0) {};
//
//    GPIO_PORTB_AFSEL_R |= 0x03;
//    GPIO_PORTB_DEN_R |= 0x03;
//    GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the disired locations
//    GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the disired locations
//
//    uint16_t iBRD = 0x08;
//    uint16_t fBRD = 0x2C;
//
//    GPIO_PORTB_DIR_R &= 0b0;      // Force 0's in the disired locations
//    GPIO_PORTB_DIR_R |= 0b10;
//
//    UART1_CTL_R &= 0xFFFFFFFE;
//    UART1_IBRD_R = iBRD;
//    UART1_FBRD_R = fBRD;
//    UART1_LCRH_R = 0x60;
//    UART1_CC_R = 0x0;
//    UART1_CTL_R |= 0x01;
//}
//
//void uart_sendChar(char data){
//    while((UART1_FR_R & 0x20) != 0){}
//    UART1_DR_R = data;
//}
//
//char uart_receive(void){
//    char rdata;
//    while((UART1_FR_R & 0x10) != 0){};
//    rdata = (char)(UART1_DR_R & 0xFF);
//    return rdata;
//}
//
//void uart_sendStr(const char *data){
//    int len = strlen(data);
//    int i;
//    for(i = 0; i < len; i++){
//        uart_sendChar(data[i]);
//    }
//    uart_sendChar('\n');
//}
//
//void init_uart_interupts(void) {
//    UART1_IM_R &= 0xEF;
//
//    UART1_ICR_R |= 0x10;
//
//    NVIC_EN0_R |= 0b1000000;
//
//    UART1_IM_R |= 0x10;
//
//    IntRegister(INT_UART1, uart1_handler);
//}
//
//void uart1_handler(void) {
//    UART1_ICR_R |= 0x10;
//    uart_data = uart_receive();
//    flag = 1;
//}
