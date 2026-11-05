#include "Client.h"

void Client::connect()
{
	if (socket == nullptr)
	{
		socket = std::make_unique<sf::TcpSocket>();
	}

	if (socket->connect(*sf::IpAddress::fromString("127.0.0.1"), 53000) == sf::Socket::Status::Done)
	{
		std::cout << "You're connected\n";
		connected = true;
	}
	else
	{
		std::cout << "Failed to connect to 127.0.0.1::53000\n";
	}
}

void Client::input()
{
	while (running)
	{
		std::string str;
		std::getline(std::cin, str);
		std::cin.clear();

		if (connected)
		{
			socket->send(reinterpret_cast<char*>(str.data()), str.length());
		}
	}
}

void Client::run()
{
	running = true;
	std::thread input_thread([&] {input(); });
	input_thread.detach();

	while (running)
	{
		char static_buffer[1028];
		while (connected)
		{
			std::size_t recieved;
			sf::Socket::Status status = socket->receive(static_buffer, 1028, recieved);

			if (status == sf::Socket::Status::Disconnected)
			{
				connected = false;
				std::cout << "Clean disconnection\n";
				socket->disconnect();
				break;
			}
			else
			{
				if (recieved < 1028) static_buffer[recieved] = '\0';
				std::cout << static_buffer << "\n";
			}
		}
	}
}