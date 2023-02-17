#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

struct user_data{
	char id[10];
	char pass[10];
	int chip;	
};
struct user_data player;
//玩家帳號、籌碼
int player_card[5][2]={0}, computer_card[5][2]={0};
//玩家和電腦的牌  

void menu(void);
void login(void);
void signup(void);
void game_control(void);
void hit(int card[5][2], int r);
int total(int card[5][2]);
void game_set(int mode, float bet);
void game_screen(int player_round, int computer_round, int round_end, float chips);

int main(void){
	srand(time(NULL));
	system("mode con cols=150 lines=45");
	menu();
	return 0;
}

void menu(void){//輸入要執行的動作
	int choice;
	while(choice!=3){
		printf("\n\n\n\n\n                  ◆ Black-Jack ◆\n\n");
		printf("                     請輸入要執行的動作：\n\n");
		printf("                     1.登入帳號\n\n");
		printf("                     2.創立新帳號\n\n");
		printf("                     3.離開\n\n\n");
		printf("                     選擇: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:	login();
					break;
			case 2:	signup();
					printf("\n\n                  ");
					break;
			case 3:	printf("\n\n                     ");
					break;
			default:printf("\n                     請輸入 1, 2 或 3 。\n\n                     ");
					while(getchar()!='\n');
					break;
		}
		system("pause");
		system("cls");
	}
	return;
}

void login(void){//登入帳號
	int game_mode=0;
	//模式(0=登入狀態	1=進入遊戲) 
	struct user_data data;
	//對照資料 
	struct user_data account;
	//輸入帳號的資料 
	int number=0;
	FILE *user;
	user=fopen("user.txt", "r");
	system("cls");
	if(user!=NULL){
		printf("\n\n\n\n\n                  請輸入帳號密碼\n");
		printf("\n                  帳號: ");
		scanf("%s", account.id);
		printf("\n                  密碼: ");
		scanf("%s", account.pass);
		while(!feof(user)){
			fscanf(user, "%s%s%d", &data.id, &data.pass, &data.chip);
			if(strcmp(data.id, account.id)==0){
				if(strcmp(data.pass, account.pass)==0){
					number=0;
					strcpy(player.id, data.id);
					strcpy(player.pass, data.pass);
					player.chip=data.chip;
					printf("\n                  登入成功\。\n");
					player.chip=player.chip+1000;				
					printf("\n                  每次登入贈送 1000 籌碼，帳號現有 %d 籌碼。\n", player.chip);
					printf("\n                  ");
					system("pause");
					game_mode++;
					break;
				}
			}
			else{
				number++;
			}
		}
		if(number!=0){
			printf("\n                  帳號密碼錯誤。\n");
		}	
	} 
	else{
		printf("資料錯誤。");
	}
	fclose(user);	
	char ans;
	while(game_mode==1){
		game_control();
		if(player.chip!=0){
			while(1){
				system("cls");
				game_screen(-1, -1, 1, 0);
				printf("是否繼續? ( 是:Y / 否:N )  ");
				scanf("%c", &ans);
				if(ans=='N'){
					game_mode=0;
					printf("\n                                                        ");
					break;
				}
				else if(ans=='Y'){
					game_mode=1;
					break;
				}
				else{
					printf("\n                                                        請輸入Y或N。\n");
					printf("\n                                                        ");
    				while(getchar()!='\n');
   	 			system("pause");
				}
			}
		}
		else{
			system("cls");
			game_screen(-1, -1, 1, 0);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
			printf("Gameover：　帳號裡沒有任何餘額了!\n\n                                                        ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			game_mode++;
		}
	}
	FILE *copy, *paste;
	copy=fopen("user.txt", "r");
	if(copy!=NULL){
		paste=fopen("back.txt", "w");
		struct user_data data_copy;
		while(!feof(copy)){
			fscanf(copy, "%s %s %d\n", &data_copy.id, &data_copy.pass, &data_copy.chip);
			if(strcmp(data_copy.id, player.id)==0){
				fprintf(paste, "%s %s %d\n", data_copy.id, data_copy.pass, player.chip);
			}
			else{ 
				fprintf(paste, "%s %s %d\n", data_copy.id, data_copy.pass, data_copy.chip);
			}
		}
		fclose(copy);
		fclose(paste);
		unlink("user.txt");
		rename("back.txt", "user.txt");
	}
	return;
}

void signup(void){//創立帳號
	struct user_data compare;
	//比較重複用 
	struct user_data new_account;
	//輸入新帳號的資料 
	int number=0;
	FILE *user;
	user=fopen("user.txt", "r"); 		
	system("cls");
	if(user!=NULL){
		printf("\n\n\n\n\n                  請輸入註冊資料\n");
		printf("\n                  帳號(英數10字以內): ");
		scanf("%s", new_account.id);
		while(!feof(user)){
			fscanf(user, "%s%s%d", &compare.id, &compare.pass, &compare.chip);
			if(strcmp(compare.id, new_account.id)==0){
				number++;
				break;
			}
		}
		fclose(user);
		if(number!=0){
			printf("\n                  已存在的帳號。\n");
		}	
		else{
			printf("\n                  密碼(英數4字以內):  ");
			scanf("%s", new_account.pass);
			user=fopen("user.txt", "a");
			fprintf(user, "\n%s %s %d", new_account.id, new_account.pass, 2500);
			fclose(user);
			printf("\n\n                  註冊成功\，回到主選單...");
		}
	}
	else{
		printf("資料錯誤。");
	}
	return;
} 

void game_control(void){//遊戲流程
	int count_x, count_y;
	//初始化用的計數器
	int player_round=0;//玩家的回合(1:結束) 
	for(count_x=0;count_x<5;count_x++){
		for(count_y=0;count_y<2;count_y++){
			player_card[count_x][count_y]=0;
			computer_card[count_x][count_y]=0;
		}
	}
	hit(player_card, 0);
	hit(player_card, 1);
	hit(computer_card, 0);
	hit(computer_card, 1);
	int player_now=1, computer_now=1;
	//player_now=玩家現在牌數(0~4)	computer_now=電腦現在牌數(0~4) 
	char answer;
	//是否要牌的回答 
	float bet_chip=0;
	//要賭的籌碼
	while(1){
		game_screen(-1, -1, player_round,0);
		printf("要賭多少籌碼? ");
		scanf("%f", &bet_chip);
		if(bet_chip>player.chip){
			printf("\n　　                                                    大於現有籌碼，請重新輸入。\n\n　　                                                    ");
			system("pause");
		}
		else{
			break;
		}
	}
	game_screen(player_now, computer_now, player_round,bet_chip);
	getchar();
	while(player_now<4){
		game_screen(player_now, computer_now, player_round, bet_chip);
		if(player_now==1){
			if(total(player_card)==11){
				printf("是否要牌? ( 是:Y / 否:N / 投降:G / 加倍:A )  ");
			}
			else{
				printf("是否要牌? ( 是:Y / 否:N / 投降:G )  ");				
			} 
		}
		else{
			printf("是否要牌? ( 是:Y / 否:N )  ");
		}
		scanf("%c", &answer);
		getchar();
		if(answer=='Y'){//要牌 
			player_now++;
			hit(player_card, player_now);
			game_screen(player_now, computer_now, player_round, bet_chip);
			if(total(player_card)>21){
				player_round++;//玩家回合結束的記號 
				break;
			}
		}
		else if(answer=='N'){//不要牌 
			player_round++;//玩家回合結束的記號 
			break;
		}
		else{
			if(player_now==1){
				if(total(player_card)==11){
					if(answer=='A'){//加倍
						if(bet_chip*2>player.chip){
							printf("\n　　                                                    大於現有籌碼。\n\n　　                                                    ");
    						system("pause");
						}
						else{
							player_now++;
							player_round++;//玩家回合結束的記號 
							hit(player_card, player_now);
							bet_chip=bet_chip*2;
							break;
						}
					}
					else if(answer=='G'){//投降 
						bet_chip=bet_chip*0.5;
						player_round++;//玩家回合結束的記號 
    					game_screen(player_now, computer_now, player_round, bet_chip);
						game_set(7, bet_chip);
						break;
					}
					else{
						printf("\n　　                                                    請輸入Y、N、A或G。\n");
    					while(getchar()!='\n');
    					printf("\n　　                                                    ");
    					system("pause");
					}
				}
				else{
					if(answer=='G'){//投降 
						player_round++;//玩家回合結束的記號 
						game_screen(player_now, computer_now, player_round, bet_chip);
						bet_chip=bet_chip*0.5;
    					game_set(7, bet_chip);
						break;
					}
					else{
						printf("\n　　                                                    請輸入Y、N或G。\n");
    					while(getchar()!='\n');
    					printf("\n　　                                                    ");
    					system("pause");
					}
				}
			}
			else{
				printf("\n　　                                                    請輸入Y或N。\n");
				while(getchar()!='\n');
				printf("\n　　                                                    "); 
				system("pause");
			}
		}
	}
	if(total(player_card)<=21&&answer!='G'){
		while(total(computer_card)<17){
			if(total(computer_card)<17){
				if(computer_now<5)
				{
					computer_now++;
					hit(computer_card, computer_now);
					Sleep(500);
					game_screen(player_now, computer_now, player_round, bet_chip);	
				}
			}
		}
	}
	if(answer!='G'){
		if(player_now==1&&total(player_card)==21){//BlackJack
			game_screen(player_now, computer_now, player_round, bet_chip);
			bet_chip=bet_chip*1.5;
			game_set(3, bet_chip);
		}
		else if(player_now==4&&total(player_card)<=21){//五張 
			if(computer_now==4){
				if(total(player_card)>total(computer_card)){
					player_round++;
					game_screen(player_now, computer_now, player_round, bet_chip);
					bet_chip=bet_chip*2;
					game_set(4, bet_chip);
				}
				else{
					game_set(5, bet_chip);		
				}
			}
			else{
				player_round++;
				game_screen(player_now, computer_now, player_round, bet_chip);
				bet_chip=bet_chip*2;
				game_set(4, bet_chip);
			}
		}
		else{
			game_screen(player_now, computer_now, player_round, bet_chip);
			if(total(player_card)>21){
				game_set(6, bet_chip);
			}
			else if(total(computer_card)>21){
				game_set(2, bet_chip);
			}
			else{
				if(total(player_card)>total(computer_card)){
					game_set(1, bet_chip);
				}
				else if(total(player_card)==total(computer_card)){
					game_set(8, bet_chip);
				}
				else{
				game_set(5, bet_chip);
				}
			}
		}
	}
	return;
}  

void hit(int card[5][2], int r){//抽牌 
	//card=抽的人	r=抽卡次數 (0~4)
	int time=0, on=1;
	//time=目前抽過的牌數	on=判斷是否重複
	card[r][0]=rand()%13+1;
	card[r][1]=rand()%4+1;
	while(on!=0){
		on=0;
		for(time=0;time<r;time++){
			if(card[r][0]==player_card[time][0]){
				if(card[r][1]==player_card[time][1]){
					on++;
				}
			}
			if(card[r][0]==computer_card[time][0]){
				if(card[r][1]==computer_card[time][1]){
					on++;
				}
			}
		}
		if(on!=0){
			card[r][0]=rand()%13+1;
			card[r][1]=rand()%4+1;
		}
	}
	return;
}

int total(int card[5][2]){//算牌的總數
	//card=要算的牌組 
	int sum=0, i;
	//sum=加總	i=次數 
	for(i=0;i<5;i++){
		if(card[i][0]>10){
			sum=sum+10;
		}
		else if(card[i][0]==1){
			sum=sum+11;
		}
		else{
			sum=sum+card[i][0];
		}
	}
	if(sum>21){
		for(i=0;i<5;i++){
			if(card[i][0]==1){
			sum=sum-10;
			}	
		}
	}
	return sum;
}

void game_set(int mode, float bet){//遊戲結束 
	//mode=模式 bet=正在賭的籌碼
	printf("\n                                                        ");
	switch(mode){
		case 1:	//勝利 (普通)
				player.chip=player.chip+bet;
				printf("勝利，獲得 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip); 
				break;
		case 2:	//勝利 (電腦爆牌)
				player.chip=player.chip+bet;
				printf("電腦爆牌勝利，獲得 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				break;
		case 3: //勝利 (BlackJack)
				player.chip=player.chip+bet;
				printf("Black Jack 勝利，獲得 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				break;
		case 4: //勝利 (五張); 
				player.chip=player.chip+bet;
				printf("五張勝利，獲得 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				break;
		case 5: //失敗 (普通) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("失敗，失去 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 6: //失敗 (玩家爆牌) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("玩家爆牌失敗，失去 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 7: //失敗 (投降) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("玩家投降，失去 %.0f 籌碼，剩下 %d 籌碼。", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 8: //平手 
				printf("平手，籌碼不變。");
				break;
		default:break;
	}
	printf("\n\n                                                        ");
	system("pause");
	return;
}

void game_screen(int player_round, int computer_round, int round_end, float bet){//畫面顯示 
	//player_round=現在玩家牌數(0~4)	computer_round=現在電腦牌數(0~4)	round_end=玩家的回合(1=結束)	bet=正在賭的籌碼 
	int count=0;//顯示用計數器 
	const char *suit[4]={"●", "★", "◆", "▲"};//四種花色
	const char *number[13]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};//13個數字 
	system("cls");
	printf("\n　　-------------------------------------------         -----------------------------------------\n");
	printf("　　|                                         |         |                                       |\n");
	printf("　　|  ＊流程：                               |         |      帳號：　%10s               |\n", player.id);
	printf("　　|      　　　　                           |         |                                       |\n");
	printf("　　|  1.在點數21內，                         |         |      籌碼：　%10d chip          |\n", player.chip);
	printf("　　|    玩家可不斷要牌至停牌，               |         |                                       |         正在賭的籌碼: %8.0f chip\n", bet);
	printf("　　|    取得比莊家高的點數即獲勝，           |         -----------------------------------------\n");
	printf("　　|    要是途中超過 21 點即為爆牌。         |         Computer:\n");
	printf("　　|                                         |         ");
	if(computer_round==-1){
		printf("\n");
	}
	else{
		if(round_end==0){
			printf("？     　　    　%s%2s\n", suit[computer_card[1][1]-1], number[computer_card[1][0]-1]);
		}
		else{
			while(count<=computer_round){
				printf("%s%2s             ", suit[computer_card[count][1]-1], number[computer_card[count][0]-1]);
				count++;
			}
			printf("\n");
		}
	}
	printf("　　|  2.玩家結束要牌後輪莊家要牌，           |         ");
	count=0;
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			printf("---------------　");
			count++;
		}
		printf("\n");
	}
	printf("　　|    17點以下需強制要牌至17點以上，       |         ");
	count=0;//1
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]>8&&computer_card[count][0]<11){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    全部要牌結束後玩家與莊家比拚。       |         ");
	count=0;//2
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]<9&&computer_card[count][0]>3){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]<4&&computer_card[count][0]>1||computer_card[count][0]==10){
				printf("|     %s      |  ", suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|                                         |         ");
	count=0;//3
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]>8&&computer_card[count][0]<11){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]==8){
				printf("|     %s      |  ", suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|  ＊其他規則：                           |         ");
	count=0;//4
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|   Unknown   |  ");
				count++;
			}
			if(computer_card[count][0]<9&&computer_card[count][0]>5){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]==9||computer_card[count][0]==5||computer_card[count][0]==3||computer_card[count][0]==1){
				printf("|     %s      |  ", suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]==11){
				printf("| %s JACK %s  |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);	
			}
			else if(computer_card[count][0]==12){
				printf("| %s Queen %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]==13){
				printf("| %s KING %s  |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|                                         |         ");
	count=0;//5
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]==9||computer_card[count][0]==10){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]==7||computer_card[count][0]==8){
				printf("|     %s      |  ", suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|  1.A可作為 1 或 11 點，                 |         ");
	count=0;//6
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]<9&&computer_card[count][0]>3){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else if(computer_card[count][0]<4&&computer_card[count][0]>1||computer_card[count][0]==10){
				printf("|     %s      |  ", suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    若玩家取得 BlackJack(A+JQK10之一)，  |         ");
	count=0;//7
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			if(round_end==0)
			{
				printf("|             |  ");
				count++;
			}
			if(computer_card[count][0]>8&&computer_card[count][0]<11){
				printf("| %s       %s |  ", suit[computer_card[count][1]-1], suit[computer_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    可獲得 1.5 倍籌碼。                  |         ");
	count=0;
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			printf("---------------　");
			count++;
		}
		printf("\n");
	}
	printf("　　|                                         |         ");
	if(computer_round==-1){
		printf("\n");
	}
	else{
		if(round_end==0){
			printf("=> ?\n");
		}
		else{
			printf("=> %d\n", total(computer_card));
		}
	}
	printf("    |  2.若玩家手上有 5 張牌還未爆牌，        |         ---------------------------------------------------------------------------------------<\n");
	printf("    |    獲勝時可得到 2 倍籌碼。              |         Player:\n");
	printf("　　|    如莊家也有 5 張牌總數大的一邊獲勝。  |         ");
	count=0;
	if(player_round==-1){
		printf("\n");
	}
	else{
		while(count<=player_round){
			printf("%s%2s             ", suit[player_card[count][1]-1], number[player_card[count][0]-1]);
			count++;
		}
			printf("\n");
	}
	printf("　　|                                         |         ");
	count=0;
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			printf("---------------　");
			count++;
		}
		printf("\n");
	}
	printf("　　|  3.玩家首兩張牌點數之和為11點，         |         ");
	count=0;//1
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]>8&&player_card[count][0]<11){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    可選擇\"加倍\"下注，勝利籌碼為 2 倍。  |         ");
	count=0;//2
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]<9&&player_card[count][0]>3){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]<4&&player_card[count][0]>1||player_card[count][0]==10){
				printf("|     %s      |  ", suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    但加注後僅獲發 1 張牌。              |         ");
	count=0;//3
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]>8&&player_card[count][0]<11){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]==8){
				printf("|     %s      |  ", suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|                                         |         ");
	count=0;//4
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]<9&&player_card[count][0]>5){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]==9||player_card[count][0]==5||player_card[count][0]==3||player_card[count][0]==1){
				printf("|     %s      |  ", suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]==11){
				printf("| %s JACK %s  |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);	
			}
			else if(player_card[count][0]==12){
				printf("| %s Queen %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]==13){
				printf("| %s KING %s  |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|  4.拿到首兩張牌後，                     |         ");
	count=0;//5
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]==9||player_card[count][0]==10){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]==7||player_card[count][0]==8){
				printf("|     %s      |  ", suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|    可選擇\"投降\"，拿回一半籌碼。         |         ");
		count=0;//6
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]<9&&player_card[count][0]>3){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else if(player_card[count][0]<4&&player_card[count][0]>1||player_card[count][0]==10){
				printf("|     %s      |  ", suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　|                                         |         ");
	count=0;//7
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			if(player_card[count][0]>8&&player_card[count][0]<11){
				printf("| %s       %s |  ", suit[player_card[count][1]-1], suit[player_card[count][1]-1]);
			}
			else{
				printf("|             |  ");
			}
			count++;
		}
		printf("\n");
	}
	printf("　　-------------------------------------------         ");
	count=0;
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			printf("---------------　");
			count++;
		}
		printf("\n");
	}
	printf("　　                                                    ");
	if(player_round==-1){
		printf("\n");
	}
	else{
		printf("=> %d\n", total(player_card));
	}
	printf("　　                                                    ");
	return;
}
