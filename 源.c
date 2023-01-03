#include <stdio.h>
#include <string.h>

typedef struct Emp
{
	int EmpId;//员工编号
	char EmpName[20]; //姓名
	char Sex; //性别
	int Age; //年龄
	int WorkYears;//工龄
	char Position[20];//职务
	char Department[20]; //部门
	char Address[30]; //住址
}Emp;

struct
{
	Emp employee[100];
	int usedFlag[100]; // 这个标志为用于标志相同索引的 employee数组中的变量 是否被使用。 1 --- 使用了， 0 --- 未使用
	int sortByWorkYears[100];
}EmpArray;

void sortByWorkYears()
{
	int i;
	int j;
	int v;

	for (i = 0; i < 100; i++)
	{
		EmpArray.sortByWorkYears[i] = i;
	}

	for (i = 0; i < 99; i++)
	{
		for (j = i + 1; j < 100; j++)
		{
			if (EmpArray.employee[i].WorkYears < EmpArray.employee[j].WorkYears)
			{
				v = EmpArray.sortByWorkYears[i];
				EmpArray.sortByWorkYears[i] = EmpArray.sortByWorkYears[j];
				EmpArray.sortByWorkYears[j] = v;
			}
		}
	}

}

void menu()
{
	printf("\n----------------企业员工信息管理程序-------------\n");
	printf("                                        \n");
	printf("   请选择操作的种类:\n");
	printf("   I|i ---- 录入：完成职工信息的输入\n");
	printf("   D|d ---- 删除：完成职工信息的删除； \n");
	printf("   C|c ---- 修改：允许对已经录入的数据重新进行编辑、修改； \n");
	printf("   S|s ---- 显示：显示所有职工的信息；\n");
	printf("   F|f ---- 查询:\n");
	printf("   Q|q ---- 退出程序。\n");
	printf("   $:");
}

void menuFind()
{
	printf("a. 按姓名查找职工记录；\n");
	printf("b. 输入部门、性别，输出所有符合条件员工记录;\n");
	printf("c. 输入年龄范围，性别，输入所有符合条件员工记录;\n");
	printf("d. 输入部门，按工龄对所有符合条件员工记录排序输出;\n");
	printf("   其他键返回上级菜单!\n");
	printf("$:");
}

Emp* AllocateEmp()
{
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (0 == EmpArray.usedFlag[i])
		{
			EmpArray.usedFlag[i] = 1;
			return &EmpArray.employee[i];
		}
	}
	return 0;
}

void show(Emp* pEmp)
{
	printf("\n-------------------------员工信息---------------------------\n");
	printf("员工号：%d\n", pEmp->EmpId);
	printf("姓名：%s", pEmp->EmpName);
	printf("\n性别：%c", pEmp->Sex);
	printf("\n年龄：%d", pEmp->Age);
	printf("\n工龄：%d", pEmp->WorkYears);
	printf("\n职务：%s", pEmp->Position);
	printf("\n部门：%s", pEmp->Department);
	printf("\n住址：%s", pEmp->Address);
}

void Edit(Emp* pEmp)
{
	printf("请输入员工编号：");
	scanf("%d", &pEmp->EmpId);
	printf("\n请输入姓名：");
	scanf("%s", pEmp->EmpName);
	printf("\n请输入性别：");
	scanf("%s", &pEmp->Sex);
	printf("\n请输入年龄：");
	scanf("%d", &(pEmp->Age));
	printf("\n请输入工龄：");
	scanf("%d", &(pEmp->WorkYears));
	printf("\n请输入职务：");
	scanf("%s", pEmp->Position);
	printf("\n请输入部门：");
	scanf("%s", pEmp->Department);
	printf("\n请输入住址：");
	scanf("%s", pEmp->Address);
}

void inputEmpInfo()
{
	Emp* pEmp = 0;
	pEmp = AllocateEmp();

	Edit(pEmp);
}

void showAll()
{
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (1 == EmpArray.usedFlag[i])
		{
			show(&EmpArray.employee[i]);
		}
	}

}

void deleteEmp()
{
	int i;
	int empNo = 0;

	printf("\n请输入要删除的员工的编号：");
	scanf("%d", &empNo);

	for (i = 0; i < 100; i++)
	{
		if (EmpArray.employee[i].EmpId == empNo)
		{
			EmpArray.usedFlag[i] = 0;
			printf("删除成功！\n");
			break;
		}
	}
}

Emp* findByEmpNo(int empNo)
{
	int i;
	for (i = 0; i < 100; i++)
	{
		if (EmpArray.employee[i].EmpId == empNo)
		{
			return &EmpArray.employee[i];
		}
	}
	return 0;
}

void changeEmp()
{
	Emp* pEmp;
	int empNo = 0;

	printf("\n请输入要修改的员工的员工编号：");
	scanf("%d", &empNo);

	pEmp = findByEmpNo(empNo);
	if (0 == pEmp)
	{
		printf("没有找到输入的员工编号\n");
	}
	else
	{
		Edit(pEmp);
	}
}

void findByName()
{
	char EmpName[200];
	int i;
	int findCount;

	findCount = 0;

	printf("\n请输入员工的姓名：");
	scanf("%s", EmpName);

	for (i = 0; i < 100; i++)
	{
		if (0 == strcmp(EmpArray.employee[i].EmpName, EmpName))
		{
			show(&EmpArray.employee[i]);
			findCount++;
		}
	}

	printf("\n一共找到%d个员工。\n", findCount);

}

void findByDepAndSex()
{
	char dep[20];
	char sex[2];
	int i;
	int findCount;

	findCount = 0;

	printf("\n请输入部门：");
	scanf("%s", dep);
	printf("\n请输入性别：");
	scanf("%s", sex);

	for (i = 0; i < 100; i++)
	{
		if ((0 == strcmp(EmpArray.employee[i].Department, dep)) && (EmpArray.employee[i].Sex == *sex))
		{
			show(&EmpArray.employee[i]);
			findCount++;
		}
	}

	printf("\n一共找到%d个员工。\n", findCount);
}

void findByAgeAndSex()
{
	int fromAge;
	int toAge;
	char sex[2];
	int i;
	int findCount;

	findCount = 0;

	printf("\n请输入最小年龄");
	scanf("%d", &fromAge);
	printf("\n请输入最大年龄");
	scanf("%d", &toAge);
	printf("\n请输入性别：");
	scanf("%s", sex);

	for (i = 0; i < 100; i++)
	{
		if ((fromAge <= EmpArray.employee[i].Age) && (EmpArray.employee[i].Age <= toAge) && (EmpArray.employee[i].Sex == *sex))
		{
			show(&EmpArray.employee[i]);
			findCount++;
		}
	}

	printf("\n一共找到%d个员工。\n", findCount);
}

void findByDep()
{
	char dep[20];
	int i;
	int findCount;

	findCount = 0;

	printf("\n请输入部门：");
	scanf("%s", dep);

	sortByWorkYears();

	for (i = 0; i < 100; i++)
	{
		if (0 == strcmp(EmpArray.employee[i].Department, dep))
		{
			show(&EmpArray.employee[EmpArray.sortByWorkYears[i]]);
			findCount++;
		}
	}

	printf("\n一共找到%d个员工。\n", findCount);
}

void FindEmp()
{
	char o[10];
	menuFind();

	scanf("%s", o);

	switch (*o)
	{
	case 'a':
		findByName();
		break;
	case 'b':
		findByDepAndSex();
		break;
	case 'c':
		findByAgeAndSex();
		break;
	case 'd':
		findByDep();
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	char op;

	while (1)
	{
		menu();
		scanf("%s", &op);
		//op = getchar();

		if (('I' == op) || ('i' == op))
		{
			inputEmpInfo();
		}
		else if (('D' == op) || ('d' == op))
		{
			deleteEmp();
		}
		else if (('C' == op) || ('c' == op))
		{
			changeEmp();
		}
		else if (('S' == op) || ('s' == op))
		{
			showAll();
		}
		else if (('F' == op) || ('f' == op))
		{
			FindEmp();
		}
		else if (('Q' == op) || ('q' == op))
		{
			break;
		}
		else
		{
			printf("Invalidate operation!");
		}

	}
	return 0;
}