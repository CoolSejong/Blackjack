//===========================================================================
// �� �� ���α׷�
// C�� ���� ���� �ݵ�� �˾ƾ� �� �͵�(����߸� ��Ű��), ���������
//===========================================================================
/*
	2021-05-25	����� �輼��
	������ �� �� ���α׷��� Ÿ�����ϸ鼭 ���α׷��� �帧�� ������ �� �ִ�.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// �� �� ī���� ���
#define CMAX 52
// Ű����� �Է��� �� �ִ� ������ ũ��
#define BUFF_SIZE 256

// ������ ī�带 ������ ����ü
struct input {
	//������ ī��
	int card[CMAX];
	//ī���� ��
	int num;
};

// ��ǻ�Ͱ� ī�带 �������ϴ�.
int comp(void);
// ����� ī�带 �������ϴ�.
int getcard(struct input *inp_card);
// ������ ī�带 ǥ���մϴ�.
void print_card(const struct input *inp_card, const char*card[]);
// ������ ����մϴ�.
int calc(const struct input *inp_card);

// ������ �ʱ�ȭ
#define randmize() srand(time(NULL))

//===========================================================================
// int main()
// ���
//   ���� ����, ���� ����
// �μ�
//   ����
// ��ȯ��
//   int ���� ���� �ÿ��� 0�� ��ȯ�մϴ�.
//===========================================================================

int main()
{
	// ī���� ����
	const static char *card[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8",
								"9", "10", "J", "Q", "K" };
	// ������ ī��
	int x;
	// ��ǻ���� ����
	int c_score;
	// ����� ����
	int h_score;
	// �Է��� ���ڿ�
	char in[BUFF_SIZE];
	// ����� ������ ī��
	struct input h_card = { {0}, 0 };

	printf("�� �� ���� \n");
	randmize();
	c_score = comp();

	x = getcard(&h_card);
	printf("'%s'�� ���������ϴ�.\n", card[x]);
	printf("�� �� �� �������ڽ��ϱ�? (y / n): ");

	while (h_card.num < CMAX && fgets(in, BUFF_SIZE, stdin) != NULL) {
		if (strncmp(in, "y", 1) == 0) {
			x = getcard(&h_card);
			printf("'%s'�� ���������ϴ�.", card[x]);
			print_card(&h_card, card);
			printf("�� �� �� �������ڽ��ϱ�? (y / n): ");
		}
		else if (strncmp(in, "n", 1) == 0)
			break;
		else
			printf("y �Ǵ� n�� �Է��ϼ���.\n");
	}

	h_score = calc(&h_card);
	printf("����� %d���Դϴ�. ��ǻ�ʹ� %d ���Դϴ�.\n", h_score, c_score);

	if (c_score <= 21 && (h_score > 21 || c_score > h_score))
		printf("��ǻ�Ͱ� �̰���ϴ�!\n");
	else if (h_score <= 21 && (c_score > 21 || h_score > c_score))
		printf("����� �̰���ϴ�!\n");
	else
		printf("���º�\n");

	return 0;
}

//===========================================================================
// int comp(void)
// ���
//   ��ǻ�Ͱ� ī�带 ��������.
// �μ�
//   ����
// ��ȯ��
//   int ������ ī��
//===========================================================================

int comp(void)
{
	return rand() % 8 + 16;		// xxx
}

//===========================================================================
// int getcard(struct input *h_card)
// ���
//   �ΰ��� ������ ī��, ������ ī�带 inp ����ü�� �����Ѵ�.
// �μ�
//   struct input *h_card;	������ ī���� ������
// ��ȯ��
//   int ������ ī��
//===========================================================================
int getcard(struct input *h_card)
{
	int x;	// ������ ī��

	x = rand() % 13 + 1;
	h_card->card[h_card->num] = x;
	++(h_card->num);

	return x;
}

//===========================================================================
// void print_card(const struct input *inp_card, const char *card[]);
// ���
//   ������ ī�带 ǥ���Ѵ�.
// �μ�
//   const struct input *inp_card;	������ ī���� ������
//   const char *card[];	ī���� ����
// ��ȯ��
//   ����
//===========================================================================

void print_card(const struct input *inp_card, const char *card[])
{
	int i; // �ݺ����� ����

	printf("���ݱ��� ������ ī��� ");
	for (i = 0; i < inp_card->num; ++i)
		printf("%s ", card[inp_card->card[i]]);
	printf(" �Դϴ�.\n");
}

//===========================================================================
// int calc(const struct input *inp_card)
// ���
//   ������ ī���� ������ ����Ѵ�.
//     ��A�� 1�� �Ǵ� 11��
//     ��2~10�� ������ ���ڰ� �����̴�.
//     ��J,Q,K�� 10��
// �μ�
//   const struct input *inp_card;	������ ī���� ������
// ��ȯ��
//   int ���� ����
//===========================================================================

int calc(const struct input *inp_card)
{
	// ī���� ���� : 0            0  A  2  3  4  5  6  7  8  9  10  J   Q   K
	const static int ncard[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
	int i;			// �ݺ����� ����
	int n1 = 0;		// A ī���� ���
	int score = 0;	// �հ� ����

	for (i = 0; i < inp_card->num; ++i) {
		score += ncard[inp_card->card[i]];
		if (inp_card->card[i] == 1)	// ī�尡 A�� ���
			++n1;
	}

	while (n1-- > 0)	// ī�尡 A�� ����� ���� ó��
		if (score <= (21 - 10))
			score += 10;

	return score;
}