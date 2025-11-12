#pragma once
#include<iostream>
#include<asio.hpp>
#include<memory>
#include<string>


class Server;
struct Adres {
	std::string odbiorca;
	std::string wiadomosc;
};

class Session: public std::enable_shared_from_this<Session>
{
private:
	Server& server_ref_;
	asio::ip::tcp::socket socket_;
	asio::streambuf buffer_;
	std::string nick;
	void handleRead(const asio::error_code& error, std::size_t bytes_transformed);
	void handleWrite(const asio::error_code& error, std::size_t bytes_transformed);
	Adres parseMessage(std::string tekst);
public:
	std::string get_nickname();
	Session(asio::io_context& io,Server& serverRef);
	asio::ip::tcp::socket& socket();
	void start();
	void write(const std::string& message);
};