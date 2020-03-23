#include "painter.h"
#include <QVBoxLayout>
#include <QDebug>
Painter::Painter(QWidget *parent, QStringListModel *qslm, QList<QPair<double, double>> *ql)
	: QWidget(parent)
{
	inputListModel = qslm;
	intersectpoints = ql;


}

void Painter::paintEvent(QPaintEvent *event)
{


	QPainter painter(this);
	QTransform transform;
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	//painter.save();

	//绘制坐标轴
	int side = qMin(width(), height()); //创建窗口宽高参数
	painter.translate(width() / 2, height() / 2); //坐标系统平移变换,把原点平移到窗口中心
	//painter.scale(side / 300.0,side / 300.0); //坐标系统比例变换,使绘制的图形随窗口的放大而放大
	painter.scale(1, -1); //Y轴向上翻转,翻转成正常平面直角坐标系
	painter.setPen(QPen(Qt::black, height() / 600));
	painter.drawLine(-2000, 0, 2000, 0);
	painter.drawLine(0, 1500, 0, -1500);

	//刻度
	int offset = qMax(width() / 2 / 50, 1); //最小刻度是1，scale<=25
	double sizeBase = 5;
	int numSize = 20;

	//int scale = 10; //整除10 scale对交点、直线、射线、线段、圆有正比例作用；对刻度有反比例作用
	for (int i = 0; i < 50; i++)
	{
		double lineSize = sizeBase;
		if (i % 5 == 0)
		{
			painter.save();
			painter.scale(1, -1); //Y轴向上翻转
			painter.drawText(offset*i, numSize, QString::number(offset*i / scale));
			if (i != 0)
			{
				painter.drawText(-offset * i, numSize, QString::number(-offset * i / scale));
				painter.rotate(+90);
				painter.drawText(offset*i, numSize, QString::number(-offset * i / scale));
				painter.drawText(-offset * i, numSize, QString::number(offset*i / scale));
			}
			lineSize = sizeBase * 2;
			painter.restore();
		}
		//x刻度 50个
		painter.drawLine(offset*i, 0, offset*i, lineSize);
		painter.drawLine(-offset * i, 0, -offset * i, lineSize);
		//y刻度 50个
		painter.drawLine(0, offset*i, lineSize, offset*i);
		painter.drawLine(0, -offset * i, lineSize, -offset * i);
	}

	//x箭头
	offset = 10;
	int x = width() / 2;
	int y = 0;
	QPoint arrowLeftPoint1(x, y);
	QPoint arrowTopPoint1(x - offset, y - offset / 2);  //箭头的两条线与x轴夹角30度
	QPoint arrowBotPoint1(x - offset, y + offset / 2);
	static const QPoint arrowPoints1[3] = {
		arrowLeftPoint1,arrowTopPoint1,arrowBotPoint1,
	};
	painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	painter.drawPolygon(arrowPoints1, 3);
	painter.drawText(x - numSize, -numSize, tr("x"));

	//y箭头
	x = 0;
	y = height() / 2;
	QPoint arrowLeftPoint2(x, y);
	QPoint arrowTopPoint2(x - offset / 2, y - offset);  //箭头的两条线与x轴夹角30度
	QPoint arrowBotPoint2(x + offset / 2, y - offset);
	static const QPoint arrowPoints2[3] = {
		arrowLeftPoint2,arrowTopPoint2,arrowBotPoint2,
	};
	painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	painter.drawPolygon(arrowPoints2, 3);
	painter.save();
	painter.scale(1, -1); //Y轴向上翻转
	painter.drawText(-numSize, -y + numSize, tr("y"));
	painter.restore();

	//绘制几何体
	painter.setBrush(Qt::transparent);
	//    painter.drawLine(-100,-100,100,100);
	//    painter.drawEllipse(-50,-50,100,100);
	//inputListModel =
	if (inputListModel)
	{

		QStringList data = inputListModel->stringList();
		//QStringList data = inputListModel.;
		foreach(QString s, data)
		{
			qDebug() << "yes";
			QStringList list = s.split(" ");
			QString type = list[0];

			if (type == "L") {
				int x1 = list[1].toInt()*scale;
				int y1 = list[2].toInt()*scale;
				int x2 = list[3].toInt()*scale;
				int y2 = list[4].toInt()*scale;
				double a = y1 - y2;
				double b = x2 - x1;
				double c = x1 * y2 - x2 * y1;
				double boundary = 2000 * scale;
				//k = -A/B
				if (b != 0) {
					painter.drawLine(boundary, (-c - a * boundary) / b, -boundary, (-c + a * boundary) / b);
				}
				else
				{
					painter.drawLine(-c / a, boundary, -c / a, -boundary);
				}
			}
			else if (type == "S") {
				int x1 = list[1].toInt()*scale;
				int y1 = list[2].toInt()*scale;
				int x2 = list[3].toInt()*scale;
				int y2 = list[4].toInt()*scale;
				painter.drawLine(x1, y1, x2, y2);
			}
			else if (type == "R") {
				int x1 = list[1].toInt()*scale;
				int y1 = list[2].toInt()*scale;
				int x2 = list[3].toInt()*scale;
				int y2 = list[4].toInt()*scale;
				double a = y1 - y2;
				double b = x2 - x1;
				double c = x1 * y2 - x2 * y1;
				double boundary = 2000 * scale;
				if (x2 > x1) {
					painter.drawLine(x1, y1, boundary, (-c - a * boundary) / b);
				}
				else if (x2 < x1)
				{
					painter.drawLine(x1, y1, -boundary, (-c + a * boundary) / b);
				}
				else if (x2 == x1 && y2 > y1)
				{
					painter.drawLine(x1, y1, (-b * boundary - c) / a, boundary);
				}
				else
				{
					painter.drawLine(x1, y1, (b*boundary - c) / a, -boundary);
				}
			}
			else if (type == "C") {
				int x = list[1].toInt()*scale;
				int y = list[2].toInt()*scale;
				int r = list[3].toInt()*scale;
				painter.drawEllipse(x - r, y - r, 2 * r, 2 * r);
			}
		}

	}


	//绘制交点
	painter.setPen(QPen(Qt::blue, 5));
	if (intersectpoints)
	{
		for (int i = 0; i < intersectpoints->size(); i++)
		{
			QPair<double, double> point = intersectpoints->at(i);
			painter.drawPoint(point.first*scale, point.second*scale);
		}
	}

}

void Painter::magnifyFigure()
{
	if (scale < 25) {
		scale = scale * 5;
	}
	update();
}

void Painter::reduceFigure()
{
	if (scale > 5) {
		scale = scale / 5;
	}
	update();
}
