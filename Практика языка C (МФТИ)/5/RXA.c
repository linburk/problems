#include <stdio.h>
#include <stdlib.h>

int process(void);

int main()
{
	int res;
	res = process();
	printf("%d\n", res);
	return 0;
}

void set_automaton(int aut[5][3])
{
	aut[0][0] = 0;
	aut[0][1] = 1;
	aut[0][2] = 4;

	aut[1][0] = 0;
	aut[1][1] = 1;
	aut[1][2] = 2;

	aut[2][0] = 4;
	aut[2][1] = 2;
	aut[2][2] = 3;

	aut[3][0] = 4;
	aut[3][1] = 3;
	aut[3][2] = 2;

	aut[4][0] = 4;
	aut[4][1] = 4;
	aut[4][2] = 4;
}

int process(void)
{
	char c;
	int automaton[5][3];
	int is_accept[5] = { 0, 1, 1, 1, 0 };
	int state = 0;
	set_automaton(automaton);
	for (;;) {
		c = getchar();
		if (c > 'c' || c < 'a')
			break;
		state = automaton[state][c - 'a'];
	}
	return is_accept[state];
}
