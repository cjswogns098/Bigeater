#include"main.h"

IMAGE_DOS_HEADER GetDosHeader(FILE* fp)
{
	IMAGE_DOS_HEADER DosHeader;
	fseek(fp, 0, SEEK_SET);
	fread(&DosHeader, 1, sizeof(IMAGE_DOS_HEADER), fp);

	return DosHeader;
}

IMAGE_NT_HEADERS GetNTHeader(FILE* fp)
{
	IMAGE_DOS_HEADER DosHeader;
	DosHeader = GetDosHeader(fp);

	IMAGE_NT_HEADERS NTHeader;
	fseek(fp, DosHeader.e_lfanew, SEEK_SET);
	fread(&NTHeader, 1, sizeof(IMAGE_NT_HEADERS), fp);

	return NTHeader;
}


void Copyfile(FILE *origin, FILE *copy)
{
	char buffer[100];
	int read, write;
	while (!feof(origin))
	{
		if ((read = fread(buffer, 1, 100, origin)) != 100)
		{
			if (ferror(origin) != 0)
			{
				printf("copy file ERROR\n");
				exit(1);
			}
		}
		if ((write = fwrite(buffer, 1, read, copy)) != read)
		{
			printf("copy file ERROR\n");
			exit(1);
		}
	}
}

int Addfile(FILE * contain, FILE * input) // 파일 끄트머리에다가 써버리면 됨
{
	int inputsize = 0;
	int writenum = 0;
	int sizetemp = 0;
	int writecheck = 0;
	char Sig[3];
	char JH[3] = "JH";
	DWORD OffsetCheck;
	DWORD checktemp=0;
	IMAGE_DOS_HEADER DOS_HEADER = GetDosHeader(contain);
	IMAGE_NT_HEADERS NT_HEADER = GetNTHeader(contain);
	fseek(input, 0, SEEK_END);
	inputsize = ftell(input);								  // input size 받아오기
	if (inputsize%NT_HEADER.OptionalHeader.FileAlignment != 0)  //file 사이즈가 align에 맞지 않다면
	{
		sizetemp = inputsize%NT_HEADER.OptionalHeader.FileAlignment;
		inputsize += sizetemp;
	}
	writenum = inputsize / NT_HEADER.OptionalHeader.FileAlignment; // 4바이트에 기재되야 할 것
	if (writenum > 0x11111111)										  // 최대 사이즈 초과 여부 체크
	{
		printf("\n삽입가능 최대 파일 사이즈 초과!\n");
		return 1;
	}
	fseek(contain,sizeof(DOS_HEADER.e_magic), SEEK_SET); // MZ 다음에 바로 4바이트씩 할당할거임
	fread(Sig,1,2,contain);
	if (strcmp(Sig,"JH")) // signature JH가 있으면 0으로 초기화 안하고, 없으면 JH 추가 및 0으로 슬럿 초기화
	{
		fwrite(JH, 1, 1, contain);
		fseek(contain, sizeof(DOS_HEADER.e_magic) + 2, SEEK_SET);
		fwrite(0, 32, 1, contain);
	}
	fseek(contain, sizeof(DOS_HEADER.e_magic)+2, SEEK_SET);
	for (writecheck = 0; writecheck < 8; writecheck++)  // 현재 슬럿에 파일이 몇개 있는지 체크
	{
		if (fread(OffsetCheck, 4, 1, contain))
		{
			break;
		}
	}


	fseek(contain, 0, SEEK_END); // 파일 끝자락에 filealignment 맞춰서 삽입

}

void Removefile(FILE * contain)
{
	IMAGE_DOS_HEADER DOS_HEADER;
	fseek(contain,sizeof(DOS_HEADER.e_magic), SEEK_SET); // MZ 다음에 바로 4바이트씩 할당한거 찾을거임
	
}

void encrypt(FILE * contain, DWORD Roundkey, DWORD data) // 암호화 함수 -> SHA-256을 사용
{
	SeedRoundKey(Roundkey,data);
	SeedEncrypt(Roundkey, data);

}

void decrypt(FILE * contain, DWORD Roundkey, DWORD data) // 복호화 함수
{
	SeedRoundKey(Roundkey, data);
	SeedDecrypt(Roundkey, data);
	
}

void RemoveOrigin(char * argv[])  // 원본 파일 삭제 하는 함수
{
	FILE *fp;

	fp = fopen("deleteme.bat", "wt");

	fprintf(fp, "\
:AAA\ndel \"%s\"\n\
IF exist \"%s\" GOTO AAA\n\
:BBB\n\
del deleteme.bat\n\
IF exist deleteme.bat GOTO BBB\n", argv[0], argv[0]);

	fclose(fp);
	ShellExecute(NULL, "open", "deleteme.bat", NULL, NULL, SW_HIDE);
}
