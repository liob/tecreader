CP = cp
G++ = g++
G++-win = i686-w64-mingw32-c++

all: linux windows

linux:
	$(G++) tecreader.cpp -o tecreader -lboost_system -lboost_program_options

windows:
	$(G++-win) tecreader.cpp -o tecreader.exe -lboost_system -lboost_program_options -lwsock32 --static

clean:
	$(RM) tecreader tecreader.exe

