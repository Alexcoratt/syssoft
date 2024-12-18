PROJECT_NAME=syssoft_lab1

SOURCE_DIR?=src
GRAMMAR_DIR?=grammar
BUILD_DIR?=build

CC?=clang
CFLAGS+=-Wall -std=gnu11 -Iinclude -Ibuild
LFLAGS+=-ll

# basic targets

main: $(BUILD_DIR)/my-lang.a
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJECT_NAME) main.c $^ $(LFLAGS)

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm $(BUILD_DIR)/*.c $(BUILD_DIR)/*.o $(BUILD_DIR)/*.h $(BUILD_DIR)/*.a

# special targets

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c build
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS+=-g
debug: main 

# text analysis

$(BUILD_DIR)/my-lang.a: $(BUILD_DIR)/my-lang.l.o $(BUILD_DIR)/my-lang.y.o $(BUILD_DIR)/ast.o $(BUILD_DIR)/ast-node-type.o
	ar rcs $@ $^

$(BUILD_DIR)/my-lang.l.o: build
	$(LEX) $(LEXFLAGS) -o $(BUILD_DIR)/my-lang.l.c $(GRAMMAR_DIR)/my-lang.l
	$(CC) $(CFLAGS) -c -o $@ $(BUILD_DIR)/my-lang.l.c

$(BUILD_DIR)/my-lang.y.o: build
	$(YACC) $(YFLAGS) -o $(BUILD_DIR)/my-lang.y.c --header=$(BUILD_DIR)/my-lang.y.h $(GRAMMAR_DIR)/my-lang.y
	$(CC) $(CFLAGS) -c -o $@ $(BUILD_DIR)/my-lang.y.c
