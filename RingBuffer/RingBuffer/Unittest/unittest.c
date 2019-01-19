/*Citation : http://wpollock.com/CPlus/CUnitNotes.htm was referred to for the code*/

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "CUnit/Console.h"
#include <time.h>
#include <stdint.h>
#include "../inc/ring.h"

#define RINGTEST

handle Ring_Test ;
int8_t * Buffer_Test;
size_t Ring_BuffLen;
int8_t Data_Test;
time_t ti;
	

int init_suite(void) 
{ 
	srand(time(NULL));
	return 0; 
}
int clean_suite(void) { return 0; }
	
void RingCUnit_InvPointer()
{
	Ring_BuffLen = rand()%100;
	Ring_Test = ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	CU_ASSERT_PTR_NOT_NULL( Ring_Test);
}

/* Test Case for error returning for Zero Buffer Length */
void RingCUnit_ZeroLength()
{
	Ring_BuffLen = 0;
	Ring_Test = ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	if( Ring_Test == NULL )
	CU_ASSERT_PTR_NULL(Ring_Test);
}

/* Test Case to check for successful Insertion of element into the buffer*/
void RingCUnit_BufInsScs()
{
	Ring_BuffLen = rand()%100;
	Data_Test = rand()%127;
	Ring_Test= ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	Ring_Status Status = ring_buf_insert( Ring_Test, Data_Test );
	CU_ASSERT_EQUAL(Status, OPR_SUCCESSFUL );
}

/* Test Case for Buffer Overflow Check */
void RingCUnit_BuffOvrflw()
{
	Ring_BuffLen = rand()%100;
	Data_Test = rand()%127;
    Ring_Test = ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	for( int i = 0; i < Ring_BuffLen; i++ )
	{
		ring_buf_insert( Ring_Test, Data_Test );
	}	
	bool Status = ring_buf_full( Ring_Test );
	CU_ASSERT_TRUE( Status );
}

/* Test Case to check for successful Deletion of element into the buffer*/
void RingCUnit_BufDelScs()
{
	Ring_BuffLen = rand()%100;
	Data_Test = rand()%127;
	Ring_Test = ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	ring_buf_insert( Ring_Test, Data_Test );
	Ring_Status Status = ring_buf_remove( Ring_Test, Data_Test );
	CU_ASSERT_EQUAL(Status, OPR_SUCCESSFUL );
}

/* Test Case to check for Empty Buffer */
void RingCUnit_BufEmpty()
{
	Ring_BuffLen = rand()%100;
	Data_Test = rand()%127;
	Ring_Test= ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	for( int i = 0; i < Ring_BuffLen; i++ )
	{
		ring_buf_insert( Ring_Test, Data_Test );
	}
	for( int j = 0; j < Ring_BuffLen; j++ )
	{
		ring_buf_remove( Ring_Test, Data_Test );
	}	
	bool Status = ring_buf_empty(Ring_Test);
	CU_ASSERT_TRUE( Status );
}

void RingCunit_BufFree()
{
	Ring_BuffLen = rand()%100;
	Ring_Test = ring_buf_init( Ring_Test, Buffer_Test, Ring_BuffLen );
	Ring_Status Status = ring_buf_free(Ring_Test);
	CU_ASSERT_EQUAL( Status,OPR_SUCCESSFUL);		
}


/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "RingCUnit_InvPointer", init_suite, clean_suite );
   pSuite = CU_add_suite( "RingCUnit_ZeroLength", init_suite, clean_suite );  
   pSuite = CU_add_suite( "RingCUnit_BufInsScs", init_suite, clean_suite );
   pSuite = CU_add_suite( "RingCUnit_BuffOvrflw", init_suite, clean_suite );
   pSuite = CU_add_suite( "RingCUnit_BufDelScs", init_suite, clean_suite );
   pSuite = CU_add_suite( "RingCUnit_BufEmpty", init_suite, clean_suite );
 pSuite = CU_add_suite( "RingCunit_BufFree", init_suite, clean_suite );

   if ( NULL == pSuite ) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "RingCUnit_InvPointer", RingCUnit_InvPointer)) || (NULL == CU_add_test(pSuite, "RingCUnit_ZeroLength", 		RingCUnit_ZeroLength)) || (NULL == CU_add_test(pSuite, "RingCUnit_BufInsScs", RingCUnit_BufInsScs)) || (NULL == CU_add_test(pSuite, 		"RingCUnit_BuffOvrflw", RingCUnit_BuffOvrflw)) || (NULL == CU_add_test(pSuite, "RingCUnit_BufDelScs", RingCUnit_BufDelScs)) || (NULL == 		CU_add_test(pSuite, "RingCUnit_BufEmpty", RingCUnit_BufEmpty))||(NULL == 		CU_add_test(pSuite, "RingCunit_BufFree", RingCunit_BufFree)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
