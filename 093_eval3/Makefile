CFLAGS = -Wall -Werror -pedantic -ggdb3 -std=gnu++98
cyoa-step1:cyoa-step1.o Page.o NavSection.o InvaildInput.o
	g++ -o cyoa-step1 cyoa-step1.o Page.o NavSection.o InvaildInput.o
Page.o:Page.cpp Page.hpp NavSection.hpp 
	g++ $(CFLAGS) -c Page.cpp
NavSection.o:NavSection.cpp NavSection.hpp
	g++ $(CFLAGS) -c NavSection.cpp
InvaildInput.o:InvaildInput.hpp
	g++ $(CFLAGS) -c InvaildInput.cpp
cyoa-step1.o:cyoa-step1.cpp Page.hpp NavSection.hpp InvaildInput.hpp
	g++ $(CFLAGS) -c cyoa-step1.cpp
