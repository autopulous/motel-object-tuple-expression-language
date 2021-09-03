/*----------------------------------------------------------------------------
  Motel Socket
 
  library implementation file
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

#include "motel.socket.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.socket.c - Copyright 2010-2011 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetMacAddresss
(
    motelMacAddress * pDestination,
    size_t pDestinationSize
)
{
{
    /*
    ** there is no mac address buffer
    */

    if (NULL == pDestination)
    {
        return (FALSE);
    }

    if (0 == pDestinationSize)
    {
        return (FALSE);
    }
}
#if defined _WIN32 || defined _WIN64
{
    PIP_ADAPTER_INFO lAdapterInfo;
    PIP_ADAPTER_INFO lAdapterInfoList = (PIP_ADAPTER_INFO) NULL;
    ULONG lOutBufLen = 0;
    ULONG lResult;

    /* 
    ** get the size that the adapter information buffer needs to be
    */

    lResult = GetAdaptersInfo((PIP_ADAPTER_INFO) NULL, &lOutBufLen);

    if (ERROR_BUFFER_OVERFLOW == lResult)
    {
        /*
        ** allocate the adapter information buffer
        */

        if (!SafeMallocBlock((void **) &lAdapterInfoList, lOutBufLen))
        {
            return (FALSE);
        }

        lResult = GetAdaptersInfo(lAdapterInfoList, &lOutBufLen);
    }

    /*
    ** verify that the GetAdaptersInfo was successful
    */
    
    if (NO_ERROR != lResult)
    {
        return (FALSE);
    }

    /*
    ** return the MAC Address of the first found Ethernet or wireless adapter interface
    */

    for (lAdapterInfo = lAdapterInfoList; NULL != lAdapterInfo; lAdapterInfo = lAdapterInfo->Next)
    {
        if ((MIB_IF_TYPE_ETHERNET == lAdapterInfo->Type || IF_TYPE_IEEE80211 == lAdapterInfo->Type) && pDestinationSize == lAdapterInfo->AddressLength)
        {
            /*
            ** a suitable adapter interface was found
            */

            CopyBlock(pDestination, pDestinationSize, lAdapterInfo->Address, lAdapterInfo->AddressLength, pDestinationSize);
        
            if (!SafeFreeBlock((void **) &lAdapterInfoList))
            {
                return (FALSE);
            }

            return (TRUE);
        }
    }

    /*
    ** no suitable adapter interface was found
    */

    memset(pDestination, 0, pDestinationSize);

    if (!SafeFreeBlock((void **) &lAdapterInfoList))
    {
        return (FALSE);
    }

    return (FALSE);
}
#else
#error need to implement MAC address determination for this compiler
#endif
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateSocket
(
    motelSocketHandle pSocket
)
{
    /*
    ** there is no socket
    */

    if (NULL == pSocket)
    {
        return (TRUE);
    }

    pSocket->result = motelResult_OK;

    if ('\0' == * pSocket->Port)
    {
        pSocket->result = motelResult_RequiredMember;

        return (FALSE);
    }

    if ('\0' != * pSocket->Host && '\0' == * pSocket->HostIP)
    {
        pSocket->result = motelResult_Corrupted;

        return (FALSE);
    }

    if ('\0' == * pSocket->Host && '\0' != * pSocket->HostIP)
    {
        pSocket->result = motelResult_Corrupted;

        return (FALSE);
    }

    if (0 == pSocket->socket)
    {
        pSocket->result = motelResult_Uninitialized;

        return (FALSE);
    }

    if (0 >= pSocket->TcpSegmentSize)
    {
        pSocket->result = motelResult_InvalidValue;

        return (FALSE);
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructSocket
(
    motelSocketHandle * pSocket,
    const char * pHost,
    const char * pPort
)
{
#if defined _WIN32 || defined _WIN64

    /*
    ** Start Windows Socket subsystem
    **
    ** WSAStartup must be the first Windows Sockets function called to specify
    ** the version of Windows Sockets required and retrieve details of the
    ** specific Windows Sockets implementation. Only issue further Windows
    ** Sockets functions after successfully calling WSAStartup.
    */

    {
        WSADATA lWsaData;

        if (SOCKET_OK != WSAStartup(MAKEWORD(1, 0), &lWsaData))
        {
            return (FALSE);
        }
    }

#endif

    /*
    ** allocate the socket control structure
    */

    if (!SafeMallocBlock((void **) pSocket, sizeof(motelSocket)))
    {
        WSACleanup();

        return (FALSE);
    }

    if (NULL == pHost)
    {
        if (!OpenAsServer(* pSocket, pPort))
        {
            DestructSocket(pSocket);

            return (FALSE);
        }
    }
    else
    {
        if (!OpenAsClient(* pSocket, pHost, pPort))
        {
            DestructSocket(pSocket);

            return (FALSE);
        }
    }

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructSocket
(
    motelSocketHandle * pSocket
)
{
    /*
    ** there is no socket
    */

    if (NULL == pSocket || NULL == * pSocket)
    {
        return (FALSE);
    }

    /*
    ** free the socket resources
    */

    if (UNUSED_SOCKET != (* pSocket)->socket)
    {
        closesocket((* pSocket)->socket);
    }

    if (UNUSED_SOCKET != (* pSocket)->clientSocket)
    {
        closesocket((* pSocket)->clientSocket);
    }

    /*
    ** free the socket control structure
    */

    if (!SafeFreeBlock((void **) pSocket))
    {
        return (FALSE);
    }

#if defined _WIN32 || defined _WIN64

    /*
    ** Stop Windows Socket subsystem
    **
    ** Applications must call one WSACleanup call for every successful
    ** WSAStartup call. If an application calls WSAStartup three times, it must
    ** call WSACleanup three times. The first two calls to WSACleanup do
    ** nothing except decrement an internal counter; the final WSACleanup call
    ** does all necessary resource deallocation.
    */

    WSACleanup();

#endif

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetSocketMember
(
    motelSocketHandle pSocket,
    motelSocketMember pMember,
    const void * pValue
)
{
    /*
    ** there is no socket object
    */

    if (NULL == pSocket)
    {
        return (FALSE);
    }

    pSocket->result = motelResult_OK;

    /*
    ** set member
    */

    switch (pMember)
    {
        case motelSocketMember_:

            return (TRUE);
    }

    if (NULL == pValue)
    {
        pSocket->result = motelResult_NullPointer;

        return (FALSE);
    }

    switch (pMember)
    {
    }

    pSocket->result = motelResult_InvalidMember;

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetSocketMember
(
    motelSocketHandle pSocket,
    motelSocketMember pMember,
    void * pValue
)
{
    int lOptionLength;

    /*
    ** there is no socket object
    */

    if (NULL == pSocket)
    {
        return (FALSE);
    }

    /*
    ** no return parameter
    */

    if (NULL == pValue)
    {
        return (FALSE);
    }

    /*
    ** result code is a special case because we want to set a result code for GetSocketMember()
    */

    if (motelSocketMember_Result == pMember)
    {
        * (motelResult *) pValue = pSocket->result;

        return (TRUE);
    }

    /*
    ** get member
    */

    pSocket->result = motelResult_OK;

    switch (pMember)
    {
        case motelSocketMember_SocketErrorNumber:

            lOptionLength = sizeof(int);

            if (SOCKET_ERROR == getsockopt(pSocket->socket, SOL_SOCKET, SO_ERROR, (char *) pValue, & lOptionLength))
            {
                pSocket->result = motelResult_Socket;

                return (FALSE);
            }

            return (TRUE);

        case motelSocketMember_Host:

            CopyString(pSocket->Host, (char *) pValue, sizeof(pSocket->Host));

            return (TRUE);

        case motelSocketMember_HostIP:

            CopyString(pSocket->HostIP, (char *) pValue, sizeof(pSocket->HostIP));

            return (TRUE);

        case motelSocketMember_Port:

            CopyString(pSocket->Port, (char *) pValue, sizeof(pSocket->Port));

            return (TRUE);

        case motelSocketMember_TcpSegmentSize:

            * (int *) pValue = pSocket->TcpSegmentSize;

            return (TRUE);
    }

    return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PushSocketBytes
(
   motelSocketHandle pSocket,
   motelBufferHandle pBuffer
)
{
    /*
    ** there is no socket
    */

    if (NULL == pSocket)
    {
        return (FALSE);
    }

    /*
    ** there is no output buffer
    */

    if (NULL == pBuffer)
    {
        pSocket->result = motelResult_NullPointer;

        return (FALSE);
    }

    if ('\0' == * pSocket->Host)
    {
        if (!PushAsServer(pSocket, pBuffer))
        {
            return (FALSE);
        }
    }
    else
    {
        if (!PushAsClient(pSocket, pBuffer))
        {
            return (FALSE);
        }
    }

    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION PullSocketBytes
(
   motelSocketHandle pSocket,
   motelBufferHandle pBuffer
)
{
    /*
    ** there is no socket
    */

    if (NULL == pSocket)
    {
        return (FALSE);
    }

    /*
    ** there is no output buffer
    */

    if (NULL == pBuffer)
    {
        pSocket->result = motelResult_NullPointer;

        return (FALSE);
    }

    if ('\0' == * pSocket->Host)
    {
        if (!PullAsServer(pSocket, pBuffer))
        {
            return (FALSE);
        }
    }
    else
    {
        if (!PullAsClient(pSocket, pBuffer))
        {
            return (FALSE);
        }
    }

    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}

/*----------------------------------------------------------------------------
  Private functions
  ----------------------------------------------------------------------------*/

boolean OpenAsServer
(
    motelSocketHandle pSocket,
    const char * pPort
)
{
    socketResult lSocketResult;

    struct sockaddr_in lSocketAddress;

    u_short lPort;

    int lTcpSegmentSize;

    int lOptionValue;
    int lOptionSize = (int) sizeof(lOptionValue);

    /*
    ** allocate an IPv4 Internet protocols stream socket
    */

    pSocket->socket = socket(PF_INET, SOCK_STREAM, 0);

    if (SOCKET_ERROR == pSocket->socket)
    {
        return (FALSE);
    }

    /*
    ** get the TCP segment size
    */

    lSocketResult = getsockopt(pSocket->socket, SOL_SOCKET, SO_RCVBUF, (char *) & lOptionValue, & lOptionSize);

    if (SOCKET_ERROR == lSocketResult)
    { 
        return (FALSE);
    }

    lTcpSegmentSize = lOptionValue;

    /*
    ** allow for reuse of the socket when binding
    */

    lOptionValue = TRUE;

    lSocketResult = setsockopt(pSocket->socket, SOL_SOCKET, SO_REUSEADDR, (const char *) & lOptionValue, lOptionSize);
    
    if (SOCKET_ERROR == lSocketResult)
    {
        return (FALSE);
    }

    /*
    ** create a socket IPv4 Internet address structure
    */

    lPort = (u_short) atoi(pPort);

    lSocketAddress.sin_family = AF_INET;
    lSocketAddress.sin_addr.s_addr = INADDR_ANY;
    lSocketAddress.sin_port = htons(lPort);

    memset(&lSocketAddress.sin_zero, 0, sizeof(lSocketAddress.sin_zero));

    /*
    ** assign the address to the socket
    */

    lSocketResult = bind(pSocket->socket, (struct sockaddr *) &lSocketAddress, sizeof(lSocketAddress));

    if (SOCKET_ERROR == lSocketResult)
    {
        return (FALSE);
    }

    /*
    ** tell socket to listen for connections
    */

    lSocketResult = listen(pSocket->socket, 10);

    if (SOCKET_ERROR == lSocketResult)
    {
        return (FALSE);
    }

    /*
    ** initialize the socket control structure
    */

    pSocket->clientSocket = UNUSED_SOCKET;

    * pSocket->HostIP = * CC_STRING_TERMINATOR;
    * pSocket->Host = * CC_STRING_TERMINATOR;

    CopyString(pPort, pSocket->Port, sizeof(pSocket->Port));

    if (0 < lTcpSegmentSize)
    {
        pSocket->TcpSegmentSize = lTcpSegmentSize;
    }
    else
    {
        pSocket->TcpSegmentSize = DEFAULT_TCP_SEGMENT_SIZE;
    }

    pSocket->result = motelResult_OK;

    return (TRUE);
}

boolean OpenAsClient
(
    motelSocketHandle pSocket,
    const char * pHost,
    const char * pPort
)
{
    socketResult lSocketResult;

    char * lHostIP;
    char lHost[MOTEL_HOST_SIZE];

    u_short lPort;

    unsigned long lBinaryAddress;
    struct hostent * lHostEnt;
    struct sockaddr_in lSocketAddress;

    int lTcpSegmentSize;
    int lOptionLength = (int) sizeof(lTcpSegmentSize);

    /*
    ** allocate an IPv4 Internet protocols stream socket
    */

    pSocket->socket = socket(PF_INET, SOCK_STREAM, 0);

    if (SOCKET_ERROR == pSocket->socket)
    {
        return (FALSE);
    }

    /*
    ** clean up host value
    */

    CopyString(pHost, lHost, sizeof(lHost));
    
    TrimString(lHost, CC_SPACE);

    /*
    ** convert the loopback local host IP address
    */

    if (EQUAL_TO == CompareiStrings((const char *) LOCAL_HOST, (const char *) lHost))
    {
        CopyString(LOCAL_HOST_IP, lHost, sizeof(lHost));
    }

    /* 
    ** Try to convert a numeric IP address (e.g. 10.0.0.200) to its binary representation
    */

    lBinaryAddress = inet_addr(lHost);

    if (INADDR_NONE != lBinaryAddress)
    {
        /*
        ** look up the remote host address by IP number
        */

        lHostEnt = gethostbyaddr((const char *) &lBinaryAddress, sizeof(lBinaryAddress), AF_INET);
    }
    else
    {
        /*
        ** not a numeric IP address, so look up the remote host address by name
        */

        lHostEnt = gethostbyname(lHost);
    }

    /*
    ** host look up failed
    */

    if (NULL == lHostEnt)
    {
        return (FALSE);
    }

    /*
    ** get the IP value of the host
    */

    lHostIP = inet_ntoa(* (struct in_addr *) * lHostEnt->h_addr_list);

    if (NULL == lHostIP)
    {
        return (FALSE);
    }

    /*
    ** create a socket IPv4 Internet address structure
    */

    lPort = (u_short) atoi(pPort);

    lSocketAddress.sin_family = AF_INET;
    lSocketAddress.sin_addr.s_addr = inet_addr(lHostIP);
    lSocketAddress.sin_port = htons(lPort);

    memset(&lSocketAddress.sin_zero, 0, sizeof(lSocketAddress.sin_zero));

    /*
    ** establish remote connection
    */

    lSocketResult = connect(pSocket->socket, (struct sockaddr *) &lSocketAddress, sizeof(lSocketAddress));

    if (SOCKET_ERROR == lSocketResult)
    { 
        return (FALSE);
    }

    /*
    ** get the TCP segment size
    */

    lSocketResult = getsockopt(pSocket->socket, SOL_SOCKET, SO_RCVBUF, (char *) &lTcpSegmentSize, &lOptionLength);

    if (SOCKET_ERROR == lSocketResult)
    { 
        return (FALSE);
    }

    /*
    ** initialize the socket control structure
    */

    pSocket->clientSocket = UNUSED_SOCKET;

    CopyString(pHost, pSocket->Host, sizeof(pSocket->Host));
    CopyString(pPort, pSocket->Port, sizeof(pSocket->Port));

    CopyString(lHostIP, pSocket->HostIP, sizeof(pSocket->HostIP));

    if (0 < lTcpSegmentSize)
    {
        pSocket->TcpSegmentSize = lTcpSegmentSize;
    }
    else
    {
        pSocket->TcpSegmentSize = DEFAULT_TCP_SEGMENT_SIZE;
    }

    pSocket->result = motelResult_OK;

    return (TRUE);
}

boolean PullAsServer
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
)
{
    SOCKET lSocket;

    byte * lBufferPointer;

    size_t lBytesRemaining;
    size_t lBytesReceived;

    /*
    ** get the buffer
    */

    SetBufferMember(pBuffer, motelBufferMember_First, (const void *) NULL);
    GetBufferMember(pBuffer, motelBufferMember_Cursor, (void *) &lBufferPointer);
    GetBufferMember(pBuffer, motelBufferMember_Size, (void *) &lBytesRemaining);

    /*
    ** clear the buffer
    */

    memset(lBufferPointer, 0, lBytesRemaining);

    /*
    ** create a socket to talk to a client, when
    ** the next client request arrives - the reponse to
    ** the client must occur on this socket
    */
    
    lSocket = accept(pSocket->socket, NULL, NULL);

    if (lSocket == INVALID_SOCKET)
    {
        pSocket->result = motelResult_Socket;

        return (FALSE);
    }

    /*
    ** wait for a client request to fill the buffer
    */

    lBytesReceived = recv(lSocket, (char *) lBufferPointer, (int) lBytesRemaining, 0);

    if (SOCKET_ERROR == lBytesReceived)
    {
        pSocket->result = motelResult_Reading;

        return (FALSE);
    }

    /*
    ** save the socket so a response can be sent
    */

    pSocket->clientSocket = lSocket;
    
    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}

boolean PullAsClient
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
)
{
    byte * lBufferPointer;

    int lBytesRemaining;
    int lBytesReceived;

    /*
    ** get the buffer
    */

    SetBufferMember(pBuffer, motelBufferMember_First, (const void *) NULL);
    GetBufferMember(pBuffer, motelBufferMember_Cursor, (void *) &lBufferPointer);
    GetBufferMember(pBuffer, motelBufferMember_Size, (void *) &lBytesRemaining);

    /*
    ** clear the buffer
    */

    memset(lBufferPointer, 0, lBytesRemaining);
    
    /*
    ** fill the buffer
    */

    while (lBytesRemaining)
    {
        lBytesReceived = recv(pSocket->socket, (char *) lBufferPointer, lBytesRemaining, 0);

        if (SOCKET_ERROR == lBytesReceived)
        {
            pSocket->result = motelResult_Reading;

            return (FALSE);
        }

        if (0 == lBytesReceived)
        {
            break;
        }

        lBytesRemaining -= lBytesReceived;
        lBufferPointer += lBytesReceived;
    }

    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}

boolean PushAsServer
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
)
{
    const byte * lBufferPointer;

    int lBytesRemaining;
    int lBytesSent;

    /*
    ** get the buffer
    */

    SetBufferMember(pBuffer, motelBufferMember_First, (const void *) NULL);
    GetBufferMember(pBuffer, motelBufferMember_Cursor, (void *) &lBufferPointer);
    GetBufferMember(pBuffer, motelBufferMember_Size, (void *) &lBytesRemaining);

    /*
    ** send the buffer in chunks of the TCP Segment Size or smaller
    */

    while (lBytesRemaining)
    {
        lBytesSent = send(pSocket->clientSocket, (const char *) lBufferPointer, (pSocket->TcpSegmentSize < lBytesRemaining) ? pSocket->TcpSegmentSize : lBytesRemaining, 0);

        if (SOCKET_ERROR == lBytesSent)
        {
            pSocket->result = motelResult_Writing;

            return (FALSE);
        }

        lBytesRemaining -= lBytesSent;
        lBufferPointer += lBytesSent;
    }

    /*
    ** close the client socket
    */

    if (SOCKET_ERROR == closesocket(pSocket->clientSocket))
    {
        pSocket->result = motelResult_Closing;

        return (FALSE);
    }

    pSocket->clientSocket = UNUSED_SOCKET;

    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}

boolean PushAsClient
(
    motelSocketHandle pSocket,
    motelBufferHandle pBuffer
)
{
    const byte * lBufferPointer;

    int lBytesRemaining;
    int lBytesSent;

    /*
    ** get the buffer
    */

    SetBufferMember(pBuffer, motelBufferMember_First, (const void *) NULL);
    GetBufferMember(pBuffer, motelBufferMember_Cursor, (void *) &lBufferPointer);
    GetBufferMember(pBuffer, motelBufferMember_Size, (void *) &lBytesRemaining);

    /*
    ** send the buffer in chunks of the TCP Segment Size or smaller
    */

    while (lBytesRemaining)
    {
        lBytesSent = send(pSocket->socket, (const char *) lBufferPointer, (pSocket->TcpSegmentSize < lBytesRemaining) ? pSocket->TcpSegmentSize : lBytesRemaining, 0);

        if (SOCKET_ERROR == lBytesSent)
        {
            pSocket->result = motelResult_Writing;

            return (FALSE);
        }

        lBytesRemaining -= lBytesSent;
        lBufferPointer += lBytesSent;
    }

    /*
    ** success
    */

    pSocket->result = motelResult_OK;

    return (TRUE);
}
 