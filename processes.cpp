#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]) {
  // Check if the correct number of arguments have been passed
  if (argc != 2) {
    cout << "Usage: ./process_search process_name" << endl;
    return 1;
  }

  int filedes[2];
  // Create a pipe to pass information between the parent and child processes
  pipe(filedes);

  pid_t pid = fork();

  if (pid == -1) {
    // Error: fork failed
    cout << "Error: fork failed" << endl;
    return 1;
  } else if (pid == 0) {
    // Child process
    // Close the read end of the pipe
    close(filedes[0]);
    // Duplicate the write end of the pipe so that it can be written to
    dup2(filedes[1], 1);

    // Execute the pgrep command to search for processes with the given name
    execlp("pgrep", "pgrep", argv[1], NULL);
  } else {
    // Parent process
    // Close the write end of the pipe
    close(filedes[1]);
    // Duplicate the read end of the pipe so that it can be read from
    dup2(filedes[0], 0);

    int count = 0;
    int pid;
    // Read the process IDs from the pipe and count them
    while (cin >> pid) {
      count++;
    }

    // Output the number of processes found
    cout << "Number of processes with name " << argv[1] << ": " << count << endl;
    // Wait for the child process to terminate
    wait(NULL);
  }

  return 0;
}
