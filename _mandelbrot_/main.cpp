#include <SDL2/SDL.h>
#include <numeric>
#include <complex>
#include <cmath>

int is_int_set(std::complex<double> c) {
    std::complex<double> z(0,0);
    // loop with the accuracy of the 1000
    for (int i = 0; i < 250; ++i) {
        //compute
        z = std::pow(z,2) + c;
        if (std::norm(z) > 10) {
            return i;
        }
    }
    return 0;
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING); /* initialize */
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(1200, 840, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    for (double x = 0.0; x < 1.0; x+= 0.001) {
        for (double y = 0.0; y < 1.0; y += 0.001) {
            double point_x = std::lerp(-2.0, 2.0, x);
            double point_y = std::lerp(-2.0, 2.0, y);
            int iters = is_int_set(std::complex<double>(point_x, point_y));
            if (iters == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Setcolor to black
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 
                    3 * iters % 255, 
                    3 * iters % 255, 
                    3 * iters % 255, 
                    255); // Setcolor to color
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
}