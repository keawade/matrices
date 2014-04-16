CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Math382.o

LIBS =

TARGET =	Math382.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
