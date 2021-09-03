/*----------------------------------------------------------------------------
  Motel keyboard command processor

  private header file
  ----------------------------------------------------------------------------
  Copyright 2011-2012-2012 John L. Hart IV. All rights reserved.

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

#ifndef MOTEL_COMMAND_H
#define MOTEL_COMMAND_H

#define MUTABILITY

#include <ctype.h>
#include <conio.h>
#include <string.h>

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

/*----------------------------------------------------------------------------
  Public macros and data types
  ----------------------------------------------------------------------------*/

#include "motel.command.t.h"

/*----------------------------------------------------------------------------
  Private macros
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.command.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

static boolean MatchToken
(
    char * pCommand,
    char * pTokens[],
    char * pToken
);

#endif
