/*----------------------------------------------------------------------------
  Motel Array Test
  
  executable implementation file
  ----------------------------------------------------------------------------
  Copyright 2011-2012-2012 John L. Hart IV. All rights reserved.
 
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

/*----------------------------------------------------------------------------
  Public interfaces
  ----------------------------------------------------------------------------*/

#include "../Motel.Array/motel.array.i.h"

/*----------------------------------------------------------------------------
  Private macros, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.array.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.array.test.c - Copyright 2011-2012-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

char gData[DATA_ELEMENT_SIZE];

char gNodes[THOROUGH_TEST_NODES > PERFORMANCE_TEST_NODES ? THOROUGH_TEST_NODES : PERFORMANCE_TEST_NODES][DATA_ELEMENT_SIZE];

unsigned long gNodeCount;

FILE *gFile;

motelArrayHandle gArray = (motelArrayHandle) NULL;

/*----------------------------------------------------------------------------
  Main
  ----------------------------------------------------------------------------*/

void main
(
    void
)
{
    int lOption;

    motelArrayHandle lArray1 = (motelArrayHandle) NULL;
    motelArrayHandle lArray2 = (motelArrayHandle) NULL;
    motelArrayHandle lArray3 = (motelArrayHandle) NULL;
    motelArrayHandle lArray4 = (motelArrayHandle) NULL;
    motelArrayHandle lArray5 = (motelArrayHandle) NULL;
    motelArrayHandle lArray6 = (motelArrayHandle) NULL;

    int lIntegers1[] = {1,2,3,4,5,6,7,8,9};
    int lIntegers2[] = {89, 76500, 1111, 9000000, -7, 0, 17};

    lem lLessEqualGreater;

	gFile = stdout;

	ConstructArray(&gArray, sizeof(char), 0, 0, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);
	DestructArray(&gArray);

	ConstructArray(&gArray, sizeof(char), 0, 0, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 3);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 3);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 0, 2, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 3);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 50, 10, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 51, 10, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 50, 10, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 2);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 10, 50, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 10, 50, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 2);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 1, 0, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 3);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 1, 2, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 3);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 2, 77, (nodeComparer) NULL, (motelNodeHandle) "123", 3, 4);
    DumpArray(gArray);
	DestructArray(&gArray);

    ConstructArray(&gArray, sizeof(char), 2, 77, (nodeComparer) NULL, (motelNodeHandle) "123", 4, 4);
    DumpArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 1);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 10);
    AutopulateArray(CATENATE | COPY, gArray, (motelNodeHandle) gArray->tail + gArray->nodeSize, 0, gArray, (motelNodeHandle) gArray->head, 10);

    DumpArray(gArray);

    ValidateArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 5);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 10);
    DumpArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 10);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 10);
    DumpArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 1);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 2);
    DumpArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 5);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 2);
    DumpArray(gArray);

	DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 10, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 11, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 10);
    DumpArray(gArray);

//    PlaceArray(gArray, gArray, 2);
    DumpArray(gArray);

    DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 30, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);

    ConstructArray(&lArray1, sizeof(char), 10, 0, (nodeComparer) NULL, (motelNodeHandle) "1234567890", 10, 10);
    DumpArray(lArray1);

//    PlaceArray(gArray, lArray1, 6);
    DumpArray(gArray);

    SetArrayCursorToNextNode(gArray);
    SetArrayCursorToNextNode(gArray);
    SetArrayCursorToNextNode(gArray);
    DumpArray(gArray);

//    PlaceArray(gArray, lArray1, 4);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 8);
    DumpArray(gArray);

//    PlaceArray(gArray, lArray1, 10);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 15);
    DumpArray(gArray);

//    PlaceArray(gArray, lArray1, 10);
    DumpArray(gArray);

    DestructArray(&gArray);
    ConstructArray(&gArray, sizeof(char), 0, 6, (nodeComparer) NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(gArray);

    ReverseArray(gArray);
    DumpArray(gArray);

	ReverseArray(lArray1);
    DumpArray(lArray1);

	ReverseArray(lArray1);
    DumpArray(lArray1);

//    CopyArray(gArray, lArray1);
    DumpArray(gArray);

    ReverseArray(lArray1);
    DumpArray(lArray1);

//    CatenateArray(gArray, lArray1);
    DumpArray(gArray);

    ReverseArray(gArray);
    DumpArray(gArray);

	ConstructArray(&lArray2, sizeof(char), 9, 0, (nodeComparer) NULL, (motelNodeHandle) "ABCDEFGHI", 10, 9);
    DumpArray(lArray2);

    ReverseArray(lArray2);
    DumpArray(lArray2);

//    CatenateArray(gArray, lArray2);
    DumpArray(gArray);

	ConstructArray(&lArray3, sizeof(char), 1, 0, (nodeComparer) NULL, (motelNodeHandle) "X", 2, 1);
    DumpArray(lArray3);

//    CatenateArray(lArray1, lArray3);
    DumpArray(lArray1);

    ReverseArray(lArray3);
    DumpArray(lArray3);

//    CatenateArray(gArray, lArray3);
    DumpArray(gArray);

    ReverseArray(gArray);
    DumpArray(gArray);

    ConstructArray(&lArray4, sizeof(char), 3, 0, (nodeComparer) NULL, (motelNodeHandle) "{-}", 4, 3);
    DumpArray(lArray4);

    ReverseArray(lArray4);
    DumpArray(lArray4);

    ReverseArray(lArray4);
    DumpArray(lArray4);

    ConstructArray(&lArray5, sizeof(int), 10, 25, IntegerNodeCompare, (motelNodeHandle) lIntegers1, sizeof(lIntegers1), sizeof(lIntegers1) / sizeof(int));
    DumpArray(lArray5);

    ValidateArray(lArray5);

    ReverseArray(lArray5);
    DumpArray(lArray5);

    ConstructArray(&lArray6, sizeof(int), 13, 7, IntegerNodeCompare, (motelNodeHandle) lIntegers2, sizeof(lIntegers2), sizeof(lIntegers2) / sizeof(int));
    DumpArray(lArray6);

    ReverseArray(lArray6);
    DumpArray(lArray6);

//    CatenateArray(lArray6, lArray5);
    DumpArray(lArray6);

//    CopyArray(lArray5, lArray6);
    DumpArray(lArray5);

    ReverseArray(lArray5);
    DumpArray(lArray5);

    DestructArray(&lArray6);
    CloneArray(&lArray6, lArray5);
    DumpArray(lArray6);

    ResetArray(gArray);
    DumpArray(gArray);

//    CatenateArray(gArray, lArray1);
    DumpArray(gArray);

//    CatenateArray(gArray, lArray1);
    DumpArray(gArray);

//    CatenateArray(gArray, lArray1);
    DumpArray(gArray);

	ConstructArray(&lArray1, sizeof(char), 10, 0, NULL, (motelNodeHandle) "123", 4, 3);
    DumpArray(lArray1);

    AppendArrayNode(lArray1, "A");
    DumpArray(lArray1);

    AppendArrayNode(lArray1, "B");
    DumpArray(lArray1);

    AppendArrayNode(lArray1, "C");
    DumpArray(lArray1);

//    ReplaceArray(gArray, lArray1, 12);
    DumpArray(gArray);

    SetArrayCursorToThisNode(gArray, 50);
    DumpArray(gArray);

    CloneArray(&lArray2, gArray);
    DumpArray(lArray2);

    ConstructArray(&lArray3, sizeof(char), 70, 0, NULL, (motelNodeHandle) "ARRAY3:", 8, 7);
    DumpArray(lArray3);

//    CatenateArray(lArray3, gArray);
    DumpArray(lArray3);

    ConstructArray(&lArray4, sizeof(char), 20, 0, NULL, (motelNodeHandle) NULL, 0, 0);
    DumpArray(lArray4);

//    CopyArray(lArray2, lArray4);
    DumpArray(lArray2);

//    CopyArray(lArray1, lArray3);
    DumpArray(lArray1);

//    CatenateArray(lArray3, lArray4);
    DumpArray(lArray3);

//    CatenateArray(lArray4, lArray3);
    DumpArray(lArray4);

    DestructArray(&lArray6);
	DestructArray(&lArray5);
	DestructArray(&lArray4);
	DestructArray(&lArray3);
	DestructArray(&lArray2);
	DestructArray(&lArray1);
    DestructArray(&gArray);

    ConstructArray(&lArray1, sizeof(char), 70, 0, CharacterNodeCompare, (motelNodeHandle) "ARRAY", 6, 5);
    DumpArray(lArray1);

    CloneArray(&lArray2, lArray1);
    DumpArray(lArray2);

    CompareArrays(&lLessEqualGreater, lArray1, lArray2);
    CompareArrays(&lLessEqualGreater, lArray2, lArray1);

//    CatenateArray(lArray1, lArray2);

    CompareArrays(&lLessEqualGreater, lArray1, lArray2);
    CompareArrays(&lLessEqualGreater, lArray2, lArray1);

	DestructArray(&lArray2);
	DestructArray(&lArray1);

    do
    {
		printf("Option: ");

//		do
		{
			lOption = fgetc(stdin);
		}
//		while (!IsPrintable(lOption)); /* eat carriage returns (etc) */

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

                OutputState();
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
		   "I - InsertArrayNode a node at the cursor location\n"
		   "S - SetArrayCursorToMatchingNode a node altering the cursor location\n"
		   "F - Fetch the node at the cursor location\n"
		   "U - UpdateArrayNode the node at the cursor location\n"
		   "D - DeleteArrayNode the node at the cursor location\n"
		   "\n"
		   "[ - Move the cursor to the head node\n"
		   "] - Move the cursor to the tail node\n"
		   "> - Move the cursor to the next node\n"
		   "< - Move the cursor to the previous node\n"
		   "\n"
		   "h - Push a node to the head\n"
		   "t - Push a node to the tail\n"
		   "H - PullArrayNode a node from the head\n"
		   "T - PullArrayNode a node from the tail\n"
		   "\n"
		   "{ - PeekArrayNode at the head node\n"
		   "} - PeekArrayNode at the tail node\n"
		   ") - PeekArrayNode at the next node\n"
		   "( - PeekArrayNode at the previous node\n"
		   "\n"
		   "A - Fetch all nodes in head to tail order\n"
		   "Z - Fetch all nodes in tail to head order\n"
		   "a - PeekArrayNode all nodes in head to tail order\n"
		   "z - PeekArrayNode all nodes in tail to head order\n"
		   "0 - PullArrayNode all nodes in head to tail order\n"
		   "9 - PullArrayNode all nodes in tail to head order\n"
		   "\n"
		   "1 - Iterated performance test\n"
		   "2 - Iterated thorough test\n\n"
		   "\n"
		   "! - Display array state\n"
		   "\n"
		   "X - ResetArray array\n"
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
    /*
	unsigned long lNodes = 0;

	if (!ValidateArray(gArray))
	{
		fprintf(gFile, "Array self validation failed.\n\n");
		return;
	}
	
	GetlArrayMember(gArray, motelArrayMember_Nodes, (motelArrayMemberValue *) &lNodes);

	if (gNodeCount != lNodes)
	{
		fprintf(gFile, "Array length disagreement: Application = %d, API = %d\n\n", gNodeCount, lNodes);
	}
    */
}

void Construct
(
    void
)
{
    /*
    if (!MotelArrayConstructArrayMotelArray(&gArray, (size_t) 0, (size_t) DATA_ELEMENT_SIZE))
	{
		return;
	}

	gNodeCount = 0;

	Validate();
    */
}

void Destruct
(
    void
)
{
    /*
	Validate();

    if (!MotelArrayDestructArrayMotelArray(&gArray))
	{
		return;
	}

	gNodeCount = 0;
    */
}

void InsertNode
(
	void
)
{
    /*
	GenerateInsertData();

	if (MotelArrayInsert(gArray, gData))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void SelectNode
(
	void
)
{
    /*
	if (MotelArraySelect(gArray, gData))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void FetchNode
(
	void
)
{
    /*
	if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void UpdateNode
(
	void
)
{
    /*
	if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
	{
		OutputNodeData();

		GenerateUpdateData();

		if (MotelArrayUpdate(gArray, gData))
		{
			if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
			{
				OutputNodeData();
			}
		}
	}

	OutputResult();

	Validate();
    */
}

void DeleteNode
(
	void
)
{
    /*
	if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
	{
		OutputNodeData();

		if (MotelArrayDelete(gArray))
		{
			gNodeCount--;
		}
	}

	OutputResult();

	Validate();
    */
}

void HeadNode
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Head, NULL))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void TailNode
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Tail, NULL))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void NextNode
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Next, NULL))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void PreviousNode
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Previous, NULL))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void PushHeadNode
(
	void
)
{
    /*
	GenerateInsertData();

	if (MotelArrayPushHead(gArray, gData))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void PushTailNode
(
	void
)
{
    /*
	GenerateInsertData();

	if (MotelArrayPushTail(gArray, gData))
	{
		if (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			gNodeCount++;

			OutputNodeData();
		}
	}

	OutputResult();

	Validate();
    */
}

void PullHeadNode
(
	void
)
{
    /*
	if (MotelArrayPullHead(gArray, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PullTailNode
(
	void
)
{
    /*
	if (MotelArrayPullTail(gArray, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PeekHeadNode
(
	void
)
{
    /*
	if (MotelArrayPeekHead(gArray, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PeekTailNode
(
	void
)
{
    /*
	if (MotelArrayPeekTail(gArray, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PeekNextNode
(
	void
)
{
    /*
	if (MotelArrayPeekNext(gArray, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PeekPreviousNode
(
	void
)
{
    /*
	if (MotelArrayPeekPrevious(gArray, gData))
	{
		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void FetchHeadToTail
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Head, NULL))
	{
		while (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();

			if (!SetArrayMember(gArray, motelArrayMember_Next, NULL))
			{
				break;
			}
		}
	}

	OutputResult();

	Validate();
    */
}

void FetchTailToHead
(
	void
)
{
    /*
	if (SetArrayMember(gArray, motelArrayMember_Tail, NULL))
	{
		while (MotelArrayFetch(gArray, (motelArrayDataHandle) gData))
		{
			OutputNodeData();

			if (!SetArrayMember(gArray, motelArrayMember_Previous, NULL))
			{
				break;
			}
		}
	}

	OutputResult();

	Validate();
    */
}

void PullHeadToTail
(
	void
)
{
    /*
	while (MotelArrayPullHead(gArray, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PullTailToHead
(
	void
)
{
    /*
	while (MotelArrayPullTail(gArray, gData))
	{
		gNodeCount--;

		OutputNodeData();
	}

	OutputResult();

	Validate();
    */
}

void PeekHeadToTail
(
	void
)
{
    /*
	if (MotelArrayPeekHead(gArray, gData))
	{
		do
		{
			OutputNodeData();
		}
		while (MotelArrayPeekNext(gArray, gData));
	}

	OutputResult();

	Validate();
    */
}

void PeekTailToHead
(
	void
)
{
    /*
	if (MotelArrayPeekTail(gArray, gData))
	{
		do
		{
			OutputNodeData();
		}
		while (MotelArrayPeekPrevious(gArray, gData));
	}

	OutputResult();

	Validate();
    */
}

void IteratedTest1
(
	void
)
{
    /*
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

		    MotelArrayStack(gArray, gData);

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
            SetArrayMember(gArray, motelArrayMember_Head, NULL);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
		        MotelArrayFetch(gArray, gData);

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

                SetArrayMember(gArray, motelArrayMember_Next, NULL);
	        }

            SetArrayMember(gArray, motelArrayMember_Tail, NULL);

	        for (lCounter = 0; lCounter < lNodes; lCounter++)
	        {
		        MotelArrayFetch(gArray, gData);

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

                SetArrayMember(gArray, motelArrayMember_Previous, NULL);
	        }
        }

	    lSeconds = difftime(time((time_t *) NULL), lStartTime);

    } while (TEST_DURATION > lSeconds);

	lFetchSeconds += lSeconds;

	printf("=  \b\b");

    lStartTime = time((time_t *) NULL);

    for (lCounter = lNodes; 0 != lCounter; lCounter--)
    {
	    MotelArrayUnstack(gArray, (motelArrayMemberValue *) gData);

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

		    MotelArrayQueue(gArray, gData);

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
            MotelArrayPeekHead(gArray, gData);

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

                MotelArrayPeekNext(gArray, gData);
	        }

	        MotelArrayPeekTail(gArray, gData);

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

                MotelArrayPeekPrevious(gArray, gData);
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
	    MotelArrayDequeue(gArray, (motelArrayMemberValue *) gData);
        
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
	printf("PeekArrayNode:    %11.0f t %6.0f s %9.0f t/s %7.3f%%\n", lPeekTransactions, lPeekSeconds, lPeekTransactions/lPeekSeconds, 100.0 * lNormalizedPeekSeconds / lNormalizedTotalSeconds);
	printf("         -----------------------------------------------\n");
	printf("Totals:  %11.0f t %6.0f s %9.0f t/s %7.3f%%\n\n", lTotalTransactions, lTotalSeconds, lTotalTransactions/lTotalSeconds, 100.0);
    */
}

void IteratedTest2
(
	void
)
{
    /*
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

	        MotelArrayStack(gArray, gData);

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

        SetArrayMember(gArray, motelArrayMember_Head, NULL);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            MotelArrayFetch(gArray, gData);

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

            SetArrayMember(gArray, motelArrayMember_Next, NULL);
        }

        Validate();

        SetArrayMember(gArray, motelArrayMember_Tail, NULL);

        for (lCounter = 0; lCounter < THOROUGH_TEST_NODES; lCounter++)
        {
            MotelArrayFetch(gArray, gData);

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

            SetArrayMember(gArray, motelArrayMember_Previous, NULL);
        }

        printf("=  \b\b");

        Validate();

        for (lCounter = THOROUGH_TEST_NODES; 0 != lCounter; lCounter--)
        {
	        MotelArrayUnstack(gArray, (motelArrayMemberValue *) gData);

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

	        MotelArrayQueue(gArray, gData);

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

        MotelArrayPeekHead(gArray, gData);

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

            MotelArrayPeekNext(gArray, gData);
        }

        Validate();

        MotelArrayPeekTail(gArray, gData);

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

            MotelArrayPeekPrevious(gArray, gData);
        }

        printf("=  \b\b");

	    printf(">");

        Validate();

        for (lCounter = 0; THOROUGH_TEST_NODES > lCounter; lCounter++)
        {
	        MotelArrayDequeue(gArray, (motelArrayMemberValue *) gData);

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
    */
}

void OutputState
(
    void
)
{
    /*
	long lArrayLength;
	size_t lArraySize;

	GetlArrayMember(gArray, motelArrayMember_Nodes, (motelArrayMemberValue *) &lArrayLength);
	GetlArrayMember(gArray, motelArrayMember_Size, (motelArrayMemberValue *) &lArraySize);

	fprintf(gFile, "Array Length = %ld\n", lArrayLength);
	fprintf(gFile, "Memory Allocated = %ld\n\n", lArraySize);
    */
}

void GenerateInsertData
(
    void
)
{
    /*
	static unsigned long lCreationOrdinal = 1;

	sprintf(gData, "InsertArrayNode Ordinal:%08ld", lCreationOrdinal++);
    */
}

void GenerateUpdateData
(
    void
)
{
    /*
	static unsigned long lUpdateOrdinal = 1;

	sprintf(gData, "UpdateArrayNode Ordinal:%08ld", lUpdateOrdinal++);
    */
}

void OutputNodeData
(
	void
)
{
    /*
	fprintf(gFile, "Data: \"%s\"\n\n", gData);
    */
}

void OutputResult
(
	void
)
{
    /*
	long lResultCode;

	if (GetlArrayMember(gArray, motelArrayMember_Result, (motelArrayMemberValue *) &lResultCode))
	{
		fprintf(gFile, "Result Code: %ld\n\n", lResultCode);
	}
	else
	{
		fprintf(gFile, "Result Code: (could not be retrieved)\n\n", lResultCode);
	}
    */
}

boolean (CALLING_CONVENTION CharacterNodeCompare)
(
    lem * pLessEqualGreater,
    motelNodeHandle pNode1,
    motelNodeHandle pNode2
)
{
    char * lCharacter1 = (char *) pNode1;
    char * lCharacter2 = (char *) pNode2;

    if (*lCharacter1 < *lCharacter2)
    {
        * pLessEqualGreater = LESS_THAN;

        return (TRUE);
    }

    if (*lCharacter1 > *lCharacter2)
    {
        * pLessEqualGreater = MORE_THAN;

        return (TRUE);
    }

    * pLessEqualGreater = EQUAL_TO;

    return (TRUE);
}

boolean (CALLING_CONVENTION IntegerNodeCompare)
(
    lem * pLessEqualGreater,
    motelNodeHandle pNode1,
    motelNodeHandle pNode2
)
{
    int * lInteger1 = (int *) pNode1;
    int * lInteger2 = (int *) pNode2;

    if (*lInteger1 < *lInteger2)
    {
        * pLessEqualGreater = LESS_THAN;

        return (TRUE);
    }

    if (*lInteger1 > *lInteger2)
    {
        * pLessEqualGreater = MORE_THAN;

        return (TRUE);
    }

    * pLessEqualGreater = EQUAL_TO;

    return (TRUE);
}