CC = gcc
OBJS =  Location.o \
		GameBoard.o GameState.o  \
		History.o \
		GameManager.o \
		Storage.o AI.o \
		Parser.o ConsoleSettingsState.o ConsoleGameState.o \
		ConsoleManager.o \
		Button.o BoardLayout.o GameLayout.o \
		MainWindow.o LoadGameWindow.o ModeWindow.o DifficultyWindow.o ColorWindow.o GameWindow.o \
		GUIManager.o \
		main.o

EXEC = chessprog



CC_COMP_FLAG = -std=c99 -Wall -Wextra \
  -pedantic-errors

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT 
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

Location.o: Location.h Location.c   
	$(CC) $(COMP_FLAG)  $(SDL_COMP_FLAG) -c $*.c
BoardLayout.o: BoardLayout.h BoardLayout.c  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Button.o: Button.h Button.c  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameState.o: GameState.c GameState.h  GameBoard.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
History.o: History.c History.h  GameState.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameManager.o: GameManager.c GameManager.h  History.h GameState.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Storage.o: Storage.c Storage.h  GameManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
AI.o: AI.c AI.h GameManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameLayout.o: GameLayout.c GameLayout.h BoardLayout.h  GameManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameWindow.o: GameWindow.c GameWindow.h Button.h  GameLayout.h Storage.h AI.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ColorWindow.o: ColorWindow.c ColorWindow.h Button.h GameManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
DifficultyWindow.o: DifficultyWindow.c DifficultyWindow.h Button.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ModeWindow.o: ModeWindow.c ModeWindow.h Button.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
LoadGameWindow.o: LoadGameWindow.c LoadGameWindow.h Button.h Storage.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MainWindow.o: MainWindow.c MainWindow.h Button.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h Location.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ConsoleGameState.o: ConsoleGameState.c ConsoleGameState.h Parser.h Storage.h  AI.h GameManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ConsoleSettingsState.o: ConsoleSettingsState.c ConsoleSettingsState.h GameManager.h Storage.h Parser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c 
GUIManager.o: GUIManager.c GUIManager.h MainWindow.h LoadGameWindow.h ModeWindow.h DifficultyWindow.h ColorWindow.h GameWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ConsoleManager.o: ConsoleManager.c ConsoleManager.h ConsoleGameState.h ConsoleSettingsState.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c ConsoleManager.h GUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)