#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <char1> <char2> ... <charN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // execl expects a list of arguments, with NULL at the end
        // We need to copy argv from parent to a new array for execl,
        // as execl will replace this process, and we want to pass
        // the original arguments to the new program.

        // Dynamically allocate memory for the argument list
        char **child_argv = (char **)malloc(sizeof(char *) * (argc + 1));
        if (child_argv == NULL) {
            perror("malloc failed for child_argv");
            exit(EXIT_FAILURE);
        }

        child_argv[0] = "./child_program"; // The name of the executable
        for (int i = 1; i < argc; i++) {
            child_argv[i] = argv[i]; // Copy arguments from parent's argv
        }
        child_argv[argc] = NULL; // Null-terminate the argument list

        printf("Parent: Executing child_program...\n");
        // Execute the child program, passing all arguments from main_program
        execv(child_argv[0], child_argv);

        // If execv returns, it means an error occurred
        perror("execv failed");
        free(child_argv); // Only if execv fails
        exit(EXIT_FAILURE);

    } else { // Parent process
        printf("Parent: Waiting for child to finish...\n");
        int status;
        waitpid(pid, &status, 0); // Wait for the specific child process
        printf("Parent: Child process finished with status %d.\n", WEXITSTATUS(status));
    }

    return 0;
}
