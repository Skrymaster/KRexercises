int main(void)
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if (needparens())
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invaid input at %s\n", token);
		printf("%s\n", out);
	}
	return 0;
}

int needparens(void)
{
	int c1, c2, rslt;

	rslt = 0;
	if ((c1 = getch()) == ' ') {
		if ((c2 = getch()) == '(' || c2 == '[')
			rslt = 1;
		ungetch(c2);
	}
	ungetch(c1);
	return rslt;
}