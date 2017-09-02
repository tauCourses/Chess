#include <stdlib.h>
#include "SimpleButton.h"
#include "SPCommon.h"

//You need a create function:
Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image) {
    if (windowRender == NULL || location == NULL || image == NULL ) {
        return NULL ;
    }
    //Allocate data
    Widget* res = (Widget*) malloc(sizeof(Widget));
    SimpleButton* data = (SimpleButton*) malloc(sizeof(SimpleButton));
    SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
                                                              loadingSurface);
    if (res == NULL || data == NULL || loadingSurface == NULL || buttonTexture == NULL)
    {
        printf("Simple button image - %s\n", image);
        printf("Simple button res - %d\n", res);
        printf("Simple button data - %d\n", data);
        printf("Simple button loadingSurface - %d\n", loadingSurface);
        printf("Simple button buttonTexture - %d\n", buttonTexture);
        free(res);
        free(data);
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
    data->buttonTexture = buttonTexture;
    data->location = spCopyRect(location);
    data->windowRenderer = windowRender;
    res->destroyWidget = destroySimpleButton;
    res->drawWidget = drawSimpleButton;
    res->handleEvent = handleSimpleButtonEvenet;
    res->data = data;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Widget* src) {
    if (src == NULL ) {
        return;
    }
    SimpleButton* castData = (SimpleButton*) src->data;
    free(castData->location);
    SDL_DestroyTexture(castData->buttonTexture);
    free(castData);
    free(src);
}

void handleSimpleButtonEvenet(Widget* src, SDL_Event* event) {
    printf("Hundle ");
    if (src == NULL || event == NULL ) {
        return; //Better to return an error value
    }
    SimpleButton* castData = (SimpleButton*) src->data;
    if (event->type == SDL_MOUSEBUTTONUP) {
        SDL_Point point;
        point.x = event->button.x;
        point.y = event->button.y;
        if (SDL_PointInRect(&point, castData->location)) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title",
                                     "We did it", NULL );
        }
    } else {
        return;
    }
}

void drawSimpleButton(Widget* src) {
    if (src == NULL ) {
        return;
    }
    SimpleButton* castData = (SimpleButton*) src->data;
    SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
                   castData->location);
}