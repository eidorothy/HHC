// bingo01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

const int BINGO_SIZE = 5;

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

void mixBingo(int(*bingo)[5], int size)    //그나마 할 만 했다
{
    int temp;

    for (int i = 0; i < 10000; ++i) {

    }
    
    // for문 중첩할 필요 X (i, j 사용 안 하고 있음)
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            //i랑 j 인덱스는 정해져 있잖아?
            //그러면 섞을 때 나도 모르는 0~5 무작위 인덱스가 필요하네
            //계속 난수를 받기도 해야 하고
            int rand1 = rand() % 5;
            int rand2 = rand() % 5;
            int rand3 = rand() % 5;
            int rand4 = rand() % 5;

            // 같은 수가 나오면 섞이지 않는 경우

            temp = bingo[rand1][rand2];
            bingo[rand1][rand2] = bingo[rand3][rand4];
            bingo[rand3][rand4] = temp;

            //std::swap(); 사용하면 편함
        }
    }
}

void showBingo(int(*bingo)[5], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // 999인 경우 O로 표시해도 좋다, \t로 바꿔 주기
            if (bingo[i][j] == 999)
                cout << "O\t";
            else 
                cout << bingo[i][j] << "\t";
        }
        cout << endl;
    }
}

void showBingoAdd(int(*bingo)[5], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << (bingo + i)[j] << " ";
        }
        cout << endl;
    }
}

void checkNum(int(*bingo)[5], int size, int input)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (bingo[i][j] == input) {
                bingo[i][j] = 999;
                return;
            }
        }
    }
}

bool checkBingo(int(*bingo)[BINGO_SIZE])  //미완성 함수 ************************************************************************
{
    int garoCount = 0;
    int seroCount = 0;
    int count = 0;

    for (int i = 0; i < BINGO_SIZE; i++)
    {
        bool rowBingo = true;

        for (int j = 0; j < BINGO_SIZE; j++)  //가로줄 5개면 빙고
        {
            // 999 0 1 2 3
            if (bingo[i][j] != 999) {
                rowBingo = false;
                break;
            }
        }

        if (rowBingo)
            count++;
    }
    
    // 세로 체크하는 for문

    if (count == 5)
        return true;
    else
        return false;
    //세로줄 5개면 빙고
}

int main()
{
    srand((unsigned)time(0));   //'인수': 'time_t'에서 'unsigned int'(으)로 변환하면서 데이터가 손실될 수 있습니다. 오류 => unsigned 키워드 붙이기

    int bingo[BINGO_SIZE][BINGO_SIZE];
    int bingoAI[BINGO_SIZE][BINGO_SIZE];
    bool bingoOK = false;
    //bingo는 2차원 배열이고 포인터나 참조 형식을 사용해야만 값을 조작할 수 있다

    //2차원 배열이라도 1차원 배열과 같이 일렬로 메모리에 저장된다
    //bingo = 2차원 배열의 시작 주소 = bingo[0][0]의 주소
    //*bingo = 
    //&bingo = bingo를 담고 있는 메모리의 주소

    while (true)
    {
        system("cls");

        makeBingo(bingo);   //얘는 한 번 생성되면 system("cls")로 초기화되면 안되잖아
        mixBingo(bingo, BINGO_SIZE);    //얘도 한 번 생성되면 system("cls")로 초기화되면 안되잖아

        while (!bingoOK)
        {
            system("cls");

            showBingo(bingo, BINGO_SIZE);
            //showBingoAdd(bingo, BINGO_SIZE);

            cout << endl;

            cout << "아무 숫자를 입력하세요" << endl;
            cout << ">> ";

            int input;
            cin >> input;

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

            checkNum(bingo, BINGO_SIZE, input);
            bingoOK = checkBingo(bingo);    //bingo 개수를 체크(미완성)

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
    }

    return 0;
}