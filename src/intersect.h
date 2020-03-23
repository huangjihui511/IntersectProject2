#pragma once

#include <QtWidgets/QWidget>
#include <QDialog>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QString>
#include <QLineEdit>
#include <QImage>
#include <QPainter>
#include <QLabel>
#include "Painter.h"
#include <QPair>

//#include "ui_intersect.h"

class intersect : public QWidget
{
	Q_OBJECT
private:

	QPushButton *addButton;
	QPushButton *deletButton;
	QPushButton *updateButton;
	QPushButton *importButton;
	QPushButton *magnifyButton;
	QPushButton *reduceButton;
	QStringListModel *inputListModel;
	QStringList *inputList;

	QListView *inputListView;
	QLineEdit *inputEdit;
	QLabel *errorInformation;

	QLabel *intersectSize;

	QListView *intersectView;
	Painter *painter;
	QList<QPair<double, double>> *intersectpoints;

public:
	intersect(QWidget *parent = Q_NULLPTR);
	void initUI();
	void iniSignalSlots();

private slots:
	void addInput();
	void deleteInput();
	void updateFigure();
	void showError(QString e);
	void importFile();

//	Ui::intersectClass ui;
};
