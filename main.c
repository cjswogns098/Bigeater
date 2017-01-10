#include"main.h"

void main(int argc,char * argv[])
{
	int menu = 0;
	char newfilename[2] = "1 ";
	char newpathbuff[_MAX_PATH];
	char inputfilepath[_MAX_PATH];
	FILE * original_exe;
	FILE * copy_exe;
	FILE * input_exe;

	printf("Project Gluttony ver 1.0\nmade by WJH\n\n");
	while (1)
	{

		if (original_exe = fopen(argv[0], "rb"))		    // 자기 자신 읽어와서 카피 뜸
		{
			if (copy_exe = fopen(newpathbuff, "wb+"))
			{
				printf("Menu\n1. 파일 수납\n2. 파일 반출\n선택 : ");
				menu = getchar();				     // 메뉴를 입력
				strcpy(newpathbuff, argv[0]);
				strcat(newpathbuff, newfilename);
				printf("%s", newpathbuff);

				Copyfile(original_exe, copy_exe);
				//printf("넣을 파일의 경로 및 이름을 입력해주세요. : ");
				//scanf("%s",inputfilepath);
				fclose(original_exe);
				*inputfilepath = "C:\\TEST.exe";

				if (menu == 1) // 파일 넣기
				{
					if (input_exe=fopen(inputfilepath, "rwb")) //입력 파일 받아옴
					{
						if (Addfile(copy_exe, input_exe))
						{
							printf("파일 추가 실패!!");
						}
						fclose(copy_exe);
						fclose(input_exe);
						RemoveOrigin(argv); // 원본 삭제
					}
					else
					{
						printf("입력 파일이 없는뎁쇼?!");
					}
				}
				else if (menu == 2) // 파일 빼기
				{
					Removefile(copy_exe);
					fclose(copy_exe);
					RemoveOrigin(argv); // 원본 삭제
				}
				else
				{
					printf("잘못된 메뉴 값입니다.");
				}

			}
			else
			{
				printf("파일 생성이 안됩니다만?!?!?");
			}
		}
		else								// 안될 경우 에러처리
		{
			printf("파일이 없는 뎁쇼?!");
			break;
		}
	}
	
}
