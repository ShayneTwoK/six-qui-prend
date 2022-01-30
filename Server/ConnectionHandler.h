#pragma once
#include <string>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/AutoPtr.h>
#include "Game.h"
using namespace Poco::Net;
class ConnectionHandler
{
public:

    /**
     * @Brief Constructor of the Connection Handler
     * @Note Each object is unique to an accepted connection
     * @Param SteamSocket is the socket accepting the connections
     * @See SocketAcceptor http://pocoproject.org/docs/Poco.Net.SocketAcceptor.html
     * @Param SocketReactor is the reacting engine (threaded) which creates notifications about the socket
     */
    ConnectionHandler(StreamSocket&, SocketReactor&);

    /**
     * @Brief Destructor
     */
    ~ConnectionHandler();

    /**
    * @Brief Event Handler when Socket becomes Readable, i.e: there is data waiting to be read
    */
    void onSocketReadable(const Poco::AutoPtr<ReadableNotification>& pNf);

    /**
    * @Brief Event Handler when Socket was written, i.e: confirmation of data sent away (not received by client)
    */
    void onSocketWritable(const Poco::AutoPtr<WritableNotification>& pNf);

    /**
    * @Brief Event Handler when Socket was shutdown on the remote/peer side
    */
    void onSocketShutdown(const Poco::AutoPtr<ShutdownNotification>& pNf);

    /**
    * @Brief Event Handler when Socket throws an error
    */
    void onSocketError(const Poco::AutoPtr<ErrorNotification>& pNf);

    /**
    * @Brief Event Handler when Socket times-out
    */
    void onSocketTimeout(const Poco::AutoPtr<TimeoutNotification>& pNf);


    /**
    * @Brief Event Handler when Socket times-out
    */
    void onSocketStartConnecting();

private:

    /**
     * @Brief Read bytes from the socket, depending on available bytes on socket
     */
    void readBytes(int size);

    /**
     * @Brief Send message to the socket
     * @Param std::string is the message (null terminated)
     */
    void sendMessage(std::string);

    /// Stream Socket
    StreamSocket _socket;

    /// Socket Reactor-Notifier
    SocketReactor& _reactor;

    enum {
        BUFFER_SIZE = 1024
    };
    /// Received Data Buffer
    char in_buffer[BUFFER_SIZE];

};