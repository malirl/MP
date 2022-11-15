NAME=MP

CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra -I -g `sdl2-config --cflags --libs` -lm 

all: clean $(NAME) run


dep:
	$(CC) -MM *.c >dep.list

-include dep.list

$(NAME):
	sh makeExe.sh $(CC) "$(CFLAGS)" $@

run:
	./$(NAME)

clean:
	rm $(NAME)
	clear	

get-dependencies:
	git clone https://github.com/kokke/tiny-regex-c.git
	cd tiny-regex-c
	make all

test:
	#nekompletni zadani
	./MP line ay by:200 ax:113 bx:12
	#"spravne zadani"
	./MP line ay:100 by:200 ax:113 bx:12 

	
