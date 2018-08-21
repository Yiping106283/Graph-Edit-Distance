cc = g++
prom = exe
deps = simulate.h
obj = readin.o simulate.o init_cost.o main.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -Wall

%.o: %.cpp $(deps)
	$(cc) -std=c++11 -c $< -Wall -O2 -o $@ 

clean:
	rm -rf $(obj) $(prom)
