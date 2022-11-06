CXXFLAGS=-std=c++11

program.exe: main.cpp list.o string.o
	clang++ $(CXXFLAGS) main.cpp -o program.exe

%.o: %.c
	clang++ $(CXXFLAGS) -c %< -o %@

clean:
	rm -f *.o *.exe
