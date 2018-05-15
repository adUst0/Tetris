INC = -I./SFML-2.4.2/include
LIBS = -L./SFML-2.4.2/lib -lsfml-graphics -lsfml-window -lsfml-system
CC = g++
CFLAGS = -Wall -std=c++11 $(INC)

SDIR = src
ODIR = obj/$(SDIR)
BIN = Tetris.exe

_OBJ = Game.o Figure.o Board.o GUI.o TetrisAI.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: Tetris

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

Tetris: $(OBJ)
	@echo "** Building the game"
	$(CC) -o $(BIN) $^ $(CFLAGS) $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f $(BIN) $(ODIR)/*.o

rebuild: clean all
	
run: all
	./$(BIN)