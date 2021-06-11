#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

void setGPIO(unsigned int gpio, string status)
{
	int io;
	io=open("/dev/demo", O_WRONLY);
	if(io<0)
	{
		perror("gpio error");
		return;
	}
	char buf[10]={0};
	if(status=="on")
	{
		strcpy(buf, (to_string(gpio)+"1").c_str());
	}
	else
	{
		strcpy(buf, (to_string(gpio)+"0").c_str());
	}

	/*if(buf == "3960")
		cout << "LED1 status: 0"<<endl;
	else if(buf == "3961")
		cout << "LED1 status: 1"<<endl;
	else if(buf == "2550")
		cout << "LED2 status: 0"<<endl;
	else if(buf == "2551")
		cout << "LED2 status: 1"<<endl;
	else if(buf == "4280")
		cout << "LED3 status: 0"<<endl;
	else if(buf == "4281")
		cout << "LED3 status: 1"<<endl;
	else if(buf == "4270")
		cout << "LED4 status: 0"<<endl;
	else if(buf == "4271")
		cout << "LED4 status: 1"<<endl;
*/
	

	cout << buf << endl;
	write(io, buf, 5);
	close(io);
	return;
}

void read_status(unsigned int gpio){
	int io;
	io=open("/dev/demo", O_WRONLY);
	if(io<0)
	{
		perror("gpio error");
		return;
	}
	char buf[10]={0};
	strcpy(buf, (to_string(gpio)).c_str());
	read(io, buf, 1);
	cout << buf <<" status: 0"  << endl;
	close(io);
	return;
}

int main(int argc, char *argv[]){
    string input1=argv[1], input2=argv[2];
    int id;
    if(input1=="LED1"){
        id=396;
    }else if(input1=="LED2"){
        id=255;
    }else if(input1=="LED3"){
        id=428;
    }else if(input1=="LED4"){
        id=427;
    }
    
    if(input2=="on" || input2=="off"){
    	setGPIO(id, input2);
    }else if(input2 == "status"){
    	read_status(id);
    }
    
}
