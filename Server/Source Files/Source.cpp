#include <optional>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main()
{
	sf::Image icon(R"(Assets\SFML\Icon Small.png)");
	sf::RenderWindow window
	(
		sf::VideoMode({ 700u, 700u }),
		"Tron Server",
		sf::Style::Default,
		sf::State::Windowed,
		{}
	);

	window.setIcon({ icon.getSize().x, icon.getSize().y }, icon.getPixelsPtr());
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);

	std::optional<sf::Event> lastEvent;

	while (window.isOpen())
	{

		lastEvent = window.pollEvent();

		while (lastEvent.has_value())
		{
			if (lastEvent->is<sf::Event::Closed>()) { window.close(); }
			lastEvent = window.pollEvent();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}