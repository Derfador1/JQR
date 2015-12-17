CFLAGS+=-std=c11
CFLAGS+=-g -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -D _XOPEN_SOURCE=800
CFLAGS+=-Werror


.PHONY: clean build

PY_PATH=/opt/rh/python33/root/usr
CFLAGS+=-I$(PY_PATH)/include/python3.3m
LDFLAGS+=-L$(PY_PATH)/lib64

build:
	python3 setup.py build

clean:
	-$(RM) *.o
