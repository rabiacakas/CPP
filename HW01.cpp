/*****************************************************************************/
/*																			 */
/*	HW01_141044042_RABİA_ÇAKAS												 */
/*																			 */
/*	main.cpp																 */
/*----------																 */
/*	Created on 17/10/2016 by Rabia Çakas									 */
/*																			 */
/*	Description																 */
/*	The main.cpp will simulate simple CPU. The CPU has only 5 registers		 */
/* (R1, R2, R3, R4, R5) and no other memory.The CPU has a small set of 	 	 */
/* instructions as decribed below. 											 */
/*	MOV																		 */
/*	ADD																		 */
/*	SUB																		 */
/*	JMP																		 */
/*	HLT																		 */
/*****************************************************************************/

/*****************************************************************************/
/*					Includes												 */
/*****************************************************************************/

#include<iostream>
#include<string>
#include<fstream>

using namespace std;
/*****************************************************************************/
/*					FUNCTION IMPLEMENTATIONS								 */
/*****************************************************************************/

/*****************************************************************************/
/*	void cleaner(string &line);												 */
/*-----------------------------												 */
/* This function will erase the all space in line.							 */
/*																			 */
/*****************************************************************************/
void cleaner(string &line);

void seperate(string &line, string &instruction, string &parses1);

void assignJmpOrPrn(string &line, string &instruction, string &regs, string &parses1);

int exitcontrol(string &instruction, string &regs, string &parses2, string &line);

int callingFunctions(string &instruction, string &regs, string &parses1, string &parses2, string &line, int *reg,ifstream &input, char *option);
/*****************************************************************************/
/*	void lowerToUpper(string &line);										 */
/*-----------------------------												 */
/* Tum harfleri kucukten buyuge cevirir.									 */
/*																			 */
/*****************************************************************************/
void lowerToUpper(string &line);
/*****************************************************************************/
/* int controlReg(string &regs, string &instruction);						 */
/*-----------------------------												 */
/* Bu fonksiyon regs ve instruction stringlerini parametre olarak alir.		 */
/* Eger instruction dan sonra gelen kisim register sa 1, constant sa		 */ 
/* 0 dondurur. Instruction a gore yanlis bir durum varsa -1 return eder.	 */
/*																			 */
/*****************************************************************************/
int controlReg(string &regs, string &instruction);
/*****************************************************************************/
/* int controlTwo(string &parses2, string &instruction);					 */
/*-----------------------------												 */
/* Bu fonksiyon parses2 ve instruction stringlerini parametre olarak alir.	 */
/* Eger instruction dan sonra gelen kisim register sa 1, constant sa		 */ 
/* 0 dondurur. Instruction a gore yanlis bir durum varsa -1 return eder.	 */
/*																			 */
/*****************************************************************************/
int controlTwo(string &parses2, string &instruction);
/*****************************************************************************/
/* int myStoi(string &parses2);												 */
/*-----------------------------												 */
/* Bu fonksiyon parses2 stringini parametre olarak alir.	 				 */
/* Stringi integer degerine donusturup return eder.							 */ 
/*																			 */
/*****************************************************************************/
int myStoi(string &parses2);
/*****************************************************************************/
/* int Move(string &regs, string &parses2, string &instruction, int *reg);	 */
/*-----------------------------												 */
/* Bu fonksiyon regs, parses2, instruction ve reg stringini parametre olarak */
/* alir.Insturction dan sonra gelen kismin ne oldugunu anlamak icin 		 */
/*controlReg e gonderir, diger parcanın ne oldugunu anlamak icin controlTwo	 */
/* fonksiyonunu cagirir ve parcalarin durumlarina göre reg-to-reg yada		 */
/* reg-constant icin move islemini yapar.								     */ 
/*     																		 */
/*****************************************************************************/
int Move(string &regs, string &parses2, string &instruction, int *reg);
/*****************************************************************************/
/* 	int Add(string &regs, string &parses2, string &instruction, int *reg);   */
/*-----------------------------												 */
/* Bu fonksiyon regs, parses2, instruction ve reg stringini parametre olarak */
/* alir.Insturction dan sonra gelen kismin ne oldugunu anlamak icin 		 */
/*controlReg e gonderir, diger parcanın ne oldugunu anlamak icin controlTwo	 */
/* fonksiyonunu cagirir ve parcalarin durumlarina göre reg-to-reg yada		 */
/* reg-constant icin add islemini yapar.								     */ 
/*     																		 */
/*****************************************************************************/
int Add(string &regs, string &parses2, string &instruction, int *reg);
/*****************************************************************************/
/* 	int Sub(string &regs, string &parses2, string &instruction, int *reg);   */
/*-----------------------------												 */
/* Bu fonksiyon regs, parses2, instruction ve reg stringini parametre olarak */
/* alir.Insturction dan sonra gelen kismin ne oldugunu anlamak icin 		 */
/*controlReg e gonderir, diger parcanın ne oldugunu anlamak icin controlTwo	 */
/* fonksiyonunu cagirir ve parcalarin durumlarina göre reg-to-reg yada		 */
/* reg-constant icin sub islemini yapar.								     */ 
/*     																		 */
/*****************************************************************************/
int Sub(string &regs, string &parses2, string &instruction, int *reg);
/*****************************************************************************/
/* 	int prn(string &regs, int *reg);									     */
/*-----------------------------												 */
/* Bu fonksiyonla iki durum kontrol edilir. Instruction dan sonra gelen kisim*/
/* eger register sa reg arrayindeki degeri basar. Eger constant degerse      */ 
/* constant ı basar.   														 */
/*****************************************************************************/
int prn(string &regs, int *reg, char *option);
/*****************************************************************************/
/* 	int setIns(string &instruction, string &regs, string &parses2, 			 */
/*string &line, int *reg,ifstream &input);								     */
/*----------------------------------------									 */
/* Bu fonksiyon gelen instruction a gore islem yapacak fonksiyonlari cagirir.*/
/*    																		 */
/*****************************************************************************/
int setIns(string &instruction, string &regs, string &parses2, string &line, int *reg,ifstream &input, char *option);
/*****************************************************************************/
/* 	int jmp(string &regs, string &line, string &instruction, string &parses2,*/
/* int *reg, ifstream &input);												 */
/*----------------------------------------									 */
/* Bu fonksiyon once parcalarin ne oldugunu anlar, eger instruction dan sonra*/
/* gelen kisim register sa ve ilgili register degeri 0 sa ikinci kisimdaki	 */ 
/* lineaddress e gider ve instruction set o satirdan devam eder				 */
/* Fakat ilk kisim register degilse bir constant degerse o satiri gidecegi   */
/* lineaddress olarak alir ayni sekilde instruction set o satirdan devam eder*/
/*																		 	 */
/*****************************************************************************/
int jmp(string &regs, string &line, string &instruction, string &parses2, int *reg, ifstream &input);
/*****************************************************************************/
/* 	int hlt(string &instruction);								 			 */
/*----------------------------------------									 */
/* Bu fonksiyon eger gelen instruction halt ise calisir programi sonlandirir.*/
/*    																		 */
/*****************************************************************************/
int hlt(string &instruction);


int main(int argc, char** argv)
{
	int indexc;
	
		ifstream input;
		string line, instruction, parses1, regs, parses2;
		char *option (argv[2]);
		int k, c;
		int reg[5]={0, 0, 0, 0, 0};
		input.open(argv[1]);
		
	if(argc != 3)
		cerr << "Arguments can be that form: ./execuatablefile file.txt option." << endl;
	else{
		if(input.is_open()){
			while(getline(input, line))
			{
				cleaner(line);
				lowerToUpper(line);
				string temp=line;
				seperate(line, instruction, parses1);
				assignJmpOrPrn(line, instruction, regs, parses1);
				exitcontrol(instruction, regs, parses2, line);
				callingFunctions(instruction,regs,parses1, parses2,line,reg,input,option);
				
			}
			
		}
	}

	return 0;
}
void cleaner(string &line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if(line[i] == ' '){
			line.erase(i,1);
			i--;
		}
	}
	for (int j = 0; j < line.size() ; j++)
	{
		if(line[j] == ';'){
			line.erase(j);
			j--;
		}
	}
}
void lowerToUpper(string &line){

	int size, p;
	size=line.length();
	for(p=0; p<size; p++)
	{
		if(line[p]>='a' && line[p]<='z')
		{
			line[p]-='a'- 'A';
				
		}
	}

}
int controlReg(string &regs, string &instruction){
	
	int k;
	if ((regs[0]=='R') && (regs.compare("R1")==0 || regs.compare("R2")==0 || regs.compare("R3")==0 || regs.compare("R4")==0 || regs.compare("R5")==0 )){
			
			return 1;
	}

	if(instruction.compare("PRN")==0 || instruction.compare("JMP")==0)
	{
		k=myStoi(regs);
		return 0;
	}

	if(((regs[0]!='R') && (instruction.compare("PRN")!=0 )) && ((regs[0]!='R') && (instruction.compare("JMP")!=0)) && (instruction.compare("HLT")!=0))
	{
			cerr<< "WRONG REGISTER NUMBER"<<endl;
			return -1;
	}
	
}
int controlTwo(string &parses2, string &instruction){
	int t;
	
	if((parses2[0]=='R') && (parses2.compare("R1")==0) || (parses2.compare("R2")==0) || (parses2.compare("R3")==0) || (parses2.compare("R4")==0) || (parses2.compare("R5")==0))
	{
		return 1;
	}

	else if(parses2[0]!='R'){
		t=myStoi(parses2);
		return 0;
	}	

	else if(instruction.compare("PRN")!=0)
	{
		cerr<< "WRONG REGISTER NUMBER"<<endl;
		return -1;
	}
	
}
int myStoi(string &parses2)
{
    int convert;
 	convert=0;
    for(int i=0; parses2[i] !='\0'; ++i)
	{
        convert=(convert*10 +parses2[i] - '0');
	}

    return convert;
}

int Move(string &regs, string &parses2, string &instruction, int *reg){
	int status1, status2, i, k, t;
	string parses3,regs2;
	
	status1=controlReg(regs, instruction);
	status2=controlTwo(parses2, instruction);

	if(status1==1 && status2==1){
		
		parses3=parses2.erase(0, 1);
		regs2=regs.erase(0, 1);
		k=myStoi(parses3);
		t=myStoi(regs2);
		reg[k-1]=reg[t-1];
		return 0;
		}

	if(status1==1 && status2==0){

		i=myStoi(parses2);
		reg[regs[1]-'1']=i;
		return(reg[regs[1]-'1']);
		return 0;
		
	}
	
	
	return 0;
}
int Add(string &regs, string &parses2, string &instruction, int *reg){
	
	int status1, status2, i, k, t;
	string parses3, regs2;
	status1=controlReg(regs, instruction);
	status2=controlTwo(parses2, instruction);

	if(status1==1 && status2==1){
		parses3=parses2.erase(0, 1);
		regs2=regs.erase(0, 1);
		k=myStoi(parses2);
		t=myStoi(regs);
		reg[t-1] += reg[k-1];
		return 0;
		
	}
	if(status1==1 && status2==0){

		i=myStoi(parses2);
		reg[regs[1]-'1'] += i;
		return(reg[regs[1]-'1']);
		return 0;
		
	}
	
	return 0;
}

int Sub(string &regs, string &parses2, string &instruction, int *reg){
	
	int status1, status2, i, k, t;
	string parses3, regs2;
	status1=controlReg(regs, instruction);
	status2=controlTwo(parses2, instruction);

	if(status1==1 && status2==1){
		parses3=parses2.erase(0, 1);
		regs2=regs.erase(0, 1);
		k=myStoi(parses3);
		t=myStoi(regs2);
		reg[t-1] -= reg[k-1];
		return 0;
		
	}
	if(status1==1 && status2==0){

		i=myStoi(parses2);
		reg[regs[1]-'1'] -= i;
		return(reg[regs[1]-'1']);
		return 0;
		
	}
	
	return 0;
}
int prn(string &regs, int *reg, char *option){
	if((*option=='0') || (*option=='1')){
		if(regs[0]=='R')
		{
			if(regs.compare("R1")==0)
				cout<<reg[0]<< endl;

			else if(regs.compare("R2")==0)
				cout<<reg[1]<< endl;

			else if(regs.compare("R3")==0)
				cout<<reg[2]<< endl;

			else if(regs.compare("R4")==0)
				cout<<reg[3]<< endl;

			else if(regs.compare("R5")==0)
				cout<<reg[4]<< endl;
	
			else
			{
				cout<<"prn-->>"<<"WRONG REGISTER ENTRY"<<endl;
				return -1;
			}
		}
	}
		
	if(regs[0]!='R')
		cout<<regs<< endl;

	return 0;
}
int setIns(string &instruction, string &regs, string &parses2, string &line, int *reg,ifstream &input, char *option){

	if(instruction.compare("MOV")==0)
	{
		Move(regs, parses2, instruction, reg);
	}
	if(instruction.compare("ADD")==0)
	{
		Add(regs, parses2, instruction, reg);
	}
	if(instruction.compare("SUB")==0)
	{
		Sub(regs, parses2, instruction, reg);
	}
	if(instruction.compare("PRN")==0)
	{
		prn(regs, reg, option);
	}
	if(instruction.compare("JMP")==0)
	{
		jmp(regs, line, instruction, parses2, reg,input);
	}
	if(instruction.compare("HLT")==0)
	{
		hlt(instruction);
	}
	return 0;
}
int jmp(string &regs, string &line, string &instruction, string &parses2, int *reg, ifstream &input){

	int status1, status2, i, k, t;
	string parses3,regs2, parses1;

	status1=controlReg(regs, instruction);
	status2=controlTwo(parses2, instruction);
	t=myStoi(parses2);
	
	if(status2==1){
		cerr<< "WRONG ENTRY"<<endl;
		return -1;
	}
	if(regs[0]!='R')
	{
		t=myStoi(regs);
	}
	//jmp reg, lineaddress
	if((status1==1 && status2==0) && (regs[0]=='R')){
		if(((regs.compare("R1")==0) && (reg[0]==0)) || ((regs.compare("R2")==0) && (reg[1]==0)) || ((regs.compare("R3")==0) && (reg[2]==0)) 			|| ((regs.compare("R4")==0) && (reg[3]==0)) || ((regs.compare("R5")==0) && (reg[4]==0)))
		{
			input.seekg(0);
			for(i=0; i<t-1; i++)
			{
				
				getline(input, line);
				if(i==t)
					break;
				
			}
					
		}	
	}
	//jmp lineaddress
	if(status1==0)
	{
		input.seekg(0);
		for(i=0; i<t-1; i++)
		{
			getline(input, line);
			if(i==t)
				break;
		
		}
		
	}

}
int hlt(string &instruction){

	if(instruction.compare("HLT")==0){
		cout<<"HALT"<<endl;
		return 0;
	}

	
}
void seperate(string &line, string &instruction, string &parses1){

	instruction = line.substr(0, 3);
	parses1= line.erase(0,3);
	
	return;
}

void assignJmpOrPrn(string &line, string &instruction, string &regs, string &parses1){
	int indexc;

	indexc=line.find_first_of(',');
	if((indexc== -1 && instruction.compare("JMP")==0) || (indexc== -1 &&  instruction.compare("PRN")==0)){
			regs=parses1;
	}
	regs = line.substr(0, indexc);
	return;
}
int exitcontrol(string &instruction, string &regs, string &parses2, string &line){

	int cntrl1=controlReg(regs, instruction);
	int cntrl2=controlTwo(parses2, instruction);
	if(cntrl1==-1 || cntrl2==-1){
		return -1;
	}

	parses2= line.erase(0, 3);
			
	return 0;

}
int callingFunctions(string &instruction, string &regs, string &parses1, string &parses2, string &line, int *reg,ifstream &input, char *option){

	setIns(instruction, regs, parses2, line, reg, input, option);
	if(*option=='1')
	{
		cout<<instruction<<" "<< parses1;
		cout<<"- "<<"R1:"<<reg[0]<<" "<<"R2:"<<reg[1]<<" "<<"R3:"<<reg[2]<<" "<<"R4:"<<reg[3]<<" "<<"R5:"<<reg[4]<<endl;
	}
	else if(*option=='0')
	{
			
	}

	return 0;

}











