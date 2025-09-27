###############################################################
# Program:
#     Lab 07, Orbit Simulator
# Author:
#     Gary Sibanda
# Summary:
#     Orbit simulator with collision detection and debris
###############################################################

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# macOS OpenGL/GLUT flags
ifeq ($(shell uname),Darwin)
    LDFLAGS = -framework OpenGL -framework GLUT
endif

# Linux OpenGL/GLUT flags
ifeq ($(shell uname),Linux)
    LDFLAGS = -lGL -lGLU -lglut
endif

SOURCES = Lab07.cpp position.cpp velocity.cpp acceleration.cpp angle.cpp \
          physics.cpp satellite.cpp dragon.cpp gps.cpp hubble.cpp \
          sputnik.cpp starlink.cpp DreamChaser.cpp projectile.cpp \
          fragment.cpp part.cpp uiDraw.cpp uiInteract.cpp test.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = orbit

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
