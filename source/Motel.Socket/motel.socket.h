/*----------------------------------------------------------------------------
  Motel Socket

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

#ifndef MOTEL_SOCKET_H
#define MOTEL_SOCKET_H

#define MUTABILITY

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel.Memory/motel.memory.i.h"

#include "../Motel.String/motel.string.t.h"
#include "../Motel.String/motel.string.i.h"

#include "../Motel.Buffer/motel.buffer.t.h"
#include "../Motel.Buffer/motel.buffer.i.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64

// Visual Studio 2010 
// Alternatively add Ws2_32.lib & IPHLPAPI.lib to Project Properties -> linker -> input -> additional dependencies

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

#include <winsock.h>
#include <io.h>
#include <iphlpapi.h>

#define ioctl ioctlsocket

#else

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

/*----------------------------------------------------------------------------
  Public macros and data types
  ----------------------------------------------------------------------------*/

#include "motel.socket.t.h"

/*----------------------------------------------------------------------------
  Private macros
  ----------------------------------------------------------------------------*/

#define UNUSED_SOCKET SOCKET_ERROR

#define SOCKET_OK 0

#define DEFAULT_TCP_SEGMENT_SIZE 1440

#define LOCAL_HOST    "localhost"
#define LOCAL_HOST_IP "127.0.0.1"

/*----------------------------------------------------------------------------
  Private data types
  ----------------------------------------------------------------------------*/

typedef int socketResult;

/*----------------------------------------------------------------------------
  Public function prototypes
  ----------------------------------------------------------------------------*/

#include "motel.socket.i.h"

/*----------------------------------------------------------------------------
  Private function prototypes
  ----------------------------------------------------------------------------*/

boolean OpenAsServer
(
    motelSocketHandle pSocket,
    const char * pPort
);

boolean OpenAsClient
(
    motelSocketHandle pSocket,
    const char * pHost,
    const char * pPort
);

boolean PullAsServer
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
);

boolean PullAsClient
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
);

boolean PushAsServer
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
);

boolean PushAsClient
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
);

#endif
