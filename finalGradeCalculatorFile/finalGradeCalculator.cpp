#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
void saveToFile(double gradeWeight[],double gradePercent[],string nameOfGrade[],int numOfGrades);
void letterGradeConverter();
int finalGradeCalculation();
int finalGradeCalculation2();
int fileCreation();

string fileName;
int menuChoice;
char letterGrade;
double finalCalculation=0.0;
int numOfGrades=1;
double totalWeightCount=0.0;
double firstPartCalculationFinal=0.0;
bool repeat=true;

int main(){
do{
  cout<<"\n--------------------------------------------";
  do{
    cout<<"\n1. Calculate Final Grade\n2. Calculate Final Grade With File\n3. Create or Modify a File\n4. Exit"<<endl;
    cout<<"Enter Choice: ";
    cin>>menuChoice;

      if (menuChoice==1){
        finalGradeCalculation();
      }else if (menuChoice==2){
        finalGradeCalculation2();
      }else if(menuChoice==3){
        fileCreation();
      }else if(menuChoice==4){
        cout<<"\nThank you for using my program!\n";
        repeat=false;
      }

      if(menuChoice <1 || menuChoice>4||!cin){
        cout<<"\n\033[31mError: Invalid response. Only enter numbers that pertain to the options.\033[0m\n"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }
    }while(menuChoice <1 || menuChoice>4||!cin);
  }while(repeat==true);
}

int finalGradeCalculation(){
  do{
    cout<<"\nHow many grades does your final grade consist of? ";
    cin>>numOfGrades;

    if(!cin){
      cout<<"Your input contains a letter, please try again and only enter positive numbers.\n"<<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }else if(numOfGrades<=0){
      cout<<"Please only enter numbers that are greater than 0.\n"<<endl;
    }

  }while(numOfGrades<=0||!cin);

  double gradeWeight[numOfGrades+1];
  double gradePercent [numOfGrades+1];
  double firstPartCalculation[numOfGrades+1];
  string nameOfGrade[numOfGrades+1];

  //cout<<"\n"<<endl;
  for (int count = 1;count<=numOfGrades;count++){//percent and weight of grade for loop
    cout<<"Enter Name of Grade "<<count<<": ";
    cin.ignore();
    getline(cin, nameOfGrade[count]);
    
    
    do{

    cout<<"Enter Percent of Grade "<<count<<": ";
    cin>> gradePercent[count];

    if(!cin){
      cout<<"\nError: One of your inputs contain a letter, please try again and only enter positive numbers.\n"<<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      count--;
      continue;
    }

    cout<<"Enter the weight of grade "<<count<<": ";
    cin>> gradeWeight[count];
    
    if(!cin){
      cout<<"\nError: One of your inputs contain a letter, please try again and only enter positive numbers.\n"<<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      count--;
      continue;
    }

    if(gradePercent[count]<0||gradeWeight[count]<0){
      cout<<"\nError: One of your inputs is less than 0, please try again and only enter positive numbers.";
    }

    cout<<"\n"<<endl;
    }while(gradePercent[count]<0||gradeWeight[count]<0/*||!isdigit(gradePercent[count])||!isdigit(gradeWeight[count])*/);
  }

  for (int count = 1;count<=numOfGrades;count++){
    totalWeightCount=totalWeightCount+gradeWeight[count];
  }
  
  for (int count = 1;count<=numOfGrades;count++){
    firstPartCalculation[count]=gradePercent[count]*gradeWeight[count];
    firstPartCalculationFinal=firstPartCalculationFinal+firstPartCalculation[count];
  }
  finalCalculation=(firstPartCalculationFinal)/totalWeightCount;

  // this_c::sleep_for(chrono::seconds(1));
  // cout<<"1... "<<endl;
  // this_thread::sleep_for(chrono::seconds(1));
  // cout<<"2... "<<endl;
  // this_thread::sleep_for(chrono::seconds(1));
  // cout<<"3... "<<endl;
  
  letterGradeConverter();
  
  cout<<"\nYour grade in the class is a "<<finalCalculation<<", which is a "<<letterGrade<<endl;

  saveToFile(gradeWeight,gradePercent,nameOfGrade,numOfGrades);

return 0;
}


int finalGradeCalculation2(){
  // use ifstream to read file
  // ask user for file name and check to see if file exists
  // input the grade weights from the file
  // ask the user for the percents for each grade weight
  string s;
  ifstream outFile;

  do{
    cout<<"Enter File Name: ";
    cin>>fileName;
    outFile.open(fileName);
    if(!outFile.is_open()){
      cout<<"\n\033[31mError: File '"<<fileName<<"' does not exist. Please try again.\033[0m\n"<<endl;
    }

  }while(!outFile.is_open());


  //Get the numbers from the file
  int t=1;//to make sure that numAmount is accounted for
  
  while(getline(outFile, s)){  
  if(t==1){
    numOfGrades=stoi(s);//allows the number in the string to become equal to numOfGrades(int)
    t++;
  } 
}

  double gradeWeight[numOfGrades+1];
  double gradePercent [numOfGrades+1];
  double firstPartCalculation[numOfGrades+1];
  string nameOfGrade[numOfGrades+1];

  outFile.clear();           //reset the file for the next reading
  outFile.seekg(0, ios::beg);

  t=1;
  int count=1;
  while(getline(outFile, s)){
    if(t!=1&&t<=numOfGrades+1){
      gradeWeight[count]=stod(s);//allows the number in the string to become equal to numOfGrades(double)
      count++;
    }
    t++;
  }

  outFile.clear();           //reset the file for the next reading
  outFile.seekg(0, ios::beg);

  t=1;
  count=1;
  while(getline(outFile,s)){
    if(t>numOfGrades+1){
      nameOfGrade[count]=s;
      count++;
    }
    t++;
  }


  cout<<"\n"<<endl;
  for(int count = 1;count<=numOfGrades;count++){
    do{
    cout<<"Grade: "<<count<<endl;
    cout<<"  Name: "<<nameOfGrade[count]<<endl;
    cout<<"  Weight: "<<gradeWeight[count]<<endl;
    cout<<"  Percent: ";
    cin>> gradePercent[count];

    if(gradePercent[count]<0){
      cout<<"\n\033[31mError: Number entered must be greater than zero. Please try again.\033[0m\n"<<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }else if(!cin){
      cout<<"\n\033[31mError: One of your inputs contain a letter, please try again and only enter positive numbers.\033[0m\n"<<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    }while(gradePercent[count]<0||!cin);
  }

  for (int count = 1;count<=numOfGrades;count++){
    totalWeightCount=totalWeightCount+gradeWeight[count];
  }
  
  for (int count = 1;count<=numOfGrades;count++){
    firstPartCalculation[count]=gradePercent[count]*gradeWeight[count];
    firstPartCalculationFinal=firstPartCalculationFinal+firstPartCalculation[count];
  }
  finalCalculation=(firstPartCalculationFinal)/totalWeightCount;

  letterGradeConverter();
  
  cout<<"\nYour grade in the class is a "<<finalCalculation<<", which is a "<<letterGrade<<endl;

  outFile.close();
  outFile.clear();
  saveToFile(gradeWeight,gradePercent,nameOfGrade,numOfGrades);

  return 0;
}


int fileCreation(){

int numAmount;
double tempNumKeep;



ofstream fileOut;
do{
  cout<<"\nPlease enter the name for your file: ";
  cin>>fileName;

  fileOut.open(fileName);

  if (!fileOut.is_open()){
    cout<<"\n\033[31mError: Could not create the file. Please try again.\033[0m\n";
  }
}while(!fileOut.is_open());



do{
  cout<<"Enter the number of grade weights: ";
  cin>>numAmount;

  if(numAmount<=0){
    cout<<"\n\033[31mError: The number entered must be greater than zero. Please try again.\033[0m\n";
  }
}while(numAmount<=0);


string titles[numAmount+1];
double numsEntered[numAmount+1];
for(int count=1;count<=numAmount;count++){
cout<<"\nGrade "<<count<<" Name: ";
cin.ignore();
getline(cin, titles[count]);
do{
    tempNumKeep=0;
    cout<<"Grade "<<count<<" Weight: ";
    cin>>numsEntered[count];
    tempNumKeep=numsEntered[count];
    if(numsEntered[count]<=0){
    cout<<"\n\033[31mError: Number entered must be greater than 0.\033[0m\n"<<endl;
    }
  }while(numsEntered[count]<=0);
}

fileOut<<numAmount<<endl;//this is so the first number of the file is numAmount
for(int count=1;count<=numAmount;count++){
  fileOut<<numsEntered[count]<<endl;
}

for(int count=1;count<=numAmount;count++){
  fileOut<<titles[count]<<endl;
}

fileOut.close();
return 0;
}


void letterGradeConverter(){
  if (finalCalculation >=90){
    letterGrade = 'A';
  }
  if (finalCalculation >=80 && finalCalculation <90){
    letterGrade = 'B';
  }
  if (finalCalculation >=70 && finalCalculation <80){
    letterGrade = 'C';
  }
  if (finalCalculation >=60 && finalCalculation <70){
    letterGrade = 'D';
  }
  if (finalCalculation <=59){
    letterGrade = 'F';
  }
}



void saveToFile(double gradeWeight[],double gradePercent[],string nameOfGrade[],int numOfGrades){
int saveFileAnswer;

do{
  cout<<"\nWould you like to save this file?\n1. Yes\n2. No"<<endl;
  cout<<"Enter answer: ";
  cin>>saveFileAnswer;

  if(saveFileAnswer<1||saveFileAnswer>2||!cin){
    cout<<"\n\033[31mError: Please only input 1 or 2\033[0m\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}while(saveFileAnswer<1||saveFileAnswer>2||!cin);

if(saveFileAnswer==1){
  string title = "";
  time_t now = time(0);
  char* dt = ctime(&now);

  cout<<"Title: ";
  cin.ignore();
  getline(cin, title);

  ofstream fileOut;

  fileOut.open("finalGradeCalcNotes.txt",ios_base::app);

  fileOut<<"Date: "<<dt<<endl;

  fileOut<<"Title: "<<title<<"\n"<<endl;
  

  for(int count = 1;count<=numOfGrades;count++){
    fileOut<<"Grade "<<count<<": "<<endl;
    fileOut<<"  Name: "<<nameOfGrade[count]<<endl;
    fileOut<<"  Percent: "<<gradePercent[count]<<endl;
    fileOut<<"  Weight: " <<gradeWeight[count]<<endl;
    fileOut<<"\n";
  }

  fileOut<<"\nGrade: "<<finalCalculation<<" ("<<letterGrade<<")"<<endl;

  fileOut<<"\n--------------------------------------------\n"<<endl;
  fileOut.close();

}

}