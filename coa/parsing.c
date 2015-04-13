#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parsing.h"
int convNum(char temp[]){ // convert string containing numbrer to integer
	int i,num,j;
	j=1;
	num=0;
	for(i=strlen(temp)-1;i>=0;i--,j*=10)
		num +=j*(temp[i]-48);
		
	return num;
}
int checkAddress(char inst[]) //check address of input and output
{
	
	int i;
	for(i=0;i<strlen(inst);i++)
	{
		if(!((inst[0]>=48 && inst[0]<=57)||inst[0]=='-'))
		{
			printf("Invalid data  ");
			printf("%c\n",inst[i]);
			return 1;
		}
		
	}
	if((convNum(inst)>=65535 && convNum(inst)<0 )||inst[0]=='-')
	{
		printf("Address out of range   Address cannot exceed 65535  and should be greater than zero\n");
			return 1;
	}
	return 0;
}
	
int labCheck(char lab[][55],char inlabel[]){ //check label
	int i,flag;
	flag=0;
	for(i=0;lab[i][0]!='\0';i++){
		//printf("%s %s %d\n",lab[i],inlabel,i);
			if(strcmp(lab[i],inlabel)==0){
				
				flag=1;
				break;
			}
	}
	if(flag)		
		return 0;
	else{
		printf("\" %s \" \n no such label exist Please check the Label name\n",inlabel);
		return -1;
	}
}


int checkComma(char oprin[],int reg) //check valid registers
{										//oprin having string r1,r2,r3
	int i,status=0;
	if(reg==1)
	{
		if((!oprin[0]>=48 && oprin[0]<=57))
		{
			printf("Invalid Register No.  ");
			printf("%c\n",oprin[i]);
			return 2;
		}
		for(i=1;i<strlen(oprin);i++)
		{
			if(!(oprin[i]==32))
			{
				printf("Invalid Register No.  ");
				printf("%c\n",oprin[i]);
				return 2;
			}
		}
	}
	if(reg==2)
	{
		if((!oprin[0]>=48 && oprin[0]<=53))
		{
			printf("Invalid Register No.  ");
			printf("%c\n",oprin[i]);
			return 2;
		}
		for(i=1;i<strlen(oprin);i++)
		{
			if(!(oprin[i]==32))
			{
				printf("Invalid Register No.  ");
				printf("%c\n",oprin[i]);
				return 2;
			}
		}
	}
	return status;
}


int checkCharacter(char inst[]) //remove special character and inst contains whole instructions
{								
	int i;
	for(i=0;inst[i]!='\0';i++){
		if(!((inst[i]>=97 && inst[i]<=122) || (inst[i]>=65 && inst[i]<=90) ||(inst[i]>=48 && inst[i]<=57) || inst[i]==32 || inst[i]==44 || inst[i]==':' || inst[i]=='-'))
		{
			printf("%s Invalid Instruction\n",inst);
			return 1;
		}
	}
	return 0;
}
int noOfRegisters(int count,char tempoprin[],char inst[]) //check invalid character and no. of registers
{
			char temp[35],reg;
			int i,status=0,j;
				
				for(i=0;i<strlen(tempoprin);i++)
				{
					while(tempoprin[i]==' ')
					i++;
					if(tempoprin[i]==82)
					{
						count--;
						reg=1;
					}
					else if(tempoprin[i]==70)
					{
						count--;
						reg=2;
					}
					else
					{
						printf("Invalid character  ");
						printf("%c\n",tempoprin[i]);
						return 4 ;
					}
					j=0;
					i++;
					while(tempoprin[i]!=',' && count!=0)
					{
						temp[j++]=tempoprin[i];
						i++;
					}
					temp[j]='\0';
					while(tempoprin[i]!='\0' && count==0)
					{
						temp[j++]=tempoprin[i];
						i++;
					}
										temp[j]='\0';
					//printf("%s\n",temp);
					status=checkComma(temp,reg);
					if(status!=0)
					return status;
				}
				if(count!=0)
				{
					printf("Invalid No. of registers  ");
					printf("%c\n",tempoprin[i]);
					return 3;
				}
			
	return status;
}
int noOfRegistersI(int count,char tempoprin[],char inst[])   ////check invalid character and no. of registers with immediate value
{

			char temp[35];
			char imm[105];
			int dcount;
			dcount =count;
			int rflag;
		
			int i,status=0,j,data,flag;
				
				for(i=0;i<strlen(tempoprin);i++)
				{
						rflag=0;
					while(tempoprin[i]==' ')
					i++;
					if(tempoprin[i]==82 || tempoprin[i]==70){
						count--;
						if(tempoprin[i]==82)
						rflag=1;
						else
						rflag=2;
					}
					else
					{
						printf(" Invalid registers  \n");
						printf("%c\n",tempoprin[i]);
						return 4 ;
					}
					j=0;
					i++;
					while(tempoprin[i]!=',')
					{
						temp[j++]=tempoprin[i];
						i++;
					}
					temp[j]='\0';
				
						if(count>=0){
							//printf("count %d ",count);
							if(temp[0]!='\0')
							status=checkComma(temp,rflag);
							else
							status =2;
							//printf("%s %d\n",temp, status);
						}
					
					if(status==2)
						return 2;
					if(count==0){
						
						i++;
					
					}
					while(tempoprin[i]==' ' && count==0){
						
						i++;
					}
					flag=1;
					while(tempoprin[i]!='\0' &&  count==0)
					{
							//printf("hiiii  %c\n",tempoprin[i]);
						
						if(tempoprin[i]>=48 && tempoprin[i]<=57)
						imm[j++]=tempoprin[i];
						else if((strcmp(inst,"LDI")==0 || strcmp(inst,"STI")==0 ) && tempoprin[i]=='-' )
							flag=0;
						i++;
					}
					imm[j]='\0';
					if(count==0){
						if(flag)
						data=convNum(imm)%65535;
						else{
							printf("Invalid Data\n");
							return 1;
						}
						
					}
				}
				if(count!=0)
				{
					printf("Invalid No. of registers  ");
					printf("%c\n",tempoprin[i]);
					return 3;
				}
			
	return status;
}
int checkOpcode(char inst[],char lab[][55])
{
	FILE *instruct;
	char tempinuser[105],tempop[105],instin[105],tempinst[105],tempoprin[105],temp,count; 
	int i=0,j,status=0,flag=0,x,k,linecounter;
	char *ptr = strchr(inst,':');
			//if the instruction is without lable  or call
			//printf("%s\n",inst);
			if(ptr==NULL)
			{
				
				flag=0;
				for(i=0;inst[i]!=' ' && inst[i]!='\n';i++)
				{
					tempinuser[i]=inst[i];      //tempiuser[] is array for the first part of instruction  i.e. "add"
				}
				tempinuser[i]='\0';
				
			}
			else
			{
				flag=0;
				i=(int)(ptr-inst) + 1;
				while(inst[i]==' ')
					i++;
				x=i; //here value of i  is stored to use it extract the operend;
				k=0;
				for(;inst[i]!=' ';i++)
				{
					tempinuser[k++] = inst[i];      //tempiuser[] is array for the first part of instruction  i.e. "add"
				}
				tempinuser[k]='\0';
				
			}
				instruct = fopen("inst.txt","r");
	
				flag=0;
				
				
			
				char c;
				while(flag==0 && (c=fgetc(instruct))!=EOF)
				{
					
					i=0;
					if(i==0 && c==' ')
					continue;
					if(c!='\0' && c!='\n'){
						instin[i++]=c;
						while((c=fgetc(instruct))!='\n' && c!='\0'){
						instin[i++] =c;
						}
						instin[i]='\0';
						
						//here instin[] contains the  opcode list defined by the isa designer
						for(i=0;instin[i]!=' ' && instin[i]!='\n';i++){
							tempinst[i] = instin[i];
						}
						tempinst[i]='\0';
						
						j=0;

					//	printf("%s %d %d\n",tempinst,strlen(tempinst),strlen(tempinuser));
						//here tempinst is the first part of instruction (i.e. "add") from instruction list defined by the isa designer
						if(strcmp(tempinst,tempinuser)==0)// tempinuser contains add sub etc
						{
														

							
							flag=1;
							int counter;
							counter =0;
							for(i=i+1;instin[i]!='\0';i++){
								tempop[j++]=instin[i];	//tempop contains the corresponding opcode from instruction file operands 01001010 etc
							}
							//printf("%c\n",instin[i-1]);
							tempop[j]='\0';
					
							//if the instruction is not immidiate type
							//if(tempinuser[strlen(tempinuser)-1]!='I'){
									if(ptr!=NULL)
										i=strlen(tempinuser)+ x  ;
									else
										i=strlen(tempinuser);
									while(inst[i]==' ')
										i++;
									j=0;
									for(;inst[i]!='\n';i++){
										tempoprin[j++]= inst[i]; //tempoprin contains r1,r2,r3
									}
									tempoprin[j] = '\0';
								//printf("%s\n",inst);
								//printf("%d\n",strlen(tempop));
									temp=(32-strlen(tempop))/16;
									count=((32-strlen(tempop))%16)/4;
									if(temp==1){
										
										if(tempinuser[0]!='J' && tempinuser[0]!='C' && tempinuser[0]!='I' && tempinuser[0]!='O' && strcmp(tempinuser,"STI")!=0 && strcmp(tempinuser,"LDI")!=0 )
										status=noOfRegistersI(count,tempoprin,tempinuser);
										else if(tempinuser[0]=='I' || tempinuser[0]=='O')
										  status=checkAddress(tempoprin);
										else if(strcmp(tempinuser,"STI")==0 || strcmp(tempinuser,"LDI")==0){
											//	printf("%s\n",tempoprin);
											//status=noOfRegistersI(1,tempoprin,tempinuser);
											return 0;
										}
										else if(tempinuser[0]=='J' || tempinuser[0]=='C'){
										
											status =labCheck(lab,tempoprin);
										}
										
									}
									else
									status=noOfRegisters(count,tempoprin,tempinuser);
									
						}
					}			
				} 
		
	fclose(instruct);

	return status;
}		




int parse(char inst[],char lab[][55]){
	
			int status;
			status =0;
			status =checkCharacter(inst);
			//printf("%s\n",inst);
			if(status==0)
			status=checkOpcode(inst,lab);
			//printf("%d\n",status);
			return status;
	
}

								
/*
int main()
{
	FILE *input;
	char inst[105],tempinst[105];
	
	char c;
	int i,status=1,counter;
	counter=0;
	input    = fopen("code.txt","r");
	while((c=fgetc(input))!=EOF)
	{
	
		i=0;
		if(i==0 && c==' ')
		continue;
		if(c!='\0' && c!='\n'){
				counter++;
			inst[i++]=c;
			while((c=fgetc(input))!='\n' && c!='\0'){
				inst[i++] =c;
			}
			inst[i]='\0';
		
			for(i=0;inst[i];i++){
				if(inst[i]>=97 && inst[i]<=122)
					inst[i] = toupper(inst[i]);
			}
		
			
			checkCharacter(inst);
			printf("%d . %s\n",counter,inst);
			status=checkOpcode(inst);
			
			
			printf("%d\n",status);
		}
	}
	fclose(input);
	return 0;
}
*/


