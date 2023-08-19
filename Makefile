all :  solar test
solar : main.cpp
	@mkdir -p bin
	g++ main.cpp -o bin/solar -lglut -lGL -lGLU
test : test.cpp
	@mkdir -p bin
	g++ test.cpp -o bin/test -lglut -lGL -lGLU
clean:
	rm -rf bin
