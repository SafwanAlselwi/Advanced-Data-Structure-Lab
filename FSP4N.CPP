/*4.Write a C++ program to read and write student objects with Variable-Length records using any suitable record
structure and to read from this file a student record using RRN (Relative Record Number).*/
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

int k = 0;
class Student{
	private:
		char buf[45],name[10],sem[10],branch[10],rrn[10];
	public:
		void pack(fstream &ofile);
		void unpack(fstream &ifile);
		int search(fstream &ifile,char key[]);
};

void main(){
	int num,ch;
	char fname[10] = "FSP4.txt";
	Student obj;
	fstream ofile; /*truncate the previous data of the file*/
	ofile.open(fname,ios::trunc|ios::app);
	ofile.close();
	clrscr();
	while(1)
	{
		clrscr();
		cout<<"1. Insert\n2. Display \n3. Search\nAny other to Exit\n";
		cout<<"Enter your choice : "<<endl;
		cin>>ch;
		switch(ch){
			case 1:
				fstream ofile;
				ofile.open(fname,ios::out|ios::app);
				cout<<"Enter the no. of Students"<<endl;
				cin>>num;
				for(int i=0;i<num;i++)
					obj.pack(ofile);
				ofile.close();
				break;
			case 2:
				fstream infile;
				infile.open(fname,ios::in);
				obj.unpack(infile);
				getch();
				infile.close();
				break;
			case 3:
				char key[10];
				cout<<"Enter the RRN to be searched"<<endl;
				cin>>key;
				fstream ifile;
				ifile.open(fname,ios::in);
				if(obj.search(ifile,key)==0)
					cout<<"Record not found\n";
				getch();
				ifile.close();
				break;
			default: exit(0);
		}
	}
}

void Student::pack(fstream &ofile){
	cout<<"\nEnter Name    : ";	cin>>name;
	cout<<"\nEnter Semester: ";	cin>>sem;
	cout<<"\nEnter Branch  : ";	cin>>branch;
	itoa(++k,rrn,10); /*Convert integer to string; included in stdlib*/

	strcpy(buf,"");
	strcat(buf,rrn);
	strcat(buf,"|");
	strcat(buf,name);
	strcat(buf,"|");
	strcat(buf,sem);
	strcat(buf,"|");
	strcat(buf,branch);
	strcat(buf,"|");
	strcat(buf,"\n");
	ofile.write(buf,strlen(buf));
}

void Student::unpack(fstream &ifile){
	while(!ifile.eof()){
		ifile.getline(rrn,10,'|');
		ifile.getline(name,10,'|');
		ifile.getline(sem,10,'|');
		ifile.getline(branch,10,'|');
		ifile.getline(buf,45,'\n');
		cout<<rrn<<"\t"<<name<<"\t"<<sem<<"\t"<<branch<<"\n";
	}
}

int Student::search(fstream &ifile,char key[]){
	while(!ifile.eof()){
		ifile.getline(rrn,10,'|');
		ifile.getline(name,10,'|');
		ifile.getline(sem,10,'|');
		ifile.getline(branch,10,'|');
		ifile.getline(buf,45,'\n');

		if(strcmp(key,rrn)==0){
			cout<<"Record found and details are:"<<endl;
			cout<<"RRN     : "<<rrn<<endl;
			cout<<"Name    : "<<name<<endl;
			cout<<"Semester: "<<sem<<endl;
			cout<<"Branch  : "<<branch<<endl;
			return 1;
		}
	}
	return 0;
}