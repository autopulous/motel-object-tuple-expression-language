/*----------------------------------------------------------------------------
  Motel Array
 
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

#ifndef MOTEL_ARRAY_T_H
#define MOTEL_ARRAY_T_H

/*----------------------------------------------------------------------------
  Motel headers
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel/motel.node.t.h"

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*----------------------------------------------------------------------------
  Includes required to compile the contents of this source file
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Data types
  ----------------------------------------------------------------------------*/

typedef boolean (CALLING_CONVENTION * nodeComparer)(lem *, motelNodeHandle, motelNodeHandle);

typedef struct motelArray motelArray;
typedef motelArray * motelArrayHandle;

struct motelArray
{
    MUTABILITY motelResult result;       /* the results of the last operation */

	MUTABILITY size_t objectSize;        /* the number of bytes allocated to this array */

    MUTABILITY size_t nodeSize;          /* the number of bytes allocated to each node in the array */

    MUTABILITY count nodeAllocationUnit; /* the number of nodes to allocate when more are needed */

    MUTABILITY count nodesAllocated;     /* the number of nodes allocated in the array */
    MUTABILITY count nodesPopulated;     /* the number of nodes populated in the array */

    MUTABILITY index index;              /* the cursor index position */

    MUTABILITY motelNodeHandle head;     /* the first motelNode in the array */
    MUTABILITY motelNodeHandle cursor;   /* the motelNode in the array corresponding to the cursor */
    MUTABILITY motelNodeHandle tail;     /* the last motelNode in the array */

	MUTABILITY nodeComparer comparer;    /* motelNode comparison callback function */
};

#endif
