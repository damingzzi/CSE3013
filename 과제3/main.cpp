#include "Str.h"

int main() {
	Str a("I'm a girl");
	Str b(10);
	Str c("");
	Str d(0);
	cout << a.length() << b.length() << c.length() << d.length();
	cout << a.contents();
	a = "I'm a boy\n";
	cout << a.contents();
	cout << a.compare("I'm a a") << endl;
	b = c;
	cout << b.length() << ' ' << a.compare(b) << '\n';
	c = a;
	cout << a.compare(c) << '\n';

	return 0;
}