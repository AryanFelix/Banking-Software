#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
using namespace std;

class bank
{
	private:
		double cash;
		double accno;
		double dep;
      		double wit;
		char name[50];
	public:
	void getdata()
	{
		cout<<"\t\tEnter Account Number : \t";
		cin>>accno;
		cout<<"\t\tName : \t\t\t";
		gets(name);
		cout<<"\t\tInitial Deposit : \t";
		cin>>cash;
	}

void showdata()
	{
		cout<<"\t\tAccount Number : \t"<<accno<<endl;
		cout<<"\t\tName : \t\t\t"<<name<<endl;
		cout<<"\t\tInitial Deposit : \t"<<cash<<endl<<endl<<endl;
	}

void deposit()
	{
		cout<<"\t\tAccount Number : \t"<<accno<<endl;
		cout<<"\tAccount Holder's Name : \t"<<name<<endl;
         		cout<<"\tAccount Holder's Funds : \t"<<cash<<endl;
		cout<<"\t\tEnter Deposit : \t";
		cin>>dep;
		cash=cash+dep;
         		cout<<"\tAccount Holder's New Funds : \t"<<cash<<endl;
	}
	void withdrawal()
	{
		cout<<"\t\tAccount Number : \t"<<accno<<endl;
		cout<<"\tAccount Holder's Name : \t"<<name<<endl;
		cout<<"\tAccount Holder's Funds : \t"<<cash<<endl;
		cout<<"\tEnter Withdrawal Amount : \t";
		cin>>wit;
		if (cash-wit>=0)
		{
		cash=cash-wit;
		cout<<"\tAccount Holder's New Funds : \t"<<cash<<endl;
		}
		else
		{
		cout<<"\t\tNOT ENOUGH FUNDS"<<endl;
		}
	}

int retaccno()
	{
		return accno;
	}
};

void write()
{
cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    CREATING A NEW ACCOUNT "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	fstream outfile;
	outfile.open("Bankinga.dat",ios::out|ios::binary|ios::app);
	bank obj;
	obj.getdata();
	outfile.write((char *)&obj,sizeof(obj));
	outfile.close();
}

void display()
{
	cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    ACCOUNTS "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	fstream infile;
	infile.open("Bankinga.dat",ios::in|ios::binary);
	bank obj;
	while(infile.read((char*)&obj,sizeof(obj)))
	{
		obj.showdata();
	}
	infile.close();
	if (infile.eof())
	{
		cout<<"\t\tNo Accounts Exist"<<endl;
	}
}

void search(int n)
{
   cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    SEARCHING "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	ifstream infile;
	infile.open("Bankinga.dat",ios::binary);
	bank obj;
	if(!infile.eof())
	{
   while(infile.read((char*)&obj,sizeof(obj)))
	{
		if(obj.retaccno()==n)
		{
			obj.showdata();
		}
	}
	}

	infile.close();
}

void delete_rec(int n)
{
   cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    DELETING "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	bank obj;
	ifstream infile;
	infile.open("Bankinga.dat",ios::binary);
	ofstream outfile;
	outfile.open("BankingT.dat",ios::out|ios::binary);
	while(infile.read((char*)&obj, sizeof(obj)))
	{
		if(obj.retaccno()!=n)
		{
			outfile.write((char*)&obj,sizeof(obj));
		}
	}
	infile.close();
	outfile.close();
	remove("Bankinga.dat");
	rename("BankingT.dat","Bankinga.dat");
}

void modify(int n)
{
   cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    MODIFY "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	fstream file;
	file.open("Bankinga.dat",ios::in|ios::out|ios::binary);
	bank obj;
	while(file.read((char*)&obj, sizeof(obj)))
	{
      if(obj.retaccno()==n)
		{
		cout<<"Enter new details"<<endl;
		obj.getdata();
		int pos=(file.tellp() - sizeof(obj));
		file.seekp(pos);
		file.write((char*)&obj,sizeof(obj));
		}
	}
file.close();
}

void modifywithdrawal(int n)
{
   cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    WITHDRAWAL "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	fstream file;
	file.open("Bankinga.dat",ios::in|ios::out|ios::binary);
	bank obj;
	while(file.read((char*)&obj, sizeof(obj)))
	{
      if(obj.retaccno()==n)
		{
		obj.withdrawal();
		int pos=(file.tellp() - sizeof(obj));
		file.seekp(pos);
		file.write((char*)&obj,sizeof(obj));
		}
	}
file.close();
}

void modifydeposit(int n)
{
	cout<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t    DEPOSIT "<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	fstream file;
	file.open("Bankinga.dat",ios::in|ios::out|ios::binary);
	bank obj;
	while(file.read((char*)&obj, sizeof(obj)))
	{
      if(obj.retaccno()==n)
		{
		obj.deposit();
		int pos=(file.tellp() - sizeof(obj));
		file.seekp(pos);
		file.write((char*)&obj,sizeof(obj));
      }
	}
file.close();
}

int main()
{
	int choice;
	char loop, yes;
	do
	{
    system("CLS");
	flag:
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	cout<<"\t\t\t\t WELCOME"<<endl;
	cout<<"\t\t\t\t   TO"<<endl;
	cout<<"\t\t\t     RED DRAGON BANK"<<endl<<endl;
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
	cout<<"\t\t How can we help you today?"<<endl;
	cout<<"\t\t Press the adjacent number"<<endl<<endl;
	cout<<"\t\t\t 1. Create an account"<<endl<<endl;
	cout<<"\t\t\t 2. Display details of all existing account"<<endl<<endl;
	cout<<"\t\t\t 3. Search for a specific account"<<endl<<endl;
	cout<<"\t\t\t 4. Delete an account"<<endl<<endl;
	cout<<"\t\t\t 5. Modify an account"<<endl<<endl;
	cout<<"\t\t\t 6. Deposit"<<endl<<endl;
	cout<<"\t\t\t 7. Withdrawal"<<endl<<endl;
	cout<<"\t\t\t 8. Exit"<<endl<<endl;
	cout<<"\t\t Enter your selection : ";
	cin>>choice;
    system("CLS");
	 switch (choice)
	 {
		case 1 : 	system("CLS");
				write();
				break;
		case 2 : 	system("CLS");
				display();
				break;
		case 3 : 	system("CLS");
				int n;
				cout<<"\t\tEnter Account Number To Be Searched : ";
				cin>>n;
				search(n);
				break;
		case 4 : 	system("CLS");
				int m;
				cout<<endl<<endl<<"\t\tEnter Account Number To Be Deleted : ";
				cin>>m;
				delete_rec(m);
				break;
		case 5 : 	system("CLS");
				int b;
				cout<<endl<<endl<<"\t\tEnter Account Number To Be Modified : ";
				cin>>b;
				modify(b);
				break;
		case 6 : 	system("CLS");
				int z;
				cout<<endl<<endl<<"\t\tEnter Account Number To Be Deposited Into : ";
				cin>>z;
				modifydeposit(z);
				break;
		case 7 : 	system("CLS");
				int y;
				cout<<endl<<endl<<"\t\tEnter Account Number To Be Withdrawn From : ";
				cin>>y;
				modifywithdrawal(y);
				break;
		case 8 : 	break;
		default :	cout<<"\t\t INVALID"<<endl;
				cout<<"\t\t ";
				getch();
				system("CLS");
				 goto flag;
	 }
	 if (choice==8)
	 {
		break;
	 }
	 cout<<"\n\n\t\t Do you wish to continue availing our services? \n\t\t (Y for yes and N for no)"<<endl;
	 cin>>yes;
	}while(yes=='Y'||yes=='y');
	system("CLS");
	cout<<"\t\tThank you for using our online portal"<<endl;
	cout<<"\t\t\t     RED DRAGON BANK"<<endl<<endl;
	return 0;
}
