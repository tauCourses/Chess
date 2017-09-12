#include <stdio.h>
#include "GUIManager.h"
#include "console.h"
#include "Infrastructure.h"
#include "SDL.h"

int main(int argc, char** argv)
{
	setvbuf(stdout, NULL, _IOLBF, 0);//shit for eclipse
	runMoveTests();//for debugging

	if(argc == 1)
        return mainConsole();
    if(argc == 2)
    {
        if(strncmp(argv[1], "-c", 2) == 0)
            return mainConsole();
        else if(strncmp(argv[1], "-g", 2) == 0)
            return  mainGUI();
        else
        {
            printf("Unknown argument %s\n", argv[1]);
            return 1;
        }
    }
    printf("invalid number of arguments");
    return 1;

}



