OUTPUTS = range output1.txt output2.txt
TRASH_FILES = *.o *~ temp.* *.lib *.dll *.exe
C_FLAGS = -Wall -O0 -g
COMPILER = gcc

range: range.c
	$(COMPILER) $(C_FLAGS) $< -o range

verify: range
	gdb -x ./test1.gdb --args range 1 12 | grep -P "^***" > output1.txt
	diff expected_output1.txt output1.txt

	gdb -x ./test2.gdb --args range -100 100 3 | grep -P "^***" > output2.txt
	diff expected_output2.txt output2.txt

clean:
	rm -f $(OUTPUTS)
	rm -f $(TRASH_FILES)
