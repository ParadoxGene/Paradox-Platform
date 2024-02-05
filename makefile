all:
	cmake -G"Visual Studio 17" -B ./build -S ./
	cmake --build ./build