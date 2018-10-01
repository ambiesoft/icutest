#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unicode/unistr.h>
#include <cstring>

using namespace std;

const wchar_t* gstr = L"あいうえお";
const size_t glenstr = 5;

void CompareShow(const char* testtype, const char* pOrg, const char* result, const char* usecode, size_t unit)
{
	if (memcmp(pOrg, result, glenstr * unit) == 0)
		cout << testtype << ":" << pOrg << " == " << usecode << endl;
	else
		cout << testtype << ":" << pOrg << " != " << usecode << endl;
}
int main(int argc, char* argv[]) {
	
	// "あいうえお"
	// UTF8
	unsigned char utf8[] = { 0xE3,0x81,0x82,0xE3,0x81,0x84,0xE3,0x81,0x86,0xE3,0x81,0x88,0xE3,0x81,0x8A,0x0 };

	// UTF16-LE
	char16_t utf16le[] = { 0x3042,0x3044,0x3046,0x3048,0x304A,0x00 };
	// UTF16-BE
	char16_t utf16be[] = { 0x4230,0x4430,0x4630,0x4830,0x4A30,0x00 };

	// UTF32-LE
	char32_t utf32le[] = { 0x00003042,0x00003044,0x00003046,0x00003048,0x0000304A,0x0000 };
	// UTF32-BE
	char32_t utf32be[] = { 0x42300000,0x44300000,0x46300000,0x48300000,0x4A300000,0x0000 };
	

	const char* ppCode[] = {
		"utf8",
		"utf16-le",
		"utf16-be",
		"utf32-le",
		"utf32-be",
	};

	for (int i = 0; i < sizeof(ppCode) / sizeof(ppCode[0]); ++i)
	{
		icu::UnicodeString src(gstr);

		const char* code = ppCode[i];
		int32_t len = src.extract(0, src.length(), NULL, code);
		char* result = new char[len + 1];
		src.extract(0, src.length(), result, code);

		printf("[%s]\n", result);

		CompareShow("utf8", (const char*)utf8, result, code, sizeof(utf8[0]));
		CompareShow("utf16le",(const char*)utf16le, result, code, sizeof(utf16le[0]));
		CompareShow("utf16be", (const char*)utf16be, result, code, sizeof(utf16be[0]));
		CompareShow("utf32le", (const char*)utf32le, result, code, sizeof(utf32le[0]));
		CompareShow("utf32be", (const char*)utf32be, result, code, sizeof(utf32be[0]));

		// 42 30 44 30 46 30 ...   "utf16-le"
		// 30 42 30 44 30 46 ...   "utf16-be"
		// 42 30 00 00 44 30 00 00 "utf32-le"
		// 00 00 30 42 00 00 30 44 "utf32-be"

		delete[] result;
	}
	return 0;
}
