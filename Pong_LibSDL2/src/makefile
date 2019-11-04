# append CXXFLAGS
override CXXFLAGS += -c -g -I../SDL2/include

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.c=.o)

LDLIBS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
EXENAME=pong
EXEDIR=..
EXEPATH=$(EXEDIR)/$(EXENAME)

all: $(EXEPATH);

# $@ = target
# $^ = prerequisite
$(EXEDIR)/pong: pong_main.o AiPaddle.o PlayerPaddle.o GameManager.o BaseEntity.o Ball.o
	$(CXX) -g -o $@ $(OBJS)  $(LDLIBS)
	@echo $(EXENAME) successully created

# generic rule to build .o from .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^

.PHONY:	clean
clean:
	rm -f *.o  $(EXEPATH)
