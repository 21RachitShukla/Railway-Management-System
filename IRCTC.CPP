#include<iostream.h>
#include<dos.h>
#include<iomanip.h>
#include<process.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>

class train
{
	int tno;
	char name[20];
	char from[20];
	char to[20];
	int dd_leave;
	int mm_leave;
	int yyyy_leave;
	int hours_leave;
	int mins_leave;
	int dd_arrive;
	int mm_arrive;
	int yyyy_arrive;
	int hours_arrive;
	int mins_arrive;
	int seatsleft;
	int fare;
 public:
	int seats;
	void getdata(void)
	{
		cout<<"Enter train number: ";
		cin>>tno;
		cout<<"Enter name: ";
		gets(name);
		cout<<"Enter departure location: ";
		gets(from);
		cout<<"Enter destination: ";
		gets(to);
		cout<<"Enter date of departure(DD/MM/YYYY): ";
		cout<<"\nDD: ";
		cin>>dd_leave;
		cout<<"MM: ";
		cin>>mm_leave;
		cout<<"YYYY: ";
		cin>>yyyy_leave;
		cout<<"Enter time of departure(Hours:Mins): ";
		cout<<"\nHours: ";
		cin>>hours_leave;
		cout<<"Mins: ";
		cin>>mins_leave;
		cout<<"Enter date of arrival(DD/MM/YYYY): ";
		cout<<"\nDD: ";
		cin>>dd_arrive;
		cout<<"MM: ";
		cin>>mm_arrive;
		cout<<"YYYY: ";
		cin>>yyyy_arrive;
		cout<<"Enter time of arrival(Hours:Mins): ";
		cout<<"\nHours: ";
		cin>>hours_arrive;
		cout<<"Mins: ";
		cin>>mins_arrive;
		cout<<"Enter number of seats: ";
		cin>>seats;
		seatsleft=seats;
		cout<<"Enter fare per ticket: Rs";
		cin>>fare;
		cout<<endl;
	}
	train()
	{
		;
	}
	train(train &t)
	{
		tno=t.tno;
		strcpy(name,t.name);
		strcpy(from,t.from);
		strcpy(to,t.to);
		dd_leave=t.dd_leave;
		mm_leave=t.mm_leave;
		yyyy_leave=t.yyyy_leave;
		dd_arrive=t.dd_arrive;
		mm_arrive=t.mm_arrive;
		yyyy_arrive=t.yyyy_arrive;
		hours_leave=t.hours_leave;
		mins_leave=t.mins_leave;
		hours_arrive=t.hours_arrive;
		mins_arrive=t.mins_arrive;
		seats=t.seats;
		seatsleft=t.seatsleft;
		fare=t.fare;
	}
	int gettrainno(void)
	{
		return tno;
	}
	void display(void)
	{
		cout<<"Train number: ";
		cout<<tno;
		cout<<"\nName: ";
		cout<<name;
		cout<<"\nDeparture location: ";
		cout<<from;
		cout<<"\nDestination: ";
		cout<<to;
		cout<<"\nDate of departure(DD/MM/YYYY): ";
		cout<<dd_leave<<"/"<<mm_leave<<"/"<<yyyy_leave;
		cout<<"\nTime of departure(Hours:Mins): ";
		cout<<hours_leave<<":"<<mins_leave;
		cout<<"\nDate of arrival(DD/MM/YYYY): ";
		cout<<dd_arrive<<"/"<<mm_arrive<<"/"<<yyyy_arrive;
		cout<<"\nTime of arrival(Hours:Mins): ";
		cout<<hours_arrive<<":"<<mins_arrive;
		cout<<"\nTotal number of seats: ";
		cout<<seats;
		cout<<"\nNumber of seats left: ";
		cout<<seatsleft<<endl;
	}
	int availcheck(void)
	{
		if(seatsleft<=0)
			return 0;
		else
			return 1;
	}
	void seatsleftmodify(int i)
	{
		seatsleft+=i;
	}
	int getseatsleft(void)
	{
		return seatsleft;
	}
	int getfare(void)
	{
		return fare;
	}
};
class passenger
{
	    char name[20];
	    int age;
	    char sex;
	    train t;
	    int seatno;
	    int fare;
   public:
	    void getdata(void)
	    {
		cout<<"Enter name: ";
		gets(name);
		cout<<"Enter age: ";
		cin>>age;
		cout<<"Enter sex(M/F): ";
		cin>>sex;
		cout<<endl;
		seatno=t.seats-t.getseatsleft()+1;
		fare=t.getfare();
		cout<<"Seat number: "<<seatno<<"\n";
		cout<<"Total fare: Rs"<<fare<<"\n";
	    }
	    void givetrain(train t1)
	    {
		t=t1;
	    }
	    train givetraindash(void)
	    {
		return t;
	    }
	    int giveseatno(void)
	    {
		return seatno;
	    }
	     void showdata(void)
	    {
		cout<<"\nSeat number: "<<seatno;
		cout<<"\nName: "<<name;
		cout<<"\nAge: "<<age;
		cout<<"\nSex: "<<sex<<endl;
	    }
};
void addtrain(void)
{
	train t,t1;
	int t0;
	char flag='n';
	cout<<"Enter train number to check availability: ";
	cin>>t0;
	cout<<endl;
	ifstream fin("trains.txt",ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&t1,sizeof(t1));
		if(t1.gettrainno()==t0)
		{
			flag='y';
			break;
		}
	}
	fin.close();
	if(flag=='n')
	{
		cout<<"Available!\n\n";
		t.getdata();
		ofstream fout("trains.txt",ios::binary|ios::app);
		fout.write((char*)&t,sizeof(t));
		fout.close();
		cout<<"\nAdded!\n\n";
	}
	else
		cout<<"\nTrain number already exists!\n\n";
}
void deltrain(void)
{
	int no;
	train t;
	ifstream fin("trains.txt",ios::binary);
	ofstream fout("temp.txt",ios::binary);
	cout<<"Enter train number: ";
	cin>>no;
	cout<<endl;
	char flag='n';
	while(!fin.eof())
	{
	     fin.read((char*)&t,sizeof(t));
	     if(t.gettrainno()==no)
	     {
		flag='y';
		continue;
	     }
	     fout.write((char*)&t,sizeof(t));
	}
	fin.close();
	fout.close();
	if(flag=='y')
	{
		remove("trains.txt");
		rename("temp.txt","trains.txt");
	}
	else
		remove("temp.txt");
}
void reserve(train t1)
{
	passenger p;
	train t;
	ofstream fout("passengers.txt",ios::binary|ios::app);
	p.givetrain(t1);
	p.getdata();
	fout.write((char*)&p,sizeof(p));
	fout.close();
	ifstream fin("trains.txt",ios::binary);
	ofstream f_out("temp.txt",ios::binary);
	while(!fin.eof())
	{
	     fin.read((char*)&t,sizeof(t));
	     if(t1.gettrainno()==t.gettrainno())
	     {
		t.seatsleftmodify(-1);
	     }
	     f_out.write((char*)&t,sizeof(t));
	}
	fin.close();
	f_out.close();
	remove("trains.txt");
	rename("temp.txt","trains.txt");
}
void cancel(void)
{
	train t;
	passenger p;
	int tno,no,check;
	ifstream fin("passengers.txt",ios::binary);
	ofstream fout("temp.txt",ios::binary);
	cout<<"Enter train number: ";
	cin>>tno;
	cout<<"Enter seat number: ";
	cin>>no;
	cout<<endl;
	char flag='n';
	while(!fin.eof())
	{
	     fin.read((char*)&p,sizeof(p));
	     t=p.givetraindash();
	     check=p.giveseatno();
	     if(t.gettrainno()==tno&&check==no)
	     {
		flag='y';
		continue;
	     }
	     fout.write((char*)&t,sizeof(t));
	}
	fin.close();
	fout.close();
	if(flag=='y')
	{
		remove("passengers.txt");
		rename("temp.txt","passengers.txt");
	}
	else
		remove("temp.txt");
	ifstream f_in("trains.txt",ios::binary);
	ofstream f_out("temp.txt",ios::binary);
	while(!f_in.eof())
	{
	     f_in.read((char*)&t,sizeof(t));
	     if(t.gettrainno()==no)
	     {
		t.seatsleftmodify(1);
	     }
	     f_out.write((char*)&t,sizeof(t));
	}
	f_in.close();
	f_out.close();
	remove("trains.txt");
	rename("temp.txt","trains.txt");
}
void searchtrain(int tno)
{
	train t;
	char flag='n';
	ifstream fin("trains.txt",ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&t,sizeof(t));
		if(t.gettrainno()==tno)
		{
			t.display();
			flag='y';
			break;
		}
	}
	if(flag=='n')
		cout<<"No record found!"<<'\n';
}
void status(int tno,int sno)
{
      train t2;
      int s2;
      char flag='n';
      passenger p;
      ifstream fin("passengers.txt",ios::binary);
      while(!fin.eof())
      {
		fin.read((char*)&p,sizeof(p));
		t2=p.givetraindash();
		s2=p.giveseatno();
		if(t2.gettrainno()==tno&&s2==sno)
		{
			p.showdata();
			flag='y';
			break;
		}
      }
      if(flag=='n')
	cout<<"No record found!"<<'\n';
}
int check(char a[5],char b[5])
{
 int i;
    for(i=0;i<5;i++)
    {
	if(a[i]!=b[i])
	{
		break;
	}
    }
    if(i==5)
	return 1;
    else
	return 0;
}

void main()
{
clrscr();
int ch1,ch2;
do
{
m:clrscr();
cout<<"..........................WELCOME TO IRCTC...........................\n\n\n\n";
cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
cout<<"1.Admin Mode\n2.User Mode\n3.Exit\n";
cout<<"\nEnter choice: ";
cin>>ch1;
clrscr();
	if(ch1==1)
	{
		char password[5];
		char pass[]="admin";
		int i=0,mycheck;
		cout<<"Password: ";
		while(i<5)
		{
			password[i]=getch();
			cout<<"*";
			++i;
		}
		cout<<endl<<endl;
		mycheck=check(password,pass);
		if(mycheck!=1)
		{
			cout<<"\nIncorrect Password!\n";
			cout<<"\nAccess Denied!\n";
			delay(3000);
			goto m;
		}
		else if(mycheck==1)
		{
		int ch1;
		a:cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ADMIN MENU^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout<<"1.Add a train record\n2.Delete existing train record\n3.Find existing train record\n4.Return to main menu\n";
		cout<<"\nEnter choice: ";
		cin>>ch1;
		cout<<'\n';
			if(ch1==1)
			{
				char ch;
					do
					{
						addtrain();
						cout<<"\nDo you want to add more records?(y/n): ";
						cin>>ch;
						cout<<endl;
					}while(ch=='y');
			}
			else if(ch1==2)
			{
				char ch;
					do
					{
						deltrain();
						cout<<"Deleted!\n\nDo you want to delete more records?(y/n): ";
						cin>>ch;
						cout<<endl;
					}while(ch=='y');
			}
			else if(ch1==3)
			{
				int tno;
				char ch;
					do
					{
						cout<<"Enter train number: ";
						cin>>tno;
						cout<<endl;
						searchtrain(tno);
						cout<<"\n\nDo you want to find more records?(y/n): ";
						cin>>ch;
						cout<<endl;
					}while(ch=='y');
			}
			else if(ch1==4)
			{
				cout<<'\n';
				goto m;
			}
		}
	}
	else if(ch1==2)
	{
		int ch1;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^USER MENU^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout<<"1.Book Ticket\n2.Cancel Ticket\n3.Check Status\n4.Return to main menu";
		cout<<"\n\nEnter choice: ";
		cin>>ch1;
		cout<<endl;
			if(ch1==1)
			{
				char ch;
					do
					{       train t;
						char flag='n';
						cout<<"Enter train number: ";
						int n;
						cin>>n;
						cout<<endl;
						ifstream fin("trains.txt",ios::binary);
						while(!fin.eof())
						{
							fin.read((char*)&t,sizeof(t));
							if((t.gettrainno()==n)&&(t.availcheck()==1))
							{	flag='y';
								break;
							}
						}
						fin.close();
						if(flag=='y')
							reserve(t);
						else
							cout<<"\nTrain not found/available!\n\n";
						cout<<"\nDo you want to book more tickets(y/n)?: ";
						cin>>ch;
						cout<<endl;
					}while(ch=='y');
			}
			else if(ch1==2)
			{
				char ch;
					do
					{
						cancel();
						cout<<"Cancelled!\n\nDo you want to cancel more tickets?(y/n): ";
						cin>>ch;
						cout<<endl;
					}while(ch=='y');
			}
			else if(ch1==3)
			{
				int tno;
				int sno;
				cout<<"Enter train number: ";
				cin>>tno;
				cout<<"Enter seat number: ";
				cin>>sno;
				cout<<endl;
				status(tno,sno);
			}
			else if(ch1==4)
		      {
				cout<<'\n';
				goto m;
		      }
	}
	else if(ch1==3)
	{
		exit(0);
	}
cout<<"\n\n1.Main Menu\n2.Exit\n";
cout<<"\nEnter choice: ";
cin>>ch2;
}while(ch2==1);
getch();
}