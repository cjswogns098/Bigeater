#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<direct.h>
#include<Windows.h>
#include"SEED_KISA.h"
#pragma warning(disable:4996)


void Copyfile(FILE *origin, FILE *copy);
void encrypt(FILE * contain, DWORD Roundkey, DWORD data);