#include "ConnectionHandler.h"
#include <Poco/Util/Application.h>
#include <Poco/NObserver.h>
#include <sstream>
#include <iostream>
#include "GameEventHandler.h"
#include "EventType.h"
#include "RequestBody.h"

using nlohmann::json;
ConnectionHandler::ConnectionHandler(StreamSocket& socket, SocketReactor& reactor) :_reactor(reactor), _socket(socket)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	app.logger().information("Connection from " + _socket.peerAddress().toString());
	_reactor.addEventHandler(_socket, Poco::NObserver<ConnectionHandler, ReadableNotification>(*this, &ConnectionHandler::onSocketReadable));
	_reactor.addEventHandler(_socket, Poco::NObserver<ConnectionHandler, ShutdownNotification>(*this, &ConnectionHandler::onSocketShutdown));
	_reactor.addEventHandler(_socket, Poco::NObserver<ConnectionHandler, TimeoutNotification>(*this, &ConnectionHandler::onSocketTimeout));
	onSocketStartConnecting();
}

ConnectionHandler::~ConnectionHandler()
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	app.logger().information("Disconnecting from" + _socket.peerAddress().toString());
	_reactor.removeEventHandler(_socket, Poco::NObserver<ConnectionHandler, ReadableNotification>(*this, &ConnectionHandler::onSocketReadable));
	_reactor.removeEventHandler(_socket, Poco::NObserver<ConnectionHandler, ShutdownNotification>(*this, &ConnectionHandler::onSocketShutdown));
	_reactor.removeEventHandler(_socket, Poco::NObserver<ConnectionHandler, TimeoutNotification>(*this, &ConnectionHandler::onSocketTimeout));
}

void ConnectionHandler::onSocketReadable(const Poco::AutoPtr<ReadableNotification>& pNf)
{

	int n = _socket.receiveBytes(in_buffer, sizeof in_buffer);
	if (n > 0)
	{
		this->readBytes(n);
	}
	else {
		delete this;
	}
}

void ConnectionHandler::onSocketShutdown(const Poco::AutoPtr<ShutdownNotification>& pNf)
{
	std::cout << "Shutdown!" << std::endl << std::flush;
	_socket.close();
	delete this;
}

void ConnectionHandler::onSocketError(const Poco::AutoPtr<ErrorNotification>& pNf)
{
	std::cout << "Error!" << std::endl << std::flush;
	delete this;
}

void ConnectionHandler::onSocketTimeout(const Poco::AutoPtr<TimeoutNotification>& pNf)
{
	std::cout << "TIMEOUT!" << std::endl << std::flush;
}

void ConnectionHandler::onSocketStartConnecting()
{
	std::cout << "Add player";
	//define socket handle
	Game* game = GameEventHandler::get_instance()->GetGame();
	game->addPlayer(new Player(_reactor, _socket));
}

void ConnectionHandler::readBytes(int size)
{
	std::string message(in_buffer, size);

	json j = json::parse(message);

	std::string key = j["key"];
	std::string body = j["body"];

	RequestBody request(key, body, _socket.impl()->sockfd());
	GameEventHandler::get_instance()->handleEvent(&request);
}

void ConnectionHandler::sendMessage(std::string message)
{
	const char* b = message.c_str();
	_socket.sendBytes(b, sizeof b);
}
