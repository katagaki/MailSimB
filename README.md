# MailSimB

**CAUTION: This code is provided AS-IS and should be considered an archive for reference purposes only.**
**The code may contain errors or bugs that may not be fixed.**

## Clean Build

To compile the Mail Simulator, navigate to the directory (use the 'cd' command) where the source files are stored, then execute the following command:

    clear; clear; rm *.o; rm *.out; g++ --std=c++11 -c mail.cpp queue.cpp; g++ --std=c++11 mailsim.cpp mail.o queue.o; ./a.out

Alternatively, execute the following commands in sequential order:

    rm *.o
    rm *.out
    g++ --std=c++11 -c mail.cpp queue.cpp
    g++ --std=c++11 mailsim.cpp mail.o queue.o
    ./a.out

## Run Only

To run the program with the provided binaries, navigate to the directory (use the 'cd' command) where the source files are stored, then execute the following command:

    ./a.out
