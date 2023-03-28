#include<iostream>
#include<string>
#include <sstream>
#include<stack>
using namespace std;
string KEYS[15];
string ENCRYPTION_FIXED_MAT[4][4] = {
				{"02","03","01","01"},
				{"01","02","03","01"},
				{"01","01","02","03"},
				{"03","01","01","02"} };

string DECRYPTION_FIXED_MAT[4][4] = {
				{"0e","0b","0d","09"},
				{"09","0e","0b","0d"},
				{"0d","09","0e","0b"},
				{"0b","0d","09","0e"} };
string S_BOX[16][16] =
{
 "63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76",
 "ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0",
 "b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15",
 "04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75",
 "09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84",
 "53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf",
 "d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8",
 "51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2",
 "cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73",
 "60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db",
 "e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79",
 "e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08",
 "ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a",
 "70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e",
 "e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df",
 "8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54","bb","16"
};
string  INV_SBOX[16][16] = {
		"52","09","6a","d5","30","36","a5","38","bf","40","a3","9e","81","f3","d7","fb",
		"7c","e3","39","82","9b","2f","ff","87","34","8e","43","44","c4","de","e9","cb",
		"54","7b","94","32","a6","c2","23","3d","ee","4c","95","0b","42","fa","c3","4e",
		"08","2e","a1","66","28","d9","24","b2","76","5b","a2","49","6d","8b","d1","25",
		"72","f8","f6","64","86","68","98","16","d4","a4","5c","cc","5d","65","b6","92",
		"6c","70","48","50","fd","ed","b9","da","5e","15","46","57","a7","8d","9d","84",
		"90","d8","ab","00","8c","bc","d3","0a","f7","e4","58","05","b8","b3","45","06",
		"d0","2c","1e","8f","ca","3f","0f","02","c1","af","bd","03","01","13","8a","6b",
		"3a","91","11","41","4f","67","dc","ea","97","f2","cf","ce","f0","b4","e6","73",
		"96","ac","74","22","e7","ad","35","85","e2","f9","37","e8","1c","75","df","6e",
		"47","f1","1a","71","1d","29","c5","89","6f","b7","62","0e","aa","18","be","1b",
		"fc","56","3e","4b","c6","d2","79","20","9a","db","c0","fe","78","cd","5a","f4",
		"1f","dd","a8","33","88","07","c7","31","b1","12","10","59","27","80","ec","5f",
		"60","51","7f","a9","19","b5","4a","0d","2d","e5","7a","9f","93","c9","9c","ef",
		"a0","e0","3b","4d","ae","2a","f5","b0","c8","eb","bb","3c","83","53","99","61",
		"17","2b","04","7e","ba","77","d6","26","e1","69","14","63","55","21","0c","7d" };
int chartoint(char c)
{
	if (c >= 'a' && c <= 'f')
	{
		return c - 87;
	}	
	if (c >= 'A' && c <= 'F')
	{
		return c - 55;
	}
	if (c >= '0' && c <= '9')
	{
		return c - 48;
	}

}
string TEXT_TO_HEX(string str)
{
	string hextext = "";
	stringstream ss;
	for (const auto& item : str)
	{
		ss << hex << int(item);
	}
	hextext = ss.str();
	return hextext;
}
long strTOHex(string str)
{
	int hexNumber;
	sscanf_s(str.c_str(), "%x", &hexNumber);
	return hexNumber;
}
string Sub_from_Sbox(string s)
{
	string temp;
	for (int i = 0; s[i]; i += 2)
	{
		temp += S_BOX[chartoint(s[i])][chartoint(s[i + 1])];
	}
	return temp;
}
string Sub_from_Inv_Sbox(string s)
{
	string temp;
	for (int i = 0; s[i]; i += 2)
	{
		temp += INV_SBOX[chartoint(s[i])][chartoint(s[i + 1])];
	}
	return temp;
}
string gw(string w)
{
	stringstream stream;
	static long ROUND_CONS = 16777216;

	rotate(w.begin(), w.begin() + 2, w.end());
	w = Sub_from_Sbox(w);
	int hexNumber;
	sscanf_s(w.c_str(), "%x", &hexNumber);
	hexNumber = (ROUND_CONS ^ hexNumber);
	ROUND_CONS = ROUND_CONS << 1;

	stream << hex << hexNumber;

	if (stream.str().length() < 8)
		stream.str() = "0" + stream.str();
	return stream.str();
}
void LeftShiftRow(string mat[], int count)
{
	stack <string> st;
	for (int i = 0; i < count; i++)
	{
		st.push(mat[i]);
	}
	for (int i = 0; i < 4 - count; i++)
	{
		mat[i] = mat[i + count];
	}
	for (int i = 3; !st.empty(); i--)
	{
		mat[i] = st.top();
		st.pop();
	}
}
void LeftShift(string** mat)
{
	for (int i = 1; i < 4; i++)
	{
		LeftShiftRow(mat[i], i);
	}
}
void RightShiftD(string** mat)
{
	for (int i = 1; i < 4; i++)
	{
		LeftShiftRow(mat[i], 4 - i);
	}
}

void GET_KEYS(string key)
{
	KEYS[0] = key.substr(0, 32);
	KEYS[1] = key.substr(32, 32);
	cout << KEYS[0] << endl;
	cout << KEYS[1] << endl;
	string temp = "";
	for (int i = 2; i < 15; i++)
	{
		int j = 0;
		if (!(i % 2))
		{
			temp = gw(KEYS[i - 1].substr(24, 8));
			stringstream ss;
			ss << hex << (strTOHex(KEYS[i - 2].substr(0, 8)) ^ strTOHex(temp));
			temp = ss.str();
			if (temp.length() < 8)
				temp = '0' + temp;
			KEYS[i] += temp;
			j++;
		}
		else
		{
			temp = Sub_from_Sbox(temp);
		}
		for (; j < 4; j++)
		{
			stringstream ss;
			ss << hex << (strTOHex(KEYS[i - 2].substr(j * 8, 8)) ^ strTOHex(temp));
			temp = ss.str();
			if (temp.length() < 8)
			{
				temp = '0' + temp;
			}
			KEYS[i] += temp;
		}
		cout << KEYS[i] << endl;
	}
}
template <typename T>
T** New2D(int r, int c, T obj1)
{
	T** obj = new T * [r];
	for (int i = 0; i < r; i++)
	{
		obj[i] = new T[c];
		for (int j = 0; j < c; j++)
		{
			obj[i][j] = obj1;
		}
	}
	return obj;
}
string** stateMatrix(string key)
{
	string** temp = New2D<string>(4, 4, "");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			temp[j / 2][i] += key[i * 8 + j];
		}
	}
	return temp;
}
string** AddroundKey(string plain, string key)
{
	string** k = stateMatrix(key);
	string** p = stateMatrix(plain);
	string** res = New2D<string>(4, 4, "");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			stringstream ss;
			ss << hex << (strTOHex(k[i][j]) ^ strTOHex(p[i][j]));
			string temp = ss.str();
			if (temp.length() < 2)
			{
				temp = '0' + temp;
			}
			res[i][j] = temp;
		}
	}
	return res;
}
void substituteBytes(string** Str)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Str[i][j] = Sub_from_Sbox(Str[i][j]);

		}
	}
}


void substituteBytesD(string** Str)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Str[i][j] = Sub_from_Inv_Sbox(Str[i][j]);
		}
	}
}

string galois(int a, int b)
{
	int p = 0;
	while (b) 
	{
		if (b & 1) 
		{
			p ^= a;
		}

		a <<= 1;
		if (a & 0x100)
		{
			a ^= 0x1b;
		}
		b >>= 1;
	}
	p = p & 0xff;
	std::ostringstream sso;
	sso << std::hex << p;
	return sso.str();
}
string** MixColumns(string** str2)
{
	string  t1;
	int tt1, tt2;
	string** res = New2D<string>(4, 4, "00");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				t1 = "";
				tt1 = (16 * chartoint(ENCRYPTION_FIXED_MAT[i][k][0])) + chartoint(ENCRYPTION_FIXED_MAT[i][k][1]);
				tt2 = (16 * chartoint(str2[k][j][0])) + chartoint(str2[k][j][1]);
				t1 = galois(tt1, tt2);
				stringstream ss;
				ss << hex << (strTOHex(res[i][j]) ^ strTOHex(t1));
				res[i][j] = ss.str();
				while (res[i][j].size() < 2)
					res[i][j] = "0" + res[i][j];
			}
	return res;
}
string** MixColumnsD(string** str2)
{
	string  t1;
	int tt1, tt2;
	string** res = New2D<string>(4, 4, "00");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				t1 = "";
				tt1 = (16 * chartoint(DECRYPTION_FIXED_MAT[i][k][0])) + chartoint(DECRYPTION_FIXED_MAT[i][k][1]);
				tt2 = (16 * chartoint(str2[k][j][0])) + chartoint(str2[k][j][1]);
				t1 = galois(tt1, tt2);
				stringstream ss;
				ss << hex << (strTOHex(res[i][j]) ^ strTOHex(t1));
				res[i][j] = ss.str();
				while (res[i][j].size() < 2)
					res[i][j] = "0" + res[i][j];
			}
	return res;
}
void printmatrix(string** m)
{
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << m[i][j] << " ";
		cout << endl;
	}

}
string convert2Dtostr(string** ptr)
{
	string temp = "";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp += ptr[j][i];
		}
	}
	return temp;
}
string hextoascii(string hex)
{
	string ascii = "";
	for (size_t i = 0; i < hex.length(); i += 2)
	{
		string part = hex.substr(i, 2);
		char ch = stoul(part, nullptr, 16);
		ascii += ch;
	}
	return ascii;
}

int main()
{
	string plaintext;
	string key;
	cout << "\n-------------->Please Enter the  16 charatcers to Encrypt using AES \n";
	getline(cin, plaintext);
	plaintext = plaintext.substr(0, 16);
	cout << "\nPlease Enter the Key 32 charcacters: ";
	getline(cin, key);
	
	key = key.substr(0, 32);
	key = TEXT_TO_HEX(key);
	plaintext = TEXT_TO_HEX(plaintext);
	 //plaintext = "00112233445566778899aabbccddeeff";
	// key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";

	cout << endl << "Generated Keys for 14 rounds: " << endl;
	GET_KEYS(key);
	string** current;
	cout << endl<<"Key Whitening" ;
	current = AddroundKey(plaintext, KEYS[0]);  //key whitening
	printmatrix(current);
	cout << endl;
	for (int i = 1; i < 15; i++)
	{
		cout << "Byte substituted";
		substituteBytes(current);
		printmatrix(current);
		cout << endl;
		cout << "Left Shift" ;
		LeftShift(current);
		printmatrix(current);
		cout << endl;
		if (i < 14)
		{
			cout << "Mix Columns" ;
			current = MixColumns(current);
			printmatrix(current);
			cout << endl;
		}
		cout << "Adding Round Key" ;
		current = AddroundKey(convert2Dtostr(current), KEYS[i]);
		printmatrix(current);
		cout << endl;
	}
	cout << endl<<endl<<"DECRYPTION" << endl; 
	cout << "#######################################################################" << endl;

	string ciphertext;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ciphertext += current[j][i];

	cout << "Adding Round Key" ;
	current = AddroundKey(ciphertext, KEYS[14]);
	printmatrix(current);
	cout << endl;

	for (int i = 13; i >= 0; i--)
	{
		cout << "Right Shift";
		RightShiftD(current);
		printmatrix(current);
		cout << endl;
		cout << "Substitute Bytes" ;
		substituteBytesD(current);
		printmatrix(current);
		cout << endl;
		cout << "Adding Round Key";
		current = AddroundKey(convert2Dtostr(current), KEYS[i]);
		printmatrix(current);
		cout << endl;
		cout << "Mix Colums";
		if (i != 0)
			current = MixColumnsD(current);
		printmatrix(current);
		cout << endl;
	}
	cout << endl<< "----Original Plain text---- " << endl;
	string plaintextNEWHEX = (convert2Dtostr(current));
	cout << hextoascii(plaintextNEWHEX);
	cout << endl<<endl; 













}
/*
Key 0 : 000102030405060708090a0b0c0d0e0f
Key 1 : 101112131415161718191a1b1c1d1e1f
Key 2 : a573c29fa176c498a97fce93a572c09c
Key 3 : 1651a8cd0244beda1a5da4c10640bade
Key 4 : ae87dff00ff11b68a68ed5fb03fc1567
Key 5 : 6de1f1486fa54f9275f8eb5373b8518d
Key 6 : c656827fc9a799176f294cec6cd5598b
Key 7 : 3de23a75524775e727bf9eb45407cf39
Key 8 : 0bdc905fc27b0948ad5245a4c1871c2f
Key 9 : 45f5a66017b2d387300d4d33640a820a
Key 10 : 7ccff71cbeb4fe5413e6bbf0d261a7df
Key 11 : f01afafee7a82979d7a5644ab3afe640
Key 12 : 2541fe719bf500258813bbd55a721c0a
Key 13 : 4e5a6699a9f24fe07e572baacdf8cdea
Key 14 : 24fc79ccbf0979e9371ac23c6d68de36*/