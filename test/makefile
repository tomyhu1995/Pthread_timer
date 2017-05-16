# Copyright (C) 2017 by Hsien Wen, Hu
#
# Makefile for sample_linked_list
#
#
# Author: Hsien-Wen, Hu
#
# Date: 2017/4/15
#

CC = gcc

CFLAGS += -Wall
CFLAGS += -g

EXE_NAME = test_pthread_timer

INC =
INC += -I../

SRC = 
SRC += ../funclog
SRC += ../linked_list
SRC += ../pthread_timer
SRC += ./test_pthread_timer

LDFALG =
LDFALG += -lpthread

SRC_FILES = ${addsuffix .c, ${SRC}}
OBJ_FILES = ${addsuffix .o, ${SRC}}

all: ${EXE_NAME}

${EXE_NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} ${INC} ${OBJ_FILES} -o $@ ${LDFALG}
${OBJ_FILES} : %.o : %.c
	${CC} ${CFLAGS} -c ${INC} $< -o $@ ${LDFALG}
clean:
	rm -rf ${OBJ_FILES} ${EXE_NAME}