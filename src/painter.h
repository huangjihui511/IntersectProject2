#pragma once

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QStringListModel>
class Painter : public QWidget
{
	Q_OBJECT
		QPushButton *b;
	int flag = 0;

public:
	Painter(QWidget *parent, QStringListModel *qslm, QList<QPair<double, double>> *ql);
	//~Painter();
	void drawGeometries(QString s);
	void paintLine(int x1, int y1, int x2, int y2);
	void paintSegment(int x1, int y1, int x2, int y2);
	void paintRay(int x1, int y1, int x2, int y2);
	void paintCircle(int x, int y, int r);

	QList<QPair<double, double>> *intersectpoints;
	QStringListModel *inputListModel;
	int scale = 10;
protected:
	void paintEvent(QPaintEvent *event);
public slots:
	void magnifyFigure();
	void reduceFigure();
};
