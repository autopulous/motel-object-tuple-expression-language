/*----------------------------------------------------------------------------
  Motel Array

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

#ifndef MOTEL_ARRAY_I_H
#define MOTEL_ARRAY_I_H

/*----------------------------------------------------------------------------
  Includes required to compile the contents of this source file
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

/*----------------------------------------------------------------------------
  Public data types
  ----------------------------------------------------------------------------*/

#include "motel.array.t.h"

/*----------------------------------------------------------------------------
  Class definition
  ----------------------------------------------------------------------------*/

/* allocate memory and initialize an array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructArray
(
    motelArrayHandle * pArray,
    size_t pNodeSize,
    count pNodesToAllocate,
    count pNodeAllocationUnit,
    nodeComparer pCompare,
    motelNodeHandle pSource,
    size_t pSourceSize,
    count pNodesToPopulate
);

/* reset the nodesPopulated node count to zero */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ResetArray
(
    motelArrayHandle pArray
);

/* free the memory associated with an array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructArray
(
    motelArrayHandle * pArray
);

/* validate the state of the array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateArray
(
    motelArrayHandle pArray
);

/* dump the state of the array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DumpArray
(
    motelArrayHandle pArray
);

/*
** array operations
*/

/* construct an array that is logically equivalent to a source array and copy all nodes */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CloneArray
(
    motelArrayHandle * pDestinationArray,
    motelArrayHandle pSourceArray
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AutopulateArray
(
    autopulation pMode,
    motelArrayHandle pDestinationArray,
    motelNodeHandle pDestinationCursor,
    count pDestinationNodes,
    motelArrayHandle pSourceArray,
    motelNodeHandle pSourceCursor,
    count pSourceNodes
);

/* reverse the order of the nodes within the array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ReverseArray
(
    motelArrayHandle pArray
);

/* translate the value of the nodes within the array, may change the nodesPopulated node count */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION TranslateArray
(
    motelArrayHandle pArray,
    motelArrayHandle pTransalationArray
);

/* compare the value of the nodes within two arrays starting at the cursor location within each array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CompareArrays
(
    lem   * pLessEqualMore,
    motelArrayHandle pArray1,
    motelArrayHandle pArray2
);

/*
** cursor operations
*/

/* set cursor to first nodesPopulated node */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToHeadNode
(
    motelArrayHandle pArray
);

/* set cursor to previous nodesPopulated node */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToPreviousNode
(
    motelArrayHandle pArray
);

/* set cursor to a node based upon an index value */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToThisNode
(
    motelArrayHandle pArray,
    index pIndex
);

/* set cursor to a node based upon search criteria */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToMatchingNode
(
    motelArrayHandle pArray,
    motelArrayHandle pCriteria
);

/* set cursor to next nodesPopulated node */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToNextNode
(
    motelArrayHandle pArray
);

/* set cursor to last nodesPopulated node */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToTailNode
(
    motelArrayHandle pArray
);

/*
** array operations based upon the cursor
*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CatenateArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PlaceArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray,
    count   pNodesToPopulate
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ReplaceArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray,
    count   pNodesToPopulate
);

/*
** node operations based upon the cursor
*/

/* insert a node at the current cursor location, will increase the nodesPopulated node count up to the allocation limit of the array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION InsertArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
);

/* update the node at the current cursor location */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION UpdateArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
);

/* append a node after the last nodesPopulated node, will increase the nodesPopulated node count up to the allocation limit of the array */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AppendArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
);

/* remove the node at the current cursor location, will reduce the nodesPopulated node count */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeleteArrayNode
(
    motelArrayHandle pArray
);

/* fetch the node at the current cursor location */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
);

/* fetch and remove the node at the current cursor location, will reduce the nodesPopulated node count */

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
);

#endif
