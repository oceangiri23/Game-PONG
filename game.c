#include <raylib.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void DrawC(float x, float y)                                     //Function to draw ball
{
	DrawCircle(x, y, 10, RED);
}

void DrawR(float x, float y, float w, float h)                  //Function to draw paddle
{
	DrawRectangle(x, y, w, h, WHITE);
}


struct Ball
{
	float x,y;
	float xspd, yspd;                                           //Variables for ball position and speed
}ball;

struct Paddle
{
	float x, y;
	float spd;                                                  //Variables for paddle position and speed
	float width, height;
}leftpd,rightpd;

int main()
{
	int bat=1;
	char name1[30];
	char name2[30];
	char score1[10], score2[10], name[30], namee[30];
	const char* win = " Wins!!!";
	int len, len1, count1 = 0, count2 = 0, index = 10, flag;

	printf("Enter name of Player 1 ->");
	scanf("%s", name1);
	len = strlen(name1);
	strncpy_s(name, len * sizeof(char*), name1, len);
	strncat_s(name, len * sizeof(char*), win, 8);

    printf("Enter name of Player 2 ->");
	scanf("%s", name2);
	len1 = strlen(name2);
	strncpy_s(namee, len1 * sizeof(char*), name2, len1);
	strncat_s(namee, len1 * sizeof(char*), win, 8);

	InitWindow(1600, 1000, "Lét's Pong");							    //Initialize a window
	InitAudioDevice();                                          //Initialize audio device
	SetWindowState(FLAG_VSYNC_HINT);						    //Sets frame rate as that of refresh rate of monitor
	char* winner = NULL;
	ball.x = GetScreenWidth() / 2;
	ball.y = GetScreenHeight() / 2;
	ball.xspd = 250;
	ball.yspd = 250;
	leftpd.x = 40;
	leftpd.y = GetScreenHeight() / 2 - 50;
	leftpd.width = 10;
	leftpd.height = 100;                                              //Initializing the positions and speed
	leftpd.spd = 480;
	rightpd.x = GetScreenWidth() - 50;
	rightpd.y = GetScreenHeight() / 2 - 50;
	rightpd.width = 10;
	rightpd.height = 100;
	rightpd.spd = 480;

	Music music = LoadMusicStream("D:\\project\\gamemusic.mp3");        //Loading music from source
	PlayMusicStream(music);                                         //Playing music

	while (!WindowShouldClose())							        //Loop to run window for infinite time
	{

		UpdateMusicStream(music);                                   // Updates buffers for music streaming
		ball.x += ball.xspd * GetFrameTime();
		ball.y += ball.yspd* GetFrameTime();
		if (ball.y > GetScreenHeight())							    //bouncing the ball from bottom
		{
			ball.y = GetScreenHeight();
			ball.yspd *= -1;
		}

		if (ball.y < 82)									        //bouncing the ball from top
		{
			ball.y = 82;
			ball.yspd *= -1;
		}

		if (leftpd.y <= 82)
			leftpd.y = 82;                                          //Stop paddle from going off the window
		if (rightpd.y <=  82)
			rightpd.y = 82;
		if (leftpd.y >=GetScreenHeight()-100)
			leftpd.y = GetScreenHeight() - 100;                     //Bringing back the paddle if goes up
		if (rightpd.y >= GetScreenHeight() - 100)
			rightpd.y = GetScreenHeight() - 100;

		if (IsKeyDown(KEY_W))                                      //Moving left paddle up with W
		{
			leftpd.y -= leftpd.spd * GetFrameTime();
		}

		if(IsKeyDown(KEY_S))                                      //Moving left paddle down with S
		{
			leftpd.y += leftpd.spd * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))                                    //Moving right paddle up with Up arrow key
		{
			rightpd.y -= rightpd.spd * GetFrameTime();
		}

		if(IsKeyDown(KEY_DOWN))                                  //Moving right paddle down with Down arrow key
		{
			rightpd.y += rightpd.spd * GetFrameTime();
		}


		if (((ball.x) >= (rightpd.x - 6.9) && ball.x < rightpd.x + 3) && ((ball.y) >= (rightpd.y-6) && ball.y <= (rightpd.y + 106)))        //Bouncing off the right paddle
		{
			if (bat==1)
			{
			ball.xspd *= -1.08;
			bat=0;
			}
		}

		if (((ball.x) <= (leftpd.x+16.9) && ball.x >( leftpd.x+3)) && ((ball.y) >= (leftpd.y-6) && ball.y <= leftpd.y + 106))   //Bouncing off the left paddle
		{	
			if (bat==0)
			{
			ball.xspd *= -1.08;
			bat=1;
			}
		}
		if (ball.x < 0)
		{
			flag = 0;
			winner = namee;                                     //Declaring winner if right player wins
		}

		if (ball.x > GetScreenWidth())
		{
			flag = 1;
			winner = name;                                      //Declaring winner if left player wins
			
		}
		
		
		  BeginDrawing();										 // Sets everything ready for drawing
		  ClearBackground(BLACK);	                             //THIS CREATES BLACK BACKGROUND COLOR WINDOW
		  DrawText("SCORE", (GetScreenWidth()/2)-MeasureText("SCORE",80)/2, 0, 80, YELLOW);           //Display score
		  DrawText(name1,70, 30, 40, YELLOW);                                                         //Display player1 name
		  DrawText(name2, GetScreenWidth()-MeasureText(name2,40)-70, 30, 40, YELLOW);                 //Display player2 name
		  DrawLine(0, 82, GetScreenWidth(), 82, DARKGREEN);
		  DrawLine(GetScreenWidth()/2, 80, GetScreenWidth()/2, GetScreenHeight(), DARKGREEN);
		  DrawText(score1, ((GetScreenWidth() / 2) - MeasureText("SCORE", 80) / 2) - 120, 5, 80, YELLOW);
		  DrawText(score2, ((GetScreenWidth() / 2) + MeasureText("SCORE", 80) / 2) + 95, 5, 80, YELLOW);
		  DrawC(ball.x,ball.y);		                                                        //Draws the ball
		  DrawR(leftpd.x, leftpd.y, leftpd.width, leftpd.height);			                //Draws left  paddle
		  DrawR(rightpd.x, rightpd.y, rightpd.width, rightpd.height);			           //Draws right paddle
		  DrawFPS(0, 0);                                                                           //Show frame rate

		  if (winner)
		  {
			  StopMusicStream(music);                                                              //Stop music when game is over
			  DrawText(winner, (GetScreenWidth() / 2) - (MeasureText(winner, 80) / 2), GetScreenHeight() / 2, 80, ORANGE);   //Display winner name
              bat=1;		  
		  }

		  if (winner != NULL && IsKeyPressed(KEY_SPACE))            //Restarting the game using space
		  {
			 PlayMusicStream(music);
			  if (flag)
				  count1++;                                       //Counting score of left player
			  else
				  count2++;                                       //Counting score of right player
			  winner = NULL;
			  ball.x = GetScreenWidth() / 2;
			  ball.y = GetScreenHeight() / 2;	                    //Maling ball position and speed as initial
			  ball.xspd = 250;
			  ball.yspd = 250;
		  }

		  _itoa_s(count1, score1, _countof(score1), index);      //Converting integer score to string score to display
		  _itoa_s(count2, score2, _countof(score2), index);
	    EndDrawing();		 							                                      	//Ends the drawing process
		
	}
	FILE *f;
	f = fopen("D:\\project\\score.txt", "a");
	fprintf(f, " %s \t\t\t\t %s \t\t\t %s \t\t\t   %s \n", name1, score1, name2, score2);
	fclose(f);
	UnloadMusicStream(music);                                     //Unload the music 
	CloseAudioDevice();                                           //Close the audio device
	CloseWindow();                                                //Close the window
	return 0;
}
