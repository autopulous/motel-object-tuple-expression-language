/*----------------------------------------------------------------------------
  Motel Socket
 
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

#ifndef MOTEL_SOCKET_T_H
#define MOTEL_SOCKET_T_H

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

/*----------------------------------------------------------------------------
  Includes required to compile the contents of this source file
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Data types
  ----------------------------------------------------------------------------*/

#define MAC_ADAPTER_ADDRESS_BYTES 6

typedef byte motelMacAddress[MAC_ADAPTER_ADDRESS_BYTES];

/*
** Public members
*/

typedef enum motelSocketMember motelSocketMember;

enum motelSocketMember
{
	motelSocketMember_Result,            /*!< Data type: (motelResult *)
                                              Description: The method result code */

    motelSocketMember_SocketErrorNumber, /*!< Data type: (int *)
                                              Description: The current system error number */

    motelSocketMember_Host,              /*!< Data type: (char *)
                                              Description: The host name or IP address */

    motelSocketMember_HostIP,            /*!< Data type: (char *)
                                              Description: The host IP address resolved by the system */

    motelSocketMember_Port,              /*!< Data type: (char *)
                                              Description: The port on the host */

    motelSocketMember_TcpSegmentSize,    /*!< Data type: (int *)
                                              Description: The number of bytes that are sent or received within a segment */

	motelSocketMember_
};

typedef struct motelSocket motelSocket;
typedef motelSocket * motelSocketHandle;

struct motelSocket
{
	MUTABILITY motelResult result;

    MUTABILITY char Host[MOTEL_HOST_SIZE];
    MUTABILITY char Port[MOTEL_PORT_SIZE];

    MUTABILITY char HostIP[MOTEL_HOST_SIZE];

    MUTABILITY SOCKET socket;
    MUTABILITY SOCKET clientSocket;

    MUTABILITY int TcpSegmentSize;
};

#endif