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

		if (original_exe = fopen(argv[0], "rb"))		    // �ڱ� �ڽ� �о�ͼ� ī�� ��
		{
			if (copy_exe = fopen(newpathbuff, "wb+"))
			{
				printf("Menu\n1. ���� ����\n2. ���� ����\n���� : ");
				menu = getchar();				     // �޴��� �Է�
				strcpy(newpathbuff, argv[0]);
				strcat(newpathbuff, newfilename);
				printf("%s", newpathbuff);

				Copyfile(original_exe, copy_exe);
				//printf("���� ������ ��� �� �̸��� �Է����ּ���. : ");
				//scanf("%s",inputfilepath);
				fclose(original_exe);
				*inputfilepath = "C:\\TEST.exe";

				if (menu == 1) // ���� �ֱ�
				{
					if (input_exe=fopen(inputfilepath, "rwb")) //�Է� ���� �޾ƿ�
					{
						if (Addfile(copy_exe, input_exe))
						{
							printf("���� �߰� ����!!");
						}
						fclose(copy_exe);
						fclose(input_exe);
						RemoveOrigin(argv); // ���� ����
					}
					else
					{
						printf("�Է� ������ ���µ���?!");
					}
				}
				else if (menu == 2) // ���� ����
				{
					Removefile(copy_exe);
					fclose(copy_exe);
					RemoveOrigin(argv); // ���� ����
				}
				else
				{
					printf("�߸��� �޴� ���Դϴ�.");
				}

			}
			else
			{
				printf("���� ������ �ȵ˴ϴٸ�?!?!?");
			}
		}
		else								// �ȵ� ��� ����ó��
		{
			printf("������ ���� ����?!");
			break;
		}
	}
	
}
