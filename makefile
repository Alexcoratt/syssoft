PROJECT_NAME=syssoft_lab1

SOURCE_DIR?=src
BUILD_DIR?=build
INCLUDE_DIR?=include

CC?=clang
CFLAGS+=-Wall -std=gnu11 -I${INCLUDE_DIR} -Imodules/c-container-library/include
LFLAGS+=-ly -ll

LEX?=flex
PRS?=bison

# basic targets
main: lex prs custom_typename_registry dynamic_array
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${BUILD_DIR}/prs.c ${BUILD_DIR}/lex.c ${BUILD_DIR}/custom_typename_registry.o ${BUILD_DIR}/DynamicArray.o ${LFLAGS}

lex: mk_build_dir
	${LEX} ${LEXFLAGS} -o ${BUILD_DIR}/lex.c ${SOURCE_DIR}/lex.l

prs: mk_include_dir mk_build_dir
	${PRS} ${PRSFLAGS} -o ${BUILD_DIR}/prs.c --defines=${INCLUDE_DIR}/prs.h ${SOURCE_DIR}/prs.y

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

mk_include_dir:
	if [ ! -d ${INCLUDE_DIR} ]; then mkdir ${INCLUDE_DIR}; fi

# specific
custom_typename_registry: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/custom_typename_registry.o ${SOURCE_DIR}/custom_typename_registry.c

dynamic_array:
	${MAKE} -C modules/c-container-library BUILD_DIR=${shell realpath ${BUILD_DIR}} DynamicArray