# 42core-get_next_line (2021)

get_next_line is a function that reads one line at a time until EOF, and returns the line without \n

Mandatory Part:
- reads a line from a file, and returns line without \n

Bonus Part:
- expand mandatory section code with 2 additional constraints:
  - work for multiple opened files
  - use only one static variable 

Structure of get_next_line
----------------------------------------------------
Main function: 
int  get_next_line(int fd, char **line)

Three parts in this code-
1. Validate all inputs, check for buff allocation error, and read errors
2. If no errors, read from file and store in temporary buffer with read_line(...)
3. Once reading is completed, process the line in the buffer and return output with make_line(...)

Part 1 done in get_next_line(...)
Part 2 done by read_line(int fd, char \*buff, char \*s)
Part 3 done by make_line(char **, char \*s)

Bonus
----------------------------------------------------
Code is the same with mandatory part, with changes in get_next_line for the extra requirements:

char \*s in mandatory declared as char \*s[FD_SIZE] array in bonus instead
