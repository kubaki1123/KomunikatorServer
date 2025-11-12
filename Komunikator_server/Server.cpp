#include"Server.h"
#include"Session.h"
#include<iostream>

Server::Server(asio::io_context& io, int port)	// definicja konstruktora
	:io_context_ref_(io), accept(io, asio::ip::tcp::endpoint(asio::ip::make_address("127.0.0.1"), port)) //: mowi ze zanim wykonamy kod w {} musimy zainicjalizowac nastepujace pola
{
	std::cout << "nasluchiwanie na porcie" << port << std::endl;
}

void Server::broadcast(std::string& nadawca, std::string message)
{
	std::string wiadomosc = "[wiadomosc od " + nadawca + "]" + message + "\n";

	for (int i = 0; i < active_sessions.size(); i++) {

		active_sessions[i]->write(wiadomosc);
	}
	return;
}

void Server::send_private(std::string& nadawca, std::string& odbiorca, std::string message)
{
	std::string wiadomosc = "[wiadomosc od " + nadawca + "]" + message + "\n";
	for (int i = 0; i < active_sessions.size(); i++) {
		if (active_sessions[i]->get_nickname() == odbiorca) {
			active_sessions[i]->write(wiadomosc);
			return;
		}
	}
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
	auto new_session = std::make_shared<Session>(io_context_ref_,*this);
	accept.async_accept(new_session->socket(),
		[this, new_session](const asio::error_code& error) {
		handleAccept(new_session, error);
		}
	);
}
void Server::sendInfo(std::shared_ptr<Session> who_asked)
{
	std::string message = "----Aktyrni urzytkownicy----";
	for (int i = 0; i < active_sessions.size(); i++) {
		message += active_sessions[i]->get_nickname() + "\n";
		
	}
	message += "-----------------\n";
	who_asked->write(message);
}
