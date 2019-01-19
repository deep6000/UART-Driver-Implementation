#include "../inc/ring.h"

int main()
{
    int input = 0, length = 0, size = 0, count = 0;
     int8_t data_ip = 0, data_out = 0, data_read = 0;
     int8_t * buffer1 = '\0';

    while(1)
    {
Here:   printf("\nCircular Buffer\n 1)Create new Buffer\n 2)Insert into Buffer\n 3)Remove Element from Buffer\n 4)Reset Buffer\n 5)Free Buffer \n 6) No of Entries\n 7) Read entries\n 8) Exit \n");
        scanf("%d",&input);
        switch(input)
        {
            case 1:
                count++;
                printf("\n Enter the length of the buffer\n");
                scanf("%d",&length);
                printf("\nLength is %d\n", length);

                ring = ring_buf_init(ring,buffer1,length);
                if(ring == NULL) goto Here;
                printf("Buffer initialized. Full: %d, empty: %d, size: %d\n",
                ring_buf_full(ring),ring_buf_empty(ring),ring_buf_capacity(ring));
            break;

            /*case 2:
                if (count>0)
                {
                	printf("Select the buffer you want to edit\n");
                }
                else
                printf("No Buffer Initialized\n");
            break;*/

            case 2:

                if(count >0)
                {	if(!(ring->full))
					{
					int8_t temp;
                	printf("Enter the data to be Inserted\n");
                	scanf("%c%c",&temp,&data_ip);
                	printf("%c",data_ip);
                	ring_buf_insert( ring , data_ip);
					}
					else
						printf("Buffer is Full\n");
			   }
                else
                {
                printf("No Buffer Initialized\n");

                }
            break;

            case 3:
                if(count >0)
                {
                ring_buf_remove(ring, data_out);
                }
                else
                printf("No Buffer Initialized\n");
		//printf("Data Deleted is %u\n",data_out);
            break;

            case 4:
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

            case 5:
                if(count > 0)
                {
                ring_buf_free(ring);
                printf("Buffer Freed");
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 6:
                if(count > 0)
                {
                size=ring_buf_entries(ring);
                printf("Size  is %d\n",size);
                }
                else
                printf("No Buffer Initialized\n");
            break;

            case 7:
                if(count > 0)
                ring_buf_read( ring, data_read);
                else
                printf("No Buffer Initialized\n");
            break;

            /*case 9:
                if(count > 0 )
                {
                    Input_length:
                    printf("Enter new length\n");
                    scanf("%d",&new_length);
                    
                        
                        ring = ring_buf_reinit(ring,buffer1,new_length);
                        printf("Buffer initialized. Full: %d, empty: %d, size: %d\n",
                        ring_buf_full(ring),ring_buf_empty(ring),ring_buf_capacity(ring));
                    
                    else
                    {
                        printf("Enter valid length\n");
                        goto Input_length;
                    }
               // }
            else
                    printf("No Buffer Initialized\n");
            break;*/

	    case 8:
		exit(0);
            default:
                printf("Invalid Input\n");
            break;
        }
    }
}

