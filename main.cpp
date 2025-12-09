#include <iostream>
using namespace std;


char letterlist[] = {'A','B','C','D','E','F','G','H','I','L','M','N','O','P','R','S','T','U'};   // Gaelic Alphabet (assuming input is fully upper-case)	

int letterlistlen = sizeof(letterlist)/sizeof(letterlist[0]);

void cipher(string& text, int len, int a, int b);
void decipher(string& text, int len, int a, int b);

int main(){

	string text;
	int a;
	int b;

	cout << "The Affine Cipher algorithim requires ciphering keys a and b" << endl << "Please enter a: ";
	cin >> a;
	cout << "Please enter b: ";
	cin >> b;

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

	for (int i = 0; i < letterlistlen; i++){

		if ( (i*a) % letterlistlen == 1 ){
			modinverse = i;    // modular inverse identified
			break;             // modular inverse is unique within the range, no need to keep iterating
		}
	}


	for (int i = 0;i<len;i++){   // Iterate through each letter in the input text

		for (int j = 0; j < letterlistlen ;j++){    // Search for each letter in the letter list array

			if ( text[i]==letterlist[j] ){      // Letter identified

				text[i] = letterlist[ ( ((j-b)*modinverse ) % letterlistlen) ];    // Affine decryption formula once letter is identified
				break;    //Letter to be deciphered identified, no need to keep going
			}


		}
	}

}

