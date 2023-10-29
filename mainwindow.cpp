#include"mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setFixedSize(540, 960);
	setMouseTracking(true);

	//生成樓梯
	stairposition();

	//圖片載入
	picture();

	time1 = 0;
	timerID = startTimer(1000 / 60); //1/60sec timer

	time2 = 0;

	time3 = 10;
	timerID3 = startTimer(20);

	time4 = 10;
	timerID4 = startTimer(20);
	
	time5 = 0;
	timerID5 = startTimer(10);

	time6 = 0;
	time7 = 0;
}

/**********************************************************************************************************************************/

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	x = event->x();
	y = event->y();
	update(); //call paintEvent
}

/**********************************************************************************************************************************/

void MainWindow::mousePressEvent(QMouseEvent *event)
{

	if (event->button() == Qt::LeftButton)
	{
		key = "mouse left button";
		QSound::play("./dataset/pika.wav");
		update(); //call paintEvent

		//使用 childAt() 函數獲取在鼠標點擊位置上的子控件，然後判斷這個子控件是否是 play。如果是，則滿足條件一按下play就會開始動畫!!
		QWidget *playc = childAt(event->pos());
		if (playc && playc == play) {
			n = 1;
			il = 0;
			b = 0;
			Blood = 3;//用以生成一開始向左的doodle，再生成後令il=1;
			
			play->hide(); 			
			interface1->hide();

			//生成doodle初始位置
			doodlex = 210;
			doodley = 550;

			update();
		}
		
		//子彈發射條件
		if (b > 0)
		{
			eject = true;
			update();
		}
		b++;
	}
}

/**********************************************************************************************************************************/

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Left)
	{
		key = "left arrow key";
		dir = 1;      //當dir==1，載入doodleL
		doodlex -= 10;

		if (doodlex <= -25)         //到達畫面最左時從最右出來
		{
			doodlex = 525;
		}
		update();//call paintEvent
	}
	else if (event->key() == Qt::Key_Right)
	{
		key = "right arrow key";
		dir = 2;      //當dir==2，載入doodleR
		doodlex += 10;
		if (doodlex >= 525)			//到達畫面最右時從最左出來
		{
			doodlex = -25;
		}
		update();//call paintEvent
	}
	else if (event->key() == Qt::Key_Up)
	{
		key = "up arrow key";
		update();
	}
	else if (event->key() == Qt::Key_Down)
	{
		key = "down arrow key";
		update();
	}
}

/**********************************************************************************************************************************/

void MainWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QFont font;
	QPen pen;
	painter.setRenderHint(QPainter::Antialiasing, true);



	//*************************************遊戲開始進行**************************************
	if (n == 1) {
		//生成背景
		painter.drawImage(0, 0, background);

		//生成樓梯
		for (int j = 0; j < 2000; j++)
		{
			if ((stairgreen_x[j] != 0) && (stairgreen_y[j] != 0) && ((stairgreen_y[j] + Score) > -30) && ((stairgreen_y[j] + Score) <= 960)) {
				painter.drawPixmap(stairgreen_x[j], stairgreen_y[j] + Score, stairgreen);
			}
		}

		for (int j = 0; j < 1000; j++)
		{
			if ((stairblue_x[j] != 0) && (stairblue_y[j] != 0) && ((stairblue_y[j] + Score) > -30) && ((stairblue_y[j] + Score) <= 960)) {
				painter.drawPixmap(stairblue_x[j], stairblue_y[j] + Score, stairblue);
			}
		}

		for (int j = 0; j < 500; j++)
		{
			if ((stairdissapear_x[j] != 0) && (stairdissapear_y[j] != 0) && ((stairdissapear_y[j] + Score) > -30) && ((stairdissapear_y[j] + Score) <= 960)) {
				painter.drawPixmap(stairdissapear_x[j], stairdissapear_y[j] + Score, stairdissapear);
			}
		}

		for (int j = 0; j < 500; j++)
		{
			if ((stairbroken_x[j] != 0) && (stairbroken_y[j] != 0) && ((stairbroken_y[j] + Score) > -30) && ((stairbroken_y[j] + Score) <= 960)) {
				if (timebroken >= 1 && timebroken < 7)
				{
					touchbroken = true;
					painter.drawPixmap(stairbroken_x[j], stairbroken_y[j] + Score, stairbroken2);
				}
				else if (timebroken >= 7 && timebroken < 14)
				{
					touchbroken = true;
					painter.drawPixmap(stairbroken_x[j], stairbroken_y[j] + Score, stairbroken3);
				}
				else if (timebroken >= 14 && timebroken < 20)
				{
					touchbroken = true;
					painter.drawPixmap(stairbroken_x[j], stairbroken_y[j] + Score, stairbroken4);
				}

				if (touchbroken == false)
				{
					painter.drawPixmap(stairbroken_x[j], stairbroken_y[j] + Score, stairbroken1);
				}
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((stairthorn_x[j] != 0) && (stairthorn_y[j] != 0) && ((stairthorn_y[j] + Score) > -30) && ((stairthorn_y[j] + Score) <= 960)) {
				painter.drawPixmap(stairthorn_x[j], stairthorn_y[j] + Score, stairthorn);
			}
		}

		for (int j = 0; j < 500; j++)
		{
			if ((stairdeepblue_x[j] != 0) && (stairdeepblue_y[j] != 0) && ((stairdeepblue_y[j] + Score) > -30) && ((stairdeepblue_y[j] + Score) <= 960)) {
				painter.drawPixmap(stairdeepblue_x[j], stairdeepblue_y[j] + Score, stairdeepblue);
			}
		}

		for (int j = 0; j < 200; j++)                              ///在畫面出現4秒後消失
		{
			if ((stairred_x[j] != 0) && (stairred_y[j] != 0) && ((stairred_y[j] + Score) > -30) && ((stairred_y[j] + Score) <= 960)) {
				if (timered <= 240)
				{
					seered = true;
					painter.drawPixmap(stairred_x[j], stairred_y[j] + Score, stairred);
				}
				else {
					stairred_x[j] = 540;
				}
			}
		}

		for (int j = 0; j < 500; j++)
		{
			if ((spring_x[j] != 0) && (monster4_y[j] != 0) && ((spring_y[j] + Score) > -30) && ((spring_y[j] + Score) <= 960)) {
				painter.drawPixmap(spring_x[j], spring_y[j] + Score, spring1);
			}
		}


		for (int j = 0; j < 200; j++)
		{
			if ((trampoline_x[j] != 0) && (trampoline_y[j] != 0) && ((trampoline_y[j] + Score) > -30) && ((trampoline_y[j] + Score) <= 960)) {
				painter.drawPixmap(trampoline_x[j], trampoline_y[j] + Score, trampoline1);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((hat_x[j] != 0) && (hat_y[j] != 0) && ((hat_y[j] + Score) > -30) && ((hat_y[j] + Score) <= 960)) {
				painter.drawPixmap(hat_x[j], hat_y[j] + Score, hat);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((jetpack_x[j] != 0) && (jetpack_y[j] != 0) && ((jetpack_y[j] + Score) > -30) && ((jetpack_y[j] + Score) <= 960)) {
				painter.drawPixmap(jetpack_x[j], jetpack_y[j] + Score, jetpack);			
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((protection_x[j] != 0) && (protection_y[j] != 0) && ((protection_y[j] + Score) > -30) && ((protection_y[j] + Score) <= 960)) {
				painter.drawPixmap(protection_x[j], protection_y[j] + Score, Protection);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((shoes_x[j] != 0) && (shoes_y[j] != 0) && ((shoes_y[j] + Score) > -30) && ((shoes_y[j] + Score) <= 960)) {
				painter.drawPixmap(shoes_x[j], shoes_y[j] + Score, springshoes);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((monster1_x[j] != 0) && (monster1_y[j] != 0) && ((monster1_y[j] + Score) > -30) && ((monster1_y[j] + Score) <= 960)) {
				painter.drawPixmap(monster1_x[j], monster1_y[j] + Score, monster01);
			}
		}


		for (int j = 0; j < 200; j++)
		{
			if ((monster2_x[j] != 0) && (monster2_y[j] != 0) && ((monster2_y[j] + Score) > -30) && ((monster2_y[j] + Score) <= 960)) {
				painter.drawPixmap(monster2_x[j], monster2_y[j] + Score, monster02);
			}
		}
	

		for (int j = 0; j < 200; j++)
		{
			if ((monster3_x[j] != 0) && (monster3_y[j] != 0) && ((monster3_y[j] + Score) > -30) && ((monster3_y[j] + Score) <= 960)) {
				painter.drawPixmap(monster3_x[j], monster3_y[j] + Score, monster03);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((monster4_x[j] != 0) && (monster4_y[j] != 0) && ((monster4_y[j] + Score) > -30) && ((monster4_y[j] + Score) <= 960)) {
				painter.drawPixmap(monster4_x[j], monster4_y[j] + Score, monster04);
			}
		}

		for (int j = 0; j < 200; j++)
		{
			if ((black_x[j] != 0) && (black_y[j] != 0) && ((black_y[j] + Score) > -30) && ((black_y[j] + Score) <= 960)) {
				painter.drawPixmap(black_x[j], black_y[j] + Score, blackhole);
			}
		}	

		//碰撞檢測
		collide();

		//******************doodle control**********************
		//初始狀態
		if (il == 0)  
		{
			painter.drawPixmap(doodlex, doodley, doodleL);
			if (gameover == true)
			{
				Blood = 0;
			}
		}

		if (dir == 1) {
			if (gameover == true)
			{
				Blood = 0;
			}

			if (touchprot == true) {
				painter.drawPixmap(doodlex, doodley, doodleprotL);
			}
			if (touchjet == true)
			{
				if (time7 >= 1 && time7 < 60)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ1);
				}
				else if (time7 >= 50 && time7 < 100)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ2);
				}
				else if (time7 >= 100 && time7 < 148)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ3);
				}
				else if (time7 >= 148 && time7 < 196)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ4);
				}
				else if (time7 >= 196 && time7 < 240)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ5);
				}
				else if (time7 >= 240 && time7 < 288)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ6);
				}
				else if (time7 >= 288 && time7 < 336)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ7);
				}
				else if (time7 >= 336 && time7 < 384)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ8);
				}
				else if (time7 >= 384 && time7 < 432)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ9);
				}
				else if (time7 >= 432 && time7 < 480)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ10);
				}
				else if (time7 >= 480) {
					time7 = 0;
					touchjet = false;
				}
			}

			if (touchhat == true)
			{
				if (time6 >= 1 && time6 < 90)
				{
					painter.drawPixmap(doodlex, doodley, doodleH1);
				}
				else if (time6 >= 90 && time6 < 180)
				{
					painter.drawPixmap(doodlex, doodley, doodleH2);
				}
				else if (time6 >= 180 && time6 < 270)
				{
					painter.drawPixmap(doodlex, doodley, doodleH3);
				}
				else if (time6 >= 270 && time6 < 360)
				{
					painter.drawPixmap(doodlex, doodley, doodleH4);
				}
				else if (time6 >= 360)
				{
					touchhat = false;
				}
			}

			else 
			{
				if (touchhat == false && touchprot == false && touchjet ==false)
				{
					painter.drawPixmap(doodlex, doodley, doodleL);
					il = 1;
				}
			}

		}
		else if (dir == 2) {
			if (gameover == true)
			{
				Blood = 0;
			}

			if (touchprot == true) {
				painter.drawPixmap(doodlex, doodley, doodleprotR);
			}

			if (touchjet == true)
			{
				if (time7 >= 1 && time7 < 60)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ1);
				}
				else if (time7 >= 50 && time7 < 100)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ2);
				}
				else if (time7 >= 100 && time7 < 148)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ3);
				}
				else if (time7 >= 148 && time7 < 196)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ4);
				}
				else if (time7 >= 196 && time7 < 240)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ5);
				}
				else if (time7 >= 240 && time7 < 288)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ6);
				}
				else if (time7 >= 288 && time7 < 336)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ7);
				}
				else if (time7 >= 336 && time7 < 384)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ8);
				}
				else if (time7 >= 384 && time7 < 432)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ9);
				}
				else if (time7 >= 432 && time7 < 480)
				{
					painter.drawPixmap(doodlex, doodley, doodleJ10);
				}
				else if (time7 >= 480) {
					time7 = 0;
					touchjet = false;
				}
			}
			if (touchhat == true)
			{
				if (time6 >= 1 && time6 < 90)
				{
					painter.drawPixmap(doodlex, doodley, doodleH1);
				}
				else if (time6 >= 90 && time6 < 180)
				{
					painter.drawPixmap(doodlex, doodley, doodleH2);
				}
				else if (time6 >= 180 && time6 < 270)
				{
					painter.drawPixmap(doodlex, doodley, doodleH3);
				}
				else if (time6 >= 270 && time6 < 360)
				{
					painter.drawPixmap(doodlex, doodley, doodleH4);
				}
			else if (time6 >= 360)
				{
					time6 = 0;
					touchhat = false;
				}
			}

			else
			{
				if (touchhat == false && touchprot == false && touchjet == false)
				{
					painter.drawPixmap(doodlex, doodley, doodleR);
					il = 1;
				}
			}

		}

		//發射子彈
		
		if (eject == true)
		{
			Bullet = new QPropertyAnimation(move_bullet, "pos");
			Bullet->setDuration(pow((pow((x - (doodlex + 40)), 2) + pow((y - doodley), 2)), 0.5) * 2);
			Bullet->setStartValue(QPoint(doodlex + 40, doodley));
			Bullet->setEndValue(QPoint(x, y));
			Bullet->start();

			connect(Bullet, &QAbstractAnimation::finished, [=]() {
				move_bullet->move(0, 960);
			});

			eject = false;
			
		}
		
		//生成頂端
		painter.drawPixmap(0, 0, top);

		//生成血量
		if (Blood == 3) {
			painter.drawPixmap(380, 0, blood);
			painter.drawPixmap(410, 0, blood);
			painter.drawPixmap(440, 0, blood);
		}
		if (Blood == 2) {
			painter.drawPixmap(410, 0, blood);
			painter.drawPixmap(440, 0, blood);			}
		if (Blood == 1) {
			painter.drawPixmap(440, 0, blood);
		}
		if (Blood <= 0) {
			gameover = true;
			Score = Score;
			n = 2;
		}

		font.setPointSize(20);
		painter.setFont(font);
		pen.setColor(Qt::black);
		painter.setPen(pen);
		painter.drawText(10, 30, QString("Score: %1").arg(Score));
	}


	if (n == 2) {
		painter.drawImage(0, 0, background);
		
		font.setPointSize(40);
		painter.setFont(font);
		pen.setColor(Qt::black);
		painter.setPen(pen);
		painter.drawText(150, 460, QString("Game over!"));
		painter.drawText(130, 540, QString("Score: %1").arg(Score));
	}
}

/**********************************************************************************************************************************/

void MainWindow::timerEvent(QTimerEvent *event)
{
	//Timer1
	if (event->timerId() == timerID && timerID != 0)
	{
		if (touchhat == true) {
			time6 = (time6 == 360) ? 0 : time6 + 1;
			if (time6 == 0)
			{
				touchhat = false;
			}
		}
		if (touchjet == true) {
			time7 = (time7 == 600) ? 0 : time7 + 1;
			if (time7 == 0)
			{
				touchjet = false;
			}
		}
		
		time1 = (time1 == 360) ? 0 : time1 + 1;
		
		if (time1 == 0) {
			touch = true;
		}
		
		if (time1 <= 59  && touchhat == false && touchjet == false)			 //上升 1s
		{
			down = false;
			if (mode == 1)   //mode 1為正常跳躍
			{
				if (doodley <= 440)
				{
					doodley = 440;
					update();
				}
				else   //未到螢幕中間時的上跳
				{
					doodley -= ((640.0 / 59 / 59) * 59 - (640.0 / 59 / 59) * time1 - (640.0 / 59 / 59 / 2));						//受重力影響且1/60s改一次y座標
					update();
				}
			}
			else if (mode == 2)  //碰到彈簧
			{
				if (doodley <= 440)
				{
					doodley = 440;
					update();
				}
				else   //未到螢幕中間時的上跳
				{
					doodley -= ((1280.0 / 59 / 59) * 59 - (1280.0 / 59 / 59) * time1 - (1280.0 / 59 / 59 / 2));						//受重力影響且1/60s改一次y座標
					update();
				}
			}
			else if (mode == 3)  //碰到trampoline
			{
				if (doodley <= 440)
				{
					doodley = 440;
					update();
				}
				else   //未到螢幕中間時的上跳
				{
					doodley -= ((3840.0 / 59 / 59) * 59 - (3840.0 / 59 / 59) * time1 - (3840.0 / 59 / 59 / 2));						//受重力影響且1/60s改一次y座標
					update();
				}
			}	
		}
		else if (touchhat == true)
		{
			down = false;
			time1 = 59;

			if (mode == 4)  //碰到propeller hat
			{
				touch = false;
				if (doodley <= 440)
				{
					doodley = 440;
					update();
				}
				else   //未到螢幕中間時的上跳
				{
					doodley -= ((7680.0  /360/360) * 360 - (7680.0 / 360 / 360) * time6 - (7680.0 / 360 / 360 / 2));						//受重力影響且1/60s改一次y座標
					update();
				}
			}
		}
		else if (touchjet == true)
		{
			down = false;
			touch = false;
			time1 = 59;
			 if (mode == 5)  //碰到jet pack
			{
					if (doodley <= 440)
				{
					doodley = 440;
					update();
				}
					else   //未到螢幕中間時的上跳
				{
					doodley -= ((9760.0 / 480 / 480) * 480 - (9760.0 / 480 / 480) * time7 - (9760.0 / 480 / 480 / 2));						//受重力影響且1/60s改一次y座標
					update();
				}
			}
		}
		
		else					//沒踩到踏板就持續下降
		{
			down = true;
			time2 = time1 - 60;
			update();

			doodley += ((640.0 / 59 / 59) * time2 + (640.0 / 59 / 59));								//受重力影響且1/60s改一次y座標
			if (doodley >= 880)
			{
				gameover = true;
				Score = Score;
				killTimer(timerID);
			}
		}

		//**********計算Score*********
		if (down == false)
		{//mode不同計分不同
			if (mode == 1)
			{
				actualheight += ((640.0 / 59 / 59) * 59 - (640.0 / 59 / 59) * time1 - (640.0 / 59 / 59 / 2));
				highest = actualheight;
				if (actualheight > Score)
				{
					Score = highest;
					update();
				}
			}
			else if (mode == 2)
			{
				actualheight += ((1960.0 / 59 / 59) * 59 - (1960.0 / 59 / 59) * time1 - (1960.0 / 59 / 59 / 2));
				highest = actualheight;
				if (actualheight > Score)
				{
					Score = highest;
					update();
				}
			}
			else if (mode == 3)
			{
				actualheight += ((3840.0 / 59 / 59) * 59 - (3840.0 / 59 / 59) * time1 - (3840.0 / 59 / 59 / 2));
				highest = actualheight;
				if (actualheight > Score )
				{
					Score = highest;
					update();
				}
			}
			else if (mode == 4)
			{
				actualheight += ((7680.0 /360/360) * 360 - (7680.0 / 360 / 360) * time6 - (7680.0 / 360 / 360 / 2));
				highest = actualheight;
				if (actualheight > Score)
				{
					Score = highest;
					update();
				}
			}
			else if (mode == 5)
			{
				actualheight += ((9760.0 / 480 / 480) * 600 - (9760.0 / 480 / 480) * time7 - (9760.0 / 480 / 480 / 2));
				highest = actualheight;

				if (actualheight > Score)
				{
					Score = highest;
					update();
				}	
			}
		}

		if (down == true)
		{
			//Score = highest;
			actualheight -= ((640.0 / 59 / 59) * time2 - (640.0 / 59 / 59));
			update();
		}

		//特殊stairs
		if (touchbroken == true)
		{
			timebroken += 1;
		}

		if (seered == true)
		{
			timered += 1;
		}
	}

	//Timer2
	if (event->timerId() == timerID3 && timerID3 != 0)
	{
		time3 = (time3 == 410) ? 10 : time3 + 1;
		for (int j = 0; j < 150; j += 2) {
			if (time3 < 210) {
				stairblue_x[j] = time3 * 2 - 10;
			}
			if (time3 >= 210) {
				stairblue_x[j] = 830 - time3 * 2;
			}
		}
		if (touchblue == true)
		{
			mode = 1;
		}
		update();
	}

	//Timer3
	if (event->timerId() == timerID4 && timerID4 != 0)
	{
		time4 = (time4 == 410) ? 10 : time4 + 1;
		for (int j = 1; j < 150; j += 2) {
			if (time4 < 210) {
				stairblue_x[j] = 430 - time4 * 2;
			}
			if (time4 >= 210) {
				stairblue_x[j] = time4 * 2 - 410;
			}
		}
		if (touchblue == true)
		{
			mode = 1;
		}
		update();
	}

	//Timer4
	if (event->timerId() == timerID5 && timerID5 != 0)
	{
		time5 = (time5 == 200) ? 0 : time5 + 1;
		for (int j = 0; j < 150; j ++) {
			if (time5 < 100) {
				stairdeepblue_y[j] += 1;
			}
			if (time5 >= 100) {
				stairdeepblue_y[j] -= 1;
			}
		}
		if (touchdeepblue == true)
		{
			mode = 1;
		}
		update();
	}
}

/**********************************************************************************************************************************/

void MainWindow::collide()
{
	//doodle位置
	QRect rect2(doodlex + 20, doodley + 75, 40, 5);
	//子彈位置
	QPoint pos = move_bullet->pos();
	QRect rect3(pos.x(), pos.y(), 20, 20);

	for (int j = 0; j < 2000; j++)
	{
		if ((stairgreen_x[j] != 0) && (stairgreen_y[j] != 0) && ((stairgreen_y[j] + Score) > -30) && ((stairgreen_y[j] + Score) <= 960)) {
			QRect rect1(stairgreen_x[j], stairgreen_y[j] + Score, 120, 30); // 創建一个矩形(左上x，左上y，矩形寬，矩形高)
			if (down == true) {                                 //下降時
				if (rect1.intersects(rect2))                    //碰到
				{
					mode = 1;
					time1 = 360;                                //時間重製，重新跳躍
					//update();
				}
			}
		}
	}

	for (int j = 0; j < 1000; j++)
	{
		if ((stairblue_x[j] != 0) && (stairblue_y[j] != 0) && ((stairblue_y[j] + Score) > -30) && ((stairblue_y[j] + Score) <= 960)) {
			QRect rect1(stairblue_x[j], stairblue_y[j] + Score, 120, 30); 
			if (down == true) {                                
				if (rect1.intersects(rect2))                   
				{
					mode = 1;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 500; j++)
	{
		if ((stairdissapear_x[j] != 0) && (stairdissapear_y[j] != 0) && ((stairdissapear_y[j] + Score) > -30) && ((stairdissapear_y[j] + Score) <= 960)) {
			QRect rect1(stairdissapear_x[j], stairdissapear_y[j] + Score, 120, 30); 
			if (down == true) {                                
				if (rect1.intersects(rect2))                    
				{
					mode = 1;
					time1 = 360;
					stairdissapear_x[j] = 540;
				}
			}
		}
	}


	for (int j = 0; j < 500; j++)
	{
		if ((stairbroken_x[j] != 0) && (stairbroken_y[j] != 0) && ((stairbroken_y[j] + Score) > -30) && ((stairbroken_y[j] + Score) <= 960)) {
			QRect rect1(stairbroken_x[j], stairbroken_y[j] + Score, 120, 30); 
			if (down == true) {                                 
				if (rect1.intersects(rect2))                    
				{
					touchbroken = true;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((stairthorn_x[j] != 0) && (stairthorn_y[j] != 0) && ((stairthorn_y[j] + Score) > -30) && ((stairthorn_y[j] + Score) <= 960)) {
			QRect rect1(stairthorn_x[j], stairthorn_y[j] + Score, 120, 30);
			if ((down == true)&&(touch == true)) {                                
				if (rect1.intersects(rect2))                   
				{
					mode = 1;
					if (touchprot == false)
					{
						Blood--;
					}
					touch = false;
					touchprot = false;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 500; j++)
	{
		if ((stairdeepblue_x[j] != 0) && (stairdeepblue_y[j] != 0) && ((stairdeepblue_y[j] + Score) > -30) && ((stairdeepblue_y[j] + Score) <= 960)) {
			QRect rect1(stairdeepblue_x[j], stairdeepblue_y[j] + Score, 120, 30); 
			if (down == true) {                                 
				if (rect1.intersects(rect2))                    
				{
					mode = 1;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)                              ///在畫面出現五秒後消失
	{
		if ((stairred_x[j] != 0) && (stairred_y[j] != 0) && ((stairred_y[j] + Score) > -30) && ((stairred_y[j] + Score) <= 960)) {
			QRect rect1(stairred_x[j], stairred_y[j] + Score, 120, 30); 
			if (down == true) {                                 
				if (rect1.intersects(rect2))                    
				{
					mode = 1;
					time1 = 360;
				}
			}
		}
	}

	
	for (int j = 0; j < 500; j++)
	{
		if ((spring_x[j] != 0) && (monster4_y[j] != 0) && ((spring_y[j] + Score) > -30) && ((spring_y[j] + Score) <= 960)) {
			QRect rect1(spring_x[j], spring_y[j] + Score, 40, 25); 
			if (down == true) {                                
				if (rect1.intersects(rect2))                    
				{
					mode = 2;
					time1 = 360;                               
				}
			}
		}
	}


	for (int j = 0; j < 200; j++)
	{
		if ((trampoline_x[j] != 0) && (trampoline_y[j] != 0) && ((trampoline_y[j] + Score) > -30) && ((trampoline_y[j] + Score) <= 960)) {
			QRect rect1(trampoline_x[j], trampoline_y[j] + Score, 72, 36); 
			if (down == true) {                                
				if (rect1.intersects(rect2))                   
				{
					mode = 3;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((hat_x[j] != 0) && (hat_y[j] != 0) && ((hat_y[j] + Score) > -30) && ((hat_y[j] + Score) <= 960)) {
			QRect rect1(hat_x[j], hat_y[j] + Score, 64, 40); 
			if (rect1.intersects(rect2))                   
			{
				hat_x[j] = 700;
				mode = 4;
				touchprot = false;
				touchjet = false;
				touchhat = true;
			}

		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((jetpack_x[j] != 0) && (jetpack_y[j] != 0) && ((jetpack_y[j] + Score) > -30) && ((jetpack_y[j] + Score) <= 960)) {
			QRect rect1(jetpack_x[j], jetpack_y[j] + Score, 50, 72);                        
				if (rect1.intersects(rect2))                  
				{
					jetpack_x[j] = 700;
					mode = 5;
					touchhat = false;
					touchprot = false;
					touchjet = true;
				}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((protection_x[j] != 0) && (protection_y[j] != 0) && ((protection_y[j] + Score) > -30) && ((protection_y[j] + Score) <= 960)) {
			QRect rect1(protection_x[j], protection_y[j] + Score, 80, 72); 
			                               
				if (rect1.intersects(rect2))                   
				{
					protection_y[j] = 700;
					touchprot = true;
				}
		}
	}

	for (int j = 0; j < 50; j++)
	{
		if ((shoes_x[j] != 0) && (shoes_y[j] != 0) && ((shoes_y[j] + Score) > -30) && ((shoes_y[j] + Score) <= 960)) {
			QRect rect1(shoes_x[j], shoes_y[j] + Score, 60, 47); 
			if (down == true) {                                
				if (rect1.intersects(rect2))                  
				{
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((monster1_x[j] != 0) && (monster1_y[j] != 0) && ((monster1_y[j] + Score) > -30) && ((monster1_y[j] + Score) <= 960)) {
			QRect rect1(monster1_x[j], monster1_y[j] + Score, 168, 105);
			if (rect1.intersects(rect3))
			{
				monster1_x[j] = 700;
			}
			
			if ((down == false) && (touch == true))                     
			{
				if (rect1.intersects(rect2))                   
				{
					if (touchprot == true) {
						touchprot = false;
						touch = false;
					}
					if ((touchprot == false) && (touch == true))
					{
						Blood--;
						touch = false;
					}
					monster1_x[j] = 700;
				}
			}
			if (down == true)
			{
				if (rect1.intersects(rect2))                  
				{
					monster1_x[j] = 700;
					time1 = 360;
				}
			}
			//*********碰到旁邊要扣血********
		}
	}


	for (int j = 0; j < 200; j++)
	{
		if ((monster2_x[j] != 0) && (monster2_y[j] != 0) && ((monster2_y[j] + Score) > -30) && ((monster2_y[j] + Score) <= 960)) {
			QRect rect1(monster2_x[j], monster2_y[j] + Score, 128, 178); 
			if (rect1.intersects(rect3))
			{
				monster2_x[j] = 700;
			}
			if ((down == false) && (touch == true))
			{
				if (rect1.intersects(rect2))                    
				{
					if (touchprot == true) {
						touchprot = false;
						touch = false;
					}
					if ((touchprot == false) && (touch == true))
					{
						Blood--;
						touch = false;

					}
					monster2_x[j] = 700;

				}
			}
			if (down == true)
			{
				if (rect1.intersects(rect2))                    
				{
					monster2_x[j] = 700;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((monster3_x[j] != 0) && (monster3_y[j] != 0) && ((monster3_y[j] + Score) > -30) && ((monster3_y[j] + Score) <= 960)) {
			QRect rect1(monster3_x[j], monster3_y[j] + Score, 160, 100); 
			if (rect1.intersects(rect3))
			{
				monster3_x[j] = 700;
			}
			if ((down == false) && (touch == true))                        
			{
				if (rect1.intersects(rect2))                    
				{
					if (touchprot == true)
					{
						touchprot = false;
						touch = false;
					}
					if ((touchprot == false) && (touch == true))
					{
						Blood--;
						touch = false;
					}
					monster3_x[j] = 700;

				}
			}
			if (down == true)
			{
				if (rect1.intersects(rect2))                   
				{
					monster3_x[j] = 700;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((monster4_x[j] != 0) && (monster4_y[j] != 0) && ((monster4_y[j] + Score) > -30) && ((monster4_y[j] + Score) <= 960)) {
			QRect rect1(monster4_x[j], monster4_y[j] + Score, 160, 90);
			if (rect1.intersects(rect3))
			{
				monster4_x[j] = 700;
			}
			if ((down == false) && (touch == true))                        
			{
				if (rect1.intersects(rect2))                    
				{
					if (touchprot == true) {
						touchprot = false;
						touch = false;
					}
					if ((touchprot == false) && (touch == true))
					{
						Blood--;
						touch = false;
					}
					monster4_x[j] = 700;
				}
			}
			if (down == true)
			{
				if (rect1.intersects(rect2))                    
				{
					monster4_x[j] = 700;
					time1 = 360;
				}
			}
		}
	}

	for (int j = 0; j < 200; j++)
	{
		if ((black_x[j] != 0) && (black_y[j] != 0) && ((black_y[j] + Score) > -30) && ((black_y[j] + Score) <= 960)) {
			QRect rect1(black_x[j], black_y[j] + Score, 150, 135);
			if (touch == true) { 
				if (rect1.intersects(rect2))
				{
					gameover = true;
				}
			}
		}
	}


}

/**********************************************************************************************************************************/

void MainWindow::stairposition()
{
	//自動生成樓梯
	//第一階固定位置
	stairgreen_x[0] = 210;
	stairgreen_y[0] = 910;
	//隨機產生
	srand(time(NULL));
	//高度0~3000 較密集
	while ((high <= 850) && (high > -2150))
	{
		if (brokenhigh > 1000) {                  //每累積高度1000，生成一個brokenstair
			highinterval = 60;
			stairinterval = highinterval - 30;
			high = high - highinterval;
			stairbroken_x[broken] = rand() % 420;
			stairbroken_y[broken] = high + 30 + (rand() % (stairinterval));
			broken++;
			brokenhigh = 0;  //高度歸零
		}
		else {
			highinterval = 60 + rand() % 120;
			stairinterval = highinterval - 59;
			high = high - highinterval;
			brokenhigh = brokenhigh + highinterval;     //累積高度
			stairgreen_x[green] = rand() % 420;
			stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
			green++;
		}
	}

	//高度3000~6000 
	while ((high <= -2150) && (high > -5150))
	{
		if (brokenhigh > 1000) {                  //累積高度1000生成一個brokenstair
			highinterval = 60;
			stairinterval = highinterval - 30;
			high = high - highinterval;
			stairbroken_x[broken] = rand() % 420;
			stairbroken_y[broken] = high + 30 + (rand() % (stairinterval));
			broken++;
			brokenhigh = 0;  //高度歸零
		}
		else {
			//隨機生成變數color
			color = 1 + rand() % 100;
			if (color < 97) {
				highinterval = 60 + rand() % 120;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 420;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				//道具生成
				if (rand() % 100 <= 15) {                         //有15%的機率生成道具
					requirement = 1 + rand() % 100;
					if (requirement < 70) {                                         //其中70%生成彈簧 
						spring_x[spr] = stairgreen_x[green] + 45;
						spring_y[spr] = stairgreen_y[green] - 20;
						spr++;
					}
					else if (requirement <= 100) {                                   //剩下30%生成防護罩
						protection_x[protection] = stairgreen_x[green] + 20;
						protection_y[protection] = stairgreen_y[green] - 72;
						protection++;
					}
				}
				green++;
			}
			//color在97、98時生成greenstair和monster1、2和黑洞
			else if ((color >= 97) && (color < 99)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 220;
				stairgreen_y[green] = high  + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster1_x[monster1] = 340 + rand() % 32;
					monster1_y[monster1] = high + 20;
					monster1++;
				}
				if (monster == 2) {
					monster2_x[monster2] = 340 + rand() % 72;
					monster2_y[monster2] = high + 20;
					monster2++;
				}
				if (monster == 3) {
					black_x[black] = 340 + rand() % 50;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
			//color在99、100時生成greenstair和monster3、4和黑洞
			else if ((color >= 99) && (color <= 100)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = 270 + rand() % 15;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster3_x[monster3] = 30 + rand() % 80;
					monster3_y[monster3] = high + 20;
					monster3++;
				}
				if (monster == 2) {
					monster4_x[monster4] = 30 + rand() % 80;
					monster4_y[monster4] = high + 20;
					monster4++;
				}
				if (monster == 3) {
					black_x[black] = 30 + rand() % 90;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
		}
	}

	//高度6000~9000
	while ((high <= -5150) && (high > -8150))
	{
		if (brokenhigh > 1000) {                  //累積高度1000生成一個brokenstair
			highinterval = 60;
			stairinterval = highinterval - 30;
			high = high - highinterval;
			stairbroken_x[broken] = rand() % 420;
			stairbroken_y[broken] = high + 30 + (rand() % (stairinterval));
			broken++;
			brokenhigh = 0;  //高度歸零
		}
		else {
			//隨機生成變數color
			color = 1 + rand() % 100;
			//color在1~80時生成greenstair
			if (color <= 80) {
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 420;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				//在stair上，有10%的機率生成道具
				if (rand() % 100 < 10) {
					requirement = 1 + rand() % 100;
					if (requirement < 70) {                                 //70%生成彈簧 
						spring_x[spr] = stairgreen_x[green] + 45;
						spring_y[spr] = stairgreen_y[green] - 20;
						spr++;
					}
					else if (requirement < 90) {                                              //20%生成跳床
						trampoline_x[trampoline] = stairgreen_x[green] + 24;
						trampoline_y[trampoline] = stairgreen_y[green] - 36;
						trampoline++;
					}
					else if (requirement <= 100) {                                              //剩下10%生成防護罩
						protection_x[protection] = stairgreen_x[green] + 20;
						protection_y[protection] = stairgreen_y[green] - 72;
						protection++;
					}
				}
				green++;
			}
			//color在81~96時生成bluestair
			else if (color <= 96) {
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairblue_y[blue] = high + 30 + (rand() % (stairinterval));
				blue++;
			}
			//color在97、98時生成greenstair和monster1、2和黑洞
			else if ((color >= 97) && (color < 99)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 220;
				stairgreen_y[green] = high + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster1_x[monster1] = 340 + rand() % 32;
					monster1_y[monster1] = high + 20;
					monster1++;
				}
				if (monster == 2) {
					monster2_x[monster2] = 340 + rand() % 72;
					monster2_y[monster2] = high + 20;
					monster2++;
				}
				if (monster == 3) {
					black_x[black] = 340 + rand() % 50;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
			//color在99、100時生成greenstair和monster3、4和黑洞
			else if ((color >= 99) && (color <= 100)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = 270 + rand() % 15;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster3_x[monster3] = 30 + rand() % 80;
					monster3_y[monster3] = high + 20;
					monster3++;
				}
				if (monster == 2) {
					monster4_x[monster4] = 30 + rand() % 80;
					monster4_y[monster4] = high + 20;
					monster4++;
				}
				if (monster == 3) {
					black_x[black] = 30 + rand() % 90;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
		}
	}

	//高度9000~12000
	while ((high <= -8150) && (high > -11150))
	{
		if (brokenhigh > 1000) {                  //累積高度1000生成一個brokenstair
			highinterval = 60;
			stairinterval = highinterval - 30;
			high = high - highinterval;
			stairbroken_x[broken] = rand() % 420;
			stairbroken_y[broken] = high + 30 + (rand() % (stairinterval));
			broken++;
			brokenhigh = 0;  //高度歸零
		}
		else {
			//隨機生成變數color
			color = 1 + rand() % 100;
			//color在0~60時生成greenstair
			if (color < 60) {
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 420;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				//道具生成
				if (rand() % 100 <= 10) {                     //有10%的機率生成道具
					requirement = 1 + rand() % 100;
					if (requirement < 50) {                                        //50%生成彈簧 
						spring_x[spr] = stairgreen_x[green] + 45;
						spring_y[spr] = stairgreen_y[green] - 20;
						spr++;
					}
					else if (requirement < 65) {                                   //15%生成跳床
						trampoline_x[trampoline] = stairgreen_x[green] + 24;
						trampoline_y[trampoline] = stairgreen_y[green] - 36;
						trampoline++;
					}
					else if (requirement < 80) {                                   //15%生成鞋子
						shoes_x[shoes] = stairgreen_x[green] + 30;
						shoes_y[shoes] = stairgreen_y[green] - 47;
						shoes++;
					}
					else if (requirement < 90) {                                   //10%生成帽子
						hat_x[hat1] = stairgreen_x[green] + 28;
						hat_y[hat1] = stairgreen_y[green] - 40;
						hat1++;
					}
					else if (requirement <= 100) {                                 //10%生成防護罩
						protection_x[protection] = stairgreen_x[green] + 20;
						protection_y[protection] = stairgreen_y[green] - 72;
						protection++;
					}
				}
				green++;
			}
			//color在61~80時生成bluestair
			else if (color < 80)
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairblue_y[blue] = high + 30 + (rand() % (stairinterval));
				blue++;
			}
			//color在80~90生成stairdeepblue
			else if (color < 90)
			{
				highinterval = 220;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairdeepblue_x[deepblue] = rand() % 420;
				stairdeepblue_y[deepblue] = high + 110;
				deepblue++;
			}
			//color在90~97生成dissapearstair
			else if ((color >= 90) && (color < 97))
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairdissapear_x[dissapear] = rand() % 420;
				stairdissapear_y[dissapear] = high + 30 + (rand() % (stairinterval));
				dissapear++;
			}
			//color在97、98時生成greenstair和monster1、2和黑洞
			else if ((color >= 97) && (color < 99)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 220;
				stairgreen_y[green] = high + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster1_x[monster1] = 340 + rand() % 32;
					monster1_y[monster1] = high + 20;
					monster1++;
				}
				if (monster == 2) {
					monster2_x[monster2] = 340 + rand() % 72;
					monster2_y[monster2] = high + 20;
					monster2++;
				}
				if (monster == 3) {
					black_x[black] = 340 + rand() % 50;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
			//color在99、100時生成greenstair和monster3、4和黑洞
			else if ((color >= 99) && (color <= 100)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = 270 + rand() % 15;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster3_x[monster3] = 30 + rand() % 80;
					monster3_y[monster3] = high + 20;
					monster3++;
				}
				if (monster == 2) {
					monster4_x[monster4] = 30 + rand() % 80;
					monster4_y[monster4] = high + 20;
					monster4++;
				}
				if (monster == 3) {
					black_x[black] = 30 + rand() % 90;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
		}
	}

	//高度大於12000
	while ((high <= -11150) && (high > -1000000))
	{
		if (brokenhigh > 1000) {                  //累積高度1000生成一個brokenstair
			highinterval = 60;
			stairinterval = highinterval - 30;
			high = high - highinterval;
			stairbroken_x[broken] = rand() % 420;
			stairbroken_y[broken] = high + 30 + (rand() % (stairinterval));
			broken++;
			brokenhigh = 0;  //高度歸零
		}
		else {
			//隨機生成變數color
			color = 1 + rand() % 100;
			//color在1~70時生成greenstair
			if (color <= 70) {
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 420;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				//道具生成
				if (rand() % 100 <= 10) {                                                        //有10%的機率生成道具
					requirement = 1 + rand() % 100;
					if (requirement < 40) {                                                      //40%生成彈簧 
						spring_x[spr] = stairgreen_x[green] + 45;
						spring_y[spr] = stairgreen_y[green] - 20;
						spr++;
					}
					else if (requirement < 60) {                                                 //20%生成跳床
						trampoline_x[trampoline] = stairgreen_x[green] + 24;
						trampoline_y[trampoline] = stairgreen_y[green] - 36;
						trampoline++;
					}
					else if (requirement < 70) {                                                 //10%生成鞋子
						shoes_x[shoes] = stairgreen_x[green] + 30;
						shoes_y[shoes] = stairgreen_y[green] - 47;
						shoes++;
					}
					else if (requirement < 80) {                                                 //10%生成帽子
						hat_x[hat1] = stairgreen_x[green] + 28;
						hat_y[hat1] = stairgreen_y[green] - 40;
						hat1++;
					}
					else if (requirement < 90) {                                                 //10%生成火箭
						jetpack_x[jetpack1] = stairgreen_x[green] + 35;
						jetpack_y[jetpack1] = stairgreen_y[green] - 72;
						jetpack1++;
					}
					else if (requirement <= 100) {                                               //10%生成防護罩
						protection_x[protection] = stairgreen_x[green] + 20;
						protection_y[protection] = stairgreen_y[green] - 72;
						protection++;
					}
				}
				green++;
			}
			//color在71~75時生成bluestair
			else if (color <= 75)
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairblue_y[blue] = high + 30 + (rand() % (stairinterval));
				blue++;
			}
			//color在76~80時生成stairdeepblue
			else if (color <= 80)
			{
				highinterval = 220;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairdeepblue_x[deepblue] = rand() % 420;
				stairdeepblue_y[deepblue] = high + 110;
				deepblue++;
			}
			//color在80~90時生成dissapearstair
			else if (color < 90)
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairdissapear_x[dissapear] = rand() % 420;
				stairdissapear_y[dissapear] = high + 30 + (rand() % (stairinterval));
				dissapear++;
			}
			//color在90~94時生成stairred
			else if (color < 95)
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairred_x[red] = rand() % 420;
				stairred_y[red] = high + 30 + (rand() % (stairinterval));
				red++;
			}
			//color在95~96時生成stairthorn
			else if ((color >= 95) && (color < 97))
			{
				highinterval = 60 + rand() % 100;
				stairinterval = highinterval - 59;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairthorn_x[thorn] = rand() % 420;
				stairthorn_y[thorn] = high + 30 + (rand() % (stairinterval));
				thorn++;
			}
			//color在97、98時生成greenstair和monster1、2和黑洞
			else if ((color >= 97) && (color < 99)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = rand() % 220;
				stairgreen_y[green] = high + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster1_x[monster1] = 340 + rand() % 32;
					monster1_y[monster1] = high + 20;
					monster1++;
				}
				if (monster == 2) {
					monster2_x[monster2] = 340 + rand() % 72;
					monster2_y[monster2] = high + 20;
					monster2++;
				}
				if (monster == 3) {
					black_x[black] = 340 + rand() % 50;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
			//color在99、100時生成greenstair和monster3、4和黑洞
			else if ((color >= 99) && (color <= 100)) {
				highinterval = 200;
				stairinterval = highinterval - 30;
				high = high - highinterval;
				brokenhigh = brokenhigh + highinterval;
				stairgreen_x[green] = 270 + rand() % 15;
				stairgreen_y[green] = high + 30 + (rand() % (stairinterval));
				monster = 1 + rand() % 3;
				if (monster == 1) {
					monster3_x[monster3] = 30 + rand() % 80;
					monster3_y[monster3] = high + 20;
					monster3++;
				}
				if (monster == 2) {
					monster4_x[monster4] = 30 + rand() % 80;
					monster4_y[monster4] = high + 20;
					monster4++;
				}
				if (monster == 3) {
					black_x[black] = 30 + rand() % 90;
					black_y[black] = high + 20;
					black++;
				}
				green++;
			}
		}
	}
}

/**********************************************************************************************************************************/

void MainWindow::picture()
{
	playbutton.load("./dataset/images/playbutton.png");
	playbutton = playbutton.scaled(188, 70, Qt::KeepAspectRatio);
	play = new QLabel(this);													//創建一個新的 QLabel，命名為 play，並將它設定為當前視窗（this）的子元素。
	play->setFixedSize(playbutton.size());								     	//設置play的大小與playbuttom的大小一樣
	play->setPixmap(playbutton);												//將縮放後的playbuttom設置到QLabel對象play中
	play->setObjectName("play");										       //指定物件名稱為"play"
	play->move(83, 311);														//將QLabel物件移動至視窗(x,y)之位置

	interface.load("./dataset/images/reference-start-interface.png");
	interface = interface.scaled(540, 960, Qt::KeepAspectRatio);
	interface1 = new QLabel(this);													//創建一個新的 QLabel，命名為 play，並將它設定為當前視窗（this）的子元素。
	interface1->setFixedSize(interface.size());								     	//設置play的大小與playbuttom的大小一樣
	interface1->setPixmap(interface);												//將縮放後的playbuttom設置到QLabel對象play中
	interface1->setObjectName("interface1");										       //指定物件名稱為"play"
	interface1->move(0, 120);											//將QLabel物件移動至視窗(x,y)之位置
	
	play->raise();

	background.load("./dataset/images/background.png");
	background = background.scaled(540, 960, Qt::KeepAspectRatio);

	bgOriginal.load("./dataset/images/bgOriginal.png");
	bgOriginal = bgOriginal.scaled(540, 960, Qt::KeepAspectRatio);

	blood.load("./dataset/images/blood.png");
	blood = blood.scaled(50, 50, Qt::KeepAspectRatio);

	top.load("./dataset/images/top.jpg");
	top = top.scaled(540, 100, Qt::KeepAspectRatio);

	blackhole.load("./dataset/images/blackhole.png");
	bullet.load("./dataset/images/bullet.png");
	doodleL.load("./dataset/images/doodleL.png");
	doodleR.load("./dataset/images/doodleR.png");
	doodleS.load("./dataset/images/doodleS.png");
	doodleUL.load("./dataset/images/doodleUL.png");
	doodleUR.load("./dataset/images/doodleUR.png");
	jetpack.load("./dataset/images/item-jetpack.png");
	hat.load("./dataset/images/item-propeller-hat.png");
	spring1.load("./dataset/images/item-spring1.png");
	spring2.load("./dataset/images/item-spring2.png");
	trampoline1.load("./dataset/images/item-trampoline1.png");
	trampoline2.load("./dataset/images/item-trampoline2.png");
	trampoline3.load("./dataset/images/item-trampoline3.png");
	monster01.load("./dataset/images/monster1.png");
	monster02.load("./dataset/images/monster2.png");
	monster03.load("./dataset/images/monster3.png");
	monster04.load("./dataset/images/monster4.png");

	stairgreen.load("./dataset/images/stair-basic.png");


	stairblue.load("./dataset/images/stair-blue.png");
	stairbroken1.load("./dataset/images/stair-broken1.png");
	stairbroken2.load("./dataset/images/stair-broken2.png");
	stairbroken3.load("./dataset/images/stair-broken3.png");
	stairbroken4.load("./dataset/images/stair-broken4.png");
	stairdissapear.load("./dataset/images/stair-disapear.png");
	doodleH1.load("./dataset/images/doodleH/doodleH1.png");
	doodleH2.load("./dataset/images/doodleH/doodleH2.png");
	doodleH3.load("./dataset/images/doodleH/doodleH3.png");
	doodleH4.load("./dataset/images/doodleH/doodleH4.png");
	doodleJ1.load("./dataset/images/doodleJ/doodleJ1.png");
	doodleJ2.load("./dataset/images/doodleJ/doodleJ2.png");
	doodleJ3.load("./dataset/images/doodleJ/doodleJ3.png");
	doodleJ4.load("./dataset/images/doodleJ/doodleJ4.png");
	doodleJ5.load("./dataset/images/doodleJ/doodleJ5.png");
	doodleJ6.load("./dataset/images/doodleJ/doodleJ6.png");
	doodleJ7.load("./dataset/images/doodleJ/doodleJ7.png");
	doodleJ8.load("./dataset/images/doodleJ/doodleJ8.png");
	doodleJ9.load("./dataset/images/doodleJ/doodleJ9.png");
	doodleJ10.load("./dataset/images/doodleJ/doodleJ10.png");

	doodleprotR.load("./dataset/images/doodleprotR.png");
	doodleprotR = doodleprotR.scaled(120, 120, Qt::KeepAspectRatio);
	doodleprotL.load("./dataset/images/doodleprotL.png");
	doodleprotL = doodleprotL.scaled(120, 120, Qt::KeepAspectRatio);


	stairthorn.load("./dataset/images/thorn stair.png");
	stairthorn = stairthorn.scaled(120, 50, Qt::KeepAspectRatio);

	stairdeepblue.load("./dataset/images/moveupdown.png");
	stairdeepblue = stairdeepblue.scaled(135, 50, Qt::KeepAspectRatio);

	stairred.load("./dataset/images/boom.png");
	stairred = stairred.scaled(121, 33, Qt::KeepAspectRatio);

	Protection.load("./dataset/images/protection.png");

	//生成子彈
	bullet.load("./dataset/images/bullet.png");
	move_bullet = new QLabel(this);
	move_bullet->setFixedSize(bullet.size());
	move_bullet->setPixmap(bullet);
}