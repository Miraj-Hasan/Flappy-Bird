/*
	author: Md. Miraj Hasan(2005084)
            Moyen Uddin(2005075)
	last modified: April 11,2022
*/


#include <stdio.h>
# include "iGraphics.h"
# include "gl.h"

int bird_image_height=65,bird_width=70,bird_height=0.9375*bird_image_height,height_above_ground=525;
int bird_x_position= 24, bird_y_position=300,i=0,h=175,x_pos=100;
int is_dead=0,hasgamepaused=0,resume_counter=-1;
float v=0,t=0;
char scra[1000],scrb[1000],scrc[1000],SCORE1[50],SCORE2[50],SCORE3[50];
int slicex[100];
void draw_lower_column(int,int);
void draw_upper_column(int,int);
int page=0,score=0, high_score_easy, high_score_medium, high_score_hard,lives=3,t1=-1,t2=0,wing_position,times, sound = 1;
int pillar_velocity=4,game_level=1,separation=200;
FILE *fp,*fp1;

struct pillar
{
    int x_position,height;
} pillar1,pillar2,pillar3,pillar4,pillar5,pillar6;


//drawtext is used to write any texts in a specific font

void drawtext(char text[],int bottom_x,int bottom_y)
{

    int i,j;
    char letterwidth[26];
    for(i=0; i<26; i++)
    {
        letterwidth[i]=28;
    }

    //different letterwidths are used due to difference of image width

    letterwidth[5]=22;
    letterwidth[8]=10;
    letterwidth[9]=22;
    letterwidth[14]=32;
    letterwidth[13]=32;
    letterwidth[12]=32;
    letterwidth[22]=40;
    char file_name[]="image/letters/A.bmp";

    for(i=0; i<strlen(text); i++)
    {
        //In the string filename the 14th character is changed to get image of different letters

        file_name[14]=text[i];

        for(j=0; j<26; j++)
        {
            //this loop is used to find the letters or digits
            if(text[i]=='a'+j || text[i]=='A'+j)
            {
                iShowBMP2(bottom_x,bottom_y,file_name,0);
                bottom_x=bottom_x+letterwidth[j];
                break;
            }
            if(text[i]=='0'+j)
            {
                iShowBMP2(bottom_x,bottom_y-5,file_name,0);
                bottom_x=bottom_x+25;
                break;
            }
        }
        if(text[i]==' ')
            bottom_x=bottom_x+15;
    }
}

void startnewgame()
{

    page = 1;
    bird_y_position=300;
    pillar1.x_position=600,pillar2.x_position=600,pillar3.x_position=1000,pillar4.x_position=1000,pillar5.x_position=1400,pillar6.x_position=1400;
    pillar1.height=75+rand()%200,pillar2.height=height_above_ground-separation-pillar1.height,pillar3.height=75+rand()%200;
    pillar4.height=height_above_ground-separation-pillar3.height,pillar5.height=75+rand()%200,pillar6.height=height_above_ground-separation-pillar5.height;
    v=0,t=0,t1=-1;
    score=0,lives=3,is_dead=0,hasgamepaused=0;
    iResumeTimer(0);
    iResumeTimer(1);
    times = 1;

}


/*
	function iDraw() is called again and again by the system.
*/

void iDraw()
{

    iClear();

//this is the home page
    if(page == 0)
    {

        iShowBMP(0, 0, "image/back_menu.bmp");

        iSetColor(255,255,255);
        iFilledRectangle(490,340,220,80);
        iFilledRectangle(490,250,220,80);
        iFilledRectangle(490,160,220,80);
        iFilledRectangle(490,70,220,80);

        iSetColor(0, 128, 128);
        iFilledRectangle(500,350,200,60);
        iFilledRectangle(500,260,200,60);
        iFilledRectangle(500,170,200,60);
        iFilledRectangle(500,80,200,60);

        iSetColor(255,255,255);
        iText(562, 372, "START", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(525, 282, "HIGH SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(550, 192, "OPTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(570, 102, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);


        iShowBMP2(391, 465, "image/gamename.bmp",0);
        iShowBMP2(200, 370, "image/bird.bmp",0);
        iShowBMP2(920, 370, "image/dead bird1.bmp",0);

        iSetColor(255,255,255);
        iFilledRectangle(1010,25,170,60);
        iSetColor(220,20,60);
        iFilledRectangle(1015,30,160,50);
        iSetColor(255,255,255);
        iText(1025, 49, "INSTRUCTIONS", GLUT_BITMAP_HELVETICA_18);
    }





//this is the main game page
    if(page == 1)
    {

        iShowBMP(0, 75, "image/background.bmp");

        for(i=0; i<=30; i++)
        {
            iShowBMP(slicex[i], 0, "image/ground slice.bmp");
        }

        if(pillar1.x_position < -50)
        {
            pillar1.x_position = 1200;
            pillar1.height=75+rand()%200,pillar2.height=height_above_ground-separation-pillar1.height;
        }
        if(pillar3.x_position < -50)
        {
            pillar3.x_position = 1200;
            pillar3.height=75+rand()%200,pillar4.height=height_above_ground-separation-pillar3.height;
        }
        if(pillar5.x_position < -50)
        {
            pillar5.x_position = 1200;
            pillar5.height=75+rand()%200,pillar6.height=height_above_ground-separation-pillar5.height;
        }





//when the bird is alive
        if(is_dead==0)

        {
            if(bird_y_position==75)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird.bmp",0);
            else if(wing_position==1)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 1.bmp",0);
            else if(wing_position==2)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 2,9.bmp",0);
            else if(wing_position==3)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 3,8.bmp",0);
            else if(wing_position==4)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 4.bmp",0);
            else if(wing_position==5)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 5,7.bmp",0);
            else if(wing_position==6)
                iShowBMP2(bird_x_position, bird_y_position-16, "image/bird_animation/animation 6.bmp",0);
            else if(wing_position==7)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 5,7.bmp",0);
            else if(wing_position==8)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 3,8.bmp",0);
            else if(wing_position==9)
                iShowBMP2(bird_x_position, bird_y_position, "image/bird_animation/animation 2,9.bmp",0);

        }

//when the bird is dead
        else
            iShowBMP2(bird_x_position, bird_y_position, "image/dead bird1.bmp",0);




//drawing the pillars

        draw_upper_column(pillar1.x_position,pillar1.height);
        draw_lower_column(pillar1.x_position,pillar2.height);
        draw_upper_column(pillar3.x_position,pillar3.height);
        draw_lower_column(pillar3.x_position,pillar4.height);
        draw_upper_column(pillar5.x_position,pillar5.height);
        draw_lower_column(pillar5.x_position,pillar6.height);



//for showing number of lives

        for(i=0; i<lives; i++)
        {

            iShowBMP2(950+45*i, 560, "image/life.bmp",0);
        }


// showing the scores  continuously

        if(is_dead==0 || is_dead==2)
        {

            iSetColor(0, 0, 0);
            sprintf(scra, "Score %d",score);
            iText(1100, 560, scra, GLUT_BITMAP_TIMES_ROMAN_24);
        }


//when game is over

        if(is_dead==1)
        {

            iSetColor(0, 0, 0);
            iShowBMP2(302, 30, "image/game_over_back.bmp",0xFFFFFF);
            iShowBMP2(370, 400, "image/game_over1.bmp",0);

            sprintf(scrb, "Your Score %d",score);
            drawtext(scrb,430,320);



//to compare the score with highscore

            if(game_level == 1)
            {
                if(score>=high_score_easy)
                {
                    sprintf(scrb, "High Score %d",score);
                    drawtext(scrb,430,240);
                }

                else
                {
                    sprintf(scrb, "High Score %d",high_score_easy);
                    drawtext(scrb,430,240);
                }

            }

            else if(game_level == 2)
            {
                if(score>=high_score_medium)
                {
                    sprintf(scrb, "High Score %d",score);
                    drawtext(scrb,430,240);
                }

                else
                {
                    sprintf(scrb, "High Score %d",high_score_medium);
                    drawtext(scrb,430,240);
                }

            }

            else if(game_level == 3)
            {
                if(score>=high_score_hard)
                {
                    sprintf(scrb, "High Score %d",score);
                    drawtext(scrb,430,240);
                }

                else
                {
                    sprintf(scrb, "High Score %d",high_score_hard);
                    drawtext(scrb,430,240);
                }

            }


            iShowBMP(445, 160, "image/button.bmp");
            drawtext("RESTART",500, 165);

            iShowBMP(445, 80, "image/button.bmp");
            drawtext("Main menu",470,85);

        }



//when lives reduce
        if(is_dead==2 && hasgamepaused==0)
        {

            sprintf(scrc, "Game will restart in%d seconds",t1);
            drawtext(scrc,240, 350);
        }


//when game is resumed
        if(hasgamepaused==1)
        {

            sprintf(scrc, "Game will restart in%d seconds",resume_counter);
            drawtext(scrc,240, 350);
        }


        iSetColor(0,0,0);
        iText(20,565, "Press  'P'  to  pause", GLUT_BITMAP_TIMES_ROMAN_24);

    }




//this is the highscore page

    if(page == 2)
    {
        iShowBMP(0, 0,"image/High_score.bmp");


//times is used so that idraw can compare score with high score only once
        while(times == 1)
        {
            if(game_level == 1)
            {
                if(score>=high_score_easy)
                    high_score_easy = score;
            }

            if(game_level == 2)
            {
                if(score>=high_score_medium)
                    high_score_medium = score;
            }

            if(game_level == 3)
            {
                if(score>=high_score_hard)
                    high_score_hard = score;
            }

//FILE is used to store highscores
            FILE *fp2;
            fp2 = fopen("data/High_score.txt","w");
            fprintf(fp2,"%d %d %d", high_score_easy,  high_score_medium,  high_score_hard);
            fclose(fp2);
            times--;

        }


        drawtext(" HIGH SCORES",150,430);
        iSetColor(255,255,255);
        sprintf(SCORE1,"EASY      %d",high_score_easy);
        drawtext(SCORE1,150,350);
        sprintf(SCORE2,"MEDIUM   %d",high_score_medium);
        drawtext(SCORE2,150,270);
        sprintf(SCORE3,"HARD      %d",high_score_hard);
        drawtext(SCORE3,150,190);

        iText(20,20, "Press 'M' to return to main menu", GLUT_BITMAP_TIMES_ROMAN_24);
    }



//this is the options page
    if(page == 3)
    {
        iShowBMP(0, 0,"image/back_options.bmp");

        iSetColor(255,255,255);
        iFilledRectangle(470,250,220,80);
        iSetColor(255, 0,0);
        iFilledRectangle(480,260,200,60);

        iSetColor(255,255,255);
        iText(538,282, "SOUND", GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(255,255,255);
        iFilledRectangle(710,250,220,80);

        if(sound == 1)
        {
            iSetColor(50,205,50);
            iFilledRectangle(720,260,95,60);
            iSetColor(255,255,255);
            iText(750, 282, "ON", GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(178,190,181);
            iFilledRectangle(825,260,95,60);
            iSetColor(255,255,255);
            iText(855, 282, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);
        }

        if(sound == 0)
        {
            iSetColor(178,190,181);
            iFilledRectangle(720,260,95,60);
            iSetColor(255,255,255);
            iText(750, 282, "ON", GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(50,205,50);
            iFilledRectangle(825,260,95,60);
            iSetColor(255,255,255);
            iText(855, 282, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(hasgamepaused==0)
        {
            iSetColor(255,255,255);
            iFilledRectangle(470,160,220,80);
            iSetColor(255, 0,0);
            iFilledRectangle(480,170,200,60);

            iSetColor(255,255,255);
            iText(538,192, "LEVEL", GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(255,255,255);
            iFilledRectangle(710,160,330,80);

            if(game_level == 1)
            {
                iSetColor(50,205,50);
                iFilledRectangle(720,170,95,60);
                iSetColor(255,255,255);
                iText(740, 192, "EASY", GLUT_BITMAP_HELVETICA_18);

                iSetColor(178,190,181);
                iFilledRectangle(825,170,95,60);
                iSetColor(255,255,255);
                iText(835, 192, "MEDIUM", GLUT_BITMAP_HELVETICA_18);

                iSetColor(178,190,181);
                iFilledRectangle(930,170,95,60);
                iSetColor(255,255,255);
                iText(955, 192, "HARD", GLUT_BITMAP_HELVETICA_18);

            }

            if(game_level == 2)
            {
                iSetColor(178,190,181);

                iFilledRectangle(720,170,95,60);
                iSetColor(255,255,255);
                iText(740, 192, "EASY", GLUT_BITMAP_HELVETICA_18);

                iSetColor(50,205,50);
                iFilledRectangle(825,170,95,60);
                iSetColor(255,255,255);
                iText(835, 192, "MEDIUM", GLUT_BITMAP_HELVETICA_18);

                iSetColor(178,190,181);
                iFilledRectangle(930,170,95,60);
                iSetColor(255,255,255);
                iText(955, 192, "HARD", GLUT_BITMAP_HELVETICA_18);
            }

            if(game_level == 3)
            {
                iSetColor(178,190,181);
                iFilledRectangle(720,170,95,60);
                iSetColor(255,255,255);
                iText(740, 192, "EASY", GLUT_BITMAP_HELVETICA_18);

                iSetColor(178,190,181);
                iFilledRectangle(825,170,95,60);
                iSetColor(255,255,255);
                iText(835, 192, "MEDIUM", GLUT_BITMAP_HELVETICA_18);

                iSetColor(50,205,50);
                iFilledRectangle(930,170,95,60);
                iSetColor(255,255,255);
                iText(955, 192, "HARD", GLUT_BITMAP_HELVETICA_18);
            }

        }


        iSetColor(255,0,0);
        iText(840,20, "Press 'M' to return to main menu", GLUT_BITMAP_TIMES_ROMAN_24);

    }




//this is the pause page while the game
    if(page==4)
    {
        iShowBMP(0, 0, "image/pauseback.bmp");

        iShowBMP2(270, 400, "image/GAME PAUSE MENU.bmp",0);

        iShowBMP(445, 320, "image/button.bmp");
        iShowBMP2(510, 325, "image/RESUME.bmp",0);

        iShowBMP(445, 240, "image/button.bmp");
        iShowBMP2(500, 245, "image/RESTART.bmp",0);

        iShowBMP(445, 160, "image/button.bmp");
        iShowBMP2(500, 165, "image/OPTION.bmp",0);

        iShowBMP(445, 80, "image/button.bmp");
        iShowBMP2(550, 85, "image/EXIT1.bmp",0);
    }



//this is the instruction page
    if(page == 5)
    {
        iShowBMP(0, 0, "image/Instructions.bmp");
        FILE *ins;
        int p=0;
        char line[150];
        ins = fopen("data/instructions.txt", "r");
        iSetColor(255,0,0);
        iText(515, 470, "INSTRUCTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
        iLine(500,460,710,460);
        iLine(500,455,710,455);
        while(fgets(line,sizeof(line),ins))
        {
            iSetColor(0,0,0);

            sprintf(line,"%s",line);
            iText(425, 408-p, line, GLUT_BITMAP_TIMES_ROMAN_24);
            p += 40;
        }
        fclose(ins);
        iSetColor(0,0,255);
        iText(855,15, "Press 'M' to return to main menu", GLUT_BITMAP_TIMES_ROMAN_24);

    }




}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}



/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{


    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if(page == 0)
        {

            if(mx >= 500 && mx <= 700 && my >= 350 && my <= 410 )
            {
                startnewgame();
            }

            else if(mx >= 500 && mx <= 700 && my >= 170 && my <= 230)
                page = 3;

            else if(mx >= 500 && mx <= 700 && my >= 260 && my <= 320)
                page = 2;

            else if(mx >= 500 && mx <= 700 && my >= 80 && my <= 140)
                exit(0);
            else if(mx >= 1015 && mx <= 1175 && my >= 30 && my <= 80)
                page = 5;


        }


        if(is_dead==0 && page == 1)
        {
            if(sound == 1)
                PlaySound("sound/Birdfly.wav",NULL,SND_ASYNC);
            v=70;
            t=0;
        }



        if(page == 3)
        {

            if(mx >= 720 && mx <= 815 && my >= 260 && my <= 320 )
            {
                sound = 1;

            }

            if(mx >= 825 && mx <= 920 && my >= 260 && my <= 320 )
            {
                sound = 0;
            }



//for changing game level only before starting the game
            if(hasgamepaused==0)
            {

                if(mx >= 720 && mx <= 815 && my >= 170 && my <= 230 )
                {
                    game_level=1;
                    separation=200;
                    pillar_velocity=4;
                }

                if(mx >= 825 && mx <= 920 && my >= 170 && my <= 230 )
                {
                    game_level = 2;
                    separation=200;
                    pillar_velocity=8;
                }

                if(mx >= 930 && mx <= 1025 && my >= 170 && my <= 230 )
                {
                    game_level = 3;
                    separation=170;
                    pillar_velocity=8;
                }

            }


        }





        if(page == 4)
        {


            if(mx >= 445 && mx <= 755 && my >= 320 && my <= 380)
            {
                page=1;
                resume_counter=3;
            }
            if(mx >= 445 && mx <= 755 && my >= 240 && my <= 300 )
            {
                startnewgame();
            }

            if(mx >= 445 && mx <= 755 && my >= 160 && my <= 220)
                page = 3;

            if(mx >= 445 && mx <= 755 && my >= 80 && my <= 140)
               {
                    page = 0;
                    hasgamepaused=0;
               }


        }



        if(page==1 && is_dead==1)
        {
            if(mx >= 445 && mx <= 755 && my >= 160 && my <= 220)
            {
                startnewgame();
            }
            if(mx >= 445 && mx <= 755 && my >= 80 && my <= 140)
            {
                page=0;
            }


        }


    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    if(key == 'p' || key == 'P')
    {

        if(is_dead!=1)
        {
            hasgamepaused=1;
            iPauseTimer(0);
            iPauseTimer(1);
            page=4;
        }

    }



    if(key == 'm' || key == 'M')
    {
        if(page==2 || page==5)
            page=0;

        else if(page==3 && hasgamepaused==0)
            page=0;

        else if(page==3 && hasgamepaused==1)
            page=4;


    }


}





void iSpecialKeyboard(unsigned char key)
{


    if(key == GLUT_KEY_UP)
    {
        if(is_dead==0 && page==1)
        {
            if(sound == 1)
                PlaySound("sound/Birdfly.wav",NULL,SND_ASYNC);

            v=70;
            t=0;
        }
    }

}



// for flying the bird
void birds_y_position_change()
{
    if(page == 1)
    {

        t += 0.01;
        if(is_dead==0)
        {

            bird_y_position += v*t;
            v -= 25*t;
            if(v<-20)
            {
                v=-20;
            }
            if(bird_y_position>600)
            {
                bird_y_position=600;
                v=0;
            }
        }


        if(is_dead==1 || is_dead==2)
        {
            bird_y_position += -30*t;
        }

        if(bird_y_position<75)
        {
            bird_y_position=75 ;
        }


//for counting the score
        if((pillar1.x_position==bird_x_position|| pillar3.x_position==bird_x_position|| pillar5.x_position==bird_x_position) &&(is_dead==0) )
        {
            if(sound == 1)
                PlaySound("sound/score.wav",NULL,SND_ASYNC);

            score++;
        }
    }

}

void pillar_x_position_change()
{

//conditions for game over
    if(page == 1)
    {


        if(bird_x_position<= pillar1.x_position+50 && bird_x_position>= pillar1.x_position-bird_width)
        {
            if((bird_y_position >= 75 && bird_y_position <= 75+pillar2.height ) || (bird_y_position >= 75+pillar2.height+separation-bird_height && bird_y_position <= 600 ) )
            {


                if(sound == 1)
                {
                    PlaySound("sound/game over 2.wav",NULL,SND_ASYNC);
                    PlaySound("sound/game over 1.wav",NULL,SND_ASYNC);
                }
                lives--;

                if(lives==0)
                {
                    is_dead=1;
                    iPauseTimer(1);
                }
                else
                {
                    is_dead=2;
                    t1=3;
                    iPauseTimer(1);

                }
            }
        }

        if(bird_x_position<= pillar3.x_position+50 && bird_x_position>= pillar3.x_position-bird_width)
        {
            if((bird_y_position >= 75 && bird_y_position<= 75+pillar4.height ) || (bird_y_position >= 75+pillar4.height+separation-bird_height && bird_y_position <= 600 ) )
            {

                if(sound == 1)
                {
                    PlaySound("sound/game over 2.wav",NULL,SND_ASYNC);
                    PlaySound("sound/game over 1.wav",NULL,SND_ASYNC);
                }

                lives--;

                if(lives==0)
                {
                    is_dead=1;
                    iPauseTimer(1);
                }
                else
                {
                    is_dead=2;
                    t1=3;
                    iPauseTimer(1);
                }
            }
        }
        if(bird_x_position<= pillar5.x_position+50 && bird_x_position>= pillar5.x_position-bird_width)
        {
            if((bird_y_position >= 75 && bird_y_position <= 75+pillar6.height ) || (bird_y_position >= 75+pillar6.height+separation-bird_height && bird_y_position <= 600 ) )
            {
                if(sound == 1)
                {
                    PlaySound("sound/game over 2.wav",NULL,SND_ASYNC);
                    PlaySound("sound/game over 1.wav",NULL,SND_ASYNC);
                }

                lives--;

                if(lives==0)
                {
                    is_dead=1;
                    iPauseTimer(1);
                }
                else
                {
                    is_dead=2;
                    t1=3;
                    iPauseTimer(1);


                }
            }
        }


        pillar1.x_position -= pillar_velocity;
        pillar3.x_position -= pillar_velocity;
        pillar5.x_position -= pillar_velocity;



        for(i=0; i<=30; i++)
        {
            slicex[i] -= pillar_velocity;
            if(slicex[i]<=-40)
            {
                slicex[i]=1200;
            }
        }



    }
}



void counter()
{
    t1--;
    if(t1==0)
    {
        bird_y_position=300;
        pillar1.x_position = 600, pillar3.x_position = 1000, pillar5.x_position = 1400,is_dead=0;
        pillar1.height=75+rand()%200,pillar2.height=height_above_ground-separation-pillar1.height,pillar3.height=75+rand()%200;
        pillar4.height=height_above_ground-separation-pillar3.height,pillar5.height=75+rand()%200,pillar6.height=height_above_ground-separation-pillar5.height;
        v=0,t=0;
        if(hasgamepaused==0)
            iResumeTimer(1);
    }


    resume_counter--;
    if(resume_counter==0)
    {
        hasgamepaused=0;
        iResumeTimer(0);
        iResumeTimer(1);
    }

}


//for the animation of the wings
void counter1()
{
    t2++;
    wing_position=t2%9+1;
}



//for drawing the lower collumns
void draw_lower_column(int x_pos,int h)
{
    iSetColor(229,57,53);
    iFilledRectangle(x_pos,75,50,h);
    iSetColor(229,57,53);
    iFilledRectangle(x_pos-6,75+h-12,62,12);
    iSetColor(211,47,47);
    iFilledRectangle(x_pos+10,75,40,h-2);
    iSetColor(198,40,40);
    iFilledRectangle(x_pos+20,75,30,h-2);
    iSetColor(183,28,28);
    iFilledRectangle(x_pos+30,75,20,h-2);
    iSetColor(255,255,255);
    iFilledRectangle(x_pos+40,75,2,h-2);
    iSetColor(227,120,120);
    iFilledRectangle(x_pos+42,75,2,h-2);
    iSetColor(242,198,198);
    iFilledRectangle(x_pos+44,75,2,h-2);
    iSetColor(242,213,213);
    iFilledRectangle(x_pos+46,75,2,h-2);

    iSetColor(255,255,255);
    iFilledRectangle(x_pos+40,75+h-4,8,2);

    iSetColor(227,120,120);
    iFilledRectangle(x_pos+42,75+h-6,8,2);
    iSetColor(227,120,120);
    iFilledRectangle(x_pos+48,75+h-6,2,4);

    iSetColor(242,198,198);
    iFilledRectangle(x_pos+44,75+h-8,8,2);
    iSetColor(242,198,198);
    iFilledRectangle(x_pos+50,75+h-8,2,6);

    iSetColor(242,213,213);
    iFilledRectangle(x_pos+46,75+h-10,8,2);
    iSetColor(242,213,213);
    iFilledRectangle(x_pos+52,75+h-10,2,8);

    iSetColor(211,47,47);
    iFilledRectangle(x_pos+5,75+h-12,10,10);
    iSetColor(198,40,40);
    iFilledRectangle(x_pos+15,75+h-12,10,10);
    iSetColor(183,28,28);
    iFilledRectangle(x_pos+25,75+h-12,10,10);

    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos-4,75+h-6,2,4);
    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos-4,75+h-4,4,2);

    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos+2,77,2,6);
    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos+2,77,6,2);
}


//for drawing the upper collumns
void draw_upper_column(int x_pos,int h)
{

    iSetColor(229,57,53);
    iFilledRectangle(x_pos,600-h,50,h);
    iSetColor(229,57,53);
    iFilledRectangle(x_pos-6,600-h,62,12);
    iSetColor(211,47,47);
    iFilledRectangle(x_pos+10,600-h+2,40,h-2);
    iSetColor(198,40,40);
    iFilledRectangle(x_pos+20,600-h+2,30,h-2);
    iSetColor(183,28,28);
    iFilledRectangle(x_pos+30,600-h+2,20,h-2);
    iSetColor(255,255,255);
    iFilledRectangle(x_pos+40,600-h+2,2,h-2);
    iSetColor(227,120,120);
    iFilledRectangle(x_pos+42,600-h+2,2,h-2);
    iSetColor(242,198,198);
    iFilledRectangle(x_pos+44,600-h+2,2,h-2);
    iSetColor(242,213,213);
    iFilledRectangle(x_pos+46,600-h+2,2,h-2);

    iSetColor(255,255,255);
    iFilledRectangle(x_pos+40,600-h+2,8,2);

    iSetColor(227,120,120);
    iFilledRectangle(x_pos+42,600-h+4,8,2);
    iSetColor(227,120,120);
    iFilledRectangle(x_pos+48,600-h+2,2,4);

    iSetColor(242,198,198);
    iFilledRectangle(x_pos+44,600-h+6,8,2);
    iSetColor(242,198,198);
    iFilledRectangle(x_pos+50,600-h+2,2,6);

    iSetColor(242,213,213);
    iFilledRectangle(x_pos+46,600-h+8,8,2);
    iSetColor(242,213,213);
    iFilledRectangle(x_pos+52,600-h+2,2,8);

    iSetColor(211,47,47);
    iFilledRectangle(x_pos+5,600-h+2,10,10);
    iSetColor(198,40,40);
    iFilledRectangle(x_pos+15,600-h+2,10,10);
    iSetColor(183,28,28);
    iFilledRectangle(x_pos+25,600-h+2,10,10);

    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos-4,600-h+2,2,4);
    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos-4,600-h+2,4,2);

    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos+2,592,2,6);
    iSetColor(255, 255, 255);
    iFilledRectangle(x_pos+2,598,6,2);


}

int main()
{


    for(i=0; i<=30; i++)
    {
        slicex[i] = 40*i;
    }

    iSetTimer(10,birds_y_position_change);
    iSetTimer(10,pillar_x_position_change);
    iSetTimer(1000,counter);
    iSetTimer(40,counter1);


    FILE *fp;
    fp = fopen("data/High_score.txt","r");
    fscanf(fp,"%d",&high_score_easy);
    fscanf(fp,"%d",&high_score_medium);
    fscanf(fp,"%d",&high_score_hard);
    fclose(fp);


    iInitialize(1200, 600, "Flappy bird");
    return 0;
}

