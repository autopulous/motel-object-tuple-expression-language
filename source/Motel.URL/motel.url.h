/*----------------------------------------------------------------------------
  Motel URL

  private header file
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

#ifndef MOTEL_URL_H
#define MOTEL_URL_H

#define MUTABILITY

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.Memory/motel.memory.i.h"

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
  Public macros and data types
  ----------------------------------------------------------------------------*/

#include "motel.url.t.h"

/*----------------------------------------------------------------------------
  Private macros
  ----------------------------------------------------------------------------*/

#define MOTEL_SCHEME_DELIMITER      "://"
#define MOTEL_PASSWORD_DELIMITER    ":"
#define MOTEL_CREDENTIALS_DELIMITER "@"
#define MOTEL_PORT_DELIMITER        ":"
#define MOTEL_FILE_DELIMITER        "/"
#define MOTEL_EXTENSION_DELIMITER   "."
#define MOTEL_QUERY_DELIMITER       "?"
#define MOTEL_FRAGMENT_DELIMITER    "#"

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.url.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

static char * ParseScheme
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseAuthority
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseCredentials
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseUsername
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParsePassword
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseHost
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParsePort
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParsePath
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseFile
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseExtension
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseQuery
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * ParseFragment
(
    motelUrlHandle pUrl,
    char * pSource
);

static char * AssembleUrl
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleScheme
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleAuthority
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleCredentials
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssemblePath
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleFile
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleExtension
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleQuery
(
    motelUrlHandle pUrl,
    char * pDestination
);

static char * AssembleFragment
(
    motelUrlHandle pUrl,
    char * pDestination
);

#endif
