#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int PassOrFail(int score) {
    if (score >= 50) {
        return 1; // 50점 이상이면 1 (Pass) 반환
    }
    else {
        return 0; // 50점 미만이면 0 (Fail) 반환
    }
}

int main() {
    int studentScore;

    printf("우리 수업의 예상평균점수를 입력하세요: ");
    scanf("%d", &studentScore);

    int result = PassOrFail(studentScore);

    if (result == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다...  재시험이다...\n");
    }

    return 0;
}