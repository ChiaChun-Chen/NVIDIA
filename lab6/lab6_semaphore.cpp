#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;
sem_t semaphore, semaphore2;

int gpio_all;
int count=0;

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

void *setGPIO(void *argv){
    sem_wait(&semaphore);             //等待工作
    string input=*(string*)argv;    //進行類型轉換
    for(int j=0; j<=3; j++){
    int i=count;
    count++;
    ///
    ///全域變數gpio_all
    if(i%4==0){
        gpio_all=396;
    }else if(i%4==1){
        gpio_all=255;
    }else if(i%4==2){
        gpio_all=428;
    }else if(i%4==3){
        gpio_all=427;
    }
    ///
    ///決定好gpio_all之後，開啟led燈
    printf("input[%d]=%c\n", i, input[i]);
	if(input[i%4]=='1'){
        gpio_set_value(gpio_all, 1);
        printf("gpio%d=1, count=%d\n", gpio_all, count-1);
	}else if(input[i%4]=='0'){
        gpio_set_value(gpio_all, 0);
        printf("gpio%d=0, count=%d\n", gpio_all, count-1);
    }
    }
    pthread_exit(NULL);
}

void *setGPIO_u(void *argv){
    sem_wait(&semaphore2);             //等待工作
    string input=*(string*)argv;    //進行類型轉換
    for(int j=0; j<=3; j++){
    int i=count;
    count++;
    ///
    ///全域變數gpio_all
    if(i%4==0){
        gpio_all=396;
    }else if(i%4==1){
        gpio_all=255;
    }else if(i%4==2){
        gpio_all=428;
    }else if(i%4==3){
        gpio_all=427;
    }
    ///
    ///決定好gpio_all之後，開啟led燈
    printf("input[%d]=%c\n", i, input[i]);
	if(input[i%4]=='0'){
        gpio_set_value(gpio_all, 1);
        printf("gpio%d=1, count=%d\n", gpio_all, count-1);
	}else if(input[i%4]=='1'){
        gpio_set_value(gpio_all, 0);
        printf("gpio%d=0, count=%d\n", gpio_all, count-1);
    }
    ///
    ///unlock
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){
    sem_init(&semaphore, 0, 0);                  //初始化號誌
    sem_init(&semaphore2, 0, 0);
    pthread_t t1, t2;   //建立子程序
    string input1=argv[1], input2=argv[2];
    int time=2*stoi(input2);
    printf("time=%d\n", time);


    ///
    ///first, export all gpio
    gpio_export(396);
    gpio_export(255);
    gpio_export(428);
    gpio_export(427);
    gpio_set_dir(396, "out");
    gpio_set_dir(255, "out");
    gpio_set_dir(428, "out");
    gpio_set_dir(427, "out");

    ///
    ///start to shine

    for(time; time>=0; time--){
        if(time%2==0){printf("into gpio396\n");pthread_create(&t1, NULL, setGPIO, (void*)&input1);
            sem_post(&semaphore);printf("into gpio255\n");//pthread_create(&t1, NULL, setGPIO, (void*)&input1);
            //sem_post(&semaphore);printf("into gpio428\n");pthread_create(&t1, NULL, setGPIO, (void*)&input1);
            //sem_post(&semaphore);printf("into gpio427\n");pthread_create(&t1, NULL, setGPIO, (void*)&input1);
            //sem_post(&semaphore);
        }else{printf("396.time=%d\n", time);pthread_create(&t2, NULL, setGPIO_u, (void*)&input1);
            sem_post(&semaphore2);printf("255.time=%d\n", time);//pthread_create(&t2, NULL, setGPIO_u, (void*)&input1);
            //sem_post(&semaphore2);printf("428.time=%d\n", time);pthread_create(&t2, NULL, setGPIO_u, (void*)&input1);
            //sem_post(&semaphore2);printf("427.time=%d\n", time);pthread_create(&t2, NULL, setGPIO_u, (void*)&input1);
            //sem_post(&semaphore2);
        }
        sleep(10);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    ///
    ///close LED
    gpio_set_value(396, 0);
    gpio_set_value(255, 0);
    gpio_set_value(428, 0);
    gpio_set_value(427, 0);

    ///
    ///last, export all gpio
    gpio_unexport(396);
    gpio_unexport(255);
    gpio_unexport(428);
    gpio_unexport(427);
    return 0;
}
