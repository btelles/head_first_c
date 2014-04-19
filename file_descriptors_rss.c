#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void error(char *message) {
	fprintf(stderr, "Error: %s (%s)", message, strerror(errno));
	exit(1);
}

void open_url(char* url) {
	char launch[255];
	sprintf(launch, "x-www-browser '%s' &", url);
	system(launch);
}

void scrape_feed_to_stdout_exit(char *phrase, char *vars[], int file_descriptor[]) {
	close(file_descriptor[0]);

	if ( dup2(file_descriptor[1], 1) == -1) {
		error("Can't redirect Standard Output");
	}
	if (execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py", "-u",
	    phrase, NULL, vars) == -1) {
	error("Can't run script");
	}

}

void get_urls_and_open_browsers(int file_descriptor[]) {
	close(file_descriptor[1]);
	if (dup2(file_descriptor[0], 0) == -1) {
		error("Couldn't redirect/read from Standard Input");
	}

	char line[255];
	while (fgets(line, 255, stdin)) {
		if (line[0] == '\t')
			open_url(line + 1);
	}
}

int main(int argc, char **argv) {
	char *phrase = argv[1];
	char *vars[] = {"RSS_FEED=http://rss.cnn.com/rss/cnn_tech.rss", NULL};

	FILE *f = fopen("stories.txt", "w");

	if (!f) {
		error("Can't open stories.txt");
	}

	int file_descriptor[2];
	if (pipe(file_descriptor) == - 1) {
		error("Can't create the pipe");
	}

	pid_t pid = fork();
	if (pid == -1) {
		error("Can't fork process");
	}

    // In child process
	if (!pid) {
		scrape_feed_to_stdout_exit(phrase, vars, file_descriptor);
	}

	// In parent process
	get_urls_and_open_browsers(file_descriptor);

	// No longer necessary since parent/main process
	// reads from stdin until the pipe closes.
	/*
	int pid_status;
	waitpid(pid, &pid_status, 0);

	if (WEXITSTATUS(pid_status)) {
        error("Error waiting for child process");
	} else {
	    printf("\nGot all the \"%s\" stories\n", phrase);
	}
	*/
	return 0;
}
