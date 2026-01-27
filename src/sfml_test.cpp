#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML: Point, Line, Rectangle");

    // ---------- Point ----------
    sf::Vertex point(sf::Vector2f(400.f, 100.f), sf::Color::White);

    // ---------- Line ----------
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(200.f, 300.f), sf::Color::White),
        sf::Vertex(sf::Vector2f(600.f, 300.f), sf::Color::White)
    };

    // ---------- Rectangle ----------
    sf::RectangleShape rect(sf::Vector2f(200.f, 100.f));
    rect.setPosition(300.f, 400.f);
    rect.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // draw point
        window.draw(&point, 1, sf::Points);

        // draw line
        window.draw(line, 2, sf::Lines);

        // draw rectangle
        window.draw(rect);

        window.display();
    }

    return 0;
}
