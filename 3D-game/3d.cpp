// https://github.com/mannki-007/raycast-StarWars/tree/main



// инклюды


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>




// функция по нахождению дистанции между стенами и игроком
void findWallDistance(float startX, float startY, float rayDirX, float rayDirY, int gamemap[8][12], float &distance, int &wallType, int &side) {
    
    bool hit = false;
    int mapX = (int)startX;
    int mapY = (int)startY;
    float deltaDistX = (rayDirX == 0) ? 1e30f : fabsf(1.0f / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30f : fabsf(1.0f / rayDirY);
    float sideDistX,sideDistY;
    side = 0;
    int stepX;
    int stepY;
    int steps = 0;

    if (rayDirX > 0) {
        stepX = 1;
        sideDistX = (mapX + 1.0f - startX) * deltaDistX;
    } else {
        stepX = -1;
        sideDistX = (startX - mapX) * deltaDistX; 
        
    }

    if (rayDirY > 0) {
        stepY = 1;
        sideDistY = (mapY + 1.0f - startY) * deltaDistY;
    } else {
        stepY = -1;
        sideDistY = (startY - mapY) * deltaDistY;
    }

    while(!hit && steps < 1000) {
        steps++;
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;

        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (mapX >= 0 && mapX < 12 && mapY >= 0 && mapY < 8) {
            if (gamemap[mapY][mapX] > 0) {
            hit = true;
            wallType = gamemap[mapY][mapX];
        }
        } else {
        hit = true;  // за картoй
            }
        }
    if (side == 0) {
        distance = (mapX - startX + (1 - stepX) / 2.0f) / rayDirX;
    } else {
        distance = (mapY - startY + (1 - stepY) / 2.0f) / rayDirY;
    }

    }


int main() {
    int gamemap[8][12] = {
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1,0,1},
        {1,0,0,0,0,0,1,0,0,1,0,1},
        {1,0,2,0,1,0,1,0,0,0,0,1},
        {1,1,0,0,1,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1}
    };
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Color wallColor[3];
    wallColor[0] = sf::Color::Black;
    wallColor[1] = sf::Color::White;
    wallColor[2] = sf::Color(129, 189, 32);



    sf::Texture wallTexture;
    wallTexture.loadFromFile("textures/metallWall.png");
    int textureWidth = wallTexture.getSize().x;   // 128x
    int textureHeight = wallTexture.getSize().y;  // 128y


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

        float speed = 3.0f * deltaTime;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
           speed *= 1.3f;
        } else {
           speed = 3.0f * deltaTime;
        
    }






        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            float newX =  posX + dirX * speed;
            float newY =  posY + dirY * speed;
    

            float checkX = newX + dirX * 0.6f;
            float checkY = newY + dirY * 0.6f;
    
            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;
    }
}
        float rightX = -dirY; 
        float rightY = dirX;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            float newX = posX - rightX * speed;
            float newY = posY - rightY * speed; 

            float checkX = newX - rightX * 0.4f;
            float checkY = newY - rightY * 0.4f;

            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;

        }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            float newX = posX + rightX * speed;
            float newY = posY + rightY * speed; 

            float checkX = newX + rightX * 0.4f;
            float checkY = newY + rightY * 0.4f;

            if(gamemap[(int)checkY][(int)checkX] == 0) {
                posX = newX;
                posY = newY;

        }
    }






        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            float newX =  posX - dirX * speed;
            float newY =  posY - dirY * speed;

            float checkX = newX - dirX * 0.6f;
            float checkY = newY - dirY * 0.6f;
    
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
        

        sf::RectangleShape ground(sf::Vector2f(1280,384));
        ground.setPosition(0,384);
        ground.setFillColor(sf::Color(192,192,192));
        window.draw(ground);
       
        sf::RectangleShape potolok(sf::Vector2f(1280,384));
        potolok.setPosition(0,0);
        potolok.setFillColor(sf::Color(28, 170, 214));
        window.draw(potolok);






        
        sf::VertexArray walls(sf::Quads);
        walls.clear();  // Очистить старые данные
        walls.resize(1280 * 4);  // Выделить память заново

        
        for (int x = 0; x < 1280; x++) {
            // направление луча
            float cameraX = 2 * x / 1280.0f - 1;
            float rayDirX = dirX + planeX * cameraX;
            float rayDirY = dirY + planeY * cameraX;
            
            //  находим стену
            float distance;
            int wallType;
            int side = 0; // 0 sever/ug 1 zapad/vostok
            findWallDistance(posX, posY, rayDirX, rayDirY, gamemap, distance, wallType, side);
            
            float hitX = posX + distance * rayDirX;
            float hitY = posY + distance * rayDirY;


            float wallX;
            if (side == 0) wallX = hitY - floor(hitY);
            else wallX = hitX - floor(hitX);

            if (distance < 0.4f) distance = 0.4f;



            //  вычисляем высоту стены
            float lineHeight = 768.0f / (distance + 0.05f);
            float maxHeight = 1536.0f;  

            if (lineHeight > maxHeight) {
                lineHeight = maxHeight;
            }


            float drawStart = 384.0f - lineHeight / 2.0f; 
            float drawEnd = 384.0f + lineHeight / 2.0f;
        

            if (drawStart < 0) drawStart = 0; // ограничение с 0
            if (drawEnd > 768) drawEnd = 768; // ограничение до 768



            // тени
            float brigtness = 1.0f; // яркость
            if (distance > 0.3f) {
                brigtness = 1.0 - (distance - 2.0f) * 0.4f; 
                if (brigtness > 1.0f) brigtness = 1.0f; // ограничиваем значения яркости
                if (brigtness < 0.6f) brigtness = 0.6f;
            }
            sf::Color originalColor = wallColor[wallType]; // яркость равняется типу стен

            sf::Color shadowColor(
                (int)(originalColor.r * brigtness),
                (int)(originalColor.g * brigtness),
                (int)(originalColor.b * brigtness)


            );


            

                int textureX = (int)(wallX * textureWidth);
                
                if (textureX < 0) textureX = 0;
                if (textureX >= textureWidth) textureX = textureWidth - 1;
                
                
            
                


                float texU = wallX * textureWidth;
                if (texU < 1.0f) texU = 1.0f;  
                if (texU > textureWidth - 2.0f) texU = textureWidth - 2.0f;  
                sf::Vertex v0, v1, v2, v3;
            
                v0.position = sf::Vector2f(x, drawStart);
                v1.position = sf::Vector2f(x + 1, drawStart);
                v2.position = sf::Vector2f(x + 1, drawEnd);
                v3.position = sf::Vector2f(x, drawEnd);
    
                float texTop = 0;
                float texBottom = textureHeight;


                if (lineHeight > 768.0f) {
                    float scale = 768.0f / lineHeight;
                    texTop = textureHeight * (1.0f - scale) / 2.0f;
                    texBottom = textureHeight - texTop;
}

                v0.texCoords = sf::Vector2f(texU, texTop);
                v1.texCoords = sf::Vector2f(texU + 1.0f, texTop);
                v2.texCoords = sf::Vector2f(texU + 1.0f, texBottom);
                v3.texCoords = sf::Vector2f(texU, texBottom);
    
                v0.color = shadowColor;
                v1.color = shadowColor;
                v2.color = shadowColor;
                v3.color = shadowColor;
    
                walls.append(v0);
                walls.append(v1);
                walls.append(v2);
                walls.append(v3);



            }   

        window.draw(walls, &wallTexture);

        
        
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