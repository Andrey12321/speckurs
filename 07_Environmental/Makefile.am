CFLAGS = -g

bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c

TESTS = test

test:
	echo "SHA1 \"data" | ./rhasher > result
	echo -n "data" | sha1sum | awk '{print $$1}' > expected
	cmp expected result

	echo "MD5 \"data" | ./rhasher > result
	echo -n "data" | md5sum | awk '{print $$1}' > expected
	cmp expected result

gitclean:
	git clean -df
