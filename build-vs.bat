
@ECHO OFF

SET msvc_ver=2019

SET msvc=C:\Program Files (x86)\Microsoft Visual Studio\%msvc_ver%\Community\VC\Auxiliary\Build\vcvars32.bat

SET compile=cl.exe /MT /W3 /TC SRC/*.c SHODAN/SRC/*.c /link Shell32.lib SHODAN/SDL2/VS/LIB/SDL2.lib SHODAN/SDL2/VS/LIB/SDL2main.lib /SUBSYSTEM:CONSOLE /MACHINE:X86 /OUT:main.exe

SET clean=del *.obj

"%msvc%" && cmd /k "%compile% && %clean% && pause && exit"

