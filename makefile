PROJECT_NAME=syssoft_lab1

SOURCE_DIR?=src
BUILD_DIR?=build

CC?=clang
CFLAGS+=-Wall -std=gnu11 -Iinclude
LFLAGS+=-ll

# basic targets

main: lex prs
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJECT_NAME) $(SOURCE_DIR)/main.c $(BUILD_DIR)/prs.c $(BUILD_DIR)/lex.c $(SOURCE_DIR)/ast.c $(SOURCE_DIR)/ast-node-type.c $(LFLAGS)

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm $(BUILD_DIR)/*.c $(BUILD_DIR)/*.o

# special targets

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c build
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS+=-g
debug: main 

# text analysis

lex: build
	$(LEX) $(LEXFLAGS) -o $(BUILD_DIR)/lex.c $(SOURCE_DIR)/lex.l

prs: build
	$(YACC) $(YFLAGS) -o $(BUILD_DIR)/prs.c --header=include/prs.h $(SOURCE_DIR)/prs.y
