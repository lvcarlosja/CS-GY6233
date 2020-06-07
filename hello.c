#define TRUE 1

while (TRUE) {
	type_prompt();
	read_command(command, parameters);

	if (fork() != 0) {
		/* Parent code.*/
		waitpid(-1, &status, 0);
	} else {
		/* Child code. */
		execv(command, parameters, 0);
	}
}