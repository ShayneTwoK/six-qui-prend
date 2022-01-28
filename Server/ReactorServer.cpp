#include <Poco/Util/ServerApplication.h>
#include "Poco/Net/SocketAcceptor.h"
#include "ConnectionHandler.h"
class ReactorServer: public Poco::Util::ServerApplication {
public:
    ReactorServer(Game& game): _game(game) {
    
    };
	~ReactorServer() {};
    
    Game GetGame() {
        return _game;
    }
protected:

    Game _game;
	void initialize(Application& self) {
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	void unitialize() {
		ServerApplication::uninitialize();
	}

	int main(const std::vector<std::string>& args) {


        // Server Socket
        Poco::Net::ServerSocket svs(3490);
        // Reactor-Notifier
        Poco::Net::SocketReactor reactor;
        Poco::Timespan timeout(2000000); // 2Sec
        reactor.setTimeout(timeout);
        // Server-Acceptor
        Poco::Net::SocketAcceptor<ConnectionHandler> acceptor(svs, reactor);

        // Threaded Reactor
        Poco::Thread thread;
        thread.start(reactor);
        // Wait for CTRL+C
        waitForTerminationRequest();
        // Stop Reactor
        reactor.stop();
        thread.join();
        return Application::EXIT_OK;
	}

};