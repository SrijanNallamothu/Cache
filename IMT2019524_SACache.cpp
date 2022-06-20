#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>

using namespace std;

int binaryToDecimal(string n); // Binary to Decimal.
string convertToString(char* a, int size);// Char array to std String.
int convert(char num[]); // Hexadecimal to Decimal.


int main(){


  string trace[5] ={ "gcc.trace","gzip.trace","mcf.trace","swim.trace","twolf.trace" } ;

  string Tag[16384][4]; //4 Tags for 4 Sets.
  bool flag[16384][4];  // Valid 
  char add[32];         //32 Bit adrress
  int ind;              //Index in Decimal
  double Hit=0,Miss=0;  //No of Hits/Misses.

  for(size_t i = 0; i < 65536; i++){ // Set all flag to false no Data.
             flag[i][0]=false;
             flag[i][1]=false;
             flag[i][2]=false;
             flag[i][3]=false;
  }

  for(int i=0;i<5;i++){

  ifstream Readfile(trace[i]);

  string a,b,c;

  while (Readfile >> a && Readfile >> b && Readfile >> c){


      strcpy(add,b.substr(2,8).c_str());// b - Input adress in Hexadecimal. 
      int dec = convert(add); // Hexadecimal to Decimal

      char bin[] ="00000000000000000000000000000000";

      //Decimal dec to 32 bit binary.

      for (int pos = 31; pos >= 0; --pos)
      {
         if (dec % 2) 
              bin[pos] = '1';
          dec /= 2;
      }

      string bins = convertToString(bin,32);//char array 32 bit to string.

      int ind = binaryToDecimal(bins.substr(16,14));// 14bit index to Decimal.
      
      bool hit = false;//flag if hit.
      int f=0;

      for(int i=0;i<4;i++){ // Check if any of the present tags matches with 18 bit tag of current adrress.

          if(flag[ind][i]){

              if((bins.substr(0,16)).compare(Tag[ind][i])==0){ // "Hit" If matched any.

                  Hit = Hit + 1;
                  hit= true;
              
            }

          }

      }

      if(!hit){ // If no match "Miss".

          if( flag[ind][0] && flag[ind][1] && flag[ind][2] && flag[ind][3] ){ //If all 4 blocks of the index are filled.

              int i = rand()%4;//Random index 
              Miss = Miss + 1;

              Tag[ind][i] = bins.substr(0,16);//Replace the Tag of Random index by tag of current address. 

          }

          //Else fill in the next empty block.

          else{

              f=0;

              for(int i=0;i<4;i++){

                  if(!flag[ind][i]&&f==0){

                      flag[ind][i] = true;
                      Tag[ind][i] = bins.substr(0,16);// Store the Tag and valid ture.

                      Miss = Miss + 1;
                      f=1;
                                           
                  }

              }

          }

      }

  }

  cout<< trace[i] << endl;
  cout<< endl;
  cout<< "Total Count = "<< Hit+Miss << endl;
  cout<<"Hits = " << Hit<<"  Hit Rate = "<<(Hit/(Hit+Miss))<<endl;  // Hit Rate.
  cout<<"Misses = "<< Miss <<"  Miss Rate = "<<(Miss/(Hit+Miss))<<endl; // Miss Rate.
  cout<< "Hit/Miss = "<< Hit/Miss << endl;
  cout<< endl;

  for(size_t i = 0; i < 65536; i++){ // Set all flag to false no Data.
             flag[i][0]=false;
             flag[i][1]=false;
             flag[i][2]=false;
             flag[i][3]=false;
  }

  Hit =0;
  Miss =0;

  }

  return 0;
}

int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
 
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

string convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

int convert(char num[]) {
   int len = strlen(num);
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='a' && num[i]<='f') {
         temp += (num[i] - 87)*base;
         base = base*16;
      }
   }
   return temp;
}