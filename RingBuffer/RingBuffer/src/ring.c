/*========================================================================
** Circular buffer
** ECEN5813
**========================================================================*/

#include"../inc/ring.h"

typedef Ring_Status Ring_Status;
bool Init_Check = -1;
/***********************************************************************************************
Initializing Buffer
This function initialize the buffer of size length
Input parameters- length(size of buffer)
Return- returns the circular buffer
returns -1 if buffer is
************************************************************************************************/
handle ring_buf_init( handle ring,int8_t *buffer, size_t length )
{

    if(length <= 0)
    {
        ring = NULL;
        printf("\n Length = 0, Cannot initialize Buffer!\n");
        return ring;
    }

    buffer  = (int8_t * )malloc(length * sizeof(int8_t));
    ring  = malloc(sizeof(ring_t));
    ring->length = length;
    ring->buffer = buffer;
    ring_buf_reset(ring);
    Init_Check = 1;
    return ring;
}
handle ring_buf_reinit(handle ring ,int8_t *buffer, int new_length)
{
	int length= ring->length;
	buffer  = realloc(buffer,new_length);
    //if(new_length <=0) //return ERR_INVALID_LENGTH;
    ring  = realloc(ring,sizeof(ring_t));
    ring->length = new_length;
    ring->buffer = buffer;
    ring->Outi = (ring->Outi+new_length - length) % new_length ;
    ring->full = false;
    return ring;
}

Ring_Status ring_buf_reset(handle ring)
{
    if( Init_Check == 1)
    {
	ring->Ini = 0;
    	ring->Outi = 0;
    	ring->full = 0;
    		if(ring_buf_empty(ring))
   	  		return OPR_SUCCESSFUL;
    }
    else
    	return ERR_BUFFER_NOT_INIT;
}

Ring_Status ring_buf_free(handle ring)
{
	if( Init_Check == 1 || ring == NULL)
    	{
   		if(ring != NULL)
		{	free(ring);
	    		return OPR_SUCCESSFUL;
		}
	}
	else
		return ERR_BUFFER_NOT_INIT;
}

bool ring_buf_full(handle ring)
{
    return ring->full;
}

bool ring_buf_empty(handle ring)
{
   return((!(ring->full) && (ring->Ini == ring->Outi)));
}

int ring_buf_capacity(handle ring)
{
    return(ring->length);
}
int ring_buf_entries(handle ring)
{
    int size;
    if(!ring->full)
    {
        if(ring->Ini >= ring->Outi)
            size= (ring->Ini- ring->Outi);
        else
            size= ring->length  + ring->Ini- ring->Outi;
    }
    else
        size = ring->length;

    return size;
}
Ring_Status ring_buf_insert(handle ring, int8_t data)
{
    if( Init_Check == 1)
    {
    	if(ring->full)
    	{
        	printf("\nBuffer is Full\n");
        	return ERR_BUFFER_FULL;
   	 }
    	else
    	{
    		ring->buffer[ring->Ini] = data;
    		ring->Ini = (ring->Ini + 1) % ring->length;
    		if(ring->Ini == ring->Outi)
     		ring->full = true;
    		return OPR_SUCCESSFUL;
    	}
     }
     else 
	return ERR_BUFFER_NOT_INIT;
	
}

Ring_Status ring_buf_remove(handle ring, int8_t data )
{
    if(!ring_buf_empty(ring))
    {
        data = ring->buffer[ring->Outi];
        printf("Element Deleted is [%c] \n", data);
        ring->full = false;
        ring->Outi = (ring->Outi + 1) % ring->length;
	return OPR_SUCCESSFUL;
    }
    else
    {
        printf("Buffer Empty\n\n");
	return ERR_BUFFER_EMPTY;
    }
}
Ring_Status ring_buf_read(handle ring, int8_t data)
{
    int size = ring_buf_entries(ring);
    if (size == 0)
    {
    	printf("Buffer is Empty");
	return ERR_BUFFER_EMPTY;
    }
    for(int i=0; i<size;i++)
    {
    	data = ring->buffer[ring->Outi+i];
    	printf(" [%c] \n",data);
    }
	return OPR_SUCCESSFUL;
}

