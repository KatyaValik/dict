#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct word *list;
	struct word {
		char word[100];
		int count;
		list next;
	};

struct mas {
	char nword;
	int ncount;
} mas[100000];




typedef struct node *tree;
	struct node {
		list words;
		tree left;
		tree right;
	};

void wordtolower(char *dst, char *src) {
	int i;
	for ( i=0; i<=strlen(src); i++) {
		dst[i] = tolower(src[i]);
	};
	dst[i] = 0;
};



tree ftree(tree T,char s[100]) {
	if (T==NULL) {
		tree T=malloc(sizeof(struct node));
		char str;
		wordtolower(str,s);
		if (islower(s[0])) {
			strcpy(T->words->word,str);
			T->words->count=1;
			T->words->next=NULL;
			T->left=NULL;
			T->right=NULL;
			return(T);
	    } else {
		strcpy(T->words->word,str);
		strcpy(T->words->next->word,s);
		T->words->count=0;
		T->words->next->count=1;
		T->left=NULL;
		T->right=NULL;
		T->words->next->next=NULL;
	    };
	} else {
		char str;
		wordtolower(str,s);
		list L=T->words;
		list Lstart=L;
		if (strcmp(L->word,str)==0) {
			if (L->count>0) {
				L->count++;
				return(T);
			} else {
				if (islower(s[0])) {
					int k=1;
					while (L!=NULL) {
						k=k+L->count;
						L=L->next;
					};
					Lstart->next=NULL;
					Lstart->count=k;
					T->words=Lstart;
					return(T);
				};
			};
				while (L!=NULL) {
					if (strcmp(L->word,s)==0) {
						L->count++;
						return (T);
					};
					L=L->next;
				};
				list p=malloc(sizeof(struct word));
				strcmp(p->word,s);
				p->count=1;
				L=Lstart;
				p->next=L->next;
				L->next=p;
				return(T);
			} else {
				if (strcmp(T->words->word,s)>0) {
					T=ftree(T->right,s);
				} else {
					T=ftree(T->left,s);
				};
			};
		};
	}

void treemas(tree T,char *s) {
	if (T!=NULL) {
		list L=T->words;
		int k=0;
		while (mas[k].ncount!=0) {
			k++;
		};
		while (L!=NULL) {
			strcpy(mas[k].nword,L->word);
			mas[k].ncount=L->count;
			L=L->next;
		};
	treemas(T->left,*s);
	treemas(T->right,*s);
	};
}






int main() {
	tree T=NULL;
	char c;
	char s[100],str[100];
	int k,p;
	memset(s,0,100);
	memset(str,0,100);
	k=0;
	while( scanf("%c",&c) != EOF ) {
		if (isalnum(c)||(c=='_')||(c=='@')||(c=='$')||(c=='%')) {
			s[k]=c;
			k++;
		} else {
			//T=ftree(T,s);
			k=0;
			if ((c!=' ')&&(c!='\n')) {
			str[0]=c;			
			//T=ftree(T,str);
			};
			memset(s,0,100);
		};
	};
	struct mas *m=malloc(sizeof(struct mas));
	//treemas(T,mas);
	return 0;
}

