/*----------------------------------------------------------------------------
  Motel Socket
 
  application programmer's interface (API) header file
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

#ifndef MOTEL_SOCKET_I_H
#define MOTEL_SOCKET_I_H

/*----------------------------------------------------------------------------
  All sockets managed by this module are full-duplex TCP protocol streams:

  AF_INET     - address family IPv4 Internet
  PF_INET     - protocol family IPv4 Internet protocols
  IPPROTO_TCP - TCP protocol
  SOCK_STREAM - Full-duplex stream socket
  ----------------------------------------------------------------------------*/

#include "../Motel.Buffer/motel.buffer.t.h"

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetMacAddresss
(
    motelMacAddress * pDestination,
	size_t pDestinationSize
);

#define MotelSocketMacAddresssToString(pSource, pDestination) sprintf(pDestination, "%02X-%02X-%02X-%02X-%02X-%02X", pSource[0], pSource[1], pSource[2], pSource[3], pSource[4], pSource[5]); 

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateSocket
(
    motelSocketHandle pSocket
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructSocket
(
    motelSocketHandle * pSocket,
    const char * pHost,
    const char * pPort
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructSocket
(
    motelSocketHandle * pSocket
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetSocketMember
(
    motelSocketHandle pSocket,
	motelSocketMember pMember,
	const void * pValue
);

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetSocketMember
(
    motelSocketHandle pSocket,
	motelSocketMember pMember,
	void * pValue
);

/*----------------------------------------------------------------------------
  PushSocketBytes()
  ----------------------------------------------------------------------------
  Writes bytes to a socket.
  ----------------------------------------------------------------------------
  Parameters:

  pSocket     - (I) Pointer to the output socket
  pBuffer     - (O) Pointer to the byte transfer buffer
  ----------------------------------------------------------------------------
  Returns:

  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushSocketBytes
(
   motelSocketHandle pSocket,
   motelBufferHandle pBuffer
);

/*----------------------------------------------------------------------------
  PullSocketBytes()
  ----------------------------------------------------------------------------
  Reads bytes from a socket.
  ----------------------------------------------------------------------------
  Parameters:

  pSocket     - (I) Pointer to the input socket
  pBuffer     - (I) Pointer to the byte transfer buffer
  pBufferSize - (I) The size of the byte transfer buffer
  ----------------------------------------------------------------------------
  Returns:

  The next byte from the input stream
  ---------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullSocketBytes
(
   motelSocketHandle pSocket,
   motelBufferHandle pBuffer
);

/*----------------------------------------------------------------------------
  PopSocketBytes()
  ----------------------------------------------------------------------------
  Convenience macro for those who prefer push/pop to push/pull.
  ---------------------------------------------------------------------------*/

#define PopSocketBytes(pSocket, pBuffer) PullSocketBytes(pSocket, pBuffer)

/*----------------------------------------------------------------------------
  PokeSocketBytes()
  ----------------------------------------------------------------------------
  Writes bytes to a socket.

  Note: Since all writes to a socket are consumptive, poking bytes is
        equivalent to pushing bytes, thus poke is implemented as a macro.
  ----------------------------------------------------------------------------
  Parameters:

  pSocket     - (I) Pointer to the output socket
  pBuffer     - (O) Pointer to the byte transfer buffer
  ----------------------------------------------------------------------------
  Returns:

  ---------------------------------------------------------------------------*/

#define PokeSocketBytes(pSocket, pBuffer) PushSocketBytes(pSocket, pBuffer)

/*----------------------------------------------------------------------------
  PeekSocketBytes()
  ----------------------------------------------------------------------------
  Reads bytes from a socket.

  Note: Since all reads from a socket are consumptive, peeking bytes is
        equivalent to pulling bytes, thus peek is implemented as a macro.
  ----------------------------------------------------------------------------
  Parameters:

  pSocket     - (I) Pointer to the input socket
  pBuffer     - (I) Pointer to the byte transfer buffer
  ----------------------------------------------------------------------------
  Returns:

  The next byte from the input stream
  ---------------------------------------------------------------------------*/

#define PeekSocketBytes(pSocket, pBuffer) PullSocketBytes(pSocket, pBuffer)

#endif
