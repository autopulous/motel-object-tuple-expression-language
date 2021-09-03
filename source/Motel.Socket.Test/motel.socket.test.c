/*----------------------------------------------------------------------------
  Motel Socket Test

  executable implementation file
  ---------------------------------------------------------------------------- 
  Copyright 2010-2012 John L. Hart IV. All rights reserved.
 
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

#include <stdio.h>

/*----------------------------------------------------------------------------
  Public data types
  ----------------------------------------------------------------------------*/

#include "motel.compilation.t.h"
#include "motel.types.t.h"
#include "motel.results.t.h"

#include "motel.memory.i.h"

#include "motel.string.i.h"

#include "motel.buffer.t.h"

#include "motel.socket.t.h"

#include "motel.uuid.t.h"
#include "motel.uuid.i.h"

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "motel.string.t.h"
#include "motel.string.i.h"

#include "motel.buffer.i.h"

#include "motel.socket.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.socket.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.socket.test.c - Copyright 2010-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

motelSocketHandle gClientSocket;
motelSocketHandle gServerSocket;

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

	char lString[128];

	/*
    ** for some reason this was a convenient place to test CompareStrings()
    */

    {
        lem lLessEqualMore;
        
        lLessEqualMore = CompareStrings((const char *) NULL, (const char *) NULL);    //  0 EQUAL_TO

        lLessEqualMore = CompareStrings("", (const char *) NULL);      //  0 EQUAL_TO
        lLessEqualMore = CompareStrings((const char *) NULL, "");      //  0 EQUAL_TO

        lLessEqualMore = CompareStrings("", "");        //  0 EQUAL_TO

        lLessEqualMore = CompareStrings("A", (const char *) NULL);     //  1 MORE_THAN
        lLessEqualMore = CompareStrings("A", "");       //  1 MORE_THAN
        lLessEqualMore = CompareStrings("1", (const char *) NULL);     //  1 MORE_THAN
        lLessEqualMore = CompareStrings("1", "");       //  1 MORE_THAN
        lLessEqualMore = CompareStrings("A", "1");      //  1 MORE_THAN

        lLessEqualMore = CompareStrings((const char *) NULL, "A");     // -1 LESS_THAN
        lLessEqualMore = CompareStrings("", "A");       // -1 LESS_THAN
        lLessEqualMore = CompareStrings((const char *) NULL, "1");     // -1 LESS_THAN
        lLessEqualMore = CompareStrings("", "1");       // -1 LESS_THAN
        lLessEqualMore = CompareStrings("1", "A");      // -1 LESS_THAN

        lLessEqualMore = CompareStrings("abc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareStrings("Abc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABC", "");     //  1 MORE_THAN

        lLessEqualMore = CompareStrings("", "abc");     // -1 LESS_THAN
        lLessEqualMore = CompareStrings("", "Abc");     // -1 LESS_THAN
        lLessEqualMore = CompareStrings("", "ABc");     // -1 LESS_THAN
        lLessEqualMore = CompareStrings("", "ABC");     // -1 LESS_THAN

        lLessEqualMore = CompareStrings("abc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("Abc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABC", "A");    //  1 MORE_THAN

        lLessEqualMore = CompareStrings("A", "abc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("A", "Abc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("A", "ABc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("A", "ABC");    // -1 LESS_THAN

        lLessEqualMore = CompareStrings("abc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("Abc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareStrings("ABC", "1");    //  1 MORE_THAN

        lLessEqualMore = CompareStrings("1", "abc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("1", "Abc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("1", "ABc");    // -1 LESS_THAN
        lLessEqualMore = CompareStrings("1", "ABC");    // -1 LESS_THAN

        lLessEqualMore = CompareStrings("abc", "ABC");  //  1 EQUAL_TO
        lLessEqualMore = CompareStrings("Abc", "ABC");  //  1 EQUAL_TO
        lLessEqualMore = CompareStrings("ABc", "ABC");  //  1 EQUAL_TO
        lLessEqualMore = CompareStrings("ABC", "ABC");  //  0 EQUAL_TO
        lLessEqualMore = CompareStrings("ABC", "ABc");  // -1 EQUAL_TO
        lLessEqualMore = CompareStrings("ABC", "Abc");  // -1 EQUAL_TO
        lLessEqualMore = CompareStrings("ABC", "abc");  // -1 EQUAL_TO

        lLessEqualMore = CompareStrings("ABC", "abc");  // -1 EQUAL_TO
        lLessEqualMore = CompareStrings("aBC", "abc");  // -1 EQUAL_TO
        lLessEqualMore = CompareStrings("abC", "abc");  // -1 EQUAL_TO
        lLessEqualMore = CompareStrings("abc", "abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareStrings("abc", "abC");  //  1 EQUAL_TO
        lLessEqualMore = CompareStrings("abc", "aBC");  //  1 EQUAL_TO
        lLessEqualMore = CompareStrings("abc", "ABC");  //  1 EQUAL_TO
    }

    /*
    ** for some reason this was a convenient place to test CompareiStrings()
    */

    {
        lem lLessEqualMore;
        
        lLessEqualMore = CompareiStrings((const char *) NULL, (const char *) NULL);    //  0 EQUAL_TO

        lLessEqualMore = CompareiStrings("", (const char *) NULL);      //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings((const char *) NULL, "");      //  0 EQUAL_TO

        lLessEqualMore = CompareiStrings("", "");        //  0 EQUAL_TO

        lLessEqualMore = CompareiStrings("A", (const char *) NULL);     //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("A", "");       //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("1", (const char *) NULL);     //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("1", "");       //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("A", "1");      //  1 MORE_THAN

        lLessEqualMore = CompareiStrings((const char *) NULL, "A");     // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("", "A");       // -1 LESS_THAN
        lLessEqualMore = CompareiStrings((const char *) NULL, "1");     // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("", "1");       // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("1", "A");      // -1 LESS_THAN

        lLessEqualMore = CompareiStrings("abc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("Abc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABc", "");     //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABC", "");     //  1 MORE_THAN

        lLessEqualMore = CompareiStrings("", "abc");     // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("", "Abc");     // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("", "ABc");     // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("", "ABC");     // -1 LESS_THAN

        lLessEqualMore = CompareiStrings("abc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("Abc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABc", "A");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABC", "A");    //  1 MORE_THAN

        lLessEqualMore = CompareiStrings("A", "abc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("A", "Abc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("A", "ABc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("A", "ABC");    // -1 LESS_THAN

        lLessEqualMore = CompareiStrings("abc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("Abc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABc", "1");    //  1 MORE_THAN
        lLessEqualMore = CompareiStrings("ABC", "1");    //  1 MORE_THAN

        lLessEqualMore = CompareiStrings("1", "abc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("1", "Abc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("1", "ABc");    // -1 LESS_THAN
        lLessEqualMore = CompareiStrings("1", "ABC");    // -1 LESS_THAN

        lLessEqualMore = CompareiStrings("abc", "ABC");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("Abc", "ABC");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABc", "ABC");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABC", "ABC");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABC", "ABc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABC", "Abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABC", "abc");  //  0 EQUAL_TO

        lLessEqualMore = CompareiStrings("abc", "abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("Abc", "abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("ABc", "abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("abc", "abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("abc", "ABc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("abc", "Abc");  //  0 EQUAL_TO
        lLessEqualMore = CompareiStrings("abc", "abc");  //  0 EQUAL_TO
    }

    /*
    ** for some reason this was a convenient place to test GetMacAddresss()
    */

    {
		motelMacAddress lMacAddress;
		GetMacAddresss(&lMacAddress, sizeof(lMacAddress));
		MotelSocketMacAddresssToString(lMacAddress, lString);
		printf("%s\n", lString);
	}

	{
        lem lLessEqualMore;
        
		loop
		{
			static int i = 0;

			motelUuidHandle lUuid1 = (motelUuidHandle) NULL;
			motelUuidHandle lUuid2 = (motelUuidHandle) NULL;

			ConstructUuid(&lUuid1);
			ConstructUuid(&lUuid2);

			escape(i++ == 500);

			GenerateUuid(lUuid1);

		    ToStringUuid(lUuid1, lString, sizeof(lString));
		    printf("%s\n", lString);

			GenerateUuid(lUuid2);

		    ToStringUuid(lUuid2, lString, sizeof(lString));
		    printf("%s\n", lString);

			lLessEqualMore = CompareUuids((const motelUuidHandle) NULL, (const motelUuidHandle) NULL);
			lLessEqualMore = CompareUuids(lUuid1, (const motelUuidHandle) NULL);
			lLessEqualMore = CompareUuids((const motelUuidHandle) NULL, lUuid2);

			lLessEqualMore = CompareUuids(lUuid1, lUuid1);
			lLessEqualMore = CompareUuids(lUuid2, lUuid2);
			lLessEqualMore = CompareUuids(lUuid1, lUuid2);
			lLessEqualMore = CompareUuids(lUuid2, lUuid1);

			DestructUuid(&lUuid2);
			DestructUuid(&lUuid1);
		}
	}
	
	gFile = stdout;

	srand(TEST_SEED);

	ConstructSockets();

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

                DestructSockets();
				break;

            case 'X':
            case 'x':

                DestructSockets();
				ConstructSockets();
				break;

            case '1': // send request

                SendSocketRequest();
				break;

            case '2': // receive request

                ReceiveSocketRequest();
				break;

            case '3': // send response

                SendSocketResponse();
				break;

            case '4': // receive response

                ReceiveSocketResponse();
				break;
/*
            case '5':

                IteratedTest();
                break;
*/
			case '!':

                OutputSocketStates();
                break;

            default:

                printf("Valid options are 1,2,3,4,5,!,X,Q,?\n");
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
		   "1 - Send a request\n"
		   "2 - Receive a request\n"
		   "3 - Send a response\n"
		   "4 - Receive a response\n"
		   "\n"
		   "5 - Iterated test\n"
		   "\n"
		   "! - Display socket state\n"
		   "\n"
		   "X - Reset socket\n"
		   "\n"
		   "Q - Quit\n"
		   "? - Display this option list\n"
		   "\n");
}

void ValidateSockets
(
	void
)
{
	if (!ValidateSocket(gClientSocket))
	{
		fprintf(gFile, "Client socket self validation failed.\n\n");
		return;
	}

    if (!ValidateSocket(gServerSocket))
	{
		fprintf(gFile, "Server socket self validation failed.\n\n");
		return;
	}
}

void ConstructSockets
(
    void
)
{
    if (!ConstructSocket(&gServerSocket, NULL, TEST_PORT))
	{
		return;
	}

    if (!ConstructSocket(&gClientSocket, TEST_HOST, TEST_PORT))
	{
		return;
	}

	ValidateSockets();
}

void DestructSockets
(
    void
)
{
	ValidateSockets();

    if (!DestructSocket(&gServerSocket))
	{
		return;
	}

    if (!DestructSocket(&gClientSocket))
	{
		return;
	}
}

void SendSocketRequest
(
    void
)
{
    char lMessage[] = 

        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "
        "Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage ""Some Garbage "

        ;

    motelBufferHandle lBuffer = (motelBufferHandle) NULL;

    if (!ConstructBuffer(&lBuffer, (byte *) lMessage, sizeof(lMessage) - 1))
    {
        return;
    }

    if (!PushSocketBytes(gClientSocket, lBuffer))
    {
        return;
    }

    if (!DestructBuffer(&lBuffer))
    {
        return;
    }

    fprintf(gFile, "Sent to server: %s\n\n", lMessage);

    ValidateSockets();
}

void ReceiveSocketRequest
(
    void
)
{
    char lMessage[50000];

    motelBufferHandle lBuffer = (motelBufferHandle) NULL;

    if (!ConstructBuffer(&lBuffer, (byte *) lMessage, sizeof(lMessage)))
    {
        return;
    }

    if (!PullSocketBytes(gServerSocket, lBuffer))
    {
        return;
    }

    if (!DestructBuffer(&lBuffer))
    {
        return;
    }

    fprintf(gFile, "Received from client: %s\n\n", lMessage);

  	ValidateSockets();
}

void SendSocketResponse
(
    void
)
{
    char lMessage[] = "Hey, I don't want your garbage!";

    motelBufferHandle lBuffer = (motelBufferHandle) NULL;

    if (!ConstructBuffer(&lBuffer, (byte *) lMessage, sizeof(lMessage)))
    {
        return;
    }

    if (!PushSocketBytes(gServerSocket, lBuffer))
    {
        return;
    }    

    if (!DestructBuffer(&lBuffer))
    {
        return;
    }

    fprintf(gFile, "Sent to client: %s\n\n", lMessage);

  	ValidateSockets();
}

void ReceiveSocketResponse
(
    void
)
{
    char lMessage[50000];

    motelBufferHandle lBuffer = (motelBufferHandle) NULL;

    if (!ConstructBuffer(&lBuffer, (byte *) lMessage, sizeof(lMessage)))
    {
        return;
    }

    if (!PullSocketBytes(gClientSocket, lBuffer))
    {
        return;
    }

    if (!DestructBuffer(&lBuffer))
    {
        return;
    }

    fprintf(gFile, "Received from server: %s\n\n", lMessage);

  	ValidateSockets();
}

void OutputSocketStates
(
    void
)
{
    int lSocketErrorCode;

    char lHost[MOTEL_HOST_SIZE];
    char lHostIP[MOTEL_HOST_SIZE];
    char lPort[MOTEL_PORT_SIZE];
    int lTcpSegmentSize;

    GetSocketMember(gServerSocket, motelSocketMember_SocketErrorNumber, (void *) & lSocketErrorCode);
    GetSocketMember(gServerSocket, motelSocketMember_Port, (void *) & lPort);
    GetSocketMember(gServerSocket, motelSocketMember_TcpSegmentSize, (void *) & lTcpSegmentSize);

    fprintf(gFile, "Server Socket:\n\n");
    fprintf(gFile, "Socket Error Code = %d\n\n", lSocketErrorCode);
    fprintf(gFile, "Listening Port = %s\n", lPort);
    fprintf(gFile, "TCP Segment Size = %d\n\n", lTcpSegmentSize);

    GetSocketMember(gClientSocket, motelSocketMember_SocketErrorNumber, (void *) & lSocketErrorCode);
    GetSocketMember(gClientSocket, motelSocketMember_Host, (void *) & lHost);
    GetSocketMember(gClientSocket, motelSocketMember_HostIP, (void *) & lHostIP);
    GetSocketMember(gClientSocket, motelSocketMember_Port, (void *) & lPort);
    GetSocketMember(gClientSocket, motelSocketMember_TcpSegmentSize, (void *) & lTcpSegmentSize);

    fprintf(gFile, "Client Socket:\n\n");
    fprintf(gFile, "Socket Error Code = %d\n\n", lSocketErrorCode);
    fprintf(gFile, "Device requested = %s:%s\n", lHost, lPort);
    fprintf(gFile, "Device resolved as = %s:%s\n\n", lHostIP, lPort);
    fprintf(gFile, "TCP Segment Size = %d\n\n", lTcpSegmentSize);
}

