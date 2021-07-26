build:
	g++ -I/home/ikr/code/ac-library -std=gnu++17 -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -pedantic -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -o ./solution ./solution.cpp

run: build
	./solution
