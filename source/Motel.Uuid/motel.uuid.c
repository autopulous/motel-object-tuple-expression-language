/*----------------------------------------------------------------------------
  Motel UUID
  
  library implementation file
  ----------------------------------------------------------------------------
  Copyright 2012 John L. Hart IV. All rights reserved.
 
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

#include "motel.uuid.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.uuid.c - Copyright 2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

static boolean gInitialized = FALSE;

static unsigned long long gPreviousTick = 0;

static unsigned short gUuidSequence = 0;
static unsigned short gUuidSequenceWrapAround = 0;

static motelMacAddress gMacAddress = {0, 0, 0, 0, 0, 0};

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructUuid
(
    motelUuidHandle * pUuid
)
{
	/*
	** allocate the UUID control structure
	*/

    if (!SafeMallocBlock((void **) pUuid, sizeof(motelUuid)))
	{
		return (FALSE);
	}

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ResetUuid
(
    motelUuidHandle pUuid
)
{
    /*
    ** there is no UUID
    */

	if (NULL == pUuid)
	{
		return (FALSE);
	}

	/*
	** clear the UUID value
	*/

	memset(pUuid, 0, sizeof(motelUuid));

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructUuid
(
    motelUuidHandle * pUuid
)
{
    /*
    ** there is no UUID
    */

    if (NULL == pUuid || NULL == * pUuid)
	{
		return (FALSE);
	}

	/*
	** release the UUID control structure
	*/

    SafeFreeBlock((void **) pUuid);

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GenerateUuid
(
    motelUuidHandle pUuid
)
{

// parameter validation

{
	if (NULL == pUuid)
	{
		return (FALSE);
	}
}

// function initialization

{
	if (!gInitialized)
	{
		srand((unsigned int) time((time_t *) NULL));
		gUuidSequence = gUuidSequenceWrapAround = (unsigned short) rand();

		GetMacAddresss(&gMacAddress, sizeof(gMacAddress));

		gInitialized = TRUE;
	}
}

// function body

{
    bits64 lTick;

#if defined _WIN32 || defined _WIN64

    // a 64-bit value representing the number of 100ns "ticks" since January 1, 1601 (UTC)

	GetSystemTimeAsFileTime((FILETIME *) &lTick);

	if (gPreviousTick == lTick)
	{
		gUuidSequence++;

		if (gUuidSequenceWrapAround == gUuidSequence)
		{
			// we've just used up all of the sequence numbers for
			// this "tick" therefore busy-wait for the next "tick"

			do
			{
				GetSystemTimeAsFileTime((FILETIME *) &lTick);
			} while (gPreviousTick == lTick);
		}
	}
	else
	{
		gUuidSequenceWrapAround = gUuidSequence;
	}

	gPreviousTick = lTick;

	// UUIDs use time in 100ns "ticks" since October 15, 1582
	
    // Add the difference between October 15, 1582 and January 1, 1601
	// 18 years + 17 days in October + 30 days in November + 31 days in December + 5 leap days
	// or 5748192000000000 100ns "ticks"
	
    lTick += (bits64) 5748192000000000;

#else

#error need to implement tick autopulation for this compiler/architecture

#endif

	// populate the UUID structure with the time and sequence number

	(* (bits32 *) &pUuid->TickLow) = (bits32) (lTick & (bits64) 0xFFFFFFFF);
    (* (bits16 *) &pUuid->TickMiddle) = (bits16) ((lTick >> 32) & 0xFFFF);
    (* (bits16 *) &pUuid->TickHighAndVersion) = (bits16) ((lTick >> 48) & 0x0FFF) | (1 << 12);	

    (* (bits8 *) &pUuid->SequenceHighAndReserved) = ((gUuidSequence & 0x3F00) >> 8) | 0x80;
    (* (bits8 *) &pUuid->SequenceLow) = gUuidSequence & 0xFF;

	// populate the UUID structure with the MAC address

	CopyBlock(pUuid->MacAddress, sizeof(pUuid->MacAddress), &gMacAddress, sizeof(gMacAddress), sizeof(pUuid->MacAddress));

	return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyUuid
(
    const motelUuidHandle pUuidDestination,
	const motelUuidHandle pUuidSource
)
{

// parameter validation

{
	if (NULL == pUuidDestination)
	{
		return (FALSE);
	}

	if (NULL == pUuidSource)
	{
		return (FALSE);
	}
}

// function body

{
	return (CopyBlock(pUuidDestination, sizeof(motelUuid), pUuidSource, sizeof(motelUuid), sizeof(motelUuid)));
}
}

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareUuids
(
    const motelUuidHandle pUuid1,
	const motelUuidHandle pUuid2
)
{

// parameter validation

{
	if (NULL == pUuid1)
	{
		return (FALSE);
	}

	if (NULL == pUuid2)
	{
		return (FALSE);
	}
}

// function body

{
	return (CompareBlocks((const byte *) pUuid1, sizeof(motelUuid), (const byte *) pUuid2, sizeof(motelUuid)));
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ToStringUuid
(
	const motelUuidHandle pUuid,
    char * pString,
    size_t pStringSize
)
{

// parameter validation

{
	if (NULL == pUuid)
	{
		return (FALSE);
	}

	if (NULL == pString)
	{
		return (FALSE);
	}

	if (37 > pStringSize)
	{
		return (FALSE);
	}
}

// function body

{
#if defined MOTEL_LITTLE_ENDIAN
	sprintf(pString, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", ((byte *) pUuid)[3], ((byte *) pUuid)[2], ((byte *) pUuid)[1], ((byte *) pUuid)[0], ((byte *) pUuid)[5], ((byte *) pUuid)[4], ((byte *) pUuid)[7], ((byte *) pUuid)[6], ((byte *) pUuid)[8], ((byte *) pUuid)[9], ((byte *) pUuid)[10], ((byte *) pUuid)[11], ((byte *) pUuid)[12], ((byte *) pUuid)[13], ((byte *) pUuid)[14], ((byte *) pUuid)[15]); 
#else
	sprintf(pString, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", ((byte *) pUuid)[0], ((byte *) pUuid)[1], ((byte *) pUuid)[2], ((byte *) pUuid)[3], ((byte *) pUuid)[4], ((byte *) pUuid)[5], ((byte *) pUuid)[6], ((byte *) pUuid)[7], ((byte *) pUuid)[8], ((byte *) pUuid)[9], ((byte *) pUuid)[10], ((byte *) pUuid)[11], ((byte *) pUuid)[12], ((byte *) pUuid)[13], ((byte *) pUuid)[14], ((byte *) pUuid)[15]); 
#endif
	
	return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION FromStringUuid
(
    char * pString,
	const motelUuidHandle pUuid
)
{

// parameter validation

{
	if (NULL == pString)
	{
		return (FALSE);
	}

	if (NULL == pUuid)
	{
		return (FALSE);
	}
}

// function body

{
	bits32 byte[16]; /* sscanf wants 32 bits per hex pair (UUID byte) */

	sscanf(pString, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", &byte[0], &byte[1], &byte[2], &byte[3], &byte[4], &byte[5], &byte[6], &byte[7], &byte[8], &byte[9], &byte[10], &byte[11], &byte[12], &byte[13], &byte[14], &byte[15]);

#if defined MOTEL_LITTLE_ENDIAN
	((bits8 *) pUuid)[3] = (bits8) byte[0];
	((bits8 *) pUuid)[2] = (bits8) byte[1];
	((bits8 *) pUuid)[1] = (bits8) byte[2];
	((bits8 *) pUuid)[0] = (bits8) byte[3];
	((bits8 *) pUuid)[5] = (bits8) byte[4];
	((bits8 *) pUuid)[4] = (bits8) byte[5];
	((bits8 *) pUuid)[7] = (bits8) byte[6];
	((bits8 *) pUuid)[6] = (bits8) byte[7];
	((bits8 *) pUuid)[8] = (bits8) byte[8];
	((bits8 *) pUuid)[9] = (bits8) byte[9];
	((bits8 *) pUuid)[10] = (bits8) byte[10];
	((bits8 *) pUuid)[11] = (bits8) byte[11];
	((bits8 *) pUuid)[12] = (bits8) byte[12];
	((bits8 *) pUuid)[13] = (bits8) byte[13];
	((bits8 *) pUuid)[14] = (bits8) byte[14];
	((bits8 *) pUuid)[15] = (bits8) byte[15];
#else
	((bits8 *) pUuid)[0] = (bits8) byte[0];
	((bits8 *) pUuid)[1] = (bits8) byte[1];
	((bits8 *) pUuid)[2] = (bits8) byte[2];
	((bits8 *) pUuid)[3] = (bits8) byte[3];
	((bits8 *) pUuid)[4] = (bits8) byte[4];
	((bits8 *) pUuid)[5] = (bits8) byte[5];
	((bits8 *) pUuid)[6] = (bits8) byte[6];
	((bits8 *) pUuid)[7] = (bits8) byte[7];
	((bits8 *) pUuid)[8] = (bits8) byte[8];
	((bits8 *) pUuid)[9] = (bits8) byte[9];
	((bits8 *) pUuid)[10] = (bits8) byte[10];
	((bits8 *) pUuid)[11] = (bits8) byte[11];
	((bits8 *) pUuid)[12] = (bits8) byte[12];
	((bits8 *) pUuid)[13] = (bits8) byte[13];
	((bits8 *) pUuid)[14] = (bits8) byte[14];
	((bits8 *) pUuid)[15] = (bits8) byte[15];
#endif

	return (TRUE);
}
}
