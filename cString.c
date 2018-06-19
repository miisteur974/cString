#include "cString.h"

string* createNode() {
	// Allocation mémoire structure string
	string* new = (string*)calloc(1, sizeof(string));

	// Affectation variables 
	new->c = 0;
	new->size = 0;
	new->next = NULL;
	new->cTab = NULL;

	// Affectation des addresses de fonctions
	new->add = &string_add;
	new->addChar = &string_addChar;
	new->push = &string_push;
	new->pop = &string_pop;
	new->display = &string_display;
	new->getCharTab = &string_getCharTab;
	new->isEqual = &string_isEqual;
	new->isEqualChar = &string_isEqualChar;
	new->free = &string_free;
	new->get = &string_get;
	new->split = &string_split;
	new->scan = &string_scan;
	new->copy = &string_copy;
	
	return new;
};

void string_push(string ** cur, char c)
{
	if (cur) {
		if (*cur) {
			if (!(*cur)->size)
			{
				(*cur)->c = c;
				(*cur)->size = 1;
			}
			else {
				string_push(&(*cur)->next, c);
				(*cur)->size = (*cur)->next->size + 1;
			}
		}
		else {
			(*cur) = createNode();
			(*cur)->c = c;
			(*cur)->size = 1;
		}
	}
}

void string_pop(string ** cur)
{
	if (cur) {
		if (*cur) {
			if (!(*cur)->size)
			{
				free(*cur);
				*cur = NULL;
			}
			else {
				if ((*cur)->next) {
					string_pop(&(*cur)->next);
					(*cur)->size -= 1;
				}
				else {
					free(*cur);
					*cur = NULL;
				}
			}
		}
	}
}

void string_display(string * cur)
{
	if (cur) {
		printf("%c", cur->c);
		string_display(cur->next);
	}
	else  printf("\n");
}

string* string_get(string * cur, int pos)
{
	if (cur)
	{
		string* temp = cur;
		int i = 0;
		if (pos > cur->size) {
			printf(" out of array ! \n");
			return NULL;
		}
		for (i = 0; i < cur->size; i++) {
			if (i == pos)
				return temp;
			temp = temp->next;
		}

		return temp;
	}
	return NULL;
}

stringt* string_split(string * cur, char c)
{
	int count = 0;
	char* test = cur->getCharTab(cur);
	for (int i = 0; i < cur->size; i++) {
		if (test[i] == c)
			count++;
	}
	count++;
	
	string **tab = (string**)calloc(count, sizeof(string*));
	int j = 0;
	char k = test[j];
	for (int i = 0; i < count; i++) {
		tab[i] = newString(NULL);
		if (k == '\n')
			j++;
		k = test[j];
		while (k != c && j < cur->size) {
			tab[i]->push(&tab[i], k);
			j++;
			k = test[j];
		}
		if (k == c)
			j++;
	}
	stringt* newT = (stringt*)calloc(1, sizeof(stringt));
	newT->mat = tab;
	newT->size = count;
	free(test);
	return newT;
}

void string_scan(string ** cur)
{
	if (!cur)
		return;
	if (!*cur)
		return;
	if ((*cur)->size)
	{
		string_free(cur);
		*cur = newString(NULL);
	}
	char c = 0;
	while (c != '\r')
	{
		if (_kbhit()) {
			c = _getch();
			if ((*cur)->size < 1 && c == 8)
				continue;
			if (c == -32)
			{
				c = _getch();
				continue;
			}
			if (c == 8) {
				printf("%c %c", 8, 8);
				if ((*cur)->size <= 1)
					(*cur)->size = 0;
				else
					(*cur)->pop(cur);
			}
			if (c < 32 || c >= 127)
				continue;
			(*cur)->push(cur, c);
			printf("%c", c);
		}
	}
}

void string_copy(string * src, string * dest)
{
	for (int i = 0; i < src->size; i++) {
		dest[i] = src[i];
	}
}

void string_add(string * cur, string * other)
{
	string* temp = NULL;
	if (cur && other) {
		int size = other->size;
		temp = other;
		for (int i = 0; i < size; i++) {
			if (temp)
			{
				cur->push(&cur, temp->c);
				temp = temp->next;
			}
		}
	}
}

void string_addChar(string * cur, char * other)
{
	if (cur)
	{
		string* new = newString(other);
		cur->add(cur, new);
	}
}

char * string_getCharTab(string * cur)
{
	if (cur)
	{
		if (cur->size) {
			char* new = (char*)calloc(cur->size + 1, sizeof(char));
			int i = 0;
			for (i = 0; i < cur->size; i++) {
				new[i] = cur->get(cur, i)->c;
			}
			new[i] = '\0';
			return new;
		}
		else return NULL;
	}
	return NULL;
}

int string_isEqual(string * cur, string * text)
{
	if (cur && text) {
		if (cur->size != text->size)
			return 0;
		else {
			int size = cur->size;
			string* temp1 = cur;
			string* temp2 = text;
			for (int i = 0; i < size-1; i++) {
				if (temp1->c != temp2->c)
					return 0;
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			return 1;
		}
	}
	return 0;
}

int string_isEqualChar(string * cur, char * text)
{
	if (cur && text)
	{
		string* new = newString(text);
		if (new->isEqual(new, cur)) {
			new->free(&new);
			return 1;
		}
	}
	return 0;
}

void string_free(string ** cur)
{
	if (cur && *cur)
	{
		int size = (*cur)->size;
		for (int i = 0; i < size; i++) {
			(*cur)->pop(cur);
		}
		*cur = NULL;
	}
}

string * newString(char * text)
{
	if (!text) {
		string* newS = createNode();
		return newS;
	}
	else {
		string* newS = createNode();
		char temp = text[0];
		int i = 0;
		while (temp) {
			newS->push(&newS, temp);
			i++;
			temp = text[i];
		}
		newS->cTab = newS->getCharTab(newS);
		return newS;
	}
	return NULL;
}
