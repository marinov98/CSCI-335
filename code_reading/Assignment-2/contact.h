#ifndef _CONTACT_H
#define	_CONTACT_H

#include "name.h"
using namespace std;


class Contact
{
public:
    Contact ();
    Contact (Name person, string tel_num ="", string email_addr ="");
    int  set (string fname, string lname, string tel_num, string email_addr);
    int  set              ( char* csv_string);
    void get_name          (Name & fullname);
    void get_tel           (string & tel_num);
    void get_email         (string & email_addr);
    void set_name          (Name fullname);
    void set_tel           (string tel_num);
    void set_email         (string email_addr);
    string convert2csv     ();
    friend bool operator>  (Contact contact1, Contact contact2);
    friend bool operator<  (Contact contact1, Contact contact2);
    friend bool operator== (Contact contact1, Contact contact2);
    friend ostream& operator<< (ostream &, Contact );
    friend bool match      (Contact contact1, Contact contact2);
private:
    Name    name;
    string  telephone;
    string  email;
    bool is_valid_telephone(string tel) const;
};


#endif	/* _CONTACT_H */

