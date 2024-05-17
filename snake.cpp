#include <graphics.h>
#include <iostream>
#include <queue>
using namespace std;
const short EMPTY=0,WALL=3,SNAKE=1,APPLE=2;
enum direction{DOWN,UP,LEFT,RIGHT};
direction snake_dir,fire_dir;
bool ext=0,is_game_over=0,fire_stared=0;
queue<pair<int,int>>snake_body; // first is row second is column 
pair<int,int>fire_loc;
short board[35][35]
{
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
    {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},

};

void game_over()
{
    is_game_over=1;
    setcolor(WHITE);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(3,HORIZ_DIR,2);
    outtextxy(getmaxx()/2,getmaxy()/2,"You are a loser");
}

void draw_snake_body(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,GREEN);
    bar(x+1,y+1,x+17,y+17);
}

void draw_fire(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,LIGHTCYAN);
    bar(x+2,y+2,x+15,y+15);   
}

void erase_fire(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}

void erase_snake_body(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}

void draw_apple(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(x+1,y+1,x+17,y+17);
    
}

void draw_wall(short row,short column)
{
    int y=row*18,x=column*18;
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(x,y,x+18,y+18);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(x+0,y+0,x+18,y+0);
    line(x+0,y+9,x+18,y+9);
    line(x+0,y+18,x+0,y+18);
    line(x+12,y+0,x+12,y+9);
    line(x+6,y+9,x+6,y+18);

}

void draw_board()
{
    for(short row=0;row<35;row++)
    {
        for(short column=0;column<35;column++)
        {
            switch(board[row][column])
            {
                case EMPTY:
                    break;
                case SNAKE:
                    draw_snake_body(row,column);
                    break;
                case APPLE:
                    draw_apple(row,column);
                    break;
                case WALL:
                    draw_wall(row,column);
                    break;

            }
        }
    }
}

void init_snake()
{
    pair<int,int>loc={rand()%5+1,rand()%5+1};
    
    for(int i=0;i<1;i++)
    {
        snake_body.push(loc);
        board[loc.first][loc.second]=1;
        loc.first++;
    }
}

pair<int,int> get_next_fire()
{
    pair<int,int>fire=fire_loc;
    switch(fire_dir)
    {
        case UP:
            fire.first--;
            break;
        case DOWN:
            fire.first++;
            break;
        case LEFT:
            fire.second--;
            break;
        case RIGHT:
            fire.second++;
            break;
    }
    return fire;
}


pair<int,int>get_next_head()
{
    pair<int,int>head=snake_body.back();
    switch(snake_dir)
    {
        case UP:
            head.first--;
            break;
        case DOWN:
            head.first++;
            break;
        case LEFT:
            head.second--;
            break;
        case RIGHT:
            head.second++;
            break;
    }
    return head;
}

void move_forward_delete_tale(pair<int,int> next_head)
{
    // move the head forward
    snake_body.push(next_head);
    draw_snake_body(next_head.first,next_head.second);
    board[next_head.first][next_head.second]=1;

    // delete the tail
    pair<int,int>tail=snake_body.front();
    snake_body.pop();
    erase_snake_body(tail.first,tail.second);
    board[tail.first][tail.second]=0;
}

void move_forward_no_delete_tale(pair<int,int> next_head)
{
    // move the head forward
    snake_body.push(next_head);
    draw_snake_body(next_head.first,next_head.second);
    board[next_head.first][next_head.second]=1;

}

void generate_apple()
{
    int row,column;
    do
    {
        row=rand()%33+1;
        column=rand()%33+1;
    } while (board[row][column]!=EMPTY);
    board[row][column]=APPLE;
    draw_apple(row,column);
}

void move_snake()
{
    pair<int,int> next_head=get_next_head();
    switch (board[next_head.first][next_head.second])
    {
        case EMPTY:
            move_forward_delete_tale(next_head);
            break;
        case APPLE:
            move_forward_no_delete_tale(next_head);
            generate_apple();
            break;
        case WALL:
        case SNAKE:
            game_over();
            break;
    }

}

void start_fire()
{
    fire_stared=1;
    fire_loc=get_next_head();
    fire_dir=snake_dir;
    draw_fire(fire_loc.first,fire_loc.second);
}

void stop_fire()
{
    fire_stared=0;
}

void move_fire()
{   if(fire_stared)
    {
        pair<int,int> next_fire=get_next_fire();
        if(next_fire.first>35||next_fire.first<0||next_fire.second>35||next_fire.second<0)
        {
            stop_fire();
            erase_fire(fire_loc.first,fire_loc.second);
            return ;
        }
        draw_fire(next_fire.first,next_fire.second);
        erase_fire(fire_loc.first,fire_loc.second);
        fire_loc=next_fire;
    }
}


void change_direction(char c)
{
    if(c==KEY_UP&&snake_dir!=DOWN)
        snake_dir=UP;
    if(c==KEY_DOWN&&snake_dir!=UP)
        snake_dir=DOWN;
    if(c==KEY_LEFT&&snake_dir!=RIGHT)
        snake_dir=LEFT;
    if(c==KEY_RIGHT&&snake_dir!=LEFT)
        snake_dir=RIGHT;
    // switch(c)
    // {
    //     case KEY_UP:
    //         snake_dir=UP;
    //         break;
    //     case KEY_DOWN:
    //         snake_dir=DOWN;
    //         break;
    //     case KEY_RIGHT:
    //         snake_dir=RIGHT;
    //         break;
    //     case KEY_LEFT:
    //         snake_dir=LEFT;
    //         break;
    // }
}

void key_input()
{
    char c;
    if(kbhit())
    {
        c=getch();
        if(c==0)
        {
            c=getch();
            change_direction(c);
        }
        else if(c=='x')
        {
            ext=1;
        }
        else if(c==' ')// space par is pressed 
        {
            start_fire();
        }
    }
}

int main()
{
    int a{630},b{630};string cheat;
    long long game_time=0;
    is_game_over=0;
//    std::cout<<"enter screen resolution note : must be 630*630 : ";
//    std::cin>>a>>b;
    initwindow(a,b,"My little snake");
    init_snake();
    draw_board();
    while(!kbhit()){}// to start the game after a press of a button
    // while(1)
    // {
        while(!is_game_over)
        {

            if(game_time%900000==0)
               move_fire();
            if(game_time%6000000==0)
                move_snake();
            key_input();
            game_time++;
            if(game_time==10000000000000000)
            {
                generate_apple();// generate a bonus apple if the player stayed alive this long of time 
                game_time=0;
            }
            if(ext)
                return 0;
        } // an attempt to make a cheat code in the game ):
    //     getline(cin,cheat);
    //     if(cheat=="mido")
    //     {
    //         is_game_over=0;
    //     }
    //     else
    //         break;
    // }


    while(!kbhit()){}
for(unsigned int i=0;i<1000000000;i++){}
        return 0;
}
