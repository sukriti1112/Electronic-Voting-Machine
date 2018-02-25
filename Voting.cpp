//Header files
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<constrea.h>
#include<dos.h>


void Sort();
void CreVoter();
void NewCan();
void ViewVoter();
void EditVoter();
int DelV();
void AddVoter();
void CheckVotes();
void NewPass();
void Admin();
void Voting();
void DispList();
void FilOpen(int,int &);
void Vote();
void Cpro();

//Class Definition

class Candidate
{
 char Name[40];
 char Gender;
 int Votes;
 int Age;
 char Aff[20];
 char Edu[40];
 float Wealth;
 char Crime[30];
 char Stmt[110];
 int id;
	public:
 void Vote() { Votes++; }
 int RVotes()
 { return Votes; }
 void DVotes()
 {
	cout<<Name<<"          "<<Votes<<endl;
 }
 void Profile()
 {
	clrscr();
	cout<<endl<<"NAME: "<<Name<<endl;
	cout<<"GENDER: "<<Gender<<endl<<"AGE: "<<Age<<endl;
	cout<<"AFFILIATION: "<<Aff<<endl;
	cout<<"EDUCATION: "<<Edu<<endl;
	cout<<"WEALTH: "<<Wealth<<endl;
	cout<<"CRIMINAL RECORD: "<<Crime<<endl;
	cout<<"STATEMENT: "<<Stmt<<endl;
	getch();
 }
 void Input()
 {
	Votes=0;
	cout<<"Enter name of candidate: ";
	gets(Name);
	cout<<"Enter gender (M/F): ";
	cin>>Gender;
	cout<<"Enter age: ";
	cin>>Age;
	cout<<"Enter affiliation(if none, enter none): ";
	gets(Aff);
	cout<<"Enter educational qualification: ";
	gets(Edu);
	cout<<"Enter wealth: ";
	cin>>Wealth;
	cout<<"Enter criminal record: ";
	gets(Crime);
	cout<<"Enter election statement: ";
	gets(Stmt);
 }
 void Inid()
 {
	randomize();
	id=random(200);
 }
 int Rid()
 {
	return id;
 }
 void List()
 {
	cout<<id<<"        "<<Name<<endl;
 }
};

class Voter
{
 char Name[40];
 int VID;
 int Voted;
	public:
 Voter(char n[40]="default", int vid=0)
 {
	strcpy(Name, n);
	VID=vid;
	Voted=0;
 }
 void Dis()
 {
	cout<<"  "<<VID<<"  "<<Name<<endl;
	getch();
 }
 int Ret(){ return VID;}
 int RVoted(){ return Voted; }
 void CVoted(){ Voted++;}
};
//Definitions over---

//MAIN
void CreVoter()    
{
 fstream fil;
 fil.open("VData.dat", ios::binary|ios::out);
 Voter v1("Voter 1", 17001);
 fil.write((char*)&v1, sizeof(v1));
}
void main()
{
 remove("VData.dat");
 remove("CanDat.dat");
 CreVoter();
 clrscr();
 int i;
 char ch=177, ce=178;
 textcolor(WHITE);
 gotoxy(37,9);
 printf("LOADING");
 gotoxy(27,10);
 for (i=0;i<=26;i++)
 printf("%c",ch);
 gotoxy(27,10);
 for(i=0;i<=26;i++)
 {
	delay(50);
	printf("%c",ce);
 }
 getch();
 cout<<endl;
 fstream Fil;
 Fil.open("font.txt",ios::in);
 char ch2;
 ch2=Fil.get();
 while (!Fil.eof())
 {
	cout<<ch2;
	ch2=Fil.get();
 }
 Fil.close();
 getch();
 clrscr();
 int choice;
 constream cout;
 cout<<setclr(500);
 cout<<"                        Welcome to the elections of 2017  \n"<<endl;
 textcolor(WHITE);
 cout<<"This is a computerised voting system. Your vote will be registered"<<endl;
 cout<<"electronically"<<endl;
 do
 {
	cout<<endl<<endl<<"     1. Voter   2. Adminisitrator    3. Exit   ";
	cin>>choice;
	if (choice==2)   //ADMIN
	{
	 int Note=0;
	 do
	 {               //password
		clrscr();
		cout<<"Enter password ";
		char Pass[30];
		char ch;
		int i=0;
		do
		{
		 ch=getch();
		 Pass[i++]=ch;
		 cout<<"*";
		 }while (ch!=13);
		 Pass[i-1]='\0';
		ifstream fil("PASSWORD.txt");
		char real[30];
		fil.getline(real,80);
		fil.close();
		if (strcmp(Pass,real)==0)
		 Note=3;
		else
		{
		 cout<<"  Wrong password. 1) Try again 2) Exit ";
		 cin>>Note;
		}
	 }while(Note==1);
	 if(Note==3)
	  Admin();
	}
	else if (choice==1)               // VOTER
	 Vote();
	else if (choice==3)
	 cout<<"Exiting.."<<endl;
 }while(choice!=3);		//EXIT
 getch();
}

void NewCan ()   //To add new candidate
{
 clrscr();
 fstream fil;
 char ch2;
 fil.open("CanDat.dat", ios::binary|ios::app);
 do
 {
	clrscr();
	Candidate C1;
	C1.Input();
	C1.Inid();
	fil.write( (char*)&C1, sizeof(C1));
	cout<<endl<<"Add more?(Y/N)";
	cin>>ch2;
 }while((ch2=='y')||(ch2=='Y'));
 fil.close();
}
 void ViewVoter()
{
		fstream fil;
		fil.open("VData.dat", ios::binary| ios::in);
		fil.seekg(0,ios::beg);
		Voter v;
		cout<<" V.ID  |  NAME"<<endl;
		while(fil.read((char*)&v, sizeof(v)))
		 v.Dis();
		fil.close();
	 }
void EditVoter() //To add or delete voter in list
{
 int ch;
 do
 {
	cout<<"1. Add Voter   2. Delete existing voter   3. Exit\n";
	cin>>ch;
	switch(ch)
	{
	 case 1://add voter
					 AddVoter();
					 break;
	 case 2://Delete voter
					 if (DelV())
					 {
						remove("VData.dat") ;
						rename("temp.dat", "VData.dat");
					 }
					 break;
	 case 3: cout<<"Exiting..";
	}
 }while(ch!=3);
}

int DelV()
{
 fstream FIL1,FIL2;
 Voter v;
 FIL1.open("VData.dat", ios::binary|ios::in);
 FIL2.open("temp.dat", ios::binary|ios::out);
 int ID,Del=0;
 cout<<"Enter voter ID to be deleted ";
 cin>>ID;
 while(FIL1.read((char*)&v, sizeof(v)))
	if (v.Ret()!=ID)
	 FIL2.write((char*)&v,sizeof(v));
	else
	 Del++;
 if (Del==0)
	cout<<"Voter not found..."<<endl;
 else
	cout<<"Voter Successfully Deleted.";
 getch();
 clrscr();
 FIL1.close();
 FIL2.close();
 return Del;
}

void AddVoter()
{
	 fstream FIL;
	 FIL.open("VData.dat", ios::binary|ios::in|ios::out);
	 char n[40];
	 cout<<"Enter Name ";
	 gets(n);
	 Voter v1;
	 FIL.seekg(0,ios::end);
	 FIL.seekg(FIL.tellg()-sizeof(Voter));
	 FIL.read((char*)&v1, sizeof(v1));
	 Voter v(n, v1.Ret()+1);
	 int x=v.Ret();
	 FIL.write((char*)&v, sizeof(v));
	 FIL.close();
	 cout<<"Voter "<<x<<" successfully added.";
	 getch();
	 clrscr();
	}

 void Sort()
 {
 fstream fil;
 fil.open("CanDat.dat",ios::in|ios::binary|ios::out);
 fil.seekg(0,ios::end);
 int NOR=fil.tellg()/sizeof(Candidate);
 Candidate c1,c2;
 for (int i=0;i<NOR-1;i++)
   for (int j=0;j<NOR-i-1;j++)
  {
   fil.seekg(j*sizeof(c1));
   fil.read((char*)&c1,sizeof(c1));
   fil.read((char*)&c2,sizeof(c2));
   if (c1.RVotes()<c2.RVotes())
   {
    fil.seekp(j*sizeof(c1));
    fil.write((char*)&c2,sizeof(c1));
    fil.write((char*)&c1,sizeof(c1));
   }
  }
  fil.close();
 }

void CheckVotes()
{
 Sort();
 clrscr();
 fstream fil;
 fil.open("CanDat.dat",ios::in|ios::binary);
 Candidate c1;
 cout<<"CANDIDATE NAME    |  VOTES "<<endl;

 fil.seekg(0,ios::beg);
 while(fil.read((char*)&c1,sizeof(c1)))
 {
	c1.DVotes();
	cout<<endl;
 }
 getch();
 fil.close();
}

void Admin()   //ADMIN
{
 clrscr();
 int choice;
 do
 {                           //Admin main menu
	clrscr();
	cout<<" 1. Candidate list  2. Voter list  3. Check votes"<<endl;
	cout<<" 4. Change password  5. Exit  ";
	cin>>choice;
	if(choice==1)         //Candi
	{
	 clrscr();
	 int ch;
	 cout<<" 1. Enter new  2. Exit ";//Candidate list menu
	 cin>>ch;
	 if(ch==1)
		NewCan();
	 else if(choice==2)
		cout<<"Exiting";
	}
	else if(choice==2)   //Voter
	{
	 clrscr();
	 int ch;
	 cout<<" 1. View  2. Edit  3. Exit ";//Voter list menu
	 cin>>ch;
	 if(ch==1)
		ViewVoter();
	 else if(ch==2)
		EditVoter();
	 else if(ch==3)
	 cout<<"Exiting.."<<endl;
	}
	else if(choice==3)   //Check votes
	 CheckVotes();
	else if(choice==4)
	 NewPass();
	else if(choice==5)
	{
	 cout<<"Exiting..";
	 clrscr();
	}
 }while(choice!=5);	//Main menu ends
}

void NewPass()
{
 clrscr();
 char pass[20];
 cout<<"Enter new password of length 6 characters"<<endl<<"   ";
 gets(pass);
 ofstream fil("Password.txt");
 fil<<pass;
 fil.close();
}

void Voting()
{
 int id, Cid;
 cout<<"Please enter your Voter ID ";
 cin>>id;
 int Found=0;
 fstream fil;
 fil.open("VData.dat", ios::in|ios::out| ios::binary);
 Voter V;
 while(!Found && fil.read((char*)&V, sizeof(V)) )
	if(V.Ret()==id)
	 Found++;
 if (!Found)
	cout<<" Invalid voter id"<<endl;
 else if (V.RVoted()>0)
 {
	cout<<" Voter ID already Voted."<<endl;
	getch();
 }
 else
 {
	int found=0;
	do{
	 clrscr();
	 cout<< "                            			     ";
	 V.Dis();
	 cout<<endl;
	 DispList();
	 cout<<"Please enter the Candidate Id of the Candidate you want to vote."<<endl;
	 cin>>Cid;
	 FilOpen(Cid,found);
	}while (!found);
	V.CVoted();
	fil.seekg( fil.tellg()-sizeof(V));
	fil.write((char*) &V, sizeof(V));
 }
 fil.close();
}

void DispList()
{
 fstream fil;
 fil.open("CanDat.dat", ios::in| ios::binary);
 Candidate C;
 while(fil.read((char*)&C, sizeof(C)))
 {
	cout<<"Candidate ID | Name"<<endl;
	C.List();
 }
 fil.close();
}

void FilOpen(int Cid, int& found)
{
 fstream Fil;
 Fil.open("CanDat.dat", ios::in|ios::binary|ios::out);
 Candidate C;
 while(!found && Fil.read((char*)&C, sizeof(C)))
  if(C.Rid()==Cid)
  {
   found++;
   C.Vote();
   Fil.seekg( Fil.tellg()-sizeof(C));
   Fil.write((char*) &C, sizeof(C));
   cout<<"\n Your vote has been registered. Thank you!"<<endl;
   getch();
  }
 if (!found)
 {
  cout<<"Invalid Candidate Id";
  getch();
 }
 Fil.close();
}

void Vote()
{
 clrscr();
 int choice;
 clrscr();
 do
 {
	clrscr();                       //VOTER Main menu
	cout<<" 1. Vote  2. Check candidate profile  3. Exit ";
	cin>>choice;
	if(choice==1)         //Vote
	 Voting();
	else if (choice==2) //CANDIDATE PROFILE
	 Cpro();
	else if(choice==3)//exiting
	{
	 cout<<"Exiting..";
	 clrscr();
	}
 }while(choice!=3);
}

void Cpro()
{
 int Cid;
 DispList();
 cout<<"Please enter the Candidate Id ";
 cin>>Cid;
 int Found=0;
 fstream fil;
 fil.open("CanDat.dat", ios::in| ios::binary);
 Candidate C;
 while(!Found && fil.read((char*)&C, sizeof(C)) )
 if (C.Rid()==Cid)
 {
	Found++;
	C.Profile();
 }
 fil.close();
 if (Found==0)
 cout<<"Invalid Candidate Id";
}
