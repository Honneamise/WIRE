gcc SRC/*.c SHODAN/SRC/*.c -L SHODAN/SDL2/MINGW/LIB -lmingw32 -lSDL2main -lSDL2 -Wl,-subsystem,console -o bin.exe
pause