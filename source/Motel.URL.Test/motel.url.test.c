/*----------------------------------------------------------------------------
  Motel URL Test

  executable implementation file
  ----------------------------------------------------------------------------  
  Copyright 2010-2012 John L. Hart IV. All rights reserved.
 
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
  Standard libraries
  ----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*----------------------------------------------------------------------------
  Public data types
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.String/motel.string.t.h"

#include "../Motel.Url/motel.url.t.h"

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.String/motel.string.i.h"

#include "../Motel.Url/motel.url.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.url.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.url.test.c - Copyright 2010-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
/*                                 Uniform Resource Locator (URL) layout                                  */
/*                                                                                                        */
/* https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel?debug=on;action=parse#strict  */
/* \___/   \_______________________________________/\_____________________/ \___________________/ \____/  */
/* scheme                 authority                           path                  query        fragment */
/*         \_______________/ \________________/ \__/         \____________/                               */
/*            credentials           host        port              file                                    */
/*         \______/ \______/                                           \__/                               */
/*         username password                                         extension                            */
/*--------------------------------------------------------------------------------------------------------*/

char * gUrls[] = 
{
    "https://www.speakhuman.org/script",
    "https://johnhart:mysecret@www.speakhuman.org",
    "https://www.speakhuman.org:8080/script",
    "https://johnhart:mysecret@www.speakhuman.org:8080/script",
    "https://www.speakhuman.org/script.motel",
    "https://johnhart:mysecret@www.speakhuman.org/script.motel",
    "https://johnhart:mysecret@www.speakhuman.org:8080/script.motel",
    "https://www.speakhuman.org/beta/ws/script.motel",
    "https://johnhart:mysecret@www.speakhuman.org/beta/ws/script.motel",
    "https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel",
    "https://www.speakhuman.org/beta/ws/script.motel?debug=on;action=parse",
    "https://johnhart:mysecret@www.speakhuman.org/beta/ws/script.motel?debug=on;action=parse",
    "https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel?debug=on;action=parse",
    "https://www.speakhuman.org/beta/ws/script.motel#strict",
    "https://johnhart:mysecret@www.speakhuman.org/beta/ws/script.motel#strict",
    "https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel#strict",
    "https://www.speakhuman.org/beta/ws/script.motel?debug=on;action=parse#strict",
    "https://johnhart:mysecret@www.speakhuman.org/beta/ws/script.motel?debug=on;action=parse#strict",
    "https://johnhart:mysecret@www.speakhuman.org:8080/beta/ws/script.motel?debug=on;action=parse#strict"
};

size_t gCount = sizeof(gUrls) / sizeof(char *);

char * gUrl = (char *) NULL;

/*----------------------------------------------------------------------------
  Main
  ----------------------------------------------------------------------------*/

void main
(
    void
)
{
    motelResult lResult;

    boolean lReturn;

    motelUrlHandle lObject = (motelUrlHandle) NULL;

    char lUrl[10000];
    char lScheme[1000];
    char lAuthority[1000];
    char lCredentials[1000];
    char lUsername[1000];
    char lPassword[1000];
    char lHost[1000];
    char lPort[1000];
    char lPath[1000];
    char lFile[1000];
    char lExtension[1000];
    char lQuery[1000];
    char lFragment[1000];

    char * lRemainder;

    size_t lCount = gCount;

    while (0 < lCount)
    {
        --lCount;

        * lScheme = * CC_STRING_TERMINATOR;
        * lAuthority = * CC_STRING_TERMINATOR;
        * lCredentials = * CC_STRING_TERMINATOR;
        * lUsername = * CC_STRING_TERMINATOR;
        * lPassword = * CC_STRING_TERMINATOR;
        * lHost = * CC_STRING_TERMINATOR;
        * lPort = * CC_STRING_TERMINATOR;
        * lPath = * CC_STRING_TERMINATOR;
        * lFile = * CC_STRING_TERMINATOR;
        * lExtension = * CC_STRING_TERMINATOR;
        * lQuery = * CC_STRING_TERMINATOR;
        * lFragment = * CC_STRING_TERMINATOR;

        lRemainder = (char *) NULL;

        gUrl = gUrls[lCount];


        /* technique 0 */

        lRemainder = ParseString(lScheme, gUrl, sizeof(lScheme), 0, 1, "://", 1);

        lRemainder = ParseString(lAuthority, lRemainder, sizeof(lAuthority), 1, "://", 1, 1, "/", MOTEL_OPTIONAL);

        lRemainder = ParseString(lPath, lRemainder, sizeof(lPath), 0, 2, "?", "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lQuery, lRemainder, sizeof(lQuery), 1, "?", 1, 1, "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lFragment, lRemainder, sizeof(lFragment), 1, "#", 1, 0);

        lRemainder = ParseString(lCredentials, lAuthority, sizeof(lCredentials), 0, 1, "@", 1);

        lRemainder = ParseString(lHost, lRemainder, sizeof(lHost), 1, "@", MOTEL_OPTIONAL, 1, ":", MOTEL_OPTIONAL);

        lRemainder = ParseString(lPort, lRemainder, sizeof(lPort), 1, ":", 1, 0);

        lRemainder = ParseString(lUsername, lCredentials, sizeof(lUsername), 0, 1, ":", MOTEL_OPTIONAL);

        lRemainder = ParseString(lPassword, lRemainder, sizeof(lPassword), 1, ":", 1, 0);

        lRemainder = ParseString(lFile, lPath, sizeof(lFile), 1, "/", MOTEL_LAST_INSTANCE, 0);

        lRemainder = ParseString(lExtension, lFile, sizeof(lExtension), 1, ".", 1, 0);

        
        /* technique 1 */

        lReturn = ConstructUrl(&lObject, (char *) NULL);

        lReturn = SetUrlMember(lObject, motelUrlMember_Scheme, lScheme);
        lReturn = SetUrlMember(lObject, motelUrlMember_Username, lUsername);
        lReturn = SetUrlMember(lObject, motelUrlMember_Password, lPassword);
        lReturn = SetUrlMember(lObject, motelUrlMember_Host, lHost);
        lReturn = SetUrlMember(lObject, motelUrlMember_Port, lPort);
        lReturn = SetUrlMember(lObject, motelUrlMember_Path, lPath);
        lReturn = SetUrlMember(lObject, motelUrlMember_Query, lQuery);
        lReturn = SetUrlMember(lObject, motelUrlMember_Fragment, lFragment);

        lReturn = GetUrlMember(lObject, motelUrlMember_Url, lUrl);

        if (!ValidateUrl(lObject))
        {
            GetUrlMember(lObject, motelUrlMember_Url, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gUrl, lUrl);
        }

        if (0 != strcmp(gUrl, lUrl))
        {
            printf("Error: Loaded URL does not match source URL\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gUrl, lUrl);
        }

        lReturn = DestructUrl(&lObject);


        /* technique 2 */

        lReturn = ConstructUrl(&lObject, (char *) NULL);

        lReturn = SetUrlMember(lObject, motelUrlMember_Scheme, lScheme);
        lReturn = SetUrlMember(lObject, motelUrlMember_Credentials, lCredentials);
        lReturn = SetUrlMember(lObject, motelUrlMember_Host, lHost);
        lReturn = SetUrlMember(lObject, motelUrlMember_Port, lPort);
        lReturn = SetUrlMember(lObject, motelUrlMember_Path, lPath);
        lReturn = SetUrlMember(lObject, motelUrlMember_Query, lQuery);
        lReturn = SetUrlMember(lObject, motelUrlMember_Fragment, lFragment);

        lReturn = GetUrlMember(lObject, motelUrlMember_Url, lUrl);

        if (!ValidateUrl(lObject))
        {
            GetUrlMember(lObject, motelUrlMember_Result, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gUrl, lUrl);
        }

        if (0 != strcmp(gUrl, lUrl))
        {
            printf("Error: Loaded URL does not match source URL\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gUrl, lUrl);
        }

        lReturn = DestructUrl(&lObject);


        /* technique 3 */

        lReturn = ConstructUrl(&lObject, (char *) NULL);

        lReturn = SetUrlMember(lObject, motelUrlMember_Scheme, lScheme);
        lReturn = SetUrlMember(lObject, motelUrlMember_Authority, lAuthority);
        lReturn = SetUrlMember(lObject, motelUrlMember_Path, lPath);
        lReturn = SetUrlMember(lObject, motelUrlMember_Query, lQuery);
        lReturn = SetUrlMember(lObject, motelUrlMember_Fragment, lFragment);

        lReturn = GetUrlMember(lObject, motelUrlMember_Url, lUrl);

        if (!ValidateUrl(lObject))
        {
            GetUrlMember(lObject, motelUrlMember_Result, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gUrl, lUrl);
        }

        if (0 != strcmp(gUrl, lUrl))
        {
            printf("Error: Loaded URL does not match source URL\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gUrl, lUrl);
        }

        lReturn = DestructUrl(&lObject);


        /* technique 4 */

        lReturn = ConstructUrl(&lObject, (char *) NULL);

        lReturn = SetUrlMember(lObject, motelUrlMember_Url, gUrl);

        lReturn = GetUrlMember(lObject, motelUrlMember_Url, lUrl);

        if (!ValidateUrl(lObject))
        {
            GetUrlMember(lObject, motelUrlMember_Result, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gUrl, lUrl);
        }

        if (0 != strcmp(gUrl, lUrl))
        {
            printf("Error: Loaded URL does not match source URL\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gUrl, lUrl);
        }

        lReturn = DestructUrl(&lObject);
    }

    printf("Press Enter to exit:");

    fgetc(stdin);
}
