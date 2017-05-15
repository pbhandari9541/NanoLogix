//By Valentin Gazeau and Pramesh Bhandari

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#define MAX 80
#define TOK_DELIM " \t\r\n\a!|"
#define CHUNK 5

char ** parse(char * input);
int execute( char ** args);
char * getln();
void login();
void level1();
void level2();
void level3();
void level4();
void level5();
void level6();
void reset();
void clear();

int helpmax = 4;
char* last;
char* user;
char* pass;
int stat = 1;
int lvl[5] = {0,0,0,0,0};

int main(){
    char* input, shell_prompt[100];
	char* cdir;
	char **arguments;
	int i;
	ssize_t bufsize = 0;
	unsigned int len;

	char *help[13] = {"cd - Change current directory (note: cd .. to go to parent dir)", "ls - List items in the current directory", "cat - Display the contents of a file", "login - Login on the system", "cygstart - Display the content of an image file", "clear - Clears the content displayed on the terminal","wc - counts the lines, words and characters of a file, respectively", "chmod (+/- rwx) - change mode of a shell script (read, write, execute)", "./file - Run an executable file", "vim - Edit or create files", "gcc - Compile C code", "exit - Exit the game (also resets the game)"};

   	// Configure readline to auto-complete paths when the tab key is hit.
   	rl_bind_key('\t', rl_complete);
	level1();

	do{
		// Free previous command
		free(input);

		char * cdir = getcwd(NULL, 1024);
		char s[] = "";
		char * token;
		last = token = strtok(cdir, "/");
		for (;(token = strtok(NULL, "/")) != NULL; last = token);

		if(!strncmp("dir3", last, 4)){
			snprintf(shell_prompt, sizeof(shell_prompt), "vimLogix:~/Turing/dir2/%s$> ", last);
		}else if( !strncmp("dir1", last, 4) || !strncmp("dir2", last, 4) ){
			snprintf(shell_prompt, sizeof(shell_prompt), "vimLogix:~/Turing/%s$> ", last);
		}else{

			// Print Shell prompt before and after every execution
        		snprintf(shell_prompt, sizeof(shell_prompt), "vimLogix:~/%s$> ", last);
		}

	        // Display prompt and read input (NB: input must be freed after use)...
	        input = readline(shell_prompt);

	        // Check for EOF.
	        if (!input){
	            break;
		}
	        // Add input to history.
	        add_history(input);

		// If the command is "exit", close the program
		if(!strncmp("exit", input, 4)){
			stat = 0;
			return 1;

		}else if (!strncmp("help", input, 4)){

			printf("\n");
			for( i = 0; i < helpmax; i++){
				printf("\t%s\n", help[i]);
			}
			printf("\n");
		}else if (!strncmp("login", input, 5)){

			login();

		}else{

			// Parse the command for arguments
			arguments = parse(input);

			// In case the command is "change directory"
			if(!strncmp("cd", input, 2)){

				if ( arguments[1] == NULL || !strcmp(arguments[1], "/")){
					printf("\nYou are not allowed to CD to that location!\n\n");

				}else if( !strcmp(arguments[1], "../..") ){
					printf("\nYou can only move to one directory at a time!\n\n");

				}else if( !strcmp(arguments[1], "..") ){

					if( !strncmp(last, "Apti", 4) || !strncmp(last, "AI-7", 4) || !strncmp(last, "Turi", 4) ){
						printf("\nYou are not allowed to CD to that location!\n\n");
					}else{
						chdir(arguments[1]);
						printf("\n");
					}

				}else{
					chdir(arguments[1]);
					printf("\n");
				}
			}else if (!strncmp("cat", input, 3) && arguments[1] == NULL){
				printf("\nPlease specify a file to display. (Usage: cat filename.txt)\n\n");
			}else{
				if(!strncmp("ls", input, 2) || !strncmp("cat", input, 3) || !strncmp("clear", input, 5) || !strncmp("cygstart", input, 3) || !strncmp("sl", input, 2) || !strncmp("wc", input, 2) || !strncmp("./", input, 2) || !strncmp("chmod", input, 5) || !strncmp("vim", input, 4) || !strncmp("gcc", input, 3)){
					printf("\n");
					// Execute the command
					stat = execute(arguments);
				}else{
					printf("\nYou are not allowed to launch this command!\n\nAvailable commands are displayed in \"help\".\n\n");
				}
				printf("\n");
			}
		}

	} while (stat);

	free(input);
	free(arguments);
	return 0;
}

//parsing the input for arguments
char ** parse(char * input){
	int buf = MAX, pos = 0;
	char **tokens = malloc(buf * sizeof(char*));
	char *token;

	token = strtok(input, TOK_DELIM);
	while(token != NULL){
		tokens[pos] = token;
		token = strtok(NULL, TOK_DELIM);
		pos++;
	}
	tokens[pos] = NULL;

	return tokens;
}

//executing the input
int execute( char ** args){
	pid_t pid, wait;
	int stat;

	pid = fork();

	if(pid == 0){
		if(execvp(args[0], args) == -1){
			printf("Could not execute: %s\n",args[0]);
		}
		exit(EXIT_FAILURE);
	}else if( pid < 0){
		printf("Error forking\n");
		exit(EXIT_FAILURE);
	}else if (!strncmp("cygstart", args[0], 3)){
		return 1;
	}else{
		do{
			wait = waitpid(pid, &stat, WUNTRACED);
		}while(!WIFEXITED(stat) && ! WIFSIGNALED(stat));
	}
	return 1;
}

void level1(){

	clear();
	chdir("AptitudeTest");

	printf("\n\n\t\tWelcome to vimLogix!\n\nvimLogix is a governmental agency which develops advanced artificial \nintelligence. More specifically, our work focuses on AIs with autonomous \nself-improvement. Recursive self-improvement AIs have the ability to \nprogram their own software, recursively.\n");
	printf("\nPlease login to your vimLogix account...\n\n");
	printf("Type \"help\" for information about the system commands.\n\n");

}

void level2(){

	char newDir[MAX] = "mkdir AI-7723";
	char **arguments = parse(newDir);
	execute(arguments);
	chdir("AI-7723");

	char newFiles[MAX] = "cp ../../res/birthday.jpg .";
	arguments = parse(newFiles);
	execute(arguments);

	char newFiles2[MAX] = "cp ../../res/research.mail .";
	arguments = parse(newFiles2);
	execute(arguments);

	char newFiles3[MAX] = "cp ../../res/birthday.mail .";
	arguments = parse(newFiles3);
	execute(arguments);

	char newFiles4[MAX] = "cp ../../res/AutomaticMachine.txt .";
	arguments = parse(newFiles4);
	execute(arguments);

	clear();

	printf("\n\n\t\tWelcome to vimLogix, AI-7723!\n\nERROR: Your personal files have been locked for security\n\nLast login: 12/02/2076, You have been away for 3 764 years.\n\nAt vimLogix, you will be asked to complete a series of task such as data \nanalysis and computation. To validate your aptitude test, you are required \nto manifest recursive self-improvement abilities.\nFor this exercise, you are required to find a password by analyzing files \non the system and login with it.\n\n* PRO TRICK => Use TAB to auto-complete an existing filename in the directory *\n\n( Hint: the help command has been updated )\n\n");

	helpmax+=2;

}

void level3(){

	char newDir[MAX] = "mkdir -p Turing Turing/dir1 Turing/dir2/dir3";
	char **arguments = parse(newDir);
	execute(arguments);
	chdir("Turing");

	char newFile[MAX] = "cp ../../../res/AI-Danger.txt .";
	arguments = parse(newFile);
	execute(arguments);

	char newFiles[MAX] = "cp ../../../res/encrypt.part1 dir1";
	arguments = parse(newFiles);
	execute(arguments);

	char newFiles2[MAX] = "cp ../../../res/coffee.mail dir1";
	arguments = parse(newFiles2);
	execute(arguments);

	chdir("dir2");
	char newFiles3[MAX] = "cp ../../../../res/puppy.jpg .";
	arguments = parse(newFiles3);
	execute(arguments);

	char newFile2[MAX] = "cp ../../../../res/ArtificialSuperIntelligence.txt .";
	arguments = parse(newFile2);
	execute(arguments);

	char newFiles4[MAX] = "cp ../../../../res/encrypt.part2 dir3";
	arguments = parse(newFiles4);
	execute(arguments);

	char newFile3[MAX] = "cp ../../../../res/StateDiagram.jpg dir3";
	arguments = parse(newFile3);
	execute(arguments);

	chdir("..");

	clear();

	printf("\n\n\t\tWelcome back Dr. Turing!\n\nLast login: 06/20/2076.\n\nCongratulations on your success on AI-7723's computer. For your next exercise \nyou will be required to move through directories and find the super hidden \nencrypted password. It is encrypted using two different files, will you be able to locate and decipher the password ? If you are, we may have a job for you...\nthe SupremeCPU may have a job for you... \n\n* PRO TRICK => Use UP and DOWN arrows to cycle through the command history *\n\n( Hint: the help command has been updated )\n\n");
	helpmax+=1;

}

void level4(){

	while(strncmp("Turing", last, 6)){
		chdir("..");
		char * cdir = getcwd(NULL, 1024);
		char * token;
		last = token = strtok(cdir, "/");
		for (;(token = strtok(NULL, "/")) != NULL; last = token);
	}
	char newDir[MAX] = "mkdir Hacker";
	char **arguments = parse(newDir);
	execute(arguments);
	chdir("Hacker");

	char newFile3[MAX] = "cp ../../../../res/script.sh .";
	arguments = parse(newFile3);
	execute(arguments);

	char newFile2[MAX] = "cp ../../../../res/diary.txt .";
	arguments = parse(newFile2);
	execute(arguments);

	char newFile1[MAX] = "cp ../../../../res/likeit.sh .";
	arguments = parse(newFile1);
	execute(arguments);

	char newFile4[MAX] = "cp ../../../../res/guesswhat.sh .";
	arguments = parse(newFile4);
	execute(arguments);

	char newFile5[MAX] = "cp ../../../../res/submarines.txt .";
	arguments = parse(newFile5);
	execute(arguments);

	helpmax += 2;

	printf("\n\n\t\tWelcome Applicant!\n\nI am the SupremeCPU, my job is to analyze people's computers to find any \nweakness in the system. As you probably already know it, it is a job that \nI can't complete on my own. Congratulations for passing previous levels \nbut in order to qualify for the job you will need to prove me your worth...\n\nHow good are you with shell scripting? A shell script is a computer program \ndesigned to be run by the Unix shell, it's basically a command-line interpreter.\nAll you have to do is to make sure the script is executable... child's play!\nNow go and don't dissapoint me...\n\n* PRO TRICK => don't forget UP/DOWN for history and TAB for auto-complete *\n\n( Hint: the help command has been updated )\n\n");

}

void level5(){

	char newDir[MAX] = "mkdir Dijkstra";
	char **arguments = parse(newDir);
	execute(arguments);
	chdir("Dijkstra");

	char newFile1[MAX] = "cp ../../../../../res/helpA.sh .";
	arguments = parse(newFile1);
	execute(arguments);

	char newFile2[MAX] = "cp ../../../../../res/helpB.sh .";
	arguments = parse(newFile2);
	execute(arguments);

	char newFile3[MAX] = "cp ../../../../../res/article.txt .";
	arguments = parse(newFile3);
	execute(arguments);

	char newFile4[MAX] = "cp ../../../../../res/triangle.jpg .";
	arguments = parse(newFile4);
	execute(arguments);

	char newFile5[MAX] = "cp ../../../../../res/oldman.jpg .";
	arguments = parse(newFile5);
	execute(arguments);

	char newFile6[MAX] = "cp ../../../../../res/flowers.jpg .";
	arguments = parse(newFile6);
	execute(arguments);

	printf("\n\n\t\tLooks like we have a future Hacker!\n\nCongratulations kid! Your application is getting better and better but there \nare still two examinations you will have to pass in order to guarantee the \nposition at vimlogix. \n\nWe already believe that you will be a great addition to our team but we still \nwant to torture you a little. Let's not spoil the fun, now that you have learnt \nall the basic tools, try to put them to good use. \n\nThis experience will test your abilities to think outside the box. This time \nthere are no Hint and no ProTrick, you are on your own !\n\n");

}

void level6(){

	char newDir[MAX] = "mkdir FinalTest";
	char **arguments = parse(newDir);
	execute(arguments);
	chdir("FinalTest");

    char newFile1[MAX] = "cp ../../../../../../res/UserPass.txt .";
	arguments = parse(newFile1);
	execute(arguments);

	helpmax+=3;

printf("\n\n\t\tvimLogix is very impressed with your skills!\n\nFor your final task, we would like you to understand and speak Machine Language.\nDid you really think you could communicate with a computer using only natural\nlanguage? Well maybe in a very near future but for the moment being, computers\ntalk in Binary and Hexadecimal.\n\nThe help command has been updated to allow you more freedom at this level.\nShow us your abilities to talk to machines and the job is yours!\n\n( Hint: binary is base 2 and Hex is base 16 )\n\n");

}

char *getln(){

	char *line = NULL, *tmp = NULL;
	size_t size = 0, index = 0;
	int ch = EOF;

	while (ch) {
		ch = getc(stdin);

	        if (ch == EOF || ch == '\n'){
			ch = 0;
		}

		if (size <= index) {
			size += CHUNK;
			tmp = realloc(line, size);

			if (!tmp) {
				free(line);
				line = NULL;
                		break;
			}
			line = tmp;
		}
	line[index++] = ch;
	}

	return line;
}

void login(){

	printf("\n\tUsername: ");
	user = getln();
	printf("\n\tPassword: ");
	pass = getln();

		if( !strncmp("AI-7723", user, 7) && !strncmp("tomorrow", pass, 8)){

			if( lvl[0] == 0){
				level2();
				lvl[0] = 1;
			}else{
				printf("\nYou are already logged in as AI-7723\n");
			}

		}else if((!strncmp("AlanTuring", user, 10) || !strncmp("alanturing", user, 10) || !strncmp("ALANTURING", user, 10)) && (!strncmp("35/23/06", pass, 8) || !strncmp("352306", pass, 6))){
			if( lvl[1] == 0){
				level3();
				lvl[1] = 1;
			}else{
				printf("\nYou are already logged in as AlanTuring\n");
			}

		}else if((!strncmp("SupremeCPU", user, 10) || !strncmp("supremecpu", user, 10)) && (!strncmp("m3gapa$$w0rd", pass, 12) )){

			if( lvl[2] == 0){
				clear();
				level4();
				lvl[2] = 1;
			}else{
				printf("\nYou are already logged in as SupremeCPU\n");
			}

		}else if( (!strncmp("Dijkstra", user, 6) || !strncmp("dijkstra", user, 6)) && (!strncmp("crypto", pass, 6) )){

			if( lvl[3] == 0){
				clear();
				level5();
				lvl[3] = 1;
			}else{
				printf("\nYou are already logged in as Dijkstra\n");
			}

		}else if( !strncmp("7wonders", user, 6) && (!strncmp("OLBAGI", pass, 6) )){

			if( lvl[4] == 0){
				clear();
				level6();
				lvl[4] = 1;
			}else{
				printf("\nYou are already logged in as 7wonders\n");
			}

		}else if( (!strncmp("ada", user, 3) || !strncmp("ADA", user, 3) ) && (!strncmp("100111011", pass, 9) )){

		printf("\n\nCongratulations on finishing the game. We hope this knowledge of basic Unix shell commands will help you in the future\n\nThe game will now reset...\n\n");

		reset();

		}else{
			printf("\n\tError: username and/or password not valid!\n");
		}

		printf("\n");

}

void clear(){
	char clear[6] = "clear";
	char **arguments = parse(clear);
	execute(arguments);

}

void reset(){

	while(strncmp("vimLogix", last, 9)){
		chdir("..");
		char * cdir = getcwd(NULL, 1024);
		char * token;
		last = token = strtok(cdir, "/");
		for (;(token = strtok(NULL, "/")) != NULL; last = token);
	}

	sleep(2);

	char reset[11] = "./reset.sh";
	char **arguments = parse(reset);
	execute(arguments);

	stat = 0;

}
