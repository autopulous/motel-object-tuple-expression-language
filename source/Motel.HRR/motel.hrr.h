/*----------------------------------------------------------------------------
  Motel HRR

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

#ifndef MOTEL_HRR_H
#define MOTEL_HRR_H

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

#include "motel.hrr.t.h"

/*----------------------------------------------------------------------------
  Private macros
  ----------------------------------------------------------------------------*/

#define MOTEL_PORT_DELIMITER        ":"
#define MOTEL_SCHEME_DELIMITER      "$"
#define MOTEL_RESOURCE_DELIMITER    "/"
#define MOTEL_CREDENTIALS_DELIMITER "@"
#define MOTEL_PASSWORD_DELIMITER    ":"
#define MOTEL_QUERY_DELIMITER       "?"
#define MOTEL_FRAGMENT_DELIMITER    "#"

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.hrr.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

static char * ParseDevice
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseScheme
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseResource
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseCredentials
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseQuery
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseFragment
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseHost
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParsePort
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseScheme
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParseIdentity
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * ParsePassword
(
    motelHrrHandle pHrr,
    char * pSource
);

static char * AssembleHrr
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleDevice
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleScheme
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleResource
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleCredentials
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleQuery
(
    motelHrrHandle pHrr,
    char * pDestination
);

static char * AssembleFragment
(
    motelHrrHandle pHrr,
    char * pDestination
);

#endif
