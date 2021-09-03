/*----------------------------------------------------------------------------
  Motel keyboard command processor

  application programmer's interface (API) header file
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

#ifndef MOTEL_COMMAND_I_H
#define MOTEL_COMMAND_I_H

/*----------------------------------------------------------------------------
  GetCommand()
  ----------------------------------------------------------------------------
  Accept a string from stdin removing control characters and whitespace
  ----------------------------------------------------------------------------
  Parameters:

  pStringCommand     - (IO) Pointer to command string buffer
  pStringCommandSize - (I)  The size of the command string buffer
  ----------------------------------------------------------------------------
  Returns:

  pStringCommand
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION GetCommand
(
    char * pStringCommand,
    size_t pStringCommandSize
);

/*----------------------------------------------------------------------------
  ParseCommand()
  ----------------------------------------------------------------------------

  ----------------------------------------------------------------------------
  Parameters:

  pX     - (IO)
  ----------------------------------------------------------------------------
  Returns:

  pX
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ParseCommand
(
    char * pStringCommand,
    char * pVerbs[],
	char * pDirectObjectArticle[],
    char * pDirectObjectAdjectives[],
    char * pDirectObjectNouns[],
    char * pPrepositions[],
	char * pIndirectObjectArticle[],
    char * pIndirectObjectAdjectives[],
    char * pIndirectObjectNouns[],
    Command * pParsedCommand
);

#endif
