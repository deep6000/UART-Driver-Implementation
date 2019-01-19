
/*========================================================================
** ring.h
** Circular buffer
** ECEN5813
**========================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>

typedef struct
{
	int8_t *buffer;  	//data buffer
	int length;		// length of buffer
	int Ini;
	int Outi;
	bool full;
} ring_t;

typedef enum
{
    ERR_INVALID_LENGTH = -1,
    ERR_BUFFER_NOT_EMPTY = -2,
    ERR_BUFFER_EMPTY = -3,
    ERR_BUFFER_FULL = -4,
    ERR_BUFFER_NOT_INIT = -5,
    OPR_SUCCESSFUL = 1,
    OPR_FAILED = 0
}Ring_Status;

typedef ring_t* handle;
handle ring,ring1,ring2,ring3;
//ring_t *arr[];

handle ring_buf_init(handle ring, int8_t *buffer, size_t length);
handle ring_buf_reinit(handle ring,int8_t *buffer, int length);
Ring_Status ring_buf_reset(handle ring);
Ring_Status ring_buf_free( handle ring);
bool ring_buf_full(handle ring);
bool ring_buf_empty(handle ring);
int ring_buf_capacity(handle ring);
int ring_buf_entries(handle ring);
Ring_Status ring_buf_insert(handle ring, int8_t data);
Ring_Status ring_buf_remove(handle ring, int8_t data );
Ring_Status ring_buf_read(handle ring, int8_t data);

