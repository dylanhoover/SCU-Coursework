#!/bin/bash
make;
echo "------FIFO------"
cat textInput.txt | ./fifo 10
echo "-----End FIFO-----"
echo
echo "------LRU------"
cat textInput.txt | ./lru 10
echo "------END LRU------"
echo
echo "-----Second Chance-----"
cat textInput.txt | ./secchance 10
echo "-----End Second Chance-----"

echo "FIFO 10k Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./fifo 10 | wc -l
cat accesses.txt | ./fifo 50 | wc -l
cat accesses.txt | ./fifo 100 | wc -l
cat accesses.txt | ./fifo 250 | wc -l
cat accesses.txt | ./fifo 500 | wc -l

echo
echo "Second Chance 10k Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./secchance 10 | wc -l
cat accesses.txt | ./secchance 50 | wc -l
cat accesses.txt | ./secchance 100 | wc -l
cat accesses.txt | ./secchance 250 | wc -l
cat accesses.txt | ./secchance 500 | wc -l
echo
echo "LRU 10k Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt| ./lru 10 | wc -l
cat accesses.txt| ./lru 50 | wc -l
cat accesses.txt| ./lru 100 | wc -l
cat accesses.txt| ./lru 250 | wc -l
cat accesses.txt| ./lru 500 | wc -l
echo
make clean;
echo