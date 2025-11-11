#pragma once
#include<asio.hpp>
#include<vector>
#include<memory>
#include"Session.h"
class Server {
private:
	void handleAccept(std::shared_ptr<Session> new_session, const asio::error_code& error);
	asio::ip::tcp::acceptor accept;
	std::vector<std::shared_ptr<Session>> active_sessions;

public:
	Server(asio::io_context& io, int port);

	void startAccepting();
};

