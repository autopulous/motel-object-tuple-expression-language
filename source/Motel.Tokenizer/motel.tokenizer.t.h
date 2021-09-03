/*----------------------------------------------------------------------------
  Motel Tokenizer
 
  application programmer's types (APT) header file 
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

#ifndef MOTEL_TOKENIZER_T_H
#define MOTEL_TOKENIZER_T_H

/*----------------------------------------------------------------------------
  Motel headers
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel/motel.node.t.h"

#include "../Motel.Document/motel.character.t.h"

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public members
*/

typedef enum motelTokenizerMember motelTokenizerMember;

enum motelTokenizerMember
{
	motelTokenizerMember_Result,            /*!< Data type:   (motelResult *)
                                                 Description: The method result code */

	motelTokenizerMember_Size,              /*!< Data type:   (size_t *)
                                                 Description: Memory currently allocated by the tokenizer object */

	motelTokenizerMember_DelimiterPattern,  /*!< Data type:   (char *)
                                                 Description: Delimiter pattern expression */

	motelTokenizerMember_Delimiter,         /*!< Data type:   (char *)
                                                 Description: The current delimiter */

	motelTokenizerMember_Token,             /*!< Data type:   (char *)
                                                 Description: The current token */

    motelTokenizerMember__NextCharacter,    /*!< Data type:   *(char *)
                                                 Description: Function pointer to source of characters to process */

	motelTokenizerMember_
};

typedef struct motelTokenizer motelTokenizer;
typedef motelTokenizer * motelTokenizerHandle;

struct motelTokenizer
{
	MUTABILITY motelResult result;

	MUTABILITY size_t maximumSize;
	MUTABILITY size_t size;

    MUTABILITY char * MUTABILITY delimiterList;

    MUTABILITY char * MUTABILITY token;
    MUTABILITY char * MUTABILITY delimiter;

    MUTABILITY motelNodeHandle MUTABILITY StreamObject;

    MUTABILITY _MotelNextCharacter MUTABILITY _NextCharacter;
};

#endif