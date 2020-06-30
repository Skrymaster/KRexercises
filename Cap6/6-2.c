#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXWORD 1000
#define DEFAULT_COMP_LEN 6


struct tnode
{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct simroot
{
	struct simword *firstword;
	struct simroot *nextroot;
};

struct simword
{
	char *word;
	int count;
	struct simword *nextword;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(const struct tnode *);
int getword(char *, int);
struct simroot *addroot(struct simroot *, struct tnode *, int);
struct simroot *parse(struct tnode *, int);
void printlist(struct simroot *, int);
void printwords(struct simword *);

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	struct simroot *listroot;
	int len;
	
	root = NULL;
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			root = addtree(root, word);
	
	if(argc == 1)
		len = DEFAULT_COMP_LEN;
	else if(argc == 2)
		len = atoi(argv[1]);
	else {
		printf("Incorrect number of arguments.\n");
		return 1;
	}
	
	listroot = NULL;
	listroot = parse(root, len);
	treeprint(root);
	printf("\nDuplicate list:\n\n");
	printlist(listroot, len);
	
	return 0;
} 


struct simroot *parse(struct tnode *node, int len)
{
	struct tnode *temp;
	int this_len;
	static struct simroot *root = NULL; 
	
	if(node == NULL)
		return NULL;
	
	this_len = strlen(node->word);
	
	parse(node->left, len); 
	
	temp = node->left;
	if(temp != NULL) {
		while(temp->right != NULL)
			temp = temp->right;
		if(this_len >= len && strncmp(temp->word, node->word, len) == 0) {
			root = addroot(root, temp, len);
			addroot(root, node, len);
		}
	}
	
	temp = node->right;
	if(temp != NULL) {
		while(temp->left != NULL)
			temp = temp->left;
		if(this_len >= len && strncmp(temp->word, node->word, len) == 0) {
			root = addroot(root, node, len);
			addroot(root, temp, len);
		}
	}
	
	parse(node->right, len);
	
	return root;
}


void printlist(struct simroot *p, int len)
{
	int i;
	if(p == NULL)
		return;
	for(i = 0; i < len; ++i)    /* print the root */
		putchar(p->firstword->word[i]);
	putchar('\n');
	printwords(p->firstword);   /* print the list of words */
	printlist(p->nextroot, len); /* print the next root/list */
}

void printwords(struct simword *p)
{
	printf("  %4d %s\n", p->count, p->word);
	if(p->nextword != NULL)
		printwords(p->nextword);
}

struct tnode *talloc(void);
char *strdup(char *);
struct simword *walloc(struct simword *, struct tnode *);
void addword(struct simword *, struct tnode *);


struct simroot *addroot(struct simroot *p, struct tnode *n, int len)
{
	if(p == NULL) {
		p = (struct simroot *) malloc(sizeof(struct simroot));
		p->nextroot = NULL;
		p->firstword = walloc(p->firstword, n);
	}
	else if(strncmp(p->firstword->word, n->word, len) == 0)
		addword(p->firstword, n);
	else
		p->nextroot = addroot(p->nextroot, n, len);
	return p;
}


void addword(struct simword *p, struct tnode *n)
{
	if(strcmp(p->word, n->word) == 0)
		return;
	if(p->nextword == NULL)
		p->nextword = walloc(p->nextword, n);
	else
		addword(p->nextword, n);
}

struct simword *walloc(struct simword *p, struct tnode *n)
{
	p = (struct simword *) malloc(sizeof(struct simword));
	if(p != NULL) {
		p->word = n->word;
		p->count = n->count;
		p->nextword = NULL;
	}
	return p;
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	static int line_beg = 1;
	static int after_slash = 0;
	int after_star = 0;
	
	if(isspace(c = getch()))
		after_slash = 0;
	while(isspace(c)) {
		if(c == '\n')
			line_beg = 1;
		c = getch();
	}
	
	if(c != EOF)
		*w++ = c;
	
	if(c == '#' && line_beg == 1) { 
		while((c = getch()) != '\n' && c != EOF) 
			;
		return getword(word, lim);
	}
	line_beg = 0;
	
	if(c == '\\') 
		after_slash = after_slash ? 0 : 1;
	
	else if(c == '/' ) {
		if((c = getch()) == '*' && !after_slash) {
			while((c = getch()) != EOF) {
				if(c == '/') {
					if(after_star) 
						return getword(word, lim);
				}
				else if(c == '*' && !after_slash)
					after_star = 1;
				else if(c == '\\')
					after_slash = after_slash ? 0 : 1; 
				else {
					after_star = 0;
					after_slash = 0;
				}
			}
		} 
		
		after_slash = 0; 
		if(c != EOF)
			ungetch(c);
	}
	
	else if(c == '\"') {
		if(!after_slash) {  
			--w; 
			while((c = getch()) != EOF) {
				if(c == '\"' && !after_slash)
					break;
				else if(c == '\\')
					after_slash = after_slash ? 0 : 1;
				else
					after_slash = 0;
				*w++ = c;
			}
			*w = '\0';
			if(c == EOF)
				return EOF;
			else
				return getword(word, lim); 
		}
		after_slash = 0;
	}
	
	if(!isalpha(c) && c != '_') { 
		*w = '\0';
		if(c != '\\')
			after_slash = 0;
		return c;
	}
	
	after_slash = 0;
	
	for( ; --lim > 0; ++w) 
		if(!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

// cod din carte \/
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	
	if(p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if(cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void treeprint(const struct tnode *p)
{
	if(p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}

#define BUFSIZE 100

char buf[BUFSIZE]; 
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
	return;
}