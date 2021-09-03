/*----------------------------------------------------------------------------
  Motel Array
  
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

#include "motel.array.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.array.c - Copyright 2011-2012-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

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
)
{
{
	/*
	** no node size provided
	*/

    if (0 == pNodeSize)
    {
        return (FALSE);
    }

    /*
    ** attempted to populate the array with values beyond the end of the source
    */

    if (pSourceSize < pNodesToPopulate * pNodeSize)
    {
        return (FALSE);
    }

	/*
	** nodes cannot be allocated
	*/

    if (0 == pNodesToAllocate && 0 == pNodesToPopulate && 0 == pNodeAllocationUnit)
    {
        return (FALSE);
    }

	/*
	** the array cannot be expanded to accept the number of source nodes specified
	*/

    if (pNodesToPopulate > pNodesToAllocate && 0 == pNodeAllocationUnit)
    {
        return (FALSE);
    }

    /*
    ** validate the initializer
    */

    if (NULL == pSource && 0 < pNodesToPopulate)
    {
        return (FALSE);
    }
}
{
	/*
	** allocate the array control structure
	*/

	if (!SafeMallocBlock((void **) pArray, sizeof(motelArray)))
	{
		return (FALSE);
	}

    /*
    ** when the array is expandable
    */

    if (0 != pNodeAllocationUnit)
    {
        /*
        ** ensure sufficient nodes to populate the array from the source
        */

        if (pNodesToPopulate > pNodesToAllocate)
        {
            pNodesToAllocate = ComputeNodeAllocation(pNodesToPopulate, pNodeAllocationUnit);
        }
        else
        {
            pNodesToAllocate = ComputeNodeAllocation(pNodesToAllocate, pNodeAllocationUnit);
        }
    }

	/*
	** allocate node storage
	*/

    (* pArray)->head = (motelNodeHandle) NULL;

    if (0 != pNodesToAllocate)
    {
	    if (!SafeMallocBlock((void **) &(* pArray)->head, pNodesToAllocate * pNodeSize))
	    {   
            SafeFreeBlock((void **) &(* pArray)->head);

		    return (FALSE);
	    }
    }
}
{
    motelNodeHandle lDestination = (* pArray)->head;

    /*
    ** populate nodes
    */

    CopyBlock(lDestination, pNodesToAllocate * pNodeSize, pSource, pSourceSize, pNodesToPopulate * pNodeSize);

    /*
    ** update object state
    */

    (* pArray)->objectSize = sizeof(motelArray) + (pNodesToAllocate * pNodeSize);

    (* pArray)->nodeSize = pNodeSize;

    (* pArray)->nodeAllocationUnit = pNodeAllocationUnit;

    (* pArray)->nodesAllocated = pNodesToAllocate;
    (* pArray)->nodesPopulated = pNodesToPopulate;

    (* pArray)->tail = (0 == pNodesToPopulate ? lDestination : lDestination + ((pNodesToPopulate - 1) * pNodeSize));

    if (0 == pNodesToPopulate)
    {
        (* pArray)->index = 0;
        (* pArray)->cursor = (motelNodeHandle) NULL;
    }
    else
    {
        (* pArray)->index = 1;
        (* pArray)->cursor = (* pArray)->head;
    }

    (* pArray)->comparer = pCompare;

	(* pArray)->result = motelResult_OK;

	return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructArray
(
    motelArrayHandle * pArray
)
{
{
    /*
    ** there is no array
    */

    if (NULL == pArray || NULL == * pArray)
    {
        return (FALSE);
    }
}
{
    /*
    ** deallocated node storage
    */

    if (NULL != (* pArray)->head)
    {
        if (!SafeFreeBlock((void **) &(* pArray)->head))
        {
		    (* pArray)->result = motelResult_MemoryDeallocation;

		    return (FALSE);
        }
    }

    /*
    ** deallocated the array control structure
    */

    if (!SafeFreeBlock((void **) pArray))
	{
		return (FALSE);
	}

	return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ResetArray
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    pArray->tail = pArray->head;

    pArray->nodesPopulated = 0;

    pArray->index = 0;
    pArray->cursor = (motelNodeHandle) NULL;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateArray
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    pArray->result = motelResult_Corrupted;

    if (motelResult_OK > pArray->result || motelResult_ <= pArray->result)
    {
        return (FALSE);
    }

    if (0 == pArray->nodeSize)
    {
        return (FALSE);
    }

    if (sizeof(motelArray) + (pArray->nodesAllocated * pArray->nodeSize) != pArray->objectSize)
    {
        return (FALSE);
    }

    if (NULL != pArray->cursor && pArray->cursor < pArray->head)
    {
        return (FALSE);
    }

    if (pArray->cursor > pArray->tail)
    {
        return (FALSE);
    }

    if (NULL == pArray->head)
    {
        return (FALSE);
    }

    if (pArray->head > pArray->tail)
    {
        return (FALSE);
    }

    if (pArray->index > pArray->nodesPopulated)
    {
        return (FALSE);
    }

    if (pArray->nodesPopulated > pArray->nodesAllocated)
    {
        return (FALSE);
    }

    if (0 == pArray->nodesAllocated && 0 == pArray->nodeAllocationUnit)
    {
        return (FALSE);
    }

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DumpArray
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Array.DumpArray: %p\n", pArray);
    fprintf(stderr, "SetArrayCursorToHeadNode:   %p\n", pArray->head);
    fprintf(stderr, "SetArrayCursorToTailNode:   %p\n", pArray->tail);
    fprintf(stderr, "SetArrayCursorToThisNode: %zd\n", pArray->index);
    fprintf(stderr, "Cursor: %p\n", pArray->cursor);
    fprintf(stderr, "Allocated: %zd\n", pArray->nodesAllocated);
    fprintf(stderr, "Populated: %zd\n", pArray->nodesPopulated);
    fprintf(stderr, "Node Size: %zd\n", pArray->nodeSize);
    fprintf(stderr, "Object Size: %zd\n", pArray->objectSize);
    fprintf(stderr, "Result: %d\n", pArray->result);
    fprintf(stderr, "\n");

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AutopulateArray
(
    autopulation pMode,
    motelArrayHandle pDestinationArray,
    motelNodeHandle pDestinationCursor,
    count pDestinationNodes,
    motelArrayHandle pSourceArray,
    motelNodeHandle pSourceCursor,
    count pSourceNodes
)
{
    /*
    ** validate that the autopulation mode
    */

    if ((~(EXCISE | MOVE)) & pMode)
    {
        return (FALSE);
    }

    /*
    ** validate that the destination node reference in bounds
    */

    if (NULL != pDestinationArray)
    {
        if (pDestinationArray->head > pDestinationCursor || pDestinationArray->tail + pDestinationArray->nodeSize < pDestinationCursor)
        {
            return (FALSE);
        }
    }

    /*
    ** validate
    */

    if (NULL != pSourceCursor)
    {
    }

    /*
    ** validate that the source node reference in bounds
    */

    if (NULL != pSourceArray)
    {
        if (pSourceArray->head > pSourceCursor || pSourceArray->tail + pSourceArray->nodeSize < pSourceCursor)
        {
            return (FALSE);
        }
    }

    /*
    ** validate 
    */

    if (NULL != pDestinationCursor)
    {
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToHeadNode
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_InvalidState;

        return (FALSE);
    }
}
{
    pArray->index = 1;
    pArray->cursor = pArray->head;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToPreviousNode
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_InvalidState;

        return (FALSE);
    }
}
{
    if (pArray->head != pArray->cursor)
    {
        pArray->index--;
        pArray->cursor -= pArray->nodeSize;
    }

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToThisNode
(
    motelArrayHandle pArray,
    index pIndex
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_InvalidState;

        return (FALSE);
    }

    /*
    ** out of bounds array reference
    */

    if (0 == pIndex || pArray->nodesPopulated < pIndex)
    {
        pArray->result = motelResult_OutOfBounds;

        return (FALSE);
    }
}
{
    pArray->index = pIndex;
    pArray->cursor = pArray->head + ((pIndex - 1) * pArray->nodeSize);

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToMatchingNode
(
    motelArrayHandle pArray,
    motelArrayHandle pCriteria
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    pArray->result = motelResult_Unimplemented;

    return (FALSE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToNextNode
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_InvalidState;

        return (FALSE);
    }
}
{
    if (pArray->tail != pArray->cursor)
    {
        pArray->index++;
        pArray->cursor += pArray->nodeSize;
    }

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetArrayCursorToTailNode
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_InvalidState;

        return (FALSE);
    }
}
{
    pArray->index = pArray->nodesPopulated;
    pArray->cursor = pArray->tail;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ReverseArray
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    motelNodeHandle lLeftNode = pArray->head;
    motelNodeHandle lRightNode = pArray->tail;

    size_t lNodeSize = pArray->nodeSize;

    loop
    {
        byte lSwapByte;

        byte * lLeftByte;
        byte * lRightByte;

        index lByteCount;

        escape(lLeftNode >= lRightNode);

        lByteCount = lNodeSize;

        lLeftByte = lLeftNode, lRightByte = lRightNode;

        loop
        {
            lSwapByte = *lRightByte;
            *lRightByte = *lLeftByte;
            *lLeftByte = lSwapByte;

            escape(1 == lByteCount);

            lByteCount--;

            lLeftByte++, lRightByte++;
        }

        lLeftNode += lNodeSize, lRightNode -= lNodeSize;
    }

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CloneArray
(
    motelArrayHandle * pDestinationArray,
    motelArrayHandle pSourceArray
)
{
{ 
    /*
    ** there is no destination array pointer
    */

    if (NULL == pDestinationArray)
    {
        return (FALSE);
    }
}
{
    if (ConstructArray(pDestinationArray, pSourceArray->nodeSize, pSourceArray->nodesAllocated, pSourceArray->nodeAllocationUnit, pSourceArray->comparer, pSourceArray->head, pSourceArray->nodesAllocated * pSourceArray->nodeSize, pSourceArray->nodesPopulated))
    {
        (* pDestinationArray)->result = motelResult_OK;

        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CopyArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray
)
{
{ 
    /*
    ** there is no destination array
    */

    if (NULL == pDestinationArray)
    {
        return (FALSE);
    }

    /*
    ** there is no source array
    */

    if (NULL == pSourceArray)
    {
        pDestinationArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** arrays have incompatible node sizes
    */

    if (pDestinationArray->nodeSize != pSourceArray->nodeSize)
    {
        pDestinationArray->result = motelResult_Incompatible;

        return (FALSE);
    }

    /*
    ** source array too large for destination array
    */

    if (pDestinationArray->nodesAllocated < pSourceArray->nodesPopulated && 0 == pDestinationArray->nodeAllocationUnit)
    {
        pDestinationArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pDestinationArray->nodeSize;

    motelNodeHandle lDestination;
    count lNodesAllocated = pDestinationArray->nodesAllocated;

    count lNodesToPopulate = pSourceArray->nodesPopulated;

    /*
    ** expand array
    */

    if (lNodesAllocated < lNodesToPopulate)
    {
        if (!AlterNodeAllocation(pDestinationArray, lNodesToPopulate))
        {
            return (FALSE);
        }

        lNodesAllocated = pDestinationArray->nodesAllocated;
    }

    lDestination = pDestinationArray->head;

    /*
    ** populate nodes
    */

    CopyBlock(lDestination, lNodesAllocated * lNodeSize, pSourceArray->head, pSourceArray->nodesAllocated * lNodeSize, lNodesToPopulate * lNodeSize);

    /*
    ** update object state
    */

    pDestinationArray->nodesPopulated = lNodesToPopulate;

    pDestinationArray->tail = (0 == lNodesToPopulate ? lDestination : lDestination + ((lNodesToPopulate - 1) * lNodeSize));

    pDestinationArray->index = 1;
    pDestinationArray->cursor = lDestination;

    pDestinationArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CatenateArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray
)
{
{ 
    /*
    ** there is no destination array
    */

    if (NULL == pDestinationArray)
    {
        return (FALSE);
    }

    /*
    ** there is no source array
    */

    if (NULL == pSourceArray)
    {
        pDestinationArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** arrays have incompatible node sizes
    */

    if (pDestinationArray->nodeSize != pSourceArray->nodeSize)
    {
        pDestinationArray->result = motelResult_Incompatible;

        return (FALSE);
    }

    /*
    ** not enough room to CatenateArray the source array
    */

    if (pDestinationArray->nodesAllocated < pDestinationArray->nodesPopulated + pSourceArray->nodesPopulated && 0 == pDestinationArray->nodeAllocationUnit)
    {
        pDestinationArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pDestinationArray->nodeSize;

    motelNodeHandle lDestination;

    count lNodesAllocated = pDestinationArray->nodesAllocated;
    count lNodesPopulated = pDestinationArray->nodesPopulated;

    count lNodesToPopulate = pSourceArray->nodesPopulated;

    /*
    ** expand array
    */

    if (lNodesAllocated < lNodesPopulated + lNodesToPopulate)
    {
        if (!AlterNodeAllocation(pDestinationArray, lNodesPopulated + lNodesToPopulate))
        {
            return (FALSE);
        }

        lNodesAllocated = pDestinationArray->nodesAllocated;
    }

    lDestination = (0 == pDestinationArray->nodesPopulated ? pDestinationArray->head : pDestinationArray->tail + lNodeSize);

    /*
    ** populate nodes
    */

    CopyBlock(lDestination, (pDestinationArray->nodesAllocated - pDestinationArray->nodesPopulated) * lNodeSize, pSourceArray->head, pSourceArray->nodesAllocated * lNodeSize, lNodesToPopulate * lNodeSize);

    /*
    ** update object state
    */

    pDestinationArray->nodesPopulated += lNodesToPopulate;

    pDestinationArray->tail = pDestinationArray->head + ((pDestinationArray->nodesPopulated - 1) * lNodeSize);
        
    pDestinationArray->index = 1;
    pDestinationArray->cursor = pDestinationArray->head;

    pDestinationArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PlaceArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray,
    count   pNodesToPopulate
)
{
{ 
    /*
    ** there is no destination array
    */

    if (NULL == pDestinationArray)
    {
        return (FALSE);
    }

    /*
    ** there is no source array
    */

    if (NULL == pSourceArray)
    {
        pDestinationArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** arrays have incompatible node sizes
    */

    if (pDestinationArray->nodeSize != pSourceArray->nodeSize)
    {
        pDestinationArray->result = motelResult_Incompatible;

        return (FALSE);
    }

    /*
    ** not enough room to insert the source array
    */

    if (pDestinationArray->nodesAllocated <  pDestinationArray->nodesPopulated + pNodesToPopulate && 0 == pDestinationArray->nodeAllocationUnit)
    {
        pDestinationArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pDestinationArray->nodeSize;

    size_t lNodesAllocated = pDestinationArray->nodesPopulated + pNodesToPopulate;

    count lHeadNodes = (1 > pDestinationArray->index ? 0 : pDestinationArray->index - 1);
    count lTailNodes = pDestinationArray->nodesPopulated - lHeadNodes;

    motelNodeHandle lDestination;

    motelNodeHandle lCursorInsertionPoint;
    motelNodeHandle lTailInsertionPoint;

    /*
    ** expand the array when needed
    */

    if (pDestinationArray->nodesAllocated < lNodesAllocated)
    {
        AlterNodeAllocation(pDestinationArray, lNodesAllocated);

        lNodesAllocated = pDestinationArray->nodesAllocated;
    }

    lDestination = pDestinationArray->head;

    lCursorInsertionPoint = lDestination + (lHeadNodes * lNodeSize);
    lTailInsertionPoint = lCursorInsertionPoint + (pNodesToPopulate * lNodeSize);

    /*
    ** copy the trailing nodes in the destination array to the end of the destination array to make room for the nodes to be inserted
    */

    if (0 != lTailNodes)
    {
        CopyBlock(lTailInsertionPoint, (lNodesAllocated - (lHeadNodes + pNodesToPopulate)) * lNodeSize, lCursorInsertionPoint, (lNodesAllocated - lHeadNodes) * lNodeSize, lTailNodes * lNodeSize);
    }

    /*
    ** insert nodes between the leading and trailing nodes
    */

    CopyBlock(lCursorInsertionPoint, pNodesToPopulate * lNodeSize, pSourceArray->head, pSourceArray->nodesAllocated * lNodeSize, pNodesToPopulate * lNodeSize);

    /*
    ** update object state
    */

    pDestinationArray->nodesPopulated += pNodesToPopulate;

    pDestinationArray->tail = pDestinationArray->head + ((pDestinationArray->nodesPopulated - 1) * lNodeSize);
        
    pDestinationArray->index = 1;
    pDestinationArray->cursor = pDestinationArray->head;

    pDestinationArray->result = motelResult_OK;

    return (TRUE);
}
}
/* todo: rewrite */
EXPORT_STORAGE_CLASS success CALLING_CONVENTION ReplaceArray
(
    motelArrayHandle pDestinationArray,
    motelArrayHandle pSourceArray,
    count   pNodesToPopulate
)
{
{
    /*
    ** there is no destination array
    */

    if (NULL == pDestinationArray)
    {
        return (FALSE);
    }

    /*
    ** there is no source array
    */

    if (NULL == pSourceArray)
    {
        pDestinationArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** arrays have incompatible node sizes
    */

    if (pDestinationArray->nodeSize != pSourceArray->nodeSize)
    {
        pDestinationArray->result = motelResult_Incompatible;

        return (FALSE);
    }

    /*
    ** not enough room to insert the source array
    */

    if (pDestinationArray->nodesAllocated < (pDestinationArray->index - 1) + pNodesToPopulate && 0 == pDestinationArray->nodeAllocationUnit)
    {
        pDestinationArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}        
{
    size_t lNodeSize = pDestinationArray->nodeSize;

    count lNodesAllocated = (pDestinationArray->index - 1) + pNodesToPopulate;

    byte * lDestination = pDestinationArray->cursor;

    /*
    ** expand the array when needed
    */

    if (pDestinationArray->nodesAllocated < lNodesAllocated)
    {
        AlterNodeAllocation(pDestinationArray, lNodesAllocated);

        lNodesAllocated = pDestinationArray->nodesAllocated;
    }

    /*
    ** update object state
    */

    pDestinationArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION TranslateArray
(
    motelArrayHandle pArray,
    motelArrayHandle pTransalationArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }
}
{
    pArray->result = motelResult_Unimplemented;

    return (FALSE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION CompareArrays
(
    lem   * pLessEqualMore,
    motelArrayHandle pArray1,
    motelArrayHandle pArray2
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray1 || NULL == pArray2)
    {
        return (FALSE);
    }

    /*
    ** arrays have incompatible node sizes
    */

    if (pArray1->nodeSize != pArray2->nodeSize)
    {
        pArray1->result = motelResult_Incompatible;

        return (FALSE);
    }

    /*
    ** no node comparison callback function defined
    */

    if (NULL == pArray1->comparer)
    {
        pArray1->result = motelResult_Undefined;

        return (FALSE);
    }
}
{
    motelNodeHandle lNode1 = pArray1->head;
    motelNodeHandle lNode2 = pArray2->head;

    count lNodeCount1 = pArray1->nodesPopulated;
    count lNodeCount2 = pArray2->nodesPopulated;

    size_t lNodeSize = pArray1->nodeSize;

    loop
    {
        escape(0 == lNodeCount1 || 0 == lNodeCount2);

        if (!pArray1->comparer(pLessEqualMore, lNode1, lNode2))
        {
            pArray1->result = motelResult_NodeError;

            return (FALSE);
        }

        if (EQUAL_TO != * pLessEqualMore)
        {
            pArray1->result = motelResult_OK;

            return (TRUE);
        }

        lNodeCount1--, lNodeCount2--;

        lNode1 += lNodeSize, lNode2 += lNodeSize;
    }

    if (0 == lNodeCount1)
    {
        * pLessEqualMore = LESS_THAN;
    }

    if (lNodeCount1 == lNodeCount2)
    {
        * pLessEqualMore = EQUAL_TO;
    }

    else
    {
        * pLessEqualMore = MORE_THAN;
    }

    pArray1->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION InsertArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** the cursor is not set
    */

    if (NULL == pArray->cursor)
    {
        pArray->result = motelResult_Cursor;

        return (FALSE);
    }

    /*
    ** there is no node
    */

    if (NULL == pNode)
    {
        pArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** not enough room to insert the node
    */

    if (pArray->nodesAllocated == pArray->nodesPopulated && 0 == pArray->nodeAllocationUnit)
    {
        pArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pArray->nodeSize;

    size_t lNodesAllocated = pArray->nodesAllocated;
    size_t lNodesPopulated = pArray->nodesPopulated;

    count lHeadNodes = (1 > pArray->index ? 0 : pArray->index - 1);
    count lTailNodes = pArray->nodesPopulated - lHeadNodes;

    motelNodeHandle lDestination;

    motelNodeHandle lCursorInsertionPoint;
    motelNodeHandle lTailInsertionPoint;

    /*
    ** expand the array when needed
    */

    if (lNodesAllocated == lNodesPopulated)
    {
        AlterNodeAllocation(pArray, lNodesAllocated + 1);

        lNodesAllocated = pArray->nodesAllocated;
    }

    /*
    ** calculate array offsets
    */

    lDestination = pArray->head;

    lCursorInsertionPoint = lDestination + (lHeadNodes * lNodeSize);
    lTailInsertionPoint = lCursorInsertionPoint + lNodeSize;

    /*
    ** copy the trailing nodes in the destination array to the end of the destination array to make room for the nodes to be inserted
    */

    if (0 != lTailNodes)
    {
        CopyBlock(lTailInsertionPoint, (lNodesAllocated - (lHeadNodes + 1)) * lNodeSize, lCursorInsertionPoint, (lNodesAllocated - lHeadNodes) * lNodeSize, lTailNodes * lNodeSize);
    }

    /*
    ** insert a node between the leading and trailing nodes
    */

    CopyBlock(lCursorInsertionPoint, lNodeSize, pNode, lNodeSize, lNodeSize);

    /*
    ** update object state
    */

    pArray->nodesPopulated++;

    pArray->tail = pArray->head + (lNodesPopulated * lNodeSize);
        
    pArray->index = 1;
    pArray->cursor = pArray->head;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION UpdateArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_NoNode;
        
        return (FALSE);
    }

    /*
    ** the cursor is not set
    */

    if (NULL == pArray->cursor)
    {
        pArray->result = motelResult_Cursor;

        return (FALSE);
    }

    /*
    ** there is no node
    */

    if (NULL == pNode)
    {
        pArray->result = motelResult_NullPointer;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pArray->nodeSize;

    CopyBlock(pArray->cursor, lNodeSize, pNode, lNodeSize, lNodeSize);

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION AppendArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
)
{
{
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there is no node
    */

    if (NULL == pNode)
    {
        pArray->result = motelResult_NullPointer;

        return (FALSE);
    }

    /*
    ** not enough room to append the node
    */

    if (pArray->nodesAllocated == pArray->nodesPopulated && 0 == pArray->nodeAllocationUnit)
    {
        pArray->result = motelResult_MaximumSize;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pArray->nodeSize;

    motelNodeHandle lDestination;

    count lNodesAllocated = pArray->nodesAllocated;
    count lNodesPopulated = pArray->nodesPopulated;

    /*
    ** expand array
    */

    if (lNodesAllocated == lNodesPopulated)
    {
        if (!AlterNodeAllocation(pArray, lNodesAllocated + 1))
        {
            return (FALSE);
        }

        lNodesAllocated = pArray->nodesAllocated;
    }

    lDestination = (0 == lNodesPopulated ? pArray->head : pArray->tail + lNodeSize);

    /*
    ** populate the node
    */

    CopyBlock(lDestination, (lNodesAllocated - lNodesPopulated) * lNodeSize, pNode, lNodeSize, lNodeSize);

    /*
    ** update object state
    */

    pArray->nodesPopulated++;
        
    pArray->tail = pArray->head + (lNodesPopulated * lNodeSize);

    pArray->index = 1;
    pArray->cursor = pArray->head;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeleteArrayNode
(
    motelArrayHandle pArray
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_NoNode;
        
        return (FALSE);
    }

    /*
    ** the cursor is not set
    */

    if (NULL == pArray->cursor)
    {
        pArray->result = motelResult_Cursor;

        return (FALSE);
    }
}
{
    if (1 == pArray->nodesPopulated)
    {
        pArray->index = 0;
        pArray->cursor = (motelNodeHandle) NULL;
        pArray->tail = (motelNodeHandle) NULL;
    }
    else
    {
        size_t lNodeSize = pArray->nodeSize;

        index lIndex = pArray->index;

        count lNodesPopulated = pArray->nodesPopulated;

        if (lIndex < lNodesPopulated)
        {
            motelNodeHandle lDestination = pArray->cursor;
            size_t lDestinationSize = (pArray->nodesAllocated - (lIndex - 1)) * lNodeSize;

            motelNodeHandle lSource = lDestination + lNodeSize;
            size_t lSourceSize = lDestinationSize - lNodeSize;

            size_t lBytesToPopulate = (lNodesPopulated - lIndex) * lNodeSize;

            CopyBlock(lDestination, lDestinationSize, lSource, lSourceSize, lBytesToPopulate);
        }
        else
        {
            pArray->index--;
            pArray->cursor -= lNodeSize;
        }

        pArray->tail -= lNodeSize;
    }

    /*
    ** update object state
    */

    pArray->nodesPopulated--;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_NoNode;
        
        return (FALSE);
    }

    /*
    ** the cursor is not set
    */

    if (NULL == pArray->cursor)
    {
        pArray->result = motelResult_Cursor;

        return (FALSE);
    }
}
{
    size_t lNodeSize = pArray->nodeSize;

    /*
    ** copy the node at the cursor location
    */

    CopyBlock(pNode, lNodeSize, pArray->cursor, pArray->nodesAllocated * lNodeSize, lNodeSize);

    /*
    ** update object state
    */

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullArrayNode
(
    motelArrayHandle pArray,
    motelNodeHandle  pNode
)
{
{ 
    /*
    ** there is no array
    */

    if (NULL == pArray)
    {
        return (FALSE);
    }

    /*
    ** there are no nodes
    */

    if (0 == pArray->nodesPopulated)
    {
        pArray->result = motelResult_NoNode;
        
        return (FALSE);
    }
}
{
    size_t lNodeSize = pArray->nodeSize;

    /*
    ** copy the node at the cursor location
    */

    CopyBlock(pNode, lNodeSize, pArray->cursor, pArray->nodesAllocated * lNodeSize, lNodeSize);

    /*
    ** delete the node at the cursor location
    */

    if (1 == pArray->nodesPopulated)
    {
        pArray->index = 0;
        pArray->cursor = (motelNodeHandle) NULL;
        pArray->tail = (motelNodeHandle) NULL;
    }
    else
    {
        size_t lNodeSize = pArray->nodeSize;

        index lIndex = pArray->index;

        count lNodesPopulated = pArray->nodesPopulated;

        if (lIndex < lNodesPopulated)
        {
            motelNodeHandle lDestination = pArray->cursor;
            size_t lDestinationSize = (pArray->nodesAllocated - (lIndex - 1)) * lNodeSize;

            motelNodeHandle lSource = lDestination + lNodeSize;
            size_t lSourceSize = lDestinationSize - lNodeSize;

            size_t lBytesToPopulate = (lNodesPopulated - lIndex) * lNodeSize;

            CopyBlock(lDestination, lDestinationSize, lSource, lSourceSize, lBytesToPopulate);
        }
        else
        {
            pArray->index--;
            pArray->cursor -= lNodeSize;
        }

        pArray->tail -= lNodeSize;
    }

    /*
    ** update object state
    */

    pArray->nodesPopulated--;

    pArray->result = motelResult_OK;

    return (TRUE);
}
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

static boolean AlterNodeAllocation
(
    motelArrayHandle pArray,
    count pNodesToAllocate
)
{
{
    ASSERT(0 != pArray->nodeAllocationUnit);
}
{
    motelNodeHandle lDestination = (motelNodeHandle) NULL;
    motelNodeHandle lSource = pArray->head;

    size_t lNodeSize = pArray->nodeSize;

    pNodesToAllocate = ComputeNodeAllocation(pNodesToAllocate, pArray->nodeAllocationUnit);

    /*
    ** allocate a new memory block
    */

    if (!SafeMallocBlock((void **) &lDestination, pNodesToAllocate * lNodeSize))
    {
        pArray->result = motelResult_MemoryAllocation;

        return (FALSE);
    }

    /*
    ** copy nodes to the newly allocated memory block
    */

    CopyBlock(lDestination, pNodesToAllocate * lNodeSize, lSource, pArray->nodesAllocated * lNodeSize, pArray->nodesPopulated * lNodeSize);

    /*
    ** free the old memory block
    */

    if (!SafeFreeBlock((void **) &lSource))
    {
        pArray->result = motelResult_MemoryDeallocation;

        return (FALSE);
    }

    /*
    ** update object state
    */

    pArray->head = lDestination;
    
    pArray->objectSize -= pArray->nodesAllocated * lNodeSize;

    pArray->nodesAllocated = pNodesToAllocate;

    pArray->objectSize += pArray->nodesAllocated * lNodeSize;

    pArray->tail = lDestination + ((pArray->nodesPopulated - 1) * lNodeSize);

    pArray->index = 1;
    pArray->cursor = lDestination;

    return (TRUE);
}
}

static count ComputeNodeAllocation
(
    count pNodesToAllocate,
    count pNodeAllocationUnit
)
{
    /*
    ** allocate nodes as a multiple of the node allocation unit (rounded up)
    */

    if (0 != pNodesToAllocate && 0 == pNodesToAllocate % pNodeAllocationUnit)
    {
        return (pNodeAllocationUnit * (pNodesToAllocate / pNodeAllocationUnit));
    }
    else
    {
        return (pNodeAllocationUnit * ((pNodesToAllocate / pNodeAllocationUnit) + 1));
    }
}
