PROJECT_NAME=syssoft_lab1

SRC?=src
GRMR?=grammar
BUILD?=build

CC?=clang
CFLAGS+=-Wall -std=gnu11 -Iinclude -Ibuild
LFLAGS+=-ll

# basic targets

main: $(BUILD)/my-lang.a
	$(CC) $(CFLAGS) -o $(BUILD)/$(PROJECT_NAME) main.c $^ $(LFLAGS)

build:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*.c $(BUILD)/*.o $(BUILD)/*.h $(BUILD)/*.a

# special targets

$(BUILD)/%.o: $(SRC)/%.c build
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS+=-g
debug: main 

# text analysis

$(BUILD)/my-lang.a: $(BUILD)/my-lang.l.o $(BUILD)/my-lang.y.o $(BUILD)/ast.o $(BUILD)/ast-output.o
	ar rcs $@ $^

$(BUILD)/my-lang.l.o: build
	$(LEX) $(LEXFLAGS) -o $(BUILD)/my-lang.l.c $(GRMR)/my-lang.l
	$(CC) $(CFLAGS) -c -o $@ $(BUILD)/my-lang.l.c

$(BUILD)/my-lang.y.o: build
	$(YACC) $(YFLAGS) -o $(BUILD)/my-lang.y.c --header=$(BUILD)/my-lang.y.h $(GRMR)/my-lang.y
	$(CC) $(CFLAGS) -c -o $@ $(BUILD)/my-lang.y.c
