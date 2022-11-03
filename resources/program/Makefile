NAME=MP

CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra -g `sdl2-config --cflags --libs`  

all: $(NAME) clean

dep:
	$(CC) -MM *.c >dep.list

-include dep.list

$(NAME):
	sh makeExe.sh $(CC) "$(CFLAGS)" $@

clean:
	rm **/*.o
	rm *.o

