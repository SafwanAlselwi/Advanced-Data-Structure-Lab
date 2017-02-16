/* 
By: Safwan Alselwi
Subscribe to my channel to get new lessons when they are published
https://www.youtube.com/safwanalselwi

1.Write a C++ program to:
Read series of names, one per line, from standard input
& write these names spelled in reverse order to the standard output using I/O redirection and pipes.

Repeat the exercise using an input file specified by the user instead of the standard input
& using an output file specified by the user instead of the standard output.*/

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

class std_file{
private:
    char names[10][20];
public:
    void std_IO();
    void file_io();
};

int main(){
    std_file obj;
    system("cls");//clrscr();
    int ch;
    while(1){ //for(;;)
        cout<<"\n1. Standard IO \t 2.File IO \t Any other choice to Exit";
        cout<<"\nEnter your choice: ";
        cin>> ch;

        switch(ch){
            case 1:
                obj.std_IO();
                break;
            case 2:
                obj.file_io();
                break;
            default:
                exit(0);
        }
    }
    return 0;
}

void std_file::std_IO(){
    int i,num;
    cout<<"\nEnter the number of names: ";
    cin>>num;

    cout<<"\nEnter the names one by one "<<endl;
    for(i=0;i<num;i++)
        cin>>names[i];

    cout<<"\nThe names in reversed order are "<<endl;
    for(i=0;i<num;i++)
        cout<<strrev(names[i])<<endl;

    char output[10];
    cout<<"\nEnter the name of the file to store the names into: ";
    cin>>output;
    fstream out;
    out.open(output,ios::out);
    for(i=0;i<num;i++)
        out<<strrev(names[i])<<endl;
    out.close();
}

void std_file::file_io(){
    fstream in,out;
    char input[10],output[10];

    cout<<"\nEnter the name of the input file: ";
    cin>>input;
    cout<<"\nEnter the name of the output file: ";
    cin>>output;

    in.open(input,ios::in);
    out.open(output,ios::out);

    if(!in){
        cout<<"\nCannot open the file";
        getch();
        exit(0);
    }

    char line[20];
    while(!in.eof()){
        in.getline(line,20);
        out<<strrev(line)<<endl;
    }

    in.close();
    out.close();
}
