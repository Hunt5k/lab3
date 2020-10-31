#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(){
	
	void sigint_handler(int sig);
	int i, flag = 0;
	int pipefds[2];
	int nombor;
	int buffer;


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
	printf("Please enter a number: \n");
	scanf("%d", &nombor);
	close(pipefds[0]); 
	write(pipefds[1], &nombor, sizeof(nombor));
	}
	else if(pid > 0){
	wait(NULL);
	close(pipefds[1]);
	read(pipefds[0], &buffer, sizeof(buffer));
	
	for (i = 2; i <= buffer / 2; ++i) {

        // condition for non-prime
    if (buffer % i == 0){
        flag = 1;
        break;
       }
    }

    if (buffer == 1){
        printf("1 is neither prime nor composite.\n");
    }
    else {
        if (flag == 0)
            printf("%d is a prime number.\n", buffer);
        else
            printf("%d is not a prime number.\n", buffer);
    }
}
	
	return EXIT_SUCCESS;
}

void sigint_handler(int sig){
	printf("Try again\n");
}

