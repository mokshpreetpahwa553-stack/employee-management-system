/*
 * 
 * This program:
 * - Stores employee records including personal details, salary, employment status,
 *   performance ratings, and up to 5 projects per employee
 * - Sorts employees by department (alphabetically), then by performance rating,
 *   then by salary (highest first)
 * - Calculates performance-based bonuses with employment status multipliers
 * - Generates department-wise statistics: average salaries by status, total project
 *   budgets, and employee counts by performance rating
 * - Lists employees working on ongoing projects below 50% completion
 * - Recommends employees eligible for promotion based on performance, tenure,
 *   completed projects, and employment status
 * -Identifies at-risk departments where >40% of employees have poor ratings
 */

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef enum {FULL_TIME,PART_TIME,CONTRACT,INTERN} EMPLOYEMENT_STATUS; //it holds employement status of employess
typedef enum {EXCELLENT,GOOD,SATISFACTORY,NEEDS_IMPROVEMENT,UNSATISFACTORY} PERFORMANCE_RATING; //it holds performance of employess
typedef enum {ONGOING,COMPLETED,PAUSED,CANCELLED} PROJECT_STATUS; //it holds project status of employees

typedef struct PROJECT{  //it will store details of project
	char project_name[50];  //project name
    PROJECT_STATUS project_st; //project status, used enum project datatype
    double budget_allocated; //budget allocated 
    int completion_percentage; //how much project got completed
}PROJECT;

typedef struct EMPLOYEE{  //it will store details of employees
	char name[30]; //name of employee
	int id; //id of emmplopyee
	char department[20]; //employee department
	double salary;
	int joining_year; //employee joining year
	double bonus; //bonus for employee, we will not input this as we will calculate this for employees and then  we will print this with employee details
	EMPLOYEMENT_STATUS status; //employement stataus of employee
	PERFORMANCE_RATING performance; //employee performance
	int num_of_project;  //number of project of each employee
	PROJECT projects[5]; //associated projects of employee
	
}EMPLOYEE;


//function to input employee details
void input_employee_details(EMPLOYEE staff[],int n); //n is number of employees

//function to sort employess based on department (alphabetically)
void sort_department(EMPLOYEE staff[],int n);

//function to sort employees based on performance rating in each department, it will also sort on salary if performance rating is same
void sort_performance(EMPLOYEE staff[],int n);

//function to caluclate bonus
void bonus_calculator(EMPLOYEE staff[],int n); //we will not return anything from this function we will edit STAFF in this function only

//function to print list of all employees after sorting
void print_after_sorting(EMPLOYEE staff[],int n);

/*function to calculate department wise stats
>Average salary per employment status within each department
>Total budget allocated to projects in each department
>Count of employees by performance rating in each department*/
void dept_stats(EMPLOYEE staff[],int n);

//function to display employees working on ongoing projects, with completion percentage be;ow 50%, grouped by department
void ongoingProject_below50_dept(EMPLOYEE staff[],int n);

/*function to give employee name, id and department of employees that completes following criteria
Performance rating is EXCELLENT or GOOD
Working on at least 2 COMPLETED projects
Tenure of at least 3 years
FULL_TIME or PART_TIME status*/
void promotion(EMPLOYEE staff[],int n);

//function that identify Identify departments where more than 40% of employees have NEEDS_IMPROVEMENT or UNSATISFACTORY ratings
void risk_assessment(EMPLOYEE staff[],int n);


//main function
int main(void)
{
	int number_of_employees;
	EMPLOYEE staff[100]; //maximum staff can be of 100 employee
	do{
	printf("Enter number of employees in your staff: ");
	scanf("%d",&number_of_employees);
	getchar(); //always use getchar after scanf if there is fgets after this, it consumes buffered newline
	}while(number_of_employees<=0 || number_of_employees>100); //used do while loop to enter number of employyes between 1 and 100


	//calling function to input employees details
	input_employee_details(staff,number_of_employees);

	//calling function to sort employees by department(alphabetically)
	sort_department(staff,number_of_employees);

	//calling function to sort employees on performance basis
	sort_performance(staff,number_of_employees);

	//calling function to calculate and add bonuses to employee details
	bonus_calculator(staff,number_of_employees);

	//calling function to print list of all employees after sorting
	print_after_sorting(staff, number_of_employees);

	//calling function to calculate stats
	dept_stats(staff,number_of_employees);

	//calling function to display employees working on ongoing projects below 50 in each department
	ongoingProject_below50_dept(staff,number_of_employees); 

	//calling function for promotion recommendations
	promotion(staff,number_of_employees);

	//calling function for risk assessment
	risk_assessment(staff,number_of_employees);

	return 0; 
	//end of main function
}


void input_employee_details(EMPLOYEE staff[],int n)
{
	printf("\t Please enter employees details\n");
	for(int i=0;i<n;i++)
	{
		printf("Employee name: ");
		fgets(staff[i].name,30,stdin); //used fgets instead of scanf bcs scanf ignores spaces and we want spaces in first and last names
		staff[i].name[strcspn(staff[i].name,"\n")]='\0'; //remove trailing newline

		printf("Employee id: ");
		scanf("%d",&staff[i].id);
		printf("Employee's Department: ");
		scanf("%19s",staff[i].department);
		printf("Employee's Salary: ");
		scanf("%lf",&staff[i].salary);
		printf("Employee's Joining year: ");
		scanf("%d",&staff[i].joining_year);
		printf("Employee's Employement Status(0-FULL_TIME, 1-PART_TIME, 2-CONTRACT, 3-INTERN): ");

		// scanf doesn't work directly with enums, so read as int first
		int temp_status;
		scanf("%d",&temp_status);
		if(temp_status<0||temp_status>3){ //to check it remain in bound
			printf("invalid status, using FULL TIME as default\n");
			temp_status=0;
		}
		staff[i].status=(EMPLOYEMENT_STATUS)temp_status;


		printf("Employee's performance rating(0-EXCELLENT, 1-GOOD, 2-SATISFACTORY, 3-NEEDS_IMPROVEMENT, 4-UNSATISFACTORY): ");
		int temp_perf;
		scanf("%d",&temp_perf);
		if(temp_perf<0 || temp_perf>4){
			printf("Invalid input, using SATISFACTORY as default\n");
			temp_perf=2;
		}
		staff[i].performance=(PERFORMANCE_RATING)temp_perf;

		do{

		printf("Number of projects: ");
		scanf("%d",&staff[i].num_of_project);
		getchar(); //always use getchar after scanf if there is fgets after this, it consumes buffered newline
		if(staff[i].num_of_project<0 || staff[i].num_of_project>5)
		{
			printf("Maximum projects allowed per employee is 5\n"); //erong input message
		}

		}while(staff[i].num_of_project<0 || staff[i].num_of_project>5); //maximum projec per employee is 5

		printf("\n");
		printf("ENTER PROJECT DETAILS:\n");

		for(int j=0; j<staff[i].num_of_project;j++)
		{
			printf("\t Project %d\n",j+1); //print number of project
			printf("Project name: ");
			fgets(staff[i].projects[j].project_name,50,stdin);
			 // Remove trailing newline
            staff[i].projects[j].project_name[strcspn(staff[i].projects[j].project_name, "\n")] = '\0';

            printf("Project Status(0-Ongoing,1-Completed,2-Paused,3-Cancelled): ");
            int temp_pro;
            scanf("%d",&temp_pro);

            if(temp_pro<0 || temp_pro>3){
            	printf("Wrong input, using Ongoing as default\n");
            	temp_pro=0;
            }
            staff[i].projects[j].project_st=(PROJECT_STATUS)temp_pro;


            printf("Enter budget allocated for project: ");
            scanf("%lf",&staff[i].projects[j].budget_allocated);
            printf("Enter completion Percentage(in whole numbers): ");
            scanf("%d",&staff[i].projects[j].completion_percentage);
            getchar();
            printf("\n"); //for good spacing
            getchar();
		}
		printf("\n\n"); //for good spacing


	}
}


void sort_department(EMPLOYEE staff[],int n)
{
	int i;
	int first_alphabetically;
	//Loop to sort employees based on department
	for(i=0;i<n-1;i++)
	{
		first_alphabetically=i;
		for(int j=i+1;j<n;j++)
		{
			if (strcmp(staff[j].department,staff[first_alphabetically].department) < 0)
			{
				first_alphabetically=j;
			}
		}
		if(first_alphabetically!=i)
		{
		EMPLOYEE temp=staff[i];
		staff[i]=staff[first_alphabetically];
		staff[first_alphabetically]=temp;
		}
		
	}

}


void sort_performance(EMPLOYEE staff[],int n)
{
	
	for(int i=0;i<n;i++)
	{ 
		char current_department[20]; //this string will hold department alphabetically, first depaartment will be first to go 
		strcpy(current_department,staff[i].department); //it will allocate departments to current_department alphabetically
		int employees_in_depart=0;  //this will count number of employees in each department
		int first_perf=i;
		
			for(int j=i;j<n;j++)
			{
				if(strcmp(staff[j].department,current_department)==0) //this loop will check that only employees of same department get sorted at once
				{
					if(staff[j].performance<staff[first_perf].performance)
					{
						first_perf=j;
					}
					else if(staff[j].performance==staff[first_perf].performance)  // to sort by salary in same performance rating 
					{
						if(staff[j].salary>staff[first_perf].salary)
						{
							first_perf=j;
						}
					}
					employees_in_depart++;
					
				}
				else
				{
					break;
				}
			}

			if(first_perf!=i)
			{
				EMPLOYEE temp=staff[i];
				staff[i]=staff[first_perf];
				staff[first_perf]=temp;
			}

			i=i+employees_in_depart-1;

		}

}
	

void bonus_calculator(EMPLOYEE staff[],int n)
{
	double performance_based[5]={0.2,0.12,0.05,0.0,0.0}; //array that holds percentage of salary foor bonus, 20% for excellent, 12 % for good 5% for satisfactory and 0% for needs_improvement and unsatisfactory
	double status_based[4]={1.5,1.0,0.5,0.5}; //1.5x bonus for full time, 1.0x for part time and 0.5x from contract and intern

	for(int i=0;i<n;i++)
	{
		/*array using has aved us from 16 if else loops, so its great approach to use 
		arrays in these kind of situations*/
		staff[i].bonus=staff[i].salary * performance_based[staff[i].performance] * status_based[staff[i].status];
	}
}


void print_after_sorting(EMPLOYEE staff[],int n)
{

	for(int i=0;i<n;i++)
	{		
		char first_dept[20];
		strcpy(first_dept,staff[i].department);
		printf("\t DEPARTMENT: %29s \n",first_dept);

		int x=i;
		while(x<n && strcmp(first_dept,staff[x].department)==0)
		{
			printf("Employee name: %s\n",staff[x].name);
			printf("Employee id: %d\n",staff[x].id);
			printf("Employee's Salary: %.2lf\n",staff[x].salary);
			printf("Employee's Joining year: %d\n",staff[x].joining_year);
			printf("Bonus: %.2lf\n",staff[x].bonus);
			switch(staff[x].status)
			{
			case 0:
				printf("Employee's Employement Status: FULL TIME ");
				break;
			case 1:
				printf("Employee's Employement Status: PART TIME ");
				break;
			case 2:
				printf("Employee's Employement Status: CONTRACT");
				break;
			case 3:
				printf("Employee's Employement Status: INTERN");
				break;
			default:
	           	printf("ERROR");
			}
			printf("\n");

			switch(staff[x].performance)
			{
			case 0:
				printf("Employee's performance rating: EXCELLENT ");
				break;
			case 1:
				printf("Employee's performance rating: GOOD ");
				break;

			case 2:
				printf("Employee's performance : SATISFACTORY");
				break;
			case 3:
				printf("Employee's performance rating: NEEDS IMPROVEMENT ");
				break;
			case 4:
				printf("Employee's performance rating: UNSATISFACTORY");
				break;
			default:
	           	printf("ERROR");
			}
			
			printf("\n\n");

			printf("Number of projects: %d\n",staff[x].num_of_project);

			for(int j=0; j<staff[x].num_of_project;j++)
			{
				printf("\t Project %d\n",j+1); //print number of project
				printf("Project name: %s\n",staff[x].projects[j].project_name);
	            
	            switch(staff[x].projects[j].project_st)
	            {
	            case 0:
	            	printf("Project Status: ONGOING ");
	            	break;
	            case 1:
	            	printf("Project Status: COMPLETED");
	            	break;
	            case 2:
	            	printf("Project Status: PAUSED");
	            	break;
	            case 3:
	            	printf("Project Status: CANCELLED");
	            	break;
	            default:
	            	printf("ERROR");
	            }
	            printf("\n");

	            printf("Budget allocated for project: %.2lf\n",staff[x].projects[j].budget_allocated);
	            printf("Completion Percentage(in whole numbers): %d\n",staff[x].projects[j].completion_percentage);

				printf("\n");
	            }
	           	           	            
	           printf("\n");
	           x++;
	           
			}
			printf("\n\n"); //for good spacing

			i=x-1;
		}

}
		
	
void dept_stats(EMPLOYEE staff[],int n)
{
	int i;
	double total_budget;
	for(i=0;i<n;i++)
	{
		total_budget=0;
		int employees_in_depart=0;
		char current_department[30];
		strcpy(current_department,staff[i].department);
		int x=i;
		while(x<n && strcmp(staff[x].department,current_department)==0) //this loop will allow employee of same department
		{

			for(int j=0;j<staff[x].num_of_project;j++)  //loop to calculate total budget of department
			{
				total_budget=total_budget+staff[x].projects[j].budget_allocated;
			}

			//starting loop to Count of employees by performance rating in each department
			
			int z=x;
			int current_perf=staff[z].performance;
			int num_employees_rating=0;

			while( z<n && staff[z].performance==current_perf && strcmp(staff[z].department, current_department) ==0) //we should check for department also everytime bcs inner loop can go to other departments
			{
				num_employees_rating++;
				z++;
			}
			printf("Number of %d(0-EXCELLENT, 1-GOOD, 2-SATISFACTORY, 3-NEEDS_IMPROVEMENT, 4-UNSATISFACTORY) employees in %s=%d\n",current_perf,current_department,num_employees_rating);

			//starting loop to calculate average salary of employees with same status in department
			int num_employees_status=0;
			double total_salary_status=0.0;
			int k=x;
			int current_status=staff[k].status;
			while(k<n && staff[k].status==current_status &&  strcmp(staff[k].department, current_department)==0)
			{
				total_salary_status+=staff[k].salary;
				num_employees_status++;
				k++;
			}

			bool division_possible=true;

			if(num_employees_status==0)
			{
				division_possible=false;
			}

			if(division_possible){
			double avg_salary_status=total_salary_status/num_employees_status;
			printf("Average Salary of %d(0-FULL_TIME, 1-PART_TIME, 2-CONTRACT, 3-INTERN) in department %s = %.2lf\n",current_status,current_department,avg_salary_status);
			}

			else{
				printf("number of %d(0-FULL_TIME, 1-PART_TIME, 2-CONTRACT, 3-INTERN) employees in %s is 0\n",current_status,current_department);
			}
			
			employees_in_depart++;
			x=z; //we did x=z to not recount employees if we do x++ then each time employess would be recount in last 2 while loops
		}
		i=i+employees_in_depart-1;
		printf("Total budget allocated to department %s = %.2lf\n",current_department,total_budget);
	}
	printf("\n\n");
}


void ongoingProject_below50_dept(EMPLOYEE staff[],int n)
{
	printf("/tOngoing projects with below 50% completion\n");
	for(int i=0;i<n;i++)
	{
		printf("\tDepartment: %s\n",staff[i].department);
		char current_department[20];
		strcpy(current_department,staff[i].department);
		int x=i;
		while(x<n && strcmp(staff[x].department,current_department)==0)
		{
			for(int j=0;j<staff[x].num_of_project;j++)
			{
				if(staff[x].projects[j].project_st==0 && staff[x].projects[j].completion_percentage<50)
				{
					printf("Employee name: %s\n",staff[x].name);
					printf("Employee ID: %d\n",staff[x].id);
				}
			}
			x++;
		}
		i=x-1;

	}
	printf("\n\n");
}


void promotion(EMPLOYEE staff[],int n)
{
	printf("\tPROMOTION RECOMMENDATIONS\n");
	bool promoted=false;
	for(int i=0;i<n;i++)
	{
		if((staff[i].performance==0 || staff[i].performance==1) && staff[i].joining_year<2023 &&
			(staff[i].status==0 || staff[i].status==1)) //it will check all criteria only except 2 completed project
		{
			int completed_project=0; 
			//below loop will check for work on 2 completed projects
			for(int j=0;j<staff[i].num_of_project;j++)
			{
				if(staff[i].projects[j].project_st==1) //if project completed then add 1
				{
					completed_project++;
				}
			}

			if(completed_project>=2)
			{
			printf("Employee Name: %s\n",staff[i].name);
			printf("Employee ID: %d\n",staff[i].id);
			printf("Employee department: %s\n",staff[i].department);
			promoted=true;
			printf("\n");
			}
		}
				
	}
	if(promoted==false)
	{
		printf("None");
	}
	printf("\n\n");
}


void risk_assessment(EMPLOYEE staff[],int n)
{
	printf("\tDepartments with below average ratings: \n");
	for(int i=0;i<n;i++)
	{
		char current_department[20];
		strcpy(current_department,staff[i].department);
		int employees_in_depart=0;
		int bad_ratings=0;
		int x=i;

		while(x<n && strcmp(current_department,staff[x].department)==0)
		{
			if(staff[x].performance==3 || staff[x].performance==4)
			{
				bad_ratings++;
			}
			x++;
			employees_in_depart++;
		}

		if(bad_ratings>(0.4*employees_in_depart))
		{
			printf("%s\n",current_department);
		}

		i=x-1;
	}
}





