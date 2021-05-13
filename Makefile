all:
	rm -rf saida
	g++ main.cpp maze.cpp cell.cpp libpgm.cpp matriz.h -o saida;clear;./saida
