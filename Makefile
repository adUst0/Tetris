ifeq ($(OS),Windows_NT)
##################################
# IF OPERATING SYSTEM IS WINDOWS #
##################################
INC = -I./SFML-2.4.2/include
LIBS = -L./SFML-2.4.2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
CC = g++
CFLAGS = -Wall -std=c++11 $(INC) -mwindows

SDIR = src
ODIR = obj/$(SDIR)

_OBJ = Game.o Figure.o Board.o GUI.o TetrisAI.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: Tetris

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

Tetris: $(OBJ)
	@echo "** Building the game"
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f Tetris.exe $(ODIR)/*.o

rebuild: clean all
	
run: all
	./Tetris.exe
	
else
##################################
# IF OPERATING SYSTEM IS LINUX   #
##################################
INC = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGL
CC = g++
CFLAGS = -Wall -std=c++11 $(INC)

ODIR = obj
ODIR = obj/$(SDIR)

_OBJ = Game.o Figure.o Board.o GUI.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: Tetris

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

Tetris: $(OBJ)
	@echo "** Building the game"
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f Tetris $(ODIR)/*.o

rebuild: clean all
	
run: all
	./Tetris
endif