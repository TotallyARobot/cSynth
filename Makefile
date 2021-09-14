soundtest: Sound.o
	gcc lists.o Sound.o -o soundtest -I/usr/include/SDL2 -L/usr/lib/ -Wall -Wl,--allow-shlib-undefined -lSDL2 -lm

Sound.o: Sound.c
	gcc -c lists.c
	gcc -c Sound.c

clean: 
	rm *.o