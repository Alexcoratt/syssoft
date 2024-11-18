PROJECT_NAME=syssoft_lab1

SOURCE_DIR?=src
BUILD_DIR?=build

CC?=clang
CFLAGS+=-Wall -std=gnu11 -Iinclude
LFLAGS+=-ly -ll

LEX?=flex
PRS?=bison

# basic targets
main: lex prs custom_typename_registry dynamic_array
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${BUILD_DIR}/prs.c ${BUILD_DIR}/lex.c ${LFLAGS}

lex: mk_build_dir
	${LEX} ${LEXFLAGS} -o ${BUILD_DIR}/lex.c ${SOURCE_DIR}/lex.l

prs: mk_build_dir
	${PRS} ${PRSFLAGS} -o ${BUILD_DIR}/prs.c --defines=include/prs.h ${SOURCE_DIR}/prs.y

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi
