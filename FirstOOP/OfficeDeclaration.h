#pragma  warning (disable:4786)	

#include <iostream>     //Stream output and input library

#include <vector>		//Library of containers of vectors and sets
#include <set>

#include <string>		//String data type library

#include <algorithm>	//Libraries for container function implementations
#include <numeric>   

using namespace std;	//Work in a standard namespace

void get_line(string& str);	//Function to get some string lines
char get_char();			//Function to get some char symbols

class Department {
private:
	string name;		//Name of Department
	int number_dep;		//Number of Department
public:
	Department(string name, int number_dep) : name(name), number_dep(number_dep)
	{}			//Constructor with 2 arguments
	~Department()
	{}			//Destructor

	int get_decnum();	//Retrun number_dep

	//Necessary to work in "set"
	friend bool operator < (const Department& dep1, const Department& dep2);
	friend bool operator == (const Department& dep1, const Department& dep2);
	friend ostream& operator << (ostream& func, const Department& dep);
};

class Compare_Department {	//Necessary to sort in "set"
public:
	bool operator () (Department* dep1, Department* dep2) const;
};

class Department_List {
private:
	//"Set" of "Department" links, sorting with "Compare_Department"
	set<Department*, Compare_Department> set_ptr_dep;	
	//"Iterator" for interaction with "set"
	set<Department*, Compare_Department> ::iterator iter;
public:
	~Department_List(); //Destructor for "set"

	void insert_department(Department* ptr);//Insert a link in "set"
	int get_number_dep(string str);			//Retrun number_dep of "Department"
	void display();							//Display "Department"'s in "set"
};

class Department_Input_Screen {
private:
	Department_List * ptrDepartment_List;	//Link to "Department_List"
	string name;		//Input name of "Departament" 
	int number_dep;		//Input number of "Departament" 
public:
	Department_Input_Screen(Department_List* ptrDepartment_List) : ptrDepartment_List(ptrDepartment_List)
	{}	//Constructor with 2 arguments
	void get_department(); //Insert info "Departament" in "set" of "Department_List"
};

class Department_Row {
private:
	int number;				//Number of "Departament"
	double pay_row[12];		//Pays in every "Departament"
public:
	Department_Row(int number);	//Constructor with 1 argument and fill "pay_row" zero's

	void set_pay(int number, double pay);//Setting info in row
	double get_sum_row();		//Retrun sum of "pay_row"
	
	//Necessary to work in "set"
	friend bool operator < (const Department_Row& row1, const Department_Row& row2);
	friend bool operator == (const Department_Row& row1, const Department_Row& row2);
	friend ostream& operator << (ostream& func, const Department_Row& row);
};

class Compare_Department_Row {	//Necessary to sort in "set"
public:
	bool operator () (Department_Row* row1, Department_Row* row2) const;
};


class Pay_Department {
private:
	//"Set" of "Department_Row" links, sorting with "Compare_Department_Row"
	set<Department_Row*, Compare_Department_Row> set_ptr_crow;
	//"Iterator" for interaction with "set"
	set<Department_Row*, Compare_Department_Row> ::iterator iter;
public:
	~Pay_Department();//Destructor for "set"

	void insert_pay(int value, int month, double amount);//Insert a data in "set"
	double get_sum_pay(); //Retrun sum of pays
	void display();		  //Display "Pay_Department"'s in "set"
};

class Pay_Input_Screen {
private:
	Department_List * ptrDepartment_List;//Link to "Department_List"
	Pay_Department* ptrPay_Department;//Link to "Department_List"
	string responsible;//Name of person , which get pays
	double pays;//Pays of "Departament"
	//Data of pay
	int month;
	int number_dep;
public:
	Pay_Input_Screen(Department_List * ptrDepartment_List, Pay_Department* ptrPay_Department) :
		ptrDepartment_List(ptrDepartment_List), ptrPay_Department(ptrPay_Department)
	{}//Constructor with 2 arguments
	void get_pay();	//Insert a data in "Department_List"
};

class Expense {
public:
	int month, day;			//Data of "Expense"
	string category, payee; //Category and payee in "Expense"
	double amount;			//Sum of "Expense"

	Expense()
	{}
	Expense(int month, int day, string category, string payee, double amount) :
		month(month), day(day), category(category), payee(payee), amount(amount)
	{}//Constructor with 4 arguments
	
	//Necessary to work in "vector"
	friend bool operator < (const Expense& exp1, const Expense& exp2);
	friend bool operator == (const Expense& exp1, const Expense& exp2);
	friend ostream& operator << (ostream& func, const Expense& exp);
};

class Compare_Expense {	  //For sort in Pay_Expense::display()
public:
	bool operator () (Expense* exp1, Expense* exp2) const;
};

class Compare_Category {  //For sort in Pay_Expense::get_sum_exp()
public:
	bool operator () (Expense* exp1, Expense* exp2) const;
};

class Pay_Expense {
private:
	//"Vector" of "Expense" links
	vector<Expense*> vect_exp;
	//"Iterator" for interaction with "vector"
	vector<Expense*> ::iterator iter;
public:
	~Pay_Expense();//Destructor for "vector"

	void insert_pay(Expense* ptrEx);//Insert data in "vector"
	double get_sum_exp();		//Retrun sum of all "Expense" in "vector"
	void display();				//Display all data vector
};

class Expense_Input_Screen {
private:
	Pay_Expense * ptrPay_Expense;//Link to "Pay_Expense" 

public:
	Expense_Input_Screen(Pay_Expense*  ptrPay_Expense);//Constructor with 2 arguments
	void get_exp(); //Insert input data in "vector"
};

class Annual_Report {
private:
	Pay_Department * ptrPay_Department;//Link to "Pay_Department" 
	Pay_Expense* ptrPay_Expense;//Link to "Pay_Expense" 
	double expenses, pays;//Sum of the report

public:
	//Constructor with 2 arguments
	Annual_Report(Pay_Department * ptrPay_Department, Pay_Expense* ptrPay_Expense);
	void display();//Display "Annual_Report" data 
};

class User_Interface {	
private:
	//Start Links for working with interface
	Department_List * ptrDepartment_List;
	Department_Input_Screen * ptrDepartment_Input_Screen;
	Pay_Department * ptrPay_Department;
	Pay_Input_Screen* ptrPay_Input_Screen;
	Pay_Expense* ptrPay_Expense;
	Expense_Input_Screen* ptrExpense_Input_Screen;
	Annual_Report * ptrAnnual_Report;
	//Choise of User
	char ch;
public:
	User_Interface();	//Creating new elements
	~User_Interface();	//Deleting new elements
	void interact();	//Main Interface for User manipulationsä
};


