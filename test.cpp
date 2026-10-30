#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "test Alpha-v2.0.5");
    window.setFramerateLimit(60);
    sf::Clock clock;

    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition({200, 400});
    float xSPEED = 200.f;
    float JUMP = 700.f;
    
    bool onFloor = true;
    float GRAVITY = 25.f;
    float maxFloor = 400.f;
    float yVelocity = 0.f;
    const float GROUND_Y = 400.f;
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onFloor) {
                    yVelocity -= JUMP;
                    onFloor = false;
                }
            }
        }

        float dt = clock.restart().asSeconds();
        sf::Vector2f movement(0.f, 0.f);

        if (!onFloor) {
            yVelocity += GRAVITY;
        }

        movement.y = yVelocity;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            movement.x -= xSPEED;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            movement.x += xSPEED;
        }

        player.move(movement * dt);

        sf::Vector2f pose = player.getPosition();
        if (pose.y + (player.getRadius() * 2) >= maxFloor) {
            pose.y = maxFloor - (player.getRadius() * 2);
            yVelocity = 0.f;
            onFloor = true;
        }
        player.setPosition(pose);

        window.clear();
        window.draw(player);
        window.display();
    }

}
