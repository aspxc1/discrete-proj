#include <iostream>
#include <string>
using namespace std;


char letterlist[] = {'A','B','C','D','E','F','G','H','I','L','M','N','O','P','R','S','T','U'};   // Scottish Gaelic Alphabet (Note: Lowercase input is converted into uppercase)	
int letterlistlen = sizeof(letterlist)/sizeof(letterlist[0]);  // Alphabet length 

int gcd(int a, int b);
void cipher(string& text, int len, int a, int b);                           // Function prototypes
void decipher(string& text, int len, int a, int b);
void upperletter(char& letter);

int main(){

	string text;
	int a;
	int b;
	bool endloop = false;
	char opt;

	while (not endloop){

	cout << "Group 12, Task 3" << endl << "===========================================" << endl;
	cout << "Affine Cipher (Scottish Gaelic Alphabet)" << endl <<"===========================================" << endl;

	cout << "The Affine Cipher algorithim requires ciphering keys a and b" << endl << "Please enter a: ";
	cin >> a;
	while (gcd(letterlistlen, a) != 1){ // check if n and a are coprime so that decryption is possible and encryption is 1 to 1

		cout << "Invalid key, a must be coprime with n (18), please try again." << endl << "Please enter a: ";
		cin >> a;
	}
	cout << "Please enter b: ";
	cin >> b;

	
	while (true){

	
	cout << "Would you like to cipher or decipher? (c/d): ";
	cin >> opt;
		if (opt != 'c' && opt != 'd'){
			cout << "Invalid entry, try again" << endl;
		}
		else
			break;
	}

	cin.ignore(); // clears leftover /n (newline character) in input buffer so that it doesnt get taken automatically so that getline works properly
	cout << "Enter the text you want to have ciphered/deciphered: ";
	getline(cin, text);

	if (opt == 'c'){

	cipher(text, text.length(), a, b);
	cout << "The new ciphered text is: " << text << endl;
	}

	if (opt == 'd'){

	decipher(text, text.length(), a, b);
	cout << "The text deciphered is now: " << text << endl;
	}

	while (true){

		cout << "Would you like to try again? (y/n): ";
		cin >> opt;

		if (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N')
			cout << "Invalid entry, please try again." << endl;

		if (opt == 'y' || opt == 'Y')
			break;                  // Break out of minor loop without breaking out of major loop to continue doing cipher/decipher operations when user enter y or Y
		else{
			endloop = true; // End major loop which includes cipher/decipher option if user enters n or N
			break;	
		}
	}
}
	return 0;
}

void cipher(string& text, int len, int a, int b){      // Text is passed into function by reference in order to modify the original
	
	for (int i = 0;i<len;i++){  //  Iterate through each letter in the input text

		if ( text[i]>='a' && text[i]<='u'){   // Check if letter is lowercase

		upperletter(text[i]); // Turn lowercase letter into uppercase
		}

		for (int j = 0; j < letterlistlen ;j++){ //   Search for each letter in the letter list array
			
			if (text[i]==letterlist[j]) {   // Letter identified
	
			text[i] =letterlist[((a*j) + b) % letterlistlen];    // Affine cipher, a*x + b , mod 18 as array indexes for letterlist ranges from 0 to 17
			break; // Letter already identified, no need to search for it again
			}
		}
	}
}


void decipher(string& text, int len, int a, int b){   // Text is passed into function by reference in order to modify the original

	int modinverse; // Modular inverse used for deciphering

	for (int i = 1; i < letterlistlen; i++){

		if ( (i*a) % letterlistlen == 1 ){
			modinverse = i;    // modular inverse identified
			break;             // modular inverse is unique within the range, no need to keep iterating
		}
	}


	for (int i = 0;i<len;i++){   // Iterate through each letter in the input text

		for (int j = 0; j < letterlistlen ;j++){    // Search for each letter in the letter list array

			if ( text[i]==letterlist[j] ){      // Letter identified

				text[i] = letterlist[ ( ((j-b+letterlistlen)*modinverse ) % letterlistlen) ];    // Affine decryption, +letterlistlen to avoid negative indexing
				break;    //Letter to be deciphered identified, no need to keep going
			}


		}
	}

}

int gcd(int a, int b){     // Functin to find gcd of 2 numbers, used to check if key and alphabet length are coprime in order for decryption to be possible
	
	if ( b > a ){ // switch numbers if second is larger than first

		int temp1;
		
		temp1 = b;

		b = a;

		a = temp1;
	}

	int temp = b;

	b = a % b;
	a = temp;

	if (b == 0)
		return temp;
	else
		return gcd(a, b);  // Repeat recursively until value is reached
}


void upperletter(char& letter){

		letter-=('a'-'A');
}
