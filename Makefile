DAY1= day1.cpp
DAY2= day2.cpp
DAY3= day3.cpp
DAY4= day4.cpp md5.cpp
DAY5= day5.cpp
DAY6= day6.cpp
DAY7= day7.cpp
DAY8= day8.cpp
DAY9= day9.cpp
FLAGS = --std=c++11
COMPILER = g++
BINDIR = bin

all: $(BINDIR) $(addprefix $(BINDIR)/,1 2 3 4 5 6 7 8 9)

$(BINDIR)/1: $(DAY1)
	$(COMPILER) $(DAY1) $(FLAGS) -o $(BINDIR)/1
$(BINDIR)/2: $(DAY2)
	$(COMPILER) $(DAY2) $(FLAGS) -o $(BINDIR)/2
$(BINDIR)/3: $(DAY3)
	$(COMPILER) $(DAY3) $(FLAGS) -o $(BINDIR)/3
$(BINDIR)/4: $(DAY4)
	$(COMPILER) $(DAY4) $(FLAGS) -o $(BINDIR)/4
$(BINDIR)/5: $(DAY5)
	$(COMPILER) $(DAY5) $(FLAGS) -o $(BINDIR)/5
$(BINDIR)/6: $(DAY6)
	$(COMPILER) $(DAY6) $(FLAGS) -o $(BINDIR)/6
$(BINDIR)/7: $(DAY7)
	$(COMPILER) $(DAY7) $(FLAGS) -o $(BINDIR)/7
$(BINDIR)/8: $(DAY8)
	$(COMPILER) $(DAY8) $(FLAGS) -o $(BINDIR)/8
$(BINDIR)/9: $(DAY9)
	$(COMPILER) $(DAY9) $(FLAGS) -o $(BINDIR)/9
$(BINDIR):
	@mkdir bin

clean:
	@rm bin -rf



