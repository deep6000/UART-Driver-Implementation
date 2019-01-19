
/*========================================================================
** ring.h
** Circular buffer
** ECEN5813
**========================================================================*/
typedef enum
{
    ERR_INVALID_LENGTH,
    ERR_BUFFER_NOT_EMPTY,
    ERR_BUFFER_EMPTY,
    ERR_BUFFER_FULL
}error;

typedef struct
{
	uint8_t *buffer;  //data buffer
	int length;		// length of buffer
	int Ini;
	int Outi;
	bool full;
} ring_t;

typedef ring_t* handle;
handle ring, ring1, ring2, ring3;
//ring_t *arr[];


int ring_buf_reset(ring_t *ring);
handle ring_buf_init( handle ring, int8_t *buffer, int length);
handle ring_buf_reinit(handle ring,int8_t *buffer, int length);
void ring_buf_free( handle ring);
bool ring_buf_full(handle ring);
bool ring_buf_empty(handle ring);
int ring_buf_capacity(handle ring);
int ring_buf_entries(handle ring);
error ring_buf_insert(handle ring, int8_t *data);

char ring_buf_remove(handle ring, int8_t *data );
error ring_buf_read(handle ring, int8_t *data);


