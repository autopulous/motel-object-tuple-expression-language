/*----------------------------------------------------------------------------
  Motel Tokenizer
 
  application programmer's interface (API) header file
  ----------------------------------------------------------------------------
  Copyright 2011-2012 John L. Hart IV. All rights reserved.
 
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

#ifndef MOTEL_TOKENIZER_I_H
#define MOTEL_TOKENIZER_I_H

/*----------------------------------------------------------------------------
  ValidateTokenizer()
  ----------------------------------------------------------------------------
  Test the state of a tokenizer to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer - (I) The tokenizer handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Tokenizer passed the validity check

  False - Tokenizer did not pass the validity check due to:

          1. 
          ..
          8. A memory leak was detected
          9. The document exceeded its memory size limit
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelTokenizer module. A
  validity check failure suggests a bug in the motelTokenizer implementation.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateTokenizer
(
    motelTokenizerHandle pTokenizer
);

/*----------------------------------------------------------------------------
  ConstructTokenizer()
  ----------------------------------------------------------------------------
  Construct a tokenizer.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer   - (I/O) Pointer to recieve the tokenizer handle
  pMaximumSize - (I)   The maximum number of bytes used by the tokenizer
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Tokenizer was succesfully constructed

  False - Motel Tokenizer was not successfully constructed due to:

          1. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  The maximum memory paramter may be set to zero to allow the document to grow
  to the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructTokenizer
(
    motelTokenizerHandle * pTokenizer,
	size_t pMaximumSize
);

/*----------------------------------------------------------------------------
  DestructTokenizer()
  ----------------------------------------------------------------------------
  Destruct the tokenizer.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer - (I/O) Pointer to the tokenizer handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Tokenizer was succesfully destructed

  False - Motel Tokenizer was not successfully destructed due to:

          1. The pTokenizer handle pointer was NULL
		  2. The destruction of the tokenizer failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructTokenizer
(
    motelTokenizerHandle * pTokenizer
);

/*----------------------------------------------------------------------------
  SetTokenizerMember()
  ----------------------------------------------------------------------------
  Set the value of a published Tokenizer member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer - (I) A document handle
  pMember    - (I) The member to retrieve
  pValue     - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member was succesfully retrieved

  False - The member was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.tokenizer.t.h of the member to learn the
  memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member.
  These values are string copied (strcpy) to the buffer provided by the
  calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetTokenizerMember
(
    motelTokenizerHandle pTokenizer,
	motelTokenizerMember pMember,
	const void * pValue
);

/*----------------------------------------------------------------------------
  GetTokenizerMember()
  ----------------------------------------------------------------------------
  Get the value of a published Tokenizer member.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer - (I)   A tokenizer handle
  pMember    - (I)   The member variable to retrieve
  pValue     - (I/O) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member was succesfully retrieved

  False - The member was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.tokenizer.t.h of the member to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member.
  These values are string copied to the buffer provided by the calling
  application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetTokenizerMember
(
    motelTokenizerHandle pTokenizer,
	motelTokenizerMember pMember,
	void * pValue
);

/*----------------------------------------------------------------------------
  NextTokenizerToken()
  ----------------------------------------------------------------------------
  Tokenize the next token.
  ----------------------------------------------------------------------------
  Parameters:

  pTokenizer - (I) Motel Tokenizer handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Token was succesfully parsed

  False - Token was not successfully parsed due to:

          1. The pTokenizer handle was NULL
		  2. The pToken handle pointer was NULL
          3. A delimiter was not found
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION NextTokenizerToken
(
    motelTokenizerHandle pTokenizer
);

#endif