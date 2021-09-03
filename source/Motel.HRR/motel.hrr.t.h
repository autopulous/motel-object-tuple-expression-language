/*----------------------------------------------------------------------------
  Motel HRR
 
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

#ifndef MOTEL_HRR_T_H
#define MOTEL_HRR_T_H

/*--------------------------------------------------------------------------------------------------*/
/*                                 Hierarchical Resource Reference (HRR)                            */
/*                                                                                                  */
/* 154.211.100.76:8080:https$delta/ws/listserver0001@johnhart:mysecret?weekly=on;when=friday#public */
/*                                               or                                                 */
/* org.speakhuman:8080:https$/beta/ws/script.motel@johnhart:mysecret?debug=on;action=parse#strict   */
/* \_______________________/\____________________/\________________/\____________________/\_____/   */
/*          channel                resource           credentials            query        fragment  */
/* \____________/\___/\____/                      \_______/\_______/                                */
/*      host     port format                       identity password                                */
/*--------------------------------------------------------------------------------------------------*/

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

typedef enum motelHrrMember motelHrrMember;

enum motelHrrMember
{
	motelHrrMember_Result,               /*!< Data type: (motelResult *)
                                              Description: The method result code */

    motelHrrMember_Device,               /*!< Data type: (char *)
                                              Description: Device portion of an HRR (includes Host & Port) */

    motelHrrMember_Host,                 /*!< Data type: (char *)
                                              Description: Host portion of an HRR device */

    motelHrrMember_PortDelimiter,        /*!< Data type: (char *)
                                              Description: Delimits the Port within an HRR device (e.g. :)  */

    motelHrrMember_Port,                 /*!< Data type: (char *)
                                              Description: Port number portion of an HRR device */

    motelHrrMember_SchemeDelimiter,      /*!< Data type: (char *)
                                              Description: Delimits the Format within an HRR device (e.g. $) */

    motelHrrMember_Scheme,               /*!< Data type: (char *)
                                              Description: Scheme portion of an HRR device */

    motelHrrMember_ResourceDelimiter,    /*!< Data type: (char *)
                                              Description: Delimits the Resource within an HRR (e.g. /) */

    motelHrrMember_Resource,             /*!< Data type: (char *)
                                              Description: Resource portion of a HRR (includes Path & Name) */

    motelHrrMember_CredentialsDelimiter, /*!< Data type: (char *)
                                              Description: Delimits the Credentials within an HRR (e.g. @) */

    motelHrrMember_Credentials,          /*!< Data type: (char *)
                                              Description: Credential portion of an HRR (includes Identity & Password) */

    motelHrrMember_Identity,             /*!< Data type: (char *)
                                              Description: Identity portion of an HRR credential */

    motelHrrMember_PasswordDelimiter,    /*!< Data type: (char *)
                                              Description: Delimits the Password within a HRR credential (e.g. :) */

    motelHrrMember_Password,             /*!< Data type: (char *)
                                              Description: Password portion of an HRR credential */

    motelHrrMember_QueryDelimiter,       /*!< Data type: (char *)
                                              Description: Delimits the Query string portion of an HRR (e.g. ?) */

    motelHrrMember_Query,                /*!< Data type: (char *)
                                              Description: Query string portion of an HRR */

    motelHrrMember_FragmentDelimiter,    /*!< Data type: (char *)
                                              Description: Delimits the Fragment portion of an HRR (e.g. #) */

    motelHrrMember_Fragment,             /*!< Data type: (char *)
                                              Description: Fragment portion of an HRR */

	motelHrrMember_Hrr,                  /*!< Data type: (char *)
                                              Description: HRR (includes Device, Resource, Credentials, Query & Fragment) */

	motelHrrMember_
};

typedef struct motelHrr motelHrr;
typedef MUTABILITY motelHrr * motelHrrHandle;

struct motelHrr
{
	MUTABILITY motelResult result;

    MUTABILITY char Host[MOTEL_HOST_SIZE];
    MUTABILITY char PortDelimiter[MOTEL_PORT_DELIMITER_SIZE];
    MUTABILITY char Port[MOTEL_PORT_SIZE];
    MUTABILITY char SchemeDelimiter[MOTEL_SCHEME_DELIMITER_SIZE];
    MUTABILITY char Scheme[MOTEL_SCHEME_SIZE];
    MUTABILITY char ResourceDelimiter[MOTEL_RESOURCE_REFERENCE_DELIMITER_SIZE];
    MUTABILITY char Resource[MOTEL_RESOURCE_REFERENCE_SIZE];
    MUTABILITY char CredentialsDelimiter[MOTEL_CREDENTIALS_DELIMITER_SIZE];
    MUTABILITY char Identity[MOTEL_IDENTITY_SIZE];
    MUTABILITY char PasswordDelimiter[MOTEL_PASSWORD_DELIMITER_SIZE];
    MUTABILITY char Password[MOTEL_PASSWORD_SIZE];
    MUTABILITY char QueryDelimiter[MOTEL_QUERY_DELIMITER_SIZE];
    MUTABILITY char Query[MOTEL_QUERY_SIZE];
    MUTABILITY char FragmentDelimiter[MOTEL_FRAGMENT_DELIMITER_SIZE];
    MUTABILITY char Fragment[MOTEL_FRAGMENT_SIZE];
};

#endif
