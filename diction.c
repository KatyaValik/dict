#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**Maximem length of string*/
#define MAX_STRING_LEN	100

/*Maximum number of words*/
#define MAX_WORDS 100000

typedef struct word *list;
struct word
{
	char word[MAX_STRING_LEN];
	int count;
	list next;
};

struct mas
{
	char nword[MAX_STRING_LEN];
	int ncount;
};

typedef struct node *tree;

struct node
{
	list words;
	tree left;
	tree right;
};

void wordtolower(char *dst, char *src)
{
	int i;
	for (i = 0; i <= strlen(src); i++)
	{
		dst[i] = tolower(src[i]);
	};
	dst[i] = 0;
}

void free_list(list L)
{
	if (L->next != NULL)
		free_list(L->next);

	free(L);
}

tree ftree(tree T, char* s)
{
	char str[MAX_STRING_LEN];

	if (T == NULL)
	{
		T = calloc(1, sizeof(struct node));

		T->words = calloc(1, sizeof(struct word));

		wordtolower(str, s);

		if (islower(s[0]))
		{
			strcpy(T->words->word, str);
			T->words->count = 1;
		}
		else
		{
			strcpy(T->words->word, str);
			T->words->next = calloc(1, sizeof(struct word));
			strcpy(T->words->next->word, s);
			T->words->next->count++;
		};
		return (T);
	}
	else
	{
		char str[MAX_STRING_LEN];
		wordtolower(str, s);
		list L = T->words;
		list Lstart = L;
		if (strcmp(L->word, str) == 0)
		{
			if (L->count > 0)
			{
				L->count++;
				return (T);
			}
			else
			{
				if (islower(s[0]))
				{
					int k = 1;
					while (L != NULL)
					{
						k = k + L->count;
						L = L->next;
					};
					free_list(Lstart->next);
					Lstart->next = NULL;
					Lstart->count = k;
					return (T);
				}

				while (L != NULL)
				{
					if (strcmp(L->word, s) == 0)
					{
						L->count++;
						return (T);
					};
					L = L->next;
				};
				list p = malloc(sizeof(struct word));
				strcpy(p->word, s);
				p->count = 1;
				L = Lstart;
				p->next = L->next;
				L->next = p;
				return (T);
			}
		}
		else
		{
			if (strcmp(T->words->word, s) > 0)
			{
				T->right = ftree(T->right, s);
				return T;
			}
			else
			{
				T->left = ftree(T->left, s);
				return T;
			}
		}
	}

	return T;
}

int print_tree(tree T, struct mas* mas_words, int mas_size)
{
	if (T == NULL)
		return mas_size;

	list L = T->words;
	if (L->count > 0)
	{
		mas_words[mas_size].ncount = L->count;
		strcpy(mas_words[mas_size].nword, L->word );
		mas_size++;
	}
	else
	{
		L = L->next;
		while (L)
		{
			strcpy(mas_words[mas_size].nword, L->word );
			mas_words[mas_size].ncount = L->count;
			mas_size++;
			L = L->next;
		}
	}

	printf("goto left\n");
	mas_size = print_tree(T->left, mas_words, mas_size);
	printf("goto right\n");

	return print_tree(T->right, mas_words, mas_size);
}

int compar(const void * c1, const void * c2)
{
	struct mas *m1 = (struct mas*) c1;
	struct mas *m2 = (struct mas*) c2;

	if (m1->ncount > m2->ncount)
		return 1;

	if (m1->ncount < m2->ncount)
		return -1;

	return 0;
}

void sort_mas(struct mas* mas_words, int size)
{
	qsort(mas_words, size, sizeof(struct mas), compar);
}

void print_mas_words( struct mas* mas_words, int size)
{
	for( int i = 0; i < size; i++ )
	{
		printf("word %d\tcount=%d\t\t%s\n", i, mas_words[i].ncount, mas_words[i].nword);
	}
}

int main()
{
	tree T = NULL;
	char c;
	char s[MAX_STRING_LEN], str[MAX_STRING_LEN];
	struct mas* mas_words;
	int k, p;
	memset(s, 0, sizeof(s));
	memset(str, 0, sizeof(str));
	k = 0;

	mas_words = calloc( MAX_WORDS, sizeof(struct mas));

	while (scanf("%c", &c) != EOF)
	{
		if (isalnum(c) || (c == '_') || (c == '@') || (c == '$') || (c == '%'))
		{
			s[k] = c;
			k++;
		}
		else
		{
			/*Exit on empty string*/
			if ((k == 0) && (c == '\n'))
				break;

			T = ftree(T, s);
			k = 0;
			if ((c != ' ') && (c != '\n'))
			{
				str[0] = c;
				T = ftree(T, str);
			}
			memset(s, 0, sizeof(s));
		}
	}

	k = print_tree(T, mas_words, 0);

	sort_mas(mas_words, k);
	print_mas_words(mas_words, k);


	free( mas_words );

	return 0;
}

