#include <iostream>
using namespace std;

const int BINGO_SIZE = 5;   //빙고판의 크기(피드백 후 변경 내용)*****

void makeBingo(int(*bingo)[BINGO_SIZE])
{
    //빙고 만들기
    for (int i = 0; i < BINGO_SIZE; i++)  //i가 행
    {
        for (int j = 0; j < BINGO_SIZE; j++) //j가 열
        {
            bingo[i][j] = i * BINGO_SIZE + j + 1;
        }
    }
}

void mixBingo(int(*bingo)[BINGO_SIZE], int size)
{
    int temp;

    // 심화 피드백 - 셔플 알고리즘 찾아보는 것을 추천
    // 직접 구현해 보는 것도 좋지만, 알고리즘도 한번씩 체크해 보는 것이 좋다
    // 커누스(Knuth), 피셔-예이츠(Fisher-Yates) 등...
    for (int i = 0; i < 10000; ++i)
    {
        //무작위 인덱스 4개 받아 섞기
        int rand1 = rand() % 5;
        int rand2 = rand() % 5;
        int rand3 = rand() % 5;
        int rand4 = rand() % 5;

        swap(bingo[rand1][rand2], bingo[rand3][rand4]);
    }
}

void showBingo(int(*bingo)[BINGO_SIZE])
{
    for (int i = 0; i < BINGO_SIZE; i++)
    {
        for (int j = 0; j < BINGO_SIZE; j++)
        {
            if (bingo[i][j] == 999)
                cout << "X\t";
            else
                cout << bingo[i][j] << "\t";
        }
        cout << endl;
    }
}

void checkNum(int(*bingo)[BINGO_SIZE], int input)
{
    for (int i = 0; i < BINGO_SIZE; i++)
    {
        for (int j = 0; j < BINGO_SIZE; j++)
        {
            if (bingo[i][j] == input) {
                bingo[i][j] = 999;
                return;
            }
        }
    }
}

int checkBingo(int(*bingo)[BINGO_SIZE])
{
    int count = 0;

    bool degakBingo1 = true, degakBingo2 = true;

    // 피드백 - for문 중복 코드 정리
    for (int i = 0; i < BINGO_SIZE; i++)
    {
        bool rowBingo = true, colBingo = true;

        for (int j = 0; j < BINGO_SIZE; j++) {
            if (bingo[i][j] != 999) 
                rowBingo = false;  // 가로 검사
            if (bingo[j][i] != 999) 
                colBingo = false;  // 세로 검사
        }

        if (rowBingo) 
            count++;
        if (colBingo) 
            count++;

        // 대각선 검사
        if (bingo[i][i] != 999)                     // 왼쪽 위 -> 오른쪽 아래
            degakBingo1 = false;
        if (bingo[i][BINGO_SIZE - 1 - i] != 999)    // 오른쪽 위 -> 왼쪽 아래
            degakBingo2 = false;
    }

    if (degakBingo1) 
        count++;

    if (degakBingo2) 
        count++;

    return count;
}

int checkAI(int(*bingoAI)[BINGO_SIZE])  //AI의 기술
{
    //1. 가로 -> 세로 -> 대각선 순서로 5칸을 채우기 위해 필요한 칸이 제일 적은 줄 찾기 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //2. 가운데부터 채우기(겹치는 부분이 많은 곳)
    //3. 꼭짓점 4군데 먼저 채우기
    //4. 플레이어가 입력한 값을 토대로 플레이어 빙고판을 예측해서 플레이어가 빙고가 안 되는 곳에서 AI 빙고가 되는 곳 고르기

    int best = 0;
    int bestX = 0;
    int bestY = 0;
    int bestXCount = 0;
    int bestYCount = 0;
    // 피드백 - 의도를 명확하게 알 수 있는 변수 네이밍 사용
    int temp1 = BINGO_SIZE;
    int temp2 = BINGO_SIZE;
    int temp3 = 0;
    int temp4 = 0;

    //가로, 세로 세서 빙고가 되기 위해 필요한 칸 개수 세서 개수가 적은 쪽일 수록 최선
    //빙고가 되지 않았는데 되는 줄이 있다면 우선 먹기(XCount가 4보다 낮고 1에 가까울수록 좋음)
    for (int i = 0; i < BINGO_SIZE; i++)
    {
        bestXCount = 0;

        for (int j = 0; j < BINGO_SIZE; j++)
        {
            if (bingoAI[i][j] != 999) {
                bestXCount++;
            }
        }

        //i번째 가로줄이 최선인지 판별하는 구문
        if (bestXCount > 0 && bestXCount != BINGO_SIZE)   //1개 이상 칸이 지워졌으며 빙고가 된 줄이 아니라면
        {
            if (bestXCount <= temp1)  //i번째 줄에 지울 칸이 이전에 빙고가 되기 위해 가장 적게 지워야 했던 줄의 칸 수보다 적으면
                //<=는 값이 같으면 최신 인덱스로 갱신하고 <는 값이 같으면 윗 인덱스를 우선한다
            {
                temp1 = bestXCount;
                bestX = i;
            }
        }
    }

    for (int i = 0; i < BINGO_SIZE; i++)
    {
        bestYCount = 0;

        for (int j = 0; j < BINGO_SIZE; j++)
        {
            if (bingoAI[j][i] != 999) {
                bestYCount++;
            }
        }

        //i번째 가로줄이 최선인지 판별하는 구문
        if (bestYCount > 0 && bestYCount != BINGO_SIZE)   //1개 이상 칸이 지워졌으며 빙고가 된 줄이 아니라면
        {
            if (bestYCount <= temp2)
                //<=는 값이 같으면 최신 인덱스로 갱신하고 <는 값이 같으면 윗 인덱스를 우선한다
            {
                temp2 = bestYCount;
                bestY = i;
            }
        }
    }

    for (int i = 0; i < BINGO_SIZE; i++)
    {
        if (bingoAI[i][i] != 999)
            temp3++;
    }

    for (int i = 0; i < BINGO_SIZE; i++)    //<-방향 대각선
    {
        if (bingoAI[i][BINGO_SIZE - 1 - i] != 999)
        {
            temp4++;
        }
    }

    cout << "----------------------- AI -----------------------" << endl << endl;
    cout << temp1 << "개만 지우면 빙고가 되는 " << bestX << "번 가로줄과" << endl;
    cout << temp2 << "개만 지우면 빙고가 되는 " << bestY << "번 세로줄이 있네요" << endl
        << "왼쪽 대각선은 " << temp3 << "개를 지워야 되고" << endl
        << "오른쪽 대각선은 " << temp4 << "개를 지워야 하네요" << endl << "제 차례가 오면 저는 ";

    // 피드백 - temp1 == temp2와 동일한 코드이기 때문에 묶었고
    // 대각선도 고려할 줄 아는 AI가 되어야 한다 (이것은 TODO)
    // 
    // 특별한 의미를 지닌 주석들이 있다, 활용해 봐도 좋음
    // TODO : 당장 구현하기 어려운 것, 추후 해야 하는 일 등
    // FIXME : 문제가 있는 코드라서 추후에 수정/개선해야 함
    if (temp1 <= temp2)
    {
        bool check = false;

        while (!check)
        {
            for (int i = 0; i < BINGO_SIZE; i++)
            {
                if (bingoAI[bestX][i] != 999) {
                    cout << bingoAI[bestX][i] << "을(를) 지우겠습니다" << endl;
                    best = bingoAI[bestX][i];
                    bingoAI[bestX][i] = 999;
                    check = true;
                    break;
                }
            }
        }
    }
    else
    {
        bool check = false;

        while (!check)
        {
            for (int i = 0; i < BINGO_SIZE; i++)
            {
                if (bingoAI[i][bestY] != 999) {
                    cout << bingoAI[i][bestY] << "을(를) 지우겠습니다" << endl;
                    best = bingoAI[i][bestY];
                    bingoAI[i][bestY] = 999;
                    check = true;
                    break;
                }
            }
        }
    }
    cout << endl << "--------------------------------------------------" << endl;

    return best;
}

int main()
{
    srand((unsigned)time(0));   //'인수': 'time_t'에서 'unsigned int'(으)로 변환하면서 데이터가 손실될 수 있습니다. 오류 => unsigned 키워드 붙이기

    int bingo[BINGO_SIZE][BINGO_SIZE];
    int bingoAI[BINGO_SIZE][BINGO_SIZE];    //AI의 빙고판
    int bingoCount = 0;
    int bingoCountAI = 0;
    bool bingoOK = false;
    int test = 0;

    makeBingo(bingo);
    mixBingo(bingo, BINGO_SIZE);

    makeBingo(bingoAI);
    mixBingo(bingoAI, BINGO_SIZE);  //AI의 빙고판 만들기

    while (bingoCount < 3)
    {
        system("cls");

        showBingo(bingo);
        cout << endl;
        cout << "\t  플레이어 빙고판" << endl;

        cout << endl;
        cout << "플레이어 빙고 개수 : " << bingoCount << endl;
        cout << endl;
        cout << "AI 빙고 개수 : " << bingoCountAI << endl;
        cout << endl;


        showBingo(bingoAI);
        cout << endl;
        cout << "\t     AI 빙고판" << endl;
        cout << endl;

        checkAI(bingoAI);
        cout << "아무 숫자를 입력하세요 >> ";


        int input;
        cin >> input;

        /*if (input == checkAI(bingoAI))
            break;*/
            /*
            int* p = nullptr; // GetUser();
            if (!p)
                return;
            */

            // 오버플로우로 인한 버퍼 비우기
        if (cin.fail() || input < 1 || input > 25) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        /*
        // 이런 방법도 있다
        if (input < 1 || input > 25) {
            continue;
        }
        */

        checkNum(bingo, input); //빙고판에 있는 숫자인지 체크
        bingoCount = checkBingo(bingo);

        checkNum(bingoAI, input);
        bingoCountAI = checkBingo(bingoAI);

        // AI의 빙고 체크하는 로직
        // 난수를 입력 받는 AI
        // [내가 가진 빙고 수 중에 가장 유리한 걸 고르는 게] 똑똑한 AI
        // == 줄 별로 검사하는 로직 (가로, 세로, 대각선)
        // 가로도 3개짜리 줄이 있고 / 세로도 3개짜리가 있을 때 어떤 걸 선택할까요?? << 구현하는 사람이 우선순위


        /* 희천님 코드
        // 입력 범위 체크
        if (input <= 25)    // 0
            checkNum(bingo, BINGO_SIZE, input);
        else
            cout << "잘못 입력" << endl;

        bingoOK = checkBingo(bingo);    //bingo 개수를 체크(미완성)
        */
    }

    system("cls");
    if (bingoCount == 3)
        cout << "승리!" << endl;
    else
        cout << "패배..." << endl;

    return 0;
}