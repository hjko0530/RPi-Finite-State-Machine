#include<iostream>
using namespace std;
bool isMale(char s)
{
      if(s=='m')return true;
      else return false;
 }
 class person
 {
       string name; char sex;
       bool collocate()
      {
           if(isMale(sex))cout<<"He's a male!";
           else cout<<"She's not!";
       }
 };
 int main(){
    person p;
    p.collate();
 }