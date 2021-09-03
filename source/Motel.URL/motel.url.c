/*----------------------------------------------------------------------------
  Motel URL
 
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

/*----------------------------------------------------------------------------
  Motel URL application programmer's interface (API) implementation file
  ----------------------------------------------------------------------------*/

#include "motel.url.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.url.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateUrl
(
    motelUrlHandle pUrl
)
{
    if (* CC_STRING_TERMINATOR == * pUrl->Scheme)
    {
        pUrl->result = motelResult_RequiredMember;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR == * pUrl->SchemeDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Password)
    {
        if (* CC_STRING_TERMINATOR == * pUrl->PasswordDelimiter)
        {
            pUrl->result = motelResult_UndefinedDelimiter;

            return (FALSE);
        }

        if (* CC_STRING_TERMINATOR == * pUrl->Username)
        {
            pUrl->result = motelResult_DependentMember;

            return (FALSE);
        }
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Username && * CC_STRING_TERMINATOR == * pUrl->CredentialsDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR == * pUrl->Host)
    {
        pUrl->result = motelResult_RequiredMember;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Port && * CC_STRING_TERMINATOR == * pUrl->PortDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR == * pUrl->Path && (* CC_STRING_TERMINATOR != * pUrl->File || * CC_STRING_TERMINATOR != * pUrl->Extension))
    {
        pUrl->result = motelResult_DependentMember;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->File && * CC_STRING_TERMINATOR == * pUrl->FileDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Extension && * CC_STRING_TERMINATOR == * pUrl->ExtensionDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Query && * CC_STRING_TERMINATOR == * pUrl->QueryDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    if (* CC_STRING_TERMINATOR != * pUrl->Fragment && * CC_STRING_TERMINATOR == * pUrl->FragmentDelimiter)
    {
        pUrl->result = motelResult_UndefinedDelimiter;

        return (FALSE);
    }

    pUrl->result = motelResult_OK;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructUrl
(
    motelUrlHandle * pUrl,
    char * pUniformResourceLocator
)
{
	/*
	** allocate the URL control structure
	*/

    if (!SafeMallocBlock((void **) pUrl, sizeof(motelUrl)))
    {
        return (FALSE);
    }

	/*
	** initialize the URL control structure
	*/

	(* pUrl)->result = motelResult_OK;

    CopyString(MOTEL_SCHEME_DELIMITER, (* pUrl)->SchemeDelimiter, sizeof((* pUrl)->SchemeDelimiter));
    CopyString(MOTEL_PASSWORD_DELIMITER, (* pUrl)->PasswordDelimiter, sizeof((* pUrl)->PasswordDelimiter));
    CopyString(MOTEL_CREDENTIALS_DELIMITER, (* pUrl)->CredentialsDelimiter, sizeof((* pUrl)->CredentialsDelimiter));
    CopyString(MOTEL_PORT_DELIMITER, (* pUrl)->PortDelimiter, sizeof((* pUrl)->PortDelimiter));
    CopyString(MOTEL_FILE_DELIMITER, (* pUrl)->FileDelimiter, sizeof((* pUrl)->FileDelimiter));
    CopyString(MOTEL_EXTENSION_DELIMITER, (* pUrl)->ExtensionDelimiter, sizeof((* pUrl)->ExtensionDelimiter));
    CopyString(MOTEL_QUERY_DELIMITER, (* pUrl)->QueryDelimiter, sizeof((* pUrl)->QueryDelimiter));
    CopyString(MOTEL_FRAGMENT_DELIMITER, (* pUrl)->FragmentDelimiter, sizeof((* pUrl)->FragmentDelimiter));

    if (NULL == pUniformResourceLocator)
    {
        * (* pUrl)->Scheme = * CC_STRING_TERMINATOR;
        * (* pUrl)->Username = * CC_STRING_TERMINATOR;
        * (* pUrl)->Password = * CC_STRING_TERMINATOR;
        * (* pUrl)->Host = * CC_STRING_TERMINATOR;
        * (* pUrl)->Port = * CC_STRING_TERMINATOR;
        * (* pUrl)->Path = * CC_STRING_TERMINATOR;
        * (* pUrl)->File = * CC_STRING_TERMINATOR;
        * (* pUrl)->Extension = * CC_STRING_TERMINATOR;
        * (* pUrl)->Query = * CC_STRING_TERMINATOR;
        * (* pUrl)->Fragment = * CC_STRING_TERMINATOR;
    }
    else
    {
        ParseFragment((* pUrl), ParseQuery((* pUrl), ParsePath((* pUrl), ParseAuthority((* pUrl), ParseScheme((* pUrl), pUniformResourceLocator)))));
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructUrl
(
    motelUrlHandle * pUrl
)
{
    /*
    ** there is no URL
    */

    if (NULL == pUrl || NULL == * pUrl)
	{
		return (FALSE);
	}

	/*
	** release the URL control structure
	*/

    SafeFreeBlock((void **) pUrl);

	return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetUrlMember
(
    motelUrlHandle pUrl,
	motelUrlMember pMember,
	const void * pValue
)
{
    /*
    ** there is no URL object
    */

	if (NULL == pUrl)
	{
		return (FALSE);
	}

    /*
    ** no input parameter
    */

	if (NULL == pValue)
	{
		pUrl->result = motelResult_NullPointer;

		return (FALSE);
	}

    /*
    ** set member
    */

	pUrl->result = motelResult_OK;

	switch (pMember)
	{
		case motelUrlMember_Url:

            ParseFragment(pUrl, ParseQuery(pUrl, ParsePath(pUrl, ParseAuthority(pUrl, ParseScheme(pUrl, (char *) pValue)))));

			return (TRUE);

        case motelUrlMember_Scheme:

            CopyString((char *) pValue, pUrl->Scheme, sizeof(pUrl->Scheme));

			return (TRUE);

        case motelUrlMember_SchemeDelimiter:

            CopyString((char *) pValue, pUrl->SchemeDelimiter, sizeof(pUrl->SchemeDelimiter));

			return (TRUE);

        case motelUrlMember_Authority:

            ParsePort(pUrl, ParseHost(pUrl, ParseCredentials(pUrl, (char *) pValue)));

			return (TRUE);

        case motelUrlMember_Credentials:

            ParsePassword(pUrl, ParseUsername(pUrl, (char *) pValue));

			return (TRUE);

        case motelUrlMember_Username:

            CopyString((char *) pValue, pUrl->Username, sizeof(pUrl->Username));

			return (TRUE);

        case motelUrlMember_PasswordDelimiter:

            CopyString((char *) pValue, pUrl->PasswordDelimiter, sizeof(pUrl->PasswordDelimiter));

			return (TRUE);

        case motelUrlMember_Password:

            CopyString((char *) pValue, pUrl->Password, sizeof(pUrl->Password));

			return (TRUE);

        case motelUrlMember_CredentialsDelimiter:

            CopyString((char *) pValue, pUrl->CredentialsDelimiter, sizeof(pUrl->CredentialsDelimiter));

			return (TRUE);

		case motelUrlMember_Host:

            CopyString((char *) pValue, pUrl->Host, sizeof(pUrl->Host));

			return (TRUE);

        case motelUrlMember_PortDelimiter:

            CopyString((char *) pValue, pUrl->PortDelimiter, sizeof(pUrl->PortDelimiter));

			return (TRUE);

        case motelUrlMember_Port:

            CopyString((char *) pValue, pUrl->Port, sizeof(pUrl->Port));

			return (TRUE);

		case motelUrlMember_Path:

            ParsePath(pUrl, (char *) pValue);

			return (TRUE);

		case motelUrlMember_FileDelimiter:

            CopyString((char *) pValue, pUrl->FileDelimiter, sizeof(pUrl->FileDelimiter));

			return (TRUE);

		case motelUrlMember_File:

            ParseFile(pUrl, (char *) pValue);

			return (TRUE);

		case motelUrlMember_ExtensionDelimiter:

            CopyString((char *) pValue, pUrl->ExtensionDelimiter, sizeof(pUrl->ExtensionDelimiter));

			return (TRUE);

		case motelUrlMember_Extension:

            CopyString((char *) pValue, pUrl->Extension, sizeof(pUrl->Extension));

			return (TRUE);

		case motelUrlMember_QueryDelimiter:

            CopyString((char *) pValue, pUrl->QueryDelimiter, sizeof(pUrl->QueryDelimiter));

			return (TRUE);

		case motelUrlMember_Query:

            CopyString((char *) pValue, pUrl->Query, sizeof(pUrl->Query));

			return (TRUE);

		case motelUrlMember_FragmentDelimiter:

            CopyString((char *) pValue, pUrl->FragmentDelimiter, sizeof(pUrl->FragmentDelimiter));

			return (TRUE);

		case motelUrlMember_Fragment:

            CopyString((char *) pValue, pUrl->Fragment, sizeof(pUrl->Fragment));

			return (TRUE);
	}

	pUrl->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetUrlMember
(
    motelUrlHandle pUrl,
	motelUrlMember pMember,
	void * pValue
)
{
    /*
    ** there is no URL object
    */

	if (NULL == pUrl)
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
	** result code is a special case because we want to set a result code for GetUrlMember()
	*/

    if (motelUrlMember_Result == pMember)
    {
		* (motelUrlMember *) pValue = pUrl->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pUrl->result = motelResult_OK;

	switch (pMember)
	{
		case motelUrlMember_Url:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleUrl(pUrl, (char *) pValue);

            return (TRUE);

        case motelUrlMember_Scheme:

            CopyString(pUrl->Scheme, (char *) pValue, sizeof(pUrl->Scheme));

			return (TRUE);

        case motelUrlMember_SchemeDelimiter:

            CopyString(pUrl->SchemeDelimiter, (char *) pValue, sizeof(pUrl->SchemeDelimiter));

			return (TRUE);

        case motelUrlMember_Authority:
            
            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleAuthority(pUrl, (char *) pValue);

			return (TRUE);

        case motelUrlMember_Credentials:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleCredentials(pUrl, (char *) pValue);

            return (TRUE);

        case motelUrlMember_Username:

            CopyString(pUrl->Username, (char *) pValue, sizeof(pUrl->Username));

			return (TRUE);

        case motelUrlMember_PasswordDelimiter:

            CopyString(pUrl->PasswordDelimiter, (char *) pValue, sizeof(pUrl->PasswordDelimiter));

			return (TRUE);

        case motelUrlMember_Password:

            CopyString(pUrl->Password, (char *) pValue, sizeof(pUrl->Password));

			return (TRUE);

        case motelUrlMember_CredentialsDelimiter:

            CopyString(pUrl->CredentialsDelimiter, (char *) pValue, sizeof(pUrl->CredentialsDelimiter));

			return (TRUE);

		case motelUrlMember_Host:

            CopyString(pUrl->Host, (char *) pValue, sizeof(pUrl->Host));

			return (TRUE);

        case motelUrlMember_PortDelimiter:

            CopyString(pUrl->PortDelimiter, (char *) pValue, sizeof(pUrl->PortDelimiter));

			return (TRUE);

        case motelUrlMember_Port:

            CopyString(pUrl->Port, (char *) pValue, sizeof(pUrl->Port));

			return (TRUE);

		case motelUrlMember_Path:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssemblePath(pUrl, (char *) pValue);

			return (TRUE);

		case motelUrlMember_FileDelimiter:

            CopyString(pUrl->FileDelimiter, (char *) pValue, sizeof(pUrl->FileDelimiter));

			return (TRUE);

		case motelUrlMember_File:

            * (char *) pValue = * CC_STRING_TERMINATOR;

            AssembleFile(pUrl, (char *) pValue);

			return (TRUE);

		case motelUrlMember_ExtensionDelimiter:

            CopyString(pUrl->ExtensionDelimiter, (char *) pValue, sizeof(pUrl->ExtensionDelimiter));

			return (TRUE);

		case motelUrlMember_Extension:

            CopyString(pUrl->Extension, (char *) pValue, sizeof(pUrl->Extension));

			return (TRUE);

		case motelUrlMember_QueryDelimiter:

            CopyString(pUrl->QueryDelimiter, (char *) pValue, sizeof(pUrl->QueryDelimiter));

			return (TRUE);

		case motelUrlMember_Query:

            CopyString(pUrl->Query, (char *) pValue, sizeof(pUrl->Query));

			return (TRUE);

		case motelUrlMember_FragmentDelimiter:

            CopyString(pUrl->FragmentDelimiter, (char *) pValue, sizeof(pUrl->FragmentDelimiter));

			return (TRUE);

		case motelUrlMember_Fragment:

            CopyString(pUrl->Fragment, (char *) pValue, sizeof(pUrl->Fragment));

			return (TRUE);
	}

	pUrl->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushUrlByte
(
   motelUrlHandle pUrl,
   byte pByte
)
{
    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullUrlByte
(
    motelUrlHandle pHrr,
	byte * pValue
)
{
    * pValue = ' ';

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static char * ParseScheme
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Scheme, pSource, sizeof(pUrl->Scheme), 0, 1, pUrl->SchemeDelimiter, 1));
}

static char * ParseAuthority
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    char lAuthority[MOTEL_AUTHORITY_SIZE];

    char * lRemainder;

    lRemainder = ParseString(lAuthority, pSource, sizeof(lAuthority), 1, pUrl->SchemeDelimiter, 1, 1, pUrl->FileDelimiter, MOTEL_OPTIONAL);

    ParsePort(pUrl, ParseHost(pUrl, ParseCredentials(pUrl, lAuthority)));

    return (lRemainder);
}

static char * ParseCredentials
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    char lCredentials[MOTEL_CREDENTIALS_SIZE];

    char * lRemainder;

    lRemainder = ParseString(lCredentials, pSource, sizeof(lCredentials), 0, 1, pUrl->CredentialsDelimiter, 1);

    ParsePassword(pUrl, ParseUsername(pUrl, lCredentials));

    return (lRemainder);
}

static char * ParseUsername
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Username, pSource, sizeof(pUrl->Username), 0, 1, pUrl->PasswordDelimiter, MOTEL_OPTIONAL));
}

static char * ParsePassword
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Password, pSource, sizeof(pUrl->Password), 1, pUrl->PasswordDelimiter, 1, 0));
}

static char * ParseHost
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Host, pSource, sizeof(pUrl->Host), 1, pUrl->CredentialsDelimiter, MOTEL_OPTIONAL, 1, pUrl->PortDelimiter, MOTEL_OPTIONAL));
}

static char * ParsePort
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Port, pSource, sizeof(pUrl->Port), 1, pUrl->PortDelimiter, 1, 0));
}

static char * ParsePath
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pUrl->Path, pSource, sizeof(pUrl->Path), 0, 2, pUrl->QueryDelimiter, pUrl->FragmentDelimiter, MOTEL_OPTIONAL);

    ParseFile(pUrl, pUrl->Path);
    
    return (lRemainder);
}

static char * ParseFile
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    char * lRemainder;

    lRemainder = ParseString(pUrl->File, pSource, sizeof(pUrl->File), 1, pUrl->PortDelimiter, MOTEL_LAST_INSTANCE, 0);

    ParseExtension(pUrl, pUrl->File);
    
    return (lRemainder);
}

static char * ParseExtension
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Extension, pSource, sizeof(pUrl->Extension), 1, pUrl->ExtensionDelimiter, 1, 0));
}

static char * ParseQuery
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Query, pSource, sizeof(pUrl->Query), 1, pUrl->QueryDelimiter, 1, 1, pUrl->FragmentDelimiter, MOTEL_OPTIONAL));
}

static char * ParseFragment
(
    motelUrlHandle pUrl,
    char * pSource
)
{
    return (ParseString(pUrl->Fragment, pSource, sizeof(pUrl->Fragment), 1, pUrl->FragmentDelimiter, 1, 0));
}

static char * AssembleUrl
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    AssembleScheme(pUrl, pDestination);

    AssembleAuthority(pUrl, pDestination);

    AssemblePath(pUrl, pDestination);

    AssembleQuery(pUrl, pDestination);

    AssembleFragment(pUrl, pDestination);

    return (pDestination);
}

static char * AssembleScheme
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    AppendString(pUrl->Scheme, pDestination, MOTEL_URL_SIZE);
    AppendString(pUrl->SchemeDelimiter, pDestination, MOTEL_URL_SIZE);

    return (pDestination);
}

static char * AssembleAuthority
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    AssembleCredentials(pUrl, pDestination);

    if (* CC_STRING_TERMINATOR != * pUrl->Username)
    {
        AppendString(pUrl->CredentialsDelimiter, pDestination, MOTEL_URL_SIZE);
    }

    AppendString(pUrl->Host, pDestination, MOTEL_URL_SIZE);

    if (* CC_STRING_TERMINATOR != * pUrl->Port)
    {
        AppendString(pUrl->PortDelimiter, pDestination, MOTEL_URL_SIZE);
        AppendString(pUrl->Port, pDestination, MOTEL_URL_SIZE);
    }

    return (pDestination);
}

static char * AssembleCredentials
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pUrl->Username)
    {
        AppendString(pUrl->Username, pDestination, MOTEL_URL_SIZE);
        
        if (* CC_STRING_TERMINATOR != * pUrl->Password)
        {
            AppendString(pUrl->PasswordDelimiter, pDestination, MOTEL_URL_SIZE);
            AppendString(pUrl->Password, pDestination, MOTEL_URL_SIZE);
        }
    }

    return (pDestination);
}

static char * AssemblePath
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    AppendString(pUrl->Path, pDestination, MOTEL_URL_SIZE);

    AssembleFile(pUrl, pDestination);

    return (pDestination);
}

static char * AssembleFile
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pUrl->File)
    {
        AppendString(pUrl->File, pDestination, MOTEL_URL_SIZE);
    }
        
    AssembleExtension(pUrl, pDestination);

    return (pDestination);
}

static char * AssembleExtension
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pUrl->Extension)
    {
        AppendString(pUrl->ExtensionDelimiter, pDestination, MOTEL_URL_SIZE);
        AppendString(pUrl->Extension, pDestination, MOTEL_URL_SIZE);
    }

    return (pDestination);
}

static char * AssembleQuery
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pUrl->Query)
    {
        AppendString(pUrl->QueryDelimiter, pDestination, MOTEL_URL_SIZE);
        AppendString(pUrl->Query, pDestination, MOTEL_URL_SIZE);
    }

    return (pDestination);
}

static char * AssembleFragment
(
    motelUrlHandle pUrl,
    char * pDestination
)
{
    if (* CC_STRING_TERMINATOR != * pUrl->Fragment)
    {
        AppendString(pUrl->FragmentDelimiter, pDestination, MOTEL_URL_SIZE);
        AppendString(pUrl->Fragment, pDestination, MOTEL_URL_SIZE);
    }

    return (pDestination);
}
