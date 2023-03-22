#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {CS,EC,EE,ME,CV} dept_code;

typedef struct RollNo_tag //Format : yy-dc-no
{
	int year; 
	dept_code dc;
	int roll;
}RollNo;

typedef struct StudentRecord
{
	char name[50];
	dept_code code;
	int year;
	RollNo roll_no;
	int classes_conducted[5];//for 5 courses
	int classes_attended[5];
	struct StudentRecord* next;
}StudentRecordList;

typedef struct AttendanceRecord
{
	RollNo roll_no;
	dept_code code;
	float attendance;
	struct AttendanceRecord* next;
}AttendanceRecordList;

typedef struct FeeStatus
{
	RollNo roll_no;
	char status[7];
	struct FeeStatus* next;
}FeeStatusList;

typedef struct Applicant
{
	char name[50];
	RollNo roll_no;
	char application[2]; // A/NA
	struct Applicant* next;
}ApplicantList;

typedef struct Record
{
	int year;
	dept_code dc;
	int roll_no;
	float attendance;
	struct Record* next;
}RecordList;

typedef struct Defaulter
{
	dept_code dc;
	int roll_no;
	char status[7];
	float attendance;
	struct Defaulter* next;
}DefaulterList;

StudentRecordList* Merge1(StudentRecordList* lptr1,StudentRecordList* lptr2)
{
	StudentRecordList *result,*ptr1,*ptr2,*tail;
	ptr1 = lptr1;
	ptr2 = lptr2;
	
	if (ptr1->year < ptr2->year)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else if (ptr1->year > ptr2->year)
	{
		result = ptr2;
		ptr2 = ptr2->next;
	}
	else
	{
		if (ptr1->code < ptr2->code)
		{
			result = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->code > ptr2->code)
		{
			result = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->roll_no.roll < ptr2->roll_no.roll)
			{
				result = ptr1;
				ptr1 = ptr1->next;
			}
			else
			{
				result = ptr2;
				ptr2 = ptr2->next;
			}
		}
	}
	tail = result;
	
	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->year < ptr2->year)
		{
			tail = tail->next = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->year > ptr2->year)
		{
			tail = tail->next = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->code < ptr2->code)
			{
				tail = tail->next = ptr1;
				ptr1 = ptr1->next;
			}
			else if (ptr1->code > ptr2->code)
			{
				tail = tail->next = ptr2;
				ptr2 = ptr2->next;
			}
			else
			{
				if (ptr1->roll_no.roll < ptr2->roll_no.roll)
				{
					tail = tail->next = ptr1;
					ptr1 = ptr1->next;
				}
				else
				{
					tail = tail->next = ptr2;
					ptr2 = ptr2->next;
				}
			}
		}
	}
	
	if (ptr1 != NULL)
		tail->next = ptr1;
	else
		tail->next = ptr2;
		
	return result;
}

StudentRecordList* Divide1(StudentRecordList* lptr)
{
	StudentRecordList *nptr,*fast,*slow;
	slow = lptr;
	fast = (lptr->next)->next;
	
	while (fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
		if (fast != NULL)
			fast = fast->next;
	} 
	
	nptr = slow->next;
	slow->next = NULL;
	return nptr;
}

StudentRecordList* MergeSort1(StudentRecordList* list_ptr)
{
	StudentRecordList *nptr,*lptr;
	lptr = list_ptr;
	
	if (lptr != NULL && lptr->next != NULL)
	{
		nptr = Divide1(lptr);
		lptr = MergeSort1(lptr);
		nptr = MergeSort1(nptr);
		lptr = Merge1(lptr,nptr);
	}
	
	return lptr;
}

ApplicantList* Merge2(ApplicantList* lptr1,ApplicantList* lptr2)
{
	ApplicantList *result,*ptr1,*ptr2,*tail;
	ptr1 = lptr1;
	ptr2 = lptr2;
	
	if (ptr1->roll_no.year < ptr2->roll_no.year)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else if (ptr1->roll_no.year > ptr2->roll_no.year)
	{
		result = ptr2;
		ptr2 = ptr2->next;
	}
	else
	{
		if (ptr1->roll_no.dc < ptr2->roll_no.dc)
		{
			result = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->roll_no.dc > ptr2->roll_no.dc)
		{
			result = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->roll_no.roll < ptr2->roll_no.roll)
			{
				result = ptr1;
				ptr1 = ptr1->next;
			}
			else
			{
				result = ptr2;
				ptr2 = ptr2->next;
			}
		}
	}
	tail = result;
	
	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->roll_no.year < ptr2->roll_no.year)
		{
			tail = tail->next = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->roll_no.year > ptr2->roll_no.year)
		{
			tail = tail->next = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->roll_no.dc < ptr2->roll_no.dc)
			{
				tail = tail->next = ptr1;
				ptr1 = ptr1->next;
			}
			else if (ptr1->roll_no.dc > ptr2->roll_no.dc)
			{
				tail = tail->next = ptr2;
				ptr2 = ptr2->next;
			}
			else
			{
				if (ptr1->roll_no.roll < ptr2->roll_no.roll)
				{
					tail = tail->next = ptr1;
					ptr1 = ptr1->next;
				}
				else
				{
					tail = tail->next = ptr2;
					ptr2 = ptr2->next;
				}
			}
		}
	}
	
	if (ptr1 != NULL)
		tail->next = ptr1;
	else
		tail->next = ptr2;
		
	return result;
}

ApplicantList* Divide2(ApplicantList* lptr)
{
	ApplicantList *nptr,*fast,*slow;
	slow = lptr;
	fast = (lptr->next)->next;
	
	while (fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
		if (fast != NULL)
			fast = fast->next;
	} 
	
	nptr = slow->next;
	slow->next = NULL;
	return nptr;
}

ApplicantList* MergeSort2(ApplicantList* list_ptr)
{
	ApplicantList *nptr,*lptr;
	lptr = list_ptr;
	
	if (lptr != NULL && lptr->next != NULL)
	{
		nptr = Divide2(lptr);
		lptr = MergeSort2(lptr);
		nptr = MergeSort2(nptr);
		lptr = Merge2(lptr,nptr);
	}
	
	return lptr;
}

FeeStatusList* Merge3(FeeStatusList* lptr1,FeeStatusList* lptr2)
{
	FeeStatusList *result,*ptr1,*ptr2,*tail;
	ptr1 = lptr1;
	ptr2 = lptr2;
	
	if (ptr1->roll_no.year < ptr2->roll_no.year)
	{
		result = ptr1;
		ptr1 = ptr1->next;
	}
	else if (ptr1->roll_no.year > ptr2->roll_no.year)
	{
		result = ptr2;
		ptr2 = ptr2->next;
	}
	else
	{
		if (ptr1->roll_no.dc < ptr2->roll_no.dc)
		{
			result = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->roll_no.dc > ptr2->roll_no.dc)
		{
			result = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->roll_no.roll < ptr2->roll_no.roll)
			{
				result = ptr1;
				ptr1 = ptr1->next;
			}
			else
			{
				result = ptr2;
				ptr2 = ptr2->next;
			}
		}
	}
	tail = result;
	
	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->roll_no.year < ptr2->roll_no.year)
		{
			tail = tail->next = ptr1;
			ptr1 = ptr1->next;
		}
		else if (ptr1->roll_no.year > ptr2->roll_no.year)
		{
			tail = tail->next = ptr2;
			ptr2 = ptr2->next;
		}
		else
		{
			if (ptr1->roll_no.dc < ptr2->roll_no.dc)
			{
				tail = tail->next = ptr1;
				ptr1 = ptr1->next;
			}
			else if (ptr1->roll_no.dc > ptr2->roll_no.dc)
			{
				tail = tail->next = ptr2;
				ptr2 = ptr2->next;
			}
			else
			{
				if (ptr1->roll_no.roll < ptr2->roll_no.roll)
				{
					tail = tail->next = ptr1;
					ptr1 = ptr1->next;
				}
				else
				{
					tail = tail->next = ptr2;
					ptr2 = ptr2->next;
				}
			}
		}
	}
	
	if (ptr1 != NULL)
		tail->next = ptr1;
	else
		tail->next = ptr2;
		
	return result;
}

FeeStatusList* Divide3(FeeStatusList* lptr)
{
	FeeStatusList *nptr,*fast,*slow;
	slow = lptr;
	fast = (lptr->next)->next;
	
	while (fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
		if (fast != NULL)
			fast = fast->next;
	} 
	
	nptr = slow->next;
	slow->next = NULL;
	return nptr;
}

FeeStatusList* MergeSort3(FeeStatusList* list_ptr)
{
	FeeStatusList *nptr,*lptr;
	lptr = list_ptr;
	
	if (lptr != NULL && lptr->next != NULL)
	{
		nptr = Divide3(lptr);
		lptr = MergeSort3(lptr);
		nptr = MergeSort3(nptr);
		lptr = Merge3(lptr,nptr);
	}
	
	return lptr;
}

void print1(ApplicantList* ptr)
{
	ApplicantList*lptr=ptr;
	while (lptr != NULL)
	{
		printf("\nName : %s\n",lptr->name);
		printf("Year : %d\n",lptr->roll_no.year);
		if (lptr->roll_no.dc == CS)  printf("Department : Computer Sc. & Engg.\n");
		else if (lptr->roll_no.dc == EC)  printf("Department : Electronics & Comm.\n");
		else if (lptr->roll_no.dc == EE)  printf("Department : Electrical\n");
		else if (lptr->roll_no.dc == ME)  printf("Department : Mechanical\n");
		else  printf("Department : Civil\n");
		
		lptr = lptr->next;
	}
}

void print2(RecordList* ptr)
{
	RecordList*lptr=ptr;
	while (lptr != NULL)
	{
		printf("\nYear : %d\n",lptr->year);
		if (lptr->dc == CS)  printf("Department : Computer Sc. & Engg.\n");
		else if (lptr->dc == EC)  printf("Department : Electronics & Comm.\n");
		else if (lptr->dc == EE)  printf("Department : Electrical\n");
		else if (lptr->dc == ME)  printf("Department : Mechanical\n");
		else  printf("Department : Civil\n");
		printf("Roll number : %d\n",lptr->roll_no);
		lptr = lptr->next;
	}
}

void print3(AttendanceRecordList* ptr)
{
	AttendanceRecordList*lptr=ptr;
	if(lptr==NULL) printf("\nEMPTY LIST.");
	while (lptr != NULL)
	{
		printf("\nYear : %d\n",lptr->roll_no.year);
		if (lptr->code == CS)  printf("Department : Computer Sc. & Engg.\n");
		else if (lptr->code == EC)  printf("Department : Electronics & Comm.\n");
		else if (lptr->code == EE)  printf("Department : Electrical\n");
		else if (lptr->code == ME)  printf("Department : Mechanical\n");
		else  printf("Department : Civil\n");
		printf("Roll number : %d\n",lptr->roll_no.roll);
		printf("Attendance : %.2f\n",lptr->attendance);
		lptr = lptr->next;
	}
}

void print4(DefaulterList* lptr)
{
	while (lptr != NULL)
	{
		if (lptr->dc == CS)  printf("\nDepartment : Computer Sc. & Engg.\n");
		else if (lptr->dc == EC)  printf("\nDepartment : Electronics & Comm.\n");
		else if (lptr->dc == EE)  printf("\nDepartment : Electrical\n");
		else if (lptr->dc == ME)  printf("\nDepartment : Mechanical\n");
		else  printf("\nDepartment : Civil\n");
		printf("Roll number : %d\n",lptr->roll_no);
		printf("Fee Status : %s\n",lptr->status);
		printf("Attendance : %.2f\n",lptr->attendance);
		lptr = lptr->next;
	}
}

void display(StudentRecordList* ptr)
{
	StudentRecordList* lptr=ptr;
	while (lptr != NULL)
	{
		printf("\nName : %s\n",lptr->name);
		if (lptr->roll_no.dc == CS)  printf("Department : Computer Sc. & Engg.\n");
		else if (lptr->roll_no.dc == EC)  printf("Department : Electronics & Comm.\n");
		else if (lptr->roll_no.dc == EE)  printf("Department : Electrical\n");
		else if (lptr->roll_no.dc == ME)  printf("Department : Mechanical\n");
		else  printf("Department : Civil\n");
		printf("Year : %d\n",lptr->year);
		printf("Roll No : %d\n",lptr->roll_no.roll);
		
		lptr = lptr->next;
	}
}

void main()
{
	FILE *fp;
	fp=fopen("data.txt","r");
	StudentRecordList* SRLptr;
	FeeStatusList* FSLptr;
	ApplicantList* ALptr;
	SRLptr = NULL;
	FSLptr = NULL;
	ALptr = NULL;
	int i;
	int cs,ec,ee,me,cv;
	cs=ec=ee=me=cv=0;
	StudentRecordList* nptr1;
	FeeStatusList* nptr2;
	ApplicantList* nptr3;
	if(fp==NULL) printf("ERROR");
	else
	{
		
	while(!feof(fp))
	{
		nptr1=(StudentRecordList*)malloc(sizeof(StudentRecordList));
		nptr2=(FeeStatusList*)malloc(sizeof(FeeStatusList));
		nptr3=(ApplicantList*)malloc(sizeof(ApplicantList));
		
		//name input
		char name[50];
		fgets(name,50,fp);
		int len=strlen(name);
		if(name[len-1]=='\n')
		{
			name[len-1]='\0';
		}
		strcpy(nptr1->name,name);
		strcpy(nptr3->name,nptr1->name);
		//printf("Name: %s\n",nptr1->name);
		
		
		//department code
		char dept[2];
		fgets(dept,5,fp);
		if(strcmp(dept,"CS\n")==0)
		{
			nptr1->code = CS;
		}
		else if (strcmp(dept,"EC\n")==0)  nptr1->code = EC;
		else if (strcmp(dept,"EE\n")==0)  nptr1->code = EE;
		else if (strcmp(dept,"ME\n")==0)  nptr1->code = ME;
		else  nptr1->code = CV;
		//printf("Department code: %d\n",nptr1->code);
		
		//year
		
		char year[4];
		fgets(year,10,fp);
		if(year[len-1]=='\n')
		{
			year[len-1]='\0';
		}
		int nyear=atoi(year);
		nptr1->year = nyear;
		//printf("Year: %d\n",nptr1->year);
		
		
		//roll no
		nptr1->roll_no.year = nptr1->year;
		nptr1->roll_no.dc = nptr1->code;
		if (nptr1->code == CS)  nptr1->roll_no.roll = ++cs;
		else if (nptr1->code == EC)  nptr1->roll_no.roll = ++ec;
		else if (nptr1->code == EE)  nptr1->roll_no.roll = ++ee;
		else if (nptr1->code == ME)  nptr1->roll_no.roll = ++me;
		else  nptr1->roll_no.roll = ++cv;
		//printf("Roll no: %d\n",nptr1->roll_no.roll);
		
		nptr2->roll_no.year = nptr1->roll_no.year;
		nptr2->roll_no.dc = nptr1->code;
		nptr2->roll_no.roll = nptr1->roll_no.roll;
		
		nptr3->roll_no.year = nptr1->roll_no.year;
		nptr3->roll_no.dc = nptr1->code;
		nptr3->roll_no.roll = nptr1->roll_no.roll;
		
		//classes info input
		char cc[10];
		fgets(cc,15,fp);
		int num;
		for (i = 0; i < 5; i++)
		{
			char cci[2]={cc[2*i],'\0'};
			num=atoi(cci);
			nptr1->classes_conducted[i]=num;
			//printf("%d\n",nptr1->classes_conducted[i]);
		}
		
		char ca[10];
		fgets(ca,15,fp);
		for (i = 0; i < 5; i++)
		{
			char cai[2]={cc[2*i],'\0'};
			num=atoi(cai);
			nptr1->classes_attended[i]=num;
			//printf("%d\n",nptr1->classes_attended[i]);
		}
		
		char stat[7];
		fgets(stat,15,fp);
		if(stat[strlen(stat)-1]=='\n')
		{
			stat[strlen(stat)-1]='\0';
		}
		strcpy(nptr2->status,stat);
		//printf("Fee status: %s\n",nptr2->status);
		
		char app[2];
		fgets(app,5,fp);
		if(app[strlen(app)-1]=='\n')
		{
			app[strlen(app)-1]='\0';
		}
		strcpy(nptr3->application,app);
		//printf("Application: %s\n",nptr3->application);	
		
		nptr1->next = SRLptr;
		SRLptr = nptr1;
		nptr2->next = FSLptr;
		FSLptr = nptr2;
		nptr3->next = ALptr;
		ALptr = nptr3;
		}
	
	}
	fclose(fp);
	
	/*
	printf("Taken input from the file:\n");
	display(SRLptr);
	*/
	
	//Sort All Lists
	SRLptr = MergeSort1(SRLptr);
	ALptr = MergeSort2(ALptr);
	FSLptr = MergeSort3(FSLptr);
	
	//print sorted student record list
	printf("\nSorted Student record list\n");
	
	//Q1
	display(SRLptr);
	
	//List of non applicants
	ApplicantList *NotApplied,*ptr;
	NotApplied = NULL;
	nptr3 = ALptr;
	while (nptr3 != NULL)
	{
		if (nptr3->application[0] == 'N')
		{
			ptr=(ApplicantList*)malloc(sizeof(ApplicantList));
			
			strcpy(ptr->name,nptr3->name);
			strcpy(ptr->application,"NA");
			ptr->roll_no.dc = nptr3->roll_no.dc;
			ptr->roll_no.year = nptr3->roll_no.year;
			ptr->roll_no.roll = nptr3->roll_no.roll;
			
			ptr->next = NotApplied;
			NotApplied = ptr;
		}
		nptr3 = nptr3->next;
	}
	
	//Q2
	printf("\n\nList of students who did not apply for the examination:\n");
	print1(NotApplied);	
	
	//Finding MCC for each department
	int mcc_cs,mcc_ec,mcc_ee,mcc_me,mcc_cv;
	mcc_cs=mcc_ec=mcc_ee=mcc_me=mcc_cv=0;
	nptr1 = SRLptr;
	while (nptr1->code == CS)
	{
	for (i = 1; i < 5; i++)
	{
		if (nptr1->classes_conducted[i] > nptr1->classes_conducted[mcc_cs])
			mcc_cs = i;
	}
	nptr1=nptr1->next;
	}
	while (nptr1->code == EC)
	{
		nptr1=nptr1->next;
	for (i = 1; i < 5; i++)
	{
		if (nptr1->classes_conducted[i] > nptr1->classes_conducted[mcc_ec])
			mcc_ec = i;
	}
	}
	while (nptr1->code == EE)
	{
		nptr1=nptr1->next;
	for (i = 1; i < 5; i++)
	{
		if (nptr1->classes_conducted[i] > nptr1->classes_conducted[mcc_ee])
			mcc_ee = i;
	}
	}
	while (nptr1->code == ME)
	{
		nptr1=nptr1->next;
	for (i = 1; i < 5; i++)
	{
		if (nptr1->classes_conducted[i] > nptr1->classes_conducted[mcc_me])
			mcc_me = i;
	}
	}
	while (nptr1->code == CV)
	{
		nptr1=nptr1->next;
	for (i = 1; i < 5; i++)
	{
		if (nptr1->classes_conducted[i] > nptr1->classes_conducted[mcc_cv])
			mcc_cv = i;
	}
	}
	
	//Finding max no of classes attended for MCC		
	int max_cs,max_ec,max_ee,max_me,max_cv;
	max_cs=max_ec=max_ee=max_me=max_cv=0;
	nptr1 = SRLptr;
	while (nptr1 != NULL)
	{
		if (nptr1->code == CS && nptr1->classes_attended[mcc_cs] > max_cs)
			max_cs = nptr1->classes_attended[mcc_cs];
		else if (nptr1->code == EC && nptr1->classes_attended[mcc_ec] > max_ec)
			max_ec = nptr1->classes_attended[mcc_ec];
		else if (nptr1->code == EE && nptr1->classes_attended[mcc_ee] > max_ee)
			max_ee = nptr1->classes_attended[mcc_ee];
		else if (nptr1->code == ME && nptr1->classes_attended[mcc_me] > max_me)
			max_me = nptr1->classes_attended[mcc_me];
		else
			max_cv = nptr1->classes_attended[mcc_cv];
			
		nptr1 = nptr1->next;
	}
	
	nptr1 = SRLptr;
	AttendanceRecordList* ARLptr;
	ARLptr = NULL;
	while (nptr1 != NULL)
	{
		AttendanceRecordList* nptr;
		nptr=(AttendanceRecordList*)malloc(sizeof(AttendanceRecordList));
		
		nptr->roll_no.year = nptr1->roll_no.year;
		nptr->roll_no.dc = nptr1->code;
		nptr->roll_no.roll = nptr1->roll_no.roll;
		
		nptr->code = nptr1->code;
		
		if (nptr->code == CS)
			nptr->attendance = (float) (nptr1->classes_attended[mcc_cs]*100)/max_cs;
		else if (nptr->code == EC)
			nptr->attendance = (float) (nptr1->classes_attended[mcc_ec]*100)/max_ec;
		else if (nptr->code == EE)
			nptr->attendance = (float) (nptr1->classes_attended[mcc_ee]*100)/max_ee;
		else if (nptr->code == ME)
			nptr->attendance = (float) (nptr1->classes_attended[mcc_me]*100)/max_me;
		else
			nptr->attendance = (float) (nptr1->classes_attended[mcc_cv]*100)/max_cv;
			
		nptr->next = ARLptr;
		ARLptr = nptr;
		nptr1 = nptr1->next;
	}
	
	/*
	printf("\n\nSorted Attendance record list:\n");
	print3(ARLptr);
	*/
	
	RecordList *Eligible;
	Eligible = NULL;
	nptr2 = FSLptr;
	nptr3 = ALptr;
	AttendanceRecordList* nptr4 = ARLptr;
	while (nptr2!=NULL && nptr3!=NULL && nptr4!=NULL)
	{
		if ((nptr4->attendance > 75.0) && (strcmp(nptr2->status,"clear")) && (nptr3->application[0] == 'A'))
		{
			RecordList* ptr;
			ptr=(RecordList*)malloc(sizeof(RecordList));
			ptr->year = nptr2->roll_no.year;
			ptr->dc = nptr2->roll_no.dc;
			ptr->roll_no = nptr2->roll_no.roll;
			ptr->attendance = nptr4->attendance;
			
			ptr->next = Eligible;
			Eligible = ptr;		
		}
		nptr2 = nptr2->next;
		nptr3 = nptr3->next;
		nptr4 = nptr4->next;
	}
	
	printf("\n\nList of students who are eligiblie:\n");
	print2(Eligible);
	
	AttendanceRecordList *Wgrade;
	Wgrade = NULL;
	nptr4 = ARLptr;
	while (nptr4 != NULL)
	{
		if ((nptr4->attendance <= 75.0) && (nptr4->attendance < 100.0))
		{
			AttendanceRecordList *ptr;
			ptr=(AttendanceRecordList*)malloc(sizeof(AttendanceRecordList));
			ptr->roll_no.dc = nptr4->roll_no.dc;
			ptr->roll_no.year = nptr4->roll_no.year;
			ptr->roll_no.roll = nptr4->roll_no.roll;
			ptr->code = nptr4->code;
			ptr->attendance = nptr4->attendance;
			
			ptr->next = Wgrade;
			Wgrade = ptr;
		}
		nptr4 = nptr4->next;
	}
	
	printf("\n\nList of students who have attendance <=75:\n");
	print3(Wgrade);	
	
	RecordList *Pending;
	Pending = NULL;
	nptr2 = FSLptr;
	nptr4 = ARLptr;
	while (nptr2!=NULL && nptr4!=NULL)
	{
		if ( (nptr4->attendance > 75.0) && (strcmp(nptr2->status,"pending")) && (nptr4->attendance < 100.0))
		{
			RecordList* ptr;
			ptr=(RecordList*)malloc(sizeof(RecordList));
			ptr->year = nptr2->roll_no.year;
			ptr->dc = nptr2->roll_no.dc;
			ptr->roll_no = nptr2->roll_no.roll;
			ptr->attendance = nptr4->attendance;
			
			ptr->next = Pending;
			Pending = ptr;		
		}
		nptr2 = nptr2->next;
		nptr4 = nptr4->next;
	}
	printf("\n\nList of students who have attendance >75 but fee status is pending:\n");
	print2(Pending);


	DefaulterList* DLptr;
	DLptr = NULL;
	nptr2 = FSLptr;
	nptr4 = ARLptr;
	int n[5];
	for(i=0; i<5; i++) n[i]=0;
	while (nptr2!=NULL && nptr4!=NULL)
	{
		if ( (nptr4->attendance <= 75.0) || (strcmp(nptr2->status,"pending")==0) && (nptr4->attendance < 100.0))
		{
			DefaulterList* ptr;
			ptr=(DefaulterList*)malloc(sizeof(DefaulterList));
			ptr->dc = nptr2->roll_no.dc;
			ptr->roll_no = nptr2->roll_no.roll;
			ptr->attendance = nptr4->attendance;
			strcpy(ptr->status,nptr2->status);
			n[ptr->dc]++;	
			
			ptr->next = DLptr;
			DLptr = ptr;		
		}
		nptr2 = nptr2->next;
		nptr4 = nptr4->next;
	}
	printf("\n\nList of defaulter students:\n");
	print4(DLptr);
	int max=0;
	for (i = 1; i < 5; i++)
	{
		if (n[i] > n[max])
			max = i;
	}
	printf("\n\nDepartment with maximum number of defaulters: ");
	if (max == 0)  printf("Computer Sc. & Engg.\n");
	else if (max == 1)  printf("Electronics & Comm.\n");
	else if (max == 2)  printf("Electrical\n");
	else if (max == 3)  printf("Mechanical\n");
	else  printf("Civil\n");
}
