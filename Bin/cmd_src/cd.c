#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include "../../Src/globals.h"
#include "../../Src/lib.h"

//If directory change success, return 0 and write to file
int write_change();

//Verify the directory change to be non-malicious :)
void audit_dir();

int main(int argc, char *argv[]){

	int result = 0;
	char *copy = argv[1];

	if( argc > 1 ){
		result = chdir(copy);
	}else{
		puts("Usage: cd [dir here]");
		return -1;
	}

	//If successfully changes dir
	if(!result)
		write_change(copy);
	else
		puts("Directory not found!");
	


	return 0;
}

int write_change(char *copy){
	FILE *fptr;

	char cwd_file[64] = "/home/";

	strcat(cwd_file, getenv("USER"));

	strcat(cwd_file, "/");

	strcat(cwd_file, RSHELL_DIR);

	strcat(cwd_file, "/");

	strcat(cwd_file, USER_CD_LOG);

	if( fopen(cwd_file,"w") == NULL )
		puts(RED_TEXT"Could not reliably determine directory!"RESET);
	
	fptr = fopen(cwd_file, "w");

	//Protect against errors
	if( fptr == NULL ){
		puts(RED_TEXT"File Access Error[FAE]...");
		puts("Error 1001..."RESET);
		return -1;
	}
	
	//char *rel = basename(copy);

	//Print the new dir to our file
	fprintf(fptr,"%s",copy);
	fclose(fptr);

	return 0;
}
