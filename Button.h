#ifndef BUTTON_H_
#define BUTTON_H_
#include <SDL.h>
#include <stdbool.h>

#define RESTART_ACTIVE_BUTTON "images/buttons/RestartActive.bmp"
#define RESTART_NOT_ACTIVE_BUTTON "images/buttons/RetartNotActive.bmp"

#define START_ACTIVE_BUTTON "images/buttons/StartActive.bmp"
#define START_NOT_ACTIVE_BUTTON "images/buttons/StartNotActive.bmp"

#define UNDO_ACTIVE_BUTTON "images/buttons/UndoActive.bmp"
#define UNDO_NOT_ACTIVE_BUTTON "images/buttons/UndoNotActive.bmp"

#define ONE_PLAYER_ACTIVE_BUTTON "images/buttons/OnePlayerActive.bmp"
#define ONE_PLAYER_NOT_ACTIVE_BUTTON "images/buttons/OnePlayerNotActive.bmp"

#define TWO_PLAYERS_ACTIVE_BUTTON "images/buttons/TwoPlayersActive.bmp"
#define TWO_PLAYERS_NOT_ACTIVE_BUTTON "images/buttons/TwoPlayersNotActive.bmp"

#define SAVE_ACTIVE_BUTTON "images/buttons/SaveActive.bmp"
#define SAVE_NOT_ACTIVE_BUTTON "images/buttons/SaveNotActive.bmp"

#define NOOB_ACTIVE_BUTTON "images/buttons/NoobActive.bmp"
#define NOOB_NOT_ACTIVE_BUTTON "images/buttons/NoobNotActive.bmp"

#define NEXT_ACTIVE_BUTTON "images/buttons/NextActive.bmp"
#define NEXT_NOT_ACTIVE_BUTTON "images/buttons/NextNotActive.bmp"

#define NEW_GAME_ACTIVE_BUTTON "images/buttons/NewGameActive.bmp"
#define NEW_GAME_NOT_ACTIVE_BUTTON "images/buttons/NewGameNotActive.bmp"

#define MODERATE_ACTIVE_BUTTON "images/buttons/ModerateActive.bmp"
#define MODERATE_NOT_ACTIVE_BUTTON "images/buttons/ModerateNotActive.bmp"

#define MAIN_MANU_ACTIVE_BUTTON "images/buttons/MainMenuActive.bmp"
#define MAIN_MANU_NOT_ACTIVE_BUTTON "images/buttons/MainMenuNotActive.bmp"

#define LOAD_ACTIVE_BUTTON "images/buttons/LoadActive.bmp"
#define LOAD_NOT_ACTIVE_BUTTON "images/buttons/LoadNotActive.bmp"

#define HARD_ACTIVE_BUTTON "images/buttons/HardActive.bmp"
#define HARD_NOT_ACTIVE_BUTTON "images/buttons/HardNotActive.bmp"

#define GAME_SLOT_1_ACTIVE_BUTTON "images/buttons/GameSlot1Active.bmp"
#define GAME_SLOT_2_ACTIVE_BUTTON "images/buttons/GameSlot2Active.bmp"
#define GAME_SLOT_3_ACTIVE_BUTTON "images/buttons/GameSlot3Active.bmp"
#define GAME_SLOT_4_ACTIVE_BUTTON "images/buttons/GameSlot4Active.bmp"
#define GAME_SLOT_5_ACTIVE_BUTTON "images/buttons/GameSlot5Active.bmp"

#define GAME_SLOT_1_NOT_ACTIVE_BUTTON "images/buttons/GameSlot1NotActive.bmp"
#define GAME_SLOT_2_NOT_ACTIVE_BUTTON "images/buttons/GameSlot2NotActive.bmp"
#define GAME_SLOT_3_NOT_ACTIVE_BUTTON "images/buttons/GameSlot3NotActive.bmp"
#define GAME_SLOT_4_NOT_ACTIVE_BUTTON "images/buttons/GameSlot4NotActive.bmp"
#define GAME_SLOT_5_NOT_ACTIVE_BUTTON "images/buttons/GameSlot5NotActive.bmp"

#define EXPERT_ACTIVE_BUTTON "images/buttons/ExpertActive.bmp"
#define EXPERT_NOT_ACTIVE_BUTTON "images/buttons/ExpertNotActive.bmp"

#define EXIT_ACTIVE_BUTTON "images/buttons/ExitActive.bmp"
#define EXIT_NOT_ACTIVE_BUTTON "images/buttons/ExitNotActive.bmp"

#define EASY_ACTIVE_BUTTON "images/buttons/EasyActive.bmp"
#define EASY_NOT_ACTIVE_BUTTON "images/buttons/EasyNotActive.bmp"

#define BACK_ACTIVE_BUTTON "images/buttons/BackActive.bmp"
#define BACK_NOT_ACTIVE_BUTTON "images/buttons/BackNotActive.bmp"

#define SELECT_COLOR_BLACK_BUTTON "images/buttons/SelectColorBlack.bmp"
#define SELECT_COLOR_WHITE_BUTTON "images/buttons/SelectColorWhite.bmp"

#define BUTTON_DEFAULT_WIDTH 200
#define BUTTON_DEFAULT_HEIGHT 50

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