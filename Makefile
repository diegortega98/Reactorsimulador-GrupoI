INCLUDE_PATHS = -I"D:\Users\Usuario\Documents\MATEO\SDL2-2.0.16\i686-w64-mingw32\include\SDL2" \
	-I"D:\Users\Usuario\Documents\MATEO\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2" 

OBJS = main.o object.o uranium.o neutron.o general.o simulation.o
SRC  = main.cpp object.cpp uranium.cpp neutron.cpp general.cpp simulation.cpp
CC = g++
RM = del $(OBJS) 
LIB_PATHS = -L"D:\Users\Usuario\Documents\MATEO\SDL2-2.0.16\i686-w64-mingw32\lib" \
	-L"D:\Users\Usuario\Documents\MATEO\SDL2_image-2.0.5\i686-w64-mingw32\lib" 
	
LINK_OPTIONS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

	
main :
	$(CC) $(INCLUDE_PATHS) $(LIB_PATHS) $(SRC) -o FissionSimulation.exe -O2 -mwindows $(LINK_OPTIONS)
	
console :
	$(CC) $(INCLUDE_PATHS) $(LIB_PATHS) $(SRC) -o FissionSimulation.exe -O2 $(LINK_OPTIONS)
	
debug :
	$(CC) $(INCLUDE_PATHS) $(LIB_PATHS) $(SRC) -o FissionSimulationDEBUG.exe --debug $(LINK_OPTIONS)
	

clean : 
	$(RM)