/*----------------------------------------------------------------------------
  Motel keyboard command processor

  library implementation file
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

/*----------------------------------------------------------------------------
  Include files
  ----------------------------------------------------------------------------*/

#include "motel.command.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright UNUSED = "@(#)motel.command.c - Copyright 2011-2012-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS char * CALLING_CONVENTION GetCommand
(
    char * pStringCommand,
    size_t pStringCommandSize
)
{
    char * lStringCommand = pStringCommand;
    char * lLastCharacter = pStringCommand;

    size_t lStringLength = pStringCommandSize - 1;

    char lCharacter;

    loop
    {
        lCharacter = getch();

        /* Handle multi-part non-text keystroke characters */

        if (* CC_STRING_TERMINATOR >= lCharacter)
        {
            char lDiscardedCharacter = getch();
            continue;
        }

        /* Handle the the control C and control X keystokes */

		if (* CC_CONTROL_C == lCharacter || * CC_CONTROL_X == lCharacter)
		{
			loop
			{
				escape(pStringCommand == lStringCommand);

			    putch(* CC_BACKSPACE);
                putch(* CC_SPACE);
                putch(* CC_BACKSPACE);

				lStringCommand--;
			}

			* pStringCommand = lCharacter;

			lLastCharacter = pStringCommand + 1;

			break;
		}

        /* Handle the enter key */

        if (* CC_NEW_LINE == lCharacter || * CC_RETURN == lCharacter)
        {
            putch(* CC_NEW_LINE);

            if (* CC_SPACE != *lLastCharacter)
            {
                lLastCharacter++;
            }

			break;
        }

        /* Handle the backspace key */

        if (* CC_BACKSPACE == lCharacter)
        {
            if (pStringCommand == lStringCommand)
            {
                putch(* CC_BELL);
                continue;
            }

            putch(lCharacter);
            putch(* CC_SPACE);
            putch(lCharacter);

            lStringCommand--;

            if (lStringCommand < lLastCharacter)
            {
                lLastCharacter = lStringCommand;
            }

            continue;
        }

        /* Handle punctuation */

        if (IsPunctuation((int) lCharacter))
        {
            /* Treat any punctuation as a space */

            lCharacter = * CC_SPACE;
        }

        /* Handle whitespace keystrokes */

        if (IsWhitespace(lCharacter))
        {
            /* Treat any whitespace as a space */

            lCharacter = * CC_SPACE;

            /* Throw out leading spaces */

            if (pStringCommand == lLastCharacter)
            {
                continue;
            }

            /* Throw out redundant spaces */

            if (IsWhitespace(* lLastCharacter))
            {
                continue;
            }
        }

		if (IsControl(lCharacter))
		{
            putch(* CC_BELL);
			continue;
		}

        /* Handle a full input buffer */

        if (lStringLength == (lLastCharacter - pStringCommand) + 1)
        {
            putch(* CC_BELL);
            continue;
        }

        /* Process the character */

        putch(lCharacter);

        lLastCharacter = lStringCommand;

        *lLastCharacter = lCharacter;

        lStringCommand++;
    }

    /* Terminate input string - possibly trimming trailing spaces */

    * lLastCharacter = * CC_STRING_TERMINATOR;

    return (pStringCommand);
}

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
)
{
    char * lToken;
    char * lStringCommandEnd;

    /* Clear the parsed command */

    * pParsedCommand->Verb = * CC_STRING_TERMINATOR;
    * pParsedCommand->DirectObjectAdjective = * CC_STRING_TERMINATOR;
	* pParsedCommand->DirectObjectArticle = * CC_STRING_TERMINATOR;
    * pParsedCommand->DirectObjectNoun = * CC_STRING_TERMINATOR;
    * pParsedCommand->Preposition = * CC_STRING_TERMINATOR;
    * pParsedCommand->IndirectObjectAdjective = * CC_STRING_TERMINATOR;
	* pParsedCommand->IndirectObjectArticle = * CC_STRING_TERMINATOR;
    * pParsedCommand->IndirectObjectNoun = * CC_STRING_TERMINATOR;

    /* Tokenize the command string */

    for (lToken = pStringCommand; * CC_STRING_TERMINATOR != * lToken; lToken++)
    {
        if (' ' == * lToken)
        {
            * lToken = * CC_STRING_TERMINATOR;
        }
    }

    /* Process an empty command string */

    lStringCommandEnd = lToken;

    if (lStringCommandEnd == pStringCommand)
    {
        return (TRUE);
    }

    lToken = pStringCommand;

    /* Look for a verb */

    if (MatchToken(lToken, pVerbs, pParsedCommand->Verb))
    {
        lToken += strlen(pParsedCommand->Verb) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    /* Look for a direct object article */

	if (MatchToken(lToken, pDirectObjectArticle, pParsedCommand->DirectObjectArticle))
    {
        lToken += strlen(pParsedCommand->DirectObjectArticle) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    /* Look for a direct object adjective */

    if (MatchToken(lToken, pDirectObjectAdjectives, pParsedCommand->DirectObjectAdjective))
    {
        lToken += strlen(pParsedCommand->DirectObjectAdjective) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (FALSE);
        }
    }

    /* Look for a direct object */

    if (MatchToken(lToken, pDirectObjectNouns, pParsedCommand->DirectObjectNoun))
    {
        lToken += strlen(pParsedCommand->DirectObjectNoun) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    /* Look for a preposition */

    if (MatchToken(lToken, pPrepositions, pParsedCommand->Preposition))
    {
        lToken += strlen(pParsedCommand->Preposition) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    /* Look for an indirect object article */

	if (MatchToken(lToken, pIndirectObjectArticle, pParsedCommand->IndirectObjectArticle))
    {
        lToken += strlen(pParsedCommand->IndirectObjectArticle) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    /* Look for an indirect object adjective */

    if (MatchToken(lToken, pIndirectObjectAdjectives, pParsedCommand->IndirectObjectAdjective))
    {
        lToken += strlen(pParsedCommand->IndirectObjectAdjective) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (FALSE);
        }
    }

    /* Look for an indirect object */

    if (MatchToken(lToken, pIndirectObjectNouns, pParsedCommand->IndirectObjectNoun))
    {
        lToken += strlen(pParsedCommand->IndirectObjectNoun) + 1;

        if (lStringCommandEnd < lToken)
        {
            return (TRUE);
        }
    }

    return (FALSE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static boolean MatchToken
(
    char * pSearchToken,
    char * pTokens[],
    char * pFoundToken
)
{
    int lIndex;

    for (lIndex = 0; * CC_STRING_TERMINATOR != * pTokens[lIndex]; lIndex++)
    {
        if (EqualStringsi(pTokens[lIndex], pSearchToken))
        {
            CopyString(pTokens[lIndex], pFoundToken, COMMAND_STRING_SIZE);
            return (TRUE);
        }
    }

    return (FALSE);
}
