# append CXXFLAGS
override CXXFLAGS += -c -g -I../SDL2/include

OBJS=pong_main.o AiPaddle.o PlayerPaddle.o GameManager.o BaseEntity.o Ball.o
LDLIBS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
EXENAME=pong
EXEDIR=..

all: $(EXEDIR)/$(EXENAME);

$(EXEDIR)/pong: pong_main.o AiPaddle.o PlayerPaddle.o GameManager.o BaseEntity.o Ball.o
	g++ -g -o ../pong $(OBJS)  $(LDLIBS)
	@echo $(EXENAME) successully created

pong_main.o: pong_main.cpp
	g++ $(CXXFLAGS) pong_main.cpp

AiPaddle.o: AiPaddle.cpp
	g++ $(CXXFLAGS)  AiPaddle.cpp

PlayerPaddle.o: PlayerPaddle.cpp
	g++ $(CXXFLAGS) PlayerPaddle.cpp

GameManager.o: GameManager.cpp
	g++ $(CXXFLAGS) GameManager.cpp

BaseEntity.o: BaseEntity.cpp
	g++ $(CXXFLAGS) BaseEntity.cpp

Ball.o: Ball.cpp
	g++ $(CXXFLAGS) Ball.cpp

clean:
	rm -f *.o  ../$(EXENAME)
