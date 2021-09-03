/*----------------------------------------------------------------------------
  Motel Document

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

#ifndef MOTEL_DOCUMENT_I_H
#define MOTEL_DOCUMENT_I_H

/*****************************************************************************
                      Generic data structure operations
 *****************************************************************************/

/*----------------------------------------------------------------------------
  ValidateDocument()
  ----------------------------------------------------------------------------
  Test the state of a document to assure that the structure is correct.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) The document handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Document passed the validity check

  False - Document did not pass the validity check due to:

          1. 
          ..
          8. A memory leak was detected
          9. The document exceeded its memory size limit
  ----------------------------------------------------------------------------
  Note:

  This function is primarily used for debugging of the motelDocument module. A
  validity check failure suggests a bug in the motelDocument implementation.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateDocument
(
    motelDocumentHandle pDocument
);

/*----------------------------------------------------------------------------
  ConstructDocument()
  ----------------------------------------------------------------------------
  Construct a document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument    - (I/O) Pointer to recieve the document handle
  pMaximumSize - (I)   The maximum number of bytes used by the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Document was succesfully constructed

  False - Motel Document was not successfully constructed due to:

          1. The SafeMallocBlock() failed
  ----------------------------------------------------------------------------
  Notes:

  The maximum memory paramter may be set to zero to allow the document to grow
  to the operating system controlled process memory limit.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructDocument
(
    motelDocumentHandle * pDocument,
	size_t pMaximumSize
);

/*----------------------------------------------------------------------------
  DestructDocument()
  ----------------------------------------------------------------------------
  Destruct the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I/O) Pointer to the document handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - Motel Document was succesfully destructed

  False - Motel Document was not successfully destructed due to:

          1. The pDocument handle pointer was NULL
		  2. The destruction of a object data object failed
          3. The destruction of a object failed
		  4. The destruction of the document failed
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructDocument
(
    motelDocumentHandle * pDocument
);

/*----------------------------------------------------------------------------
  SetDocumentMember()
  ----------------------------------------------------------------------------
  Set the value of a published Document member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) A document handle
  pMember   - (I) The member to retrieve
  pValue    - (I) A pointer to memory to receive the member's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.document.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided
  by the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetDocumentMember
(
    motelDocumentHandle pDocument,
	motelDocumentMember pMember,
	const void * pValue
);

/*----------------------------------------------------------------------------
  GetDocumentMember()
  ----------------------------------------------------------------------------
  Get the value of a published Document member variable.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) A document handle
  pMember   - (I)   The member variable to retrieve
  pValue    - (I/O) A pointer to memory to receive the member variable's value
  ----------------------------------------------------------------------------
  Return Values:

  True  - The member variable was succesfully retrieved

  False - The member variable was not successfully retrieved due to:

          1. pValue was NULL
		  2. The pMember value was invalid
  ----------------------------------------------------------------------------
  Notes:

  Check the comments within motel.document.t.h of the member variable to learn
  the memory and data type requirements of each.

  Sufficient memory must be allocated to retrieve string (char *) member
  variables. These values are string copied (strcpy) to the buffer provided by
  the calling application.

  This function will corrupt user memory when pValue is of insufficient size
  to hold the value of a given member variable.

  Special attention must be paid to assure that pValue points to a variable
  of the appropriate data type to recieive the member variable value.
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetDocumentMember
(
    motelDocumentHandle pDocument,
	motelDocumentMember pMember,
	void * pValue
);

/*----------------------------------------------------------------------------
  ParseDocument()
  ----------------------------------------------------------------------------
  Parse a document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  ----------------------------------------------------------------------------
  Return Values:

  True  - The document was succesfully parsed

  False - The document was not successfully parsed due to:

          1. The pDocument handle was NULL
		  2. The document was invalid
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ParseDocument
(
    motelDocumentHandle pDocument
);

/*----------------------------------------------------------------------------
  SelectDocument()
  ----------------------------------------------------------------------------
  Select (find) a object within the document - changing the cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle in which the object to delete exists
  pObject   - (I) Data object to select from the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully selected

  False - Object was not successfully selected due to:

          1. The pDocument handle was NULL
          2. The pObject handle was NULL
		  3. The document is empty
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SelectDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

/*----------------------------------------------------------------------------
  FetchDocument()
  ----------------------------------------------------------------------------
  Fetch a object from the document at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle in which the object to delete exists
  pObject   - (O) Data object to fetch to the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully fetched

  False - Object was not successfully fetched due to:

          1. The pDocument handle was NULL
		  2. The document is empty
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION FetchDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

/*----------------------------------------------------------------------------
  UpdateDocument()
  ----------------------------------------------------------------------------
  Update a object in the document at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle in which the object to delete exists
  pObject   - (I) Data object to update to the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully updated

  False - Object was not successfully updated due to:

          1. The pDocument handle was NULL
          2. The pObject handle was NULL
		  3. The document cursor was NULL
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION UpdateDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

/*----------------------------------------------------------------------------
  DeleteDocument()
  ----------------------------------------------------------------------------
  Delete a object from the document at the current cursor location.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle in which the object to delete exists
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully deleted

  False - Object was not successfully deleted due to:

          1. The pDocument handle was NULL
		  2. The document cursor was NULL
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DeleteDocument
(
    motelDocumentHandle pDocument
);

/*****************************************************************************
                          Stack and Queue operations
  *****************************************************************************/

/*----------------------------------------------------------------------------
  PushHeadDocument()
  ----------------------------------------------------------------------------
  Add a data object to the document at the head/top - aka push.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object to add to the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully stacked

  False - Object was not successfully stacked due to:

          1. The pDocument handle was NULL
		  2. The pObject handle was NULL
  ----------------------------------------------------------------------------
  Usage note:
  
  PushHeadDocument() + PullHeadDocument() = Stack
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define StackDocument(pDocument, pObject)                                       \
	    (SetDocumentMember(pDocument, motelDocumentMember_Head, NULL) ?         \
		(InsertDocument(pDocument, pObject)) :                                  \
		FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushHeadDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PushTopDocument(pDocument, pObject) PushHeadDocument(pDocument, pObject)
#define StackDocument(pDocument, pObject)   PushHeadDocument(pDocument, pObject)

/*----------------------------------------------------------------------------
  PushTailDocument()
  ----------------------------------------------------------------------------
  Add a data object to the document at the tail/bottom.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object to add to the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully queued

  False - Object was not successfully queued due to:

          1. The pDocument handle was NULL
		  2. The pObject handle was NULL
  ----------------------------------------------------------------------------
  Usage note:
  
  PushTailDocument() + PullHeadDocument() = Queue
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define QueueDocument(pDocument, pObject)                                       \
	    (SetDocumentMember(pDocument, motelDocumentMember_Tail, NULL) ?         \
		(InsertDocument(pDocument, pObject))                                    \
		: FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushTailDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PushBottomDocument(pDocument, pObject) PushTailDocument(pDocument, pObject)
#define QueueDocument(pDocument, pObject)      PushTailDocument(pDocument, pObject)

/*----------------------------------------------------------------------------
  PeekHeadDocument()
  ----------------------------------------------------------------------------
  Non-destructively copy the data object at the head/top of the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object in which to copy the data value from the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully peeked

  False - Object was not successfully peeked due to:

          1. The pDocument handle was NULL
		  2. The pObject handle pointer was NULL
		  3. The document is empty
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekHeadDocument(pDocument, pObject)                                    \
	    (SetDocumentMember(pDocument, motelDocumentMember_Head, NULL) ?         \
		(FetchDocument(pDocument, pObject) :                                    \
		FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekHeadDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PeekTopDocument(pDocument, pObject) PeekHeadDocument(pDocument, pObject)

/*----------------------------------------------------------------------------
  PeekTailDocument()
  ----------------------------------------------------------------------------
  Non-destructively copy the data object at the tail/bottom of the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object in which to copy the data value from the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully peeked

  False - Object was not successfully peeked due to:

          1. The pDocument handle was NULL
		  2. The pObject handle pointer was NULL
		  3. The document is empty
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekTailDocument(pDocument, pObject)                                    \
	    (SetDocumentMember(pDocument, motelDocumentMember_Tail, NULL) ?         \
		(FetchDocument(pDocument, pObject) :                                    \
		FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekTailDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PeekBottomDocument(pDocument, pObject) PeekTailDocument(pDocument, pObject)

/*----------------------------------------------------------------------------
  PeekPreviousDocument()
  ----------------------------------------------------------------------------
  Non-destructively copy the data object at the previous object in the document.

  Calling this function when the cursor is not set will result in the Tail
  object being returned; thus permitting wrap-around traversal of the values in
  the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object in which to copy the data value from the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully peeked

  False - Object was not successfully peeked due to:

          1. The pDocument handle was NULL
		  2. The pObject handle pointer was NULL
		  3. The document is empty
		  4. There is no previous object before the head object
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekPreviousDocument(pDocument, pObject)                                \
	    (SetDocumentMember(pDocument, motelDocumentMember_Previous, NULL) ?     \
		(FetchDocument(pDocument, pObject) :                                    \
		FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekPreviousDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

/*----------------------------------------------------------------------------
  PeekNextDocument()
  ----------------------------------------------------------------------------
  Non-destructively copy the data object at the next object in the document.

  Calling this function when the cursor is not set will result in the Head
  object being returned; thus permitting wrap-around traversal of the values in
  the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object in which to copy the data value from the document
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully peeked

  False - Object was not successfully peeked due to:

          1. The pDocument handle was NULL
		  2. The pObject handle pointer was NULL
		  3. The document is empty
		  4. There is no next object after the tail object
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PeekNextDocument(pDocument, pObject)                                    \
	    (SetDocumentMember(pDocument, motelDocumentMember_Next, NULL) ?         \
		(FetchDocument(pDocument, pObject) :                                    \
		FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PeekNextDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

/*----------------------------------------------------------------------------
  PullHeadDocument()
  ----------------------------------------------------------------------------
  Destructively copy the data object at the head/top of the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object receive the data object value
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully undocumentd

  False - Object was not successfully undocumentd due to:

          1. The pDocument handle was NULL
		  2. The pObject handle pointer was NULL
		  3. The pObject handle pointer was NULL
		  4. The object's data object could not destructed
		  5. The object could not destructed
  ----------------------------------------------------------------------------
  Usage note:
  
  PushHeadDocument() + PullHeadDocument() = Stack
  PushTailDocument() + PullHeadDocument() = Queue
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PullHeadDocument(pDocument, pObject)                                  \
	    (SetDocumentMember(pDocument, motelDocumentMember_Head, NULL) ?       \
		(FetchDocument(pDocument, pObject) ?                                  \
		(DeleteDocument(pDocument))                                           \
		: FALSE) : FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullHeadDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PullTopDocument(pDocument, pObject) PullHeadDocument(pDocument, pObject)
#define UnstackDocument(pDocument, pObject) PullHeadDocument(pDocument, pObject)
#define DequeueDocument(pDocument, pObject) PullHeadDocument(pDocument, pObject)

/*----------------------------------------------------------------------------
  PullTailDocument()
  ----------------------------------------------------------------------------
  Destructively copy the data object at the tail/bottom of the document.
  ----------------------------------------------------------------------------
  Parameters:

  pDocument - (I) Motel Document handle
  pObject   - (O) Data object receive the data object value
  ----------------------------------------------------------------------------
  Return Values:

  True  - Object was succesfully undocumentd

  False - Object was not successfully undocumentd due to:

          1. The pDocument handle was NULL
          2. The document is empty
		  3. The pObject handle pointer was NULL
		  4. The object's data object could not destructed
		  5. The object could not destructed
  ----------------------------------------------------------------------------
  This function is logically equivalent to the following macro:

#define PullTailDocument(pDocument, pObject)                                  \
	    (SetDocumentMember(pDocument, motelDocumentMember_Tail, NULL) ?       \
		(FetchDocument(pDocument, pObject) ?                                  \
		(DeleteDocument(pDocument))                                           \
		: FALSE) : FALSE)
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullTailDocument
(
    motelDocumentHandle pDocument,
	motelDocumentNodeHandle pObject
);

#define PullBottomDocument(pDocument, pObject) PullHeadDocument(pDocument, pObject)

#endif