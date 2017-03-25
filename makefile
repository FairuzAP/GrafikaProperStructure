all:
	g++ -o main Border.cpp Color.cpp Point.cpp Screen.cpp shape.cpp ColorMatrix.cpp Layer.cpp main.cpp

clean:
	rm main
