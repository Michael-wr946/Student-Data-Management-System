//NITC Semester wise Student Database Management System
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;
//Global Variables
int maxlenName = 0; //stores the length of the longest name for aligning the output while printing
int maxlenEmail = 0; //sotores the length of the longest email for aligning the output while printing
unordered_map<string, int> dictionary;//Stores the name of students as key and its index in the vector database, as value for searching by student name.

class student{//student class stores all the data of a single student.
    public:
        string name;
        string regno;
        vector<string> grades;
        float sgpa;
        string DoB;
        string email;
        bool gotName;
        bool gotGrade;
    student(){
        gotName = false;
        sgpa = 0;
    }
};
vector<student> database(3000);//A vector of students where each the integers in the registration no. are taken as the index positions.
class compare{//Custom comparator for a priority queue where the students are sorted based on sgpa and alphabetically if they have the same sgpa.    
public:
    bool operator()(int a, int b){
        if(database[a].gotName and database[b].gotName and database[a].sgpa == database[b].sgpa){
            return database[a].name > database[b].name;
        }
        return database[a].sgpa < database[b].sgpa;
    }
};
priority_queue<int,vector<int>,compare> rankedIndex;//Stores the indexes of students in descending order of sgpa.

//**************************************************************
//   FUNCTION TO PRINT THE DATA OF A SINGLE STUDENT FROM ROLL NO
//*
string upperCase(string name){
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    return name;
}
//*********************************************************************************************
//   FUNCTION TO INPUT THE NAME, REG NO., EMAIL AND DOB OF EACH STUDENT FROM THE "Names.txt" FILE AND STORE IT IN THE VECTOR "DATABASE".
//*********************************************************************************************
void addNames(){
    string first_name,last_name,email,dob,reg;

    ifstream inFile;
    inFile.open("Names.txt");
    //Check for error
    if(inFile.fail()){
        cerr<<"Error Reading file";
        exit(1);
    }
    while(!inFile.eof()){
        inFile>>first_name;
        inFile>>last_name;
        inFile>>email;
        inFile>>dob;
        int index =0;
        for(int i = 0 ;i<email.size();i++){
            if(email[i]=='_'){
                i++;
                index = stoi(email.substr(i+3,4));
                string regno = email.substr(i,9);
                database[index].regno = regno;
                break;
            }
        }
        string name = first_name + " " + last_name;
        database[index].name = name;
        maxlenName = max(maxlenName,(int)name.size());
        database[index].email = email;
        maxlenEmail = max(maxlenEmail,(int)email.size());
        database[index].DoB = dob;
        database[index].gotName = true;
        //Read a file until you've reached the end;
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        dictionary[name] = index;

    }
    inFile.close();

}

//*********************************************************************************************
//   FUNCTION TO INPUT THE SGPA AND REG NO. OF EACH STUDENT FROM THE "Grades.txt" FILE AND STORE IT IN THE VECTOR "DATABASE".
//*********************************************************************************************
void addGrades(){
    ifstream inFile;
    inFile.open("Grades.txt");
    //check for error
    if(inFile.fail()){
        cerr<<"Error Reading file";
        exit(1);
    }
    string str;
    int count =0;
    //Read a file until you'vve reached the end
    while(!inFile.eof()){
        inFile>>str;
        if(str[0]=='B' and str[1] == '1' and str[2] == '8'){
            int index = stoi(str.substr(3,4));
            database[index].regno = str;
            int subs =100;
            while(subs--){
                inFile>>str;
                try{
                    database[index].sgpa = (float)stof(str);
                    database[index].gotGrade = true;
                    break;
                }
                catch(...){
                    if(str!="H" and str!="N"){
                        database[index].grades.push_back(str);
                    }
                }    
                
            }
            rankedIndex.push(index);//pushes the index of each student to the priority queue which gets sorted automatically
            
        }
    }
    inFile.close();
}
//*********************************************************************************************
//   FUNCTION TO PRINT ALL THE DATA IN ASCENDING ORDER OF REG NO. OF STUDENTS
//*********************************************************************************************
void printAll(){
    cout<<"List of Students ordered according to their Registration Numbers"<<endl;
    cout<<endl;
    int number = 1;
    for(int i=0;i<3000;i++){
        if(database[i].gotName and database[i].gotGrade){
            if(number<10){
                cout<<"  ";
            }else if(number <100){
                cout<<" ";
            }//else if(number <1000){
            //     cout<<" ";
            // }
            cout<<number++<<" ";
            cout<<database[i].regno<<" | ";
            int sizeOfName = database[i].name.size();
            cout<<database[i].name;
            while(sizeOfName != maxlenName){
                cout<<" ";
                sizeOfName++;
            }
            cout<<" | ";
            cout<<database[i].sgpa;
            int decimal = (int)((database[i].sgpa)*100);
            if((decimal)%10 != 0){
                cout<<" | ";
            }else{
                decimal = (int)((database[i].sgpa)*10);
                if((decimal)%10 == 0 ){
                    cout<<"   ";
                }else{
                    cout<<" ";
                }
                cout<<" | ";
            }
            int sizeOfEmail = database[i].email.size();
            cout<<database[i].email;
            while(sizeOfEmail != maxlenEmail){
                cout<<" ";
                sizeOfEmail++;
            }
            cout<<endl;
        }
    }
}
//*********************************************************************************************
//   FUNCTION TO PRINT ALL THE DATA IN DESCENDING ORDER OF SGPA OF STUDENTS
//*********************************************************************************************
void printRank(priority_queue<int,vector<int>,compare> rankedIndex){
    cout<<"List of Student ordered according to their Semester GPAs"<<endl;
    cout<<endl;
   int number = 1;
   while(!rankedIndex.empty()){

        if(database[rankedIndex.top()].gotName and database[rankedIndex.top()].gotGrade){
            if(number<10){
                cout<<"  ";
            }else if(number <100){
                cout<<" ";
            }//else if(number <1000){
            //     cout<<" ";
            // }
            cout<<number++<<" ";
            cout<<database[rankedIndex.top()].regno<<" | ";
            int sizeOfName = database[rankedIndex.top()].name.size();
            cout<<database[rankedIndex.top()].name;
            while(sizeOfName != maxlenName){
                cout<<" ";
                sizeOfName++;
            }
            cout<<" | ";
            cout<<database[rankedIndex.top()].sgpa;
            int decimal = (int)((database[rankedIndex.top()].sgpa)*100);
            if((decimal)%10 != 0){
                cout<<" | ";
            }else{
                decimal = (int)((database[rankedIndex.top()].sgpa)*10);
                if((decimal)%10 == 0 ){
                    cout<<"   ";
                }else{
                    cout<<" ";
                }
                cout<<" | ";
            }
            cout<<database[rankedIndex.top()].email<<endl;  
        }
        rankedIndex.pop();
    }
}
//***************************************************************************
//   FUNCTION TO PRINT LIST OF STUDENTS NOT PRESENT IN THE "Grades.txt" file
//***************************************************************************
void printOnlyNames(){
    cout<<"List of Students who are not present in the Semester Results file"<<endl;
    cout<<endl;
    int number = 1;
    for(int i=0;i<3000;i++){
        if(database[i].gotName and !database[i].gotGrade){
            if(number<10){
                cout<<"  ";
            }else if(number <100){
                cout<<" ";
            }//else if(number <1000){
            //     cout<<" ";
            // }
            cout<<number++<<" ";
            int sizeOfName = database[i].name.size();
            cout<<database[i].name;
            while(sizeOfName != maxlenName){
                cout<<" ";
                sizeOfName++;
            }
            cout<<" | ";
            cout<<database[i].regno<<" | ";
            cout<<database[i].sgpa<<endl;
        }
    }
}
//***************************************************************************
//   FUNCTION TO PRINT LIST OF STUDENTS NOT PRESENT IN THE "Names.txt" file
//***************************************************************************
void printOnlyGrades(){
    int number = 1;
    for(int i=0;i<3000;i++){
        if(!database[i].gotName and database[i].gotGrade){
            if(number<10){
                cout<<"  ";
            }else if(number <100){
                cout<<" ";
            }//else if(number <1000){
            //     cout<<" ";
            // }
            cout<<number++<<" ";
            cout<<database[i].regno<<" | ";
            cout<<database[i].sgpa<<endl;
        }
    }
}

//***********************************************************
//   FUNCTION TO PRINT THE DATA OF A SINGLE STUDENT FROM NAME
//***********************************************************
void printFromName(string student_name){
    string name = student_name;
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    if(dictionary.count(name)){
        int index = dictionary[name];
        cout<<database[index].regno<<" | ";
        cout<<database[index].name<<" | ";
        cout<<database[index].sgpa<<" | ";
        cout<<database[index].email<<endl;
    }else{
        cout<<"Student not found!"<<endl;
    }
}

//**************************************************************
//   FUNCTION TO PRINT THE DATA OF A SINGLE STUDENT FROM ROLL NO
//**************************************************************
void printFromRegNo(string regno){
    int index = stoi(regno.substr(3,4));
    if(database[index].gotGrade){
        cout<<database[index].regno<<" | ";
        cout<<database[index].name<<" | ";
        cout<<database[index].sgpa<<" | ";
        cout<<database[index].email<<endl;
    }else{
        cout<<"Student not found!"<<endl;
    }
}
//***************************************************************************
//   FUNCTION TO PRINT "_" IN A LOOP. TO BE USED AS A SEPERATOR 
//***************************************************************************
void filler(){
    for(int i=0;i<30;i++){
            cout<<"_ ";
    }
    cout<<endl;
    cout<<endl;
}
//***************************************************************************
//   FUNCTION TO SAVE ALL THE DATA IN A CSV FORMAT IN THE "Output.csv" FILE.
//***************************************************************************
void saveOutputAll(){
    int number = 1;
    ofstream outfile;
    outfile.open("Output.csv");
    if(outfile.fail()){
        cerr<<"Error Reading file";
        exit(1);
    }
    outfile<<"Index No."<<", ";
    outfile<<"Roll No."<<", ";
    outfile<<"Name               "<<", ";
    outfile<<"SGPA"<<", ";
    outfile<<"Email"<<", ";
    outfile<<"Date of Birth"<<endl;
    for(int i=0;i<3000;i++){
        if(database[i].gotName and database[i].gotGrade){
            outfile<<number++<<", ";
            outfile<<database[i].regno<<", ";
            outfile<<database[i].name<<", ";
            outfile<<database[i].sgpa<<", ";
            outfile<<database[i].email<<", ";
            outfile<<database[i].DoB<<endl;
        }
    }
    outfile.close();
    cout<<"The Ouput has been succesfully saved"<<endl;
}

//********************************************************************************************
//   FUNCTION TO SAVE ALL THE DATA IN THE RANKED ORDERIN A CSV FORMAT IN THE "Output.csv" FILE.
//********************************************************************************************
void saveOutputRanked(priority_queue<int,vector<int>,compare> rankedIndex){
    int number = 1;
    ofstream outfile;
    outfile.open("Output.csv");
    if(outfile.fail()){
        cerr<<"Error Reading file";
        exit(1);
    }
    outfile<<"Index No."<<", ";
    outfile<<"Roll No."<<", ";
    outfile<<"Name"<<", ";
    outfile<<"SGPA"<<", ";
    outfile<<"Email"<<", ";
    outfile<<"Date of Birth"<<endl;
     while(!rankedIndex.empty()){

        if(database[rankedIndex.top()].gotName and database[rankedIndex.top()].gotGrade){
            outfile<<number++<<", ";
            outfile<<database[rankedIndex.top()].regno<<", ";
            outfile<<database[rankedIndex.top()].name<<", ";
            outfile<<database[rankedIndex.top()].sgpa<<", ";
            outfile<<database[rankedIndex.top()].email<<", ";
            outfile<<database[rankedIndex.top()].DoB<<endl;
        }
        rankedIndex.pop();
    }
    outfile.close();
    cout<<"The Ouput has been succesfully saved"<<endl;
}

//********************************************************
//   FUNCTION TO ADD THE DATA OF A STUDENT TO THE DATABASE
//********************************************************
void addStudent(){
    string first_name,last_name,email,dob,reg;
    float sgpa = 0;
    cout<<" Enter the first name of the student"<<endl;
    cin>>first_name;
    cout<<" Enter the last_name of the student"<<endl;
    cin>>last_name;
    cout<<" Enter the registration number of the student"<<endl;
    cin>>reg;
    cout<<" Enter the SGPA of the student"<<endl;
    cin>>sgpa;
    cout<<" Enter the email address of the student"<<endl;
    cin>>email;
    cout<<" Enter the date of birth of the student"<<endl;
    cin>>dob;
    int index = stoi(reg.substr(3,4));
    string name = first_name + " " + last_name;
    database[index].name = upperCase(name);
    maxlenName = max(maxlenName,(int)name.size());
    database[index].email = email;
    maxlenEmail = max(maxlenEmail,(int)email.size());
    database[index].DoB = dob;
    database[index].regno = upperCase(reg);
    database[index].gotName = true;
    database[index].sgpa = sgpa;
    database[index].gotGrade = true;
    //Read a file until you've reached the end;
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    dictionary[name] = index;
    rankedIndex.push(index);
    filler();
    cout<<"Student added succesfully"<<endl;
}
int main(){
    addNames();
    addGrades();
    int loop = 3;
    while(loop == 3){
        cout<<" Available Operations: "<<endl;
        cout<<" 1. Student Access"<<endl;
        cout<<" 2. Faculty Access"<<endl;
        cout<<" 3. Admin View"<<endl;
        cout<<" 4. Exit"<<endl;
        cout<<" ";
        int choice;
        cin>>choice;
        filler();
        if(choice == 1){
            string regno;
            cout<<" Enter your Registration Number:"<<endl;
            cout<<" ";
            cin>>regno;
            filler();
            printFromRegNo(regno);
        }else if(choice == 2){
            while(loop == 3){
                cout<<" Available Operations For Faculty: "<<endl;
                cout<<" 1. Add new student "<<endl;
                cout<<" 2. Search Student by Name"<<endl;
                cout<<" 3. Back"<<endl;
                cout<<" 4. Exit"<<endl;
                cout<<" ";
                cin>>choice;
                if(choice == 1){
                    addStudent();
                }else if(choice == 2){
                    string student_name;
                    cout<<" Enter the full name of the Student:"<<endl;
                    cout<<" ";
                    cin.ignore();
                    getline(cin, student_name);
                    filler();
                    printFromName(student_name);

                }else if(choice == 3){
                    break;
                }else {
                    choice = -1;
                    break;
                }
                filler();
            }
        }else if(choice == 3){
            while(loop == 3){
                cout<<" Available Operations For Admin: "<<endl;
                cout<<" 1. Print all the data"<<endl;
                cout<<" 2. Print Ranked data"<<endl;
                cout<<" 3. Print Names with no grades"<<endl;
                cout<<" 4. Save Roll NO. sorted Output"<<endl;
                cout<<" 5. Save SGPA Ranked Output"<<endl;
                cout<<" 6. Back"<<endl;
                cout<<" 7. Exit"<<endl;
                cout<<" ";
                int choice;
                cin>>choice;
                    filler();
                if(choice == 1){
                    printAll();
                }else if(choice == 2){
                    printRank(rankedIndex);
                }else if(choice == 3){
                    printOnlyNames();
                }else if(choice == 4){
                    saveOutputAll();
                }else if(choice == 5){
                    saveOutputRanked(rankedIndex);
                }else if(choice == 6){
                    break;
                }
                else{
                    choice = -1;
                    break;
                }
                filler();
            }
        }else{
            cout<<"Exited Succesfully"<<endl;
                filler();
                break;
        }
        filler();
        if(choice == -1){
            cout<<"Exited Succesfully"<<endl;
                filler();
                break;
        }
    }
    return 0;
}
