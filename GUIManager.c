#include "GUIManager.h"

GUIManager* managerCreate()
{
    GUIManager* res = calloc(sizeof(GUIManager), sizeof(char));
    if (res == NULL )
        return NULL;

    res->mainWindow = createMainWindow();
    if (res->mainWindow == NULL )
    {
        free(res);
        return NULL ;
    }
    res->activeWin = MAIN_WINDOW_ACTIVE;
    return res;
}

void managerDestroy(GUIManager* src)
{
    if (!src) {
        return;
    }
    if(src->mainWindow != NULL)
        destroyMainWindow(src->mainWindow);
    if(src->loadWindow != NULL)
        destroyLoadWindow(src->loadWindow);
    if(src->modeWindow != NULL)
        destroyModeWindow(src->modeWindow);
    if(src->difficultyWindow != NULL)
        destroyDifficultyWindow(src->difficultyWindow);
    if(src->colorWindow != NULL)
        destroyColorWindow(src->colorWindow);

    free(src);
}

void managerDraw(GUIManager* src)
{
    if (!src) {
        return;
    }
    switch(src->activeWin)
    {
        case MAIN_WINDOW_ACTIVE:
            drawMainWindow(src->mainWindow);
            break;
        case LOAD_WINDOW_ACTIVE:
            drawLoadWindow(src->loadWindow);
            break;
        case MODE_WINDOW_ACTIVE:
            drawModeWindow(src->modeWindow);
            break;
        case DIFFICULTY_WINDOW_ACTIVE:
            drawDifficultyWindow(src->difficultyWindow);
            break;
        case COLOR_WINDOW_ACTIVE:
            drawColorWindow(src->colorWindow);
            break;
        default:
            printf("unknown window to draw %d\n", src->activeWin);
    }
}

MANAGER_EVENT managerHandleEvent(GUIManager* src, SDL_Event* event) {
    if (src == NULL || event == NULL )
        return MANAGER_NONE;

    switch(src->activeWin)
    {
        case MAIN_WINDOW_ACTIVE:
            return handleManagerDueToMainEvent(src, handleEventMainWindow(src->mainWindow, event));
        case LOAD_WINDOW_ACTIVE:
            return handleManagerDueToLoadEvent(src, handleEventLoadWindow(src->loadWindow, event));
        case MODE_WINDOW_ACTIVE:
            return handleManagerDueToModeEvent(src, handleEventModeWindow(src->modeWindow, event));
        case DIFFICULTY_WINDOW_ACTIVE:
            return handleManagerDueToDifficultyEvent(src, handleEventDifficultyWindow(src->difficultyWindow, event));
        case COLOR_WINDOW_ACTIVE:
            return handleManagerDueToColorEvent(src, handleEventColorWindow(src->colorWindow, event));
        default:
            printf("unkonwn event\n");
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToMainEvent(GUIManager* src, MAIN_WINDOW_EVENTS event)
{
    if (src == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case MAIN_EXIT:
            return MANAGER_QUIT;
            break;
        case MAIN_START:
            hideMainWindow(src->mainWindow);
            if(src->modeWindow == NULL)
                src->modeWindow = createModeWindow();
            else
                showModeWindow(src->modeWindow);
            src->activeWin = MODE_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case MAIN_LOAD:
            hideMainWindow(src->mainWindow);
            if(src->loadWindow == NULL)
                src->loadWindow = createLoadWindow();
            else
                showLoadWindow(src->loadWindow);
            src->activeWin = LOAD_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case MAIN_INVALID_ARGUMENT:
            printf("INVALID, BUG1?!\n");
            return MANAGER_NONE;
            break;
        case MAIN_NONE:
            // printf("TODO BOOM\n");
            return MANAGER_NONE;
            break;
        default:
            return MANAGER_NONE;
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToLoadEvent(GUIManager* src, LOAD_WINDOW_EVENTS event)
{
    if (src == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case LOAD_EXIT:
            return MANAGER_QUIT;
            break;
        case LOAD_BACK:
            hideLoadWindow(src->loadWindow);
            if(src->mainWindow == NULL)
                src->mainWindow = createMainWindow();
            else
                showMainWindow(src->mainWindow);
            src->activeWin = MAIN_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;

        case LOAD_CONITNUE:
            printf("NOT SUPPORTED YET\n");
            return MANAGER_NONE;
            break;
        case LOAD_INVALID_ARGUMENT:
            printf("INVALID, BUG2?!\n");
            return MANAGER_NONE;
            break;
        case LOAD_NONE:
            // printf("TODO BOOM\n");
            return MANAGER_NONE;
            break;
        default:
            printf("INVALID, BUG3?!\n");
            return MANAGER_NONE;
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToModeEvent(GUIManager* src, MODE_WINDOW_EVENTS event)
{
    if (src == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case MODE_EXIT:
            return MANAGER_QUIT;
            break;
        case MODE_BACK:
            hideLoadWindow(src->modeWindow);
            if(src->mainWindow == NULL)
                src->mainWindow = createMainWindow();
            else
                showMainWindow(src->mainWindow);
            src->activeWin = MAIN_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case MODE_START:
            printf("NOT SUPPORTED YET\n");
            return MANAGER_NONE;
            break;
        case MODE_NEXT:
            hideLoadWindow(src->modeWindow);
            if(src->difficultyWindow == NULL)
                src->difficultyWindow = createDifficultyWindow();
            else
                showDifficultyWindow(src->difficultyWindow);
            src->activeWin = DIFFICULTY_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case MODE_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n");
            return MANAGER_NONE;
            break;
        case MODE_NONE:
            return MANAGER_NONE;
            break;
        default:
            printf("INVALID, BUG5?!\n");
            return MANAGER_NONE;
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToDifficultyEvent(GUIManager* src, DIFFICULTY_WINDOW_EVENTS event)
{
    if (src == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case DIFFICULTY_EXIT:
            return MANAGER_QUIT;
            break;
        case DIFFICULTY_BACK:
            hideDifficultyWindow(src->difficultyWindow);
            if(src->modeWindow == NULL)
                src->modeWindow = createModeWindow();
            else
                showModeWindow(src->modeWindow);
            src->activeWin = MODE_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case DIFFICULTY_NEXT:
            hideDifficultyWindow(src->difficultyWindow);
            if(src->colorWindow == NULL)
                src->colorWindow = createColorWindow();
            else
                showColorWindow(src->colorWindow);
            src->activeWin = COLOR_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case DIFFICULTY_NONE:
            return MANAGER_NONE;
            break;
        case DIFFICULTY_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n");
            return MANAGER_NONE;
            break;

        default:
            printf("INVALID, BUG5?!\n");
            return MANAGER_NONE;
    }
}

MANAGER_EVENT handleManagerDueToColorEvent(GUIManager* src, COLOR_WINDOW_EVENTS event)
{
    if (src == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case COLOR_EXIT:
            return MANAGER_QUIT;
            break;
        case COLOR_BACK:
            hideColorWindow(src->colorWindow);
            if(src->difficultyWindow == NULL)
                src->difficultyWindow = createDifficultyWindow();
            else
                showDifficultyWindow(src->difficultyWindow);
            src->activeWin = DIFFICULTY_WINDOW_ACTIVE;
            return MANAGER_NONE;
            break;
        case COLOR_START:
            printf("NOT SUPPORTED YET\n");
            return MANAGER_NONE;
            break;
        case COLOR_NONE:
            return MANAGER_NONE;
            break;
        case COLOR_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n");
            return MANAGER_NONE;
            break;

        default:
            printf("INVALID, BUG5?!\n");
            return MANAGER_NONE;
    }
}