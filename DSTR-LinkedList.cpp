#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int sizeofUsersLinkedList = 0;
int sizeofTutorsLinkedList = 0;
int sizeofCentreLinkedList = 0;
int sizeofSubjectLinkedList = 0;

//Declare necessary structs
struct Users {
	int UserID;
	string Username;
	string Password;
	string Role;
	int Centre_Code;
	Users* nextAddress;
	Users* prevAddress;
} *usershead, *userstail;

struct Tutors {
	int TutorID;
	string Name;
	time_t Join_Date;
	time_t Term_Date;
	float Hourly_Rate;
	int Phone;
	string Address;
	int Centre_Code;
	int Subject_Code;
	float Rating;
	int Rating_No;
	Tutors* nextAddress;
	Tutors* prevAddress;
} *tutorshead, *tutorstail;

struct Centre {
	int CentreCode;
	string Centre_Name;
	string Address;
	string Region;
	int Tutors_Total;
	int Tutors_Terminated;
	Centre* nextAddress;
	Centre* prevAddress;
} *centrehead, *centretail;

struct Subject {
	int SubjectCode;
	string Subject_Name;
	Subject* nextAddress;
	Subject* prevAddress;
} *subjecthead, *subjecttail;


Users* CreateNewUser(int UserID, string Username, string Password, string Role, int Centre_Code) //create user newnode
{
	Users* newnode = new Users;
	newnode->UserID = UserID;
	newnode->Username = Username;
	newnode->Password = Password;
	newnode->Role = Role;
	newnode->Centre_Code = Centre_Code;
	newnode->nextAddress = NULL;
	newnode->prevAddress = NULL;

	return newnode;
}

Tutors* CreateNewTutor(int TutorID, string Name, int Join_Date, int Term_Date, float Hourly_Rate, int Phone, string Address, int Centre_Code, int Subject_Code, float Rating, int Rating_No) //create tutor newnode
{
	Tutors* newnode = new Tutors;
	newnode->TutorID = TutorID;
	newnode->Name = Name;
	newnode->Join_Date = Join_Date;
	newnode->Term_Date = Term_Date;
	newnode->Hourly_Rate = Hourly_Rate;
	newnode->Phone = Phone;
	newnode->Address = Address;
	newnode->Centre_Code = Centre_Code;
	newnode->Subject_Code = Subject_Code;
	newnode->Rating = Rating;
	newnode->Rating_No = Rating_No;
	newnode->nextAddress = NULL;
	newnode->prevAddress = NULL;

	return newnode;
}

Centre* CreateNewCentre(int CentreCode, string Centre_Name, string Address, string Region, int Tutors_Total, int Tutors_Terminated) //create centre newnode
{
	Centre* newnode = new Centre;
	newnode->CentreCode = CentreCode;
	newnode->Centre_Name = Centre_Name;
	newnode->Address = Address;
	newnode->Region = Region;
	newnode->Tutors_Total = Tutors_Total;
	newnode->Tutors_Terminated = Tutors_Terminated;
	newnode->nextAddress = NULL;
	newnode->prevAddress = NULL;

	return newnode;
}

Subject* CreateNewSubject(int SubjectCode, string Subject_Name) //create subject newnode
{
	Subject* newnode = new Subject;
	newnode->SubjectCode = SubjectCode;
	newnode->Subject_Name = Subject_Name;
	newnode->nextAddress = NULL;
	newnode->prevAddress = NULL;

	return newnode;
}


//Convert date
time_t toTimeStamp(string date) {
	struct tm t;
	time_t t_of_day;

	t.tm_year = stoi(date.substr(0, 4)) - 1900;
	t.tm_mon = stoi(date.substr(5, 7)) - 1;
	t.tm_mday = stoi(date.substr(8, 10));
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	t.tm_isdst = 0;
	t_of_day = mktime(&t);

	return t_of_day;
}


//Validation
bool compareStrings(string first, string second)
{
	transform(first.begin(), first.end(), first.begin(), ::tolower);
	transform(second.begin(), second.end(), second.begin(), ::tolower);

	return first == second;
}

bool isDateNumber(const string& str) {
	for (int i = 0; i < str.length(); i++) {
		if (i != 4 && i != 7) {
			if (isdigit(str[i]) == 0) return false;
		}
	}
	return true;
}

bool checkDateValid(string date) {
	if (date.length() != 10 || !isDateNumber(date) || stoi(date.substr(0, 4)) - 1900 < 0 ||
		!(stoi(date.substr(5, 7)) - 1 >= 0 && stoi(date.substr(5, 7)) - 1 < 12) ||
		!(stoi(date.substr(8, 10)) > 0 && stoi(date.substr(8, 10)) <= 31)) {
		cout << " **Invalid format try again!" << endl;
		return true;
	}
	return false;
}

int enterUsername()
{
	string loginUsername;
	int ID = 0;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter your username: ";
	cin >> loginUsername;

	while (cin.fail())
	{
		cout << "Invalid Username! Enter your username again: ";
		cin >> loginUsername;
	}

	Users* userscurrent = usershead;
	while (userscurrent != NULL)
	{
		if (compareStrings(loginUsername, userscurrent->Username))
		{
			ID = userscurrent->UserID;
			break;
		}
		userscurrent = userscurrent->nextAddress;
	}

	return ID;
}

int enterPassword(int ID)
{
	string loginPassword;
	int middle_point = sizeofUsersLinkedList / 2;
	int signal = 0;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter your password: ";
	cin >> loginPassword;

	while (cin.fail())
	{
		cout << "Invalid Password! Enter your password again: ";
		cin >> loginPassword;
	}

	if (ID <= middle_point)
	{
		int count = 1;
		Users* userscurrent = usershead;
		while (userscurrent != NULL)
		{
			if (ID == count)
			{
				if (loginPassword == userscurrent->Password)
				{
					cout << "You have logged in successfully!" << endl;
					if (userscurrent->Role == "STUDENT")
					{
						signal = 1;
					}
					else if (userscurrent->Role == "ADMIN")
					{
						signal = 2;
					}
					else
					{
						signal = 3;
					}
					break;
				}
			}
			count++;
			userscurrent = userscurrent->nextAddress;
		}
	}
	else
	{
		int count = sizeofUsersLinkedList;
		Users* userscurrent = userstail;
		while (userscurrent != NULL)
		{
			if (ID == count)
			{
				if (loginPassword == userscurrent->Password)
				{
					cout << "You have logged in successfully!" << endl;
					if (userscurrent->Role == "STUDENT")
					{
						signal = 1;
					}
					else if (userscurrent->Role == "ADMIN")
					{
						signal = 2;
					}
					else
					{
						signal = 3;
					}
					break;
				}
			}
			count--;
			userscurrent = userscurrent->prevAddress;
		}
	}

	return signal;
}


//Additional functions
time_t todayDate()
{
	time_t t = system_clock::to_time_t(system_clock::now()); // get time now
	struct tm now;
	localtime_s(&now, &t);

	// convert today date to timestamp
	struct tm time;
	time_t time_now;
	time.tm_year = now.tm_year;
	time.tm_mon = now.tm_mon;
	time.tm_mday = now.tm_mday;
	time.tm_hour = 0;
	time.tm_min = 0;
	time.tm_sec = 0;
	time.tm_isdst = 0;
	time_now = mktime(&time);

	return time_now;
}

void countNumberOfTutorsperCentre(int centre_code, int signal)
{
	//signal 1 - to count total number of tutors per centre; 2 - to count number of terminated/deleted tutors per centre

	//scenario 1: list is still empty
	if (centrehead == NULL)
	{
		return;
	}

	if (signal == 1)
	{
		if (centrehead->CentreCode == centre_code)
		{
			int temp = centrehead->Tutors_Total;
			centrehead->Tutors_Total = temp + 1;
			return;
		}
		else if (centretail->CentreCode == centre_code)
		{
			int temp = centretail->Tutors_Total;
			centretail->Tutors_Total = temp + 1;
			return;
		}
		else
		{
			Centre* centrecurrent = centrehead->nextAddress;
			while (centrecurrent != NULL)
			{
				if (centrecurrent->CentreCode == centre_code)
				{
					int temp = centrecurrent->Tutors_Total;
					centrecurrent->Tutors_Total = temp + 1;
					return;
				}
				centrecurrent = centrecurrent->nextAddress;
			}
		}
	}
	else
	{
		if (centrehead->CentreCode == centre_code)
		{
			int temp = centrehead->Tutors_Terminated;
			centrehead->Tutors_Terminated = temp + 1;
			return;
		}
		else if (centretail->CentreCode == centre_code)
		{
			int temp = centretail->Tutors_Terminated;
			centretail->Tutors_Terminated = temp + 1;
			return;
		}
		else
		{
			Centre* centrecurrent = centrehead->nextAddress;
			while (centrecurrent != NULL)
			{
				if (centrecurrent->CentreCode == centre_code)
				{
					int temp = centrecurrent->Tutors_Terminated;
					centrecurrent->Tutors_Terminated = temp + 1;
					return;
				}
				centrecurrent = centrecurrent->nextAddress;
			}
		}
	}
}

void checkTermination() {
	time_t t = system_clock::to_time_t(system_clock::now()); // get time now
	struct tm now;
	localtime_s(&now, &t);

	int date = now.tm_mday;
	int month = now.tm_mon;
	int year = now.tm_year;

	if (month - 6 < 0) {
		month = month + 6; // (-6 + 12)
		year--;
	}
	else {
		month = month - 6;
	}

	// convert today date to timestamp
	struct tm time;
	time_t time_now;
	time.tm_year = year;
	time.tm_mon = month;
	time.tm_mday = date;
	time.tm_hour = 0;
	time.tm_min = 0;
	time.tm_sec = 0;
	time.tm_isdst = 0;
	time_now = mktime(&time);

	Tutors* tutorscurrent = tutorshead;

	while (tutorscurrent != NULL)
	{
		if (tutorscurrent->Term_Date != 0 && tutorscurrent->Term_Date <= time_now)
		{
			if (tutorscurrent->prevAddress == NULL)
			{
				if (tutorscurrent->nextAddress != NULL)
				{
					tutorscurrent->nextAddress->prevAddress = NULL;
				}
				if (tutorscurrent->nextAddress == NULL)
				{
					tutorstail = NULL;
				}
				tutorshead = tutorshead->nextAddress;
			}
			else if (tutorscurrent->nextAddress == NULL)
			{
				tutorscurrent->prevAddress->nextAddress = NULL;
				tutorstail = tutorstail->prevAddress;
			}
			else
			{
				tutorscurrent->prevAddress->nextAddress = tutorscurrent->nextAddress;
				tutorscurrent->nextAddress->prevAddress = tutorscurrent->prevAddress;
			}
			countNumberOfTutorsperCentre(tutorscurrent->Centre_Code, 2);
			delete tutorscurrent;
			sizeofTutorsLinkedList--;
			return;
		}
		tutorscurrent = tutorscurrent->nextAddress;
	}
}

int getCentreCodeBasedOnID(int ID)
{
	int middle_point = sizeofUsersLinkedList / 2;
	int centre_code = 0;

	if (ID <= middle_point)
	{
		Users* userscurrent = usershead;
		while (userscurrent != NULL)
		{
			if (userscurrent->UserID == ID)
			{
				centre_code = userscurrent->Centre_Code;
				return centre_code;
			}
			userscurrent = userscurrent->nextAddress;
		}
	}
	else
	{
		Users* userscurrent = userstail;
		while (userscurrent != NULL)
		{
			if (userscurrent->UserID == ID)
			{
				centre_code = userscurrent->Centre_Code;
				return centre_code;
			}
			userscurrent = userscurrent->prevAddress;
		}
	}
}


//Centre's functions
void inserintoEndofCentreLinkedList(Centre* newnode)
{
	//scenario 1: list is still empty, means centrehead is still empty
	if (centrehead == NULL)
	{
		centrehead = centretail = newnode;
	}
	//scenario 2: if list not empty, means add item to the last location
	else
	{
		centretail->nextAddress = newnode;
		newnode->prevAddress = centretail;
		centretail = newnode;
	}
	::sizeofCentreLinkedList++;
}

void displayCentreLinkedList()
{
	Centre* centrecurrent = centrehead;

	if (centrecurrent == NULL)
	{
		cout << "No centre being recorded yet!" << endl;
	}

	while (centrecurrent != NULL)
	{
		cout << centrecurrent->CentreCode << " - " << centrecurrent->Centre_Name << " - " << centrecurrent->Address << " - " << centrecurrent->Region << endl;
		centrecurrent = centrecurrent->nextAddress;
	}
}

void addCentre(int CentreCode)
{
	string Centre_Name;
	string Address;
	string Region;
	int Tutors_Total;
	int Tutors_Terminated;

	cout << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Centre Name: ";
	getline(cin, Centre_Name);
	while (cin.fail())
	{
		cout << "Enter Centre Name: ";
		getline(cin, Centre_Name);
	}
	cout << "Enter Centre Address: ";
	getline(cin, Address);
	while (cin.fail())
	{
		cout << "Enter Centre Address: ";
		getline(cin, Address);
	}
	cout << "Enter Centre Region: ";
	getline(cin, Region);
	while (cin.fail())
	{
		cout << "Enter Centre Region: ";
		getline(cin, Region);
	}

	Centre* centreNewnode = CreateNewCentre(CentreCode, Centre_Name, Address, Region, 0, 0);
	inserintoEndofCentreLinkedList(centreNewnode);
}

string convertCentreCodeToName(int centreCode)
{
	int middle_point = sizeofCentreLinkedList / 2;
	string centreName;

	if (centreCode <= middle_point)
	{
		Centre* centrecurrent = centrehead;
		while (centrecurrent != NULL)
		{
			if (centrecurrent->CentreCode == centreCode)
			{
				centreName = centrecurrent->Centre_Name;
				return centreName;
			}
			centrecurrent = centrecurrent->nextAddress;
		}
	}
	else
	{
		Centre* centrecurrent = centretail;
		while (centrecurrent != NULL)
		{
			if (centrecurrent->CentreCode == centreCode)
			{
				centreName = centrecurrent->Centre_Name;
				return centreName;
			}
			centrecurrent = centrecurrent->prevAddress;
		}
	}
}


//User's functions
void inserintoEndofUsersLinkedList(Users* newnode)
{
	//scenario 1: list is still empty, means usershead is still empty
	if (usershead == NULL)
	{
		usershead = userstail = newnode;
	}
	//scenario 2: if list not empty, means add item to the last location
	else
	{
		userstail->nextAddress = newnode;
		newnode->prevAddress = userstail;
		userstail = newnode;
	}
	::sizeofUsersLinkedList++;
}

void addUser(int IDuser)
{
	string user_name;
	string user_pass;
	string user_role;
	int user_centre_code;

	int temp_role;

	cout << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter User Name: ";
	getline(cin, user_name);
	while (cin.fail())
	{
		cout << "Enter Username: ";
		getline(cin, user_name);
	}
	cout << "Enter User's Password: ";
	cin >> user_pass;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter User's Password: ";
		cin >> user_pass;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Available User Role: " << endl;
	cout << "1. Student " << endl;
	cout << "2. Admin" << endl;
	cout << "3. HR Manager" << endl;
	cout << "Enter User Role: ";
	cin >> temp_role;
	while (cin.fail() || temp_role < 1 || temp_role > 3)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Available User Role: " << endl;
		cout << "1. Student " << endl;
		cout << "2. Admin" << endl;
		cout << "3. HR Manager" << endl;
		cout << "Enter User Role: ";
		cin >> temp_role;
	}
	if (temp_role == 1)
	{
		user_role = "STUDENT";
	}
	else if (temp_role == 2)
	{
		user_role = "ADMIN";
	}
	else
	{
		user_role = "HR MANAGER";
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Available Centre Code: " << endl;
	displayCentreLinkedList();
	if (temp_role == 3)
	{
		cout << "User Centre Code: 1" << endl;
		cout << "HR Manager only works in HEAD QUARTER" << endl;
		user_centre_code = 1;
	}
	else
	{
		cout << "Enter User Centre Code: ";
		cin >> user_centre_code;
		while (cin.fail() || user_centre_code < 1 || user_centre_code > sizeofCentreLinkedList)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Available Centre Code: " << endl;
			displayCentreLinkedList();
			cout << "Enter User Centre Code: ";
			cin >> user_centre_code;
		}
	}

	Users* usersNewnode = CreateNewUser(IDuser, user_name, user_pass, user_role, user_centre_code);
	inserintoEndofUsersLinkedList(usersNewnode);
}


//Subject's functions
void inserintoEndofSubjectLinkedList(Subject* newnode)
{
	//scenario 1: list is still empty, means subjecthead is still empty
	if (subjecthead == NULL)
	{
		subjecthead = subjecttail = newnode;
	}
	//scenario 2: if list not empty, means add item to the last location
	else
	{
		subjecttail->nextAddress = newnode;
		newnode->prevAddress = subjecttail;
		subjecttail = newnode;
	}
	::sizeofSubjectLinkedList++;
}

void displaySubjectLinkedList()
{
	Subject* subjectcurrent = subjecthead;

	if (subjectcurrent == NULL)
	{
		cout << "No subject being recorded yet!" << endl;
	}

	while (subjectcurrent != NULL)
	{
		cout << subjectcurrent->SubjectCode << " - " << subjectcurrent->Subject_Name << endl;
		subjectcurrent = subjectcurrent->nextAddress;
	}
}

void addSubject(int SubjectCode)
{
	string Subject_Name;

	cout << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Subject Name: ";
	getline(cin, Subject_Name);
	while (cin.fail())
	{
		cout << "Enter Subject Name: ";
		getline(cin, Subject_Name);
	}

	Subject* subjectNewnode = CreateNewSubject(SubjectCode, Subject_Name);
	inserintoEndofSubjectLinkedList(subjectNewnode);
}

string convertSubjectCodeToName(int subjectCode)
{
	int middle_point = sizeofSubjectLinkedList / 2;
	string subjectName;

	if (subjectCode <= middle_point)
	{
		Subject* subjectcurrent = subjecthead;
		while (subjectcurrent != NULL)
		{
			if (subjectcurrent->SubjectCode == subjectCode)
			{
				subjectName = subjectcurrent->Subject_Name;
				return subjectName;
			}
			subjectcurrent = subjectcurrent->nextAddress;
		}
	}
	else
	{
		Subject* subjectcurrent = subjecttail;
		while (subjectcurrent != NULL)
		{
			if (subjectcurrent->SubjectCode == subjectCode)
			{
				subjectName = subjectcurrent->Subject_Name;
				return subjectName;
			}
			subjectcurrent = subjectcurrent->prevAddress;
		}
	}
}


//Tutor's functions
void inserintoEndofTutorsLinkedList(Tutors* newnode)
{
	//scenario 1: list is still empty, means tutorshead is still empty
	if (tutorshead == NULL)
	{
		tutorshead = tutorstail = newnode;
	}
	//scenario 2: if list not empty, means add item to the last location
	else
	{
		tutorstail->nextAddress = newnode;
		newnode->prevAddress = tutorstail;
		tutorstail = newnode;
	}
	::sizeofTutorsLinkedList++;
}

void displayTutorsLinkedList()
{
	Tutors* tutorscurrent = tutorshead;

	if (tutorscurrent == NULL)
	{
		cout << "No tutor being recorded yet!" << endl;
	}

	while (tutorscurrent != NULL)
	{
		time_t t_join = tutorscurrent->Join_Date;
		struct tm now_join;
		localtime_s(&now_join, &t_join);

		int date_join = now_join.tm_mday;
		int month_join = 1 + now_join.tm_mon;
		int year_join = 1900 + now_join.tm_year;

		int date_terminate;
		int month_terminate;
		int year_terminate;

		time_t t_terminate = tutorscurrent->Term_Date;
		struct tm now_terminate;
		localtime_s(&now_terminate, &t_terminate);

		if (t_terminate == 0)
		{
			date_terminate = 0;
			month_terminate = 0;
			year_terminate = 0;
		}
		else
		{
			date_terminate = now_terminate.tm_mday;
			month_terminate = 1 + now_terminate.tm_mon;
			year_terminate = 1900 + now_terminate.tm_year;
		}

		string centreName = convertCentreCodeToName(tutorscurrent->Centre_Code);
		string subjectName = convertSubjectCodeToName(tutorscurrent->Subject_Code);

		cout << tutorscurrent->TutorID << " - " << tutorscurrent->Name << " - " << date_join << "/" 
			<< month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
			<< " - " << tutorscurrent->Hourly_Rate << " - " << tutorscurrent->Phone << " - " 
			<< tutorscurrent->Address << " - " << centreName
			<< " - " << subjectName << " - " << tutorscurrent->Rating << endl;
		tutorscurrent = tutorscurrent->nextAddress;
	}
}

void displayTutorsLinkedListOnebyOne()
{
	int count = 1;

	Tutors* tutorscurrent = tutorshead;

	if (tutorscurrent == NULL)
	{
		cout << "No tutor being recorded yet!" << endl;
	}

	while (tutorscurrent != NULL)
	{
		if (count > 1)
		{
			system("cls");
		}

		int nextprevious = 0;

		time_t t_join = tutorscurrent->Join_Date;
		struct tm now_join;
		localtime_s(&now_join, &t_join);

		int date_join = now_join.tm_mday;
		int month_join = 1 + now_join.tm_mon;
		int year_join = 1900 + now_join.tm_year;

		int date_terminate;
		int month_terminate;
		int year_terminate;

		time_t t_terminate = tutorscurrent->Term_Date;
		struct tm now_terminate;
		localtime_s(&now_terminate, &t_terminate);

		if (t_terminate == 0)
		{
			date_terminate = 0;
			month_terminate = 0;
			year_terminate = 0;
		}
		else
		{
			date_terminate = now_terminate.tm_mday;
			month_terminate = 1 + now_terminate.tm_mon;
			year_terminate = 1900 + now_terminate.tm_year;
		}

		string centreName = convertCentreCodeToName(tutorscurrent->Centre_Code);
		string subjectName = convertSubjectCodeToName(tutorscurrent->Subject_Code);

		cout << tutorscurrent->TutorID << " - " << tutorscurrent->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
			<< " - " << tutorscurrent->Hourly_Rate << " - " << tutorscurrent->Phone << " - " << tutorscurrent->Address << " - " << centreName
			<< " - " << subjectName << " - " << tutorscurrent->Rating << endl;

		if (tutorscurrent->prevAddress == NULL && sizeofTutorsLinkedList > 1)
		{
			cout << endl << "This is the starting item of the list!" << endl;
			cout << "Enter 1 to view next; 0 to terminate this display!" << endl;
			cout << "Your choice: ";
			cin >> nextprevious;
			while (cin.fail() || nextprevious < 0 || nextprevious > 1)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter 1 to view next; 0 to terminate this display!" << endl;
				cout << "Your choice: ";
				cin >> nextprevious;
			}
		}
		else if (tutorscurrent->prevAddress == NULL && sizeofTutorsLinkedList == 1)
		{
			cout << endl << "This is the only item of the list!" << endl;
		}
		else if (tutorscurrent->nextAddress == NULL)
		{
			cout << endl << "This is the last item of the list!" << endl;
			cout << "Enter 2 to view previous; 0 to terminate this display!" << endl;
			cout << "Your choice: ";
			cin >> nextprevious;
			while (cin.fail() || nextprevious < 0 || nextprevious > 2 || nextprevious == 1)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter 2 to view previous; 0 to terminate this display!" << endl;
				cout << "Your choice: ";
				cin >> nextprevious;
			}
		}
		else
		{
			cout << endl << "Enter 1 to view next; 2 to view previous; 0 to terminate this display!" << endl;
			cout << "Your choice: ";
			cin >> nextprevious;
			while (cin.fail() || nextprevious < 0 || nextprevious > 2)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter 1 to view next; 2 to view previous; 0 to terminate this display!!" << endl;
				cout << "Your choice: ";
				cin >> nextprevious;
			}
		}

		if (nextprevious == 1)
		{
			tutorscurrent = tutorscurrent->nextAddress;
		}
		else if (nextprevious == 2)
		{
			tutorscurrent = tutorscurrent->prevAddress;
		}
		else
		{
			return;
		}
		count++;
	}
}

void displayTutorsLinkedListBasedOnCentreCode(int CentreCode)
{
	bool signal = false;
	Tutors* tutorscurrent = tutorshead;

	if (tutorscurrent == NULL)
	{
		cout << "No tutor being recorded yet!" << endl;
	}

	while (tutorscurrent != NULL)
	{
		if (tutorscurrent->Centre_Code == CentreCode)
		{
			signal = true;

			time_t t_join = tutorscurrent->Join_Date;
			struct tm now_join;
			localtime_s(&now_join, &t_join);

			int date_join = now_join.tm_mday;
			int month_join = 1 + now_join.tm_mon;
			int year_join = 1900 + now_join.tm_year;

			int date_terminate;
			int month_terminate;
			int year_terminate;

			time_t t_terminate = tutorscurrent->Term_Date;
			struct tm now_terminate;
			localtime_s(&now_terminate, &t_terminate);

			if (t_terminate == 0)
			{
				date_terminate = 0;
				month_terminate = 0;
				year_terminate = 0;
			}
			else
			{
				date_terminate = now_terminate.tm_mday;
				month_terminate = 1 + now_terminate.tm_mon;
				year_terminate = 1900 + now_terminate.tm_year;
			}

			string centreName = convertCentreCodeToName(tutorscurrent->Centre_Code);
			string subjectName = convertSubjectCodeToName(tutorscurrent->Subject_Code);

			cout << tutorscurrent->TutorID << " - " << tutorscurrent->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
				<< " - " << tutorscurrent->Hourly_Rate << " - " << tutorscurrent->Phone << " - " << tutorscurrent->Address << " - " << centreName
				<< " - " << subjectName << " - " << tutorscurrent->Rating << endl;
		}
		tutorscurrent = tutorscurrent->nextAddress;
	}

	if (!signal)
	{
		cout << "There is no tutor yet in this centre!" << endl;
	}
}

void addTutor(int IDtutor)
{
	string tutor_name;
	time_t  tutor_join;
	time_t  tutor_terminate;
	float tutor_payrate;
	int tutor_phone;
	string tutor_address;
	int tutor_centrecode;
	int tutor_subjectcode;

	string join_date;

	cout << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Tutor Name: ";
	getline(cin, tutor_name);
	while (cin.fail())
	{
		cout << "Enter Tutor Name: ";
		getline(cin, tutor_name);
	}
	cout << "Enter Tutor Join Date (YYYY-MM-DD): ";
	cin >> join_date;
	bool flag = checkDateValid(join_date);
	while (cin.fail() || flag)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter Tutor Join Date (YYYY-MM-DD): ";
		cin >> join_date;
		flag = checkDateValid(join_date);
	}
	tutor_join = toTimeStamp(join_date);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Tutor Hourly Pay Rate: RM ";
	cin >> tutor_payrate;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter Tutor Hourly Pay Rate: RM ";
		cin >> tutor_payrate;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Tutor Phone: ";
	cin >> tutor_phone;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter Tutor Phone: ";
		cin >> tutor_phone;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Tutor Address: ";
	getline(cin, tutor_address);
	while (cin.fail())
	{
		cout << "Enter Tutor Address: ";
		getline(cin, tutor_address);
	}
	cout << "Available Centre Code: " << endl;
	displayCentreLinkedList();
	cout << "Enter Tutor Centre Code: ";
	cin >> tutor_centrecode;
	while (cin.fail() || tutor_centrecode < 1 || tutor_centrecode > sizeofCentreLinkedList)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Available Centre Code: " << endl;
		displayCentreLinkedList();
		cout << "Enter Tutor Centre Code: ";
		cin >> tutor_centrecode;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Available Subject Code: " << endl;
	displaySubjectLinkedList();
	cout << "Enter Tutor Subject Code: ";
	cin >> tutor_subjectcode;
	while (cin.fail() || tutor_subjectcode < 1 || tutor_subjectcode > sizeofSubjectLinkedList)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Available Subject Code: " << endl;
		displaySubjectLinkedList();
		cout << "Enter Tutor Subject Code: ";
		cin >> tutor_subjectcode;
	}

	Tutors* tutorsNewnode = CreateNewTutor(IDtutor, tutor_name, tutor_join, 0, tutor_payrate, tutor_phone, tutor_address, tutor_centrecode, tutor_subjectcode, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	countNumberOfTutorsperCentre(tutor_centrecode, 1);
	checkTermination();
}

void LinearSearchTutorID()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to search!" << endl;
		return;
	}

	int keyword;

	cout << endl << "Enter Tutor ID whose record you want to search: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Tutor ID whose record you want to search: ";
		cin >> keyword;
	}

	auto starttime = high_resolution_clock::now();

	//scenario 2: head tutor id = keyword
	if (tutorshead->TutorID == keyword)
	{
		time_t t_join = tutorshead->Join_Date;
		struct tm now_join;
		localtime_s(&now_join, &t_join);

		int date_join = now_join.tm_mday;
		int month_join = 1 + now_join.tm_mon;
		int year_join = 1900 + now_join.tm_year;

		int date_terminate;
		int month_terminate;
		int year_terminate;

		time_t t_terminate = tutorshead->Term_Date;
		struct tm now_terminate;
		localtime_s(&now_terminate, &t_terminate);

		if (t_terminate == 0)
		{
			date_terminate = 0;
			month_terminate = 0;
			year_terminate = 0;
		}
		else
		{
			date_terminate = now_terminate.tm_mday;
			month_terminate = 1 + now_terminate.tm_mon;
			year_terminate = 1900 + now_terminate.tm_year;
		}

		string centreName = convertCentreCodeToName(tutorshead->Centre_Code);
		string subjectName = convertSubjectCodeToName(tutorshead->Subject_Code);

		cout << tutorshead->TutorID << " - " << tutorshead->Name << " - " << date_join << "/" << month_join << "/" 
			<< year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
			<< " - " << tutorshead->Hourly_Rate << " - " << tutorshead->Phone << " - " << tutorshead->Address << " - " << centreName
			<< " - " << subjectName << " - " << tutorshead->Rating << endl;
		auto stoptime = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stoptime - starttime);
		cout << "Linear Search Time Used: " << duration.count() << " microseconds" << endl;
		return;
	}
	//scenario 3: tail tutor id = keyword
	else if (tutorstail->TutorID == keyword)
	{
		time_t t_join = tutorstail->Join_Date;
		struct tm now_join;
		localtime_s(&now_join, &t_join);

		int date_join = now_join.tm_mday;
		int month_join = 1 + now_join.tm_mon;
		int year_join = 1900 + now_join.tm_year;

		int date_terminate;
		int month_terminate;
		int year_terminate;

		time_t t_terminate = tutorstail->Term_Date;
		struct tm now_terminate;
		localtime_s(&now_terminate, &t_terminate);

		if (t_terminate == 0)
		{
			date_terminate = 0;
			month_terminate = 0;
			year_terminate = 0;
		}
		else
		{
			date_terminate = now_terminate.tm_mday;
			month_terminate = 1 + now_terminate.tm_mon;
			year_terminate = 1900 + now_terminate.tm_year;
		}

		string centreName = convertCentreCodeToName(tutorstail->Centre_Code);
		string subjectName = convertSubjectCodeToName(tutorstail->Subject_Code);

		cout << tutorstail->TutorID << " - " << tutorstail->Name << " - " << date_join << "/" << month_join 
			<< "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
			<< " - " << tutorstail->Hourly_Rate << " - " << tutorstail->Phone << " - " << tutorstail->Address << " - " << centreName
			<< " - " << subjectName << " - " << tutorstail->Rating << endl;
		auto stoptime = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stoptime - starttime);
		cout << "Linear Search Time Used: " << duration.count() << " microseconds" << endl;
		return;
	}
	//scenario 4: where the keyword unable to find in first and last item
	else
	{
		Tutors* tutorscurrent = tutorshead->nextAddress;

		while (tutorscurrent != NULL)
		{
			if (tutorscurrent->TutorID == keyword)
			{
				time_t t_join = tutorscurrent->Join_Date;
				struct tm now_join;
				localtime_s(&now_join, &t_join);

				int date_join = now_join.tm_mday;
				int month_join = 1 + now_join.tm_mon;
				int year_join = 1900 + now_join.tm_year;

				int date_terminate;
				int month_terminate;
				int year_terminate;

				time_t t_terminate = tutorscurrent->Term_Date;
				struct tm now_terminate;
				localtime_s(&now_terminate, &t_terminate);

				if (t_terminate == 0)
				{
					date_terminate = 0;
					month_terminate = 0;
					year_terminate = 0;
				}
				else
				{
					date_terminate = now_terminate.tm_mday;
					month_terminate = 1 + now_terminate.tm_mon;
					year_terminate = 1900 + now_terminate.tm_year;
				}

				string centreName = convertCentreCodeToName(tutorscurrent->Centre_Code);
				string subjectName = convertSubjectCodeToName(tutorscurrent->Subject_Code);

				cout << tutorscurrent->TutorID << " - " << tutorscurrent->Name << " - " << date_join << "/" << month_join 
					<< "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
					<< " - " << tutorscurrent->Hourly_Rate << " - " << tutorscurrent->Phone << " - " << tutorscurrent->Address << " - " << centreName
					<< " - " << subjectName << " - " << tutorscurrent->Rating << endl;
				auto stoptime = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stoptime - starttime);
				cout << "Linear Search Time Used: " << duration.count() << " microseconds" << endl;
				return;
			}
			tutorscurrent = tutorscurrent->nextAddress;
		}
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	cout << "Linear Search Time Used: " << duration.count() << " microseconds" << endl;
	cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
}

void LinearSearchRating()
{
	int signal = 0;

	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to search!" << endl;
		return;
	}

	float keyword;

	cout << endl << "Enter Rating that you want to search: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Rating that you want to search: ";
		cin >> keyword;
	}

	auto starttime = high_resolution_clock::now();

	Tutors* tutorscurrent = tutorshead;

	while (tutorscurrent != NULL)
	{
		if (tutorscurrent->Rating == keyword)
		{
			time_t t_join = tutorscurrent->Join_Date;
			struct tm now_join;
			localtime_s(&now_join, &t_join);

			int date_join = now_join.tm_mday;
			int month_join = 1 + now_join.tm_mon;
			int year_join = 1900 + now_join.tm_year;

			int date_terminate;
			int month_terminate;
			int year_terminate;

			time_t t_terminate = tutorscurrent->Term_Date;
			struct tm now_terminate;
			localtime_s(&now_terminate, &t_terminate);

			if (t_terminate == 0)
			{
				date_terminate = 0;
				month_terminate = 0;
				year_terminate = 0;
			}
			else
			{
				date_terminate = now_terminate.tm_mday;
				month_terminate = 1 + now_terminate.tm_mon;
				year_terminate = 1900 + now_terminate.tm_year;
			}

			string centreName = convertCentreCodeToName(tutorscurrent->Centre_Code);
			string subjectName = convertSubjectCodeToName(tutorscurrent->Subject_Code);

			cout << tutorscurrent->TutorID << " - " << tutorscurrent->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
				<< " - " << tutorscurrent->Hourly_Rate << " - " << tutorscurrent->Phone << " - " << tutorscurrent->Address << " - " << centreName
				<< " - " << subjectName << " - " << tutorscurrent->Rating << endl;
			signal = 1;
		}
		tutorscurrent = tutorscurrent->nextAddress;
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	cout << "Linear Search Time Used: " << duration.count() << " microseconds" << endl;

	if (signal == 0)
	{
		cout << endl << "Rating as " << keyword << " is not found in the record!" << endl;
	}
}

Tutors *findMiddleTutor(Tutors *start, Tutors *last)
{
	if (start == NULL)
	{
		return NULL;
	}

	Tutors* slow = start;
	Tutors* fast = start->nextAddress;

	while (fast != last)
	{
		fast = fast->nextAddress;

		if (fast != last)
		{
			slow = slow->nextAddress;
			fast = fast->nextAddress;
		}
	}

	return slow;
}

void BinarySearchTutorID()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to search!" << endl;
		return;
	}

	int keyword;

	cout << endl << "Enter Tutor ID whose record you want to search: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Tutor ID whose record you want to search: ";
		cin >> keyword;
	}

	auto starttime = high_resolution_clock::now();

	Tutors* start = tutorshead;
	Tutors* last = NULL;

	do
	{
		Tutors* tutorsmiddle = findMiddleTutor(start, last);

		if (tutorsmiddle == NULL)
		{
			cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
			return;
		}

		if (tutorsmiddle->TutorID == keyword)
		{
			time_t t_join = tutorsmiddle->Join_Date;
			struct tm now_join;
			localtime_s(&now_join, &t_join);

			int date_join = now_join.tm_mday;
			int month_join = 1 + now_join.tm_mon;
			int year_join = 1900 + now_join.tm_year;

			int date_terminate;
			int month_terminate;
			int year_terminate;

			time_t t_terminate = tutorsmiddle->Term_Date;
			struct tm now_terminate;
			localtime_s(&now_terminate, &t_terminate);

			if (t_terminate == 0)
			{
				date_terminate = 0;
				month_terminate = 0;
				year_terminate = 0;
			}
			else
			{
				date_terminate = now_terminate.tm_mday;
				month_terminate = 1 + now_terminate.tm_mon;
				year_terminate = 1900 + now_terminate.tm_year;
			}

			string centreName = convertCentreCodeToName(tutorsmiddle->Centre_Code);
			string subjectName = convertSubjectCodeToName(tutorsmiddle->Subject_Code);

			cout << tutorsmiddle->TutorID << " - " << tutorsmiddle->Name << " - " << date_join << "/" << month_join 
				<< "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
				<< " - " << tutorsmiddle->Hourly_Rate << " - " << tutorsmiddle->Phone << " - " << tutorsmiddle->Address << " - " << centreName
				<< " - " << subjectName << " - " << tutorsmiddle->Rating << endl;
			auto stoptime = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stoptime - starttime);
			cout << "Binary Search Time Used: " << duration.count() << " microseconds" << endl;
			return;
		}
		else if (tutorsmiddle->TutorID < keyword)
		{
			start = tutorsmiddle->nextAddress;
		}
		else
		{
			last = tutorsmiddle;
		}
	} while (last == NULL || last != start);

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	cout << "Binary Search Time Used: " << duration.count() << " microseconds" << endl;
	cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
}

void BinarySearchRating()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to search!" << endl;
		return;
	}

	float keyword;

	cout << endl << "Enter Rating that you want to search: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Rating that you want to search: ";
		cin >> keyword;
	}

	auto starttime = high_resolution_clock::now();

	Tutors* start = tutorshead;
	Tutors* last = NULL;
	Tutors* temp = NULL;

	do
	{
		Tutors* tutorsmiddle = findMiddleTutor(start, last);

		if (tutorsmiddle == NULL)
		{
			break;
		}

		if (tutorsmiddle->Rating == keyword)
		{
			time_t t_join = tutorsmiddle->Join_Date;
			struct tm now_join;
			localtime_s(&now_join, &t_join);

			int date_join = now_join.tm_mday;
			int month_join = 1 + now_join.tm_mon;
			int year_join = 1900 + now_join.tm_year;

			int date_terminate;
			int month_terminate;
			int year_terminate;

			time_t t_terminate = tutorsmiddle->Term_Date;
			struct tm now_terminate;
			localtime_s(&now_terminate, &t_terminate);

			if (t_terminate == 0)
			{
				date_terminate = 0;
				month_terminate = 0;
				year_terminate = 0;
			}
			else
			{
				date_terminate = now_terminate.tm_mday;
				month_terminate = 1 + now_terminate.tm_mon;
				year_terminate = 1900 + now_terminate.tm_year;
			}

			string centreName = convertCentreCodeToName(tutorsmiddle->Centre_Code);
			string subjectName = convertSubjectCodeToName(tutorsmiddle->Subject_Code);

			cout << tutorsmiddle->TutorID << " - " << tutorsmiddle->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
				<< " - " << tutorsmiddle->Hourly_Rate << " - " << tutorsmiddle->Phone << " - " << tutorsmiddle->Address << " - " << centreName
				<< " - " << subjectName << " - " << tutorsmiddle->Rating << endl;
			temp = tutorsmiddle->prevAddress;

			while (temp != NULL)
			{
				if (temp->Rating == keyword)
				{
					time_t t_join = temp->Join_Date;
					struct tm now_join;
					localtime_s(&now_join, &t_join);

					int date_join = now_join.tm_mday;
					int month_join = 1 + now_join.tm_mon;
					int year_join = 1900 + now_join.tm_year;

					int date_terminate;
					int month_terminate;
					int year_terminate;

					time_t t_terminate = temp->Term_Date;
					struct tm now_terminate;
					localtime_s(&now_terminate, &t_terminate);

					if (t_terminate == 0)
					{
						date_terminate = 0;
						month_terminate = 0;
						year_terminate = 0;
					}
					else
					{
						date_terminate = now_terminate.tm_mday;
						month_terminate = 1 + now_terminate.tm_mon;
						year_terminate = 1900 + now_terminate.tm_year;
					}

					string centreName = convertCentreCodeToName(temp->Centre_Code);
					string subjectName = convertSubjectCodeToName(temp->Subject_Code);

					cout << temp->TutorID << " - " << temp->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
						<< " - " << temp->Hourly_Rate << " - " << temp->Phone << " - " << temp->Address << " - " << centreName
						<< " - " << subjectName << " - " << temp->Rating << endl;
				}
				if (temp->prevAddress != NULL)
				{
					if (temp->prevAddress->Rating != keyword)
					{
						break;
					}
				}
				temp = temp->prevAddress;
			}

			temp = tutorsmiddle->nextAddress;

			while (temp != NULL)
			{
				if (temp->Rating == keyword)
				{
					time_t t_join = temp->Join_Date;
					struct tm now_join;
					localtime_s(&now_join, &t_join);

					int date_join = now_join.tm_mday;
					int month_join = 1 + now_join.tm_mon;
					int year_join = 1900 + now_join.tm_year;

					int date_terminate;
					int month_terminate;
					int year_terminate;

					time_t t_terminate = temp->Term_Date;
					struct tm now_terminate;
					localtime_s(&now_terminate, &t_terminate);

					if (t_terminate == 0)
					{
						date_terminate = 0;
						month_terminate = 0;
						year_terminate = 0;
					}
					else
					{
						date_terminate = now_terminate.tm_mday;
						month_terminate = 1 + now_terminate.tm_mon;
						year_terminate = 1900 + now_terminate.tm_year;
					}

					string centreName = convertCentreCodeToName(temp->Centre_Code);
					string subjectName = convertSubjectCodeToName(temp->Subject_Code);

					cout << temp->TutorID << " - " << temp->Name << " - " << date_join << "/" << month_join << "/" << year_join << " - " << date_terminate << "/" << month_terminate << "/" << year_terminate
						<< " - " << temp->Hourly_Rate << " - " << temp->Phone << " - " << temp->Address << " - " << centreName
						<< " - " << subjectName << " - " << temp->Rating << endl;
				}
				if (temp->nextAddress != NULL)
				{
					if (temp->nextAddress->Rating != keyword)
					{
						break;
					}
				}
				temp = temp->nextAddress;
			}
			auto stoptime = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stoptime - starttime);
			cout << "Binary Search Time Used: " << duration.count() << " microseconds" << endl;
			return;
		}
		else if (tutorsmiddle->Rating < keyword)
		{
			start = tutorsmiddle->nextAddress;
		}
		else
		{
			last = tutorsmiddle;
		}
	} while (last == NULL || last != start);

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	cout << "Binary Search Time Used: " << duration.count() << " microseconds" << endl;
	cout << endl << "Rating as " << keyword << " is not found in the record!" << endl;
}

void bubbleSortforTutorID(int command)
{
	auto starttime = high_resolution_clock::now();

	Tutors* tutorsbefore, * tutorsafter;
	Tutors* tutorscurrent = tutorshead;

	bool sorted = false;

	if (tutorscurrent == NULL)
	{
		return;
	}

	while (sorted == false)
	{
		sorted = true;
		tutorscurrent = tutorshead;

		while (tutorscurrent->nextAddress != NULL)
		{
			if (tutorscurrent->TutorID > tutorscurrent->nextAddress->TutorID)
			{
				tutorsbefore = tutorscurrent->prevAddress;
				tutorsafter = tutorscurrent->nextAddress;

				if (tutorsbefore != NULL)
				{
					tutorsbefore->nextAddress = tutorsafter;
				}
				else
				{
					tutorshead = tutorsafter;
				}

				tutorscurrent->nextAddress = tutorsafter->nextAddress;
				if (tutorsafter->nextAddress != NULL)
				{
					tutorsafter->nextAddress->prevAddress = tutorscurrent;
				}
				tutorscurrent->prevAddress = tutorsafter;
				tutorsafter->nextAddress = tutorscurrent;
				tutorsafter->prevAddress = tutorsbefore;

				sorted = false;
			}
			else
			{
				tutorscurrent = tutorscurrent->nextAddress;
			}
		}
	}

	tutorstail = NULL;
	tutorscurrent = tutorshead;
	while (tutorscurrent != NULL)
	{
		tutorstail = tutorscurrent;
		tutorscurrent = tutorscurrent->nextAddress;
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	if (command == 1)
	{
		cout << "Bubble Sort Time Used: " << duration.count() << " microseconds" << endl;
	}
}

void bubbleSortforHourlyRate(int command)
{
	auto starttime = high_resolution_clock::now();

	Tutors* tutorsbefore, * tutorsafter;
	Tutors* tutorscurrent = tutorshead;

	bool sorted = false;

	if (tutorscurrent == NULL)
	{
		return;
	}

	while (sorted == false)
	{
		sorted = true;
		tutorscurrent = tutorshead;

		while (tutorscurrent->nextAddress != NULL)
		{
			if (tutorscurrent->Hourly_Rate > tutorscurrent->nextAddress->Hourly_Rate)
			{
				tutorsbefore = tutorscurrent->prevAddress;
				tutorsafter = tutorscurrent->nextAddress;

				if (tutorsbefore != NULL)
				{
					tutorsbefore->nextAddress = tutorsafter;
				}
				else
				{
					tutorshead = tutorsafter;
				}

				tutorscurrent->nextAddress = tutorsafter->nextAddress;
				if (tutorsafter->nextAddress != NULL)
				{
					tutorsafter->nextAddress->prevAddress = tutorscurrent;
				}
				tutorscurrent->prevAddress = tutorsafter;
				tutorsafter->nextAddress = tutorscurrent;
				tutorsafter->prevAddress = tutorsbefore;

				sorted = false;
			}
			else
			{
				tutorscurrent = tutorscurrent->nextAddress;
			}
		}
	}

	tutorstail = NULL;
	tutorscurrent = tutorshead;
	while (tutorscurrent != NULL)
	{
		tutorstail = tutorscurrent;
		tutorscurrent = tutorscurrent->nextAddress;
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	if (command == 1)
	{
		cout << "Bubble Sort Time Used: " << duration.count() << " microseconds" << endl;
	}
}

void bubbleSortforRating(int command)
{
	auto starttime = high_resolution_clock::now();

	Tutors* tutorsbefore, * tutorsafter;
	Tutors* tutorscurrent = tutorshead;

	bool sorted = false;

	if (tutorscurrent == NULL)
	{
		return;
	}

	while (sorted == false)
	{
		sorted = true;
		tutorscurrent = tutorshead;

		while (tutorscurrent->nextAddress != NULL)
		{
			if (tutorscurrent->Rating > tutorscurrent->nextAddress->Rating)
			{
				tutorsbefore = tutorscurrent->prevAddress;
				tutorsafter = tutorscurrent->nextAddress;

				if (tutorsbefore != NULL)
				{
					tutorsbefore->nextAddress = tutorsafter;
				}
				else
				{
					tutorshead = tutorsafter;
				}

				tutorscurrent->nextAddress = tutorsafter->nextAddress;
				if (tutorsafter->nextAddress != NULL)
				{
					tutorsafter->nextAddress->prevAddress = tutorscurrent;
				}
				tutorscurrent->prevAddress = tutorsafter;
				tutorsafter->nextAddress = tutorscurrent;
				tutorsafter->prevAddress = tutorsbefore;

				sorted = false;
			}
			else
			{
				tutorscurrent = tutorscurrent->nextAddress;
			}
		}
	}

	tutorstail = NULL;
	tutorscurrent = tutorshead;
	while (tutorscurrent != NULL)
	{
		tutorstail = tutorscurrent;
		tutorscurrent = tutorscurrent->nextAddress;
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	if (command == 1)
	{
		cout << "Bubble Sort Time Used: " << duration.count() << " microseconds" << endl;
	}

}

void bubbleSortTutorName()
{
	Tutors* tutorsbefore, * tutorsafter;
	Tutors* tutorscurrent = tutorshead;

	bool sorted = false;

	if (tutorscurrent == NULL)
	{
		return;
	}

	while (sorted == false)
	{
		sorted = true;
		tutorscurrent = tutorshead;

		while (tutorscurrent->nextAddress != NULL)
		{
			if (tutorscurrent->Name > tutorscurrent->nextAddress->Name)
			{
				tutorsbefore = tutorscurrent->prevAddress;
				tutorsafter = tutorscurrent->nextAddress;

				if (tutorsbefore != NULL)
				{
					tutorsbefore->nextAddress = tutorsafter;
				}
				else
				{
					tutorshead = tutorsafter;
				}

				tutorscurrent->nextAddress = tutorsafter->nextAddress;
				if (tutorsafter->nextAddress != NULL)
				{
					tutorsafter->nextAddress->prevAddress = tutorscurrent;
				}
				tutorscurrent->prevAddress = tutorsafter;
				tutorsafter->nextAddress = tutorscurrent;
				tutorsafter->prevAddress = tutorsbefore;

				sorted = false;
			}
			else
			{
				tutorscurrent = tutorscurrent->nextAddress;
			}
		}
	}

	tutorstail = NULL;
	tutorscurrent = tutorshead;
	while (tutorscurrent != NULL)
	{
		tutorstail = tutorscurrent;
		tutorscurrent = tutorscurrent->nextAddress;
	}

}

void sortedInsertTutorID(Tutors** tutorssorted, Tutors* tutorscurrent)
{
	Tutors* tutorscurrent2;

	if (*tutorssorted == NULL)
	{
		*tutorssorted = tutorscurrent;
	}
	else if ((*tutorssorted)->TutorID >= tutorscurrent->TutorID)
	{
		tutorscurrent->nextAddress = *tutorssorted;
		tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		*tutorssorted = tutorscurrent;
	}
	else
	{
		tutorscurrent2 = *tutorssorted;

		while (tutorscurrent2->nextAddress != NULL && tutorscurrent2->nextAddress->TutorID < tutorscurrent->TutorID)
		{
			tutorscurrent2 = tutorscurrent2->nextAddress;
		}

		tutorscurrent->nextAddress = tutorscurrent2->nextAddress;

		if (tutorscurrent2->nextAddress != NULL)
		{
			tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		}

		tutorscurrent2->nextAddress = tutorscurrent;
		tutorscurrent->prevAddress = tutorscurrent2;
	}
}

void sortedInsertHourlyRate(Tutors **tutorssorted, Tutors *tutorscurrent)
{
	Tutors* tutorscurrent2;

	if (*tutorssorted == NULL)
	{
		*tutorssorted = tutorscurrent;
	}
	else if ((* tutorssorted)->Hourly_Rate >= tutorscurrent->Hourly_Rate)
	{
		tutorscurrent->nextAddress = *tutorssorted;
		tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		*tutorssorted = tutorscurrent;
	}
	else
	{
		tutorscurrent2 = *tutorssorted;

		while (tutorscurrent2->nextAddress != NULL && tutorscurrent2->nextAddress->Hourly_Rate < tutorscurrent->Hourly_Rate)
		{
			tutorscurrent2 = tutorscurrent2->nextAddress;
		}

		tutorscurrent->nextAddress = tutorscurrent2->nextAddress;

		if (tutorscurrent2->nextAddress != NULL)
		{
			tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		}

		tutorscurrent2->nextAddress = tutorscurrent;
		tutorscurrent->prevAddress = tutorscurrent2;
	}
}

void sortedInsertRating(Tutors** tutorssorted, Tutors* tutorscurrent)
{
	Tutors* tutorscurrent2;

	if (*tutorssorted == NULL)
	{
		*tutorssorted = tutorscurrent;
	}
	else if ((*tutorssorted)->Rating >= tutorscurrent->Rating)
	{
		tutorscurrent->nextAddress = *tutorssorted;
		tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		*tutorssorted = tutorscurrent;
	}
	else
	{
		tutorscurrent2 = *tutorssorted;

		while (tutorscurrent2->nextAddress != NULL && tutorscurrent2->nextAddress->Rating < tutorscurrent->Rating)
		{
			tutorscurrent2 = tutorscurrent2->nextAddress;
		}

		tutorscurrent->nextAddress = tutorscurrent2->nextAddress;

		if (tutorscurrent2->nextAddress != NULL)
		{
			tutorscurrent->nextAddress->prevAddress = tutorscurrent;
		}

		tutorscurrent2->nextAddress = tutorscurrent;
		tutorscurrent->prevAddress = tutorscurrent2;
	}
}

void insertionSort(int code, int command)
{
	auto starttime = high_resolution_clock::now();

	Tutors* tutorssorted = NULL;
	Tutors* tutorscurrent = tutorshead;

	while (tutorscurrent != NULL)
	{
		Tutors* nexttutors = tutorscurrent->nextAddress;

		tutorscurrent->prevAddress = tutorscurrent->nextAddress = NULL;

		if (code == 1)
		{
			sortedInsertTutorID(&tutorssorted, tutorscurrent);
		}
		else if (code == 2)
		{
			sortedInsertHourlyRate(&tutorssorted, tutorscurrent);
		}
		else
		{
			sortedInsertRating(&tutorssorted, tutorscurrent);
		}

		tutorscurrent = nexttutors;
	}

	tutorshead = tutorssorted;
	tutorstail = NULL;

	tutorscurrent = tutorshead;
	while (tutorscurrent != NULL)
	{
		tutorstail = tutorscurrent;
		tutorscurrent = tutorscurrent->nextAddress;
	}

	auto stoptime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stoptime - starttime);
	if (command == 1)
	{
		cout << "Insertion Sort Time Used: " << duration.count() << " microseconds" << endl;
	}
}

void deleteTutor()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to delete!" << endl;
		return;
	}

	int keyword;

	cout << endl << "Enter Tutor ID whose record you want to delete: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Tutor ID whose record you want to delete: ";
		cin >> keyword;
	}

	//scenario 2: head tutor id = keyword
	if (tutorshead->TutorID == keyword) //delete from the front
	{
		Tutors* tutorscurrent = tutorshead;
		tutorshead = tutorshead->nextAddress;
		if (tutorshead != NULL) // head is still not empty
		{
			tutorshead->prevAddress = NULL;
		}
		else //head = null
		{
			tutorstail = NULL;
		}
		countNumberOfTutorsperCentre(tutorscurrent->Centre_Code, 2);
		cout << endl << "Tutor with Tutor ID as " << keyword << " is deleted from the record!" << endl;
		delete tutorscurrent;
		sizeofTutorsLinkedList--;
		return;
	}
	//scenario 3: tail tutor id = keyword
	else if (tutorstail->TutorID == keyword) //delete from the end
	{
		Tutors* tutorscurrent = tutorstail;
		tutorstail = tutorstail->prevAddress;
		if (tutorstail != NULL) // tail is still not empty
		{
			tutorstail->nextAddress = NULL;
		}
		else //tail = null
		{
			tutorshead = NULL;
		}
		countNumberOfTutorsperCentre(tutorscurrent->Centre_Code, 2);
		cout << endl << "Tutor with Tutor ID as " << keyword << " is deleted from the record!" << endl;
		delete tutorscurrent;
		sizeofTutorsLinkedList--;
		return;
	}
	//scenario 4: where the keyword unable to find in first and last item
	else
	{
		Tutors* tutorscurrent = tutorshead->nextAddress;

		while (tutorscurrent != NULL)
		{
			if (tutorscurrent->TutorID == keyword)
			{
				tutorscurrent->prevAddress->nextAddress = tutorscurrent->nextAddress;
				tutorscurrent->nextAddress->prevAddress = tutorscurrent->prevAddress;
				countNumberOfTutorsperCentre(tutorscurrent->Centre_Code, 2);
				cout << endl <<"Tutor with Tutor ID as " << keyword << " is deleted from the record!" << endl;
				delete tutorscurrent;
				sizeofTutorsLinkedList--;
				return;
			}
			tutorscurrent = tutorscurrent->nextAddress;
		}
	}
	cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
}

void modifyTutor()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to modify!" << endl;
		return;
	}

	int keyword, criteria;

	cout << endl << "Enter Tutor ID whose record you want to modify: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Tutor ID whose record you want to modify: ";
		cin >> keyword;
	}

	//scenario 2: head tutor id = keyword
	if (tutorshead->TutorID == keyword) 
	{
		cout << endl << "What do you want to modify?";
		cout << endl << "1. Tutor Phone";
		cout << endl << "2. Tutor Address";
		cout << endl << "3. Tutor Termination Date";
		cout << endl << "Your choice: ";
		cin >> criteria;
		while (cin.fail() || criteria < 1 || criteria > 3)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid Input!";
			cout << endl << "What do you want to modify?";
			cout << endl << "1. Tutor Phone";
			cout << endl << "2. Tutor Address";
			cout << endl << "3. Tutor Termination Date";
			cout << endl << "Your choice: ";
			cin >> criteria;
		}

		if (criteria == 1)
		{
			system("cls");

			int phone_temporary;

			cout << endl << "Enter Tutor New Phone Number: ";
			cin >> phone_temporary;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter Tutor New Phone Number: ";
				cin >> phone_temporary;
			}

			tutorshead->Phone = phone_temporary;
		}
		else if (criteria == 2)
		{
			system("cls");

			string address_temporary;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter Tutor New Address: ";
			getline(cin, address_temporary);
			while (cin.fail())
			{
				cout << endl << "Enter Tutor New Address: ";
				getline(cin, address_temporary);
			}

			tutorshead->Address = address_temporary;
		}
		else
		{
			system("cls");

			string term_date;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
			cin >> term_date;
			bool flag = checkDateValid(term_date);
			while (cin.fail() || flag)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
				cin >> term_date;
				flag = checkDateValid(term_date);
			}

			tutorshead->Term_Date = toTimeStamp(term_date);
		}
		checkTermination();
		return;
	}
	//scenario 3: tail tutor id = keyword
	else if (tutorstail->TutorID == keyword)
	{
		cout << endl << "What do you want to modify?";
		cout << endl << "1. Tutor Phone";
		cout << endl << "2. Tutor Address";
		cout << endl << "3. Tutor Termination Date";
		cout << endl << "Your choice: ";
		cin >> criteria;
		while (cin.fail() || criteria < 1 || criteria > 3)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Invalid Input!";
			cout << endl << "What do you want to modify?";
			cout << endl << "1. Tutor Phone";
			cout << endl << "2. Tutor Address";
			cout << endl << "3. Tutor Termination Date";
			cout << endl << "Your choice: ";
			cin >> criteria;
		}

		if (criteria == 1)
		{
			system("cls");

			int phone_temporary;

			cout << endl << "Enter Tutor New Phone Number: ";
			cin >> phone_temporary;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter Tutor New Phone Number: ";
				cin >> phone_temporary;
			}

			tutorstail->Phone = phone_temporary;
		}
		else if (criteria == 2)
		{
			system("cls");

			string address_temporary;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter Tutor New Address: ";
			getline(cin, address_temporary);
			while (cin.fail())
			{
				cout << endl << "Enter Tutor New Address: ";
				getline(cin, address_temporary);
			}

			tutorstail->Address = address_temporary;
		}
		else
		{
			system("cls");

			string term_date;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
			cin >> term_date;
			bool flag = checkDateValid(term_date);
			while (cin.fail() || flag)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
				cin >> term_date;
				flag = checkDateValid(term_date);
			}

			tutorstail->Term_Date = toTimeStamp(term_date);
		}
		checkTermination();
		return;
	}
	//scenario 4: where the keyword unable to find in first and last item
	else
	{
		Tutors* tutorscurrent = tutorshead->nextAddress;

		while (tutorscurrent != NULL)
		{
			if (tutorscurrent->TutorID == keyword)
			{
				cout << endl << "What do you want to modify?";
				cout << endl << "1. Tutor Phone";
				cout << endl << "2. Tutor Address";
				cout << endl << "3. Tutor Termination Date";
				cout << endl << "Your choice: ";
				cin >> criteria;
				while (cin.fail() || criteria < 1 || criteria > 3)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid Input!";
					cout << endl << "What do you want to modify?";
					cout << endl << "1. Tutor Phone";
					cout << endl << "2. Tutor Address";
					cout << endl << "3. Tutor Termination Date";
					cout << endl << "Your choice: ";
					cin >> criteria;
				}

				if (criteria == 1)
				{
					system("cls");

					int phone_temporary;

					cout << endl << "Enter Tutor New Phone Number: ";
					cin >> phone_temporary;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << endl << "Enter Tutor New Phone Number: ";
						cin >> phone_temporary;
					}

					tutorscurrent->Phone = phone_temporary;
				}
				else if (criteria == 2)
				{
					system("cls");

					string address_temporary;

					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Enter Tutor New Address: ";
					getline(cin, address_temporary);
					while (cin.fail())
					{
						cout << endl << "Enter Tutor New Address: ";
						getline(cin, address_temporary);
					}

					tutorscurrent->Address = address_temporary;
				}
				else
				{
					system("cls");

					string term_date;

					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
					cin >> term_date;
					bool flag = checkDateValid(term_date);
					while (cin.fail() || flag)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << endl << "Enter Tutor Termination Date (YYYY-MM-DD): ";
						cin >> term_date;
						flag = checkDateValid(term_date);
					}

					tutorscurrent->Term_Date = toTimeStamp(term_date);
				}
				checkTermination();
				return;
			}
			checkTermination();
			tutorscurrent = tutorscurrent->nextAddress;
		}
	}
	checkTermination();
	cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
}

void giveTutorRating()
{
	//scenario 1: list is still empty
	if (tutorshead == NULL)
	{
		cout << "No tutor being recorded yet! Nothing to rate!" << endl;
		return;
	}

	int keyword;
	float rating;

	cout << endl << "Enter Tutor ID that you want to give rate: ";
	cin >> keyword;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Enter Tutor ID that you want to give rate: ";
		cin >> keyword;
	}

	//scenario 2: head tutor id = keyword
	if (tutorshead->TutorID == keyword)
	{
		cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
		cin >> rating;
		while (cin.fail() || rating < 1.0 || rating > 5.0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
			cin >> rating;
		}

		float final_rating = tutorshead->Rating * tutorshead->Rating_No + rating;
		tutorshead->Rating_No++;
		final_rating = final_rating / (float)tutorshead->Rating_No;
		tutorshead->Rating = final_rating;

		return;
	}
	//scenario 3: tail tutor id = keyword
	else if (tutorstail->TutorID == keyword)
	{
		cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
		cin >> rating;
		while (cin.fail() || rating < 1.0 || rating > 5.0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
			cin >> rating;
		}

		float final_rating = tutorstail->Rating * tutorstail->Rating_No + rating;
		tutorstail->Rating_No++;
		final_rating = final_rating / (float)tutorstail->Rating_No;
		tutorstail->Rating = final_rating;

		return;
	}
	//scenario 4: where the keyword unable to find in first and last item
	else
	{
		Tutors* tutorscurrent = tutorshead->nextAddress;

		while (tutorscurrent != NULL)
		{
			if (tutorscurrent->TutorID == keyword)
			{
				cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
				cin >> rating;
				while (cin.fail() || rating < 1.0 || rating > 5.0)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Enter your rating for this tutor (1.0 - 5.0): ";
					cin >> rating;
				}

				float final_rating = tutorscurrent->Rating * tutorscurrent->Rating_No + rating;
				tutorscurrent->Rating_No++;
				final_rating = final_rating / (float)tutorscurrent->Rating_No;
				tutorscurrent->Rating = final_rating;

				return;
			}
			tutorscurrent = tutorscurrent->nextAddress;
		}
	}
	cout << endl << "Tutor with Tutor ID as " << keyword << " is not found in the record!" << endl;
}

void generateReport(int centre_code)
{
	float percentage;

	if (centrehead == NULL || tutorshead == NULL)
	{
		cout << "No centre and tutor being recorded yet! Nothing to generate!" << endl;
		return;
	}

	if (centre_code == 0)
	{
		Centre* centrecurrent = centrehead;

		while (centrecurrent != NULL)
		{
			cout << endl;
			cout << "=========================================================" << endl;
			cout << "                          REPORT                         " << endl;
			cout << "=========================================================" << endl;
			cout << "Centre Name: " << centrecurrent->Centre_Name << endl;
			cout << "Total number of tutor(s): " << centrecurrent->Tutors_Total << endl;
			cout << "Total number of terminated tutor(s): " << centrecurrent->Tutors_Terminated << endl;
			if (centrecurrent->Tutors_Total == 0)
			{
				percentage = 0;
			}
			else
			{
				percentage = (float)centrecurrent->Tutors_Terminated / (float)centrecurrent->Tutors_Total * 100;
			}
			cout << "Percentage of termination: " << percentage << "%" << endl;

			if (percentage >= 50)
			{
				cout << "<ALERT>This centre needs more tutor(s) to be hired!<ALERT>" << endl;
			}
			centrecurrent = centrecurrent->nextAddress;
		}

		return;
	}
	else if (centrehead->CentreCode == centre_code)
	{
		cout << "=========================================================" << endl;
		cout << "                          REPORT                         " << endl;
		cout << "=========================================================" << endl;
		cout << "Centre Name: " << centrehead->Centre_Name << endl;
		cout << "Total number of tutor(s): " << centrehead->Tutors_Total << endl;
		cout << "Total number of terminated tutor(s): " << centrehead->Tutors_Terminated << endl;
		if (centrehead->Tutors_Total == 0)
		{
			percentage = 0;
		}
		else
		{
			percentage = (float)centrehead->Tutors_Terminated / (float)centrehead->Tutors_Total * 100;
		}
		cout << "Percentage of termination: " << percentage << "%" << endl;

		if (percentage >= 50)
		{
			cout << "<ALERT>This centre needs more tutor(s) to be hired!<ALERT>" << endl;
		}

		return;
	}
	else if (centretail->CentreCode == centre_code)
	{
		cout << "=========================================================" << endl;
		cout << "                          REPORT                         " << endl;
		cout << "=========================================================" << endl;
		cout << "Centre Name: " << centretail->Centre_Name << endl;
		cout << "Total number of tutor(s): " << centretail->Tutors_Total << endl;
		cout << "Total number of terminated tutor(s): " << centretail->Tutors_Terminated << endl;
		if (centretail->Tutors_Total == 0)
		{
			percentage = 0;
		}
		else
		{
			percentage = (float)centretail->Tutors_Terminated / (float)centretail->Tutors_Total * 100;
		}
		cout << "Percentage of termination: " << percentage << "%" << endl;

		if (percentage >= 50)
		{
			cout << "<ALERT>This centre needs more tutor(s) to be hired!<ALERT>" << endl;
		}

		return;
	}
	else
	{
		Centre* centrecurrent = centrehead->nextAddress;

		while (centrecurrent != NULL)
		{
			if (centrecurrent->CentreCode == centre_code)
			{
				cout << "=========================================================" << endl;
				cout << "                          REPORT                         " << endl;
				cout << "=========================================================" << endl;
				cout << "Centre Name: " << centrecurrent->Centre_Name << endl;
				cout << "Total number of tutor(s): " << centrecurrent->Tutors_Total << endl;
				cout << "Total number of terminated tutor(s): " << centrecurrent->Tutors_Terminated << endl;
				if (centrecurrent->Tutors_Total == 0)
				{
					percentage = 0;
				}
				else
				{
					percentage = (float)centrecurrent->Tutors_Terminated / (float)centrecurrent->Tutors_Total * 100;
				}
				cout << "Percentage of termination: " << percentage << "%" << endl;

				if (percentage >= 50)
				{
					cout << "<ALERT>This centre needs more tutor(s) to be hired!<ALERT>" << endl;
				}

				return;
			}
			centrecurrent = centrecurrent->nextAddress;
		}
	}
}


int main()
{
	int option = 0;
	int centreCode = 1;
	int subjectCode = 1;
	int IDuser = 1;
	int IDtutor = 1;

	usershead = userstail = NULL;
	tutorshead = tutorstail = NULL;
	centrehead = centretail = NULL;
	subjecthead = subjecttail = NULL;

	Centre* centreNewnode = CreateNewCentre(centreCode, "HEAD QUARTER", "Jalan Bukit Bintang No. 1", "WP Kuala Lumpur", 0, 0);
	inserintoEndofCentreLinkedList(centreNewnode);
	centreCode++;

	centreNewnode = CreateNewCentre(centreCode, "Bukit Jalil", "Jalan Taman Teknologi No. 1", "WP Kuala Lumpur", 0, 0);
	inserintoEndofCentreLinkedList(centreNewnode);
	centreCode++;

	centreNewnode = CreateNewCentre(centreCode, "Sungai Besi", "Kem, Sungai Besi, 57000 Kuala Lumpur", "Selangor ", 0, 0);
	inserintoEndofCentreLinkedList(centreNewnode);
	centreCode++;

	centreNewnode = CreateNewCentre(centreCode, "Platinum Lake", "Jalan Langkawi, Taman Danau Kota, 53100 Kuala Lumpur, Wilayah Persekutuan Kuala Lumpur", "WP Kuala Lumpur", 0, 0);
	inserintoEndofCentreLinkedList(centreNewnode);
	centreCode++;

	Users* usersNewnode = CreateNewUser(IDuser, "sawchanghau", "sch123", "STUDENT", 1);
	inserintoEndofUsersLinkedList(usersNewnode);
	IDuser++;

	usersNewnode = CreateNewUser(IDuser, "taihongyi", "thy123", "ADMIN", 1);
	inserintoEndofUsersLinkedList(usersNewnode);
	IDuser++;

	usersNewnode = CreateNewUser(IDuser, "laurentiusmichael", "lm123", "HR MANAGER", 1);
	inserintoEndofUsersLinkedList(usersNewnode);
	IDuser++;

	Subject* subjectNewnode = CreateNewSubject(subjectCode, "Data Structure");
	inserintoEndofSubjectLinkedList(subjectNewnode);
	subjectCode++;

	subjectNewnode = CreateNewSubject(subjectCode, "Object Oriented Programming");
	inserintoEndofSubjectLinkedList(subjectNewnode);
	subjectCode++;

	time_t date_of_today = todayDate();

	Tutors* tutorsNewnode = CreateNewTutor(IDtutor, "James", date_of_today, 0, 10, 1234567, "Jalan Teknologi No. 1", 2, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(2, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Louis", date_of_today, 0, 20, 7654321, "Jalan Inovasi No. 1", 2, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(2, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Andrew", date_of_today, 0, 15, 8473920, "Jalan Jendral Sudirman No. 3", 3, 2, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(3, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Benedict", date_of_today, 0, 30, 6290378, "Jalan MH Thamrin No. 45", 4, 2, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(4, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Lily", date_of_today, 0, 33, 8183232, "Jalan Jatinegara No. 8", 1, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(1, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Ivory", date_of_today, 0, 5, 2893093, "Jalan Braga No. 62", 1, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(1, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Sanjaya", date_of_today, 0, 18, 5320998, "Jalan Raden Saleh No. 8", 2, 2, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(2, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Petrus", date_of_today, 0, 27, 3728884, "Jalan Pantai Indah Kapuk No. 72", 1, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(1, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Ambar", date_of_today, 0, 13, 2239877, "Jalan Kebon Pala No. 88", 3, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(3, 1);

	tutorsNewnode = CreateNewTutor(IDtutor, "Jeffry", date_of_today, 0, 13, 6643374, "Jalan Matraman Raya No. 90", 4, 1, 0, 0);
	inserintoEndofTutorsLinkedList(tutorsNewnode);
	IDtutor++;
	countNumberOfTutorsperCentre(4, 1);

	cout << string(100, '=') << endl;
	cout << "\t\t\tWELCOME TO EXCEL TUITION CENTRE MANAGEMEMT SYSTEM" << endl;
	cout << string(100, '=') << endl << endl << endl << endl;

	cout << "Press <enter> to start!";

	while (option == 0)
	{
		int sub_option = 0;
		int ID = enterUsername();

		while (ID == 0)
		{
			cout << "Username not found, please enter the correct username!" << endl;
			ID = enterUsername();
		}

		int signal = enterPassword(ID);

		while (signal == 0)
		{
			cout << "Wrong password, please enter your correct password!" << endl;
			signal = enterPassword(ID);
		}


		if (signal == 1)
		{
			while (sub_option == 0)
			{
				system("cls");

				int choice = 0;
				
				do
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Please choose one of these student functionalities: " << endl;
					cout << "1. Display All Tutor Records" << endl;
					cout << "2. Rate a Tutor" << endl;
					cout << "Your chosen option: ";
					cin >> choice;
				} while (cin.fail() || choice < 1 || choice > 2);

				if (choice == 1)
				{
					system("cls");
					bubbleSortTutorName();
					displayTutorsLinkedList();
				}
				else
				{
					system("cls");
					giveTutorRating();
				}

				cout << endl << "Do you still want to continue accessing student functionalities? 0 - Yes, others - No : ";
				cin >> sub_option;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Do you still want to continue accessing student functionalities? 0 - Yes, others - No : ";
					cin >> sub_option;
				}
			}
		}
		else if (signal == 2)
		{
			while (sub_option == 0)
			{
				system("cls");

				int choice = 0;
				
				do
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Please choose one of these admin functionalities: " << endl;
					cout << "1. Display Tutor Records" << endl;
					cout << "2. Generate Report" << endl;
					cout << "Your chosen option: ";
					cin >> choice;
				} while (cin.fail() || choice < 1 || choice > 2);

				int userCentreCode = getCentreCodeBasedOnID(ID);

				if (choice == 1)
				{
					system("cls");
					bubbleSortTutorName();
					displayTutorsLinkedListBasedOnCentreCode(userCentreCode);
				}
				else
				{
					system("cls");
					generateReport(userCentreCode);
				}

				cout << endl << "Do you still want to continue accessing admin functionalities? 0 - Yes, others - No : ";
				cin >> sub_option;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Do you still want to continue accessing admin functionalities? 0 - Yes, others - No : ";
					cin >> sub_option;
				}
			}
		}
		else
		{
			while (sub_option == 0)
			{
				system("cls");

				int choice = 0;

				do
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Please choose one of these HR Manager functionalities: " << endl;
					cout << "1. Add a Tutor Record" << endl;
					cout << "2. Display All Tutor Records" << endl;
					cout << "3. Search a Tutor by Tutor ID" << endl;
					cout << "4. Search Tutors by overall performance (Rating)" << endl;
					cout << "5. Sort and display by Tutors ID in ascending order" << endl;
					cout << "6. Sort and display by Tutors Hourly Pay Rate in ascending order" << endl;
					cout << "7. Sort and display by Tutors Overall Performance in ascending order" << endl;
					cout << "8. Modify a Tutor Record" << endl;
					cout << "9. Delete a Tutor Record" << endl;
					cout << "10. Add a New User" << endl;
					cout << "11. Add a New Centre" << endl;
					cout << "12. Add a New Subject" << endl;
					cout << "13. Generate Report" << endl;
					cout << "Your chosen option: ";
					cin >> choice;
				} while (cin.fail() || choice < 1 || choice > 13);

				if (choice == 1)
				{
					system("cls");
					addTutor(IDtutor);
					IDtutor++;
				}
				else if (choice == 2)
				{
					system("cls");
					bubbleSortTutorName();
					displayTutorsLinkedList();
				}
				else if (choice == 3)
				{
					int preference = 0;

					system("cls");
					cout << "What kind of searching algorithm you want to use?" << endl;
					cout << "1. Linear Search" << endl;
					cout << "2. Binary Search" << endl;
					cout << "Your chosen option: ";
					cin >> preference;
					while (cin.fail() || preference < 1 || preference > 2)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "What kind of searching algorithm you want to use?" << endl;
						cout << "1. Linear Search" << endl;
						cout << "2. Binary Search" << endl;
						cout << "Your chosen option: ";
						cin >> preference;
					}

					if (preference == 1)
					{
						system("cls");
						LinearSearchTutorID();
					}
					else
					{
						system("cls");
						insertionSort(1, 0);
						BinarySearchTutorID();
					}
				}
				else if (choice == 4)
				{
					int preference = 0;

					system("cls");
					cout << "What kind of searching algorithm you want to use?" << endl;
					cout << "1. Linear Search" << endl;
					cout << "2. Binary Search" << endl;
					cout << "Your chosen option: ";
					cin >> preference;
					while (cin.fail() || preference < 1 || preference > 2)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "What kind of searching algorithm you want to use?" << endl;
						cout << "1. Linear Search" << endl;
						cout << "2. Binary Search" << endl;
						cout << "Your chosen option: ";
						cin >> preference;
					}

					if (preference == 1)
					{
						system("cls");
						LinearSearchRating();
					}
					else
					{
						system("cls");
						insertionSort(3, 0);
						BinarySearchRating();
					}
				}
				else if (choice == 5)
				{
					int preference = 0;

					system("cls");
					cout << "What kind of sorting algorithm you want to use?" << endl;
					cout << "1. Bubble Sort" << endl;
					cout << "2. Insertion Sort" << endl;
					cout << "Your chosen option: ";
					cin >> preference;
					while (cin.fail() || preference < 1 || preference > 2)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "What kind of sorting algorithm you want to use?" << endl;
						cout << "1. Bubble Sort" << endl;
						cout << "2. Insertion Sort" << endl;
						cout << "Your chosen option: ";
						cin >> preference;
					}

					if (preference == 1)
					{
						system("cls");
						bubbleSortforTutorID(1);
						displayTutorsLinkedListOnebyOne();
					}
					else
					{
						system("cls");
						insertionSort(1, 1);
						displayTutorsLinkedListOnebyOne();
					}
				}
				else if (choice == 6)
				{
					int preference = 0;

					system("cls");
					cout << "What kind of sorting algorithm you want to use?" << endl;
					cout << "1. Bubble Sort" << endl;
					cout << "2. Insertion Sort" << endl;
					cout << "Your chosen option: ";
					cin >> preference;
					while (cin.fail() || preference < 1 || preference > 2)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "What kind of sorting algorithm you want to use?" << endl;
						cout << "1. Bubble Sort" << endl;
						cout << "2. Insertion Sort" << endl;
						cout << "Your chosen option: ";
						cin >> preference;
					}

					if (preference == 1)
					{
						system("cls");
						bubbleSortforHourlyRate(1);
						displayTutorsLinkedListOnebyOne();
					}
					else
					{
						system("cls");
						insertionSort(2, 1);
						displayTutorsLinkedListOnebyOne();
					}
				}
				else if (choice == 7)
				{
					int preference = 0;

					system("cls");
					cout << "What kind of sorting algorithm you want to use?" << endl;
					cout << "1. Bubble Sort" << endl;
					cout << "2. Insertion Sort" << endl;
					cout << "Your chosen option: ";
					cin >> preference;
					while (cin.fail() || preference < 1 || preference > 2)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "What kind of sorting algorithm you want to use?" << endl;
						cout << "1. Bubble Sort" << endl;
						cout << "2. Insertion Sort" << endl;
						cout << "Your chosen option: ";
						cin >> preference;
					}

					if (preference == 1)
					{
						system("cls");
						bubbleSortforRating(1);
						displayTutorsLinkedListOnebyOne();
					}
					else
					{
						system("cls");
						insertionSort(3, 1);
						displayTutorsLinkedListOnebyOne();
					}
				}
				else if (choice == 8)
				{
					system("cls");
					modifyTutor();
				}
				else if (choice == 9)
				{
					system("cls");
					deleteTutor();
				}
				else if (choice == 10)
				{
					system("cls");
					addUser(IDuser);
					IDuser++;
				}
				else if (choice == 11)
				{
					system("cls");
					addCentre(centreCode);
					centreCode++;
				}
				else if (choice == 12)
				{
					system("cls");
					addSubject(subjectCode);
					subjectCode++;
				}
				else
				{
					system("cls");
					generateReport(0);
				}

				cout << endl << "Do you still want to continue accessing HR Manager functionalities? 0 - Yes, others - No : ";
				cin >> sub_option;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Do you still want to continue accessing HR Manager functionalities? 0 - Yes, others - No : ";
					cin >> sub_option;
				}
			}
		}

		cout << endl << "Do you still want to continue? 0 - Yes, others - No : ";
		cin >> option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Do you still want to continue? 0 - Yes, others - No : ";
			cin >> option;
		}
	}

	return 0;
}