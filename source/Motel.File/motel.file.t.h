/*----------------------------------------------------------------------------
  Motel File

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

#ifndef MOTEL_FILE_T_H
#define MOTEL_FILE_T_H

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public File members
*/

typedef enum motelFileMember motelFileMember;

enum motelFileMember
{
	motelFileMember_Result,             /*!< Data type:   (motelResult *)
                                             Description: The method result code */

	motelFileMember_FileErrorNumber,    /*!< Data type:   (int *)
                                             Description: The current system error number */

	motelFileMember_Size,               /*!< Data type:   (unsigned long *)
                                             Description: The number of characters in the file */

	motelFileMember_First,              /*!< Data type:   NULL
                                             Description: Move the cursor to first character of the file */

	motelFileMember_Last,               /*!< Data type:   NULL
                                             Description: Move the cursor to last character of the file */

	motelFileMember_Previous,           /*!< Data type:   NULL
                                             Description: Move the cursor to the previous character of the file */

	motelFileMember_Next,               /*!< Data type:   NULL
                                             Description: Move the cursor to the next character of the file */

	motelFileMember_
};

typedef struct motelFile motelFile;
typedef MUTABILITY motelFile * motelFileHandle;

struct motelFile
{
	MUTABILITY motelResult result;

    MUTABILITY char * MUTABILITY fileReference;
    MUTABILITY boolean createMode;

    MUTABILITY FILE * MUTABILITY stream;
};

#endif
