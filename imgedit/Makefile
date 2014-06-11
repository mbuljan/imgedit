PARAMS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_gpu -w
OUTPUT_FILE_NAME=imgedit

all: Image.o Effect.o Blur.o Resize.o Sobel.o Erosion.o
	g++ Image.o Effect.o Blur.o Resize.o Sobel.o Erosion.o  main.cpp $(PARAMS) -o $(OUTPUT_FILE_NAME)

Image.o: Effect.o
	g++ -c Image.cpp $(PARAMS) 

Effect.o: 
	g++ -c Effect/Effect.cpp $(PARAMS)

Blur.o: Image.o Effect.o
	g++ -c Effect/LiteralEffects/Blur.cpp $(PARAMS)

Resize.o: Image.o Effect.o
	g++ -c Effect/LiteralEffects/Resize.cpp $(PARAMS)

Sobel.o: Image.o Effect.o
	g++ -c Effect/LiteralEffects/Sobel.cpp $(PARAMS)

Erosion.o: Image.o Effect.o
	g++ -c Effect/LiteralEffects/Erosion.cpp $(PARAMS)

clean:
	rm -rf *.o
