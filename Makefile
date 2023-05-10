CXX=g++
LDFLAGS=-lmpg123 -lao -lGL -lGLU -lglut -lSOIL -lpthread
SOURCES=$(wildcard src/*.cpp)
EXECUTABLE=project

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
