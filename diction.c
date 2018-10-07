#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct word *list;
	struct word {
		int count;
		list next;
	};

typedef struct node *tree;
	struct node {
		list words;
		tree left;
		tree right;
	};

int main() {
	tree T=NULL;
	char c;
	char s[100],str[100];
	int k,p;
	memset(s,0,100);
	memset(str,0,100);
	k=0;
	while( ((p = scanf("%c",&c))>0)&&(c!=0)) {
		printf("p=%d c=%d\n",p, c);
		if (isalnum(c)||(c=='_')||(c=='@')) {
			s[k]=c;
			k++;
		} else {
			//ftree(T,s);
			k=0;
			str[0]=c;			
			//ftree(T,str);
			memset(s,0,100);
		}
		
	}
	return 0;
}

