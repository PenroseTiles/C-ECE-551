
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step4: cyoa-step4.cpp utils.h
	g++ -Wall -Werror -pedantic -std=gnu++98 cyoa-step4.cpp -o cyoa-step4
cyoa-step3: cyoa-step3.cpp utils.h
	g++  -Wall -Werror -pedantic -std=gnu++98  cyoa-step3.cpp -o cyoa-step3
cyoa-step2: cyoa-step2.cpp utils.h
	g++  -Wall -Werror -pedantic  -std=gnu++98  cyoa-step2.cpp -o cyoa-step2
cyoa-step1: cyoa-step1.cpp utils.h
	g++  -Wall -Werror -pedantic  -std=gnu++98 cyoa-step1.cpp -o cyoa-step1
clean:
	rm -f cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
