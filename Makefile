all: Token.o Database.o YUVPixel.o RGBPixel.o GSCPixel.o RGBImage.o GSCImage.o hw4.o
	g++ -std=c++11 -fsanitize=address hw4.o GSCImage.o RGBImage.o YUVPixel.o GSCPixel.o RGBPixel.o Token.o Database.o -o hw4

hw4.o: hw4.cpp GSCImage.cpp GSCImage.hpp RGBImage.cpp RGBImage.hpp GSCPixel.cpp GSCPixel.hpp RGBPixel.cpp RGBPixel.hpp YUVPixel.cpp YUVPixel.hpp Pixel.hpp Token.cpp Token.hpp Database.cpp Database.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address hw4.cpp -c

GSCImage.o: GSCImage.cpp GSCImage.hpp RGBImage.cpp RGBImage.hpp GSCPixel.cpp GSCPixel.hpp RGBPixel.cpp RGBPixel.hpp Pixel.hpp 
	g++ -Wall -g -std=c++11 -fsanitize=address GSCImage.cpp -c
	
RGBImage.o: RGBImage.cpp RGBImage.hpp RGBPixel.cpp RGBPixel.hpp Pixel.hpp YUVPixel.cpp YUVPixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address RGBImage.cpp -c

GSCPixel.o: GSCPixel.cpp GSCPixel.hpp Pixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address GSCPixel.cpp -c

YUVPixel.o: YUVPixel.cpp YUVPixel.hpp Pixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address YUVPixel.cpp -c

RGBPixel.o: RGBPixel.cpp RGBPixel.hpp Pixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address RGBPixel.cpp -c

Database.o: Database.cpp Database.hpp Pixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address Database.cpp -c
	
Token.o: Token.cpp Token.hpp Pixel.hpp
	g++ -Wall -g -std=c++11 -fsanitize=address Token.cpp -c
clean :
	rm *.o -f hw4
	
