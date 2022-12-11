build:
	g++ -I/home/ikr/code/ac-library -std=gnu++20 -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -pedantic -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_CONCEPT_CHECKS -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_SANITIZE_VECTOR -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -O2 -lgmp -o ./solution ./solution.cpp

optimized:
	g++ -I/home/ikr/code/ac-library -std=gnu++20 -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -pedantic -Wcast-qual -Wcast-align -O2 -lgmp -o ./solution ./solution.cpp

run: build
	./solution
