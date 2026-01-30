#include <SFML/Graphics.hpp>
#include "MemoryTracker.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    auto window = sf::RenderWindow(
        sf::VideoMode(800, 600), "memory graph tool",
        sf::Style::Default, settings);
    window.setFramerateLimit(simulationSpeed);

    // scaling: higher scaling means bigger graph
    sf::RectangleShape point;
    point.setSize(sf::Vector2f(pointWidth, pointWidth));
    point.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (currentFrame % graphDevidedBy == 0) graph();

        point.setPosition(currentFrame/graphScalingHorizontal, window.getSize().y
            - point.getSize().y - (float) (totalAllocated/graphScalingVertical));
        window.draw(point);
        window.display();
        currentFrame++;

    }

    return 0;
}
