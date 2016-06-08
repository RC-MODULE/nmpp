#include <stdio.h>
#include <time.h>
#include <string>
#include "profiler.h"
#include "profiler_nmcout.h"

typedef int (*tReadMemBlock)(void* host_dst, unsigned nmc_addr, unsigned size32);

unsigned map_symbol2address(char* mapfile,char* symbol){
	FILE* f;
	char str[1024];    
	f=fopen(mapfile,"rt");
	if (f==0) return 0;
	while(!feof(f)){
		fgets(str,1024,f);
		const char* where=strstr(str,symbol);
		if (where==0)
			continue;
		const char* addrpos=strstr(str,"0x");
		if (addrpos==0)
			continue;
		unsigned addr;
		sscanf(addrpos,"%X8",&addr);
		return addr;
	}
	fclose(f);
	return 0;
}

bool map_address2symbol(char* mapfile, unsigned addr, char* fullname){
	FILE* f;
	char str[1024];    
	f=fopen(mapfile,"rt");
	if (f==0) 
		return false;
	char addr_str[16];
	sprintf(addr_str,"0x%08x",addr);
	
	while(!feof(f)){
		fgets(str,1024,f);
		const char* where_addr=strstr(str,addr_str);
		if (where_addr==0)
			continue;
		if (strstr(str,":"))
			continue;
		if (strlen(str)>(where_addr-str+11))
			continue;
		sscanf(str," %s ",fullname);
		fclose(f);
		return true;
	}
	fclose(f);
	return false;
}


std::string& replace(std::string& s, const std::string& from, const std::string& to)
{
	for(size_t pos = 0; (pos = s.find(from, pos)) != std::string::npos; pos += to.size())
		s.replace(pos, from.size(), to);
	return s;
}


char* demangle (const char* mangled, char* demangled){

	int shift=(mangled[0]=='_');
	std::string str=mangled+shift;
	std::string out;

	out=replace(str,".8.8","::");
	out=replace(str,"._"," ");
	out=replace(str,".0","*");
	out=replace(str,".9",",");
	out=replace(str,".1","(");
	out=replace(str,".2",")");
	out=replace(str,".3","<");
	out=replace(str,".4",">");
	out=replace(str,".6","&");
	out=replace(str,".g","[]");
	out=replace(str,".b","=");

	std::strcpy(demangled, out.c_str());
	return demangled;
}

char* demangle2xml (const char* mangled, char* demangled){

	demangle(mangled,demangled);
	std::string str=demangled;
	std::string out;
	out=replace(str,"&","&amp;");
	out=replace(str,"<","&lt;");
	out=replace(str,">","&gt;");
	std::strcpy(demangled, out.c_str());
	return demangled;
}


unsigned profiler_head_address(char* mapfile){
	unsigned addr=map_symbol2address(mapfile,"_profiler_first");
	if (addr)
		addr+=4;
	return addr;
}

unsigned stopwatch_head_address(char* mapfile){
	unsigned addr=map_symbol2address(mapfile,"_class._C_Stopwatch._.8.8HeadStopwatch");
	return addr;
}

//! конвертиртирует строку funcname с 32-разрядными символами в стандартную 8-разрядную char строку на месте исходной. 
char* profiler_funcname2char(unsigned* funcname )	{	
	char* str86=(char*)funcname;
	for(int i=0;i<MAX_FUNCNAME_LENGTH; i++){
		str86[i]=funcname[i];
		if (str86[i]==0)
			break;
	}
	return str86;
}

int  profiler_readfunc(int addr, S_ProfilerData* prof, tReadMemBlock ReadMemBlock){
	if (ReadMemBlock(prof,addr,sizeof(S_ProfilerData)/4)!=0)
		return 0;
	profiler_funcname2char(prof->funcname);
	return prof->funcaddr;
}


void  profiler_print2tbl(S_ProfilerData* head){
	char format[]="%-12u| %-12u| %-12u| %08X| %s\n";
	printf("SUMMARY     | CALLS       | AVERAGE     | ADDRESS | FUNCTION \n");
	printf("------------+-------------+-------------+---------+----------\n");
	S_ProfilerData* profile=head;
	while(profile){
		
		printf(format,	profile->summary, 
						profile->calls,  
						profile->summary/(profile->calls+(profile->calls==0)), 
						profile->funcaddr,
						profile->funcname);
		profile=profile->next;
	};
}

S_ProfilerData* profiler_read(char* mapfile, tReadMemBlock ReadMemBlock){

	unsigned check_addr=map_symbol2address(mapfile,"_profiler_check");
	if (check_addr==0)
		return 0;
	unsigned check_val;
	if (ReadMemBlock(&check_val,check_addr,1)!=0)
		return 0;
	if (check_val!=0x600DBEEF)
		return 0;

	unsigned head_addr=profiler_head_address(mapfile);
	if (head_addr==0)
		return 0;
	
	S_ProfilerData* head_profile=new S_ProfilerData;
	S_ProfilerData* tail_profile=head_profile;
	if (profiler_readfunc(head_addr, head_profile, ReadMemBlock)==0)
		return 0;
	
	while (tail_profile->next){
		S_ProfilerData* profile= new S_ProfilerData;						// create profile
		if (profiler_readfunc((int)tail_profile->next, profile, ReadMemBlock)==0)	// read profile
			return 0;
		tail_profile->next=profile;											// link prev(tail) profile with current in x86 memspace
		tail_profile=profile;												// current profile now is tail
	} 

	return head_profile;
}

void profiler_delete(S_ProfilerData* head_profile){
	while (head_profile){
		S_ProfilerData* next_profile=head_profile->next;	
		delete head_profile;
		head_profile=next_profile;
	};
}

void profiler_print2tbl(char* mapfile, tReadMemBlock ReadMemBlock){
	char format[]="%-12u| %-12u| %-12u| %08X| %s\n";
	printf("SUMMARY     | CALLS       | AVERAGE     | ADDRESS | FUNCTION \n");
	printf("------------+-------------+-------------+---------+----------\n");

	S_ProfilerData* head_profile=profiler_read(mapfile,ReadMemBlock);
	S_ProfilerData* profile=head_profile;
	char fullname[1024];
	while (profile){
		map_address2symbol(mapfile, profile->funcaddr, fullname);
		demangle(fullname,fullname);
		printf(format,	profile->summary, 
						profile->calls,  
						profile->summary/(profile->calls+(profile->calls==0)), 
						profile->funcaddr,
						fullname);
		profile=profile->next;
	}
	profiler_delete(head_profile);
}

bool profiler_save2tbl(char* tblfile, char* mapfile, tReadMemBlock ReadMemBlock){
	FILE* f=fopen(tblfile,"wt");
	if (f==0) 
		return false;

	char format[]="%-12u| %-12u| %-12u| %08X| %s\n";
	fprintf(f,"SUMMARY     | CALLS       | AVERAGE     | ADDRESS | FUNCTION \n");
	fprintf(f,"------------+-------------+-------------+---------+----------\n");

	S_ProfilerData* head_profile=profiler_read(mapfile,ReadMemBlock);
	S_ProfilerData* profile=head_profile;
	char fullname[1024];
	while (profile){
		map_address2symbol(mapfile, profile->funcaddr, fullname);
		demangle(fullname,fullname);
		fprintf(f,format,	profile->summary, 
			profile->calls,  
			profile->summary/(profile->calls+(profile->calls==0)), 
			profile->funcaddr,
			fullname);
		profile=profile->next;
	}
	profiler_delete(head_profile);
	fclose(f);
	return true;
}


bool profiler_save2xml(char* xmlfile, char* mapfile, tReadMemBlock ReadMemBlock){
	FILE* f=fopen(xmlfile,"wt");
	if (f==0) 
		return false;

	char format[]="  <prof summary=\"%-12u\"	calls=\"%-12u\"	average=\"%-12u\"	addr=\"%08X\"	name=\"%s\"/>\n";
	//printf("<?xml version='1.0' encoding='UTF-8' ?>\n");
	fprintf(f,"<?xml version='1.0' ?>\n");
	fprintf(f,"<?xml-stylesheet type='text/xsl' href='profile.xsl'?>\n");
	fprintf(f,"<profiling version=\"1.0\">\n");


	S_ProfilerData* head_profile=profiler_read(mapfile,ReadMemBlock);
	S_ProfilerData* profile=head_profile;
	char fullname[1024];
	while (profile){
		map_address2symbol(mapfile, profile->funcaddr, fullname);
		demangle2xml(fullname,fullname);
		fprintf(f,format,	profile->summary, 
			profile->calls,  
			profile->summary/(profile->calls+(profile->calls==0)), 
			profile->funcaddr,
			fullname);
		profile=profile->next;
	}
	profiler_delete(head_profile);
	fprintf(f,"</profiling>\n");
	fclose(f);
	
	return true;
}


S_ProfilerData* stopwatch_read(char* mapfile, tReadMemBlock ReadMemBlock){

	unsigned head_addr=map_symbol2address(mapfile,"_pHeadStopwatchProfile");
	if (head_addr==0)
		return 0;
	ReadMemBlock(&head_addr,head_addr,1);
	//unsigned check_val;
	//if (ReadMemBlock(&check_val,check_addr,1)!=0)
	//	return 0;
	//if (check_val!=0x600DBEEF)
	//	return 0;
	//unsigned head_addr=profiler_head_address(mapfile);
	//if (head_addr==0)
	//	return 0;

	S_ProfilerData* head_profile=new S_ProfilerData;
	S_ProfilerData* tail_profile=head_profile;
	if (profiler_readfunc(head_addr, head_profile, ReadMemBlock)==0)
		return 0;

	while (tail_profile->next){
		S_ProfilerData* profile= new S_ProfilerData;						// create profile
		if (profiler_readfunc((int)tail_profile->next, profile, ReadMemBlock)==0)	// read profile
			return 0;
		tail_profile->next=profile;											// link prev(tail) profile with current in x86 memspace
		tail_profile=profile;												// current profile now is tail
	} 

	return head_profile;
}

void stopwatch_print2tbl(char* mapfile, tReadMemBlock ReadMemBlock){
	char format[]="%-12u| %-12u| %-12u| %08X| %s\n";
	printf("SUMMARY     | CALLS       | AVERAGE     | ADDRESS | TIMER \n");
	printf("------------+-------------+-------------+---------+----------\n");

	S_ProfilerData* head_profile=stopwatch_read(mapfile,ReadMemBlock);
	S_ProfilerData* curr_profile=head_profile;
	while (curr_profile){
		printf(format,	curr_profile->summary, 
						curr_profile->calls,  
						curr_profile->summary/(curr_profile->calls+(curr_profile->calls==0)), 
						0,
						curr_profile->funcname);
		curr_profile=curr_profile->next;
	}
	profiler_delete(head_profile);
}



	// Отключает все макросы таймеров
	//inline void stopwatch_print2tbl()	{ profiler_print2tbl(stopwatch_head()); }
	//inline void stopwatch_print2xml()	{ profiler_print2xml(stopwatch_head()); }

/*
struct STextSection{
	unsigned begin;
	unsigned end;
	char	 name[128];
	STextSection *next;
};
void map_read_sections(char* map){
	FILE* f=fopen (map,"rt");
	if (f) return;
	char str[1024];
	while(!feof(f)){
		fgets(str,1024,f);
		sscanf(" .text_%s ")
		const char* where_addr=strstr(str,addr_str);
		if (where_addr==0)
			continue;
		if (strstr(str,":"))
			continue;
		if (strlen(str)>(where_addr-str+11))
			continue;
		sscanf(str," %s ",fullname);
		fclose(f);
		return true;
	}
	fclose(f);
	return false;
}*/