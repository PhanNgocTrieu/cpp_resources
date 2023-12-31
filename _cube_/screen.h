#ifndef __SCREN_H__
#define __SCREN_H__

#include <SDL2/SDL.h>
#include <vector>

class Screen {
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    // std::vector<SDL_FPoint> points;
    std::vector<SDL_FPoint> points;

    public:
        Screen() {
            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(
                640 * 2, 320 * 2, 0, &window, &renderer);
            SDL_RenderSetScale(renderer, 2, 2);
        }

        // Emplacing the pixels on the screen
        void pixel(float x, float y) {
            SDL_FPoint point;
            point.x = x;
            point.y = y;
            points.emplace_back(point);
        }

        void show() {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            for (auto& point : points) {
                SDL_RenderDrawPointF(renderer, point.x, point.y);
            }

            SDL_RenderPresent(renderer);
        }

        void clear() {
            points.clear();
        }


        void input() {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    SDL_Quit();
                    exit(0);
                }
            }
        }
};

#endif