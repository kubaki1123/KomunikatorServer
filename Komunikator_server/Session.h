#pragma once
#include<iostream>
#include<asio.hpp>
#include<memory>

struct Adres {
	std::string odbiorca;
	std::string wiadomosc;
};

class Session: public std::enable_shared_from_this<Session>
{
private:
	asio::ip::tcp::socket socket_;
	asio::streambuf buffer_;
	std::string nick;
	void handleRead(const asio::error_code& error, std::size_t bytes_transformed);
	void handleWrite();
	Adres parseMessage(std::string tekst);
public:
	Session(asio::io_context& io);
	asio::ip::tcp::socket& socket();
	void start();
};