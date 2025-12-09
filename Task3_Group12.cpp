#include <iostream>
#include <string>
using namespace std;


char letterlist[] = {'A','B','C','D','E','F','G','H','I','L','M','N','O','P','R','S','T','U'};   // Scottish Gaelic Alphabet (assuming input is fully upper-case)	

int letterlistlen = sizeof(letterlist)/sizeof(letterlist[0]);

void cipher(string& text, int len, int a, int b);
void decipher(string& text, int len, int a, int b);

int main(){

	string text;
	int a;
	int b;
	
	cout << "Group 12, Task 3" << endl << "===========================================" << endl;
	cout << "Affine Cipher (Scottish Gaelic Alphabet)" << endl <<"===========================================" << endl;

	cout << "The Affine Cipher algorithim requires ciphering keys a and b" << endl << "Please enter a: ";
	cin >> a;
	cout << "Please enter b: ";
	cin >> b;
	cin.ignore(); // clears leftover /n (newline character) so that getline works properly

	cout << "Enter the text you want to have ciphered: ";
	getline(cin, text);
	cipher(text, text.length(), a, b);
	cout << "The new ciphered text is: " << text << endl;

	decipher(text, text.length(), a, b);
	cout << "The text deciphered is now: " << text << endl;


	return 0;
}

void cipher(string& text, int len, int a, int b){
	
	for (int i = 0;i<len;i++){  //  Iterate through each letter in the input text

		for (int j = 0; j < letterlistlen ;j++){ //   Search for each letter in the letter list array

			if (text[i]==letterlist[j]) {   // Letter identified
	
			text[i] =letterlist[((a*j) + b) % letterlistlen];    // Affine cipher, a*x + b , mod 18 as array indexes for letterlist ranges from 0 to 17
			break; // Letter already identified, no need to search for it again
			}
		}
	}
}


void decipher(string& text, int len, int a, int b){

	int modinverse;

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

