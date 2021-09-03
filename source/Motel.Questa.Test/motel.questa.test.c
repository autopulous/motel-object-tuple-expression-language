/*----------------------------------------------------------------------------
  Motel Questa Test

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

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

#include "../Motel.Questa/motel.questa.t.h"

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.Questa/motel.questa.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.questa.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.questa.test.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

motelQuestaHandle gQuesta;

char gData[DATA_ELEMENT_SIZE];

char gNodes[THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES][DATA_ELEMENT_SIZE];

unsigned long gNodeCount;

FILE *gFile;

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

            case 'I': // insert
            case 'i':

                InsertNode();
				break;

            case 'S': // select
            case 's':

                SelectNode();
				break;

            case 'F': // fetch
            case 'f':

                FetchNode();
				break;

            case 'U': // update
            case 'u':

                UpdateNode();
				break;

            case 'D': // delete
            case 'd':

                DeleteNode();
				break;

			case '[': // move to head

                HeadNode();
                break;

			case ']': // move to tail

                TailNode();
                break;

            case '>': // move to next

                NextNode();
                break;

			case '<': // move to previous

                PreviousNode();
                break;

            case 'h': // push head

                PushHeadNode();
				break;
        
            case 't': // push tail

                PushTailNode();
				break;
        
            case 'H': // pull head

                PullHeadNode();
                break;

            case 'T': // pull tail

                PullTailNode();
                break;

			case '{': // peek head

                PeekHeadNode();
                break;

			case '}': // peek tail

                PeekTailNode();
                break;

			case ')': // peek next

                PeekNextNode();
                break;

            case '(': // peek previous

                PeekPreviousNode();
                break;

			case 'A': // fetch all nodes head to tail

                FetchHeadToTail();
				break;

			case 'Z': // fetch all nodes tail to head

                FetchTailToHead();
				break;

			case 'a': // peek all nodes head to tail

                PeekHeadToTail();
				break;

			case 'z': // peek all nodes tail to head

                PeekTailToHead();
				break;

			case '0': // pull all nodes head to tail

                PullHeadToTail();
				break;

			case '9': // pull all nodes tail to head

                PullTailToHead();
				break;

            case '1':

                Destruct();
                Construct();

				IteratedTest1();
                break;

			case '2':
                Destruct();
                Construct();

				IteratedTest2();
                break;

			case '!':

                OutputQuestaState();
                break;

            default:

                printf("Valid options are I,S,F,U,D,[,],>,<,h,t,H,T,{,},),(,A,Z,a,z,1,2,!,X,Q,?\n");
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
		   "I - Insert a node at the cursor location\n"
		   "S - Select a node altering the cursor location\n"
		   "F - Fetch the node at the cursor location\n"
		   "U - Update the node at the cursor location\n"
		   "D - Delete the node at the cursor location\n"
		   "\n"
		   "[ - Move the cursor to the head node\n"
		   "] - Move the cursor to the tail node\n"
		   "> - Move the cursor to the next node\n"
		   "< - Move the cursor to the previous node\n"
		   "\n"
		   "h - Push a node to the head\n"
		   "t - Push a node to the tail\n"
		   "H - Pull a node from the head\n"
		   "T - Pull a node from the tail\n"
		   "\n"
		   "{ - Peek at the head node\n"
		   "} - Peek at the tail node\n"
		   ") - Peek at the next node\n"
		   "( - Peek at the previous node\n"
		   "\n"
		   "A - Fetch all nodes in head to tail order\n"
		   "Z - Fetch all nodes in tail to head order\n"
		   "a - Peek all nodes in head to tail order\n"
		   "z - Peek all nodes in tail to head order\n"
		   "0 - Pull all nodes in head to tail order\n"
		   "9 - Pull all nodes in tail to head order\n"
		   "\n"
		   "1 - Iterated performance test\n"
		   "2 - Iterated thorough test\n\n"
		   "\n"
		   "! - Display questa state\n"
		   "\n"
		   "X - Reset questa\n"
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
	unsigned long lNodes = 0;

	if (!ValidateQuesta(gQuesta))
	{
		fprintf(gFile, "Questa self validation failed.\n\n");
		return;
	}
	
	GetQuestaMember(gQuesta, motelQuestaMember_Nodes, (void **) &lNodes);

	if (gNodeCount != lNodes)
	{
		fprintf(gFile, "Questa length disagreement: Application = %d, API = %d\n\n", gNodeCount, lNodes);
	}
}

void Construct
(
    void
)
{
    if (!ConstructQuesta(&gQuesta, (size_t) 0, (size_t) DATA_ELEMENT_SIZE))
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

    if (!DestructQuesta(&gQuesta))
	{
		return;
	}

	gNodeCount = 0;
}

void InsertNode
(
	void
)
{
	GenerateInsertData();

	if (InsertQuestaNode(gQuesta, gData))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void SelectNode
(
	void
)
{
	if (SelectQuestaNode(gQuesta, gData))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void FetchNode
(
	void
)
{
	if (FetchQuestaNode(gQuesta, (void *) gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void UpdateNode
(
	void
)
{
	if (FetchQuestaNode(gQuesta, (void *) gData))
	{
		OutputNodeData();

		GenerateUpdateData();

		if (UpdateQuestaNode(gQuesta, gData))
		{
			if (FetchQuestaNode(gQuesta, (void *) gData))
			{
				OutputNodeData();
			}
		}
	}

	OutputResult();

	Validate();
}

void DeleteNode
(
	void
)
{
	if (FetchQuestaNode(gQuesta, (void *) gData))
	{
		OutputNodeData();

		if (DeleteQuestaNode(gQuesta))
		{
			gNodeCount--;
		}
	}

	OutputResult();

	Validate();
}

void HeadNode
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Head, NULL))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void TailNode
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Tail, NULL))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void NextNode
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Next, NULL))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void PreviousNode
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Previous, NULL))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void PushHeadNode
(
	void
)
{
	GenerateInsertData();

	if (PushHeadQuestaNode(gQuesta, gData))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void PushTailNode
(
	void
)
{
	GenerateInsertData();

	if (PushTailQuestaNode(gQuesta, gData))
	{
		if (FetchQuestaNode(gQuesta, (void *) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
}

void PullHeadNode
(
	void
)
{
	if (PullHeadQuestaNode(gQuesta, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PullTailNode
(
	void
)
{
	if (PullTailQuestaNode(gQuesta, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PeekHeadNode
(
	void
)
{
	if (PeekHeadQuestaNode(gQuesta, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PeekTailNode
(
	void
)
{
	if (PeekTailQuestaNode(gQuesta, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PeekNextNode
(
	void
)
{
	if (PeekNextQuestaNode(gQuesta, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PeekPreviousNode
(
	void
)
{
	if (PeekPreviousQuestaNode(gQuesta, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void FetchHeadToTail
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Head, NULL))
	{
		while (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();

			if (!SetQuestaMember(gQuesta, motelQuestaMember_Next, NULL))
			{
				break;
			}
		}
	}

	OutputResult();

	Validate();
}

void FetchTailToHead
(
	void
)
{
	if (SetQuestaMember(gQuesta, motelQuestaMember_Tail, NULL))
	{
		while (FetchQuestaNode(gQuesta, (void *) gData))
		{
			OutputNodeData();

			if (!SetQuestaMember(gQuesta, motelQuestaMember_Previous, NULL))
			{
				break;
			}
		}
	}

	OutputResult();

	Validate();
}

void PullHeadToTail
(
	void
)
{
	while (PullHeadQuestaNode(gQuesta, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PullTailToHead
(
	void
)
{
	while (PullTailQuestaNode(gQuesta, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
}

void PeekHeadToTail
(
	void
)
{
	if (PeekHeadQuestaNode(gQuesta, gData))
	{
		do
		{
			OutputNodeData();
		}
		while (PeekNextQuestaNode(gQuesta, gData));
	}

	OutputResult();

	Validate();
}

void PeekTailToHead
(
	void
)
{
	if (PeekTailQuestaNode(gQuesta, gData))
	{
		do
		{
			OutputNodeData();
		}
		while (PeekPreviousQuestaNode(gQuesta, gData));
	}

	OutputResult();

	Validate();
}

void IteratedTest1
(
	void
)
{
    unsigned long lNodes = 0;

    unsigned long lCounter;
    unsigned long lSearchCounter;

	time_t lStartTime;

	double lSeconds;

	double lStackSeconds = 0;
	double lUnstackSeconds = 0;
    double lFetchSeconds = 0;
	double lQueueSeconds = 0;
	double lDequeueSeconds = 0;
    double lPeekSeconds = 0;
	double lTotalSeconds;

    double lNormalizedStackSeconds;
    double lNormalizedUnstackSeconds;
    double lNormalizedFetchSeconds;
    double lNormalizedQueueSeconds;
    double lNormalizedDequeueSeconds;
    double lNormalizedPeekSeconds;
    double lNormalizedTotalSeconds;

    double lStackTransactions = 0;
    double lUnstackTransactions = 0;
    double lFetchTransactions = 0;
    double lQueueTransactions = 0;
    double lDequeueTransactions = 0;
    double lPeekTransactions = 0;
    double lTotalTransactions;

	lStartTime = time((time_t *) NULL);

    do
    {
	    for (lCounter = 0; lCounter < PERFORMANCE_TEST_NODES; lCounter++)
	    {
		    GenerateInsertData();

		    StackQuestaNode(gQuesta, gData);

            lNodes++;

            lStackTransactions++;

		    if (0L == (long) lStackTransactions % 500L)
		    {
			    switch (((long) lStackTransactions / 500L) % 4L)
			    {
			    case 0L:
				    printf("-\b");
				    break;
			    case 1L:
				    printf("\\\b");
				    break;
			    case 2L:
				    printf("|\b");
				    break;
			    case 3L:
				    printf("/\b");
				    break;
			    }
		    }
	    }

	    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

	lStackSeconds += lSeconds;

	printf(">");

	lStartTime = time((time_t *) NULL);

    do
    {
        for (lSearchCounter = 0; lSearchCounter < 50; lSearchCounter++)
        {
            SetQuestaMember(gQuesta, motelQuestaMember_Head, NULL);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
		        FetchQuestaNode(gQuesta, gData);

                lFetchTransactions++;

		        if (0L == (long) lFetchTransactions % 500L)
		        {
			        switch (((long) lFetchTransactions / 500L) % 4L)
			        {
			        case 0L:
				        printf(">  \b\b\b");
				        break;
			        case 1L:
				        printf(" > \b\b\b");
				        break;
			        case 2L:
				        printf("  >\b\b\b");
				        break;
			        case 3L:
				        printf(" > \b\b\b");
				        break;
			        }
		        }

                SetQuestaMember(gQuesta, motelQuestaMember_Next, NULL);
	        }

            SetQuestaMember(gQuesta, motelQuestaMember_Tail, NULL);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
		        FetchQuestaNode(gQuesta, gData);

                lFetchTransactions++;

		        if (0 == (long) lFetchTransactions % 500L)
		        {
			        switch (((long) lFetchTransactions / 500L) % 4L)
			        {
			        case 0:
				        printf("<  \b\b\b");
				        break;
			        case 1:
				        printf(" < \b\b\b");
				        break;
			        case 2:
				        printf("  <\b\b\b");
				        break;
			        case 3:
				        printf(" < \b\b\b");
				        break;
			        }
		        }

                SetQuestaMember(gQuesta, motelQuestaMember_Previous, NULL);
	        }
        }

	    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

	lFetchSeconds += lSeconds;

	printf("=  \b\b");

    lStartTime = time((time_t *) NULL);

    for (lCounter = lNodes; 0 != lCounter; lCounter--)
    {
	    UnstackQuestaNode(gQuesta, (void **) gData);

        lUnstackTransactions++;

        lNodes--;

	    if (0 == (long) lUnstackTransactions % 500L)
	    {
		    switch (((long) lUnstackTransactions / 500L) % 4L)
		    {
		    case 0:
			    printf("-\b");
			    break;
		    case 1:
			    printf("\\\b");
			    break;
		    case 2:
			    printf("|\b");
			    break;
		    case 3:
			    printf("/\b");
			    break;
		    }
	    }
    }

    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    lUnstackSeconds += lSeconds;

	printf("<");

	lStartTime = time((time_t *) NULL);

    do
    {
	    for (lCounter = 0; lCounter < PERFORMANCE_TEST_NODES; lCounter++)
	    {
		    GenerateInsertData();

		    QueueQuestaNode(gQuesta, gData);

            lNodes++;

            lQueueTransactions++;

		    if (0 == (long) lQueueTransactions % 500L)
		    {
			    switch (((long) lQueueTransactions / 500L) % 4L)
			    {
			    case 0:
				    printf("-\b");
				    break;
			    case 1:
				    printf("\\\b");
				    break;
			    case 2:
				    printf("|\b");
				    break;
			    case 3:
				    printf("/\b");
				    break;
			    }
		    }
	    }

	    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

	lQueueSeconds += lSeconds;

    lStartTime = time((time_t *) NULL);

    do
    {
        for (lSearchCounter = 0; lSearchCounter < 50; lSearchCounter++)
        {
            PeekHeadQuestaNode(gQuesta, gData);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
                lPeekTransactions++;

		        if (0 == (long) lPeekTransactions % 500L)
		        {
			        switch (((long) lPeekTransactions / 500L) % 4L)
			        {
			        case 0:
				        printf(">  \b\b\b");
				        break;
			        case 1:
				        printf(" > \b\b\b");
				        break;
			        case 2:
				        printf("  >\b\b\b");
				        break;
			        case 3:
				        printf(" > \b\b\b");
				        break;
			        }
		        }

                PeekNextQuestaNode(gQuesta, gData);
	        }

	        PeekTailQuestaNode(gQuesta, gData);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
                lPeekTransactions++;

		        if (0 == (long) lPeekTransactions % 500L)
		        {
			        switch (((long) lPeekTransactions / 500L) % 4L)
			        {
			        case 0:
				        printf("<  \b\b\b");
				        break;
			        case 1:
				        printf(" < \b\b\b");
				        break;
			        case 2:
				        printf("  <\b\b\b");
				        break;
			        case 3:
				        printf(" < \b\b\b");
				        break;
			        }
		        }

                PeekPreviousQuestaNode(gQuesta, gData);
	        }
        }

	    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

    lPeekSeconds += lSeconds;

	printf("=  \b\b");

	printf(">");

    lStartTime = time((time_t *) NULL);

    for (lCounter = lNodes - 1; 0 != lCounter; lCounter--)
    {
	    DequeueQuestaNode(gQuesta, (void **) gData);
        
        lDequeueTransactions++;

        lNodes--;

	    if (0 == (long) lDequeueTransactions % 500L)
	    {
		    switch (((long) lDequeueTransactions / 500L) % 4L)
		    {
		    case 0:
			    printf("-\b");
			    break;
		    case 1:
			    printf("\\\b");
			    break;
		    case 2:
			    printf("|\b");
			    break;
		    case 3:
			    printf("/\b");
			    break;
		    }
	    }
    }

    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    lDequeueSeconds += lSeconds;

	printf("<");

	printf("\n");

	lTotalSeconds = lStackSeconds + lUnstackSeconds + lFetchSeconds + lQueueSeconds + lDequeueSeconds + lPeekSeconds;
    lTotalTransactions = lStackTransactions + lUnstackTransactions + lFetchTransactions + lQueueTransactions + lDequeueTransactions + lPeekTransactions;

    lNormalizedStackSeconds = (lTotalTransactions / lStackTransactions) * lStackSeconds;
    lNormalizedUnstackSeconds = (lTotalTransactions / lUnstackTransactions) * lUnstackSeconds;
    lNormalizedFetchSeconds = (lTotalTransactions / lFetchTransactions) * lFetchSeconds;
    lNormalizedQueueSeconds = (lTotalTransactions / lQueueTransactions) * lQueueSeconds;
    lNormalizedDequeueSeconds = (lTotalTransactions / lDequeueTransactions) * lDequeueSeconds;
    lNormalizedPeekSeconds = (lTotalTransactions / lPeekTransactions) * lPeekSeconds;

    lNormalizedTotalSeconds = lNormalizedStackSeconds + lNormalizedUnstackSeconds + lNormalizedFetchSeconds + lNormalizedQueueSeconds + lNormalizedDequeueSeconds + lNormalizedPeekSeconds;;

	printf("\n\n");

	printf("Stack:   %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lStackTransactions, lStackSeconds, lStackTransactions/lStackSeconds, 100.0 * lNormalizedStackSeconds / lNormalizedTotalSeconds);
	printf("Unstack: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lUnstackTransactions, lUnstackSeconds, lUnstackTransactions/lUnstackSeconds, 100.0 * lNormalizedUnstackSeconds / lNormalizedTotalSeconds);
	printf("Fetch:   %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lFetchTransactions, lFetchSeconds, lFetchTransactions/lFetchSeconds, 100.0 * lNormalizedFetchSeconds / lNormalizedTotalSeconds);
	printf("Queue:   %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lQueueTransactions, lQueueSeconds, lQueueTransactions/lQueueSeconds, 100.0 * lNormalizedQueueSeconds / lNormalizedTotalSeconds);
	printf("Dequeue: %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lDequeueTransactions, lDequeueSeconds, lDequeueTransactions/lDequeueSeconds, 100.0 * lNormalizedDequeueSeconds / lNormalizedTotalSeconds);
	printf("Peek:    %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lPeekTransactions, lPeekSeconds, lPeekTransactions/lPeekSeconds, 100.0 * lNormalizedPeekSeconds / lNormalizedTotalSeconds);
	printf("         -----------------------------------------------\n");
	printf("Totals:  %11.0f t %6.0f s %9.0f t/s %7.3f%%\n\n", lTotalTransactions, lTotalSeconds, lTotalTransactions/lTotalSeconds, 100.0);
}

void IteratedTest2
(
	void
)
{
	unsigned long lIterations;
	unsigned long lIteration;

    unsigned long lCounter;

	printf("\n");
	printf("Iterations: ");
	scanf("%ld", &lIterations);

	for (lIteration = 1; lIterations >= lIteration; lIteration++)
	{
        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
	        GenerateInsertData();

            strcpy(gNodes[lCounter], gData);

	        StackQuestaNode(gQuesta, gData);

            gNodeCount++;
            
	        if (0 == (long) lCounter % 500L)
	        {
		        switch (((long) lCounter / 500L) % 4L)
		        {
		        case 0:
			        printf("-\b");
			        break;
		        case 1:
			        printf("\\\b");
			        break;
		        case 2:
			        printf("|\b");
			        break;
		        case 3:
			        printf("/\b");
			        break;
		        }
	        }
        }

	    printf(">");

        Validate();

        SetQuestaMember(gQuesta, motelQuestaMember_Head, NULL);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            FetchQuestaNode(gQuesta, gData);

            if (strcmp(gNodes[(THOROUGH_TEST_NODES - lCounter) - 1], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

            if (0 == (long) lCounter % 500L)
            {
	            switch (((long) lCounter / 500L) % 4L)
	            {
	            case 0:
		            printf(">  \b\b\b");
		            break;
	            case 1:
		            printf(" > \b\b\b");
		            break;
	            case 2:
		            printf("  >\b\b\b");
		            break;
	            case 3:
		            printf(" > \b\b\b");
		            break;
	            }
            }

            SetQuestaMember(gQuesta, motelQuestaMember_Next, NULL);
        }

        Validate();

        SetQuestaMember(gQuesta, motelQuestaMember_Tail, NULL);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            FetchQuestaNode(gQuesta, gData);

            if (strcmp(gNodes[lCounter], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

            if (0 == (long) lCounter % 500L)
            {
	            switch (((long) lCounter / 500L) % 4L)
	            {
	            case 0:
		            printf("<  \b\b\b");
		            break;
	            case 1:
		            printf(" < \b\b\b");
		            break;
	            case 2:
		            printf("  <\b\b\b");
		            break;
	            case 3:
		            printf(" < \b\b\b");
		            break;
	            }
            }

            SetQuestaMember(gQuesta, motelQuestaMember_Previous, NULL);
        }

        printf("=  \b\b");

        Validate();

        for (lCounter = THOROUGH_TEST_NODES; 0 != lCounter; lCounter--)
        {
	        UnstackQuestaNode(gQuesta, (void **) gData);

            gNodeCount--;
            
            if (strcmp(gNodes[lCounter - 1], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

	        if (0 == (long) lCounter % 500L)
	        {
		        switch (((long) lCounter / 500L) % 4L)
		        {
		        case 0:
			        printf("-\b");
			        break;
		        case 1:
			        printf("\\\b");
			        break;
		        case 2:
			        printf("|\b");
			        break;
		        case 3:
			        printf("/\b");
			        break;
		        }
	        }
        }

	    printf("<");

        Validate();

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
	        GenerateInsertData();

	        QueueQuestaNode(gQuesta, gData);

            strcpy(gNodes[lCounter], gData);

            gNodeCount++;
            
	        if (0 == (long) lCounter % 500L)
	        {
		        switch (((long) lCounter / 500L) % 4L)
		        {
		        case 0:
			        printf("-\b");
			        break;
		        case 1:
			        printf("\\\b");
			        break;
		        case 2:
			        printf("|\b");
			        break;
		        case 3:
			        printf("/\b");
			        break;
		        }
	        }
        }

        Validate();

        PeekHeadQuestaNode(gQuesta, gData);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            if (strcmp(gNodes[lCounter], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

            if (0 == (long) lCounter % 500L)
            {
	            switch (((long) lCounter / 500L) % 4L)
	            {
	            case 0:
		            printf(">  \b\b\b");
		            break;
	            case 1:
		            printf(" > \b\b\b");
		            break;
	            case 2:
		            printf("  >\b\b\b");
		            break;
	            case 3:
		            printf(" > \b\b\b");
		            break;
	            }
            }

            PeekNextQuestaNode(gQuesta, gData);
        }

        Validate();

        PeekTailQuestaNode(gQuesta, gData);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            if (strcmp(gNodes[(THOROUGH_TEST_NODES - lCounter) - 1], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

            if (0 == (long) lCounter % 500L)
            {
	            switch (((long) lCounter / 500L) % 4L)
	            {
	            case 0:
		            printf("<  \b\b\b");
		            break;
	            case 1:
		            printf(" < \b\b\b");
		            break;
	            case 2:
		            printf("  <\b\b\b");
		            break;
	            case 3:
		            printf(" < \b\b\b");
		            break;
	            }
            }

            PeekPreviousQuestaNode(gQuesta, gData);
        }

        printf("=  \b\b");

	    printf(">");

        Validate();

        for (lCounter = 0; THOROUGH_TEST_NODES > lCounter; lCounter++)
        {
	        DequeueQuestaNode(gQuesta, (void **) gData);

            if (strcmp(gNodes[lCounter], gData))
            {
                printf("%06d Data mismatch:\n%s\n%s\n\n", lCounter, gNodes[lCounter], gData);
            }

            gNodeCount--;
            
	        if (0 == (long) lCounter % 500L)
	        {
		        switch (((long) lCounter / 500L) % 4L)
		        {
		        case 0:
			        printf("-\b");
			        break;
		        case 1:
			        printf("\\\b");
			        break;
		        case 2:
			        printf("|\b");
			        break;
		        case 3:
			        printf("/\b");
			        break;
		        }
	        }
        }

	    printf("<");

        Validate();

        printf("\r");
    }

	printf("\n");
}

void OutputQuestaState
(
    void
)
{
	long lQuestaLength;
	size_t lQuestaSize;

	GetQuestaMember(gQuesta, motelQuestaMember_Nodes, (void **) &lQuestaLength);
	GetQuestaMember(gQuesta, motelQuestaMember_Size, (void **) &lQuestaSize);

	fprintf(gFile, "Questa Length = %ld\n", lQuestaLength);
	fprintf(gFile, "Memory Allocated = %zd\n\n", lQuestaSize);
}

void GenerateInsertData
(
    void
)
{
	static unsigned long lCreationOrdinal = 1;

	sprintf(gData, "Insert Ordinal:%08ld", lCreationOrdinal++);
}

void GenerateUpdateData
(
    void
)
{
	static unsigned long lUpdateOrdinal = 1;

	sprintf(gData, "Update Ordinal:%08ld", lUpdateOrdinal++);
}

void OutputNodeData
(
	void
)
{
	fprintf(gFile, "Data: \"%s\"\n\n", gData);
}

void OutputResult
(
	void
)
{
	long lResultCode;

	if (GetQuestaMember(gQuesta, motelQuestaMember_Result, (void **) &lResultCode))
	{
		fprintf(gFile, "Result Code: %ld\n\n", lResultCode);
	}
	else
	{
		fprintf(gFile, "Result Code: (could not be retrieved)\n\n");
	}
}
