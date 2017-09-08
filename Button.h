#ifndef BUTTON_H_
#define BUTTON_H_
#include <SDL.h>
#include <stdbool.h>

typedef enum { //type of button, enable to refer the the button as choice or as valid or as two valid options
    BUTTON_TYPE_VALIDATE,
    BUTTON_TYPE_CHOICE,
    BUTTON_TYPE_ONE_OPTION,
    BUTTON_TYPE_TWO_OPTIONS,
    BUTTON_TYPE_DEGENERATED
} ButtonType;

typedef enum { //validation options
    BUTTON_VALID, BUTTON_INVALID
} ButtonValidType;

typedef enum { //choice options
    BUTTON_CHOSEN, BUTTON_UNCHOSEN
} ButtonChoiceType;

typedef enum { //choice options
    BUTTON_FIRST_OPTION, BUTTON_SECOND_OPTION
} ButtonTwoOptions;

typedef union  //enable to refer the button as choice or as valid. make the code cleaner and more readable
{
    ButtonValidType valid;
    ButtonChoiceType choosen;
    ButtonTwoOptions option;
}ButtonState;

typedef struct{
    SDL_Texture* mainTexture;
    SDL_Texture* secondaryTexture;
    SDL_Renderer* renderer;
    SDL_Rect location;
    ButtonState state;
    ButtonType type;
} Button;

Button* createButton(SDL_Renderer* renderer, SDL_Rect location, const char* mainPath,
                     const char* secondaryPath, ButtonType type);

void setTextures(Button* button, const char* mainPath, const char* secondaryPath);

void destroyButton(Button* button);

void drawButton(Button* button);

bool clickOnButton(Button* button, int x, int y);

#endif