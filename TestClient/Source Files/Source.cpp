#include <iostream>
#include <optional>

#include <SFML/Network.hpp>

#include "PackageHeader.h"

using std::cout;
using std::endl;

constexpr unsigned int gPort = 55001;

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
}

int main()
{
	connectToUDPServer();
	return 0;
}