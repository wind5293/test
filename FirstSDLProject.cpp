#include <iostream>
#include "C:/SDL2-2.30.0/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "C:/SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#include <string>

#undef main

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
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

//Loads individual image
SDL_Surface* loadSurface(string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current display image
SDL_Surface* gStretchedSurface = NULL;

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
        //Load media
        if (!loadMedia()){
            cout << "Failed to load media!!!" << endl;
        }
        else {
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit){
                while (SDL_PollEvent(&e) != 0){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                }
                //Apply the current image
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled (gStretchedSurface, NULL, gScreenSurface, &stretchRect);

                //Update the surface
                SDL_UpdateWindowSurface (gWindow);
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
            //Create renderer for window
            SDL_GetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            if (gRenderer == NULL){
                cout << "Renderer color could not be created! SDL error: " << SDL_GetError() << endl;
                success = false;
            }
            else {
                //Initialize render color
                SDL_SetRenderDrawColor()

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)){
                    cout << "SDL_image could not initialize! SDL error: " << IMG_GetError() << "\n";
                    success = false;
                }
            }
            //gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    gStretchedSurface = loadSurface("stretch.bmp");
    if (gStretchedSurface == NULL){
        cout << "Failed to load stretch image! SDL error: " << SDL_GetError() << endl;
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    //Destroy window
    SDL_DestroyWindow (gWindow);
    gWindow = NULL;

    //Quit SDL subsystem
    SDL_Quit();
}

SDL_Surface* loadSurface(string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specific path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadSurface == NULL){
        cout << "Unable to load image!!! SDL Error: " << SDL_GetError() << endl;
    }
    else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL){
            cout << "Unable to optimized image! SDL error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

SDL_Texture* loadTexture(string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specific path

}
