/*----------------------------------------------------------------------------
  Motel File
 
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

#include "motel.file.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.file.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructFile
(
    motelFileHandle * pFile,
    char * pFileReference,
    boolean pCreateIndicator
)
{
    size_t lFileReferenceLength;
    size_t lFileReferenceSize;

	/*
	** no source file pointer was provided
	*/

    if (NULL == pFile)
    {
		return (FALSE);
    }

	/*
	** allocate the file control structure
	*/

	if (!SafeMallocBlock((void **) pFile, sizeof(motelFile)))
	{
		return (FALSE);
	}

	/*
	** initialize the file control structure
	*/

    lFileReferenceLength = strlen(pFileReference);

    if (0 == lFileReferenceLength)
    {
    	(* pFile)->result = motelResult_Opening;

        return (FALSE);
    }

    /*
    ** open file read/write (binary mode, where meaningful)
    */

    if (pCreateIndicator)
    {
        (* pFile)->stream = fopen(pFileReference, "wb+");
    }
    else
    {
        (* pFile)->stream = fopen(pFileReference, "rb+");
    }

    if (NULL == (* pFile)->stream)
    {
    	(* pFile)->result = motelResult_Opening;

        return (FALSE);
    }

    lFileReferenceSize = lFileReferenceLength + 1;

    (* pFile)->fileReference = (char *) NULL;

	if (!SafeMallocBlock((void **) &(* pFile)->fileReference, lFileReferenceSize))
	{
		return (FALSE);
	}

    CopyString(pFileReference, (* pFile)->fileReference, lFileReferenceSize);

    (* pFile)->createMode = pCreateIndicator;

	(* pFile)->result = motelResult_OK;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructFile
(
    motelFileHandle * pFile
)
{
    /*
    ** there is no file
    */

    if (NULL == pFile || NULL == * pFile)
    {
        return (FALSE);
    }

    if (!SafeFreeBlock((void **) &(* pFile)->fileReference))
    {
		(* pFile)->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    if (!SafeFreeBlock((void **) pFile))
	{
		(* pFile)->result = motelResult_MemoryDeallocation;

		return (FALSE);
	}

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetFileMember
(
    motelFileHandle pFile,
	motelFileMember pMember,
	const void * pValue
)
{
    /*
    ** there is no file object
    */

	if (NULL == pFile)
	{
		return (FALSE);
	}

	pFile->result = motelResult_OK;

	/*
	** byte cursor navigation
	*/

	switch (pMember)
	{
        case motelFileMember_FileErrorNumber:

            if (0 != * (int *) pValue)
            {
            	pFile->result = motelResult_InvalidValue;

                return (FALSE);
            }
            
            clearerr(pFile->stream);

            return (TRUE);
    
        case motelFileMember_First:

            if (0 != fseek(pFile->stream, 0, SEEK_SET))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

			return (TRUE);

		case motelFileMember_Last:

            if (0 != fseek(pFile->stream, 0, SEEK_END))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

			return (TRUE);

		case motelFileMember_Previous:

            if (0 != fseek(pFile->stream, -1, SEEK_CUR))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

			return (TRUE);

		case motelFileMember_Next:

            if (0 != fseek(pFile->stream, 1, SEEK_CUR))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

			return (TRUE);
	}

	if (NULL == pValue)
	{
		pFile->result = motelResult_NullPointer;

		return (FALSE);
	}

	switch (pMember)
	{
	}

	pFile->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetFileMember
(
    motelFileHandle pFile,
	motelFileMember pMember,
	void * pValue
)
{
    long lFilePosition;
    long lFileSize;

    /*
    ** there is no file object
    */

	if (NULL == pFile)
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
	** result code is a special case because we want to set a result code for GetFileMember()
	*/

    if (motelFileMember_Result == pMember)
    {
		* (motelResult *) pValue = pFile->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pFile->result = motelResult_OK;

	switch (pMember)
	{
        case motelFileMember_Size:

            /*
            ** flush the file stream
            */

            if (EOF == fflush(pFile->stream))
            {
                pFile->result = motelResult_File;

                return (FALSE);
            }

            /*
            ** hold the current cursor position
            */

            lFilePosition = ftell(pFile->stream);

            if (-1L == lFilePosition)
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

            /*
            ** move to the end of the file
            */

            if (0 != fseek(pFile->stream, 0, SEEK_END))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

            /*
            ** get the EOF cursor position as the file length
            */

            lFileSize = ftell(pFile->stream);

            if (-1L == lFileSize)
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

            /*
            ** reset the current cursor position
            */

            if (0 != fseek(pFile->stream, lFilePosition, SEEK_SET))
            {
                pFile->result = motelResult_Cursor;

                return (FALSE);
            }

            /*
            ** return the file length
            */

            * (size_t *) pValue = lFileSize;

            return (TRUE);

        case motelFileMember_FileErrorNumber:

            * (int *) pValue = ferror(pFile->stream);
            
            return (TRUE);
	}

	pFile->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushFile
(
   motelFileHandle pFile,
   byte pByte
)
{
    /*
    ** there is no file
    */

    if (NULL == pFile)
    {
        return (FALSE);
    }

    /*
    ** write character
    */

    if (EOF == fputc((int) pByte, pFile->stream))
    {
        pFile->result = motelResult_Writing;
        
        return (FALSE);
    }

    /*
    ** success
    */

    pFile->result = motelResult_OK;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekFile
(
   motelFileHandle pFile,
   byte * pByte
)
{
    /*
    ** pull the current character from the file
    */

    if (FALSE == PullFile(pFile, pByte))
    {
        return (FALSE);
    }

    /*
    ** restore file pointer
    */

    if (0 != fseek(pFile->stream, -1, SEEK_CUR))
    {
    	pFile->result = motelResult_Cursor;

        return (FALSE);
    }

    /*
    ** success
    */

    pFile->result = motelResult_OK;

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullFile
(
   motelFileHandle pFile,
   byte * pByte
)
{
    char lCharacter;

    /*
    ** there is no file
    */

    if (NULL == pFile)
    {
        return (FALSE);
    }

    /*
    ** there is no output byte pointer
    */

    if (NULL == pByte)
    {
        pFile->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** read character
    */

    lCharacter = (char) fgetc(pFile->stream);

    if (0 != ferror(pFile->stream))
    {
        * pByte = '\0';

        if (0 != feof(pFile->stream))
        {
            pFile->result = motelResult_StreamEnd;

            return (TRUE);
        }

        pFile->result = motelResult_StreamEnd;

        return (FALSE);
    }

    * pByte = lCharacter;

    /*
    ** success
    */

    pFile->result = motelResult_OK;

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/
