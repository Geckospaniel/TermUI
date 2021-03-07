HEADER	=	$(wildcard *.hh)
SOURCE	=	$(wildcard *.cc)
OBJECT	+=	$(addprefix obj/,$(addsuffix .o,$(SOURCE)))

build: build_lib obj/ $(OBJECT)
	@echo $(OBJECT)
	@g++ -o x $(OBJECT) ../obj/*.o -lncurses -lpthread

obj/%.cc.o:	%.cc $(HEADER)
	@echo "Building $<"
	@g++ -c -o $@ $< -std=c++17 -pedantic -Wall -Wextra

build_lib:
	make -C ..

obj/:
	@mkdir -p obj
