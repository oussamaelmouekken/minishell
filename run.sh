#!/bin/bash

make && make clean && clear && ./minishell #valgrind --leak-check=full --show-leak-kinds=all --suppressions=file.supp -s 
