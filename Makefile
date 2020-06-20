FLAGS=-std=c++11 -O4 -g0 -m64
TARGET=oct_tree

all:
	g++ -c $(FLAGS) -DISOFUNCTION='"${ISOFUNCTION}"' test.cpp -o test.o
	g++ -c $(FLAGS) draw.cpp -o draw.o
	g++ $(FLAGS) test.o draw.o -o $(TARGET) -lGL -lGLU -lglut -lGLEW -lboost_thread -lboost_system 
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
