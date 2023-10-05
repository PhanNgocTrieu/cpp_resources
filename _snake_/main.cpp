#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <deque>

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;
    enum Direction {
        DOWN,
        LEFT,
        RIGHT,
        UP
    };
    
    bool running = true;
    int dir = 0;

    // Snake head position
    SDL_Rect head {
        500, 500, 10, 10
    };

    // Snake body container
    std::deque<SDL_Rect> recQueue;
    int size = 1;

    // Apple container
    std::vector<SDL_Rect> apples;

    // Create apples on the map
    for (int i = 0; i < 100; ++i) {
        SDL_Rect rec_temp{rand() % 100 * 10, rand() % 100 * 10, 10, 10};
        apples.emplace_back(rec_temp);
    }

    while (running) {
        // check Input
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_DOWN:     { dir = DOWN;   break; }
                case SDLK_LEFT:     { dir = LEFT;   break; }
                case SDLK_RIGHT:    { dir = RIGHT;  break; }
                case SDLK_UP:       { dir = UP;     break; }
                default: { break; }
                }
            }
        }
        
        // Moving
        switch (dir)
        {
            case DOWN:  { head.y += 10; break;}
            case UP:    { head.y -= 10; break; }
            case LEFT:  { head.x -= 10; break; }
            case RIGHT: { head.x += 10; break; }
            default:    { break; }
        }

        // Collision detection with apple
        std::for_each(apples.begin(), apples.end(), [&](auto& apple) {
            if (head.x == apple.x && head.y == apple.y) {
                size += 10;
                apple.x -= 10;
                apple.y -= 10;
            }
        });

        // Collision detection with snake body
        std::for_each(recQueue.begin(), recQueue.end(), [&](auto& snake_segment) {
            if (head.x == snake_segment.x && head.y == snake_segment.y) {
                // Reset the snake when snake hits his own body
                size = 1;
            }
        });

        // Add newest head to the snake
        recQueue.push_front(head);

        while (recQueue.size() > size) {
            recQueue.pop_back();
        }

        // Clear Window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw Body
        //SDL_RenderFillRect(renderer, &head);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        std::for_each(recQueue.begin(), recQueue.end(), [&](auto& snake_segment){
            SDL_RenderFillRect(renderer, &snake_segment);
        });

        // Draw Apples
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // set "Red" Color
        std::for_each(apples.begin(), apples.end(), [&](auto& apple) {
            SDL_RenderFillRect(renderer, &apple);
        });

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
    
    return 0;
}