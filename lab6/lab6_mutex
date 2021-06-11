#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;
pthread_mutex_t mutex;

int gpio_all;

int gpio_export(unsigned int gpio){
    int fd, len;
    char buf[64];
    fd=open("/sys/class/gpio/export", O_WRONLY);
    if(fd<0){
        perror("gpio/export");
        return fd;
    }
    len=snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_unexport(unsigned int gpio){
    int fd, len;
    char buf[64];
    fd=open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd<0){
        perror("gpio/unexport");
        return fd;
    }
    len=snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_set_dir(unsigned int gpio, string dir_status){
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
    fd=open(buf, O_WRONLY);
    if(fd<0){
        perror("gpio/direction");
        return fd;
    }
    if(dir_status=="out"){
        write(fd, "out", 4);
    }else{
        write(fd, "in", 3);}
    close(fd);
    return 0;
}

int gpio_set_value(unsigned int gpio, int value){
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
    fd=open(buf, O_WRONLY);
    if(fd<0){
        perror("gpio/set-value");
        return fd;
    }
    if(value==0){
        write(fd, "0", 2);
    }else{
        write(fd, "1", 2);}
    close(fd);
    return 0;
}

void *setGPIO(string input, int i){
    ///
    ///lock
    pthread_mutex_lock(&mutex);
    ///
    ///全域變數gpio_all會被lock
    if(i==0){
        gpio_all=396;
    }else if(i==1){
        gpio_all=255;
    }else if(i==2){
        gpio_all=428;
    }else if(i==3){
        gpio_all=427;
    }
    ///
    ///決定好gpio_all之後，開啟led燈
	if(input[i]=="1"){
        gpio_set_value(gpio_all, 1);
	}else if(input[i]=="0"){
        gpio_set_value(gpio_all, 0);
    }
    ///
    ///unlock
    pthread_exit(NULL);
}

void *setGPIO_u(string input, int i){
    ///
    ///lock
    pthread_mutex_lock(&mutex);
    ///
    ///全域變數gpio_all會被lock
    if(i==0){
        gpio_all=396;
    }else if(i==1){
        gpio_all=255;
    }else if(i==2){
        gpio_all=428;
    }else if(i==3){
        gpio_all=427;
    }
    ///
    ///決定好gpio_all之後，開啟led燈
	if(input[i]=="0"){
        gpio_set_value(gpio_all, 1);
	}else if(input[i]=="1"){
        gpio_set_value(gpio_all, 0);
    }
    ///
    ///unlock
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){
    pthread_mutex_init(&mutex, 0);                  //初始化mutex
    pthread_t thread1, thread2, thread3, thread4;   //建立子程序
    ///
    ///first, export all gpio
    gpio_export(396);
    gpio_export(255);
    gpio_export(428);
    gpio_export(427);

    ///
    ///start to shine
    string input1=argv[1], input2=argv[2];
    int time=2*stoi(input2);
    for(time; time>=0; time--){
        if(time%2==0){
            pthread_create(&thread1, NULL, setGPIO(input1, 0), 0);
            pthread_create(&thread2, NULL, setGPIO(input1, 1), 0);
            pthread_create(&thread3, NULL, setGPIO(input1, 2), 0);
            pthread_create(&thread4, NULL, setGPIO(input1, 3), 0);
        }else{
            pthread_create(&thread1, NULL, setGPIO_u(input1, 0), 0);
            pthread_create(&thread2, NULL, setGPIO_u(input1, 1), 0);
            pthread_create(&thread3, NULL, setGPIO_u(input1, 2), 0);
            pthread_create(&thread4, NULL, setGPIO_u(input1, 3), 0);
        }
        sleep(300);
    }
    pthread_mutex_destroy(&mutex);

    ///
    ///last, export all gpio
    gpio_unexport(396);
    gpio_unexport(255);
    gpio_unexport(428);
    gpio_unexport(427);
    return 0;
}
