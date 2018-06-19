#ifndef _CSTRING_H_
#define _CSTRING_H_
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>
	// MACRO
	
	#define dalloc(type, size) (type##*)calloc(size, sizeof(type))
	#define $(var, champ) var = var->champ

	// ENUMS
	typedef enum {false, true} bool;

	//	D�finition liste 'string'  ---------------------------------------

	typedef struct string string;
	typedef struct stringt stringt;

	struct string {

		//	variables  ---------------------------------------------------

		char			c;
		unsigned int	size;
		string*			next;
		char*			cTab;
		//	fonctions  ---------------------------------------------------

		void	 (*push)(string**, char);
		void	 (*pop)(string**);
		void	 (*display)(string*);
		void	 (*add)(string*, string*);
		void	 (*addChar)(string*, char*);
		char*	 (*getCharTab)(string*);
		int		 (*isEqual)(string*, string*);
		int		 (*isEqualChar)(string*, char*);
		void	 (*free)(string**);
		string*  (*get)(string*, int);
		stringt* (*split)(string*, char);
		void     (*scan)(string**);
		void	 (*copy)(string*, string*);
		
	};

	struct stringt {
		string**  mat;
		int		  size;
	};

	//	Prototypes fonctions de la structure "string" --------------------

	void	  string_push(string** cur, char c); // Ajoute une lettre � la fin de la cha�ne de caract�re
	void	  string_pop(string** cur); // Supprime la derni�re lettre de la cha�ne de caract�re
	void	  string_display(string* cur); // Affiche la cha�ne de caract�re
	void	  string_add(string* cur, string* other); // Ajoute une cha�ne de caract�re � une autre
	void	  string_addChar(string* cur, char* other);
	char*	  string_getCharTab(string* cur);  // Renvoie un tableau de char
	int		  string_isEqual(string* cur, string* text); // Compare deux cha�nes de caract�res
	int		  string_isEqualChar(string* cur, char* text); // Compare un String et un tableau de char
	void	  string_free(string** cur);
	string*   string_get(string* cur, int pos);
	stringt*  string_split(string* cur, char c);
	void	  string_scan(string** cur);
	void	  string_copy(string* src, string* dest);
	// Autres ------------------------------------------------------------

	string* newString(char* text);

#endif