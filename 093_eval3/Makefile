CFLAGS = -Wall -Werror -pedantic -ggdb3 -std=gnu++98
all: cyoa-step1 cyoa-step2 cyoa-step3
cyoa-step1:cyoa-step1.o Page.o NavSection.o InvaildInput.o
	g++ -o cyoa-step1 cyoa-step1.o Page.o NavSection.o InvaildInput.o
cyoa-step2:cyoa-step2.o Story.o Page.o NavSection.o InvaildInput.o
	g++ -o cyoa-step2 cyoa-step2.o Story.o Page.o NavSection.o InvaildInput.o
cyoa-step3:cyoa-step3.o Story.o Page.o NavSection.o InvaildInput.o
	g++ -o cyoa-step3 cyoa-step3.o Story.o Page.o NavSection.o InvaildInput.o
Story.o:Story.cpp Story.hpp Page.hpp
	g++ $(CFLAGS) -c Story.cpp
Page.o:Page.cpp Page.hpp NavSection.hpp 
	g++ $(CFLAGS) -c Page.cpp
NavSection.o:NavSection.cpp NavSection.hpp
	g++ $(CFLAGS) -c NavSection.cpp
InvaildInput.o:InvaildInput.hpp
	g++ $(CFLAGS) -c InvaildInput.cpp
cyoa-step1.o:cyoa-step1.cpp Page.hpp NavSection.hpp InvaildInput.hpp
	g++ $(CFLAGS) -c cyoa-step1.cpp
cyoa-step2.o:cyoa-step2.cpp Story.hpp Page.hpp NavSection.hpp InvaildInput.hpp
	g++ $(CFLAGS) -c cyoa-step2.cpp
cyoa-step3.o:cyoa-step3.cpp Story.hpp Page.hpp NavSection.hpp InvaildInput.hpp
	g++ $(CFLAGS) -c cyoa-step3.cpp
