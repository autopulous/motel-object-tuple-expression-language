/*----------------------------------------------------------------------------
  Motel Buffer

  library implementation file
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

#include "motel.buffer.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.buffer.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructBuffer
(
    motelBufferHandle * pBuffer,
    byte * pBytes,
    size_t pSize
)
{
	/*
	** no source byte buffer was provided
	*/

    if (NULL == pBytes)
    {
		return (FALSE);
    }

	/*
	** allocate the buffer control structure
	*/

	if (!SafeMallocBlock((void **) pBuffer, sizeof(motelBuffer)))
	{
		return (FALSE);
	}

	/*
	** initialize the buffer control structure
	*/

	(* pBuffer)->result = motelResult_OK;

    (* pBuffer)->size = pSize;

    (* pBuffer)->firstByte = pBytes;
    (* pBuffer)->thisByte = pBytes;
    (* pBuffer)->lastByte = pBytes + pSize - 1;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructBuffer
(
    motelBufferHandle * pBuffer
)
{
    /*
    ** there is no buffer
    */

    if (NULL == pBuffer || NULL == * pBuffer)
    {
        return (FALSE);
    }

    if (!SafeFreeBlock((void **) pBuffer))
	{
		(* pBuffer)->result = motelResult_MemoryDeallocation;

		return (FALSE);
	}

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetBufferMember
(
    motelBufferHandle pBuffer,
	motelBufferMember pMember,
	const void * pValue
)
{
    /*
    ** there is no buffer object
    */

	if (NULL == pBuffer)
	{
		return (FALSE);
	}

	pBuffer->result = motelResult_OK;

	/*
	** byte cursor navigation
	*/

	switch (pMember)
	{
		case motelBufferMember_First:

            pBuffer->thisByte = pBuffer->firstByte;

			return (TRUE);

		case motelBufferMember_Last:

            pBuffer->thisByte = pBuffer->lastByte;

			return (TRUE);

		case motelBufferMember_Previous:

            if (pBuffer->firstByte == pBuffer->thisByte)
            {
                return (FALSE);
            }

			pBuffer->thisByte--;

			return (TRUE);

		case motelBufferMember_Next:

            if (pBuffer->lastByte == pBuffer->thisByte)
            {
                return (FALSE);
            }

			pBuffer->thisByte++;

			return (TRUE);
	}

    /*
    **  set member
    */

	if (NULL == pValue)
	{
		pBuffer->result = motelResult_NullPointer;

		return (FALSE);
	}

	switch (pMember)
	{
	}

	pBuffer->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetBufferMember
(
    motelBufferHandle pBuffer,
	motelBufferMember pMember,
	void * pValue
)
{
    /*
    ** there is no buffer object
    */

	if (NULL == pBuffer)
	{
		return (FALSE);
	}

	/*
	** no return parameter
	*/

	if (NULL == pValue)
	{
		return (FALSE);
	}

	/*
	** result code is a special case because we want to set a result code for GetBufferMember()
	*/

    if (motelBufferMember_Result == pMember)
    {
		* (motelResult *) pValue = pBuffer->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pBuffer->result = motelResult_OK;

	switch (pMember)
	{
        case motelBufferMember_Size:

            * (size_t *) pValue = pBuffer->size;

            return (TRUE);

        case motelBufferMember_Cursor:

            * (byte **) pValue = pBuffer->thisByte;

			return (TRUE);
	}

	pBuffer->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekBuffer
(
   motelBufferHandle pBuffer,
   byte * pByte
)
{
    /*
    ** there is no buffer
    */

    if (NULL == pBuffer)
    {
        return (FALSE);
    }

    /*
    ** there is no output byte pointer
    */

    if (NULL == pByte)
    {
        pBuffer->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** get the byte cursor
    */

    * pByte = * pBuffer->thisByte;

    pBuffer->result = motelResult_OK;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullBuffer
(
   motelBufferHandle pBuffer,
   byte * pByte
)
{
    /*
    ** there is no buffer
    */

    if (NULL == pBuffer)
    {
        return (FALSE);
    }

    /*
    ** there is no output byte pointer
    */

    if (NULL == pByte)
    {
        pBuffer->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** get the byte cursor
    */

    * pByte = * pBuffer->thisByte;

    /*
    ** advance the byte cursor when not the last byte
    */

    if (pBuffer->lastByte > pBuffer->thisByte)
    {
        pBuffer->thisByte++;
    }

    pBuffer->result = motelResult_OK;

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/
