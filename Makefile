CPP_FILES     := $(wildcard src/*.cpp)
O_FILE        := $(subst .cpp,.o,$(CPP_FILES))
COMPILE_FLAGS := -O3 -Wall

all: app clean

app: $(O_FILE)
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	g++ -c $^ -o $@ $(COMPILE_FLAGS)

clean:
	rm -rf *src/*.o

run: all
	./app