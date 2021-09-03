/*----------------------------------------------------------------------------
  Motel Document Test
  
  executable implementation file
  ----------------------------------------------------------------------------
  Copyright 2011-2012 John L. Hart IV. All rights reserved.
 
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

#include "../Motel.Document/motel.document.t.h"

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.Document/motel.document.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.document.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.document.test.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

motelDocumentHandle gDocument;

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

	srand(TEST_SEED);

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
/*
            case 'I': // insert
            case 'i':

                InsertNode();
				break;

            case 'S': // select
            case 's':

                SelectNode();
				break;

            case 'F': // fetch singly

                FetchNode();
				break;

            case 'f': // fetch duplicates

                FetchDuplicatedNodes();
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

                LeastNode();
                break;

			case ']': // move to tail

                GreatestNode();
                break;

            case '>': // move to next

				GreaterNode();
                break;

			case '<': // move to previous

                LesserNode();
                break;

			case '{': // peek head

                PeekLeastNode();
                break;

			case '}': // peek tail

                PeekGreatestNode();
                break;

			case ')': // peek next

                PeekGreaterNode();
                break;

            case '(': // peek previous

                PeekLesserNode();
                break;

			case '^': // display document diagram

                DocumentDiagram();
				break;

            case '#': // display object structure

                DocumentStructure();
				break;

			case 'A': // fetch all objects head to tail

                FetchLeastToGreatest();
				break;

			case 'Z': // fetch all objects tail to head

                FetchGreatestToLeast();
				break;

			case 'a': // peek all objects head to tail

                PeekLeastToGreatest();
				break;

			case 'z': // peek all objects tail to head

                PeekGreatestToLeast();
				break;

            case '1':

                IteratedTest1();
                break;

			case '2':

                IteratedTest2();
                break;
*/
			case '!':

                OutputDocumentState();
                break;

            default:

                printf("Valid options are I,S,F,U,D,[,],>,<,{,},),(,A,Z,a,z,1,2,!,X,Q,?\n");
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
		   "I - Insert a object\n"
		   "S - Select a object altering the cursor location\n"
		   "F - Fetch the object at the cursor location\n"
		   "f - Fetch the objects of equal value at the cursor location\n"
		   "U - Update the object at the cursor location\n"
		   "D - Delete the object at the cursor location\n"
		   "\n"
		   "[ - Move the cursor to the least object\n"
		   "] - Move the cursor to the greatest object\n"
		   "> - Move the cursor to the greater object\n"
		   "< - Move the cursor to the lesser object\n"
		   "\n"
		   "{ - Peek at the least object\n"
		   "} - Peek at the greatest object\n"
		   ") - Peek at the greater object\n"
		   "( - Peek at the lesser object\n"
		   "\n"
		   "^ - Display document diagram\n"
           "# - Display object structure\n"
		   "\n"
		   "A - Fetch all objects in least to greatest order\n"
		   "Z - Fetch all objects in greatest to least order\n"
		   "a - Peek all objects in least to greatest order\n"
		   "z - Peek all objects in greatest to least order\n"
		   "\n"
		   "1 - Iterated performance test\n"
		   "2 - Iterated thorough test\n"
		   "\n"
		   "! - Display document state\n"
		   "\n"
		   "X - Reset document\n"
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
	if (!ValidateDocument(gDocument))
	{
		fprintf(gFile, "Document self validation failed.\n\n");
		return;
	}
}

void Construct
(
    void
)
{
    if (!ConstructDocument(&gDocument, (size_t) 0))
	{
		return;
	}

	Validate();
}

void Destruct
(
    void
)
{
	Validate();

    if (!DestructDocument(&gDocument))
	{
		return;
	}
}

void OutputDocumentState
(
    void
)
{
	size_t lSize;

	GetDocumentMember(gDocument, motelDocumentMember_Size, (void **) &lSize);

	fprintf(gFile, "Memory Allocated = %zd\n\n", lSize);
}
