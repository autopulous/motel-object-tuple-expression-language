/*----------------------------------------------------------------------------
  Motel Buffer

  application programmer's interface (API) header file
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

#ifndef MOTEL_BUFFER_I_H
#define MOTEL_BUFFER_I_H

#if defined MOTEL_NAMESPACE

#define ConstructBuffer Motel_ConstructBuffer
#define DestructBuffer  Motel_DestructBuffer
#define SetBufferMember Motel_SetBufferMember
#define GetBufferMember Motel_GetBufferMember
#define PeekBuffer      Motel_PeekBuffer
#define PullBuffer      Motel_PullBuffer

#endif

/*----------------------------------------------------------------------------
  ConstructBuffer()
  ----------------------------------------------------------------------------
  Construct a byte buffer.
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I/O) Pointer to recieve the byte buffer handle
  pBytes  - (I)   A byte array
  pLength - (I)   The number of bytes in the byte array
  ----------------------------------------------------------------------------
  Return Values:

  True  - Buffer was succesfully constructed

  False - Buffer was not successfully constructed due to:

          1. Insufficient maximum memory requested
          2. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  The buffer length controls how many bytes are accessible within the buffer.

  A buffer is a defined portion of a chunk of memory allocated by the calling
  process. It is permissible to partition a chunk of memory into multiple
  buffers which may be overlapping.

  Any type of data may be stored in a buffer.
  
  Buffers may contain strings - but it is up to the calling process to treat
  the value contained within the buffer as a string because the string '\0'
  character has no meaning within a buffer object.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructBuffer
(
    motelBufferHandle * pBuffer,
    byte * pBytes,
    size_t pLength
);

/*----------------------------------------------------------------------------
  DestructBuffer()
  ----------------------------------------------------------------------------
  Destruct a byte buffer.
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I/O) Pointer to the byte buffer handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Buffer was succesfully destructed

  False - Buffer was not successfully destructed due to:

          1. The pBuffer handle pointer was NULL
		  2. The SafeFreeBlock() of the buffer failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructBuffer
(
    motelBufferHandle * pBuffer
);

/*----------------------------------------------------------------------------
  SetBufferMember()
  ----------------------------------------------------------------------------
  Set the value of a published buffer member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I) A buffer handle
  pMember - (I) The member to retrieve
  pValue  - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pBuffer was NULL
          2. pValue was NULL
		  3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.buffer.t.h of the member variable to learn
  the memory and data type requirements of each.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetBufferMember
(
    motelBufferHandle pBuffer,
	motelBufferMember pMember,
	const void * pValue
);

/*----------------------------------------------------------------------------
  GetBufferMember()
  ----------------------------------------------------------------------------
  Get the value of a published buffer member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I)   A buffer handle
  pMember - (I)   The member variable to retrieve
  pValue  - (I/O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pBuffer was NULL
          2. pValue was NULL
		  3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.buffer.t.h of the member variable to learn
  the memory and data type requirements of each.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetBufferMember
(
    motelBufferHandle pBuffer,
	motelBufferMember pMember,
	void * pValue
);

/*----------------------------------------------------------------------------
  PeekBuffer()
  ----------------------------------------------------------------------------
  Return the byte pointed to by the byte buffer cursor (does not alter the
  byte buffer cursor).
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I) Pointer to byte buffer buffer
  pByte -   (O) Pointer to receive byte buffer cursor
  ----------------------------------------------------------------------------
  Returns:

  The byte at the byte cursor
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekBuffer
(
   motelBufferHandle pBuffer,
   byte * pByte
);

/*----------------------------------------------------------------------------
  PullBuffer()
  ----------------------------------------------------------------------------
  Return the byte pointed to by the byte buffer cursor then advances the byte
  buffer cursor.
  ----------------------------------------------------------------------------
  Parameters:

  pBuffer - (I) Pointer to byte buffer buffer
  pByte -   (O) Pointer to receive byte buffer cursor
  ----------------------------------------------------------------------------
  Returns:

  The byte at the byte buffer cursor
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullBuffer
(
   motelBufferHandle pBuffer,
   byte * pByte
);

#endif
