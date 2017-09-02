#ifndef SIMPLEBUTTON_H_
#define SIMPLEBUTTON_H_

#include "Widget.h" //A button is a widget also

typedef struct simplebutton_t SimpleButton;
struct simplebutton_t{
    SDL_Texture* buttonTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
};

//You need a create function:
Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location,
                           const char* image);

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Widget*);

void handleSimpleButtonEvenet(Widget* src, SDL_Event* event);

void drawSimpleButton(Widget* src);

#endif