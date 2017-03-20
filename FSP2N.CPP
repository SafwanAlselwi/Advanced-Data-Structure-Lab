/*2.Write a C++ Program to read and write Student objects with fixed length method and the fields delimited by "|".
Implement pack(), unpack(), modify() and search() methods.*/
#include<iostream.h>
#include<fstream.h>
#include<process.h>
#include<string.h>
#include<conio.h>

class Student{
	private:
		char buf[45],name[10],sem[10],branch[10];
	public:
		void pack(fstream &ofile);
		void unpack(fstream &ifile);
		int search(fstream &ifile,char key[]);
		void modify(fstream &iofile,char key[]);
};

void main(){
	int num,ch;
	char fname[10] = "FSP2.txt";
	Student obj;
	fstream ofile; /*truncate the previous data of the file*/
	ofile.open(fname,ios::trunc|ios::app);
	ofile.close();
	clrscr();
	while(1)
	{
		clrscr();
		cout<<"1. Insert\n2. Display \n3. Search\n4. Modify\nAny other to Exit\n";
		cout<<"Enter your choice"<<endl;
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
				cout<<"Enter the record name to be searched"<<endl;
				cin>>key;
				fstream ifile;
				ifile.open(fname,ios::in);
				if(obj.search(ifile,key)==0)
					cout<<"Record not found\n";
				getch();
				ifile.close();
				break;
			case 4: 
				fstream iofile;
				iofile.open(fname,ios::in|ios::out);
				cout<<"Enter the record name to be modified"<<endl;
				cin>>key;
				obj.modify(iofile,key);
				getch();
				iofile.close();
				break;
			default: exit(0);
		}
	}
}

void Student::pack(fstream &ofile){
	cout<<"\nEnter Name    : ";	cin>>name;
	cout<<"\nEnter Semester: ";	cin>>sem;
	cout<<"\nEnter Branch  : ";	cin>>branch;

	strcpy(buf,"");
	strcat(buf,name);
	strcat(buf,"|");
	strcat(buf,sem);
	strcat(buf,"|");
	strcat(buf,branch);
	strcat(buf,"|");
	while(strlen(buf)<45)
		strcat(buf,"_");
	strcat(buf,"\n");
	ofile.write(buf,strlen(buf));
}

void Student::unpack(fstream &ifile){
	while(!ifile.eof()){
		ifile.getline(name,10,'|');
		ifile.getline(sem,10,'|');
		ifile.getline(branch,10,'|');
		ifile.getline(buf,45,'\n');
		cout<<name<<"\t"<<sem<<"\t"<<branch<<"\n";
	}
}

int Student::search(fstream &ifile,char key[]){
	while(!ifile.eof()){
		ifile.getline(name,10,'|');
		ifile.getline(sem,10,'|');
		ifile.getline(branch,10,'|');
		ifile.getline(buf,45,'\n');

		if(strcmp(name,key)==0){
			cout<<"Record found and details are:"<<endl;
			cout<<"Name    : "<<name<<endl;
			cout<<"Semester: "<<sem<<endl;
			cout<<"Branch  : "<<branch<<endl;
			return 1;
		}
	}
	return 0;
}

void Student::modify(fstream &iofile,char key[]){
	if(search(iofile,key)){
		cout<<"Record found, Enter new details:"<<endl;
		iofile.seekp(-47,ios::cur);
		pack(iofile);
	}
	else
		cout<<"Sorry! No such record\n";
}