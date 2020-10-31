#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(){
	
	void sigint_handler(int sig);
	int i, bendera = 0;
	int pipefds[2];
	int number;
	int tunggu;


	if (signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal");
		exit(1);
	}
	
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	
	if(pid == 0){
	printf("Pick a number: \n");
	scanf("%d", &number);
	close(pipefds[0]); 
	write(pipefds[1], &number, sizeof(number));
	}
	else if(pid > 0){
	wait(NULL);
	close(pipefds[1]);
	read(pipefds[0], &tunggu, sizeof(tunggu));
	
	for (i = 2; i <= tunggu / 2; ++i) {

        // condition for non-prime
    if (tunggu % i == 0){
        bendera = 1;
        break;
       }
    }

    if (tunggu == 1){
        printf("1 is neither prime nor composite.\n");
    }
    else {
        if (bendera == 0)
            printf("%d is a prime number.\n", tunggu);
        else
            printf("%d is not a prime number.\n", tunggu);
    }
}
	
	return EXIT_SUCCESS;
}

void sigint_handler(int sig){
	printf("Try again\n");
}

