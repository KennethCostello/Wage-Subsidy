/*CostelloKenneth_FinalExam_CT609*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//name structure 
typedef struct
{
	char* employee_fname[15];
	char* employee_sname[15];
}name;

//employee structure
typedef struct
{
	int employee_code;
	name employee_name;
	int insurable_weeks;
	float gross_pay;
	float subsidy;
} employee;

//declaring functions 
void display_menu();
void view_all_employees(employee[], int c);
void add_new_employee(employee[], int size);
void save_data(employee[], int size);
void delete_employee (employee[], int size);
void view_total_subsidy_amount(float a, float b, float c, float d);
void sort_employees_by_name(employee[], int size);
void view_qualifying_employees(employee[], int c);
void find_disqualified_employees(employee[], int c);
void sort_employees_by_subsidy_amount(employee[], int c);

//main function
int main(void)
{
	//declaing varibles 
	int selected = 0;
	FILE* cfPtr; /* file pointer */
	int menuChoice;
	int length = 0, p = 0, i = 0;
	int word_alloc = 500;
	int word_count = 0;
	char word[50];
	employee* tempEmployee = (employee*)malloc(sizeof(employee) * word_alloc);
	employee* OrginalEmployee = (employee*)malloc(sizeof(employee) * word_alloc);
	int id = 1;
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0;

	//open file or create new 
	if (((cfPtr = fopen("data.txt", "r")) == NULL))
	{
		printf("*********\nFile could not be opened a new file has been created \n*********\n");

	}
	else if (((cfPtr = fopen("data.txt", "a+")) != NULL))
	{
		/*while loop to scan file and place words in temp char to loaded into array*/
		while (fscanf(cfPtr, "%d %s %s %d %f", &tempEmployee[word_count].employee_code ,tempEmployee[word_count].employee_name.employee_fname, tempEmployee[word_count].employee_name.employee_sname, &tempEmployee[word_count].insurable_weeks, &tempEmployee[word_count].gross_pay) != EOF)
		{
			tempEmployee[word_count].employee_code = id;
			/*determining subsidy amount*/
			if (tempEmployee[word_count].insurable_weeks <= 5 && tempEmployee[word_count].insurable_weeks >= 1)
				{
					if (tempEmployee[word_count].gross_pay >= 400.00)
					{
						tempEmployee[word_count].subsidy = 350;
						s1++;
					}
					if (tempEmployee[word_count].gross_pay <= 400.00 && tempEmployee[word_count].gross_pay >= 300.00)
					{
						tempEmployee[word_count].subsidy = 300;
						s2++;
					}
					if (tempEmployee[word_count].gross_pay <= 300.00 && tempEmployee[word_count].gross_pay >= 203.00)
					{
						tempEmployee[word_count].subsidy = 250;
						s3++;
					}
					if (tempEmployee[word_count].gross_pay <= 203.00 && tempEmployee[word_count].gross_pay >= 151.50)
					{
						tempEmployee[word_count].subsidy = 203;
						s4++;
					}
					if (tempEmployee[word_count].gross_pay < 151.50)
					{
						tempEmployee[word_count].subsidy = 0;
					}
			}
			else
			{
				tempEmployee[word_count].subsidy = 0;
			}
			
			/* If more words than allocated then double size*/
			if (word_count >= word_alloc)
			{
				tempEmployee = OrginalEmployee;
				if (tempEmployee == NULL)
				{
					printf("\n Error memory not allocated \n");
					exit(0);
				}
				word_alloc *= 2;
			}
			++word_count;
			++id;
		}

	}
	else
	{
		printf("\n Unable to create a file! Goodbye \n");
		return 1;
	}
	fclose(cfPtr);

	OrginalEmployee = tempEmployee;

	do
	{
		//displaying menu and switch to determine user options calling on functions
		display_menu();
		menuChoice = 0;
		while (menuChoice < 1 || menuChoice>9)
		{
			printf("*********\nPlease select from the menu \n*********\n");
			scanf("%d", &menuChoice);
		}
		switch (menuChoice)
		{
		case 1:
			add_new_employee(tempEmployee, word_count); 
			word_count++;
			break;
		case 2:
			delete_employee(tempEmployee, word_count);
			word_count--;
			break;
		case 3:
			view_all_employees(tempEmployee, word_count);
			break;
		case 4:
			view_qualifying_employees(tempEmployee, word_count);
			break;
		case 5:
			find_disqualified_employees(tempEmployee, word_count);
			break;
		case 6:
			sort_employees_by_name(tempEmployee, word_count);
			break;
		case 7:
			sort_employees_by_subsidy_amount(tempEmployee, word_count);
			break;
		case 8:
			view_total_subsidy_amount(s1, s2, s3, s4);
			break;
		default:
			break;
		}
	} while (menuChoice != 9);
	
	//save on closing 
	if (menuChoice == 9)
	{
		save_data(tempEmployee, word_count);
	}
	return 0; /* indicates successful termination */
}

/*Menu Display Function*/
void display_menu()
{
	printf("\n\n------------------------------\n");
	printf("**        MAIN MENU           **\n");
	printf("  ------------------------------\n");
	printf("1. Add new employee\n");
	printf("2. Delete employee\n");
	printf("3. View all employees\n");
	printf("4. View only qualifying employees\n");
	printf("5. View disqualified employees\n");
	printf("6. Sort employees by name\n");
	printf("7. Sort employees by subsidy amount\n");
	printf("8. View total subsidy amount (Total for all employees)\n");
	printf("9. Exit\n");
}

/*view employees Function*/
void view_all_employees(employee* n, int c)
{
	int count;
	/*print titles*/
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array*/
	for (count = 0; count < c; count++)
	{
		printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
	}
}

/*add employee Function*/
void add_new_employee(employee* n, int c)
{
	int count = c;
	char fName[15], sName[15];
	int insWeeks= 0;
	float pay = 0;

	employee* TempEmp = n;

	/*assign next user ID*/
	printf("New Employee Id assigned : %d\n", count + 1);
	n[count].employee_code = count + 1;

	/*Ask for first name - kept getting const char* issue here would not compile*/	
	/*printf("Please enter Employees First Name: \n");
	scanf("%s", fName);
	strcpy(n[count].employee_name.employee_fname, fName); */
	
	/*Ask for Second name - same issue */
	/*printf("Please enter Employees Second Name: \n");
	scanf("%s", sName);
	strcpy(n[count].employee_name.employee_sname, sName);
	*/

	/*Ask for insurable weeks*/
	printf("Please enter Employees insurable_weeks: \n ");
	scanf("%d", &insWeeks);
	n[count].insurable_weeks = insWeeks;

	/*Ask for gross pay*/
	printf("Please enter Employees gross pay: \n");
	scanf("%f", &pay);
	n[count].gross_pay = pay;

	/* print new employee*/
	printf("\n ****************** New Employee Added *************\n");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
}

/*save data Function*/
void save_data(employee* n, int c)
{
	FILE* cfPtr1;
	/* opening file */
	cfPtr1 = fopen("data.txt", "w");

	int count;
	/*writing txt to file using for loop */
	for (count = 0; count < c; count++)
	{
		fprintf(cfPtr1, "\n%d %22s %22s %22d %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay);
	}
	fclose(cfPtr1);
	printf("*********\n You have stored the Employee list and saved to file : data.txt\n\n*********\n");
}

/* delete Function*/
void delete_employee(employee* n, int c)
{
	int count = c + 1;
	employee temp;
	int position, pos;

	/* ask for employee no to delete*/
	printf("Enter the Employee No. you wish to delete:\n");
	scanf("%d", &position);

	/* deletes if inside array error message if not*/
	if (position >= count + 1)
		printf("Deletion not possible.\n");
	else
	{
		for (count = position; count < c; count++)
			n[count-1] = n[count];
	}		
}

/* Total subsidy Function*/
void view_total_subsidy_amount(float a, float b, float c, float d)
{
	/*Declare varibles*/
	float Sub1 = a * 350.00;
	float Sub2 = b * 300.00;
	float Sub3 = c * 250.00;
	float Sub4 = d * 203.00;
	float TotalSubsidy = Sub1 + Sub2 + Sub3 + Sub4;
	/*Print totals*/
	printf("Total subsidy amount (total for all employees):%.2f", TotalSubsidy);
}

/* Sort by name Function*/
void sort_employees_by_name(employee* n, int c)
{
	int j, count = c + 1;
	employee temp;
	/*for (int i = 0; i < count; i++)   \\ kept getting const char* issue here would not compile	
	{
		j = i - 1;
		while (j >= 0 && strcmp(n[j + 1].employee_name.employee_fname, n[j].employee_name.employee_fname) < 0)
		{
			temp = n[j + 1];
			n[j + 1] = n[j];
			n[j] = temp;
			j--;
		}
	}
	*/
	/*print titles*/
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print new sorted array*/
	for (count = 0; count < c; count++)
	{
		printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
	}
}

/* qualifying_employees Function*/
void view_qualifying_employees(employee* n, int c)
{
	int count;
	/*print titles*/
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].gross_pay > 151.50 && n[count].insurable_weeks != 0)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
}

/* find_disqualified_employees Function*/
void find_disqualified_employees(employee* n, int c)
{
	int count;
	/*print titles*/
	printf("\n\nEmployees Do Not Earn Enough to Qualify");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].gross_pay < 151.50)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
	/*print titles*/
	printf("\n\nEmployees Do Not Fall Within Insurable Weeks");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].insurable_weeks < 1 || n[count].insurable_weeks > 5)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
}

/* sort_employees_by_subsidy_amount Function*/
void sort_employees_by_subsidy_amount(employee* n, int c)
{
	int count;
	/*print titles*/
	printf("\n\nEmployees Receiving a Subsidy Amount of 350");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].subsidy == 350)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
	/*print titles*/
	printf("\n\nEmployees Receiving a Subsidy Amount of 300");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].subsidy == 300)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
	/*print titles*/
	printf("\n\nEmployees Receiving a Subsidy Amount of 250");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].subsidy == 250)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}
	/*print titles*/
	printf("\n\nEmployees Receiving a Subsidy Amount of 203");
	printf("\n%s %22s %30s %22s %22s\n", "Employee Number", "Name", "Weeks", "Grosspay", "Subsidy");
	/*for loop to print array with employees falling into conditions of if statement */
	for (count = 0; count < c; count++)
	{
		if (n[count].subsidy == 203)
		{
			printf("\n%d %22s %22s %22d %22.2f %22.2f", n[count].employee_code, n[count].employee_name.employee_fname, n[count].employee_name.employee_sname, n[count].insurable_weeks, n[count].gross_pay, n[count].subsidy);
		}
	}

}