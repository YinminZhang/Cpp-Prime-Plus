// brass.cpp -- bank accout class methods
#include<iostream>
#include"13.7 brass.h"
using std::cout;
using std::endl;
using std::string;

// formatting stuff
typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass methods
Brass::Brass(const string&s, long an, double bal)
{
	fullNAme = s;
	acctNum = an;
	balance = bal;
}

void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "Negative deposite not allowed; "
		<< "deposit is cancelled." << endl;
	else
		balance += amt;
}

void Brass::Withdraw(double amt)
{
	// set up ###.## format
	format inintialState = setFormat();
	precis prec = cout.precision(2);

	if (amt < 0)
		cout << "Withdrawal amount must be positive; "
		<< "Withdrawal canceled." << endl;
	else if (amt <= balance)
		balance -= amt;
	else
		cout << "Withdrawal amount of $" << amt
		<< " exceeds your balance." << endl
		<< "Withdrawal canceled." << endl;
	restore(inintialState, prec);
}

double Brass::Balance()const
{
	return balance;
}

void Brass::ViewAcct()const
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);
	cout << "Client: " << fullNAme << endl;
	cout << "Account Number: " << acctNum << endl;
	cout << "Balance: $" << balance << endl;
	restore(initialState, prec);	// restore original format
}

// BrassPlus Methods
BrassPlus::BrassPlus(const string & s, long an, double bal,
	double ml, double r) :Brass(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r)
	:Brass(ba)	// uses implicit copy constructor
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

// redefine how ViewAcct() works
void BrassPlus::ViewAcct()const
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	Brass::ViewAcct();		// display base portion
	cout << "Maximun loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);		// ###.### format
	cout << "Loan Rate: " << 100 * rate << "%" << endl;
	restore(initialState, prec);
}

// redefine how Withdraw() works
void BrassPlus::Withdraw(double amt)
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	double bal = Balance();
	if (amt <= bal)
		Brass::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)
	{
		double advance = amt - bal;
		owesBank += advance*(1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance*rate << endl;
		Deposit(advance);
		Brass::Withdraw(amt);
	}
	else cout << "Credit limit exceeded. Transaction cancelled." << endl;
	restore(initialState, prec);
}

format setFormat()
{
	// set up ###.## format
	return cout.setf(std::ios_base::fixed,
		std::ios_base::floatfield);
}

void restore(format f, precis p)
{
	cout.setf(f, std::ios_base::floatfield);
	cout.precision(p);
}
