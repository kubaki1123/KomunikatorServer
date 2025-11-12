#pragma once
#include<asio.hpp>
#include<vector>
#include<memory>


class Session;
class Server {
private:
	void handleAccept(std::shared_ptr<Session> new_session, const asio::error_code& error);
	asio::ip::tcp::acceptor accept;
	std::vector<std::shared_ptr<Session>> active_sessions;

public:
	Server(asio::io_context& io, int port);
	void broadcast(std::string& nadawca, std::string message);
	void send_private(std::string& nadawca, std::string& odbiorca, std::string message);
	void startAccepting();
	void sendInfo(std::shared_ptr<Session> who_asked);
};

