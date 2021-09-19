soundtest: Sound.o lists.o
	gcc lists.o Sound.o -o soundtest -I/usr/include/SDL2 -L/usr/lib/ -Wall -Wl,--allow-shlib-undefined -lSDL2 -lm

Sound.o: Sound.c
	clear
	gcc -c Sound.c

lists.o: lists.c lists.h
	clear
	gcc -c lists.c

clean: 
	rm *.o