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
//���a�b���B�w�X
int player_card[5][2]={0}, computer_card[5][2]={0};
//���a�M�q�����P  

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

void menu(void){//��J�n���檺�ʧ@
	int choice;
	while(choice!=3){
		printf("\n\n\n\n\n                  �� Black-Jack ��\n\n");
		printf("                     �п�J�n���檺�ʧ@�G\n\n");
		printf("                     1.�n�J�b��\n\n");
		printf("                     2.�Х߷s�b��\n\n");
		printf("                     3.���}\n\n\n");
		printf("                     ���: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:	login();
					break;
			case 2:	signup();
					printf("\n\n                  ");
					break;
			case 3:	printf("\n\n                     ");
					break;
			default:printf("\n                     �п�J 1, 2 �� 3 �C\n\n                     ");
					while(getchar()!='\n');
					break;
		}
		system("pause");
		system("cls");
	}
	return;
}

void login(void){//�n�J�b��
	int game_mode=0;
	//�Ҧ�(0=�n�J���A	1=�i�J�C��) 
	struct user_data data;
	//��Ӹ�� 
	struct user_data account;
	//��J�b������� 
	int number=0;
	FILE *user;
	user=fopen("user.txt", "r");
	system("cls");
	if(user!=NULL){
		printf("\n\n\n\n\n                  �п�J�b���K�X\n");
		printf("\n                  �b��: ");
		scanf("%s", account.id);
		printf("\n                  �K�X: ");
		scanf("%s", account.pass);
		while(!feof(user)){
			fscanf(user, "%s%s%d", &data.id, &data.pass, &data.chip);
			if(strcmp(data.id, account.id)==0){
				if(strcmp(data.pass, account.pass)==0){
					number=0;
					strcpy(player.id, data.id);
					strcpy(player.pass, data.pass);
					player.chip=data.chip;
					printf("\n                  �n�J���\\�C\n");
					player.chip=player.chip+1000;				
					printf("\n                  �C���n�J�ذe 1000 �w�X�A�b���{�� %d �w�X�C\n", player.chip);
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
			printf("\n                  �b���K�X���~�C\n");
		}	
	} 
	else{
		printf("��ƿ��~�C");
	}
	fclose(user);	
	char ans;
	while(game_mode==1){
		game_control();
		if(player.chip!=0){
			while(1){
				system("cls");
				game_screen(-1, -1, 1, 0);
				printf("�O�_�~��? ( �O:Y / �_:N )  ");
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
					printf("\n                                                        �п�JY��N�C\n");
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
			printf("Gameover�G�@�b���̨S������l�B�F!\n\n                                                        ");
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

void signup(void){//�Х߱b��
	struct user_data compare;
	//������ƥ� 
	struct user_data new_account;
	//��J�s�b������� 
	int number=0;
	FILE *user;
	user=fopen("user.txt", "r"); 		
	system("cls");
	if(user!=NULL){
		printf("\n\n\n\n\n                  �п�J���U���\n");
		printf("\n                  �b��(�^��10�r�H��): ");
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
			printf("\n                  �w�s�b���b���C\n");
		}	
		else{
			printf("\n                  �K�X(�^��4�r�H��):  ");
			scanf("%s", new_account.pass);
			user=fopen("user.txt", "a");
			fprintf(user, "\n%s %s %d", new_account.id, new_account.pass, 2500);
			fclose(user);
			printf("\n\n                  ���U���\\�A�^��D���...");
		}
	}
	else{
		printf("��ƿ��~�C");
	}
	return;
} 

void game_control(void){//�C���y�{
	int count_x, count_y;
	//��l�ƥΪ��p�ƾ�
	int player_round=0;//���a���^�X(1:����) 
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
	//player_now=���a�{�b�P��(0~4)	computer_now=�q���{�b�P��(0~4) 
	char answer;
	//�O�_�n�P���^�� 
	float bet_chip=0;
	//�n�䪺�w�X
	while(1){
		game_screen(-1, -1, player_round,0);
		printf("�n��h���w�X? ");
		scanf("%f", &bet_chip);
		if(bet_chip>player.chip){
			printf("\n�@�@                                                    �j��{���w�X�A�Э��s��J�C\n\n�@�@                                                    ");
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
				printf("�O�_�n�P? ( �O:Y / �_:N / �뭰:G / �[��:A )  ");
			}
			else{
				printf("�O�_�n�P? ( �O:Y / �_:N / �뭰:G )  ");				
			} 
		}
		else{
			printf("�O�_�n�P? ( �O:Y / �_:N )  ");
		}
		scanf("%c", &answer);
		getchar();
		if(answer=='Y'){//�n�P 
			player_now++;
			hit(player_card, player_now);
			game_screen(player_now, computer_now, player_round, bet_chip);
			if(total(player_card)>21){
				player_round++;//���a�^�X�������O�� 
				break;
			}
		}
		else if(answer=='N'){//���n�P 
			player_round++;//���a�^�X�������O�� 
			break;
		}
		else{
			if(player_now==1){
				if(total(player_card)==11){
					if(answer=='A'){//�[��
						if(bet_chip*2>player.chip){
							printf("\n�@�@                                                    �j��{���w�X�C\n\n�@�@                                                    ");
    						system("pause");
						}
						else{
							player_now++;
							player_round++;//���a�^�X�������O�� 
							hit(player_card, player_now);
							bet_chip=bet_chip*2;
							break;
						}
					}
					else if(answer=='G'){//�뭰 
						bet_chip=bet_chip*0.5;
						player_round++;//���a�^�X�������O�� 
    					game_screen(player_now, computer_now, player_round, bet_chip);
						game_set(7, bet_chip);
						break;
					}
					else{
						printf("\n�@�@                                                    �п�JY�BN�BA��G�C\n");
    					while(getchar()!='\n');
    					printf("\n�@�@                                                    ");
    					system("pause");
					}
				}
				else{
					if(answer=='G'){//�뭰 
						player_round++;//���a�^�X�������O�� 
						game_screen(player_now, computer_now, player_round, bet_chip);
						bet_chip=bet_chip*0.5;
    					game_set(7, bet_chip);
						break;
					}
					else{
						printf("\n�@�@                                                    �п�JY�BN��G�C\n");
    					while(getchar()!='\n');
    					printf("\n�@�@                                                    ");
    					system("pause");
					}
				}
			}
			else{
				printf("\n�@�@                                                    �п�JY��N�C\n");
				while(getchar()!='\n');
				printf("\n�@�@                                                    "); 
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
		else if(player_now==4&&total(player_card)<=21){//���i 
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

void hit(int card[5][2], int r){//��P 
	//card=�⪺�H	r=��d���� (0~4)
	int time=0, on=1;
	//time=�ثe��L���P��	on=�P�_�O�_����
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

int total(int card[5][2]){//��P���`��
	//card=�n�⪺�P�� 
	int sum=0, i;
	//sum=�[�`	i=���� 
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

void game_set(int mode, float bet){//�C������ 
	//mode=�Ҧ� bet=���b�䪺�w�X
	printf("\n                                                        ");
	switch(mode){
		case 1:	//�ӧQ (���q)
				player.chip=player.chip+bet;
				printf("�ӧQ�A��o %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip); 
				break;
		case 2:	//�ӧQ (�q���z�P)
				player.chip=player.chip+bet;
				printf("�q���z�P�ӧQ�A��o %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				break;
		case 3: //�ӧQ (BlackJack)
				player.chip=player.chip+bet;
				printf("Black Jack �ӧQ�A��o %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				break;
		case 4: //�ӧQ (���i); 
				player.chip=player.chip+bet;
				printf("���i�ӧQ�A��o %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				break;
		case 5: //���� (���q) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("���ѡA���h %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 6: //���� (���a�z�P) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("���a�z�P���ѡA���h %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 7: //���� (�뭰) 
				player.chip=player.chip-bet;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("���a�뭰�A���h %.0f �w�X�A�ѤU %d �w�X�C", bet, player.chip);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
		case 8: //���� 
				printf("����A�w�X���ܡC");
				break;
		default:break;
	}
	printf("\n\n                                                        ");
	system("pause");
	return;
}

void game_screen(int player_round, int computer_round, int round_end, float bet){//�e����� 
	//player_round=�{�b���a�P��(0~4)	computer_round=�{�b�q���P��(0~4)	round_end=���a���^�X(1=����)	bet=���b�䪺�w�X 
	int count=0;//��ܥέp�ƾ� 
	const char *suit[4]={"��", "��", "��", "��"};//�|�ت��
	const char *number[13]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};//13�ӼƦr 
	system("cls");
	printf("\n�@�@-------------------------------------------         -----------------------------------------\n");
	printf("�@�@|                                         |         |                                       |\n");
	printf("�@�@|  ���y�{�G                               |         |      �b���G�@%10s               |\n", player.id);
	printf("�@�@|      �@�@�@�@                           |         |                                       |\n");
	printf("�@�@|  1.�b�I��21���A                         |         |      �w�X�G�@%10d chip          |\n", player.chip);
	printf("�@�@|    ���a�i���_�n�P�ܰ��P�A               |         |                                       |         ���b�䪺�w�X: %8.0f chip\n", bet);
	printf("�@�@|    ���o����a�����I�ƧY��ӡA           |         -----------------------------------------\n");
	printf("�@�@|    �n�O�~���W�L 21 �I�Y���z�P�C         |         Computer:\n");
	printf("�@�@|                                         |         ");
	if(computer_round==-1){
		printf("\n");
	}
	else{
		if(round_end==0){
			printf("�H     �@�@    �@%s%2s\n", suit[computer_card[1][1]-1], number[computer_card[1][0]-1]);
		}
		else{
			while(count<=computer_round){
				printf("%s%2s             ", suit[computer_card[count][1]-1], number[computer_card[count][0]-1]);
				count++;
			}
			printf("\n");
		}
	}
	printf("�@�@|  2.���a�����n�P������a�n�P�A           |         ");
	count=0;
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			printf("---------------�@");
			count++;
		}
		printf("\n");
	}
	printf("�@�@|    17�I�H�U�ݱj��n�P��17�I�H�W�A       |         ");
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
	printf("�@�@|    �����n�P�����᪱�a�P���a���C       |         ");
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
	printf("�@�@|                                         |         ");
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
	printf("�@�@|  ����L�W�h�G                           |         ");
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
	printf("�@�@|                                         |         ");
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
	printf("�@�@|  1.A�i�@�� 1 �� 11 �I�A                 |         ");
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
	printf("�@�@|    �Y���a���o BlackJack(A+JQK10���@)�A  |         ");
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
	printf("�@�@|    �i��o 1.5 ���w�X�C                  |         ");
	count=0;
	if(computer_round==-1){
	printf("\n");
	}
	else{
		while(count<=computer_round){
			printf("---------------�@");
			count++;
		}
		printf("\n");
	}
	printf("�@�@|                                         |         ");
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
	printf("    |  2.�Y���a��W�� 5 �i�P�٥��z�P�A        |         ---------------------------------------------------------------------------------------<\n");
	printf("    |    ��Ӯɥi�o�� 2 ���w�X�C              |         Player:\n");
	printf("�@�@|    �p���a�]�� 5 �i�P�`�Ƥj���@����ӡC  |         ");
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
	printf("�@�@|                                         |         ");
	count=0;
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			printf("---------------�@");
			count++;
		}
		printf("\n");
	}
	printf("�@�@|  3.���a����i�P�I�Ƥ��M��11�I�A         |         ");
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
	printf("�@�@|    �i���\"�[��\"�U�`�A�ӧQ�w�X�� 2 ���C  |         ");
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
	printf("�@�@|    ���[�`�����o 1 �i�P�C              |         ");
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
	printf("�@�@|                                         |         ");
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
	printf("�@�@|  4.���쭺��i�P��A                     |         ");
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
	printf("�@�@|    �i���\"�뭰\"�A���^�@�b�w�X�C         |         ");
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
	printf("�@�@|                                         |         ");
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
	printf("�@�@-------------------------------------------         ");
	count=0;
	if(player_round==-1){
	printf("\n");
	}
	else{
		while(count<=player_round){
			printf("---------------�@");
			count++;
		}
		printf("\n");
	}
	printf("�@�@                                                    ");
	if(player_round==-1){
		printf("\n");
	}
	else{
		printf("=> %d\n", total(player_card));
	}
	printf("�@�@                                                    ");
	return;
}
