#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#undef main

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string TITLE = "SDL Tuorial";

//enum KeyPressSurfaces
//{
//    KEY_PRESS_SURFACE_DEFAULT,
//    KEY_PRESS_SURFACE_UP,
//    KEY_PRESS_SURFACE_DOWN,
//    KEY_PRESS_SURFACE_LEFT,
//    KEY_PRESS_SURFACE_RIGHT,
//    KEY_PRESS_SURFACE_TOTAL
//};

//Starts up SDL and create window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer;

//Loads individual image as textual
SDL_Texture* loadTexture(string path);

//Current displayed texture
SDL_Texture* gTexture = NULL;

int main()
{
    if (!init()){
        cout << "Failed to initialize!!!" << endl;
    }
    else {
        if (!loadMedia()){
            cout << "Failed to load media!" << endl;
        }
        else {
            bool quit = false;

            SDL_Event e;

            while(!quit){
                while (SDL_PollEvent (&e) != 0){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render red filled quad
                SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect);

                SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_HEIGHT; i += 8){
                    SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, i, SCREEN_WIDTH / 2, i + 4);
                }

                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL){
                cout << "Renderer could not be created! SDL error: " << SDL_GetError() << endl;
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 255);

                int imgFlags = IMG_INIT_PNG;
                if (!( IMG_Init( imgFlags ) & imgFlags)) {
                    cout << "SDL_image could not initialize! SDL error: " << SDL_GetError() << endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

//    gTexture = loadTexture("texture.png");
//    if (gTexture == NULL){
//        cout << "Failed to load texture image! SDL error: " << SDL_GetError() << endl;
//        success = false;
//    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyWindow (gWindow);
    gWindow = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    //Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}

//SDL_Surface* loadSurface(string path)
//{
//    //The final optimized image
//    SDL_Surface* optimizedSurface = NULL;
//
//    //Load image at specific path
//    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
//    if (loadSurface == NULL){
//        cout << "Unable to load image!!! SDL Error: " << SDL_GetError() << endl;
//    }
//    else {
//        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
//        if (optimizedSurface == NULL){
//            cout << "Unable to optimized image! SDL error: " << SDL_GetError() << endl;
//        }
//        SDL_FreeSurface(loadedSurface);
//    }
//    return optimizedSurface;
//}

SDL_Texture* loadTexture(string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specific path
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL){
        printf("Unable to load image %s! SDL_image error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if (newTexture == NULL){
            printf("Unable to create texture from %s! SDL error %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}
