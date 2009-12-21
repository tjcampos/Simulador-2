CC   = g++
OBJ  = main.o object.o drawing.o kbddecoder.o simctrl.o eventmanager.o point2d.o trigtable.o robot.o obstacle.o rsensor.o checkintersect.o sockserv.o
LINKOBJ  = $(OBJ)
LIBS =  -lSDL -lSDL_gfx -g 
BIN  = simula
CFLAGS = $(INCS) -g 
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before simula all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o "simula" $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

object.o: object.cpp
	$(CC) -c object.cpp -o object.o $(CFLAGS)

drawing.o: drawing.cpp
	$(CC) -c drawing.cpp -o drawing.o $(CFLAGS)

kbddecoder.o: kbddecoder.cpp
	$(CC) -c kbddecoder.cpp -o kbddecoder.o $(CFLAGS)

simctrl.o: simctrl.cpp
	$(CC) -c simctrl.cpp -o simctrl.o $(CFLAGS)

eventmanager.o: eventmanager.cpp
	$(CC) -c eventmanager.cpp -o eventmanager.o $(CFLAGS)

point2d.o: point2d.cpp
	$(CC) -c point2d.cpp -o point2d.o $(CFLAGS)

trigtable.o: trigtable.cpp
	$(CC) -c trigtable.cpp -o trigtable.o $(CFLAGS)

robot.o: robot.cpp
	$(CC) -c robot.cpp -o robot.o $(CFLAGS)

obstacle.o: obstacle.cpp
	$(CC) -c obstacle.cpp -o obstacle.o $(CFLAGS)

rsensor.o: rsensor.cpp
	$(CC) -c rsensor.cpp -o rsensor.o $(CFLAGS)

checkintersect.o: checkintersect.cpp
	$(CC) -c checkintersect.cpp -o checkintersect.o $(CFLAGS)

slevel.o: slevel.cpp
	$(CC) -c slevel.cpp -o slevel.o $(CFLAGS)
	
sockserv.o: sockserv.cpp
	$(CC) -c sockserv.cpp -o sockserv.o $(CFLAGS)
