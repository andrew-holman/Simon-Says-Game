
/*         Andrew Holman
        aholman@iastate.edu 
        CPRE 185 Section E  
Programming Practice 04
         <Reflection 1 What were you trying to learn or achieve?>
				I was trying to work with 2d arrays to create a game. Also create an external file to hold the highscore table.
        <Reflection 2 Were you successful? Why or Why not?>
				I was successful, the game works as intended without any bugs.
<Reflection 3 Would you do anything differently if starting this program over?  If so, explain what.>
				If I were to start this over I probably would have just made functions that manually
				filled the shapes because the program allows them to be different sizes in different locations
				with different characters but, except for the square, the shapes are only used in one place with one character
				at one size even though that was a big time consumer.
<Reflection 4 Think about the most important thing you learned when writing this piece of code.  What was it and explain why it was significant.>
				I learned how to make things work even if I don't understand how or why. Initially the width and height were different, but after
				first iteration of the program, the board would get messed up and all my variables would get overidden. So just messed around with the
				different variables and eventually I found having height and width the same made it work. So I just kept it and didn't question it.
				And I never had another problem with it. Also I learned how to work on external files by creating the highscore table.
<Other questions/comments for Instructors>
				So, before I fixed the width and height I would print the board but there would be random characters in the image. I remember there was
				an "@" and "!" even though I don't have those characters in my code. Also I created a char variable to see if the program was overidding
				all my variables, it did overide it but then my program would print that character in my board. So, is there like a simple explaination for that?
				I just assumed one of my arrays was going over its bound and taking values from other variable's addresses but I don't know.
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 40

//Prototypes for the later methods.
void fillBoard(char board[HEIGHT][WIDTH]);
void printBoard(char board[HEIGHT][WIDTH]);
void fillTriangle(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY);
void fillX(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY);
void fillCircle(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY);
void fillSquare(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY);
void resetBoard(char board[HEIGHT][WIDTH]);
void circleTriangle(char board[HEIGHT][WIDTH]);
void circleX(char board[HEIGHT][WIDTH]);
void circleCircle(char board[HEIGHT][WIDTH]);
void circleSquare(char board[HEIGHT][WIDTH]);
void readInHighScores(char scores[100]);
void printHighScores(char scores[100]);
void changeFile(char scores[100], int score, char name[4]);
int onHighScores(char scores[100], int score);

int  main() {
	//Initialized variables
	char board[HEIGHT][WIDTH]; //Board that contains the characters that print out.
	int triangle, circle, x, square; //Used for DS4 inputs
	int turn = 0; //Counts the number of turns the user has done.
	int score = 0; //Keeps track of the number of correct guesses the user makes.
	char game; //Determines if user does the demo or the game. 
	char key[40]; //Array that can hold up to 39 directions for the game.
	char guess[40]; //Array that can hold up to 39 guesses for hte game.
	srand(time(NULL)); //Generates a random number later.
	int i;
	char highScore[100];
	char inputName[4];
	
	printf("Welcome to the Simon Says game. To demo the functionality\n");
	printf("of the game press \"d\". To start the game press \"g\".\n");
	printf("In the game various shapes will appear with a circle around it\n");
	printf("You must remember the shapes that are circled and repeat the order\n");
	printf("Use w for up, s for down, d for right, a for left\n");

	printf("\n");
	readInHighScores(highScore);
	//changeFile(highScore, 20, "CBA");
	printHighScores(highScore);

	printf("\n");
	//Fills the board with spaces and the base shapes.
	resetBoard(board);
	
	printf("What would you like to do?\n\"g\" for a game\n\"d\" for a demo\n");
	scanf(" %c", &game);
	
	while(1){
		sleep(1);
		turn++;
		//Demos the movement of the square in an infinite loop.
		if (game == 'd'){
			if(turn%4 == 0){ //Around the Square.
				circleSquare(board);
			}
			else if(turn%4 == 1){ //Around the Triangle.
				circleTriangle(board);
			}
			else if(turn%4 ==2){ //Around the Circle.
				circleCircle(board);
			}
			else if(turn%4 ==3){ //Around the X.
				circleX(board);
			}
			printBoard(board);
			printf("Turn: %d\n", turn);
			resetBoard(board);
			
		}
		//The actual game.
		else if(game == 'g'){
			
			printf("3...\n");
			sleep(1);
			printf("2...\n");
			sleep(1);
			printf("1...\n");
			sleep(1);
			//Loop that creates a key for the player.
			for(i=0; i < turn; i++){
				int r = rand()%4;
				if(r==0){
					circleSquare(board);
					key[i] = 'a';
				}
				else if(r==1){
					circleTriangle(board);
					key[i] = 'w';
				}
				else if(r==2){
					circleCircle(board);
					key[i] = 'd';
				}
				else if(r==3){
					circleX(board);
					key[i] = 's';
				}
				//prints the updated board
				printBoard(board);
				printf("\n\n\n\n\n\n");
				sleep(1);
				//prints a blank board
				resetBoard(board);
				printBoard(board);
				printf("\n\n\n\n\n\n");
				sleep(1);
				
			}
			printf("Turn: %d\nScore: %d\n", turn, score);
			printf("Okay, what did Simon say?(Use w,a,s,d)\n");
			//User guesses the pattern.
			for(i = 0; i<turn; i++){
				printf("%d time: ", i+1);
				scanf(" %c", &guess[i]);

				//If their guess doesn't match up with the key the game ends.
				if(key[i] != guess[i]){
					printf("Nope the correct answer was %c.\n", key[i]);
					printf("Sorry, you lose, at least you got to turn %d.\n", turn);
					printf("Your final score was %d. Try again and get even higher!\n", score);
					if(onHighScores(highScore, score)){
						printf("Congratulation, you made it on the highscore table\n");
						printf("Please enter your name (Only 3 captial letters):\n");
						scanf(" %c%c%c", &inputName[0], &inputName[1], &inputName[2]);
						printf("\n\n");
						changeFile(highScore, score, inputName);
						printHighScores(highScore);
					}
					return 0;
				}
				score++;
				printf("Score: %d\n", score);
				printf("\n");

				
			}
			printf("Good job, get ready for the next round.\n");
			

		}
		//Condition if the user does not either d or g.
		else{
			printf("Invalid input");
			return 0;
		}
			
			
		
	}
	
	
	
}
//Fills board with spaces
void fillBoard(char board[HEIGHT][WIDTH]){
	int i,j;
	
	for(i=0; i < HEIGHT; i++){
		for(j=0; j < WIDTH; j++){
			board[i][j] = ' ';
		}
	}
}
//Prints the characters of the board	
void printBoard(char board[HEIGHT][WIDTH]){
	int i,j;
	
	for(i=0; i < HEIGHT; i++){
		for(j=0; j < WIDTH; j++){
			printf("%c", board[j][i]);
		}
		printf("\n");
	}
}
//Puts a triangle in the board.
void fillTriangle(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY){
	int i, j, k;
	
	
	for(i=0; i < height; i++){
		for(j=0; j < height-i; j++){
			
		}
		for(k=0; k < i*2+1; k++){
			board[j+k+1+ moveX][i + moveY] = character;
		}
	}
}
//Puts an "X" in the board.
void fillX(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY){
	int i=0;
	int j=0;	
	
	for(i=0; i < height+1; i++){
		board[i+moveX+4][i+moveY] = character;
	}
	for(j=0; j < height+1; j++){
		board[j+moveX+4][height-j+moveY] = character;
	}

}
//Puts a circle in the board.
void fillCircle(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY){
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	
	
	for(j=0; j < (height+1)/2; j++){
		board[j+moveX+4][height-j+moveY] = character;
	}
	for(i=0; i< (height+1)/2; i++){
		board[i + moveX][height -i -height/2 +moveY] = character;
	}
	
	for(k=0; k < (height+1)/2; k++){
		board[k+moveX+4][k+moveY+1] = character;
	}
	for(k=0; k < (height+1)/2; k++){
		board[k+moveX+4-height/2][k+moveY+1+height/2] = character;
	}
	
}

//Puts a circle in the board
void fillSquare(char board[HEIGHT][WIDTH], int height, char character, int moveX, int moveY){
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	
	for(i=0; i < height; i++){
		board[i+moveX][moveY] = character;
	}
	for(j=0; j < height; j++){
		board[moveX][j+moveY] = character;
	}
	for(i=0; i < height+1; i++){
		board[i+moveX][height+moveY] = character;
	}
	for(j=0; j < height; j++){
		board[moveX+ height][j+moveY] = character;
	}

}

//Fills the board with spaces then puts in each shape at the correct location	
void resetBoard(char board[HEIGHT][WIDTH]){
	fillBoard(board);
 	fillTriangle(board, 6, '^', 15,3);
	fillX(board, 6, 'X', 15, 20);
	fillCircle(board, 8, 'O', 29, 10);
	fillSquare(board, 6, 'H', 6, 12); 
}
//Prints a square of periods around the triangle.
void circleTriangle(char board[HEIGHT][WIDTH]){
	fillSquare(board, 12, '.', 16, 0);
}
//Puts a square of periods around the "X".
void circleX(char board[HEIGHT][WIDTH]){
	fillSquare(board, 10, '.', 17, 18);
}
//Puts a square of periods around the circle.
void circleCircle(char board[HEIGHT][WIDTH]){
	fillSquare(board, 10, '.', 27, 9);
}
//Puts a square of periods around the square.
void circleSquare(char board[HEIGHT][WIDTH]){
	fillSquare(board, 10, '.', 4, 10);
}
//Creates an array of characters from the text file
void readInHighScores(char scores[100]){
	int i;
	FILE * fp;
	fp=fopen("testFile.txt", "r+"); //Opens file
	rewind(fp); //Starts scanning at the beginning of file
	
	//Reads the values into the array
	for(i=0; i< 100; i++){
		scores[i] = fgetc(fp);
	}
	fclose(fp); //Closes the file
}
//Prints out the highscore table
void printHighScores(char scores[100]){
	int rank =1;
	int i;
	
	//Print statement for the table
	printf("Highscore Table:\n");
	printf("Rank Score  Name\n %d   ", rank);

	for(i=0; i<100; i++){
		if(scores[i] == '-'){
			rank++;
			printf("\n %d   ", rank);
		}
		//Ends if it hits a '}' which the end of the text file is filled with
		else if(scores[i] == '}'){
			break; 
		}
		else{
			printf(" %c", scores[i]);
		}
	}	
}
//Given a score and name, it alters the array and text file.
void changeFile(char scores[100], int score, char name[4]){
	int i;
	FILE * fp;
	fp=fopen("testFile.txt", "r+");
	rewind(fp);
	int tmpTens;
	int tmpOnes;
	char charTens;
	char charOnes;
	char tmpStr[4];
	char name1[4] = {name[0],name[1],name[2]};
	
	for(i=0; i<100; i++){
		//Every 7th value is the first digit in the score.
		if(i%7 == 0){
			tmpTens = scores[i];
			tmpOnes = scores[i+1];
			charTens = score/10 +48; //Converts the int to a character
			charOnes = score%10 +48; //Converts the int to a character
			//Changes values in the array if it is larger than the highscore table
			if(tmpTens -48 < score/10 || (tmpTens -48 == score/10 && tmpOnes -48 < score%10)){
				scores[i] = charTens;
				scores[i+1] = charOnes;
				
				tmpStr[0] = scores[i+3];
				tmpStr[1] = scores[i+4];
				tmpStr[2] = scores[i+5];
				
				scores[i+3] = name1[0];
				scores[i+4] = name1[1];
				scores[i+5] = name1[2];
				
				score = (tmpTens -48) *10 + (tmpOnes -48);
				name1[0] = tmpStr[0];
				name1[1] = tmpStr[1];
				name1[2] = tmpStr[2];
			}
		}
	else if(scores[i] == '}'){
			break;
		}
	}
	for(i=0; i<100; i++){
		fprintf(fp, "%c", scores[i]);
	}
	fclose(fp);
}
//Returns true if the score should be on the highscore table and false if it isn't
int onHighScores(char scores[100], int score){
	int i;
	int tmpTens = scores[56] -48;
	int tmpOnes = scores[57] -48;
	if(score/10 > tmpTens || (score/10 == tmpTens && score%10 > tmpOnes)){
		return 1;
	}
	else{
		return 0;
	}
	
}

	