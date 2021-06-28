#include "final_lab.h"
#include "ui_final_lab.h"
#include <iostream>
#include <QTime>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;
sem_t sem1, sem2;
pthread_t t1, t2, t3, t4;
int light1, light2, light3, light4;
int time_all=0;
QString time_string="";

final_lab::final_lab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::final_lab)
{
    ui->setupUi(this);
}

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

void* set1(void *arg){
    sem_wait(&sem1);
    if(light1==1){
        printf("set1_1");
        gpio_set_value(396, 1);
    }else{
        printf("set1_0");
        gpio_set_value(396, 0);
    }
    pthread_exit(NULL);
}
void* setu_1(void *arg){
    sem_wait(&sem2);
    if(light1==1){
        printf("set1_0");
        gpio_set_value(396, 0);
    }else{
        printf("set1_1");
        gpio_set_value(396, 1);
    }
    pthread_exit(NULL);
}

void* set2(void *arg){
    sem_wait(&sem1);
    if(light2==1){
        printf("set2_1");
        gpio_set_value(255, 1);
    }else{
        printf("set2_0");
        gpio_set_value(255, 0);
    }
    pthread_exit(NULL);
}
void* setu_2(void *arg){
    sem_wait(&sem2);
    if(light2==1){
        printf("set2_0");
        gpio_set_value(255, 0);
    }else{
        printf("set2_1");
        gpio_set_value(255, 1);
    }
    pthread_exit(NULL);
}

void* set3(void *arg){
    sem_wait(&sem1);
    if(light3==1){
        printf("set3_1");
        gpio_set_value(428, 1);
    }else{
        printf("set3_0");
        gpio_set_value(428, 0);
    }
    pthread_exit(NULL);
}
void* setu_3(void *arg){
    sem_wait(&sem2);
    if(light3==1){
        printf("set3_0");
        gpio_set_value(428, 0);
    }else{
        printf("set3_1");
        gpio_set_value(428, 1);
    }
    pthread_exit(NULL);
}

void* set4(void *arg){
    sem_wait(&sem1);
    if(light4==1){
        printf("set4_1");
        gpio_set_value(427, 1);
    }else{
        printf("set4_0");
        gpio_set_value(427, 0);
    }
    pthread_exit(NULL);
}
void* setu_4(void *arg){
    sem_wait(&sem2);
    if(light4==1){
        printf("set4_0");
        gpio_set_value(427, 0);
    }else{
        printf("set4_1");
        gpio_set_value(427, 1);
    }
    pthread_exit(NULL);
}

void final_lab::set_time(){
    ui->process_time->setText(t.toString("hh:mm"));
}

final_lab::~final_lab()
{
    delete ui;
}

void final_lab::on_Semophore_clicked()
{printf("here\n");
    time_all=ui->Count->value()*2;
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    t.setHMS(0,0,0);
    gpio_export(396);
    gpio_export(255);
    gpio_export(428);
    gpio_export(427);
    gpio_set_dir(396, "out");
    gpio_set_dir(255, "out");
    gpio_set_dir(428, "out");
    gpio_set_dir(427, "out");

    if(ui->LED1->isChecked()){
        light1=1;
    }else{
        light1=0;
    }
    if(ui->LED2->isChecked()){
        light2=1;
    }else{
        light2=0;
    }
    if(ui->LED3->isChecked()){
        light3=1;
    }else{
        light3=0;
    }
    if(ui->LED4->isChecked()){
        light4=1;
    }else{
        light4=0;
    }

    for(; time_all>0; time_all--){
        if(time_all%2==0){
            sem_post(&sem1);pthread_create(&t1, NULL, set1, NULL);
            sem_post(&sem1);pthread_create(&t2, NULL, set2, NULL);
            sem_post(&sem1);pthread_create(&t3, NULL, set3, NULL);
            sem_post(&sem1);pthread_create(&t4, NULL, set4, NULL);
        }else{
            sem_post(&sem2);pthread_create(&t1, NULL, setu_1, NULL);
            sem_post(&sem2);pthread_create(&t2, NULL, setu_2, NULL);
            sem_post(&sem2);pthread_create(&t3, NULL, setu_3, NULL);
            sem_post(&sem2);pthread_create(&t4, NULL, setu_4, NULL);
        }
        sleep(1);
        t=t.addSecs(60);printf("time:%d\n", t.minute());set_time();
    }

    gpio_set_value(396, 0);
    gpio_set_value(255, 0);
    gpio_set_value(428, 0);
    gpio_set_value(427, 0);
    gpio_unexport(396);
    gpio_unexport(255);
    gpio_unexport(428);
    gpio_unexport(427);

}
