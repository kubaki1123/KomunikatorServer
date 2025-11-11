#include<iostream>
#include<asio.hpp>
#include"Server.h"

int main() {
	const int port = 8080;
	
	try {
		asio::io_context io;
		Server server(io,port);
		std::cout << "twoja pierwsza wiadomosc zostanie twoim nickiem wiec napisz jak sie nazywasz" << std::endl;

		server.startAccepting();
		io.run();
	}
	catch (std::exception& e) {
		std::cout << "wystapil blad" << e.what() << std::endl;
	}
	return 0;
}

