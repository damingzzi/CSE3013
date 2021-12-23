#include "Str.h"

Str::Str(int leng) {
	len = leng;
	str = new char[len + 1];
	for (int i = 0; i < len; i++) {
		str[i] = ' ';
	}
}

Str::Str(const char* neyong) {
	len = strlen(neyong);
	str = new char[len + 1];
	strcpy(str, neyong);
}

Str::~Str() {
	delete[] str;
}

int Str::length(void) {
	return len;
}

char* Str::contents(void) {
	return str;
}

int Str::compare(class Str& a) {
	char* astr = a.contents();
	return strcmp(str, astr);
}

int Str::compare(const char* a) {
	return strcmp(str, a);
}

void Str::operator=(const char* a) {
	delete[] str;
	len = strlen(a);
	str = new char[len + 1];
	strcpy(str, a);
}

void Str::operator=(class Str& a) {
	delete[] str;
	len = a.length();
	str = new char[len + 1];
	strcpy(str, a.contents());
}



