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
	./MP line by:200 ax:113 bx:12
	#chybejici hodnota parametru
	./MP line ay: by:200 ax:113 bx:12 
	#"primka"
	./MP line ay:100 by:200 ax:113 bx:12 
	#"polygon"
	./MP polygon line:ax:50,ay:20,bx:30,by:50 line:ax:100,ay:200,bx:300,by:400 line:ax:200,bx:300,by:678,ay:34

