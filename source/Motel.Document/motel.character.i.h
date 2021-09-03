/*----------------------------------------------------------------------------
  Motel Character

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

#ifndef MOTEL_CHARACTER_I_H
#define MOTEL_CHARACTER_I_H

/*****************************************************************************
                      Generic data structure operations
 *****************************************************************************/

/*----------------------------------------------------------------------------
  ValidateCharacter()
  ----------------------------------------------------------------------------
  Test the state of a character to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter - (I) The Character handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Character passed the validity check

  False - Character did not pass the validity check due to:

          1. 
          ..
          8. A memory leak was detected
          9. The Character exceeded its memory size limit
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelCharacter module. A
  validity check failure suggests a bug in the motelCharacter implementation.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateCharacter
(
    motelCharacterHandle pCharacter
);

/*----------------------------------------------------------------------------
  ConstructCharacter()
  ----------------------------------------------------------------------------
  Construct a Character.
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter - (I/O) Pointer to recieve the Character handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Character was succesfully constructed

  False - Motel Character was not successfully constructed due to:

          1. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  The maximum memory paramter may be set to zero to allow the Character to grow
  to the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructCharacter
(
    motelCharacterHandle * pCharacter
);

/*----------------------------------------------------------------------------
  DestructCharacter()
  ----------------------------------------------------------------------------
  Destruct the Character.
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter - (I/O) Pointer to the Character handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Character was succesfully destructed

  False - Motel Character was not successfully destructed due to:

          1. The pCharacter handle pointer was NULL
		  2. The destruction of a object data object failed
          3. The destruction of a object failed
		  4. The destruction of the Character failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructCharacter
(
    motelCharacterHandle * pCharacter
);

/*----------------------------------------------------------------------------
  SetCharacterMember()
  ----------------------------------------------------------------------------
  Set the value of a published Character member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter - (I) A Character handle
  pMember -    (I) The member to retrieve
  pValue  -    (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.Character.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided
  by the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetCharacterMember
(
    motelCharacterHandle pCharacter,
	motelCharacterMember pMember,
	const void * pValue
);

/*----------------------------------------------------------------------------
  GetCharacterMember()
  ----------------------------------------------------------------------------
  Get the value of a published Character member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pCharacter - (I) A Character handle
  pMember -    (I)   The member variable to retrieve
  pValue  -    (I/O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.Character.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided by
  the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetCharacterMember
(
    motelCharacterHandle pCharacter,
	motelCharacterMember pMember,
	void * pValue
);

#endif