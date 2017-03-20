/*7.Write a C++ program to read two lists of names and then match the names in the two lists using
Consequential Match based on a single loop. Output the names common to both the lists.*/
/*Note: Before running this program create 2 files that includes some names*/
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

void bsort (char list[20][20],int n){
	char tmp[20];
	int i,j;
	for(i=0 ; i<n-1; i++){
		for(j=0 ; j<n-i-1; j++){
			if(strcmp(list[j],list[j+1])>0)
			{
				strcpy(tmp,list[j]);
				strcpy(list[j],list[j+1]);
				strcpy(list[j+1],tmp);
			}
		}
	}
}

void main(){
	char list1[20][20],list2[20][20];
	int i=0,j=0,m=0,n=0;
	clrscr();

	fstream out1,out2,out3;
	out1.open("file1.txt",ios::in);
	out2.open("file2.txt",ios::in);
	out3.open("file3.txt",ios::out);
	if((!out3)||(!out1)||(!out2)){
		cout<<"Unable to open one of the file";
		getch();
		exit(0);
	}

	cout<<"\nElements of 1st lists: \n";
	while(!out1.eof()){
		out1.getline(list1[m],20,'\n');
		cout<<list1[m]<<"\t";
		m++;
	}

	cout<<"\n\nElements of 2nd Lists: \n";
	while(!out2.eof()){
		out2.getline(list2[n],20,'\n');
		cout<<list2[n]<<"\t";
		n++;
	}

	bsort(list1,m);
	bsort(list2,n);

	cout<<"\n\nElements common to both files are\n";
	while(i<m && j<n){
		if(strcmp(list1[i],list2[j])==0){
			out3<<list1[i]<<'\n';
			cout<<list1[i]<<"\n";
			i++;
			j++;
		}
		else if(strcmp(list1[i],list2[j]) < 0)
			i++;
		else
			j++;
	}
	getch();
}