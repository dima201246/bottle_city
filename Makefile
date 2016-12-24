CC				= g++
FLAGS 			= -c -Wall -g
OutPut			= bottle_city
_BTLC_VERSION	= \"0.0.1\"

Modules		= bullet.o tank.o configurator.o game_map.o player.o AIplayer.o body.o game.o g_pause.o right_bar.o menu.o watch_dog.o game_over.o bottle_city.o
Main 		= main.o

VPATH = ./src

all: $(Modules) $(Main) 
		$(CC) $^ -o $(OutPut) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
		chmod u=rwx,g=rx,o=rx ./$(OutPut)

start:
		./$(OutPut)

.PHONY: clean 
clean:
	rm -rf *.o

.PHONY: clean-all
clean-all:
	rm -rf *.o
	rm $(OutPut)
