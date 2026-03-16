#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64



		// Fonction pour afficher le prompt
		void print_prompt() {
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			printf("MINI-SHELL PERSO \n :%s$ ", cwd);
		}
		// Fonction pour afficher le prompt




		// Fonction pour parser la commande
		void parse_input(char *input, char **args) {
			int i = 0;

			args[i] = strtok(input, " \n");

			while (args[i] != NULL && i < MAX_ARGS - 1) {
				i++;
				args[i] = strtok(NULL, " \n");
			}

			args[i] = NULL;
		}
		// Fonction pour parser la commande




// PROGRAMME
int main() {
	
	system("clear");

    char input[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
		
        print_prompt();

        if (fgets(input, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break;
        }

        parse_input(input, args);

        if (args[0] == NULL) {
            continue;
        }

        // commande exit
        if (strcmp(args[0], "exit") == 0) {
            printf("Bye 👋\n");
            break;
        }

        // commande cd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: argument manquant\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                }
            }
            continue;
        }

        // processus
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // processus enfant
            if (execvp(args[0], args) == -1) {
                perror("commande");
            }
            exit(EXIT_FAILURE);
        } else {
            // processus parent
            wait(NULL);
        }
    }

    return 0;
}
// PROGRAMME
