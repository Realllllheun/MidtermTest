#include <windows.h>  // 콘솔 관련 구조체 사용을 위한 헤더
#include <stdio.h>    // printf 사용을 위한 헤더

// 커서 이동 함수 (ANSI)
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// 커서 이동 함수 (Windows API)
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 색상 설정 함수 (Windows API)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int bgColorCode)
{
    int textColor = 15; // 흰색 텍스트
    int color = textColor + (bgColorCode << 4); // 배경색 + 텍스트

    for (int i = 0; i < height; i++) {
        gotoxy(startX, startY + i);
        for (int j = 0; j < width; j++) {
            // X 버튼 출력 위치
            if (i == 1 && j == width - 5) {
                int closeBtnColor = 15 + (4 << 4);  // 흰글씨 + 빨간 배경
                setColor(closeBtnColor);
                printf("[X]");
                j += 2; // [X] 출력했으니 3칸 건너뜀
                continue;
            }

            setColor(color);

            if (i == 0 || i == height - 1) {
                // 윗줄, 아랫줄
                if (j == 0 || j == width - 1) {
                    printf("|");
                }
                else {
                    printf("-");
                }
            }
            else if (i == 1) {
                // 이름 들어가는 줄
                if (j == 0 || j == width - 1) {
                    printf("|");
                }
                else if (j == 1) {
                    printf("%s", title);
                    j += strlen(title) - 1;
                }
                else {
                    printf(" ");
                }
            }
            else {
                // 내부 줄
                if (j == 0 || j == width - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
    }

    setColor(7); // 기본 색상 복원
}


void BackGroundColor()
{
    // 배경 크기 설정
    int width = 80;
    int height = 25;

    // 여백 설정
    int left_margin = 2;
    int right_margin = 2;
    int top_margin = 1;
    int bottom_margin = 1;

    // ANSI 파란색 배경 설정
    printf("\033[44m");

    // 여백 제외 영역 출력 (공백으로 색칠)
    for (int row = top_margin + 1; row <= height - bottom_margin; row++) {
        // 커서를 해당 행의 왼쪽 여백 + 1 위치로 이동
        printf("\033[%d;%dH", row, left_margin + 1);
        for (int col = left_margin + 1; col <= width - right_margin; col++) {
            printf(" ");
        }
    }

    // 마지막 줄 (회색 배경으로 채우기)
    printf("\033[100m"); // 밝은 회색 배경
    printf("\033[%d;%dH", height, left_margin + 1);
    for (int col = left_margin + 1; col <= width - right_margin; col++) {
        printf(" ");
    }

    // 색상 원래대로 복원 (흰 글씨, 검정 배경)
    printf("\033[0m");

    // 마지막 줄로 커서 옮기기
    printf("\033[%d;1H", height);
}

void MousePos(int backgroundWidth, int backgroundHeight)
{
    POINT mousePos;       // 마우스 위치
    COORD prevPos = { -1, -1 }; // 이전 위치 저장
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // ANSI 모드 활성화 (색상 등)
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    while (1) {
        GetCursorPos(&mousePos);

        // 콘솔 창 내부 좌표로 변환 (대략적인 비율 사용)
        int x = mousePos.x / 9;
        int y = mousePos.y / 19;

        // 마우스 커서가 배경 영역 내에 있는지 확인
        if (x >= 0 && x < backgroundWidth && y >= 0 && y < backgroundHeight) {
            // 이전 커서 위치 복원 (배경색으로 덮어쓰기)
            if (prevPos.X != -1 && prevPos.Y != -1) {
                gotoxy(prevPos.X, prevPos.Y);
                printf("\033[44m \033[0m"); // 파란색 배경으로 공백 출력
            }

            // 현재 위치에 파란색 배경을 가진 '<' 마우스 모양 출력
            gotoxy(x, y);
            printf("\033[44m\033[30m<\033[0m"); // 파란색 배경 + 검정 텍스트의 < 마우스 모양

            prevPos.X = x;
            prevPos.Y = y;

            // 위치 텍스트 출력 (고정 위치에)
            gotoxy(0, 0);
            printf("마우스 위치: (%d, %d)          ", x, y); // 공백으로 덮어쓰기
        }

        // ESC 키 누르면 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(30);
    }

    // 커서 다시 보이게
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


int main()
{
    // 배경 크기 설정
    int backgroundWidth = 80;
    int backgroundHeight = 25;

    // ANSI 모드 활성화 (BackGroundColor 함수에서도 사용)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    BackGroundColor();
    // 창 3개 출력
    drawConsoleWindow(5, 2, 30, 10, "나의 멋진 윈도우", 1;  // 파란 배경
    drawConsoleWindow(20, 8, 30, 10, "나의 멋진 윈도우", 2); // 초록 배경
    drawConsoleWindow(35, 14, 30, 10, "나의 멋진 윈도우", 4); // 노란 배경
    MousePos(backgroundWidth, backgroundHeight); // 배경 크기를 넘겨줌

    return 0;
}
