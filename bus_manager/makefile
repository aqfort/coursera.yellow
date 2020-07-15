start: query.h query.cpp responses.h responses.cpp bus_manager.h bus_manager.cpp
	g++ -c -Wall -Wextra -pedantic query.cpp
	g++ -c -Wall -Wextra -pedantic responses.cpp
	g++ -c -Wall -Wextra -pedantic bus_manager.cpp
	g++ -c -Wall -Wextra -pedantic main.cpp
	g++ main.o query.o responses.o bus_manager.o -o output
clean:
	rm main.o && rm query.o && rm responses.o && rm bus_manager.o