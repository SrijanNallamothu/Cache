#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>

using namespace std;

int binaryToDecimal(string n); // Binary to Decimal.
string convertToString(char* a, int size);// Char array to std String.
int convert(char num[]); // Hexadecimal To Decimal Function.

int main(){

	  string Tag[65536]; // Tag
	  bool flag[65536]; // Valid
    char add[32];
    double Hit=0,Miss=0; // No of Hits,Misses.

    for(size_t i = 0; i < 65536; i++){ // flag = true if filled.
             flag[i]=false;
    }

	  int ind;
    string a,b,c;

    string trace[5] ={ "gcc.trace","gzip.trace","mcf.trace","swim.trace","twolf.trace" } ;

    for(int i=0;i<5;i++){

    ifstream Readfile(trace[i]);

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

        ind = binaryToDecimal(bins.substr(14,16));// 16 bit index to Decimal.

        if(flag[ind]){ // If Data is filled.

        //Compare the Tag present with tag of current address.


            //If they are Equal "Hit" can use the data.

            if(Tag[ind].compare(bins.substr(0,14))==0){ 
                Hit = Hit + 1;
            }

            //If they are not "Miss" replace with tag of current adress.  

            else{ 
                Tag[ind] = bins.substr(0,14);
                Miss = Miss + 1;
            }

        }
        else{ // No Data
    
            flag[ind]=true; //Valid true
            Tag[ind]=bins.substr(0,14);//Store the Tag.
            Miss = Miss+1;
        }

    }


    cout<< trace[i] << endl;
    cout<< endl;
    cout<< "Total Count = "<< Hit+Miss << endl;
    cout<<"Hits = " << Hit<<"  Hit Rate = "<<(Hit/(Hit+Miss))<<endl;  // Hit Rate.
    cout<<"Misses = "<< Miss <<"  Miss Rate = "<<(Miss/(Hit+Miss))<<endl; // Miss Rate.
    cout<< "Hit/Miss = "<< Hit/Miss << endl;
    cout<< endl;


    for(size_t i = 0; i < 65536; i++){ // flag = true if filled.
             flag[i]=false;
    }
    
    Hit =0;
    Miss =0;

  }

	return 0;
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