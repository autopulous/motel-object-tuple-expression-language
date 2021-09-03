/*----------------------------------------------------------------------------
  Motel HRR
  
  library implementation file
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

#include "motel.hrr.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.hrr.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateHrr
(
    motelHrrHandle pHrr
)
{
    if (* CC_STRING_TERMINATOR == * pHrr->Host)
    {
        pHrr->result = motelResult_RequiredMember;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Port && * CC_STRING_TERMINATOR == * pHrr->PortDelimiter)
    {
        pHrr->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR == * pHrr->Scheme)
    {
        pHrr->result = motelResult_RequiredMember;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Scheme && * CC_STRING_TERMINATOR == * pHrr->SchemeDelimiter)
    {
        pHrr->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Identity && * CC_STRING_TERMINATOR == * pHrr->CredentialsDelimiter)
    {
        pHrr->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Password)
    {
        if (* CC_STRING_TERMINATOR == * pHrr->PasswordDelimiter)
        {
            pHrr->result = motelResult_UndefinedDelimiter;

            return (FALSE);
        }

        if (* CC_STRING_TERMINATOR == * pHrr->Identity)
        {
            pHrr->result = motelResult_DependentMember;

            return (FALSE);
        }
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Query && * CC_STRING_TERMINATOR == * pHrr->QueryDelimiter)
    {
        pHrr->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pHrr->Fragment && * CC_STRING_TERMINATOR == * pHrr->FragmentDelimiter)
    {
        pHrr->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    pHrr->result = motelResult_OK;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructHrr
(
    motelHrrHandle * pHrr,
    char * pHierarchicalResourceReference
)
{
	/*
	** allocate the HRR control structure
	*/

    if (!SafeMallocBlock((void **) pHrr, sizeof(motelHrr)))
    {
        return (FALSE);
    }

	/*
	** initialize the HRR control structure
	*/

	(* pHrr)->result = motelResult_OK;

    CopyString(MOTEL_PORT_DELIMITER, (* pHrr)->PortDelimiter, sizeof((* pHrr)->PortDelimiter));
    CopyString(MOTEL_SCHEME_DELIMITER, (* pHrr)->SchemeDelimiter, sizeof((* pHrr)->SchemeDelimiter));
    CopyString(MOTEL_RESOURCE_DELIMITER, (* pHrr)->ResourceDelimiter, sizeof((* pHrr)->ResourceDelimiter));
    CopyString(MOTEL_CREDENTIALS_DELIMITER, (* pHrr)->CredentialsDelimiter, sizeof((* pHrr)->CredentialsDelimiter));
    CopyString(MOTEL_PASSWORD_DELIMITER, (* pHrr)->PasswordDelimiter, sizeof((* pHrr)->PasswordDelimiter));
    CopyString(MOTEL_QUERY_DELIMITER, (* pHrr)->QueryDelimiter, sizeof((* pHrr)->QueryDelimiter));
    CopyString(MOTEL_FRAGMENT_DELIMITER, (* pHrr)->FragmentDelimiter, sizeof((* pHrr)->FragmentDelimiter));

    if (NULL == pHierarchicalResourceReference)
    {
        * (* pHrr)->Host = * CC_STRING_TERMINATOR;
        * (* pHrr)->Port = * CC_STRING_TERMINATOR;
        * (* pHrr)->Scheme = * CC_STRING_TERMINATOR;
        * (* pHrr)->Resource = * CC_STRING_TERMINATOR;
        * (* pHrr)->Identity = * CC_STRING_TERMINATOR;
        * (* pHrr)->Password = * CC_STRING_TERMINATOR;
        * (* pHrr)->Query = * CC_STRING_TERMINATOR;
        * (* pHrr)->Fragment = * CC_STRING_TERMINATOR;
    }
    else
    {
        ParseFragment((* pHrr), ParseQuery((* pHrr), ParseCredentials((* pHrr), ParseResource((* pHrr), ParseScheme((* pHrr), ParseDevice((* pHrr), pHierarchicalResourceReference))))));
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructHrr
(
    motelHrrHandle * pHrr
)
{
    /*
    ** there is no HRR
    */

    if (NULL == pHrr || NULL == * pHrr)
	{
		return (FALSE);
	}

	/*
	** release the HRR control structure
	*/

    SafeFreeBlock((void **) pHrr);

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetHrrMember
(
    motelHrrHandle pHrr,
	motelHrrMember pMember,
	const void * pValue
)
{
    /*
    ** there is no HRR object
    */

	if (NULL == pHrr)
	{
		return (FALSE);
	}

    /*
    ** no input parameter
    */

	if (NULL == pValue)
	{
		pHrr->result = motelResult_NullPointer;

		return (FALSE);
	}

    /*
    ** set member
    */

	pHrr->result = motelResult_OK;

	switch (pMember)
	{
        case motelHrrMember_Hrr:

            ParseFragment(pHrr, ParseQuery(pHrr, ParseCredentials(pHrr, ParseResource(pHrr, ParseScheme(pHrr, ParseDevice(pHrr, (char *) pValue))))));

			return (TRUE);

        case motelHrrMember_Device:

            ParseScheme(pHrr, ParsePort(pHrr, ParseHost(pHrr, (char *) pValue)));

			return (TRUE);

		case motelHrrMember_Host:

            CopyString((char *) pValue, pHrr->Host, sizeof(pHrr->Host));

			return (TRUE);

        case motelHrrMember_PortDelimiter:

            CopyString((char *) pValue, pHrr->PortDelimiter, sizeof(pHrr->PortDelimiter));

			return (TRUE);

        case motelHrrMember_Port:

            CopyString((char *) pValue, pHrr->Port, sizeof(pHrr->Port));

			return (TRUE);

        case motelHrrMember_SchemeDelimiter:

            CopyString((char *) pValue, pHrr->SchemeDelimiter, sizeof(pHrr->SchemeDelimiter));

			return (TRUE);

        case motelHrrMember_Scheme:

            CopyString((char *) pValue, pHrr->Scheme, sizeof(pHrr->Scheme));

			return (TRUE);

		case motelHrrMember_ResourceDelimiter:

            CopyString((char *) pValue, pHrr->ResourceDelimiter, sizeof(pHrr->ResourceDelimiter));

			return (TRUE);

        case motelHrrMember_Resource:

            CopyString((char *) pValue, pHrr->Resource, sizeof(pHrr->Resource));

			return (TRUE);

        case motelHrrMember_CredentialsDelimiter:

            CopyString((char *) pValue, pHrr->CredentialsDelimiter, sizeof(pHrr->CredentialsDelimiter));

			return (TRUE);

        case motelHrrMember_Credentials:

            ParsePassword(pHrr, ParseIdentity(pHrr, (char *) pValue));

			return (TRUE);

        case motelHrrMember_Identity:

            CopyString((char *) pValue, pHrr->Identity, sizeof(pHrr->Identity));

			return (TRUE);

        case motelHrrMember_PasswordDelimiter:

            CopyString((char *) pValue, pHrr->PasswordDelimiter, sizeof(pHrr->PasswordDelimiter));

			return (TRUE);

        case motelHrrMember_Password:

            CopyString((char *) pValue, pHrr->Password, sizeof(pHrr->Password));

			return (TRUE);

		case motelHrrMember_QueryDelimiter:

            CopyString((char *) pValue, pHrr->QueryDelimiter, sizeof(pHrr->QueryDelimiter));

			return (TRUE);

		case motelHrrMember_Query:

            CopyString((char *) pValue, pHrr->Query, sizeof(pHrr->Query));

			return (TRUE);

		case motelHrrMember_FragmentDelimiter:

            CopyString((char *) pValue, pHrr->FragmentDelimiter, sizeof(pHrr->FragmentDelimiter));

			return (TRUE);

		case motelHrrMember_Fragment:

            CopyString((char *) pValue, pHrr->Fragment, sizeof(pHrr->Fragment));

			return (TRUE);
	}

	pHrr->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetHrrMember
(
    motelHrrHandle pHrr,
	motelHrrMember pMember,
	void * pValue
)
{
    /*
    ** there is no HRR object
    */

	if (NULL == pHrr)
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
	** result code is a special case because we want to set a result code for GetHrrMember()
	*/

    if (motelHrrMember_Result == pMember)
    {
		* (motelHrrMember *) pValue = pHrr->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pHrr->result = motelResult_OK;

	switch (pMember)
	{
		case motelHrrMember_Hrr:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleHrr(pHrr, (char *) pValue);

            return (TRUE);

        case motelHrrMember_Device:
            
            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleDevice(pHrr, (char *) pValue);

			return (TRUE);

		case motelHrrMember_Host:

            CopyString(pHrr->Host, (char *) pValue, sizeof(pHrr->Host));

			return (TRUE);

        case motelHrrMember_PortDelimiter:

            CopyString(pHrr->PortDelimiter, (char *) pValue, sizeof(pHrr->PortDelimiter));

			return (TRUE);

        case motelHrrMember_Port:

            CopyString(pHrr->Port, (char *) pValue, sizeof(pHrr->Port));

			return (TRUE);

        case motelHrrMember_SchemeDelimiter:

            CopyString(pHrr->SchemeDelimiter, (char *) pValue, sizeof(pHrr->SchemeDelimiter));

			return (TRUE);

        case motelHrrMember_Scheme:
            
            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleScheme(pHrr, (char *) pValue);

			return (TRUE);

		case motelHrrMember_ResourceDelimiter:

            CopyString(pHrr->ResourceDelimiter, (char *) pValue, sizeof(pHrr->ResourceDelimiter));

			return (TRUE);

		case motelHrrMember_Resource:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleResource(pHrr, (char *) pValue);

			return (TRUE);

        case motelHrrMember_CredentialsDelimiter:

            CopyString(pHrr->CredentialsDelimiter, (char *) pValue, sizeof(pHrr->CredentialsDelimiter));

			return (TRUE);

        case motelHrrMember_Credentials:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleCredentials(pHrr, (char *) pValue);

            return (TRUE);

        case motelHrrMember_Identity:

            CopyString(pHrr->Identity, (char *) pValue, sizeof(pHrr->Identity));

			return (TRUE);

        case motelHrrMember_PasswordDelimiter:

            CopyString(pHrr->PasswordDelimiter, (char *) pValue, sizeof(pHrr->PasswordDelimiter));

			return (TRUE);

        case motelHrrMember_Password:

            CopyString(pHrr->Password, (char *) pValue, sizeof(pHrr->Password));

			return (TRUE);

		case motelHrrMember_QueryDelimiter:

            CopyString(pHrr->QueryDelimiter, (char *) pValue, sizeof(pHrr->QueryDelimiter));

			return (TRUE);

		case motelHrrMember_Query:

            CopyString(pHrr->Query, (char *) pValue, sizeof(pHrr->Query));

			return (TRUE);

		case motelHrrMember_FragmentDelimiter:

            CopyString(pHrr->FragmentDelimiter, (char *) pValue, sizeof(pHrr->FragmentDelimiter));

			return (TRUE);

		case motelHrrMember_Fragment:

            CopyString(pHrr->Fragment, (char *) pValue, sizeof(pHrr->Fragment));

			return (TRUE);
	}

	pHrr->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushHrrByte
(
   motelHrrHandle pHrr,
   byte pByte
)
{
    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullHrrByte
(
    motelHrrHandle pHrr,
	byte * pValue
)
{
    * pValue = ' ';

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static char * ParseDevice
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char lDevice[MOTEL_DEVICE_SIZE];

    char * lRemainder;

    lRemainder = ParseString(lDevice, pSource, sizeof(lDevice), 0, 1, pHrr->SchemeDelimiter, MOTEL_LAST_INSTANCE);

    ParsePort(pHrr, ParseHost(pHrr, lDevice));

    return (lRemainder);
}

static char * ParseScheme
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Scheme, pSource, sizeof(pHrr->Scheme), 1, pHrr->SchemeDelimiter, MOTEL_OPTIONAL, 1, pHrr->ResourceDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * ParseResource
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Resource, pSource, sizeof(pHrr->Resource), 1, pHrr->ResourceDelimiter, MOTEL_OPTIONAL, 3, pHrr->CredentialsDelimiter, pHrr->QueryDelimiter, pHrr->FragmentDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * ParseCredentials
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char lCredentials[MOTEL_CREDENTIALS_SIZE];

    char * lRemainder;

    lRemainder = ParseString(lCredentials, pSource, sizeof(lCredentials), 1, pHrr->CredentialsDelimiter, MOTEL_OPTIONAL, 2, pHrr->QueryDelimiter, pHrr->FragmentDelimiter, MOTEL_OPTIONAL);

    ParsePassword(pHrr, ParseIdentity(pHrr, lCredentials));

    return (lRemainder);
}

static char * ParseQuery
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Query, pSource, sizeof(pHrr->Query), 1, pHrr->QueryDelimiter, MOTEL_OPTIONAL, 1, pHrr->FragmentDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * ParseFragment
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Fragment, pSource, sizeof(pHrr->Fragment), 1, pHrr->FragmentDelimiter, MOTEL_OPTIONAL, 0);

    return (lRemainder);
}

static char * ParseHost
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Host, pSource, sizeof(pHrr->Host), 0, 1, pHrr->PortDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * ParsePort
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Port, pSource, sizeof(pHrr->Port), 1, pHrr->PortDelimiter, MOTEL_OPTIONAL, 1, pHrr->SchemeDelimiter, MOTEL_OPTIONAL);

    if (!FindClassMemberCharacter(pHrr->Port, CC_LEADING_DECIMAL_DIGIT, 1))
    {
        * pHrr->Port = * CC_STRING_TERMINATOR;

        return (pSource);
    }

    return (lRemainder);
}

static char * ParseIdentity
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Identity, pSource, sizeof(pHrr->Identity), 1, pHrr->CredentialsDelimiter, MOTEL_OPTIONAL, 3, pHrr->PasswordDelimiter, pHrr->QueryDelimiter, pHrr->FragmentDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * ParsePassword
(
    motelHrrHandle pHrr,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pHrr->Password, pSource, sizeof(pHrr->Password), 1, pHrr->PasswordDelimiter, MOTEL_OPTIONAL, 2, pHrr->QueryDelimiter, pHrr->FragmentDelimiter, MOTEL_OPTIONAL);

    return (lRemainder);
}

static char * AssembleHrr
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    AssembleDevice(pHrr, pDestination);

    AssembleScheme(pHrr, pDestination);

    AssembleResource(pHrr, pDestination);

    AssembleCredentials(pHrr, pDestination);

    AssembleQuery(pHrr, pDestination);

    AssembleFragment(pHrr, pDestination);

    return (pDestination);
}

static char * AssembleDevice
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    AppendString(pHrr->Host, pDestination, MOTEL_HRR_SIZE);

    if (* CC_STRING_TERMINATOR != * pHrr->Port)
    {
        AppendString(pHrr->PortDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Port, pDestination, MOTEL_HRR_SIZE);
    }

    return (pDestination);
}

static char * AssembleScheme
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pHrr->Scheme)
    {
        AppendString(pHrr->SchemeDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Scheme, pDestination, MOTEL_HRR_SIZE);
    }

    return (pDestination);
}

static char * AssembleResource
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pHrr->Resource)
    {
        AppendString(pHrr->ResourceDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Resource, pDestination, MOTEL_HRR_SIZE);
    }

    return (pDestination);
}

static char * AssembleCredentials
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pHrr->Identity)
    {
        AppendString(pHrr->CredentialsDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Identity, pDestination, MOTEL_HRR_SIZE);
        
        if (* CC_STRING_TERMINATOR != * pHrr->Password)
        {
            AppendString(pHrr->PasswordDelimiter, pDestination, MOTEL_HRR_SIZE);
            AppendString(pHrr->Password, pDestination, MOTEL_HRR_SIZE);
        }
    }

    return (pDestination);
}

static char * AssembleQuery
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pHrr->Query)
    {
        AppendString(pHrr->QueryDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Query, pDestination, MOTEL_HRR_SIZE);
    }

    return (pDestination);
}

static char * AssembleFragment
(
    motelHrrHandle pHrr,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pHrr->Fragment)
    {
        AppendString(pHrr->FragmentDelimiter, pDestination, MOTEL_HRR_SIZE);
        AppendString(pHrr->Fragment, pDestination, MOTEL_HRR_SIZE);
    }

    return (pDestination);
}
