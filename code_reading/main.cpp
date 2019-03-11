#include "contact.h"
#include "contactlist.h"
#include "vector"



int main() {
	Name security_guard("Jane");
	Name office_person("Joe");
	Name test("Jane");
	Contact c6(security_guard, "", "");
	Contact c5(Name("Jane",""), "", "");



	if (c5 == c6) cout << 0; else cout << 1;
}


