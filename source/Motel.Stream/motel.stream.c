/*----------------------------------------------------------------------------
  Motel Stream
  
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

#include "motel.stream.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.stream.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructStream
(
    motelStreamHandle * pStream,
    FILE * pFile
)
{
	/*
	** no source stream pointer was provided
	*/

    if (NULL == pStream)
    {
		return (FALSE);
    }

	/*
	** no file pointer was provided
	*/

    if (NULL == pFile)
    {
        (* pStream)->result = motelResult_NullPointer;

        return (FALSE);
    }

	/*
	** allocate the stream control structure
	*/

	if (!SafeMallocBlock((void **) pStream, sizeof(motelStream)))
	{
		return (FALSE);
	}

	/*
	** initialize the stream control structure
	*/

	(* pStream)->result = motelResult_OK;

    (* pStream)->stream = pFile;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructStream
(
    motelStreamHandle * pStream
)
{
    /*
    ** there is no stream
    */

    if (NULL == pStream || NULL == * pStream)
    {
        return (FALSE);
    }

    if (!SafeFreeBlock((void **) pStream))
	{
		(* pStream)->result = motelResult_MemoryDeallocation;

		return (FALSE);
	}

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetStreamMember
(
    motelStreamHandle pStream,
	motelStreamMember pMember,
	const void * pValue
)
{
    /*
    ** there is no stream object
    */

	if (NULL == pStream)
	{
		return (FALSE);
	}

    /*
    ** no input parameter
    */

	if (NULL == pValue)
	{
		pStream->result = motelResult_NullPointer;

		return (FALSE);
	}

    /*
    ** set member
    */

	pStream->result = motelResult_OK;

	switch (pMember)
	{
        case motelStreamMember_StreamErrorNumber:

            if (0 != * (int *) pValue)
            {
            	pStream->result = motelResult_InvalidValue;

                return (FALSE);
            }
            
            clearerr(pStream->stream);

            return (TRUE);
	}

	pStream->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetStreamMember
(
    motelStreamHandle pStream,
	motelStreamMember pMember,
	void * pValue
)
{
    /*
    ** there is no stream object
    */

	if (NULL == pStream)
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
	** result code is a special case because we want to set a result code for GetStreamMember()
	*/

    if (motelStreamMember_Result == pMember)
    {
		* (motelResult *) pValue = pStream->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pStream->result = motelResult_OK;

	switch (pMember)
	{
        case motelStreamMember_StreamErrorNumber:

            * (int *) pValue = ferror(pStream->stream);
            
            return (TRUE);
	}

	pStream->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushStreamByte
(
   motelStreamHandle pStream,
   byte pByte
)
{
    /*
    ** there is no stream
    */

    if (NULL == pStream)
    {
        return (FALSE);
    }

    /*
    ** write character
    */

    if (EOF == fputc(pByte, pStream->stream))
    {
        pStream->result = motelResult_Writing;

        return (FALSE);
    }

    /*
    ** success
    */

    pStream->result = motelResult_OK;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullStreamByte
(
   motelStreamHandle pStream,
   byte * pByte
)
{
    byte lByte;

    /*
    ** there is no stream
    */

    if (NULL == pStream)
    {
        return (FALSE);
    }

    /*
    ** there is no output byte pointer
    */

    if (NULL == pByte)
    {
        pStream->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** read character
    */

    lByte = (byte) fgetc(pStream->stream);

    if (ferror(pStream->stream))
    {
        * pByte = '\0';

        if (feof(pStream->stream))
        {
            pStream->result = motelResult_StreamEnd;

            return (TRUE);
        }

        pStream->result = motelResult_Reading;

        return (FALSE);
    }

    * pByte = lByte;

    /*
    ** success
    */

    pStream->result = motelResult_OK;

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/
