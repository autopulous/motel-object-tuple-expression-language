/*----------------------------------------------------------------------------
  Motel URL
 
  application programmer's types (APT) header file 
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

#ifndef MOTEL_URL_T_H
#define MOTEL_URL_T_H

/*------------------------------------------------------------------------------------------------------*/
/*                               Uniform Resource Locator (URL) structure                               */
/*                                                                                                      */
/* https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel?debug=on;action=parse#strict  */
/* \___/   \_______________________________________/\___________________/ \___________________/ \____/  */
/* scheme                 authority                     resource path             query        fragment */
/*         \_______________/ \________________/ \__/         \____________/                             */
/*            credentials           host        port         resource name                              */
/*         \______/ \______/                                           \__/                             */
/*         username password                                    resource extension                      */
/*------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*----------------------------------------------------------------------------
  Public macros
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Public members
  ----------------------------------------------------------------------------*/

typedef enum motelUrlMember motelUrlMember;

enum motelUrlMember
{
	motelUrlMember_Result,               /*!< Data type: (motelResult *)
                                              Description: The method result code */

	motelUrlMember_Url,                  /*!< Data type: (char *)
                                              Description: Complete URL */

    motelUrlMember_Scheme,               /*!< Data type: (char *)
                                              Description: Scheme portion of a URL */

    motelUrlMember_SchemeDelimiter,      /*!< Data type: (char *)
                                              Description: Separates the scheme from the rest of the URL (e.g. ://) */

    motelUrlMember_Authority,            /*!< Data type: (char *)
                                              Description: Authority portion of a URL (includes Credentials, Host & Port) */

    motelUrlMember_Credentials,          /*!< Data type: (char *)
                                              Description: Username & Password portion of a URL */

    motelUrlMember_Username,             /*!< Data type: (char *)
                                              Description: Username portion of a URL */

    motelUrlMember_PasswordDelimiter,    /*!< Data type: (char *)
                                              Description: Separates Username & Password within a URL (e.g. :) */

    motelUrlMember_Password,             /*!< Data type: (char *)
                                              Description: Password portion of a URL */

    motelUrlMember_CredentialsDelimiter, /*!< Data type: (char *)
                                              Description: Separates the credentials from the rest of the URL (e.g. @) */

    motelUrlMember_Host,                 /*!< Data type: (char *)
                                              Description: Host portion of a URL */

    motelUrlMember_PortDelimiter,        /*!< Data type: (char *)
                                              Description: Separates Host & Port within a URL (e.g. :)  */

    motelUrlMember_Port,                 /*!< Data type: (char *)
                                              Description: Port number portion of a URL */

    motelUrlMember_Path,                 /*!< Data type: (char *)
                                              Description: Path, file name & file extension portion of a URL */

    motelUrlMember_FileDelimiter,        /*!< Data type: (char *)
                                              Description: Separates path & file name within a URL (e.g. /) */

    motelUrlMember_File,                 /*!< Data type: (char *)
                                              Description: File name & extension portion of a URL */

    motelUrlMember_ExtensionDelimiter,   /*!< Data type: (char *)
                                              Description: Separates file name & extension within a URL (e.g. .) */

    motelUrlMember_Extension,            /*!< Data type: (char *)
                                              Description: File extension portion of a URL */

    motelUrlMember_QueryDelimiter,       /*!< Data type: (char *)
                                              Description: Separates a query string from the rest of the URL (e.g. ?) */

    motelUrlMember_Query,                /*!< Data type: (char *)
                                              Description: Query string portion of a URL */

    motelUrlMember_FragmentDelimiter,    /*!< Data type: (char *)
                                              Description: Separates a fragment from the rest of the URL (e.g. #) */

    motelUrlMember_Fragment,             /*!< Data type: (char *)
                                              Description: Fragment portion of a URL */

	motelUrlMember_
};

typedef struct motelUrl motelUrl;
typedef MUTABILITY motelUrl * motelUrlHandle;

struct motelUrl
{
	MUTABILITY motelResult result;

    MUTABILITY char Scheme[MOTEL_SCHEME_SIZE];
    MUTABILITY char SchemeDelimiter[MOTEL_SCHEME_DELIMITER_SIZE];
    MUTABILITY char Username[MOTEL_USERNAME_SIZE];
    MUTABILITY char PasswordDelimiter[MOTEL_PASSWORD_DELIMITER_SIZE];
    MUTABILITY char Password[MOTEL_PASSWORD_SIZE];
    MUTABILITY char CredentialsDelimiter[MOTEL_CREDENTIALS_DELIMITER_SIZE];
    MUTABILITY char Host[MOTEL_HOST_SIZE];
    MUTABILITY char PortDelimiter[MOTEL_PORT_DELIMITER_SIZE];
    MUTABILITY char Port[MOTEL_PORT_SIZE];
    MUTABILITY char Path[MOTEL_RESOURCE_PATH_SIZE];
    MUTABILITY char FileDelimiter[MOTEL_RESOURCE_NAME_DELIMITER_SIZE];
    MUTABILITY char File[MOTEL_RESOURCE_NAME_SIZE];
    MUTABILITY char ExtensionDelimiter[MOTEL_EXTENSION_DELIMITER_SIZE];
    MUTABILITY char Extension[MOTEL_RESOURCE_EXTENSION_SIZE];
    MUTABILITY char QueryDelimiter[MOTEL_QUERY_DELIMITER_SIZE];
    MUTABILITY char Query[MOTEL_QUERY_SIZE];
    MUTABILITY char FragmentDelimiter[MOTEL_FRAGMENT_DELIMITER_SIZE];
    MUTABILITY char Fragment[MOTEL_FRAGMENT_SIZE];
};

#endif