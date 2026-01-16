// инклюды


#include <SFML/Graphics.hpp>
#include <cmath>





// функция по нахождению дистанции между стенами и игроком
void findWallDistance(float startX, float startY, float dirX, float dirY, int gamemap[8][12], float &distance, int &wallType) {
    float x = startX;
    float y = startY;
    
    for (int step = 0; step < 200; step++) {
        x += dirX * 0.1f;
        y += dirY * 0.1f;
        
        int cellX = (int)x;
        int cellY = (int)y;
    
        if (cellX >= 0 && cellX < 12 && cellY >= 0 && cellY < 8) {
            if (gamemap[cellY][cellX] > 0) {
                distance = step * 0.1f;
                wallType = gamemap[cellY][cellX];
                return;
            }
        } 
    }
    
    distance = 100.0f;
    wallType = 0;
}

int main() {
    int gamemap[8][12] = {
        {4,4,4,4,4,4,4,4,4,4,4,4},
        {4,0,2,3,0,0,0,0,0,0,0,4},
        {4,0,0,3,0,0,0,0,0,1,0,4},
        {4,0,0,0,0,0,2,0,0,1,0,4},
        {4,0,0,0,3,0,2,0,0,0,0,4},
        {4,2,0,0,2,0,3,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,0,4},
        {4,4,4,4,4,4,4,4,4,4,4,4}
    };
    sf::Color rainbowTex [3] = {sf::Color::Yellow, sf::Color::Red, sf::Color::White};
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Color wallColor[5];
    wallColor[0] = sf::Color::Black;
    wallColor[1] = sf::Color::White;
    wallColor[2] = sf::Color::Red;
    wallColor[3] = sf::Color::Green;
    wallColor[4] = sf::Color(129, 189, 32);

    float posX = 1.5f;
    float posY = 1.5f;
    float angle = 0.0f;
    bool showFps = false;
    float dirX = cos(angle);
    float dirY = sin(angle);
    float planeX = -dirY * 0.66f;  
    float planeY = dirX * 0.66f;
    int frameCount;
    int fps;
    int timer;
    sf::Clock fpsTimer;
    sf::Clock deltaClock;

    
    sf::RenderWindow window(sf::VideoMode(1280, 768), "3D-game");
    window.setFramerateLimit(30);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        dirX = cos(angle);
        dirY = sin(angle);
        planeX = -dirY * 0.66f;
        planeY = dirX * 0.66f;
        float moveSpeed = 0.1f;
        float rotSpeed = 0.05f;
        static bool btnPresd = false;
        float deltaTime = deltaClock.restart().asSeconds();
        bool btnIsPresd = sf::Keyboard::isKeyPressed(sf::Keyboard::P);


        if (btnIsPresd && !btnPresd) {
            showFps = !showFps;
        }
        btnPresd = btnIsPresd;
        static bool btnMPresd = false;
        bool btnMIsPresd = sf::Keyboard::isKeyPressed(sf::Keyboard::M);


        static bool showMap = false;
        if (btnMIsPresd && !btnMPresd) {
            showMap = !showMap;
        }
        btnMPresd = btnMIsPresd;

        float baseMoveSpeed = 3.0f;  
        float currentMoveSpeed = baseMoveSpeed;
        float moveSpeedPerSecond = 3.0f;  
        float actualMoveSpeed = moveSpeedPerSecond * deltaTime;  
        float moveThisFrame = currentMoveSpeed * deltaTime;



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            moveSpeedPerSecond += 0.15f;
        } else {
            moveSpeedPerSecond += 0.0f;
        
    }






        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            float newX = posX + dirX * actualMoveSpeed;
            float newY = posY + dirY * actualMoveSpeed;
    
    // Сдвигаем точку проверки НА 0.2 от стены
            float checkX = newX + dirX * 0.4f;
            float checkY = newY + dirY * 0.4f;
    
            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;
    }
}
        float rightX = -dirY; 
        float rightY = dirX;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            float newX = posX - rightX * moveThisFrame;;
            float newY = posY - rightY * moveThisFrame;;

            float checkX = newX - rightX * 0.4f;
            float checkY = newY - rightY * 0.4f;

            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;

        }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            float newX = posX + rightX * moveThisFrame;;
            float newY = posY + rightY * moveThisFrame;;

            float checkX = newX + rightX * 0.4f;
            float checkY = newY + rightY * 0.4f;

            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;

        }
    }






        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            float newX = posX - dirX * actualMoveSpeed;
            float newY = posY - dirY * actualMoveSpeed;
    
    // Сдвигаем точку проверки НА 0.2 от стены
            float checkX = newX - dirX * 0.4f;
            float checkY = newY - dirY * 0.4f;
    
            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;
    }
}             
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    angle -= rotSpeed;
            }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    angle += rotSpeed;
            }
        

        sf::RectangleShape floor(sf::Vector2f(1280,384));
        floor.setPosition(0,384);
        floor.setFillColor(sf::Color(192,192,192));
        window.draw(floor);
        
        sf::RectangleShape potolok(sf::Vector2f(1280,384));
        potolok.setPosition(0,0);
        potolok.setFillColor(sf::Color(28, 170, 214));
        window.draw(potolok);









        for (int x = 0; x < 1280; x++) {
            // направление луча
            float cameraX = 2.0f * x / 1280.0f - 1.0f;
            float rayDirX = dirX + planeX * cameraX;
            float rayDirY = dirY + planeY * cameraX;
            
            //  находим стену
            float distance;
            int wallType;
            findWallDistance(posX, posY, rayDirX, rayDirY, gamemap, distance, wallType);
            
            //  вычисляем высоту стены
            float lineHeight = 768.0f / (distance + 0.0001f);  // +0.0001 чтобы не делить на 0
            if (lineHeight > 768.0f) lineHeight =  768.0f;  // ограничиваем
            
            float drawStart = 384.0f - lineHeight / 2.0f;
            float drawEnd = 384.0f + lineHeight / 2.0f;
            int texIndex = x % 3;



            // тени
            float brigtness = 1.0f; // яркость
            if (distance > 0.3f) {
                brigtness = 1.0 - (distance - 2.0f) * 0.4f; 
                if (brigtness > 1.0f) brigtness = 1.0f; // ограничиваем значения яркости
                if (brigtness < 0.8f) brigtness = 0.8f;
            }
            sf::Color originalColor = wallColor[wallType]; // яркость равняется типу стен

            sf::Color shadowColor(
                (int)(originalColor.r * brigtness),
                (int)(originalColor.g * brigtness),
                (int)(originalColor.b * brigtness)


            );


            if (distance < 200.0f) {
                float lineHeight = 1024.0f / (distance + 0.001f);
                float drawStart = 384.0f - lineHeight/2.0f;
                float drawEnd = 384.0f + lineHeight/2.0f;

                sf::Vertex Wall[2] = { 

                    sf::Vertex(sf::Vector2f(x, drawStart+2), shadowColor),
                    sf::Vertex(sf::Vector2f(x, drawEnd-2), shadowColor)
            };
                sf::Vertex bottomEdge[2] {
                    sf::Vertex(sf::Vector2f(x, drawEnd-2), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x, drawEnd), sf::Color::Black)
                };
                sf::Vertex upEdge[2] {
                    sf::Vertex(sf::Vector2f(x, drawStart+2), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x, drawStart), sf::Color::Black)
                };






                window.draw(Wall, 2, sf::Lines);
                window.draw(bottomEdge, 2, sf::Lines);
                window.draw(upEdge, 2, sf::Lines);
            }   


        }


        int mapScale = 10;
        int mapX = 10;
        int mapY = 20;


        if (showMap == true) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 12; x++) {
                    if (gamemap[y][x] > 0) {
                        sf::RectangleShape cell(sf::Vector2f(mapScale, mapScale));
                        cell.setPosition(mapX + x*mapScale, mapY + y*mapScale);
                        cell.setFillColor(wallColor[gamemap[y][x]]);
                        cell.setOutlineThickness(1.0f);
                        cell.setOutlineColor(sf::Color::Black);
                        window.draw(cell);
                }

            }
        }
            sf::CircleShape playerOnMap(2.0f);
            playerOnMap.setFillColor(sf::Color::Black);
            playerOnMap.setPosition(
                mapX + posX * mapScale - 3,  
                mapY + posY * mapScale - 3
        );
            window.draw(playerOnMap);

    }

        frameCount++;
        if (fpsTimer.getElapsedTime() >= sf::seconds(1.0f)) {
            fps = frameCount;
            frameCount = 0;
            fpsTimer.restart();

        }

        sf::RectangleShape crosshair(sf::Vector2f(1, 1));
        crosshair.setFillColor(sf::Color::White);
        crosshair.setPosition(640, 384);

        sf::RectangleShape square(sf::Vector2f(2, 2));
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(1); 
        square.setPosition(640, 384);
            
        window.draw(crosshair);
        window.draw(square);
        if (showFps == true) {
            sf::Text text;
            text.setFont(font);
            text.setString("FPS: " + std::to_string(fps));
            text.setPosition(1024, 5);
            window.draw(text);
        }



        window.display();
    }
    
    return 0;
}