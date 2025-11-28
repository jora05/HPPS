CC?=cc
CFLAGS?=-std=c11 -Wall -Werror -Wextra -pedantic

# Template for a new program 'foo'
# The line below $(CC) MUST start with a single TAB character
test_bitvec8: bitvec8.c test_bitvec8.c
	$(CC) $(CFLAGS) -o test_bitvec8 bitvec8.c test_bitvec8.c

# The 'test' target depends on 'test_bitvec8' being compiled
test: test_bitvec8
	./test_bitvec8