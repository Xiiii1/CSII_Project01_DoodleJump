#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QMOuseEvent>
#include<QKeyEvent>
#include<QPainter>
#include<QLAbel>
#include<QSound>
#include<QPropertyAnimation>
//#include<QWidgerts>  //optional
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include <QMessageBox>

//自己引入
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <QtGlobal>
#include "math.h"
#include <QRect>

		     
class MainWindow : public QMainWindow
{
Q_OBJECT
	
	public:
	MainWindow(QWidget *parent = 0);
	
	protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	void collide();
	void stairposition();
	void picture();

	private:
	int x;                      //滑鼠x
	int y;                      //滑鼠y
	int time1, timerID;         //正常跳躍參數
	int time2;					//從最高點下降的時間
	int time3, timerID3;        //stairblue第一種移動方式的計時器
	int time4, timerID4;        //stairblue第二種移動方式的計時器
	int time5, timerID5;        //stairdeepblue移動方式的計時器
	int time6;					//hat計時
	int time7;					//jetpack計時
	int timered;                //stairred計時
	int timebroken;             //stairrbroken計時
	int timeprot;               //防護罩計時
	int timehat;                //帽子計時
	int timejet;                //火箭計時



	QString key;
	int Score;
	int doodlex;
	double doodley;
	int dir;                     //判斷doodle朝左還右
	int il;						//用以生成一開始向左的doodle，再生成後令il=1;

	QImage background;
	QImage bgOriginal;
	QPixmap interface;
	QPixmap top;

	//about doodle
	QPixmap doodleL;
	QPixmap doodleR;
	QPixmap doodleS;
	QPixmap doodleUL;
	QPixmap doodleUR;
	QPixmap doodleH1;
	QPixmap doodleH2;
	QPixmap doodleH3;
	QPixmap doodleH4;
	QPixmap doodleJ1;
	QPixmap doodleJ2;
	QPixmap doodleJ3;
	QPixmap doodleJ4;
	QPixmap doodleJ5;
	QPixmap doodleJ6;
	QPixmap doodleJ7;
	QPixmap doodleJ8;
	QPixmap doodleJ9;
	QPixmap doodleJ10;
	QPixmap doodleprotR;
	QPixmap doodleprotL;

	//about 子彈
	QPropertyAnimation* Bullet;
	bool eject = false;
	QPixmap bullet;
	QLabel* move_bullet;
	int b = -100;            //-100的目的在於因為點即左鍵會b++，因此若是b初始化為1，在開始介面亂點時也會發射子彈

	//about 血量
	int Blood;
	QPixmap blood;

	//遊戲開始、結束參數
	int n = 0;             

	QLabel *movedoodle;
	QPixmap playbutton;
	QLabel *play;
	QLabel *interface1;

	//自動生成樓梯變數
	static int const number = 10000;
	int high = 850;
	int highinterval, stairinterval;
	int color;
	int brokenhigh = 0;
	int requirement;

	QPixmap stairgreen;
	int stairgreen_x[number];//greenstair位置
	int	stairgreen_y[number];
	int green = 1;//計算greenstair數量

	QPixmap stairblue;
	int stairblue_x[number];
	int stairblue_y[number];
	int blue = 0;

	QPixmap stairdissapear;
	int stairdissapear_x[number];
	int stairdissapear_y[number]; 
	int dissapear = 0;

	QPixmap stairbroken1;
	QPixmap stairbroken2;
	QPixmap stairbroken3;
	QPixmap stairbroken4;
	int stairbroken_x[number];
	int stairbroken_y[number]; 
	int broken = 0;

	QPixmap stairthorn;
	int stairthorn_x[number];
	int stairthorn_y[number]; 
	int thorn = 0;

	QPixmap stairdeepblue;
	int stairdeepblue_x[number];
	int stairdeepblue_y[number];
	int deepblue = 0;

	QPixmap stairred;
	int stairred_x[number];
	int stairred_y[number];
	int red = 0;

	QPixmap spring1;
	QPixmap spring2;
	int spring_x[number];//spring位置
	int spring_y[number];
	int spr = 0; //spring數量計算

	QPixmap trampoline1;
	QPixmap trampoline2;
	QPixmap trampoline3;
	int trampoline_x[number];
	int trampoline_y[number];
	int trampoline = 0; 

	QPixmap hat;
	int hat_x[number];
	int hat_y[number];
	int hat1 = 0; 
	
	QPixmap jetpack;
	int jetpack_x[number];
	int jetpack_y[number];
	int jetpack1 = 0; 

	QPixmap Protection;
	int protection_x[number];
	int protection_y[number];
	int protection = 0;

	QPixmap springshoes;
	int shoes_x[number];
	int shoes_y[number];
	int shoes = 0;

	int monster;

	QPixmap monster01;
	int monster1_x[number];
	int monster1_y[number];
	int monster1 = 0;

	QPixmap monster02;
	int monster2_x[number];
	int monster2_y[number];
	int monster2 = 0;

	QPixmap monster03;
	int monster3_x[number];
	int monster3_y[number];
	int monster3 = 0;

	QPixmap monster04; 
	int monster4_x[number];
	int monster4_y[number];
	int monster4 = 0;

	QPixmap blackhole;
	int black_x[number];
	int black_y[number];
	int black = 0;

	//布林值們
	bool down = false;                 //down == true為上升時後，反之
	bool touch = true;                 //touch = trueh才能觸發與道具的碰撞
	bool touchbroken = false;          //touchbroken = true 觸發broken動畫
	bool seered = false;               //seered = true 觸發stairred開始消失的計時
	bool touchprot = false;            //touchprot = true 觸發防護罩相關功能
	bool touchhat = false;             //touchhat = true 觸發帽子相關功能
	bool touchjet= false;              //touchjet = true 觸發火箭相關功能
	bool touchblue = false;            //偵測stairblue觸碰跳躍
	bool touchdeepblue = false;        //偵測stairdeepblue觸碰跳躍
	bool gameover = false;             //gameover = true 遊戲結束
	
	int mode;
	int actualheight;
	int highest = 0;
};
#endif


