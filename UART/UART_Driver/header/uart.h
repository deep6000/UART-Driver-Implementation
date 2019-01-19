


#include "stdint-gcc.h"
#define System_clock (48000000)  // System clck is 48MHz
#define Baud_rate (115200)        // baud rate
#define OSR (15)                 // over sampling rate 16

typedef enum UART
{
    Success = -1,
    Null_pointer = -2,
    Invalid_length = -3,
    Config_fail = -4,
    Unknown_error = -5,
} UART_Status;

UART_Status UART_Configure();
UART_Status UART_Send(uint8_t data);
UART_Status UART_Send_bytes(uint8_t* data, uint8_t length);
char UART_Receive (uint8_t data);
UART_Status UART_Receive_bytes();
void Myprintf(char* format,...);






