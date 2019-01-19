/*========================================================================
** Circular buffer
** ECEN5813
**========================================================================*/
#include"main.h"


bool ring_buf_empty(handle ring);
/************************************************************************************************
Initializing Buffer
This function initialize the buffer of size length
Input parameters- length(size of buffer)
Return- returns the circular buffer
returns -1 if buffer is
************************************************************************************************/
handle ring_buf_init( handle ring, int8_t *buffer, int length)
{

    if(length <=0) return ERR_INVALID_LENGTH;
    buffer  = malloc(length);
    ring  = malloc(sizeof(ring_t));
    ring->length = length;
    ring->buffer = buffer;
    ring_buf_reset(ring);
  //      return -1;
    if(ring_buf_empty(ring))
    {
    return ring;
    }
    else
    {
   // printf("Buffer not Empty");
    	return ERR_BUFFER_NOT_EMPTY;
    }
}
handle ring_buf_reinit(handle ring ,int8_t *buffer, int new_length)
    {
	int length= ring->length;
	buffer  = realloc(buffer,new_length);
  //  if(new_length <=0) return ERR_INVALID_LENGTH;
    ring  = realloc(ring,sizeof(ring_t));
    ring->length = new_length;
    ring->buffer = buffer;
    ring->Ini = (ring->Ini+length)% new_length;
    ring->full = false;
    return ring;
    }

int ring_buf_reset(handle ring)
{
    ring->Ini = 0;
    ring->Outi = 0;
    ring->full = false;
    if(ring_buf_empty(ring))
        return 1;
    else
    return 0;
}
void ring_buf_free( handle ring)
{
    //assert(ring);
    free(ring);
}
bool ring_buf_full(handle ring)
{
    //assert(ring);
    return ring->full;
}

bool ring_buf_empty(handle ring)
{
   assert(ring);
   return((!(ring->full) && (ring->Ini == ring->Outi)));
}

int ring_buf_capacity(handle ring)
{
    assert(ring);
    return(ring->length);
}
int ring_buf_entries(handle ring)
{
    int size;
    assert(ring);
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
error ring_buf_insert(handle ring, int8_t *data)
{
    if(ring->full)
    {
     //   printf("Buffer is Full\n");
     //   return ERR_BUFFER_FULL;
    }
    else
    {
	ring->buffer[ring->Ini]= *data;
    ring->Ini = (ring->Ini + 1) % ring->length;
    if(ring->Ini == ring->Outi)
     ring->full = true;
    //return 0;
    }
}

char ring_buf_remove(handle ring, int8_t *data )
{
    if(!ring_buf_empty(ring))
    {
        *data = ring->buffer[ring->Outi];
      //  printf("data deleted is %s \n", data);
        ring->full = false;
        ring->Outi = (ring->Outi + 1) % ring->length;
        return *data;
    }
    else
    	return ERR_BUFFER_EMPTY;
    	//printf("Buffer Empty\n\n");
}
error ring_buf_read(handle ring, int8_t *data)
{
    int size=ring_buf_entries(ring);
    if (size == 0)
    {
    	return ERR_BUFFER_EMPTY;
    // printf("Buffer is Empty");
    }
    for(int i=0; i<size;i++)
    {
    data = ring->buffer[ring->Outi+i];
    //printf("Data is %s \n",data);
    }
}
/*
int main()
{
    int input=0, length=0, size=0, new_length, count=0;
     char data_ip=0, *data_out=0, *data_read=0;
     char *buffer;

    while(1)
    {
        printf("\nCircular Buffer\n 1)Create new Buffer\n 2)Edit buffer\n 3)Insert into Buffer\n 4)Remove Buffer\n 5)Reset Buffer\n 6)Free Buffer \n 7) No of Entries\n 8) read entries\n 9) Increase Buffer size\n");
        scanf("%d",&input);
        switch(input)
        {
            case 1:
                count++;
                printf("\n Enter the length of the buffer\n");
                scanf("%d",&length);
                printf("\nLength is %d\n", length);

                ring = ring_buf_init(ring1,buffer,length);
                printf("Buffer initialized. Full: %d, empty: %d, size: %d\n",
                ring_buf_full(ring),ring_buf_empty(ring),ring_buf_capacity(ring));
            break;

            case 2:
                if (count>0)
                {
                printf("Select the buffer you want to edit\n");
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 3:

                if(count >0)
                {
                printf("Enter the data to be Inserted\n");
                scanf("%s",&data_ip);
                ring_buf_insert( ring , &data_ip);
                }
                else
                {
                printf("No Buffer Initialized\n");

                }
            break;

            case 4:
                if(count >0)
                {
                ring_buf_remove(ring, &data_out);
                }
                else
                printf("No Buffer Initialized\n");
//printf("Data Deleted is %u\n",data_out);
            break;

            case 5:
                if(count >0)
                {
                    if(ring_buf_reset(ring))
                        printf("Reset Successful\n");
                    else
                        printf("Reset UnSuccessful\n");
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 6:
                if(count>0)
                {
                ring_buf_free(ring);
                printf("Buffer Freed");
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 7:
                if(count>0)
                {
                size=ring_buf_entries(ring);
                printf("Size  is %d\n",size);
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 8:
                if(count >0)
                ring_buf_read( ring, &data_read);
                else
                printf("No Buffer Initialized\n");
            break;

            case 9:
                if(count >0 )
                {
                    Input_length:
                    printf("Enter new length\n");
                    scanf("%d",&new_length);
                    if (new_length>length)
                    {
                        buffer  = realloc(buffer,new_length);
                        ring = ring_buf_reinit(buffer,new_length);
                        printf("Buffer initialized. Full: %d, empty: %d, size: %d\n",
                        ring_buf_full(ring),ring_buf_empty(ring),ring_buf_capacity(ring));
                    }
                    else
                    {
                        printf("Enter valid length\n");
                        goto Input_length;
                    }
                }
                else
                    printf("No Buffer Initialized\n");
            break;


            default:
                printf("Invalid Input\n");
            break;
        }
    }
}
*/
