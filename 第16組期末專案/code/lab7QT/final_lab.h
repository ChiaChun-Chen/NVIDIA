#ifndef FINAL_LAB_H
#define FINAL_LAB_H

#include <QMainWindow>
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

namespace Ui {
class final_lab;
}

class final_lab : public QMainWindow
{
    Q_OBJECT

public:
    explicit final_lab(QWidget *parent = 0);
    ~final_lab();

    void set_time();

private slots:
    void on_Semophore_clicked();

private:
    Ui::final_lab *ui;
    QTime t;
    int gpio=0;
    int LED1=396, LED2=255, LED3=428, LED4=427;
};

#endif // FINAL_LAB_H
