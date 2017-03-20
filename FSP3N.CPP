/*3.Write a C++ Program to read and write Student objects with variable length records using any suitable structure.
Implement pack(), unpack(), modify() and search() methods.*/
/*Note: This is the same as Program2, but with modify() function changed and pack() becomes v-length*/
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
	char fname[10] = "FSP3.txt";
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
	Student s[10];
	char extra[50];
	int i=0;
	while(!iofile.eof()){
		iofile.getline(s[i].name,10,'|');
		iofile.getline(s[i].sem,10,'|');
		iofile.getline(s[i].branch,10,'|');
		iofile.getline(extra,45,'\n');
		i++;
	}
	iofile.close();

	int flag=0;
	for(int j=0;j<i;j++){
		if(strcmp(key,s[j].name)==0){
			flag=1;
			cout<<"Record Found, Enter the new details"<<endl;
			cout<<"Enetr the name"<<endl;
			cin>>s[j].name;
			cout<<"Enter the sem;"<<endl;
			cin>>s[j].sem;
			cout<<"Enter the branch"<<endl;
			cin>>s[j].branch;
		}
	}
	if(flag==0){
		cout<<"Record not found\n";
		return;
	}
	iofile.open("FSP3.txt",ios::trunc|ios::app);
	for(int k=0;k<i;k++){
		if (s[k].name != "|"){
			strcpy(buf,"");
			strcat(buf,s[k].name);
			strcat(buf,"|");
			strcat(buf,s[k].sem);
			strcat(buf,"|");
			strcat(buf,s[k].branch);
			strcat(buf,"|");
			strcat(buf,"\n");
			iofile.write(buf,strlen(buf));
		}
	}
	iofile.close();
}