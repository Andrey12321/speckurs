#!/bin/bash

# Тест на успешное перемещение
./move test.txt moved.txt
if [ -f moved.txt ]; then
	echo "Test 1 passed: moved.txt created."
else
	echo "Test 1 failed: moved.txt not created."
fi

# Тест на попытку удаления защищенного файла
echo "This file should not be deleted" > PROTECT_test.txt
LD_PRELOAD=./protect.so ./move PROTECT_test.txt moved.txt
if [ -f PROTECT_test.txt ]; then
	echo "Test 2 passed: PROTECT_test.txt not deleted."
else
	echo "Test 2 failed: PROTECT_test.txt deleted."
fi

# Тест на ошибки
./move non_existent.txt moved.txt
if [ $? -ne 1 ]; then
	echo "Test 3 failed: should return error code for non-existent infile."
else
	echo "Test 3 passed."
fi
