#include"Server.h"
#include<iostream>
#include"Session.h"

Server::Server(asio::io_context& io, int port)	// definicja konstruktora
	:accept(io, asio::ip::tcp::endpoint(asio::ip::make_address("127.0.0.1"), port)) //: mowi ze zanim wykonamy kod w {} musimy zainicjalizowac nastepujace pola
{
	std::cout << "nasluchiwanie na porcie" << port << std::endl;
}
void Server::handleAccept(std::shared_ptr<Session> new_session, const asio::error_code& error){
	
	if (!error) {
		std::cout << "nowy klient polaczony" << std::endl;
		Server::active_sessions.push_back(new_session);
		new_session->start();
		
	}
	else {
		std::cout << "error" << error.message() << std::endl;
	}
	startAccepting();
}


void Server::startAccepting()
{
	auto new_session = std::make_shared<Session>(accept.get_executor().context());
	accept.async_accept(new_session->socket(),
		[this, new_session](const asio::error_code& error) {
		handleAccept(new_session, error);
		}
	);
}	