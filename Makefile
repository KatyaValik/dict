all: dict

dict: diction.c
	gcc -g diction.c -o dict
	
clean: 
	rm -vf dict
	