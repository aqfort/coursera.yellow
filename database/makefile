start: condition_parser.h condition_parser.cpp database.h database.cpp date.h date.cpp node.h node.cpp test.h test.cpp token.h token.cpp
	g++ -c -Wall -Wextra -pedantic condition_parser.cpp
	g++ -c -Wall -Wextra -pedantic database.cpp
	g++ -c -Wall -Wextra -pedantic date.cpp
	g++ -c -Wall -Wextra -pedantic node.cpp
	g++ -c -Wall -Wextra -pedantic token.cpp
	g++ -c -Wall -Wextra -pedantic main.cpp
	g++ main.o condition_parser.o database.o date.o node.o token.o -o output
clean:
	rm main.o && rm condition_parser.o && rm database.o && rm date.o && rm node.o && rm token.o