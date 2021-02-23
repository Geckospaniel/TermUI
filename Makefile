HEADER	=	$(wildcard *.hh)
SOURCE	=	$(wildcard *.cc)
OBJECT	=	$(addprefix obj/,$(addsuffix .o,$(SOURCE)))

build: obj/ $(OBJECT)
	@g++ -o x $(OBJECT) -lncurses

obj/%.cc.o:	%.cc $(HEADER)
	@echo "Building $<"
	@g++ -c -o $@ $< -std=c++11 -pedantic -Wall -Wextra

obj/:
	@mkdir -p obj
