/*----------------------------------------------------------------------------
  Motel Pool Test

  private header file
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

#ifndef MOTEL_POOL_TEST_H
#define MOTEL_POOL_TEST_H

#define TEST_DURATION 10
#define PERFORMANCE_TEST_NODES 100000
#define THOROUGH_TEST_NODES PERFORMANCE_TEST_NODES

#define ALLOCATION_SIZE ((size_t) 100000)

#define DATA_ELEMENT_SIZE 64

typedef struct a a;

struct a
{
    char a[17];
    long long b;
    float c;
    float d;
    double e;
    char f[777];
};

typedef struct b b;

struct b
{
    char a[7700];
    char b[32];
    long long * c;
    void * d;
};

typedef struct c c;

struct c
{
    char a[509];
};

typedef struct d d;

struct d
{
    short a[509];
};

typedef struct e e;

struct e
{
    double a[509];
};

struct f
{
    byte type;

    union
    {
        a a;
        b b;
        c c;
        d d;
        e e;
    };
};

struct g
{
    short a;
    char b[60];
};

struct node
{
    byte type;

    union
    {
        struct f * f;
        struct g * g; 
    };
};

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

void AllocateNode
(
	void
);

void DeallocateNode
(
	void
);

void NodeList
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

void IteratedTest3
(
	void
);

void OutputPoolState
(
    void
);

void GenerateInsertData
(
	byte pType,
    motelMemoryObjectHandle pObject
);

void OutputNodeData
(
	void
);

void OutputResult
(
	void
);

#endif
