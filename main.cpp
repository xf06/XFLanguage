#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <sstream>
using namespace std; 


float addition(float v1, float v2){

return (v1+v2);

}

float substraction(float v1, float v2){

return (v1-v2);

}


float multiplication(float v1, float v2){

return (v1*v2);

}

float division (float v1, float v2){

return (v1/v2);

}

float performCalculation(float v1, string c, float v2) {
          
          
          if (c=="+")
            return(addition(v1,v2));
             
          else if (c=="-")
            return(substraction(v1,v2));
             
          else if (c=="*")
            return(multiplication(v1,v2));
      
          else if (c=="/")
            return(division(v1,v2));
 
          else 
            return 0;          
}



int main() {

string input;  
cout << "Enter Formula: " << endl;
//cin.ignore();
cin >> input;

int a = input.find("(");
int b = input.find(")");


string s1 = input.substr((a+1),1);
string s2 = input.substr((a+3),1);
string sc = input.substr((a+2),1);
string sc2 = input.substr((a-1),1);
string sc3 = input.substr((b+1),1);
string s3 = input.substr((a-2),1);
string s4 = input.substr((b+2),1);
float v1 = atof(s1.c_str());
float v2 = atof(s2.c_str());
float v3 = atof(s3.c_str());
float v4 = atof(s4.c_str());

float result1= performCalculation(v1,sc,v2);

if ((sc3 =="*") || (sc3=="/")){
  float result2=performCalculation(result1,sc3,v4);
  float result3=performCalculation(v3,sc2,result2);
  cout << input << "=" << result3 << endl;
  
}   
    
else {
  float result2 =performCalculation(v3,sc2,result1);
  float result3 = performCalculation(result2,sc3,v4);
  cout << input << "=" << result3 << endl;
}
    

   
   
return 0 ;
}
  
 



