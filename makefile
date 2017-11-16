OBJ = main.o enigma.o config.o plugboard_reflector.o rotor.o
EXE = enigma
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

main.o: enigma.h

plugboard_reflector.o: plugboard_reflector.h

rotor.o: rotor.h

config.o: config.h

enigma.o: enigma.h

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
