#include <SFML/Graphics.hpp>

int main() {

    //The game window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "test Alpha-v2.0.5");
    window.setFramerateLimit(60);
    sf::Clock clock;

    //The player
    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition({200, 400});
    float xSPEED = 200.f;
    float JUMP = 700.f;
    
    //Physic and gravity for jump
    bool onFloor = true;
    float GRAVITY = 25.f;
    float maxFloor = 400.f;
    float yVelocity = 0.f;
    
    //The game heart
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            //Unique click
            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onFloor) {
                    yVelocity -= JUMP;
                    onFloor = false;
                }
            }
        }

        //Delta time for better performace
        float dt = clock.restart().asSeconds();
        sf::Vector2f movement(0.f, 0.f);

        //check if the player on air, the gravity will pull it
        if (!onFloor) {
            yVelocity += GRAVITY;
        }

        //Make the jump a part of move
        movement.y = yVelocity;

        //Horizontal move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            movement.x -= xSPEED;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            movement.x += xSPEED;
        }

        //Move
        player.move(movement * dt);

        //Check if the player is on floor
        sf::Vector2f pose = player.getPosition();
        if (pose.y + (player.getRadius() * 2) >= maxFloor) {
            pose.y = maxFloor - (player.getRadius() * 2);
            //Stop the gravity force if the player on floor
            yVelocity = 0.f;

            //say to the system to let player jump again
            onFloor = true;
        }
        player.setPosition(pose);

        window.clear();
        window.draw(player);
        window.display();
    }

}
