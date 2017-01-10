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

int Addfile(FILE * contain, FILE * input) // ���� ��Ʈ�Ӹ����ٰ� ������� ��
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
	inputsize = ftell(input);								  // input size �޾ƿ���
	if (inputsize%NT_HEADER.OptionalHeader.FileAlignment != 0)  //file ����� align�� ���� �ʴٸ�
	{
		sizetemp = inputsize%NT_HEADER.OptionalHeader.FileAlignment;
		inputsize += sizetemp;
	}
	writenum = inputsize / NT_HEADER.OptionalHeader.FileAlignment; // 4����Ʈ�� ����Ǿ� �� ��
	if (writenum > 0x11111111)										  // �ִ� ������ �ʰ� ���� üũ
	{
		printf("\n���԰��� �ִ� ���� ������ �ʰ�!\n");
		return 1;
	}
	fseek(contain,sizeof(DOS_HEADER.e_magic), SEEK_SET); // MZ ������ �ٷ� 4����Ʈ�� �Ҵ��Ұ���
	fread(Sig,1,2,contain);
	if (strcmp(Sig,"JH")) // signature JH�� ������ 0���� �ʱ�ȭ ���ϰ�, ������ JH �߰� �� 0���� ���� �ʱ�ȭ
	{
		fwrite(JH, 1, 1, contain);
		fseek(contain, sizeof(DOS_HEADER.e_magic) + 2, SEEK_SET);
		fwrite(0, 32, 1, contain);
	}
	fseek(contain, sizeof(DOS_HEADER.e_magic)+2, SEEK_SET);
	for (writecheck = 0; writecheck < 8; writecheck++)  // ���� ������ ������ � �ִ��� üũ
	{
		if (fread(OffsetCheck, 4, 1, contain))
		{
			break;
		}
	}


	fseek(contain, 0, SEEK_END); // ���� ���ڶ��� filealignment ���缭 ����

}

void Removefile(FILE * contain)
{
	IMAGE_DOS_HEADER DOS_HEADER;
	fseek(contain,sizeof(DOS_HEADER.e_magic), SEEK_SET); // MZ ������ �ٷ� 4����Ʈ�� �Ҵ��Ѱ� ã������
	
}

void encrypt(FILE * contain, DWORD Roundkey, DWORD data) // ��ȣȭ �Լ� -> SHA-256�� ���
{
	SeedRoundKey(Roundkey,data);
	SeedEncrypt(Roundkey, data);

}

void decrypt(FILE * contain, DWORD Roundkey, DWORD data) // ��ȣȭ �Լ�
{
	SeedRoundKey(Roundkey, data);
	SeedDecrypt(Roundkey, data);
	
}

void RemoveOrigin(char * argv[])  // ���� ���� ���� �ϴ� �Լ�
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
