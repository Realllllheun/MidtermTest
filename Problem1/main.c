#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int PassOrFail(int score) {
    if (score >= 50) {
        return 1; // 50�� �̻��̸� 1 (Pass) ��ȯ
    }
    else {
        return 0; // 50�� �̸��̸� 0 (Fail) ��ȯ
    }
}

int main() {
    int studentScore;

    printf("�츮 ������ ������������� �Է��ϼ���: ");
    scanf("%d", &studentScore);

    int result = PassOrFail(studentScore);

    if (result == 1) {
        printf("����� �����ϴ�!\n");
    }
    else {
        printf("�츮�� ���ߴ�...  ������̴�...\n");
    }

    return 0;
}