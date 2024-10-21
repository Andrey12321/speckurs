TARGET = esub
TRASH = *.txt
CFLAGS = -Wall
CC = gcc

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $< -o $@

test: $(TARGET)
	./$(TARGET) '.ui' 'SUI' 'sui' > provided_results_1.txt
	echo 'sui' | sed -E 's/.ui/SUI/' > expected_results_1.txt
	cmp expected_results_1.txt provided_results_1.txt

	./$(TARGET) '[0-9][0-9]' '##' 'Phone: 12345' > provided_results_2.txt
	echo 'Phone: 12345' | sed 's/[0-9][0-9]/##/' > expected_results_2.txt
	cmp expected_results_2.txt provided_results_2.txt

	./$(TARGET) '(.)\1' '\1' 'boookkeeper' > provided_results_3.txt
	echo 'boookkeeper' | sed -E 's/(.)\1/\1/' > expected_results_3.txt
	cmp expected_results_3.txt provided_results_3.txt

clean:
	rm -f $(TARGET)
	rm -f $(TRASH)
