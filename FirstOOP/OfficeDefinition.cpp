#include "OfficeDeclaration.h"
using namespace std;
void get_line(string& str) {
	char temp[101];
	cin.get(temp, 101, '\n');
	cin.ignore(101, '\n');
	str = temp;

}

char get_char() {
	char ch = cin.get();
	cin.ignore(101, '\n');
	return ch;
}

int Department::get_decnum() {
	return number_dep;
}

bool operator < (const Department& dep1, const Department& dep2) {
	return dep1.name < dep2.name;
}
bool operator == (const Department& dep1, const Department& dep2) {
		return dep1.name == dep2.name;
}
ostream& operator << (ostream& func, const Department& dep) {
	func << dep.number_dep << '\t' << dep.name << endl;
	return func;
}

void Department_Input_Screen::get_department() {
	cout << "Enter name of Departament: ";
	get_line(name);
	cout << "Enter number of Departament: ";
	cin >> number_dep;
	cin.ignore(101, '\n');
	Department* ptrDepartament = new Department(name, number_dep);
	ptrDepartment_List->insert_department(ptrDepartament);
}

bool Compare_Department::operator() (Department* dep1, Department* dep2) const {
	return *dep1 < *dep2;
}

Department_List::~Department_List() {
	while (!set_ptr_dep.empty())
	{
		iter = set_ptr_dep.begin();
		delete *iter;
		set_ptr_dep.erase(iter);
	}
}

void Department_List::insert_department(Department* ptr) {
	set_ptr_dep.insert(ptr);
}

int Department_List::get_number_dep(string str) {
	int num_dep;
	Department dep(str, 0);
	iter = set_ptr_dep.begin();
	while (iter != set_ptr_dep.end()) {
		num_dep = (*iter)->get_decnum();
		if (dep == **iter++)
			return num_dep;
	}
	return -1;
}

void Department_List::display() {
	cout << "\nDep#\tName of Department\n---------------------\n";
	if (set_ptr_dep.empty())
		cout << "Doesn't have a Departments\n";
	else {
		iter = set_ptr_dep.begin();
		while (iter != set_ptr_dep.end())
			cout << **iter++;
	}
}

Department_Row::Department_Row(int number) : number(number)
{
	fill(&pay_row[0], &pay_row[12], 0);
}

void Department_Row::set_pay(int number, double pay) {
	pay_row[number] = pay;
}

double Department_Row::get_sum_row() {
	return accumulate(&pay_row[0], &pay_row[12], 0.0);
}

bool operator < (const Department_Row& row1, const Department_Row& row2) {
	return row1.number < row2.number;
}
bool operator == (const Department_Row& row1, const Department_Row& row2) {
	return row1.number == row2.number;
}
ostream& operator << (ostream& func, const Department_Row& row) {
	func << row.number << '\t';
	for (int i = 0; i < 12; i++) {
		if (row.pay_row[i] == 0)
			func << "  0  ";
		else func << row.pay_row[i] << "  ";
	}
	func << endl;
	return func;
}

bool Compare_Department_Row ::operator() (Department_Row* row1, Department_Row* row2) const {
	return *row1 < *row2;
}

Pay_Department::~Pay_Department() {
	while (!set_ptr_crow.empty()) {
		iter = set_ptr_crow.begin();
		delete *iter;
		set_ptr_crow.erase(iter);
	}
}

void Pay_Department::insert_pay(int value, int month, double amount) {
	Department_Row searchRow(value);
	
	iter = set_ptr_crow.begin();

	while (iter != set_ptr_crow.end()) {
		if (searchRow == **iter) {
			(*iter)->set_pay(month, amount);
			return;
		}
		else iter++;
	}
	Department_Row* ptrRow = new Department_Row(value);
	ptrRow->set_pay(month, amount);
	set_ptr_crow.insert(ptrRow);
}

void Pay_Department::display() {
	cout << "\nNumber\tJan  Feb  Mar  Apr  May  Jun  "
		 <<           "Jul  Aug  Sep  Oct  Nov  Dec\n"
		 << "-----------------------------------"
		 << "-----------------------------------\n";
	if (set_ptr_crow.empty())
		cout << "Nothing here!\n";
	else {
		iter = set_ptr_crow.begin();
		while (iter != set_ptr_crow.end())
			cout << **iter++;
	}
}

double Pay_Department::get_sum_pay() {
	double sum = 0.0;
	iter = set_ptr_crow.begin();
	while (iter != set_ptr_crow.end()) {
		sum += (*iter)->get_sum_row();
		iter++;
	}
	return sum;
}

void Pay_Input_Screen::get_pay() {
	cout << "Enter name of Departament : ";
	get_line(responsible);
	number_dep = ptrDepartment_List->get_number_dep(responsible);
	if(number_dep > 0){
		cout << "Enter sum of pays : ";
		cin >> pays;
		cin.ignore(100, '\n');
		cout << "Enter number of month (1-12) : ";
		cin >> month;
		cin.ignore(100, '\n');
		month--;
		ptrPay_Department->insert_pay(number_dep, month, pays);
	}
	else cout << "Nothing here! \n";
}

bool operator < (const Expense& exp1, const Expense& exp2) {
	if (exp1.month == exp2.month)
		return exp1.day < exp2.day;
	else return exp1.month < exp2.month;
}

bool operator == (const Expense& exp1, const Expense& exp2) {
	return ((exp1.month == exp2.month) && (exp1.day == exp2.day));
}
ostream& operator << (ostream& func, const Expense& exp) {
	func << exp.month << "/" << exp.day << "\t" << exp.payee << "\t\t"
		 << exp.amount << "\t" << exp.category << endl;
	return func;
}

bool Compare_Expense::operator () (Expense* exp1, Expense* exp2) const {
	return *exp1 < *exp2;
}

bool Compare_Category::operator () (Expense* exp1, Expense* exp2) const {
	return exp1->category < exp2->category;
}

Pay_Expense::~Pay_Expense() {
	while (!vect_exp.empty())
	{
		iter = vect_exp.begin();
		delete *iter;
		vect_exp.erase(iter);
	}
}

void Pay_Expense::insert_pay(Expense* ptrEx) {
	vect_exp.push_back(ptrEx);
}
void Pay_Expense::display() {
	cout << "\nDate\tRecipient\tSum\tCategory\n"
		<< "--------------------------------------\n";
	if (vect_exp.size() == 0) cout << "Nothing here! ";
	else {
		sort(vect_exp.begin(), vect_exp.end(), Compare_Expense());
		iter = vect_exp.begin();
		while (iter != vect_exp.end())
			cout << **iter++;
	}
}

double Pay_Expense::get_sum_exp() {
	double total = 0.0;

	if (vect_exp.size() == 0) {
		cout << "\tAll categoryes\t\t0\n";
		return 0;
	}

	sort(vect_exp.begin(), vect_exp.end(), Compare_Category());

	iter = vect_exp.begin();
	string temp = (*iter)->category;
	double sum = 0.0;

	while (iter != vect_exp.end()) {
		if (temp == (*iter)->category)
			sum += (*iter)->amount;
		else {
			cout << '\t' << temp << '\t\t' << sum << endl;
			total += sum;

			temp = (*iter)->category;
			sum = (*iter)->amount;
		}
		iter++;
	}
	total += sum;

	cout << '\t' << temp << '\t' << sum << endl;
	return total;
}

Expense_Input_Screen::Expense_Input_Screen(Pay_Expense*  ptrPay_Expense)
	: ptrPay_Expense(ptrPay_Expense)
{}

void Expense_Input_Screen::get_exp() {
	unsigned short month, day;
	string category, payee;
	double amount;

	cout << "Enter a month: ";
	cin >> month;
	cin.ignore(100, '\n');
	cout << "Enter a day: ";
	cin >> day;
	cin.ignore(100, '\n');
	cout << "Enter a category: ";
	get_line(category);
	cout << "Enter a payee: ";
	get_line(payee);
	cout << "Enter a amount: ";
	cin >> amount;
	cin.ignore(100, '\n');

	Expense* ptrExp = new Expense(month, day, category, payee, amount);
	ptrPay_Expense->insert_pay(ptrExp);
}

Annual_Report::Annual_Report(Pay_Department * ptrPay_Department, Pay_Expense* ptrPay_Expense)
	: ptrPay_Department(ptrPay_Department), ptrPay_Expense(ptrPay_Expense)
{}

void Annual_Report::display() {
	cout << "Year Report\n---------------------\n";
	cout << "Income\n";
	cout << "\tTotal fee\t\t";
	pays = ptrPay_Department->get_sum_pay();
	cout << pays << endl;

	cout << "Expenses\n";
	expenses = ptrPay_Expense->get_sum_exp();
	cout << "\nBalance\t\t\t\t" << pays - expenses << endl;
}

User_Interface::User_Interface() {
	ptrDepartment_List = new Department_List;
	ptrPay_Department = new Pay_Department;
	ptrPay_Expense = new Pay_Expense;
}

User_Interface::~User_Interface() {
	delete ptrDepartment_List;
	delete ptrPay_Department;
	delete ptrPay_Expense;
}

void User_Interface::interact() {
	while (true) {
		cout << "For Enter a data - press 'i', \n"
			<< "For Display a data - press 'd', \n"
			<< "For Exit - press 'q', \n"
			<< "Your choise : ";
		ch = get_char();
		if (ch == 'i') {
			cout << "For add a Department - press 't', \n"
				<< "For add a Pay - press 'r', \n"
				<< "For add a Expense - press 'e', \n"
				<< "Your choise : ";
			ch = get_char();
			switch (ch)
			{
			case 't': {
				ptrDepartment_Input_Screen = new Department_Input_Screen(ptrDepartment_List);
				ptrDepartment_Input_Screen->get_department();
				delete ptrDepartment_Input_Screen;
				break;
			}
			case 'r': {
				ptrPay_Input_Screen = new Pay_Input_Screen(ptrDepartment_List, ptrPay_Department);
				ptrPay_Input_Screen->get_pay();
				delete ptrPay_Input_Screen;
				break;
			}
			case 'e': {
				ptrExpense_Input_Screen = new Expense_Input_Screen(ptrPay_Expense);
				ptrExpense_Input_Screen->get_exp();
				delete ptrExpense_Input_Screen;
				break;
			}
			default: { cout << "Unknown action! \n"; break; }
			}
		}
		else if (ch == 'd') {
			cout << "For display Departaments - press 't', \n"
				<< "For display Pay - press 'r', \n"
				<< "For display Expense - press 'e', \n"
				<< "For display Annual Report - press 'a', \n"
				<< "Your choise : ";
			ch = get_char();
			switch (ch)
			{
			case 't': {ptrDepartment_List->display(); break; }
			case 'r': {ptrPay_Department->display(); break; }
			case 'e': {ptrPay_Expense->display(); break; }
			case 'a': {
				ptrAnnual_Report = new Annual_Report(ptrPay_Department, ptrPay_Expense);
				ptrAnnual_Report->display();
				delete ptrAnnual_Report;
				break;
			}
			default: { cout << "Unknown action! \n"; break; }
			}
		}
		else if (ch == 'q')
			return;
		else cout << "Unknown action! \n"; 
	}
}