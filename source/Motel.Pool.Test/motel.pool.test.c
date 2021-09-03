/*----------------------------------------------------------------------------
  Motel Pool Test

  executable implementation file
  ---------------------------------------------------------------------------- 
  Copyright 2010-2011 John L. Hart IV. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain all copyright notices,
     this list of conditions and the following disclaimer.
 
  2. Redistributions in binary form must reproduce all copyright
     notices, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
 
  THIS SOFTWARE IS PROVIDED BY John L. Hart IV "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
  NO EVENT SHALL John L. Hart IV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
 
  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of John L Hart IV.
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Standard libraries
  ----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*----------------------------------------------------------------------------
  Public data types
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.Memory/motel.memory.i.h"

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

#include "../Motel.Pool/motel.pool.t.h"

  /*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.Pool/motel.pool.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.pool.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.pool.test.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

motelMemoryHandle gMemory = (motelMemoryHandle) NULL;

struct node gNodes[THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES];

unsigned long gNodeCount;
unsigned long gNodeIndex;

FILE *gFile;

long long gLongLong = 9876543210;

/*----------------------------------------------------------------------------
  Main
  ----------------------------------------------------------------------------*/

void main
(
    void
)
{
    int lOption;

	gFile = stdout;

	Construct();

    do
    {
		printf("Option: ");

		do
		{
			lOption = fgetc(stdin);
		}
		while (!IsPrintable(lOption)); /* eat carriage returns (etc) */

        switch ((char) lOption)
        {
            case '?':

                DisplayOptions();
                break;

            case 'Q':
            case 'q':

                Destruct();
				break;

            case 'X':
            case 'x':

                Destruct();
				Construct();
				break;

            case 'C': // allocate
            case 'c':

                AllocateNode();
				break;

            case 'D': // deallocate
            case 'd':

                DeallocateNode();
				break;

            case '#': // display nodes

                NodeList();
				break;

            case '1':

                IteratedTest1();
                break;

			case '2':

                IteratedTest2();
                break;

			case '3':

                IteratedTest3();
                break;

			case '!':

                OutputPoolState();
                break;

            default:

                printf("Valid options are C,D,#,1,2,3,!,X,Q,?\n");
                continue;
        }
    }
	while ('Q' != lOption && 'q' != lOption);
}

void DisplayOptions
(
    void
)
{
	printf("\n"
		   "Options:\n"
		   "\n"
		   "C - Allocate an object\n"
		   "D - Deallocate an object\n"
		   "\n"
           "# - Display object list\n"
		   "\n"
		   "1 - Iterated thorough test\n"
		   "2 - Iterated performance benchmark test\n"
		   "3 - Another iterated performance benchmark test\n"
		   "\n"
		   "! - Display pool state\n"
		   "\n"
		   "X - Reset pool\n"
		   "\n"
		   "Q - Quit\n"
		   "? - Display this option list\n"
		   "\n");
}

void Validate
(
	void
)
{
	if (!ValidatePool(gMemory))
	{
		fprintf(gFile, "Pool self validation failed.\n\n");
		return;
	}
}

void Construct
(
    void
)
{
    if (!ConstructPool(&gMemory, ALLOCATION_SIZE))
	{
		return;
	}

	gNodeCount = 0;

	Validate();
}

void Destruct
(
    void
)
{
	Validate();

    if (!DestructPool(&gMemory))
	{
		return;
	}

	gNodeCount = 0;
}

void AllocateNode
(
	void
)
{
    int lType;

    size_t lSize;

    motelMemoryObjectHandle lObject = (motelMemoryObjectHandle) NULL;

    if ((THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES) == gNodeCount)
    {
        fprintf(gFile, "No room for another node\n\n");
        return;
    }

    lType = rand() % 2;

    if (0 == lType)
    {
        SizeOfObject(struct f, lSize);
    }
    else
    {
        SizeOfObject(struct g, lSize);
    }

	if (AllocatePoolMemory(gMemory, &lObject, lSize))
    {
    	Validate();
	    
        GenerateInsertData(lType, lObject);

        gNodes[gNodeCount].type = lType;

        if (0 == lType)
        {
            gNodes[gNodeCount].f = (struct f *) lObject;
        }
        else
        {
            gNodes[gNodeCount].g = (struct g *) lObject;
        }

        gNodeCount++;
    }

   	Validate();
}

void DeallocateNode
(
	void
)
{
    motelMemoryObjectHandle lObject;

    if (0 == gNodeCount)
    {
        fprintf(gFile, "No node to delete\n\n");
        return;
    }

    gNodeCount--;

    if (0 == gNodes[gNodeCount].type)
    {
        lObject = gNodes[gNodeCount].f;
    }
    else
    {
        lObject = gNodes[gNodeCount].g;
    }

    if (!DeallocatePoolMemory(gMemory, &lObject))
    {
        fprintf(gFile, "Deallocation failed\n\n");
    }

	Validate();
}

void NodeList
(
	void
)
{
	for (gNodeIndex = 0; gNodeIndex < gNodeCount; gNodeIndex++)
    {
        OutputNodeData();
    }
}

void IteratedTest1
(
	void
)
{
    unsigned long lAllocationLimit;
    unsigned long lBlockSize;
    unsigned long lPools = 0;
    unsigned long lPool;
    unsigned long lPoolObjectSize[1000];
    unsigned long lSmallestPoolObjectSize = 1000000;
    unsigned long lTestDuration;

    unsigned long lAllocation;

    void ** lObjects;
    void ** lObject;

    size_t lIndexSize;

	time_t lStartTime;

    printf("\n"
           "Thorough test of:\n"
           "AllocatePoolMemory() & DestructPool() & DeallocatePoolMemory()\n");

    printf("\n");

    do
    {
        printf("Minimum Test Duration (3-600 seconds): ");
        scanf("%u", &lTestDuration);
    } while (3 > lTestDuration || 600 < lTestDuration);

    printf("\n");

    do
    {
        printf("Memory Allocation Limit (10-2,000 megabytes): ");
        scanf("%u", &lAllocationLimit);
    } while (10 > lAllocationLimit || 2000 < lAllocationLimit);

    lAllocationLimit *= 1000000;

    printf("\n");

    do
    {
        printf("Block Allocation Size (max 100 megabytes): ");
        scanf("%u", &lBlockSize);
    } while (0 == lBlockSize || 100 < lBlockSize);

    lBlockSize *= 1000000;

    printf("\n");

    while (TRUE)
    {
        printf("Pool %d: Object Size (max 1,000,000 bytes): ", lPools + 1);
        scanf("%u", &lPoolObjectSize[lPools]);

        if (0 < lPools && 0 == lPoolObjectSize[lPools])
        {
            break;
        }

        if (1000000 > lPoolObjectSize[lPools])
        {
            lSmallestPoolObjectSize = lSmallestPoolObjectSize > lPoolObjectSize[lPools] ? lPoolObjectSize[lPools] : lSmallestPoolObjectSize;

            lPools++;
        }

        if (0 < lPools)
        {
            printf("Enter Zero to Begin Test\n");
        }
    }

    Destruct();

    Validate();

    printf("\n"
           "STARTED: AllocatePoolMemory() & DestructPool()\n");

	lStartTime = time((time_t *) NULL);

    do
    {
        void * lObject;

        Construct();
        Validate();

        if (!SetPoolMember(&gMemory, motelPoolMember_BlockSize, &lBlockSize))
        {
            return;
        }

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            lObject = NULL;

            if (!AllocatePoolMemory(gMemory, &lObject, lPoolObjectSize[lPool]))
            {
                break;
            }
        }

        Validate();

        Destruct();

        Validate();

    } while (lTestDuration > (unsigned long) difftime(time((time_t *) NULL), lStartTime));

    printf("FINISHED: AllocatePoolMemory() & DestructPool()\n");

    Construct();

    Validate();

    /*
    ** set the alloation size of blocks within a pool
    */

    if (!SetPoolMember(&gMemory, motelPoolMember_BlockSize, &lBlockSize))
    {
        return;
    }

    /*
    ** allocate the object index
    */

    lIndexSize = sizeof(void *) * (lAllocationLimit / lSmallestPoolObjectSize);

    lObjects = (void **) NULL;

    if (!SafeMallocBlock((void **) lObjects, lIndexSize))
    {
        return;
    }

    printf("\n"
           "STARTED: AllocatePoolMemory() & DeallocatePoolMemory()\n");

	lStartTime = time((time_t *) NULL);

    do
    {
        lObject = lObjects;

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            * lObject = NULL;

            if (!AllocatePoolMemory(gMemory, lObject, lPoolObjectSize[lPool]))
            {
                break;
            }

            lObject++;
        }

        Validate();

	    while (lObjects < lObject)
	    {
            lObject--;

            if (!DeallocatePoolMemory(gMemory, lObject))
            {
                break;
            }
        }

        Validate();

    } while (lTestDuration > (unsigned long) difftime(time((time_t *) NULL), lStartTime));

    printf("FINISHED: AllocatePoolMemory() & DeallocatePoolMemory()\n");

    /*
    ** deallocate the object index
    */

    if (!SafeFreeBlock((void **) &lObjects))
    {
        return;
    }

    /*
    ** finished
    */

	printf("\n");

    OutputPoolState();
}

void IteratedTest2
(
	void
)
{
    unsigned long lAllocationLimit;
    unsigned long lBlockSize;
    unsigned long lPools = 0;
    unsigned long lPool;
    unsigned long lPoolObjectSize[1000];
    unsigned long lSmallestPoolObjectSize = 1000000;
    unsigned long lTestDuration;

    unsigned long lAllocation;

    void ** lObjects;
    void ** lObject;

    size_t lIndexSize;

	time_t lStartTime;

	double lSeconds;

	double lAllocatePoolMemorySeconds = 0;
	double lSafeMallocSeconds = 0;
	double lTotalSeconds;

    double lNormalizedAllocatePoolMemorySeconds;
    double lNormalizedSafeMallocSeconds;
    double lNormalizedTotalSeconds;

    double lAllocatePoolMemoryTransactions = 0;
    double lSafeMallocTransactions = 0;
    double lTotalTransactions;

    printf("\n"
           "Performance comparison of:\n"
           "AllocatePoolMemory() & DestructPool() versus SafeMallocBlock() & SafeFreeBlock()\n");

    printf("\n");

    do
    {
        printf("Minimum Test Duration (3-600 seconds): ");
        scanf("%u", &lTestDuration);
    } while (3 > lTestDuration || 600 < lTestDuration);

    printf("\n");

    do
    {
        printf("Memory Allocation Limit (10-2,000 megabytes): ");
        scanf("%u", &lAllocationLimit);
    } while (10 > lAllocationLimit || 2000 < lAllocationLimit);

    lAllocationLimit *= 1000000;

    printf("\n");

    do
    {
        printf("Block Allocation Size (max 100 megabytes): ");
        scanf("%u", &lBlockSize);
    } while (0 == lBlockSize || 100 < lBlockSize);

    lBlockSize *= 1000000;

    printf("\n");

    while (TRUE)
    {
        printf("Pool %d: Object Size (max 1,000,000 bytes): ", lPools + 1);
        scanf("%u", &lPoolObjectSize[lPools]);

        if (0 < lPools && 0 == lPoolObjectSize[lPools])
        {
            break;
        }

        if (1000000 > lPoolObjectSize[lPools])
        {
            lSmallestPoolObjectSize = lSmallestPoolObjectSize > lPoolObjectSize[lPools] ? lPoolObjectSize[lPools] : lSmallestPoolObjectSize;

            lPools++;
        }

        if (0 < lPools)
        {
            printf("Enter Zero to Begin Test\n");
        }
    }

    Destruct();

    printf("\n"
           "STARTED: AllocatePoolMemory() & DestructPool()\n");

	lStartTime = time((time_t *) NULL);

    do
    {
        void * lObject;

        Construct();

        if (!SetPoolMember(&gMemory, motelPoolMember_BlockSize, &lBlockSize))
        {
            return;
        }

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            lObject = NULL;

            if (!AllocatePoolMemory(gMemory, &lObject, lPoolObjectSize[lPool]))
            {
                break;
            }

            lAllocatePoolMemoryTransactions++;
        }

        Destruct();

    } while (lTestDuration > (unsigned long) (lSeconds = difftime(time((time_t *) NULL), lStartTime)));

	lAllocatePoolMemorySeconds += lSeconds;

    lAllocatePoolMemoryTransactions *= 2; // account for freeing the memory

    printf("FINISHED: AllocatePoolMemory() & DestructPool()\n");

    Construct();

    printf("\n"
           "STARTED: SafeMallocBlock() & SafeFreeBlock()\n");

    /*
    ** allocate the object index
    */

    lIndexSize = sizeof(void *) * (lAllocationLimit / lSmallestPoolObjectSize);

    lObjects = (void **) NULL;

    if (!SafeMallocBlock((void **) lObjects, lIndexSize))
    {
        return;
    }

    lStartTime = time((time_t *) NULL);

    do
    {
        lObject = lObjects;

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            * lObject = NULL;

            if (!SafeMallocBlock((void **) lObject, lPoolObjectSize[lPool]))
            {
                break;
            }

            lObject++;

            lSafeMallocTransactions++;
        }

	    while (lObjects < lObject)
	    {
            lObject--;

            if (!SafeFreeBlock((void **) lObject))
            {
                break;
            }
        }

    } while (lTestDuration > (unsigned long) (lSeconds = difftime(time((time_t *) NULL), lStartTime)));

	lSafeMallocSeconds += lSeconds;

    lSafeMallocTransactions *= 2; // account for freeing the memory

    printf("FINISHED: SafeMallocBlock() & SafeFreeBlock()\n");

    /*
    ** deallocate the object index
    */

    if (!SafeFreeBlock((void **) &lObjects))
    {
        return;
    }

    /*
    ** calculate results
    */

	lTotalSeconds = lAllocatePoolMemorySeconds + lSafeMallocSeconds;
    lTotalTransactions = lAllocatePoolMemoryTransactions + lSafeMallocTransactions;

    lNormalizedAllocatePoolMemorySeconds = (lTotalTransactions / lAllocatePoolMemoryTransactions) * lAllocatePoolMemorySeconds;
    lNormalizedSafeMallocSeconds = (lTotalTransactions / lSafeMallocTransactions) * lSafeMallocSeconds;

    lNormalizedTotalSeconds = lNormalizedAllocatePoolMemorySeconds + lNormalizedSafeMallocSeconds;

    /*
    ** display results
    */

	printf("\n");

	printf("AllocatePoolMemory: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lAllocatePoolMemoryTransactions, lAllocatePoolMemorySeconds, lAllocatePoolMemoryTransactions/lAllocatePoolMemorySeconds, 100.0 * lNormalizedAllocatePoolMemorySeconds / lNormalizedTotalSeconds);
 	printf("SafeMallocBlock:              %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lSafeMallocTransactions, lSafeMallocSeconds, lSafeMallocTransactions/lSafeMallocSeconds, 100.0 * lNormalizedSafeMallocSeconds / lNormalizedTotalSeconds);
	printf("                         -----------------------------------------------\n");
	printf("Totals:                  %11.0f t %6.0f s %9.0f t/s %7.3f%%\n\n", lTotalTransactions, lTotalSeconds, lTotalTransactions/lTotalSeconds, 100.0);
}

void IteratedTest3
(
	void
)
{
    unsigned long lAllocationLimit;
    unsigned long lBlockSize;
    unsigned long lPools = 0;
    unsigned long lPool;
    unsigned long lPoolObjectSize[1000];
    unsigned long lSmallestPoolObjectSize = 1000000;
    unsigned long lTestDuration;

    unsigned long lAllocation;

    void ** lObjects;
    void ** lObject;

    size_t lIndexSize;

	time_t lStartTime;

	double lSeconds;

	double lAllocatePoolMemorySeconds = 0;
	double lSafeMallocSeconds = 0;
	double lTotalSeconds;

    double lNormalizedAllocatePoolMemorySeconds;
    double lNormalizedSafeMallocSeconds;
    double lNormalizedTotalSeconds;

    double lAllocatePoolMemoryTransactions = 0;
    double lSafeMallocTransactions = 0;
    double lTotalTransactions;

    printf("\n"
           "Performance comparison of:\n"
           "AllocatePoolMemory() & DeallocatePoolMemory() versus SafeMallocBlock() & SafeFreeBlock()\n");

    printf("\n");

    do
    {
        printf("Minimum Test Duration (3-600 seconds): ");
        scanf("%u", &lTestDuration);
    } while (3 > lTestDuration || 600 < lTestDuration);

    printf("\n");

    do
    {
        printf("Memory Allocation Limit (10-2,000 megabytes): ");
        scanf("%u", &lAllocationLimit);
    } while (10 > lAllocationLimit || 2000 < lAllocationLimit);

    lAllocationLimit *= 1000000;

    printf("\n");

    do
    {
        printf("Block Allocation Size (max 100 megabytes): ");
        scanf("%u", &lBlockSize);
    } while (0 == lBlockSize || 100 < lBlockSize);

    lBlockSize *= 1000000;

    printf("\n");

    while (TRUE)
    {
        printf("Pool %d: Object Size (max 1,000,000 bytes): ", lPools + 1);
        scanf("%u", &lPoolObjectSize[lPools]);

        if (0 < lPools && 0 == lPoolObjectSize[lPools])
        {
            break;
        }

        if (1000000 > lPoolObjectSize[lPools])
        {
            lSmallestPoolObjectSize = lSmallestPoolObjectSize > lPoolObjectSize[lPools] ? lPoolObjectSize[lPools] : lSmallestPoolObjectSize;

            lPools++;
        }

        if (0 < lPools)
        {
            printf("Enter Zero to Begin Test\n");
        }
    }

    Destruct();
    Construct();

    /*
    ** set the alloation size of blocks within a pool
    */

    if (!SetPoolMember(&gMemory, motelPoolMember_BlockSize, &lBlockSize))
    {
        return;
    }

    /*
    ** allocate the object index
    */

    lIndexSize = sizeof(void *) * (lAllocationLimit / lSmallestPoolObjectSize);

    lObjects = (void **) NULL;

    if (!SafeMallocBlock((void **) lObjects, lIndexSize))
    {
        return;
    }

    printf("\n"
           "STARTED: AllocatePoolMemory() & DeallocatePoolMemory()\n");

	lStartTime = time((time_t *) NULL);

    do
    {
        lObject = lObjects;

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            * lObject = NULL;

            if (!AllocatePoolMemory(gMemory, lObject, lPoolObjectSize[lPool]))
            {
                break;
            }

            lObject++;

            lAllocatePoolMemoryTransactions++;
        }

	    while (lObjects < lObject)
	    {
            lObject--;

            if (!DeallocatePoolMemory(gMemory, lObject))
            {
                break;
            }
        }

    } while (lTestDuration > (unsigned long) (lSeconds = difftime(time((time_t *) NULL), lStartTime)));

	lAllocatePoolMemorySeconds += lSeconds;

    lAllocatePoolMemoryTransactions *= 2; // account for freeing the memory

    printf("FINISHED: AllocatePoolMemory() & DeallocatePoolMemory()\n");

    Destruct();
    Construct();

    printf("\n"
           "STARTED: SafeMallocBlock() & SafeFreeBlock()\n");

    lStartTime = time((time_t *) NULL);

    do
    {
        lObject = lObjects;

	    for (lAllocation = 0; lAllocation < lAllocationLimit; lAllocation += lPoolObjectSize[lPool])
	    {
            lPool = rand() % lPools;

            * lObject = NULL;

            if (!SafeMallocBlock((void **) lObject, lPoolObjectSize[lPool]))
            {
                break;
            }

            lObject++;

            lSafeMallocTransactions++;
        }

	    while (lObjects < lObject)
	    {
            lObject--;

            if (!SafeFreeBlock((void **) lObject))
            {
                break;
            }
        }

    } while (lTestDuration > (unsigned long) (lSeconds = difftime(time((time_t *) NULL), lStartTime)));

	lSafeMallocSeconds += lSeconds;

    lSafeMallocTransactions *= 2; // account for freeing the memory

    printf("FINISHED: SafeMallocBlock() & SafeFreeBlock()\n");

    /*
    ** deallocate the object index
    */

    if (!SafeFreeBlock((void **) &lObjects))
    {
        return;
    }

    /*
    ** calculate results
    */

	lTotalSeconds = lAllocatePoolMemorySeconds + lSafeMallocSeconds;
    lTotalTransactions = lAllocatePoolMemoryTransactions + lSafeMallocTransactions;

    lNormalizedAllocatePoolMemorySeconds = (lTotalTransactions / lAllocatePoolMemoryTransactions) * lAllocatePoolMemorySeconds;
    lNormalizedSafeMallocSeconds = (lTotalTransactions / lSafeMallocTransactions) * lSafeMallocSeconds;

    lNormalizedTotalSeconds = lNormalizedAllocatePoolMemorySeconds + lNormalizedSafeMallocSeconds;

    /*
    ** display results
    */

	printf("\n");

	printf("AllocatePoolMemory: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lAllocatePoolMemoryTransactions, lAllocatePoolMemorySeconds, lAllocatePoolMemoryTransactions/lAllocatePoolMemorySeconds, 100.0 * lNormalizedAllocatePoolMemorySeconds / lNormalizedTotalSeconds);
 	printf("SafeMallocBlock:              %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lSafeMallocTransactions, lSafeMallocSeconds, lSafeMallocTransactions/lSafeMallocSeconds, 100.0 * lNormalizedSafeMallocSeconds / lNormalizedTotalSeconds);
	printf("                         -----------------------------------------------\n");
	printf("Totals:                  %11.0f t %6.0f s %9.0f t/s %7.3f%%\n\n", lTotalTransactions, lTotalSeconds, lTotalTransactions/lTotalSeconds, 100.0);
}

void OutputPoolState
(
    void
)
{
	size_t lPools;
	size_t lBlocks;
	size_t lSegments;
	size_t lSegmentsUsed;
	size_t lAllocation;
	size_t lAllocationUsed;

	GetPoolMember(gMemory, motelPoolMember_PoolCount, (void *) &lPools);
	GetPoolMember(gMemory, motelPoolMember_BlockCount, (void *) &lBlocks);
	GetPoolMember(gMemory, motelPoolMember_Segments, (void *) &lSegments);
	GetPoolMember(gMemory, motelPoolMember_SegmentsUsed, (void *) &lSegmentsUsed);
	GetPoolMember(gMemory, motelPoolMember_Bytes, (void *) &lAllocation);
	GetPoolMember(gMemory, motelPoolMember_BytesUsed, (void *) &lAllocationUsed);

	fprintf(gFile, "\n");
	fprintf(gFile, "Pools Created = %zd\n", lPools);
	fprintf(gFile, "Blocks Allocated = %zd\n\n", lBlocks);
	fprintf(gFile, "Segments Allocated = %zd\n", lSegments);
	fprintf(gFile, "Segments Used = %zd\n\n", lSegmentsUsed);
	fprintf(gFile, "Memory Allocated = %zd\n", lAllocation);
	fprintf(gFile, "Memory Used = %zd\n\n", lAllocationUsed);
}

void GenerateInsertData
(
    byte pType,
    motelMemoryObjectHandle pObject
)
{
	static unsigned long lCreationOrdinal = 1;

    int i;

    char lData[512];

	sprintf(lData, "Allocation Ordinal:%08ld", lCreationOrdinal++);

    if (0 == pType)
    {
        struct f * lObject = (struct f *) pObject;

        lObject->type = rand() % 5;

        switch(lObject->type)
        {
        case 0:

            strcpy(lObject->a.a, "0123456789ABCDEF");
            lObject->a.b = 9876543210;
            lObject->a.c = 98765.4321F;
            lObject->a.d = 12345.6789F;
            lObject->a.e = 9.99999999;
            strcpy(lObject->a.f, lData);
            break;

        case 1:

            strcpy(lObject->b.a, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz)!@#$%^&*({}[]:;'<>,.?/~`");
                strcpy(lObject->b.b, lData);
                lObject->b.c = &gLongLong;
                lObject->b.d = (void *)(0xFFFFFFFFLL);
                break;

        case 2:

            strcpy(lObject->c.a, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz)!@#$%^&*({}[]:;'<>,.?/~`");
                break;

        case 3:

            for (i = 0; i < 509; i++)
                {
                    lObject->d.a[i] = (short) (i * sizeof(short));
                }

                break;

        case 4:

            for (i = 0; i < 509; i++)
                {
                    lObject->e.a[i] = (double) (i * sizeof(double));
                }
                
                break;
        }
    }
    else
    {
        struct g * lObject = (struct g *) pObject;

        lObject->a = (short) (lCreationOrdinal % 256);
        strcpy(lObject->b, lData);
    }
}

void OutputNodeData
(
	void
)
{
    struct node * lNode = &gNodes[gNodeIndex];

    fprintf(gFile, "\nAddress: %p\n", lNode);

    if (0 == lNode->type)
    {
        struct f * lObject = lNode->f;

   	    fprintf(gFile, "Type: %d\n", lObject->type);

        switch(lObject->type)
        {
        case 0:

            fprintf(gFile, "char [17]: \"%s\"\n", lObject->a.a);
            fprintf(gFile, "long long: %lld\n", lObject->a.b);
            fprintf(gFile, "float: %f\n", lObject->a.c);
            fprintf(gFile, "float: %f\n", lObject->a.d);
            fprintf(gFile, "double: %f\n", lObject->a.e);
    	    fprintf(gFile, "char [777]: \"%s\"\n", lObject->a.f);
            break;

        case 1:

            fprintf(gFile, "char [7700]: \"%s\"\n", lObject->b.a);
            fprintf(gFile, "char [29]: \"%s\"\n", lObject->b.b);
            fprintf(gFile, "long long *: %p\n", lObject->b.c);
            fprintf(gFile, "void *: %p\n\n", lObject->b.d);
            break;

        case 2:

            fprintf(gFile, "char [509]: \"%s\"\n", lObject->c.a);
            break;

        case 3:

            fprintf(gFile, "short [509]: %d ... %d\n", lObject->d.a[0], lObject->d.a[508]);
            break;

        case 4:

            fprintf(gFile, "double [509]: %f ... %f\n", lObject->e.a[0], lObject->e.a[508]);
            break;
        }
    }
    else
    {
        struct g * lObject = lNode->g;

        fprintf(gFile, "short: %d\n", lObject->a);
        fprintf(gFile, "char[60]: \"%s\"\n", lObject->b);
    }

    fprintf(gFile, "\n");
}
