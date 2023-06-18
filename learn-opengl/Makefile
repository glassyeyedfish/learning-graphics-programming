CC = cc
CFLAGS = -std=c99 -Wall -Wextra -g -Iinclude
LDFLAGS = -lGL -lglfw

TGT = program
SRC = $(shell find -type f -name "*.c")
OBJ = $(SRC:./src/%.c=./build/%.o)
SRC_DIR =  $(shell find src -type d)
OBJ_DIR = $(SRC_DIR:src/%=build/%)

all: ${OBJ_DIR} ${TGT}

${OBJ_DIR}:
	mkdir -p $@

build/%.o: src/%.c
		${CC} -c ${CFLAGS} $< -o $@

${TGT}: ${OBJ}
		${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
		rm -fr build/
		rm ${TGT}
