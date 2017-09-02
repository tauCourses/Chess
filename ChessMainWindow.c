#include <stdlib.h>
#include "ChessMainWindow.h"
#include "SimpleButton.h"

//Helper function to create buttons in the simple window;
Widget** createMainWindowWidget(SDL_Renderer *renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }
    Widget** widgets = malloc(sizeof(Widget*) * 2);
    if (widgets == NULL ) {
        return NULL ;
    }
    SDL_Rect startR = { .x = 75, .y = 100, .h = 100, .w = 250 };
    SDL_Rect exitR = { .x = 75, .y = 250, .h = 100, .w = 250 };
    widgets[0] = createSimpleButton(renderer, &startR, "./start.bmp");
    widgets[1] = createSimpleButton(renderer, &exitR, "./exit.bmp");
    if (widgets[0] == NULL || widgets[1] == NULL ) {
        printf("hii  %d\t%d", widgets[0], widgets[1]);
        destroyWidget(widgets[0]); //NULL SAFE
        destroyWidget(widgets[1]); //NULL SAFE
        free(widgets);
        return NULL ;
    }
    return widgets;
}
SPWindow* createSimpleWindow() {
    SPWindow* res = malloc(sizeof(SPWindow));
    SPSimpleWindow* data = malloc(sizeof(SPSimpleWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);
    Widget** widgets = createMainWindowWidget(renderer);

    if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL )
    {
        printf("%p\n %p\n %p\n%p\n %p\n", res, data, window, renderer, widgets);
        free(res);
        free(data);
        free(widgets);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    data->widgets = widgets;
    data->numOfWidgets = 2;
    data->window = window;
    data->windowRenderer = renderer;
    data->widgets = widgets;
    res->data = (void*) data;
    res->destroyWindow = destroySimpleWindow;
    res->drawWindow = drawSimpleWindow;
    res->handleEventWindow = handleEvenetSimpleWindow;
    return res;
}
void destroySimpleWindow(SPWindow* src) {
    if (src == NULL ) {
        return;
    }
    SPSimpleWindow* data = (SPSimpleWindow*) src->data;
    int i = 0;
    for (; i < 2; i++) {
        destroyWidget(data->widgets[i]);//
    }
    free(data->widgets);
    SDL_DestroyRenderer(data->windowRenderer);
    SDL_DestroyWindow(data->window);
    free(data);
    free(src);
}
void drawSimpleWindow(SPWindow* src) {
    if (src == NULL ) {
        return;
    }
    SPSimpleWindow* data = (SPSimpleWindow*) src->data;
    //Draw window
    SDL_SetRenderDrawColor(data->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(data->windowRenderer);
    int i = 0;
    for (; i < data->numOfWidgets; i++) {
        (data->widgets[i])->drawWidget(data->widgets[i]);
    }
    SDL_RenderPresent(data->windowRenderer);
}

void handleEvenetSimpleWindow(SPWindow* src, SDL_Event* event){
    if(src == NULL || event==NULL){
        return;
    }
    SPSimpleWindow* data = (SPSimpleWindow*)src->data;
    int i =0;
    for(;i<data->numOfWidgets;i++){
        data->widgets[i]->handleEvent(data->widgets[i],event);
    }
    return;
}