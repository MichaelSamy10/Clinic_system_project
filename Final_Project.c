#include<stdio.h>
#include"std_type.h"
void addPatient();
void editPatient (u8 pID);
void reserveSlot(u8 idIn);
void cancel_slot(u8 patient_id);
void viewPatient(u8 patient_ID);
void viewResLog();
typedef struct {
	u8 name[100];
	u8 age;
	u8 gender[100];
	u8 ID;
}patient_records;

/* Zero in slots means that the slot is reserved */
 static u8 slots[6]  = {0,1, 2, 3, 4, 5};

/* Zero in slotLog means that the slot is not reserved */
 static u8 slotLog [50] = {};

u8 add_counter=3;
patient_records arr[50]={{"Michael",20,"male",0},
						 {"Mina",25,"male",1},
						 {"Waleed",30,"male",2},
						 
	}; 

int main(){
	u8 mode,feature,flag=0;
	u32 pass,patient_id;
	while(flag==0){
		printf("\nPlease enter the mode:\n");
		printf("1 for Admin mode , 2 for User mode\n");
		printf("Your Choice: ");
		scanf("%d",&mode);
		switch(mode){
			case 1:
			printf("Enter Password: ");
				for(int i=0;i<3;i++){
					scanf("%d",&pass);
					if(pass == 1234)
						break;
					else if(i!=2)
						printf("Incorrect Password, Enter password again: ");
					else if(i==2)
						return 0;
				}
				printf("\nPlease Choose what feature you want to do: \n");
				printf("1 -->  Add new patient record\n");
				printf("2 -->  Edit patient record\n");
				printf("3 -->  Reserve a slot with the doctor\n");
				printf("4 -->  Cancel reservation\n");
				printf("5 -->  Exit \n");

				printf("Your Choice: ");
				scanf("%d",&feature);
				switch(feature){
					//Add new patient record
					case 1: 
						addPatient();
						break;
					//Edit patient record
					case 2:
						printf("Please enter patient ID: ");
						scanf("%d",&patient_id);
						editPatient(patient_id);
						break;
					case 3:
						printf("Please enter patient ID: ");
						scanf("%d",&patient_id);
					    reserveSlot(patient_id);
						break;
					case 4:
						printf("Please enter patient ID: ");
						scanf("%d",&patient_id);
						cancel_slot(patient_id);
						break;
					case 5:
						flag = 1;
						break;
					default:
						printf("Wrong choice!\n");
						break;
				}
				break;
			case 2:
				printf("\nPlease Choose what feature you want : \n");
				printf("1 -->  View patient record\n");
				printf("2 -->  View today's reservation\n");
				printf("3 -->  Exit \n");
				printf("Your Choice: ");
				scanf("%d",&feature);			
				switch(feature){
					case 1: 
						printf("Please enter your ID: ");
						scanf("%d",&patient_id);
						viewPatient(patient_id);
						break;
					case 2:
						viewResLog();
						break;
					case 3:
						flag = 1;
						break;
					default:
						printf("Wrong choice!\n");
						break;
				}
			break;
			default:
				printf("Wrong choice!\n");
		}
	}
	
	
}

void addPatient()
{
	u8 id;
	/* ID */
	printf("Enter patient ID: ");
	scanf("%d",&id);

	for(int i=0;i<add_counter;i++){
		/*ID already exist */
		if(id == arr[i].ID){
			printf("ID is already exist.\n\n");
			return ;
		}
	}
	arr[add_counter].ID = id ;
	/* Name */
	printf("Enter patient name: ");
	scanf("%s",&arr[add_counter].name);	
    /* Age */
    printf("Enter patient age: ");
	scanf("%d",&arr[add_counter].age);
    /* Gender */
	printf("Enter patient gender: ");
	scanf("%s",&arr[add_counter].gender);
    
	printf("\nNew Patient is added successfully with ID = %d\n\n",arr[add_counter].ID);
	add_counter++;
}

void editPatient (u8 pID){
	u8 i,saveI,found=0;
	for(i=0;i<add_counter;i++){
		if(pID == arr[i].ID){
			saveI = i;
			found =1;
			break;
		}
	}
	if(found==1){
		printf("Your data: \n");

		printf("ID     : %d\n", arr[saveI].ID);		
		printf("Name   : %s\n", arr[saveI].name);
		printf("Age    : %d\n", arr[saveI].age);
		printf("Gender : %s\n", arr[saveI].gender);
		
		printf("Enter edited name: ");
		scanf("%s", &arr[saveI].name);
        printf("Enter edited age: ");
	    scanf("%d", &arr[saveI].age);
        printf("Enter edited gender: ");
	    scanf("%s", &arr[saveI].gender);
	}
	else
		return;
   
}

void reserveSlot(u8 patient_ID)
{
	static u8 flag  = 0;
	static u8 choice;
	u8 i,saveI,found=0;
	for(i=0;i<add_counter;i++){
		if(patient_ID == arr[i].ID){
			saveI = i;
			found =1;
			break;
		}
	}
	if (found == 1)
	{	
		if (flag == 0)
		{
			printf("\nAvailable Slots are: \n1. 2pm to 2:30pm.\n2. 2:30pm to 3pm.\n3. 3pm to 3:30pm.\n"
				   "4. 3:30pm to 4pm.\n5. 4pm to 4:30pm.\n");
			
			printf("\nPlease choose slot number: ");
			scanf("%d", &choice);
			
			if (choice >= 1 && choice <= 5)
			{
				slots[choice] = 0;
				slotLog[patient_ID] = choice;
				flag++;
			}
			else 
			{ printf("There are only 5 slots!!\n"); }
		}
		
		else 
		{
			printf("Available slots are: \n");
			
			for (i = 1; i <= 5; i++)
			{
			   printf("%d. %d\n", i, slots[i]);
			}			  
			   
			printf("Please choose slot number: ");
			scanf("%d", &choice);
			
			if (choice >= 1 && choice <= 5)
			{
				if (slots[choice] == 0)
				{ printf("Slot is not available!!\n\n"); }
				else
				{ 
					slots[choice] = 0;
					slotLog[patient_ID] = choice;			
				}
			}
			else 
			{ printf("There are only 5 slots!!\n"); }
		}
	}
	else
	{ printf("Incorrect ID!!\n"); }

	for (i = 1; i <= 5; i++)
	{ printf("Slots1-%d: %d\n", i, slots[i]); }
	for (i = 1; i < add_counter; i++)
	{ printf("ID: %4d, Slot: %4d\n", arr[i].ID, slotLog[i]); }
	
}
void cancel_slot(u8 patient_ID){
	u8 slotNum;
	// check patient_ID
	u8 i,saveI,choice,flag=0,found=0;
	for(i=0;i<add_counter;i++){
		if(patient_ID == arr[i].ID){
			saveI = i;
			found =1;
			break;
		}
	}
	
	if (found == 1)
	{
		if (slotLog[saveI] == 0){
			printf("No previous reservation!!\n"); 
			return;
		}
		else
		{
			slotNum = slotLog[saveI];
			slots[slotNum] = slotNum;
			slotLog[saveI] = 0;
		}
	}
	else{ 
		printf("ID not exist!\n");
	return;	
	}
	
	for (u8 i = 1; i <= 5; i++){ 
		printf("Slot %d. %d\n", i, slots[i]);
	}
	
}

void viewPatient (u8 patient_ID)
{
	u8 saveI,found=0;
	for(u8 i=0;i<add_counter;i++){
		if(patient_ID == arr[i].ID){
			saveI = i;
			found =1;
			printf("SaveI = %d",saveI);
			break;
		}
	}
	if(found==1){
		printf("Your data: \n");

		printf("ID     : %d\n", arr[saveI].ID);		
		printf("Name   : %s\n", arr[saveI].name);
		printf("Age    : %d\n", arr[saveI].age);
		printf("Gender : %s\n", arr[saveI].gender);
	}
	else{
		printf("Id is not exist!");
		return;
	}
}
void viewResLog()
{
	
	for (u8 i = 0; i <add_counter; i++)
	{ printf("ID: %4d, Slot: %4d\n", arr[i].ID, slotLog[i]); }

}