/*----------------------------------------------------------------------------
  Motel Tokenizer
 
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

#include "motel.tokenizer.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.tokenizer.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateTokenizer
(
    motelTokenizerHandle pTokenizer
)
{
    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructTokenizer
(
    motelTokenizerHandle * pTokenizer,
	size_t pMaximumSize
)
{
	/*
	** the maximum size is too small to even create the tokenizer control structure
	*/

	if (0 != pMaximumSize && sizeof(motelTokenizer) > pMaximumSize)
	{
		return (FALSE);
	}
    
	/*
	** allocate the tokenizer control structure
	*/

    if (!SafeMallocBlock((void **) pTokenizer, sizeof(motelTokenizer)))
    {
        return (FALSE);
    }

	/*
	** initialize the tokenizer control structure
	*/

	(* pTokenizer)->result = motelResult_OK;

	(* pTokenizer)->maximumSize = pMaximumSize;
	(* pTokenizer)->size = sizeof(motelTokenizer);

    (* pTokenizer)->delimiter = (char *) NULL;
    (* pTokenizer)->token = (char *) NULL;

    (* pTokenizer)->_NextCharacter = (_MotelNextCharacter) NULL;

	/*
	** allocate the delimiter buffer
	*/

    if (!SafeMallocBlock((void **) &(* pTokenizer)->delimiter, sizeof(DELIMITER_BUFFER_SIZE)))
    {
        DestructTokenizer(pTokenizer);

        return (FALSE);
    }

	/*
	** allocate the token buffer
	*/

    if (!SafeMallocBlock((void **) &(* pTokenizer)->token, sizeof(TOKEN_BUFFER_SIZE)))
    {
        DestructTokenizer(pTokenizer);

        return (FALSE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructTokenizer
(
    motelTokenizerHandle * pTokenizer
)
{
    /*
    ** there is no tokenizer
    */

    if (NULL == pTokenizer || NULL == * pTokenizer)
	{
		return (FALSE);
	}

    /*
    ** free the internal buffers
    */

    if (NULL != (* pTokenizer)->token)
    {
        SafeFreeBlock((void **) &(* pTokenizer)->token);
    }

    if (NULL != (* pTokenizer)->delimiter)
    {
        SafeFreeBlock((void **) &(* pTokenizer)->delimiter);
    }

	/*
	** release the tokenizer control structure
	*/

    SafeFreeBlock((void **) pTokenizer);

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetTokenizerMember
(
    motelTokenizerHandle pTokenizer,
	motelTokenizerMember pMember,
	const void * pValue
)
{
    /*
    ** there is no tokenizer object
    */

	if (NULL == pTokenizer)
	{
		return (FALSE);
	}

	pTokenizer->result = motelResult_OK;

	/*
	** node cursor navigation
	*/

	switch (pMember)
	{
        case motelTokenizerMember__NextCharacter:

            /*
            ** Set attribute
            */

            pTokenizer->_NextCharacter = (_MotelNextCharacter) pValue;

			return (TRUE);
	}

	if (NULL == pValue)
	{
		pTokenizer->result = motelResult_NullPointer;

		return (FALSE);
	}

	switch (pMember)
	{
	}

	pTokenizer->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetTokenizerMember
(
    motelTokenizerHandle pTokenizer,
	motelTokenizerMember pMember,
	void * pValue
)
{
    /*
    ** there is no tokenizer object
    */

	if (NULL == pTokenizer)
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
	** result code is a special case because we want to set a result code for GetTokenizerMember()
	*/

    if (motelTokenizerMember_Result == pMember)
    {
		* (motelResult *) pValue = pTokenizer->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pTokenizer->result = motelResult_OK;

	switch (pMember)
	{
		case motelTokenizerMember_Size:

            * (size_t *) pValue = pTokenizer->size;

			return (TRUE);

        case motelTokenizerMember__NextCharacter:

             * (_MotelNextCharacter *) pValue = pTokenizer->_NextCharacter;

            return (TRUE);
	}

	pTokenizer->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION NextTokenizerToken
(
    motelTokenizerHandle pTokenizer
)
{
    byte * lByte = (byte *) pTokenizer->token;

    for (;;)
    {
        pTokenizer->_NextCharacter(pTokenizer->StreamObject, lByte);

        lByte++;

        for (;;)
        {
            if (EqualStringsi(pTokenizer->delimiterList, (char *) pTokenizer->StreamObject))
            {
                return (TRUE);
            }
        }
    }

    return (FALSE);
}
