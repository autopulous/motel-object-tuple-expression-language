/*----------------------------------------------------------------------------
  Motel Document
  
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

#include "motel.document.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.document.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateDocument
(
    motelDocumentHandle pDocument
)
{
    unsigned int lCount;

    /*
    ** make sure that no more than one document source is set
    */

    lCount = 0;

    if (NULL != pDocument->documentHrr)
    {
        lCount++;
    }

    if (NULL != pDocument->documentUrl)
    {
        lCount++;
    }

    if (NULL != pDocument->documentFile)
    {
        lCount++;
    }

    if (NULL != pDocument->documentStream)
    {
        lCount++;
    }

    if (NULL != pDocument->documentBuffer)
    {
        lCount++;
    }

    if (1 < lCount)
    {
        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructDocument
(
    motelDocumentHandle * pDocument,
	size_t pMaximumSize
)
{
	/*
	** the maximum size is too small to even create the document control structure
	*/

	if (0 != pMaximumSize && sizeof(motelDocument) > pMaximumSize)
	{
		return (FALSE);
	}
    
	/*
	** allocate the document control structure
	*/

    if (!SafeMallocBlock((void **) pDocument, sizeof(motelDocument)))
    {
        return (FALSE);
    }

	/*
	** initialize the document control structure
	*/

	(* pDocument)->result = motelResult_OK;

	(* pDocument)->maximumSize = pMaximumSize;
	(* pDocument)->size = sizeof(motelDocument);

//    (* pDocument)->character = gCharacter;

    (* pDocument)->documentHrr = (motelHrrHandle) NULL;
    (* pDocument)->documentUrl = (motelUrlHandle) NULL;
    (* pDocument)->documentFile = (motelFileHandle) NULL;
    (* pDocument)->documentStream = (motelStreamHandle) NULL;
    (* pDocument)->documentBuffer = (motelBufferHandle) NULL;

	(* pDocument)->root = (motelDocumentNodeHandle) NULL;
	(* pDocument)->cursor = (motelDocumentNodeHandle) NULL;

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructDocument
(
    motelDocumentHandle * pDocument
)
{
    /*
    ** there is no document
    */

    if (NULL == pDocument || NULL == * pDocument)
	{
		return (FALSE);
	}

	/*
	** release the document control structure
	*/

    SafeFreeBlock((void **) pDocument);

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetDocumentMember
(
    motelDocumentHandle pDocument,
	motelDocumentMember pMember,
	const void * pValue
)
{
    /*
    ** there is no document object
    */

	if (NULL == pDocument)
	{
		return (FALSE);
	}

	pDocument->result = motelResult_OK;

	/*
	** node cursor navigation
	*/

	switch (pMember)
	{
        case motelDocumentMember_DocumentHRR:

            /*
            ** Set attribute
            */

            if (NULL == pDocument->documentHrr)
            {
                ConstructHrr(&pDocument->documentHrr, (char *) pValue);
            }

            /*
            ** Reset mutually exclusive attributes
            */

            if (NULL != pDocument->documentUrl)
            {
                DestructUrl(&pDocument->documentUrl);
            }

            if (NULL != pDocument->documentFile)
            {
                DestructFile(&pDocument->documentFile);
            }

            if (NULL != pDocument->documentStream)
            {
                DestructStream(&pDocument->documentStream);
            }

            if (NULL != pDocument->documentBuffer)
            {
                DestructBuffer(&pDocument->documentBuffer);
            }

			return (TRUE);

		case motelDocumentMember_DocumentURL:

            /*
            ** Set attribute
            */

            if (NULL == pDocument->documentUrl)
            {
                ConstructUrl(&pDocument->documentUrl, (char *) NULL);
            }

            SetUrlMember(pDocument->documentUrl, motelUrlMember_Url, (void *) pValue);

            /*
            ** Reset mutually exclusive attributes
            */

            if (NULL != pDocument->documentHrr)
            {
                DestructHrr(&pDocument->documentHrr);
            }

            if (NULL != pDocument->documentFile)
            {
                DestructFile(&pDocument->documentFile);
            }

            if (NULL != pDocument->documentStream)
            {
                DestructStream(&pDocument->documentStream);
            }

            if (NULL != pDocument->documentBuffer)
            {
                DestructBuffer(&pDocument->documentBuffer);
            }

			return (TRUE);

        case motelDocumentMember_DocumentFile:

            /*
            ** Set attribute
            */

            if (NULL == pDocument->documentFile)
            {
                ConstructFile(&pDocument->documentFile, (char *) pValue, FALSE);
            }

            /*
            ** Reset mutually exclusive attributes
            */

            if (NULL != pDocument->documentHrr)
            {
                DestructHrr(&pDocument->documentHrr);
            }

            if (NULL != pDocument->documentUrl)
            {
                DestructUrl(&pDocument->documentUrl);
            }

            if (NULL != pDocument->documentStream)
            {
                DestructStream(&pDocument->documentStream);
            }

            if (NULL != pDocument->documentBuffer)
            {
                DestructBuffer(&pDocument->documentBuffer);
            }

			return (TRUE);

        case motelDocumentMember_DocumentStream:

            /*
            ** Set attribute
            */

            if (NULL == pDocument->documentStream)
            {
                ConstructStream(&pDocument->documentStream, (FILE *) pValue);
            }

            /*
            ** Reset mutually exclusive attributes
            */

            if (NULL != pDocument->documentHrr)
            {
                DestructHrr(&pDocument->documentHrr);
            }

            if (NULL != pDocument->documentUrl)
            {
                DestructUrl(&pDocument->documentUrl);
            }

            if (NULL != pDocument->documentFile)
            {
                DestructFile(&pDocument->documentFile);
            }

            if (NULL != pDocument->documentBuffer)
            {
                DestructBuffer(&pDocument->documentBuffer);
            }

			return (TRUE);

        case motelDocumentMember_DocumentBuffer:

            /*
            ** Set attribute
            */

            if (NULL == pDocument->documentBuffer)
            {
                ConstructBuffer(&pDocument->documentBuffer, (char *) pValue, strlen((char *) pValue));
            }

            /*
            ** Reset mutually exclusive attributes
            */

            if (NULL != pDocument->documentHrr)
            {
                DestructHrr(&pDocument->documentHrr);
            }

            if (NULL != pDocument->documentUrl)
            {
                DestructUrl(&pDocument->documentUrl);
            }

            if (NULL != pDocument->documentFile)
            {
                DestructFile(&pDocument->documentFile);
            }

            if (NULL != pDocument->documentStream)
            {
                DestructStream(&pDocument->documentStream);
            }

			return (TRUE);
	}

	if (NULL == pValue)
	{
		pDocument->result = motelResult_NullPointer;

		return (FALSE);
	}

	switch (pMember)
	{
	}

	pDocument->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetDocumentMember
(
    motelDocumentHandle pDocument,
	motelDocumentMember pMember,
	void * pValue
)
{
    /*
    ** there is no document object
    */

	if (NULL == pDocument)
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
	** result code is a special case because we want to set a result code for GetDocumentMember()
	*/

    if (motelDocumentMember_Result == pMember)
    {
		* (motelResult *) pValue = pDocument->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pDocument->result = motelResult_OK;

	switch (pMember)
	{
		case motelDocumentMember_Size:

            * (size_t *) pValue = pDocument->size;

			return (TRUE);

        case motelDocumentMember_DocumentHRR:

            * (motelHrrHandle *) pValue = pDocument->documentHrr;

            return (TRUE);

        case motelDocumentMember_DocumentURL:

            * (motelUrlHandle *) pValue = pDocument->documentUrl;

            return (TRUE);

        case motelDocumentMember_DocumentFile:

            * (motelFileHandle *) pValue = pDocument->documentFile;

            return (TRUE);

        case motelDocumentMember_DocumentStream:

            * (motelStreamHandle *) pValue = pDocument->documentStream;

            return (TRUE);

        case motelDocumentMember_DocumentBuffer:

            * (motelBufferHandle *) pValue = pDocument->documentBuffer;

            return (TRUE);
	}

	pDocument->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ParseDocument
(
    motelDocumentHandle pDocument
)
{
    motelInputHandle lCharacterStream;

    MotelInputPull * MotelInputPull;

    char lCharacter;

    if (NULL != pDocument->documentHrr)
    {
        lCharacterStream = pDocument->documentHrr;

        MotelInputPull = PullHrrByte;
    }
    else if (NULL != pDocument->documentUrl)
    {
        lCharacterStream = pDocument->documentStream;

        MotelInputPull = PullUrlByte;
    }
    else if (NULL != pDocument->documentFile)
    {
        lCharacterStream = pDocument->documentFile;

        MotelInputPull = PullFile;
    }
    else if (NULL != pDocument->documentStream)
    {
        lCharacterStream = pDocument->documentStream;

        MotelInputPull = PullStreamByte;
    }
    else if (NULL != pDocument->documentBuffer)
    {
        lCharacterStream = pDocument->documentBuffer;

        MotelInputPull = PullBuffer;
    }
    else
    {
        pDocument->result = motelResult_NoSource;

        return (FALSE);
    }

    /*
    ** ignore leading whitespace at the beginning of stream (temporary implementation)
    */

    while(MotelInputPull(lCharacterStream, (byte *) & lCharacter))
    {
        if (' ' != lCharacter)
        {
            break;
        }
    }

    return (TRUE);
}
