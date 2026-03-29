#include "SFML/Graphics.hpp"

using namespace std;

const int winWid = 800, winHig = 800;
const float changeTime = 0.1f;

int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode(winWid, winHig), "Dice Roller");
    window.setFramerateLimit(60);

    //Textures
    sf::Texture d1;
    sf::Texture d2;
    sf::Texture d3;
    sf::Texture d4;
    sf::Texture d5;
    sf::Texture d6;
    d1.loadFromFile("dice1.png");
    d2.loadFromFile("dice2.png");
    d3.loadFromFile("dice3.png");
    d4.loadFromFile("dice4.png");
    d5.loadFromFile("dice5.png");
    d6.loadFromFile("dice6.png");

    sf::Texture txts[] = { d1, d2, d3, d4, d5, d6 };

    //Sprites
    sf::Sprite sprite;
    sprite.setTexture(d1);
    sprite.setPosition(sf::Vector2f(winWid / 2 - 1.5f * sprite.getLocalBounds().width, winHig/ 2 - sprite.getLocalBounds().height / 2));

    sf::Sprite sprite2;
    sprite2.setTexture(d1);
    sprite2.setPosition(sf::Vector2f(winWid / 2 + 0.5f * sprite2.getLocalBounds().width, winHig / 2 - sprite2.getLocalBounds().height / 2));

    //Text
    sf::Text t1;
    sf::Text t2;
    sf::Text instr;
    sf::Font font;
    font.loadFromFile("Minecraft.ttf");
    t1.setFont(font);
    t2.setFont(font);
    t1.setCharacterSize(60);
    t2.setCharacterSize(60);
    t1.setOutlineThickness(4);
    t2.setOutlineThickness(4);
    t1.setPosition(sf::Vector2f(winWid / 2 - sprite.getLocalBounds().width - 0.5f * t1.getCharacterSize() / 2, winHig / 2 - 
                                sprite.getLocalBounds().height / 2 - 2 * t1.getCharacterSize()));
    t2.setPosition(sf::Vector2f(winWid / 2 + sprite2.getLocalBounds().width - 0.5f * t2.getCharacterSize() / 2, winHig / 2 -
                                sprite2.getLocalBounds().height / 2 - 2 * t2.getCharacterSize()));

    instr.setFont(font);
    instr.setCharacterSize(40);
    instr.setOutlineThickness(4);
    instr.setString("Hold Space to Roll");
    instr.setPosition(sf::Vector2f(25, 25));


    //Logical variables
    int r1 = 1;
    int r2 = 1;

    //Clock
    float currTime = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //If rolling
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (clock.getElapsedTime().asSeconds() - currTime >= changeTime) {
                int tmp1 = r1;
                do {
                    r1 = rand() % 6 + 1;
                } while (r1 == tmp1);
                int tmp2 = r2;
                do {
                    r2 = rand() % 6 + 1;
                } while (r2 == tmp2);
                sprite.setTexture(txts[r1 - 1]);
                sprite2.setTexture(txts[r2 - 1]);
                currTime = clock.getElapsedTime().asSeconds();
            }
        }

        //Text
        t1.setString(to_string(r1));
        t2.setString(to_string(r2));

        //Render
        window.clear(sf::Color(0, 100, 0));
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(t1);
        window.draw(t2);
        window.draw(instr);
        window.display();
    }

    return 0;
}