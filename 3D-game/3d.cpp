#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
int screenW = 640;
int screenH = 460;
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
    int side = 0; // 0 - vertikal 1 - gorizontal
    int stepX = 0;
    int stepY = 0;
    float shagPoX;
    float shagPoY;
    int tekushX = (int)startX;
    int tekushY = (int)startY;
    kydaLuchX = cos(ugol);
    kydaLuchY = sin(ugol);
    shagPoX = fabsf(1.0f / kydaLuchX);
    shagPoY = fabsf(1.0f / kydaLuchY);
    float distance;
    

    if (kydaLuchX < 0) {
        stepX = -1;
        kydaLuchX = (startX - tekushX)  * shagPoX;
    } else {
        stepX = 1;
        kydaLuchX = (tekushX + 1.0f - startX)  * shagPoX;
    }

    if (kydaLuchY < 0) {
        stepY = -1;
        kydaLuchY = (startY - tekushY)  * shagPoY;
    } else {
        stepY = 1;
        kydaLuchY = (tekushY + 1.0f - startY)  * shagPoY;
    }
    bool naidenaStena = false;

    while (naidenaStena == false) {
        
        if (kydaLuchX < kydaLuchY) {
            kydaLuchX += shagPoX;
            tekushX += stepX;
            side = 0;
        } else {
            kydaLuchY += shagPoY;
            tekushY += stepY;
            side = 1;
        }

        if (map[tekushY][tekushX] == 1) {
            naidenaStena = true;
}
    }
    if (side == 0) {
        distance = (tekushX - startX + (1 - stepX) / 2.0f) / cos(ugol);
    } else {
        distance = (tekushY - startY + (1 - stepY) / 2.0f) / sin(ugol);
}






    return distance;
  
        
}

void drawVerticalLine(sf::RenderWindow& window, int luch, float visota, sf::Color color) {
    sf::RectangleShape line(sf::Vector2f(1.0f, visota));
    float startY = (screenH - visota) / 2.0f;  
    line.setPosition(luch, startY);
    line.setFillColor(color);
    window.draw(line);
}

void raycast(sf::RenderWindow& window, sf::Color color) {
    for(int luch = 0; luch < screenW; luch++) {
        float cameraX = 2.0f * luch / screenW - 1.0f;   
        float kydaLuch = playerAngle + cameraX * 0.5f;
        float distance = wallfound(playerX, playerY, kydaLuch);
        float perpDistance = distance * cos(cameraX * 0.5);
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
            playerX += cos(playerAngle) * speed;  
            playerY += sin(playerAngle) * speed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerX -= cos(playerAngle) * speed;  
            playerY -= sin(playerAngle) * speed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerX += sin(playerAngle) * speed;  
            playerY += -cos(playerAngle) * speed;
} 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerX += -sin(playerAngle) * speed;  
            playerY += cos(playerAngle) * speed;
}         
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            playerAngle -= cameraspeed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            playerAngle += cameraspeed;
}






        window.clear();
        sf::Color color (255, 255, 255);
        raycast(window, color);







        window.display();
    }

    return 0;
}






