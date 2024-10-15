#include <iostream>
#include <optional>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "PackageHeader.h"

using std::cout;
using std::vector;
using std::endl;
using std::string;

constexpr unsigned int gPort = 55001;

void Keep_Alive(sf::UdpSocket& socket, PackageHeader header, sf::IpAddress ip )
{
	vector <char> Buffer(1024);
	size_t				Recieved = 0;
	std::optional < sf::IpAddress> Sender;
	unsigned short		Sender_Port;

	if (
		socket.receive
		(
			Buffer.data(),
			Buffer.size(),
			Recieved,
			Sender,
			Sender_Port
		)
		==
		sf::Socket::Status::Done
		)
	{
		cout << "Message recieved from sender " << string(Buffer.begin(), Buffer.end() + Recieved) << std::endl;
	}

	sf::sleep(sf::seconds(5));
	cout << "Im still alive :)" << endl;

	if
		(
			socket.send
			(
				&header,
				sizeof(PackageHeader),
				ip,
				gPort
			)
			!=
			sf::Socket::Status::Done
			)
	{
		cout << "Failed to be alive. :(" << endl;
	}
}

void connectToUDPServer()
{
	// Create a socket
	sf::UdpSocket socket;

	// Save the localhost IP address
	std::optional<sf::IpAddress> ip = sf::IpAddress::getLocalAddress();

	// Create the package header
	PackageHeader header
	{
		PackageType::Connect,
		// No more data to send
		size_t(0u)
	};

	// Try to send the header to the server
	if (
		socket.send
		(
			&header,
			sizeof(PackageHeader),
			*ip,
			gPort
		)
		!=
		   sf::Socket::Status::Done
		)
	{
		cout << "Failed to connect to the server" << endl;
		return;
	}

	cout << "Connected to the server" << ip.value() << endl;

	////////////// FUNCION NUEVA ////////////
	while (true)
	{
		Keep_Alive(socket, header, *ip);
	}
}

int main()
{
	connectToUDPServer();
	return 0;
}