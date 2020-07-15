start: phone_number.cpp phone_number.h test.cpp test.h
	g++ -c -Wall -Wextra -pedantic phone_number.cpp
	g++ -c -Wall -Wextra -pedantic test.cpp
	g++ -c -Wall -Wextra -pedantic main.cpp
	g++ main.o phone_number.o test.o -o output
clean:
	rm main.o && rm phone_number.o && rm test.o