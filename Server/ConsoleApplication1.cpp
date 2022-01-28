// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Util/ServerApplication.h"
#include "ReactorServer.cpp"
using namespace std;
class newConnection : public Poco::Net::TCPServerConnection {
public:
    newConnection(const Poco::Net::StreamSocket& s) :
        Poco::Net::TCPServerConnection(s) {
    }

    void run() {
        std::cout << "New connection from: " << socket().peerAddress().host().toString() << std::endl << std::flush;
        bool isOpen = true;
        Poco::Timespan timeOut(10, 0);
        unsigned char incommingBuffer[1000];
        while (isOpen) {
            if (socket().poll(timeOut, Poco::Net::Socket::SELECT_READ) == false) {
                cout << "TIMEOUT!" << endl << flush;
            }
            else {
                cout << "RX EVENT!!! ---> " << flush;
                int nBytes = -1;

                try {
                    nBytes = socket().receiveBytes(incommingBuffer, sizeof(incommingBuffer));
                }
                catch (Poco::Exception& exc) {
                    //Handle your network errors.
                    cerr << "Network error: " << exc.displayText() << endl;
                    isOpen = false;
                }


                if (nBytes == 0) {
                    cout << "Client closes connection!" << endl << flush;
                    isOpen = false;
                }
                else {
                    cout << "Receiving nBytes: " << nBytes << endl << flush;
                }
            }
        }
        cout << "Connection finished!" << endl << flush;
    }
};

int main(int argc, char** argv) {

    ////Create a server socket to listen.
    //Poco::Net::ServerSocket svs(3490);

    ////Configure some server params.
    //Poco::Net::TCPServerParams* pParams = new Poco::Net::TCPServerParams();
    //pParams->setMaxThreads(4);
    //pParams->setMaxQueued(4);
    //pParams->setThreadIdleTime(100);

    ////Create your server
    //Poco::Net::TCPServer myServer(new Poco::Net::TCPServerConnectionFactoryImpl<newConnection>(), svs, pParams);
    //myServer.start();

    //while (1);

    //return 0;
    Game game;
    return ReactorServer(game).run(argc, argv);
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
