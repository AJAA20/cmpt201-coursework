/*write a program that creates a child process. The program should use 'sigaction()' and install a
 * signal handler that catches 'SIGINT' and prints out "CTRL-C pressed". The parent should run an
 * infnite loop with 'sleep()'. The chid should have an infinite looop that perioditically sends
 * 'SIGINT' to the parent (with 'sleep()" to control the send rate). experiment with CTRL-C as well
 * - no need to set any flags i.e., '0' is fine
 *  - no need to set the masks either. learn how to not set the masks 
 *  - use 'btop' to kill the processes
 *  - look up 'getpid()' and see what it does
 *  - use 'write()' instead of 'printf()' or other print functions. (will explain later)
 *  - use 'STDOUT_FILENO' as the file discriptor (will cover later)
 *  - 
