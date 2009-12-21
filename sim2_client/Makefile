CC   = g++
OBJ  = main.o ag.o sim.o point2d.o
LINKOBJ  = $(OBJ)
LIBS = -O3
BIN  = sim_client
CFLAGS = $(INCS)
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before sim_client all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

ag.o: ag.cpp
	$(CC) -c ag.cpp -o ag.o $(CFLAGS)

sim.o: sim.cpp
	$(CC) -c sim.cpp -o sim.o $(CFLAGS)

point2d.o: point2d.cpp
	$(CC) -c point2d.cpp -o point2d.o $(CFLAGS)
