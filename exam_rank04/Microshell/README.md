### Microshell ###

| 1. | 2. |
|-----|-----|
|[Subject](https://github.com/Ysoroko/exams_42/blob/master/exam_rank04/Microshell/subject.en.txt) | [My solution](https://github.com/Ysoroko/exams_42/blob/master/exam_rank04/Microshell/microshell.c)|


#### Pro tips:
- If you use **exit(exit_status)** command with the right exit_status, there is no need to free all the memory you allocated
- Main arguments can easily be separated by replacing strings "|" and ";" by NULL pointers
  - Just store the type (";" or "|") in a variable before doing this
  - Store the address of the first string of the command in **argv** in a variable -> this will be your string array for execve
  - Example:
    ``` Bash
    ./a.out cat microshell.c "|" wc -l ";" ls
    ```
    
    - 1) Array of strings = &(argv[1]). Type = '|'. Replace argv[3] ("|") by NULL
    - 2) Array of strings = &(argv[4]). Type = ';'. Replace argv[6] (";") by NULL
    - 3) Array of strings = &(argv[7]). Type = '0'.
