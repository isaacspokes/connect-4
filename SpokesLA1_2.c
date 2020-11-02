#include <stdio.h>
/* Here is where I declare all of the functions I'll be using. 
For certain ones I needed them to return values so those are 
int functions, the others are void. They are not really in any 
order, just the order I created them. */
void startgame(char *, int *);
void readgame(char board[], int *);
void newgame(char board[]);
void displayboard(char board[]);
int displaymenu(char board[], int *);
void writegame(char board[]);
void playerturn();
void userinput(char *, int, int *);
int legalmove(char board[], char, int *);
void filetrans();
void domove(char board[], char x, int y, int plyr);
int gamewon(char board[]);
void winner(int);

int main(void){ 
    int check = 0; int i = 0; int over; //initializes the proper integers
    char board[42];						//initializes the board array
    for (int i = 0; i<42; i++){			//sets each space to a space
        board[i]=32;
    }
    
    startgame(board, &i);
    displayboard(board);
    do{
        userinput(board, i, &over);
        check = gamewon(board);
        i++;
    } while((i<42) && (check == 0) && (over != 1));
    if (over != 1){
        winner(i);
    } else{
        printf("The game is a tie, wow!\n");
    }
}
void startgame(char *board, int *i){ //beginning of game
    char let;
    printf("\nCONNECT FOUR \nHello! Enter L to load an old game, N for a new one. \nPlease do not attempt to load a game that has been won.\nEnter here: ");
    //not worth letting them load a finished game. no point
    scanf(" %c", &let);
    if (let == 'l' || let == 'L'){ //l for load game
        readgame(board, &*i);//runs function to read old file
    } else if (let == 'N' || let == 'n'){ //n for new game
        newgame(board); //runs function to create new board
    } else 
    printf("Error, unknown input\n");
}
void readgame(char *board, int *x){ //reads from a previous file
    char c;
    int i=0; int turn = 0;
    FILE *ifile, *ofile; //initiates file statements
    ifile = fopen ("Connect4Save.txt", "r"); //opens it to read
    ofile = fopen("currentgame.txt", "w"); //opens new file and writes to it
    while ((fscanf(ifile, "%c", &c)) != EOF){
        fprintf(ofile, "%c", c);
        if(c == 'R' || c == 'Y'){ //checks for turns made
            turn++;
        }
        if (c == 'R' || c == 'Y' || c == 32){ //any space gets written to array
            board[i] = c;
            i++;
        }
    }
    *x+= turn;
    fclose(ifile);
    fclose(ofile);
}
void newgame(char board[]){ //sets up a brand new board
    FILE *ifile;
    ifile = fopen("NewGame.txt", "w"); //opens new file to write
    fprintf(ifile, " 1 2 3 4 5 6 7 \n");
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[0], board[1], board[2], board[3], board[4], board[5], board[6]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[7], board[8], board[9], board[10], board[11], board[12], board[13]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[14], board[15], board[16], board[17], board[18], board[19], board[20]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[21], board[22], board[23], board[24], board[25], board[26], board[27]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[28], board[29], board[30], board[31], board[32], board[33], board[34]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[35], board[36], board[37], board[38], board[39], board[40], board[41]);
    fclose(ifile);
    filetrans(); //runs function to put it to currentgame
}
void filetrans(){ //transfers from newgame file to currentgame file
    char c;
	FILE *ifile, *ofile;
	ifile = fopen("NewGame.txt", "r");
	ofile = fopen("currentgame.txt", "w");
	while (fscanf(ifile, "%c", &c) != EOF){
        fprintf(ofile, "%c", c);
    }
    //scans from one and prints to the other
}
void displayboard(char board[]){ //change this to just print the array, fuck the files for now
    char c;
    FILE *ifile, *ofile;
    ifile = fopen("currentgame.txt", "w");
    fprintf(ifile, " 1 2 3 4 5 6 7 \n");
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[0], board[1], board[2], board[3], board[4], board[5], board[6]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[7], board[8], board[9], board[10], board[11], board[12], board[13]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[14], board[15], board[16], board[17], board[18], board[19], board[20]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[21], board[22], board[23], board[24], board[25], board[26], board[27]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[28], board[29], board[30], board[31], board[32], board[33], board[34]);
    fprintf(ifile, "|%c|%c|%c|%c|%c|%c|%c|\n", board[35], board[36], board[37], board[38], board[39], board[40], board[41]);
    fclose(ifile);
    ofile = fopen("currentgame.txt", "r");
    while (fscanf(ofile, "%c", &c) != EOF){
        printf("%c", c);
    }
}
int displaymenu(char board[], int *y){ 
	/*menu before each turn to check if user wants to 
	continue playing or quit. */
    int c, save;
    char input;
    printf("To continue, enter 1. To quit, enter 0. ");
    scanf(" %1c", &input);
    c = input - '0';
    if (c == 1){ //game continues to run
        return(0);
    }    
    else if (c == 0){ //check if user wants to save
        printf("Enter 1 to save game, 0 to quit without saving: ");
        scanf("%1d", &save);
            if (save == 1){
                writegame(board); //save file function
                printf("Your game has been saved.");
                *y = 1;
            } else {
                *y = 1;
            }
        return(1);
    } else{
        printf("Invalid input");
        return(0);
    }
}
void writegame(char board[]){
	/* The purpose of this function is to save the current 
	game to a file Connect4Save. It does so by scanning the 
	current game function, which is updated after each turn,
	and printing the scanned characters to the new file. */
    char c;
    
    FILE *ifile, *efile;
    ifile = fopen("Connect4Save.txt", "w"); //opens new file to write
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[0], board[1], board[2], board[3], board[4], board[5], board[6]);
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[7], board[8], board[9], board[10], board[11], board[12], board[13]);
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[14], board[15], board[16], board[17], board[18], board[19], board[20]);
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[21], board[22], board[23], board[24], board[25], board[26], board[27]);
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[28], board[29], board[30], board[31], board[32], board[33], board[34]);
    fprintf(ifile, "%c,%c,%c,%c,%c,%c,%c.\n", board[35], board[36], board[37], board[38], board[39], board[40], board[41]);
    fclose(ifile);
    printf("Game Saved.\n");
    printf("Your saved game is: \n");
    // shows the user what they've saved
    efile = fopen("Connect4Save.txt", "r");
    while (fscanf(efile, "%c", &c) != EOF){
        printf("%c", c);
    }
    fclose(efile);
}
void userinput(char *board, int x, int *y){
	/* This function requests user input while the turn counter
	is less than 43, at which point the game is a tie. It also 
	checks that each move is legal and that the game has not 
	been won. It passes variable to the domove function in 
	order to perform the change to the array. */
    int leg, plyr;
    char m1, m2;
    if (x % 2 == 0){ //Red player
    	printf("\n Red player, enter a column number, or 0 to open the menu: ");
        scanf(" %1c", &m1);
    	leg = legalmove(board, m1, &*y);
    	while (!leg && *y!=1){ //illegal move, asks again
       		printf("Illegal move, pick another column: ");
        	scanf(" %c", &m1);
        	leg=legalmove(board, m1, &*y);
    	}
    	plyr = x+1;
    	domove(board, m1, leg, plyr);
    	displayboard(board);
    }
	else if (x % 2 == 1){ //Yellow player
    	printf("\n Yellow player, enter a column number, or 0 to open the menu: ");
    	scanf(" %1c", &m2);
    	leg = legalmove(board, m2, &*y);
    	while (!leg && *y!=1){ //illegal move, asks again
    	    printf("Illegal move, pick another column: ");
    	    scanf(" %c", &m2);
    	    leg=legalmove(board, m2, &*y);
    	}
    	plyr = x+1;
		domove(board, m2, leg, plyr);
		displayboard(board);
	}
 	x++;
}
void domove(char board[], char x, int y, int plyr){
	/*	this function actually does the move by changing
		the value of the array for the other functions. 
		
		I decided to use a switch because I felt that 
		this was the easiest way to deal with the different
		column values being entered by the user.
		
		It should check each column until there is an open 
		spot and then fill that spot with the correct
		character. Also checks that the move is legal */
	int spot, legal, number;
	int open = 1;
	number = x-'0';
	switch(number){
		case 1:
			spot = 35; //the bottom leftmost number
			do{
				legal = y; //gives legal a value set by legalmove
				if(board[spot] == 32){ //checks if it's a space
					if(plyr%2 == 1)
						board[spot] = 82; //prints capital R
					if(plyr%2 == 0)
						board[spot] = 89; //prints capital Y
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
			//each case after is the same but 1 extra spot
		case 2:
			spot = 36;
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		case 3:
			spot = 37;
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		case 4:
			spot = 38;
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		case 5:
			spot = 39;
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		case 6:
			spot = 40;
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		case 7:
			spot = 41; //the bottom right-most number
			do{
				legal = y;
				if(board[spot] == 32){
					if(plyr%2 == 1)
						board[spot] = 82;
					if(plyr%2 == 0)
						board[spot] = 89;
					open = 0;
				}
				spot -= 7;
			} while(open && legal);
			break;
		default:
		printf("Game has been quit...\n");
	}
}
int legalmove(char board[], char x, int *y){ 
	/*	checks if the move is legal by looking at the
		top column value of each row. If there is a 
		space, the move should return legal. If not
		a space, the move should return illegal */
	int c = x-'0';
	if (c== 0){
	    displaymenu(board, &*y);
	}
    if (c==1 && board[0] == 32){ 
        return(1);
    }else if (c==2 && board[1] == 32){
        return(1);
    }else if (c==3 && board[2] == 32){
        return(1);
    }else if (c==4 && board[3] == 32){
        return(1);
    }else if (c==5 && board[4] == 32){
        return(1);
    }else if (c==6 && board[5] == 32){
        return(1);
    }else if (c==7 && board[6] == 32){
        return(1);
    }else {
        return(0);
    }
}
int gamewon(char board[]){
	int i;
	i=0;
	for(i=0; i<21; i++){
        if((board[i] != 32) && (board[i]==board[i+7]) && (board[i]==board[i+14]) && (board[i]==board[i+21])) {
	    //vertical check, checks that it's not space and equals 4 above it
		return(1);
		} 
	}
	     /* next up is horizontal check. I do one check for the left side of each row
	    	which in turn checks the full row.  This was the easiest logical way I found
	    	that I could get this done  */
	for(i=0; i<42; i++)	{
		if((i%7 < 4)){ //checks left side of array
			if ((board[i] != 32) && (board[i]==board[i+1]) && (board[i]==board[i+2]) && (board[i]==board[i+3])){
				return(1);		
			} 
		}
	}
	for (i=0; i<42; i++){
		if((i%7<4) && (i<18)){ //check upper left corner
			if((board[i] != 32) && (board[i] == board[i+8]) && (board[i] == board[i+16]) && (board[i] == board[i+24])){
				return(1);
			}
		}
		if((i%7<4) && (i>20)){ //check upper left corner
			if((board[i] != 32) && (board[i] == board[i-6]) && (board[i] == board[i-12]) && (board[i] == board[i-18])){
				return(1);
			}
		}
	}
    return (0);
}
void winner(int x){ //congratulates the correct winner
    printf("Congratulations to ");
    if (x % 2 == 1){
        printf("red player.");
    }
    else {
        printf("yellow player.");
    }
}