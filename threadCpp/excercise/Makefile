CC		= g++
CFLAGS		= -c -Wall
LDFLAGS		= -pthread
SOURCES		= Test.cpp Thread.cpp
INCLUDES	= -I../threads
OBJECTS		= $(SOURCES:.cpp=.o)
TARGET		= mutex

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
