#include "stdafx.h"
#include <iostream>
using namespace std;

extern "C" void Setkey(uint16_t *, uint16_t *);
extern "C" void Setkey_128(uint32_t *, uint32_t *);
extern "C" void Setkey_256(uint32_t *, uint32_t *);

extern "C" void Encryption(uint16_t *, uint16_t *, uint16_t *);
extern "C" void Encryption_128(uint32_t *, uint32_t *, uint32_t *);
extern "C" void Encryption_256(uint32_t *, uint32_t *, uint32_t *);

extern "C" void Decryption(uint16_t *, uint16_t *, uint16_t *);
extern "C" void Decryption_128(uint32_t *, uint32_t *, uint32_t *);
extern "C" void Decryption_256(uint32_t *, uint32_t *, uint32_t *);

//인자로 들어온 텍스트를 출력해주는 함수
void print_bytes(char *s, uint16_t *p, int len) {
	int i;
	printf("%s : ", s);
	for (i = 0; i<len; i++) {
		printf("%04x ", p[i]);
	}
	putchar('\n');
}

void print_bytes_32(char *s, uint32_t *p, int len) {
	int i;
	printf("%s : ", s);
	for (i = 0; i<len; i++) {
		printf("%08x ", p[i]);
	}
	putchar('\n');
}


int main()
{
	uint16_t key[8] = { 0x0100, 0x0302, 0x0504, 0x0706, 0x0908, 0x0b0a, 0x0d0c, 0x0f0e };
	uint16_t RK[16];
	uint16_t PT[4] = { 0x1100, 0x3322, 0x5544, 0x7766 };
	uint16_t RCT[4];

	uint32_t key_128[4] = { 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c };
	uint32_t key_256[8] = { 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0xf3f2f1f0, 0xf7f6f5f4, 0xfbfaf9f8, 0xfffefdfc };

	uint16_t RK_64[16];
	uint32_t RK_128[8];
	uint32_t RK_256[16];

	uint16_t CT_64[4];
	uint32_t CT_128[4];
	uint32_t CT_256[4];

	uint16_t PT_64[4] = { 0x1100, 0x3322, 0x5544, 0x7766 };
	uint32_t PT_128[4] = { 0x33221100, 0x77665544, 0xbbaa9988, 0xffeeddcc };

	uint16_t RCT_64[4];
	uint32_t RCT_128[4];
	uint32_t RCT_256[4];

	uint16_t DCT_64[4] = { 0x453c, 0x63bc, 0xdcfa, 0xbf4e };
	uint32_t DCT_128[4] = { 0xc3746034, 0xb55700c5, 0x8d64ec32, 0x489332f7 };
	uint32_t DCT_256[4] = { 0xa899c8a0, 0xc929d55c, 0xab670d38, 0x0c4f7ac8 };


	cout << "CHAM-64/128" << endl;
	Setkey(key, RK_64);
	Encryption(PT_64, CT_64, RK_64);
	Decryption(DCT_64, RCT_64, RK_64);

	print_bytes("PT", PT_64, 4);
	print_bytes("CT", CT_64, 4);
	print_bytes("DT", RCT_64, 4);
	cout << endl;

	cout << "CHAM-128/128" << endl;

	Setkey_128(key_128, RK_128);
	Encryption_128(PT_128, CT_128, RK_128);
	Decryption_128(DCT_128, RCT_128, RK_128);

	print_bytes_32("PT", PT_128, 4);
	print_bytes_32("CT", CT_128, 4);
	print_bytes_32("DT", RCT_128, 4);
	cout << endl;

	cout << "CHAM-128/256" << endl;

	Setkey_256(key_256, RK_256);
	Encryption_256(PT_128, CT_256, RK_256);
	Decryption_256(DCT_256, RCT_256, RK_256);

	print_bytes_32("PT", PT_128, 4);
	print_bytes_32("CT", CT_256, 4);
	print_bytes_32("DT", RCT_256, 4);

	cout << endl;

	return 0;
} 