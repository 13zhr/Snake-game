#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
HANDLE hOut;
COORD pos;
int t,n;
int mx_score=-1;
int mn_score=1e9;
int win=0;
int lose=0;
void HideCursor(){
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=false;    
	SetConsoleCursorInfo(handle,&CursorInfo);
}
void gotoxy(short x,short y){
	hOut=GetStdHandle(STD_OUTPUT_HANDLE); 
	pos={x,y};
	SetConsoleCursorPosition(hOut,pos); 
}
struct node{
	char body;
	short x,y; 
};

class snake_game{
	private:
 		char image;
 		enum mapSize{width=30,height=15}; 
 		deque<node> snake;   
 		int score=0;
 		char hit='w';   
		bool eat_Food=false;  
		short food_x,food_y;  
		int speed=100;   
		bool snake_state=true;   
		int level=1;
	public:
		snake_game();
		void pre_order(){
			system("mode con cols=60 lines=25");
		    system("color F0");
		    system("title Snake");
		    srand(static_cast<unsigned int>(time(NULL)));
		    gotoxy(35,1);
		    printf("THE SNAKE GAME");
		    gotoxy(35,3);
	 		printf("Made by fruitberry");
	 		gotoxy(35,5);
	 		printf("Enjoy Snake Game :)");
		}
		void draw_Frame(){
			for(int i=0;i<height;i++){
				gotoxy(0,i);
				cout<<"o";
				gotoxy(width,i);
				cout<<"o";
			}
			for(int i=0;i<=width;i++){
			    gotoxy(i,0);
			    cout<<"o";
			    gotoxy(i,height);
			    cout<<"o";
			}
		}
		void init_snake(){
			snake.push_back({'*',width/2,static_cast<short>(height/2)}); 
			for(int i=0;i<5;i++){
				snake.push_back({char('o'),width/2,static_cast<short>((height/2)+1+i)});
			}
			snake.push_back({' ',width/2,static_cast<short>((height/2)+4)}); 
		}
		void draw_Snake(){
			for(int k=0;k<snake.size();k++){
				gotoxy(snake[k].x,snake[k].y);
				cout<<snake[k].body;
			}
		}
		void clear_Tail(){
	    	int k=snake.size()-1;
	    	gotoxy(snake[k].x,snake[k].y);
	    	cout<<" "; 
		}
		void draw_Food(){
	    	while(1){
		    	food_x=rand()%(width-4)+2; 
		    	food_y=rand()%(height-2)+1; 
		    	if(iswrong()&&food_x%2==0) break;
	    	}
	    	gotoxy(food_x,food_y);
	    	cout<<"$";
		}
		bool iswrong(){
	    	for(auto i:snake){
				if(food_x==i.x&&food_y==i.y) return 0;
	 		}
	 		return 1;
		}
		void eatFood(){
	 		if(food_x==snake[0].x&&food_y==snake[0].y)
	 		eat_Food=true;
		}
		void state(){
			if(snake.size()>=4){
	 			deque<node>::iterator it=snake.begin()+1; 
	 			int x=(it-1)->x,y=(it-1)->y;
	 			for(it;it!=snake.end();++it){
	 				if(it->x==x&&it->y==y) 
	  					snake_state=false;
	 			}
	 		}
	 		if(snake[0].x==1||snake[0].x==29||snake[0].y==0||snake[0].y==15) 
	 			snake_state=false;
		}
		void Key(){
	 		char key=hit;
	 		if(kbhit()) hit=getch(); 
	 		for(int i=snake.size()-1;i>0;i--){
	 			snake[i].x=snake[i-1].x;
	 			snake[i].y=snake[i-1].y;
	 		}
	 		if((hit=='a'||hit=='A')&&hit!='d'){
	 			hit='a';
				snake[0].x--;
	 		}
			else if((hit=='d'||hit=='D')&&hit!='a'){
	 			hit='d';
				snake[0].x++;
	 		}
	 		else if((hit=='w'||hit=='W')&&hit!='s'){
	 			hit='w';
				snake[0].y--;
	 		}
	 		else if((hit=='s'||hit=='S')&&hit!='w'){
	 			hit='s';
				snake[0].y++;
	 		}
	 	}
		void print(){
			gotoxy(35,7);
			cout<<"Up:w"<<endl;
			gotoxy(35,8);
			cout<<"Down:s"<<endl;
			gotoxy(35,9);
			cout<<"Left:a"<<endl;
			gotoxy(35,10);
			cout<<"Right:d"<<endl;
	 		gotoxy(35,12);
	 		cout<<"Score:"<<score;
	 		gotoxy(35,14);
	 		cout<<"Level:"<<level;
	 	}
};
snake_game::snake_game(){
 	HideCursor();
 	pre_order();
 	init_snake();
 	draw_Food();
 	node tail;
	while(1){
 		draw_Frame();
 		tail=snake.back();
 		if(eat_Food){
	 		snake.back().body='o'; 
	 		snake.push_back(tail);
	 		gotoxy(food_x,food_y);
	 		cout<<" ";
	 		draw_Food();
	 		score++;
	 		if(score%5==0){
	 			speed*=0.8;
	 			level++;
 			}
 			eat_Food=false;
 		}
 		if(n==2){
 			if(level==3){
	 			win++;
	 			gotoxy(10,8);
	 			system("color f1");
	 			cout<<"YOU WIN";
	 			goto pass;
			}
		}
	 	Key();
	 	draw_Snake();
	 	state();
	 	if(!snake_state){
	 		mx_score=max(mx_score,score);
	 		mn_score=min(mn_score,score);
			break;
		}
	 	eatFood(); 
	 	Sleep(speed);
	 	clear_Tail();
	 	print();
	}
	lose++;
	gotoxy(5,16);
	system("color f4");
    cout<<"GAME OVER";
	gotoxy(5,17);
	cout<<"YOU LOSE"<<endl;
    pass:;
}

int main(){
	printf("IPS:");
	cin>>t;
	puts("Choose your mode:");
	puts("1.Endless");
	puts("2.Level"); 
	cin>>n;
	if(n!=1&&n!=2) return puts("What are you doing?"),0;
	puts("Game Begin!!!"); 
	Sleep(1000);
	while(t--){
		snake_game game;
		Sleep(2000);
	}
	if(n==1){
		gotoxy(20,17);
		cout<<"Max Score:"<<mx_score;
		gotoxy(20,18);
		cout<<"Min Score:"<<mn_score;
	}else{
		system("color F0");
		gotoxy(20,16);
		printf("Win:%d times",win);
		gotoxy(20,17);
		printf("Lose:%d times",lose);
		gotoxy(20,18);
	}
    return 0;
}
