/*----------------------------------------------------------------------------
  Motel Stream
 
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
  Motel Stream application programmer's interface (API) header stream
  ----------------------------------------------------------------------------*/

#ifndef MOTEL_STREAM_I_H
#define MOTEL_STREAM_I_H

/*----------------------------------------------------------------------------
  ConstructStream()
  ----------------------------------------------------------------------------
  Construct a byte stream.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I/O) Pointer to recieve the byte stream handle
  pBytes  - (I)   A byte array
  pLength - (I)   The number of bytes in the byte array
  ----------------------------------------------------------------------------
  Return Values:

  True  - Stream was succesfully constructed

  False - Stream was not successfully constructed due to:

          1. Insufficient maximum memory requested
          2. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  This function requires the contents of the pStream handle to be initialized
  to NULL prior to calling this function because this function assumes that 
  a pointer with value represents an unfreed memory block and therefore
  overwritting this pointer with a new value would orphan the previously
  allocated memory block.

  The maximum memory paramter may be set to zero to allow the stream to grow
  to the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructStream
(
    motelStreamHandle * pStream,
    FILE * pFile
);

/*----------------------------------------------------------------------------
  DestructStream()
  ----------------------------------------------------------------------------
  Destruct a byte stream.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I/O) Pointer to the byte stream handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Stream was succesfully destructed

  False - Stream was not successfully destructed due to:

          1. The pStream handle pointer was NULL
		  2. The SafeFreeBlock() of the stream failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructStream
(
    motelStreamHandle * pStream
);

/*----------------------------------------------------------------------------
  SetStreamMember()
  ----------------------------------------------------------------------------
  Set the value of a published byte stream member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I) A byte stream handle
  pMember - (I) The member to retrieve
  pValue  - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pStream was NULL
          2. pValue was NULL
		  3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.stream.t.h of the member variable to learn
  the memory and data type requirements of each.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetStreamMember
(
    motelStreamHandle pStream,
	motelStreamMember pMember,
	const void * pValue
);

/*----------------------------------------------------------------------------
  GetStreamMember()
  ----------------------------------------------------------------------------
  Get the value of a published byte stream member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I)   A byte stream handle
  pMember - (I)   The member variable to retrieve
  pValue  - (I/O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pStream was NULL
          2. pValue was NULL
		  3. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.stream.t.h of the member variable to learn
  the memory and data type requirements of each.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetStreamMember
(
    motelStreamHandle pStream,
	motelStreamMember pMember,
	void * pValue
);

/*----------------------------------------------------------------------------
  PushStreamByte()
  ----------------------------------------------------------------------------
  Sends a byte through a stream.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I) Pointer to the stream
  pByte   - (I) The next byte to the output stream
  ----------------------------------------------------------------------------
  Returns:

  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushStreamByte
(
   motelStreamHandle pStream,
   byte pByte
);

/*----------------------------------------------------------------------------
  PullStreamByte()
  ----------------------------------------------------------------------------
  Receives a byte through a stream.
  ----------------------------------------------------------------------------
  Parameters:

  pStream - (I) Pointer to the stream
  pByte   - (O) Pointer to the byte transfer buffer
  ----------------------------------------------------------------------------
  Returns:

  The next byte from the input stream
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullStreamByte
(
   motelStreamHandle pStream,
   byte * pByte
);

#endif
