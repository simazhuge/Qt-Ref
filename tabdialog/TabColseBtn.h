#ifndef TABCOLSEBTN_H
#define TABCOLSEBTN_H

#include <QPushButton>
class QMouseEvent;
class TabColseBtn : public QPushButton
{
	   Q_OBJECT

public:
    TabColseBtn(QWidget *parent = 0);
	~TabColseBtn();
signals:
	void clicked(QWidget* );
 
private:
	QWidget *tabWidget;
	
};

#endif // TABCOLSEBTN_H
