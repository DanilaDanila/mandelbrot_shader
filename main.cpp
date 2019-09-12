#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <unistd.h>
#include <iostream>

int main()
{
	std::cout<<"\n213";

    sf::RenderWindow window(sf::VideoMode(700, 700), "Mandelbrot set");
    window.setFramerateLimit(60);
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);

    sf::Shader shader;
    shader.loadFromFile("shader.frag", sf::Shader::Fragment);

    sf::Texture tex;
    tex.create(700, 700);
    sf::Sprite result;
    result.setTexture(tex);

    float pos_x = 0.0;
    float pos_y = 0.0;
    float zoom = 1.0;
    float move_speed = 0.000003;
    int depth = 20;

    bool unpressed = true;
    sf::Clock timer;

    sf::Clock clock;
    float time;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        
        if(!unpressed)
        {
            unpressed = (timer.getElapsedTime().asMilliseconds() > 100);
            /*
            unpressed = (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::X)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
                        (!sf::Keyboard::isKeyPressed(sf::Keyboard::S));
            */
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pos_x -= move_speed*time/zoom;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pos_x += move_speed*time/zoom;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                pos_y += move_speed*time/zoom;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                pos_y -= move_speed*time/zoom;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                if(zoom > 0) zoom /= 0.9;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                zoom *= 0.9;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if(depth > 0) depth --;
                unpressed = false;
                timer.restart();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                depth++;
                unpressed = false;
                timer.restart();
            }
        }

		std::cout<<"\rX: "<<pos_x<<" | Y: "<<pos_y<<
				 " | -x "<<pos_x<<" -y "<<pos_y;;

        shader.setUniform("depth", depth);
        shader.setUniform("resolution", (int)window.getSize().x);
        shader.setUniform("pos_x", pos_x);
        shader.setUniform("pos_y", pos_y);
        shader.setUniform("zoom", zoom);

        window.draw(result, &shader);

        window.display();
        usleep(1000);
    }
    return 0;
}
