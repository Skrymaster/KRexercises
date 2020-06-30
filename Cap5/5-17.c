#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lines.h"
#include "quicksort.h"

#define CHARCOMP int (*)(char *, char *)
#define VOIDCOMP int (*)(void *, void *)

void parseargs(int argc, char *argv[]);
char **getsortdata(char *line);
int compare(char **s1, char **s2);

char *line(char *sortdata[]);
char *fieldspace(char *sortdata[]);
void fold(char *value);
void dirsort(char *value);
int strcmpr(char *, char *);
int numcmp(char *, char *);
int numcmpr(char *, char *);
void freestuff(char ***kvms, int nlines);

int *sortidxs;
int nsortflds;
int maxsortidx;
int (**compares)(char *, char *);
int *folds;
int *dirsorts;

int main(int argc, char *argv[])
{
	int i, nlines;
	char *buff, **lines, ***linedata;

	parseargs(argc, argv);

	if ((nlines = readlines(&buff, &lines)) == LNS_ERROR) {
		printf("input too big to sort\n");
		return 0;
	}

	linedata = malloc(nlines * sizeof(char **));
	for (i = 0; i < nlines; i++)
		linedata[i] = getsortdata(lines[i]);

	quicksort((void **)linedata, 0, nlines - 1, (VOIDCOMP)compare);

	for (i = 0; i < nlines; i++)
		lines[i] = line(linedata[i]);

	writelines(lines, nlines);

	freestuff(linedata, nlines);
	freelines(buff, lines);
	return 0;
}

int compare(char **sortdata1, char **sortdata2)
{
	int i, rslt = 0;

	for (i = 0; i < nsortflds && rslt == 0; i++)
		rslt = (*compares[i])(sortdata1[i], sortdata2[i]);
	return rslt;
}

void parseargs(int argc, char *argv[])
{
	int i;
	int maxsortcount = argc - 1;

	nsortflds = 0;
	sortidxs = malloc(maxsortcount * sizeof(int));
	compares = malloc(maxsortcount * sizeof(CHARCOMP));
	folds = malloc(maxsortcount * sizeof(int));
	dirsorts = malloc(maxsortcount * sizeof(int));

	argv++;
	for (i = 0; i < argc - 1; i++) {
		char *arg = argv[i];

		int fieldidx;
		int numeric = 0;
		int reverse = 0;
		int (*compare)(char *, char *);
		int fold = 0;
		int dirsort = 0;

		if (*arg == '-' && isdigit(*++arg)) {
			fieldidx = atoi(arg) - 1;
			while (*++arg) {
				if (*arg == 'n')
					numeric = 1;
				else if (*arg == 'r')
					reverse = 1;
				else if (*arg == 'f')
					fold = 1;
				else if (*arg == 'd')
					dirsort = 1;
			}
			if (numeric && reverse)
				compare = numcmpr;
			else if (numeric)
				compare = numcmp;
			else if (reverse)
				compare = strcmpr;
			else
				compare = (CHARCOMP)strcmp;
			maxsortidx =
				fieldidx > maxsortidx ? fieldidx : maxsortidx;
			sortidxs[nsortflds] = fieldidx;
			compares[nsortflds] = compare;
			folds[nsortflds] = fold;
			dirsorts[nsortflds] = dirsort;
			nsortflds++;
		}
	}
}

char **getsortdata(char *line)
{
	char *fieldspace = malloc((strlen(line) + 1) * sizeof(char));
	char *chr, *field;
	int fieldidx, i;

	char **tmpfields = malloc((maxsortidx + 2) * sizeof(char *));
	char **sortdata = malloc((nsortflds + 2) * sizeof(char *));

	strcpy(fieldspace, line);

	field = fieldspace;
	fieldidx = 0;
	for (chr = fieldspace; *chr; chr++) {
		if (*chr == '\t' || *chr == '\n') {
			*chr = '\0';
			if (fieldidx <= maxsortidx + 1)
				tmpfields[fieldidx] = field;
			field = chr + 1;
			fieldidx++;
		}
	}

	for (i = 0; i < nsortflds; i++) {
		field = tmpfields[sortidxs[i]];
		if (folds[i])
			fold(field);
		if (dirsorts[i])
			dirsort(field);
		sortdata[i] = field;
	}
	sortdata[nsortflds] = line;
	sortdata[nsortflds + 1] = fieldspace;

	free(tmpfields);
	return sortdata;
}

char *line(char *sortdata[])
{
	return sortdata[nsortflds];
}

char *fieldspace(char *sortdata[])
{
	return sortdata[nsortflds + 1];
}

void fold(char *value)
{
	while ((*value = toupper(*value)))
		value++;
}

void dirsort(char *value)
{
	char c, *write;
	write = value;
	while ((c = *value++))
		if (isalnum(c) || c == ' ' || c == '\n')
			*write++ = c;
	*write = '\0';
}

int strcmpr(char *s1, char *s2)
{
	return strcmp(s2, s1);
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int numcmpr(char *s1, char *s2)
{
	return numcmp(s2, s1);
}

void freestuff(char ***linedata, int nlines)
{
	int i;

	for (i = 0; i < nlines; i++) {
		free(fieldspace(linedata[i]));
		free(linedata[i]);
	}
	free(linedata);

	free(sortidxs);
	free(compares);
	free(folds);
	free(dirsorts);
}