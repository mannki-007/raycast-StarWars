#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
int screenW = 480;
int screenH = 320;
const int mapSizeY = 8;
const int mapSizeX = 8;
float playerX = 1.5f;
float playerY = 1.5f;
float speed = 0.05f;
float cameraspeed = 0.03f;
float playerAngle = 0.05f;
float luchX;
float luchY;
float kydaLuchX;
float kydaLuchY;
float startX;
float startY;
int map[mapSizeY][mapSizeX] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,1,0,0,1,0,0,1},
    {1,1,1,0,0,1,0,1},
    {1,0,1,0,0,0,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};
float wallfound(float startX, float startY, float ugol) {
    luchX = startX;
    luchY = startY;
    kydaLuchX = cos(ugol);
    kydaLuchY = sin(ugol);
    for(int step = 0; step < 1000; step++) {
        luchX += kydaLuchX * 0.05;
        luchY += kydaLuchY * 0.05;
        if (map[(int)luchY][(int)luchX] == 1) {
            return step * 0.05f;
        } 
        
   }
   return 20.0f;
}

void drawVerticalLine(sf::RenderWindow& window, int luch, float visota, sf::Color color) {
    sf::RectangleShape line(sf::Vector2f(1.0f, visota));
    float startY = (screenH - visota) / 2.0f;  
    line.setPosition(luch, startY);
    line.setFillColor(color);
    window.draw(line);
}

void raycast(sf::RenderWindow& window, sf::Color color) {
    for(int luch = 0; luch < 480; luch++) {
        float cameraX = 2.0f * luch / screenW - 1.0f;   
        float kydaLuch = playerAngle + cameraX * 0.5f;
        float distance = wallfound(playerX, playerY, kydaLuch);
        float perpDistance = distance * cos(cameraX * 0.5f);
        if (perpDistance < 0.001f) perpDistance = 0.001f;  
        float visota = screenH / perpDistance;
        
        drawVerticalLine(window, luch, visota, sf::Color::Red);

    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(screenW, screenH), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        window.setFramerateLimit(40);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerX += cos(playerAngle) * speed;  // просто двигаем
            playerY += sin(playerAngle) * speed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerX -= cos(playerAngle) * speed;  // просто двигаем
            playerY -= sin(playerAngle) * speed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerAngle -= cameraspeed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerAngle += cameraspeed;
}






        window.clear();
        sf::Color color (255, 255, 255);
        raycast(window, color);







        window.display();
    }

    return 0;
}






