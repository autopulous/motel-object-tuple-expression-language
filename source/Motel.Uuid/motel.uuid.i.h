/*----------------------------------------------------------------------------
  Motel UUID

  application programmer's interface (API) header file
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

#ifndef MOTEL_UUID_I_H
#define MOTEL_UUID_I_H

#include "motel.uuid.t.h"

/*----------------------------------------------------------------------------
  ConstructUuid()
  ----------------------------------------------------------------------------
  Construct an empty UUID
  ----------------------------------------------------------------------------
  Parameters:

  pUuid - (I/O) Pointer to recieve the UUID handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - UUID was succesfully constructed

  False - UUID was not successfully constructed due to:

          1. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructUuid
(
    motelUuidHandle * pUuid
);

/*----------------------------------------------------------------------------
  ResetUuid()
  ----------------------------------------------------------------------------
  Clear an UUID
  ----------------------------------------------------------------------------
  Parameters:

  pUuid - (I) The UUID handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - UUID was succesfully cleared

  False - UUID was not successfully cleared due to:
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ResetUuid
(
    motelUuidHandle pUuid
);

/*----------------------------------------------------------------------------
  DestructUuid()
  ----------------------------------------------------------------------------
  Destruct a UUID
  ----------------------------------------------------------------------------
  Parameters:

  pUuid - (I/O) Pointer to the UUID handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - UUID was succesfully destructed

  False - UUID was not successfully destructed due to:

          1. The pUuid handle pointer was NULL
		  2. The SafeFreeBlock() failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructUuid
(
    motelUuidHandle * pUuid
);

/*----------------------------------------------------------------------------
  GenerateUuid()
  ----------------------------------------------------------------------------
  Generate a version 1 UUID from a MAC address, the time and a sequence number

  Field                   Data Type                 Byte   Note
  ----------------------------------------------------------------------------
  TickLow                 unsigned 32 bit integer   0-3    The low field of the timestamp

  TickMiddle              unsigned 16 bit integer   4-5    The middle field of the timestamp

  TickHighAndVersion      unsigned 16 bit integer   6-7    The high field of the timestamp multiplexed with the version number

  SequenceHighAndReserved unsigned 8 bit integer    8      The high field of the clock sequence multiplexed with the variant

  SequenceLow             unsigned 8 bit integer    9      The low field of the clock sequence

  MacAddress              unsigned 48 bit integer   10-15  The spatially unique MacAddress identifier

  The version number is in the most significant 4 bits of the time stamp (TickHighAndVersion).
  ----------------------------------------------------------------------------
  Parameters:
  
  pUuid     - (I) Pointer generated UUID
  ----------------------------------------------------------------------------
  Returns:

  TRUE  - Success
  FALSE - Failure
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GenerateUuid
(
    motelUuidHandle pUuid
);

/*----------------------------------------------------------------------------
  CopyUuid()
  ----------------------------------------------------------------------------
  UUID copy
  ----------------------------------------------------------------------------
  Parameters:

  pUuidDestination - (I) Pointer to UUID
  pUuidSource      - (I) Pointer to UUID
  ----------------------------------------------------------------------------
  Returns:

  TRUE  - Success
  FALSE - Failure
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyUuid
(
    const motelUuidHandle pUuidDestination,
	const motelUuidHandle pUuidSource
);

/*----------------------------------------------------------------------------
  CompareUuids()
  ----------------------------------------------------------------------------
  UUID comparison
  ----------------------------------------------------------------------------
  Parameters:

  pUuid1 - (I) Pointer to UUID
  pUuid2 - (I) Pointer to UUID
  ----------------------------------------------------------------------------
  Returns:

  lem (LESS_THAN, EQUAL_TO, MORE_THAN) value
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS lem CALLING_CONVENTION CompareUuids
(
    const motelUuidHandle pUuid1,
	const motelUuidHandle pUuid2
);

/*----------------------------------------------------------------------------
  ToStringUuid()
  ----------------------------------------------------------------------------
  Converts a UUID to a formatted string of hexidecimal charactes

  The UUID string representation is described by the following extended BNF:

  UUID                    = <TickLow> "-" <TickMiddle> "-" <TickHighAndVersion> "-" <SequenceHighAndReserved> <SequenceLow> "-" <MacAddress>

  TickLow                 = 4 * <hexPair>
  TickMiddle              = 2 * <hexPair>
  TickHighAndVersion      = 2 * <hexPair>
  SequenceHighAndReserved = 1 * <hexPair>
  SequenceLow             = 1 * <hexPair>
  MacAddress              = 6 * <hexPair>

  hexPair                 = <hexDigit> <hexDigit>
  hexDigit                = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "a" | "b" | "c" | "d" | "e" | "f" | "A" | "B" | "C" | "D" | "E" | "F"

  Example UUID string:

  476e2373-3e20-11e1-9f14-542930e7bb0d
  ----------------------------------------------------------------------------
  Parameters:

  pUuid       - (I) Pointer to a UUID
  pString     - (O) Pointer to string buffer to hold the formatted UUID
  pStringSize - (I) Size of the string buffer
  ----------------------------------------------------------------------------
  Notes:

  The "to string" must be sized to at least 37 characters
  ----------------------------------------------------------------------------
  Returns:

  TRUE  - Success
  FALSE - Failure
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ToStringUuid
(
	const motelUuidHandle pUuid,
    char * pString,
    size_t pStringSize
);

/*----------------------------------------------------------------------------
  ToStringUuid()
  ----------------------------------------------------------------------------
  Converts a formatted string of hexidecimal charactes to a UUID object
  ----------------------------------------------------------------------------
  Parameters:

  pString     - (O) Pointer to the formatted UUID string buffer
  pUuid       - (I) Pointer to the UUID
  ----------------------------------------------------------------------------
  Notes:

  The "from string" must represent a valid UUID
  ----------------------------------------------------------------------------
  Returns:

  TRUE  - Success
  FALSE - Failure
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION FromStringUuid
(
    char * pString,
	const motelUuidHandle pUuid
);

#endif
