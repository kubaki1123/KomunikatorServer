#include"Session.h"

Adres Session::parseMessage(std::string tekst) {
	int i = 0;
	Adres nowy_adres;
	while (tekst[i] != ':') {
		if (i >= tekst.size()) {
			
			nowy_adres.odbiorca = nick;
			nowy_adres.wiadomosc = "nieprawidlowy format wiadomosci wpisujemy najpierw odbiorce potem znak : a na koncu wiadomosc. np. Bob:czesc";
			return nowy_adres;
		}
		nowy_adres.odbiorca = nowy_adres.odbiorca + tekst[i];
		i++;
	}

	for (int j = i + 1; j < tekst.size(); j++) {
		nowy_adres.wiadomosc = nowy_adres.wiadomosc + tekst[j];
	}
	return nowy_adres;
}

void Session::handleRead(const asio::error_code& error, std::size_t bytes_transformed)
{
	if (!error) {
		std::istream stream(&buffer_);
		std::string tekst;
		std::getline(stream, tekst);

		if (nick == "") {
			nick = tekst;
		}
		else {
			Adres nowy_adres = parseMessage(tekst);

			std::cout << "[klient 1]" << tekst << std::endl;
		}
		asio::async_read_until(socket_, buffer_, "\n",
			[this, self = shared_from_this()](const asio::error_code& error, std::size_t bytes_transformed) {
				handleRead(error, bytes_transformed);
			}

		);
	}
	else if (error == asio::error::eof) {
		std::cout << "klient sie rozlaczyl" << std::endl;
		
	}
	else {
		std::cout << "wystapil blad odczytu" << std::endl;
	}
}

void Session::handleWrite()
{
}

Session::Session(asio::io_context& io)
	:socket_(io)
{

}

asio::ip::tcp::socket& Session::socket() {
	return socket_;
}

void Session::start()
{
	std::cout << "sesja sie rozpoczela!" << std::endl;
	asio::async_read_until(socket_, buffer_, "\n",
		[this, self = shared_from_this()](const asio::error_code& error,std::size_t bytes_transformed) {
			handleRead(error, bytes_transformed);
		}
	
	);
}
