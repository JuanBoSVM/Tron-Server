#include <iostream>
#include <optional>
#include <vector>
#include <string>

#include <SFML/Network.hpp>

#include "PackageHeader.h"

using std::string;
using std::cout;
using std::endl;

constexpr unsigned int gPort = 55001;

void printStatus(unsigned int clients)
{
	system("cls");
	cout
		<< "Server is listening on port " << gPort << endl
		<< "Clients connected: " << clients << endl;
}

void startUDPServer(unsigned int port)
{
	// Create a socket and bind it to the port `port`
	sf::UdpSocket socket;
	socket.bind(port);

	unsigned int clientsConnected { 0u };


	printStatus(clientsConnected);

	// Create a buffer to hold the incoming data's header
	std::vector<char> headerBuffer(sizeof(PackageHeader));

	// Wait for a message
	while (true)
	{
		// Initialize variables to hold the sender's IP address and port
		size_t recieved { 0 };
		std::optional<sf::IpAddress> sender;
		unsigned short senderPort;

		if (
			// Receive the header of the incoming message
			socket.receive
			(
				headerBuffer.data(),
				sizeof(PackageHeader),
				recieved,
				sender,
				senderPort
			)
			// Check if the receive operation failed
			!=
			sf::Socket::Status::Done
			)
		{
			// If the receive operation failed, skip the rest of the loop
			continue;
		}

		// Convert the buffer to a PackageHeader
		PackageHeader* header { reinterpret_cast<PackageHeader*>(headerBuffer.data()) };

		// Determine if the message is a connection request
		clientsConnected += header->type == PackageType::Connect ? 1u : 0u;

		// Print the status of the server
		printStatus(clientsConnected);
	}
}

int main()
{
	startUDPServer(gPort);
	return 0;
}