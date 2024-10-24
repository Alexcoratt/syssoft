PROJECT_NAME=syssoft_lab1

SOURCE_DIR?=src
BUILD_DIR?=build
INCLUDE_DIR?=include

CC?=clang
CFLAGS+=-Wall -std=gnu11 -I${INCLUDE_DIR}
LFLAGS+=-ly -ll

LEX?=flex
PRS?=bison

# basic targets
main: lex prs
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${BUILD_DIR}/prs.c ${BUILD_DIR}/lex.c ${LFLAGS}

lex: mk_build_dir
	${LEX} ${LEXFLAGS} -o ${BUILD_DIR}/lex.c ${SOURCE_DIR}/lex.l

prs: mk_include_dir mk_build_dir
	${PRS} ${PRSFLAGS} -o ${BUILD_DIR}/prs.c --defines=${INCLUDE_DIR}/prs.h ${SOURCE_DIR}/prs.y

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

mk_include_dir:
	if [ ! -d ${INCLUDE_DIR} ]; then mkdir ${INCLUDE_DIR}; fi

# tests
dynarray_test: mk_build_dir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/dynarray_test ${SOURCE_DIR}/dynarray_test.c ${BUILD_DIR}/dynarray_float.o