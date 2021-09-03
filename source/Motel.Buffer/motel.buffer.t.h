/*----------------------------------------------------------------------------
  Motel Buffer

  application programmer's types (APT) header file
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

#ifndef MOTEL_BUFFER_T_H
#define MOTEL_BUFFER_T_H

/*----------------------------------------------------------------------------
  Motel headers
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public Buffer members
*/

typedef enum motelBufferMember motelBufferMember;

enum motelBufferMember
{
	motelBufferMember_Result,        /*!< Data type:   (motelResult *)
                                          Description: The method result code */

	motelBufferMember_Size,          /*!< Data type:   (size_t *)
                                          Description: The number of bytes in the buffer */

	motelBufferMember_First,         /*!< Data type:   NULL
                                          Description: Move the cursor to first byte of the buffer */

	motelBufferMember_Last,          /*!< Data type:   NULL
                                          Description: Move the cursor to last byte of the buffer */

	motelBufferMember_Previous,      /*!< Data type:   NULL
                                          Description: Move the cursor to the previous byte of the buffer */

	motelBufferMember_Next,          /*!< Data type:   NULL
                                          Description: Move the cursor to the next byte of the buffer */

	motelBufferMember_Cursor,        /*!< Data type:   NULL
                                          Description: The location of the cursor within the buffer */

	motelBufferMember_
};

/*----------------------------------------------------------------------------
  Data types
  ----------------------------------------------------------------------------*/

typedef struct motelBuffer motelBuffer;
typedef MUTABILITY motelBuffer * motelBufferHandle;

struct motelBuffer
{
	MUTABILITY motelResult result;          /* the results of the last operation */

    MUTABILITY size_t size;                 /* the number of bytes allocated to this array */

	MUTABILITY byte * MUTABILITY firstByte; /* the first byte in the buffer */
    MUTABILITY byte * MUTABILITY thisByte;  /* the byte in the buffer corresponding to the cursor */
	MUTABILITY byte * MUTABILITY lastByte;  /* the last byte in the buffer */
};

#endif
