IFLAGS = -I./raylib-5.0_linux_amd64/include/
LFLAGS = -L./raylib-5.0_linux_amd64/lib/ -l:libraylib.so -Wl,-rpath=./raylib-5.0_linux_amd64/lib/

main: main.c
	cc main.c -o main $(IFLAGS) $(LFLAGS)
