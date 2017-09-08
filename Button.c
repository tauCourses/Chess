#include "Button.h"

Button* createButton(SDL_Renderer* renderer, SDL_Rect location, const char* mainPath,
                     const char* secondaryPath, ButtonType type)
{
    if (renderer == NULL)
        return NULL;

    Button* button = (Button*) malloc(sizeof(Button));
    if(button == NULL)
        return NULL;

    button->renderer = renderer;
    button->location = location; //set the location of the button
    button->type = type; //set as valid/invalid button by default
    if(button->type == BUTTON_TYPE_VALIDATE)
        button->state.valid = BUTTON_VALID; //set as valid by default
    else if(button->type == BUTTON_TYPE_CHOICE)
        button->state.choosen = BUTTON_UNCHOSEN; //set as UNCHOSEN by default
    else if(button->type == BUTTON_TYPE_TWO_OPTIONS)
        button->state.option = BUTTON_FIRST_OPTION;

    setTextures(button, mainPath, secondaryPath);

    if(button->mainTexture == NULL ||
            (button->type != BUTTON_TYPE_DEGENERATED && button->type != BUTTON_TYPE_ONE_OPTION &&
                    button->secondaryTexture == NULL))
    {
        destroyButton(button);
        return NULL;
    }

    return button;
}

void setTextures(Button* button, const char* mainPath, const char* secondaryPath)
{
    SDL_Surface* loadingSurface = SDL_LoadBMP(mainPath);
    if (loadingSurface == NULL )
        return;

    button->mainTexture = SDL_CreateTextureFromSurface(button->renderer, loadingSurface);
    if(button->mainTexture == NULL)
    {
        SDL_FreeSurface(loadingSurface);
        return;
    }

    if(button->type == BUTTON_TYPE_DEGENERATED || button->type == BUTTON_TYPE_ONE_OPTION) //no need to load second picture
    {
        SDL_FreeSurface(loadingSurface);
        return;
    }

    loadingSurface = SDL_LoadBMP(secondaryPath);
    if (loadingSurface == NULL )
    {
        SDL_FreeSurface(loadingSurface);
        return;
    }

    button->secondaryTexture = SDL_CreateTextureFromSurface(button->renderer, loadingSurface);
    if(button->secondaryTexture == NULL)
    {
        SDL_FreeSurface(loadingSurface);
        return;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after textures created
}

void destroyButton(Button* button)
{
    if (button == NULL )
        return;

    if(button->mainTexture != NULL)
        SDL_DestroyTexture(button->mainTexture);

    if(button->secondaryTexture != NULL)
        SDL_DestroyTexture(button->secondaryTexture);
    //the renderer is not freed because it's used by others probably.
    free(button);
}

void drawButton(Button* button)
{
    if (button == NULL )
        return;

    SDL_Texture* texture;
    switch (button->type) {
        case BUTTON_TYPE_VALIDATE:
            texture = button->state.valid == BUTTON_VALID ? button->mainTexture : button->secondaryTexture;
            break;
        case BUTTON_TYPE_CHOICE:
            texture = button->state.choosen == BUTTON_UNCHOSEN ? button->mainTexture : button->secondaryTexture;
            break;
        case BUTTON_TYPE_TWO_OPTIONS:
            texture = button->state.option == BUTTON_FIRST_OPTION ? button->mainTexture : button->secondaryTexture;
            break;
        case BUTTON_TYPE_DEGENERATED:
            texture = button->mainTexture;
            break;
        case BUTTON_TYPE_ONE_OPTION:
            texture = button->mainTexture;
            break;
        default:
            printf("BUG!");
            texture = button->mainTexture;

    }
    SDL_RenderCopy(button->renderer, texture, NULL, &button->location);
}

bool clickOnButton(Button* button, int x, int y)
{
    bool inButton =  (x >= button->location.x) &&
           (y >= button->location.y) &&
           (x < button->location.x + button->location.w) &&
           (y < button->location.y + button->location.h);

    if(!inButton)
        return false;
    switch (button->type)
    {
        case BUTTON_TYPE_VALIDATE:
            return button->state.valid == BUTTON_VALID;
        case BUTTON_TYPE_CHOICE:
            return button->state.choosen == BUTTON_UNCHOSEN;
        case BUTTON_TYPE_TWO_OPTIONS:
            return true; // both options are valid
        case BUTTON_TYPE_ONE_OPTION:
            return true; // just one option is presented, and it is always valid
        case BUTTON_TYPE_DEGENERATED:
            return false; // non option is valid;
        default:
            printf("BUG!");
            return false;

    }

}

