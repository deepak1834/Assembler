#ifndef parsing_h__
#define parsing_h__
 
extern int convNum(char temp[]);
extern int checkAddress(char inst[]);
extern int checkComma(char oprin[],int reg);
extern int checkCharacter(char inst[]);
extern int noOfRegisters(int count,char tempoprin[],char inst[]);
extern int noOfRegistersI(int count,char tempoprin[],char inst[]);
extern int checkOpcode(char inst[],char lab[][55]);
extern int parse(char inst[],char lab[][55]);
#endif  



