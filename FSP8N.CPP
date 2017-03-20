/*8.Write a C++ program to read k Lists of names and merge them using kway merge algorithm with k =8 */
#include<conio.h>
#include<string.h>
#include<fstream.h>

class record{
	private:	
		char name[20];
	public :
		void merge_file(char* file1,char* file2,char* mfname);
		void kwaymerge();
}rec[20],obj;

char fname[8][8]={"1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt"};
char mfname[7][20]={"12.txt","34.txt","56.txt","78.txt","1234.txt","5678.txt","12345678.txt"};

void main(){
	int i,no;
	char name[20];
	fstream file[8];
	clrscr();
	
	/*PART A: 1.Open the Files 2. Write data to Files 3.Close the Files*/
	for(i=0; i<8 ; i++)
		file[i].open(fname[i],ios::out);

	cout<<"Enter no. of records: ";
	cin>>no;
	cout<<"Enter the details\n";
	for(i=0; i<no ; i++){
		cout<<"Name : ";
		cin>>name;
		file[i%8]<<name<<"\n";
	}
	for(i=0; i<8 ; i++)
		file[i].close();

	/*PART B: Applay the k-way merge*/
	obj.kwaymerge();

	/*PART C: Read the Merged Results from the Result File and Display on Screen*/
	cout<<"\nSorted Records are: \n";
	fstream result;
	result.open(mfname[6],ios::in); //12345678.txt
	while(!result.eof()){
		result.getline(name,20,'\n');
		cout<<"  "<<name;
	}
	getch();
}

void record::kwaymerge(){
	int i,k;
	
	k=0;
	cout<<"\n\nPass 1: (2 Page Run) ";
	for(i=0 ; i<8 ; i+=2)
		merge_file(fname[i],fname[i+1],mfname[k++]);
	
	k=4;
	cout<<"\n\nPass 2: (4 Page Run)";
	for(i=0 ; i<4 ; i+=2)
		merge_file(mfname[i],mfname[i+1],mfname[k++]);

	cout<<"\n\nPass 3: (8 Page Run)";
	merge_file(mfname[4],mfname[5],mfname[6]);
}

void record::merge_file(char* file1,char* file2,char* mfname){
	record temp;
	int k=0,i,j;
	fstream f1,f2,mf;

	f1.open(file1,ios::in);
	f2.open(file2,ios::in);
	mf.open(mfname,ios::out);

	/*PART A: Read contents of Files into rec objects*/
	while(!f1.eof())
		f1>>rec[k++].name;
	while(!f2.eof())
		f2>>rec[k++].name;

	/*PART B: Compare Names and swap if needed*/
	for(i=0 ; i<k-2 ; i++){ /* -2 is for 2 empty lines, one in each compared file*/
		for(j=0 ; j<k-i-2 ; j++){
			if(strcmp(rec[j].name,rec[j+1].name) > 0 ){
				temp = rec[j];
				rec[j] = rec[j+1];
				rec[j+1] = temp;
			}
		}
	}

	cout<<"\n"<<file1<<"+"<<file2<<" = "<<mfname<<": ";
	/*PART C: Write the sorted data to the File*/
	for(i=1; i<k-1; i++){
		mf<<rec[i].name<<"\n";
		cout<<rec[i].name<<"  ";
	}

	f1.close();
	f2.close();
	mf.close();
}