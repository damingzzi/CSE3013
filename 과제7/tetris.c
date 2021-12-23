#include "tetris.h"

static struct sigaction act, oact;

int rankSize = 0, newranksize = 0;
Node* rankList = NULL;

int main() {
	int exit = 0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	srand((unsigned int)time(NULL));

	while (!exit) {
		clear();
		createRankList();
		switch (menu()) {
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit = 1; break;
		case MENU_RANK: rank(); break;
		default: break;
		}
		writeRankFile();
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris() {
	int i, j;

	for (j = 0; j < HEIGHT; j++)
		for (i = 0; i < WIDTH; i++)
			field[j][i] = 0;

	nextBlock[0] = rand() % 7;
	nextBlock[1] = rand() % 7;
	nextBlock[2] = rand() % 7;
	blockRotate = 0;
	blockY = -1;
	blockX = WIDTH / 2 - 2;
	score = 0;
	gameOver = 0;
	timed_out = 0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline() {
	int i, j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0, 0, HEIGHT, WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2, WIDTH + 10);
	printw("NEXT BLOCK");
	DrawBox(3, WIDTH + 10, 4, 8);
	/* 2번째 next block을 보여주는 공간의 테두리를 그린다.*/
	DrawBox(10, WIDTH + 10, 4, 8);
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(17, WIDTH + 10);
	printw("SCORE");
	DrawBox(18, WIDTH + 10, 1, 8);
}

int GetCommand() {
	int command;
	command = wgetch(stdscr);
	switch (command) {
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command) {
	int ret = 1;
	int drawFlag = 0;
	switch (command) {
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if ((drawFlag = CheckToMove(field, nextBlock[0], (blockRotate + 1) % 4, blockY, blockX)))
			blockRotate = (blockRotate + 1) % 4;
		break;
	case KEY_DOWN:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY, blockX + 1)))
			blockX++;
		break;
	case KEY_LEFT:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY, blockX - 1)))
			blockX--;
		break;
	default:
		break;
	}
	if (drawFlag) DrawChange(field, command, nextBlock[0], blockRotate, blockY, blockX);
	return ret;
}

void DrawField() {
	int i, j;
	for (j = 0; j < HEIGHT; j++) {
		move(j + 1, 1);
		for (i = 0; i < WIDTH; i++) {
			if (field[j][i] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score) {
	move(19, WIDTH + 11);
	printw("%8d", score);
}

void DrawNextBlock(int* nextBlock) {
	int i, j;
	for (i = 0; i < 4; i++) {
		move(4 + i, WIDTH + 13);
		for (j = 0; j < 4; j++) {
			if (block[nextBlock[1]][0][i][j] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for (i = 0; i < 4; i++) {
		move(11 + i, WIDTH + 13);
		for (j = 0; j < 4; j++) {
			if (block[nextBlock[2]][0][i][j] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID, int blockRotate, char tile) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (block[blockID][blockRotate][i][j] == 1 && i + y >= 0) {
				move(i + y + 1, j + x + 1);
				attron(A_REVERSE);
				printw("%c", tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT, WIDTH + 10);
}

void DrawBox(int y, int x, int height, int width) {
	int i, j;
	move(y, x);
	addch(ACS_ULCORNER);
	for (i = 0; i < width; i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for (j = 0; j < height; j++) {
		move(y + j + 1, x);
		addch(ACS_VLINE);
		move(y + j + 1, x + width + 1);
		addch(ACS_VLINE);
	}
	move(y + j + 1, x);
	addch(ACS_LLCORNER);
	for (i = 0; i < width; i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play() {
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM, &act, &oact);
	InitTetris();
	do {
		if (timed_out == 0) {
			alarm(1);
			timed_out = 1;
		}

		command = GetCommand();
		if (ProcessCommand(command) == QUIT) {
			alarm(0);
			DrawBox(HEIGHT / 2 - 1, WIDTH / 2 - 5, 1, 10);
			move(HEIGHT / 2, WIDTH / 2 - 4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	} while (!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT / 2 - 1, WIDTH / 2 - 5, 1, 10);
	move(HEIGHT / 2, WIDTH / 2 - 4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu() {
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH], int currentBlock, int blockRotate, int blockY, int blockX) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][blockRotate][i][j] == 1) {
				if (f[blockY + i][blockX + j] == 1) return 0;
				else if (((blockY + i) >= HEIGHT) || (blockX + j) < 0 || ((blockX + j) >= WIDTH)) {
					return 0; //블록이 field 밖으로 넘어가는 경우
				}
			}
		}
	}
	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH], int command, int currentBlock, int blockRotate, int blockY, int blockX) {
	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	int lRotate, lblockY, lblockX;
	lRotate = blockRotate;
	lblockY = blockY;
	lblockX = blockX;

	switch (command) {
	case KEY_UP:
		lRotate = (blockRotate + 3) % 4; //원래의 rotation을 찾아줌
		break;
	case KEY_DOWN:
		lblockY--;
		break;
	case KEY_RIGHT:
		lblockX--;
		break;
	case KEY_LEFT:
		lblockX++;
		break;
	default:
		break;
	}

	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][blockRotate][i][j] == 1) f[lblockY + i][lblockX + j] = 0;
		}
	}
	//3. 새로운 블록 정보를 그린다. 
	DrawField();
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);

}

void BlockDown(int sig) {
	if (CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)) {
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else {
		if (blockY == -1) gameOver = 1;
		else {
			score+=AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
			DeleteLine(field); //블록이 아래로 내려가지 못하므로 블록을 field에 추가하고 라인을 체크
			nextBlock[0] = nextBlock[1];
			nextBlock[1] = nextBlock[2];
			nextBlock[2] = rand() % 7;
			DrawNextBlock(nextBlock);
			blockRotate = 0;
			blockY = -1;
			blockX = WIDTH / 2 - 2;
		}
	}

	timed_out = 0; //반복해서 blockDown 실행하기 위함
}

int AddBlockToField(char f[HEIGHT][WIDTH], int currentBlock, int blockRotate, int blockY, int blockX) {
	//Block이 추가된 영역의 필드값을 바꾼다.
	int t_cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][blockRotate][i][j] == 1) {
				f[blockY + i][blockX + j] = 1;
				if ((blockY + i + 1) < HEIGHT) {
					if (f[blockY + i + 1][blockX + j] == 1)t_cnt++;
				}
				else if ((blockY + i + 1) == HEIGHT) t_cnt++;
			}
		}
	}
	return t_cnt * 10;
}

int DeleteLine(char f[HEIGHT][WIDTH]) {
	// user code
	int delLine = 0;
	int full_flag;

	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	for (int i = 0; i < HEIGHT; i++) {
		full_flag = 1;
		for (int j = 0; j < WIDTH; j++) {
			if (f[i][j] == 0) {
				full_flag = 0;
				break;
			}
		}
		//2, 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
		if (full_flag == 1) { //중간에 비어있는 부분이 없음
			delLine++;
			for (int k = i - 1; k >= 0; k--) { //field의 위로 갈수록 y값이 작아짐을 기억하자
				for (int j = 0; j < WIDTH; j++) {
					f[k + 1][j] = f[k][j]; //아랫줄의 정보를 받아온다.
				}
			}
		}
	}
	score += (delLine * delLine * 100);
	PrintScore(score);
	DrawField();
	return score;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID, int blockRotate) {
	while (CheckToMove(field, nextBlock[0], blockRotate, y, x) == 1) { y++; }
	y--;
	DrawBlock(y, x, blockID, blockRotate, '/');
}

void DrawBlockWithFeatures(int y, int x, int blockID, int BlockRotate) {
	DrawBlock(y, x, blockID, blockRotate, ' ');
	DrawShadow(y, x, blockID, blockRotate);
}

///////////////////////////////////////////////////////////////////////////

void createRankList() {
	Node* temp, * newNode;
	
	rankList = (Node*)malloc(sizeof(Node));
	rankList->pointer = NULL;

	FILE *ifp = fopen("rank.txt", "r");
	if (ifp == NULL) {
		return;
	}
	
	else {
		fscanf(ifp, "%d", &rankSize);

		temp = rankList;

		for (int i = 0; i < rankSize; i++) {
			newNode = (Node*)malloc(sizeof(Node));
			fscanf(ifp, "%s %d", (newNode->name), &(newNode->score));
			newNode->pointer = NULL;
			rankList->pointer = newNode;
			rankList = rankList->pointer;
		}

		rankList = temp;
	}
	fclose(ifp);
}

void rank() {
	int x, y, i;
	Node* temp = NULL;
	char input[NAMELEN];
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	switch (wgetch(stdscr)) {
	case '1':
		x = 1;
		y = rankSize;
		echo();
		printw("X: ");
		scanw("%d", &x);
		printw("Y: ");
		scanw("%d", &y);
		noecho();
		printw("      name      |   score   \n");
		printw("----------------------------\n");
		if (x > y||x<1||y>rankSize) {
			printw("\nsearch failure: no rank in the list\n");
			break;
		}
		temp = rankList;
		for (i = 0; i < x; i++) {
			temp = temp->pointer;
		}
		for (i = 0; i <= (y-x); i++) {
			printw("%-18s| %d\n", temp->name, temp->score);
			temp = temp->pointer;
		}
		break;
	case '2':
		i = 0;
		echo();
		printw("input the name: ");
		scanw("%s", input);
		noecho();
		printw("      name      |   score   \n");
		printw("----------------------------\n");
		temp = rankList->pointer;
		while (temp != NULL) {
			if (strcmp(temp->name,input)==0) {
				printw("%-18s| %d\n", temp->name, temp->score);
				i++;
			}
			temp = temp->pointer;
		}
		if (i == 0) {
			printw("\nsearch failure: no name in the list\n");
		}
		break;
	case '3':
		echo();
		printw("input the rank: ");
		scanw("%d", &x);
		noecho();

		Node* temp1, * temp2;
		temp1 = rankList;
		temp2 = rankList->pointer;
		if (x > rankSize) {
			printw("\nsearch failure: the rank not in the list\n");
		}
		else {
			for (i = 1; i < x; i++) {
				temp1 = temp2;
				temp2 = temp2->pointer;
			}
			temp1->pointer = temp2->pointer;
			free(temp2);
			rankSize--;
			printw("\nresult: the rank delete\n");
		}
		break;
	default: break;
	}
	getch();
}

void writeRankFile() {
	FILE* ofp = fopen("rank.txt", "w");
	Node* temp;
	temp = rankList->pointer;
	fprintf(ofp, "%d\n", rankSize);
	if (rankSize == 0) {
		fclose(ofp);
		return;
	}
	while (temp != NULL) {
		fprintf(ofp, "%s %d\n", (temp->name), (temp->score));
		temp = temp->pointer;
	}
	fclose(ofp);

	temp = rankList->pointer;
	while (temp->pointer != NULL) {
		Node * delete = temp;
		temp = temp->pointer;
		free(delete);
	}
	free(temp);
	free(rankList);
}

void newRank(int score) {
	char tempName[NAMELEN];
	clear();
	echo();
	printw("your name: ");
	scanw("%s", tempName);
	noecho();

	Node* temp, * search1, *search2;
	temp = (Node*)malloc(sizeof(Node));
	strcpy(temp->name, tempName);
	temp->score = score;

	if (rankList->pointer == NULL) {
		temp->pointer = NULL;
		rankList->pointer = temp;
		rankSize++;
		return;
	}

	search1 = rankList;
	search2 = rankList->pointer;

	while (1) {
		if ((temp->score) >= (search2->score)) {
			temp->pointer = search2;
			search1->pointer = temp;
			rankSize++;
			break;
		}
		else if ((temp->score) < (search2->score)) {
			if (search2->pointer == NULL) {
				search2->pointer = temp;
				rankSize++;
				break;
			}
			else {
				search1 = search2;
				search2 = search2->pointer;
			}
		}
	}
}

void DrawRecommend(int y, int x, int blockID, int blockRotate) {
	// user code
}

int recommend(RecNode* root) {
	int max = 0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay() {
	// user code
}
