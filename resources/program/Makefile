NAME=MP

CC=gcc
CFLAGS=-pg -std=c99 -pedantic -Wall -Wextra -I -g `sdl2-config --cflags --libs` -lm 

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
	./MP polygon point:x:100,y:200 point:x:700,y:200 point:x:200,y:300 point:x:340,y:650 point:x:200,y:800 point:x:190,y:800
	#strany se protínají, polygon se nevytvoří
	./MP polygon point:x:100,y:200 point:x:700,y:200 point:x:200,y:300 point:x:340,y:650 point:x:200,y:800 point:x:230,y:830

