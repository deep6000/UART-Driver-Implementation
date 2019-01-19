
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"uart.h"
#include"ring.h"
#include"project2.h"
#include "MKL25Z4.h"
#include <assert.h>
#include<string.h>
#include<stdarg.h>

handle TX_Pointer;
handle RX_Pointer;
handle Stats_Pointer;
 int8_t* Tx_buffer= NULL;
 int8_t* Rx_buffer = NULL;
 int8_t* statistics =NULL;
int8_t TDATA = 0;
int8_t RDATA = 0;
int Stats[256]= {0};
int8_t TD_ptr =NULL;
#define IRQ
uint8_t new_line = 10;
uint8_t next_line = 13;
uint8_t space = 9;
