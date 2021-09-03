/*----------------------------------------------------------------------------
  Motel HRR Test
  
  executable implementation file
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

#include "../Motel.Hrr/motel.hrr.t.h"

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

#include "../Motel.Hrr/motel.hrr.i.h"

/*----------------------------------------------------------------------------
  Private defines, data types and function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.hrr.test.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.hrr.test.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Globals
  ----------------------------------------------------------------------------*/

char * gHrrs[] = 
{
    "org.speakhuman.www$https/script",
    "org.speakhuman$https@johnhart:mysecret",
    "org.speakhuman.www:8080$https/script",
    "19.200.57.77:8080$https/script@johnhart:mysecret",
    "org.speakhuman.www$https/script.motel",
    "org.speakhuman.www$https/script.motel@johnhart:mysecret",
    "org.speakhuman:8080$https/script.motel@johnhart:mysecret",
    "org.speakhuman.www$https/beta/ws/script.motel",
    "org.speakhuman.www$https/beta/ws/script.motel@johnhart:mysecret",
    "org.speakhuman.www:8080$https/beta/ws/script.motel@johnhart:mysecret",
    "org.speakhuman.www$https/beta/ws/script.motel?debug=on;action=parse",
    "org.speakhuman.www$https/beta/ws/script.motel@johnhart:mysecret?debug=on;action=parse",
    "org.speakhuman.www$8080:https/beta/ws/script.motel@johnhart:mysecret?debug=on;action=parse",
    "12.54.33.122$https/beta/ws/script.motel#strict",
    "org.speakhuman$https/beta/ws/script.motel@johnhart:mysecret#strict",
    "org.speakhuman.www:8080$https/beta/ws/script.motel@johnhart:mysecret#strict",
    "org.speakhuman.www$https/beta/ws/script.motel?debug=on;action=parse#strict",
    "175.15.12.21$https/beta/ws/script.motel@johnhart:mysecret?debug=on;action=parse#strict",
    "org.speakhuman.www:8080$https/beta/ws/script.motel@johnhart:mysecret?debug=on;action=parse#strict"
};

size_t gCount = sizeof(gHrrs) / sizeof(char *);

char * gHrr = (char *) NULL;

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

    motelHrrHandle lObject = (motelHrrHandle) NULL;

    char lHrr[10000];
    char lDevice[1000];
    char lHost[1000];
    char lPort[1000];
    char lScheme[1000];
    char lCredentials[1000];
    char lIdentity[1000];
    char lPassword[1000];
    char lResource[1000];
    char lQuery[1000];
    char lFragment[1000];

    char * lRemainder;

    size_t lCount = gCount;

    while (0 < lCount)
    {
        --lCount;

        * lDevice = * CC_STRING_TERMINATOR;
        * lHost = * CC_STRING_TERMINATOR;
        * lPort = * CC_STRING_TERMINATOR;
        * lScheme = * CC_STRING_TERMINATOR;
        * lCredentials = * CC_STRING_TERMINATOR;
        * lIdentity = * CC_STRING_TERMINATOR;
        * lPassword = * CC_STRING_TERMINATOR;
        * lResource = * CC_STRING_TERMINATOR;
        * lQuery = * CC_STRING_TERMINATOR;
        * lFragment = * CC_STRING_TERMINATOR;

        lRemainder = (char *) NULL;

        gHrr = gHrrs[lCount];


        /* technique 0 */

        lRemainder = ParseString(lDevice, gHrr, sizeof(lDevice), 0, 5, "$", "/", "@", "?", "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lScheme, lRemainder, sizeof(lScheme), 1, "$", MOTEL_OPTIONAL, 4, "/", "@", "?", "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lResource, lRemainder, sizeof(lResource), 1, "/", 1, 3, "@", "?", "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lCredentials, lRemainder, sizeof(lCredentials), 1, "@", 1, 2, "?", "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lQuery, lRemainder, sizeof(lQuery), 1, "?", 1, 1, "#", MOTEL_OPTIONAL);

        lRemainder = ParseString(lFragment, lRemainder, sizeof(lFragment), 1, "#", 1, 0);

        lRemainder = ParseString(lHost, lDevice, sizeof(lHost), 0, 1, ":", MOTEL_OPTIONAL);

        lRemainder = ParseString(lPort, lRemainder, sizeof(lPort), 1, ":", 1, 0);

        lRemainder = ParseString(lIdentity, lCredentials, sizeof(lIdentity), 0, 1, ":", MOTEL_OPTIONAL);

        lRemainder = ParseString(lPassword, lRemainder, sizeof(lPassword), 1, ":", 1, 0);

        
        /* technique 1 */

        lReturn = ConstructHrr(&lObject, (char *) NULL);

        lReturn = SetHrrMember(lObject, motelHrrMember_Host, lHost);
        lReturn = SetHrrMember(lObject, motelHrrMember_Port, lPort);
        lReturn = SetHrrMember(lObject, motelHrrMember_Scheme, lScheme);
        lReturn = SetHrrMember(lObject, motelHrrMember_Resource, lResource);
        lReturn = SetHrrMember(lObject, motelHrrMember_Identity, lIdentity);
        lReturn = SetHrrMember(lObject, motelHrrMember_Password, lPassword);
        lReturn = SetHrrMember(lObject, motelHrrMember_Query, lQuery);
        lReturn = SetHrrMember(lObject, motelHrrMember_Fragment, lFragment);

        lReturn = GetHrrMember(lObject, motelHrrMember_Hrr, &lHrr);

        if (!ValidateHrr(lObject))
        {
            GetHrrMember(lObject, motelHrrMember_Result, &lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gHrr, lHrr);
        }

        if (0 != strcmp(gHrr, lHrr))
        {
            printf("Error: Loaded HRR does not match source HRR\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gHrr, lHrr);
        }

        lReturn = DestructHrr(&lObject);


        /* technique 2 */

        lReturn = ConstructHrr(&lObject, (char *) NULL);

        lReturn = SetHrrMember(lObject, motelHrrMember_Device, lDevice);
        lReturn = SetHrrMember(lObject, motelHrrMember_Scheme, lScheme);
        lReturn = SetHrrMember(lObject, motelHrrMember_Resource, lResource);
        lReturn = SetHrrMember(lObject, motelHrrMember_Credentials, lCredentials);
        lReturn = SetHrrMember(lObject, motelHrrMember_Query, lQuery);
        lReturn = SetHrrMember(lObject, motelHrrMember_Fragment, lFragment);

        lReturn = GetHrrMember(lObject, motelHrrMember_Hrr, lHrr);

        if (!ValidateHrr(lObject))
        {
            GetHrrMember(lObject, motelHrrMember_Result, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gHrr, lHrr);
        }

        if (0 != strcmp(gHrr, lHrr))
        {
            printf("Error: Loaded HRR does not match source HRR\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gHrr, lHrr);
        }

        lReturn = DestructHrr(&lObject);


        /* technique 3 */

        lReturn = ConstructHrr(&lObject, (char *) NULL);

        lReturn = SetHrrMember(lObject, motelHrrMember_Hrr, gHrr);

        lReturn = GetHrrMember(lObject, motelHrrMember_Hrr, lHrr);

        if (!ValidateHrr(lObject))
        {
            GetHrrMember(lObject, motelHrrMember_Result, & lResult);

            printf("Error: %d\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", lResult, gHrr, lHrr);
        }

        if (0 != strcmp(gHrr, lHrr))
        {
            printf("Error: Loaded HRR does not match source HRR\n"
                   "Source = \"%s\"\n"
                   "Loaded = \"%s\"\n", gHrr, lHrr);
        }

        lReturn = DestructHrr(&lObject);
    }

    printf("Press Enter to exit:");

    fgetc(stdin);
}
