/*6. Write a C++ program to implement index on secondary key, the name, for a file of student objects.
Implement add(),search(),remove() using the secondary index.*/
/*Note: Same as p5, but here use NAME as secondary key instead of USN*/
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int n=0,index=0;
char fname_i[15] = "FSP6N_I.txt";
char fname_r[15] = "FSP6N_R.txt";

class Student{
	private:
		char name[10],usn[10],sem[10],branch[10];
	public:
		void add(fstream &fi,fstream &fr);
		void write(fstream &fi,fstream &fr);
		void display(fstream &fr);
		int search(fstream &fi,fstream &fr,char key[10]);
		int remove(fstream &fi,fstream &fr,char key[10]);
}s[20];

void main(){
	Student obj;
	int ch,num,i;

	fstream fi,fr;
	fi.open(fname_i,ios::trunc|ios::app);																																												/*truncate the previous data of the file*/
	fr.open(fname_r,ios::trunc|ios::app);
	fi.close();
	fr.close();
	clrscr();
	while(1){
		cout<<"\n1.Add \n2.Display \n3.Search \n4.Delete \nAny other to Exit";
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch){
			case 1:
				fi.open(fname_i,ios::out|ios::app);
				fr.open(fname_r,ios::out|ios::app);
				cout<<"Enter no. of Students: ";
				cin>>num;
				n=n+num;
				for(i=1;i<=num;i++)
					s[i].add(fi,fr);
				fi.close();
				fr.close();
				break;
			case 2:
				fr.open(fname_r,ios::in);
				cout<<"\nName \tUSN \tSem \tBranch\n";
				for(i=1;i<=n;i++)
					s[i].display(fr);
				fr.close();
				break;
			case 3:
				char key[10];
				cout<<"Enter NAME key to search: ";
				cin>>key;
				fi.open(fname_i,ios::in);
				fr.open(fname_r,ios::in);
				if(obj.search(fi,fr,key)==0)
					cout<<"Record not found\n";
				getch();
				fi.close();
				fr.close();
				break;
			case 4:
				cout<<"Enter NAME key to delete: ";
				cin>>key;
				fi.open(fname_i,ios::in);
				fr.open(fname_r,ios::in);
				if(obj.remove(fi,fr,key)!=0)
					cout<<"Deletion Successful\n";
				getch();
				fi.close();
				fr.close();
				break;
			default:exit(0);
		}
	}
}

void Student::add(fstream &fi,fstream &fr){
	cout<<"Enter Name  : ";		cin>>name;
	cout<<"Enter USN   : ";		cin>>usn;
	cout<<"Enter Sem   : ";		cin>>sem;
	cout<<"Enter Branch: ";		cin>>branch;
	write(fi,fr);
}

void Student::write(fstream &fi,fstream &fr){
	fi<<(++index)<<"\t"<<name<<"\n"; /*name as secondary key index ,,, instead of usn*/
	fr<<name<<"\t"<<usn<<"\t"<<sem<<"\t"<<branch<<"\n";
}

void Student::display(fstream &fr){
	fr>>name>>usn>>sem>>branch;
	cout<<name<<"\t"<<usn<<"\t"<<sem<<"\t"<<branch<<"\n";
}

int Student::search(fstream &fi,fstream &fr,char key[10]){
	/*First: search in index file(fi), then if index found , search in records file(fr)*/
	int i=0;
	char x[10];
	while(!fi.eof()){
		fi>>x>>name; /*name as secondary key index ,,, instead of usn*/
		i++;
		if(strcmp(name,key)==0){
			while(!fr.eof()){
				fr>>name>>usn>>sem>>branch;
				if(strcmp(name,key)==0){
					cout<<"Record found & Details are\n";
					cout<<"Name   : "<<name<<endl;
					cout<<"USN    : "<<usn<<endl;
					cout<<"Sem    : "<<sem<<endl;
					cout<<"Branch : "<<branch<<endl;
					return i;
				}
			}
		}
	}
	return 0;
}

int Student::remove(fstream &fi,fstream &fr,char key[10]){
	int i,j=0;
	j = search(fi,fr,key);
	if (j != 0)/*record Found, do shifting, reduce index number, rewrite data gain to files*/
	{
		for(i=j; i<n; i++)
			s[i]=s[i+1];

		n--;
		index--;
		fi.close();
		fr.close();
		fi.open(fname_i,ios::trunc|ios::app);
		fr.open(fname_r,ios::trunc|ios::app);
		index=0;
		for(i=1; i<=n; i++)
			s[i].write(fi,fr);
		return 1;//Deletion occured
	}
	cout<<"Record not found, No Deletion Occured\n";
	return 0;
}