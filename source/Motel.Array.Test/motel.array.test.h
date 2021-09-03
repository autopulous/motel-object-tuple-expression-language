/*----------------------------------------------------------------------------
  Motel Array Test
  
  private header file
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

#ifndef MOTEL_ARRAY_TEST_H
#define MOTEL_ARRAY_TEST_H

#define TEST_DURATION 3
#define PERFORMANCE_TEST_NODES 1000
#define THOROUGH_TEST_NODES PERFORMANCE_TEST_NODES * 100

#define DATA_ELEMENT_SIZE 64

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

void DisplayOptions
(
    void
);

void Validate
(
	void
);

void Construct
(
    void
);

void Destruct
(
    void
);

void InsertNode
(
	void
);

void SelectNode
(
	void
);

void PeekNode
(
	void
);

void FetchNode
(
	void
);

void UpdateNode
(
	void
);

void DeleteNode
(
	void
);

void HeadNode
(
	void
);

void TailNode
(
	void
);

void NextNode
(
	void
);

void PreviousNode
(
	void
);

void PushHeadNode
(
	void
);

void PushTailNode
(
	void
);

void PullHeadNode
(
	void
);

void PullTailNode
(
	void
);

void PeekHeadNode
(
	void
);

void PeekTailNode
(
	void
);

void PeekNextNode
(
	void
);

void PeekPreviousNode
(
	void
);

void FetchHeadToTail
(
	void
);

void FetchTailToHead
(
	void
);

void PullHeadToTail
(
	void
);

void PullTailToHead
(
	void
);

void PeekHeadToTail
(
	void
);

void PeekTailToHead
(
	void
);

void IteratedTest1
(
	void
);

void IteratedTest2
(
	void
);

void OutputState
(
    void
);

void GenerateInsertData
(
	void
);

void GenerateUpdateData
(
	void
);

void OutputNodeData
(
	void
);

void OutputResult
(
	void
);

boolean (CALLING_CONVENTION CharacterNodeCompare)
(
    lem *,
    motelNodeHandle,
    motelNodeHandle
);

boolean (CALLING_CONVENTION IntegerNodeCompare)
(
    lem *,
    motelNodeHandle,
    motelNodeHandle
);

#endif
