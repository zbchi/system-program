
src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))

target=out

CC=gcc
CFLAGS=-g -Wall -Wextra 


ALL: $(target)

$(target): $(obj)
	$(CC) $^ -o $@


$(obj): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	-rm -rf $(obj) $(target)

.PHONY: clean ALL
