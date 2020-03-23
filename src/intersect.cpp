#include "intersect.h"

#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <string>
#include <QFileDialog>
#include <QtDebug>
#include <string>
#include "core.h"

using namespace std;

intersect::intersect(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	iniSignalSlots();
}


void intersect::initUI()
{
	inputList = new QStringList();
	intersectpoints = new QList<QPair<double, double>>;

	inputListModel = new QStringListModel(this);
	inputListModel->setStringList(*inputList);

	QVBoxLayout *VLay = new QVBoxLayout;

	QVBoxLayout *HLay1 = new QVBoxLayout;
	inputListView = new QListView;
	inputListView->setModel(inputListModel);

	HLay1->addWidget(inputListView);

	QVBoxLayout *HLay2 = new QVBoxLayout;
	addButton = new QPushButton(this);
	addButton->setText("ADD OBJECT");
	deletButton = new QPushButton(this);
	deletButton->setText("DEL OBJECT");
	HLay2->addWidget(addButton);
	HLay2->addWidget(deletButton);

	updateButton = new QPushButton(this);
	updateButton->setText("UPD FIGURE");
	HLay2->addWidget(updateButton);
	importButton = new QPushButton(this);
	importButton->setText("IMPORT FILE");
	HLay2->addWidget(importButton);

	magnifyButton = new QPushButton(this);
	magnifyButton->setText("STRETCH *5");
	HLay2->addWidget(magnifyButton);
	reduceButton = new QPushButton(this);
	reduceButton->setText("STRETCH /5");
	HLay2->addWidget(reduceButton);

	inputEdit = new QLineEdit;
	inputEdit->setText("L 0 0 1 1");
	painter = new Painter(this, inputListModel, intersectpoints);
	painter->setMinimumSize(1000, 1000);

	VLay->addLayout(HLay2);
	VLay->addLayout(HLay1);
	VLay->addWidget(inputEdit);
	errorInformation = new QLabel;
	errorInformation->setFixedWidth(200);
	errorInformation->setMaximumHeight(400);
	errorInformation->setWordWrap(true);
	errorInformation->setText("Welcome");

	VLay->addWidget(errorInformation);

	intersectView = new QListView;

	intersectSize = new QLabel;
	intersectSize->setText("NUM:?");

	QVBoxLayout *VLay2 = new QVBoxLayout;
	VLay2->addWidget(intersectSize);
	VLay2->addWidget(intersectView);


	QHBoxLayout *Lay = new QHBoxLayout;
	Lay->addLayout(VLay);
	Lay->addWidget(painter);
	Lay->addLayout(VLay2);
	Lay->setStretchFactor(VLay, 1);
	Lay->setStretchFactor(painter, 100);
	Lay->setStretchFactor(VLay2, 1);

	setLayout(Lay);
}

void intersect::iniSignalSlots()
{
	//������ɫ QRadioButton ��clicked()�ź���setTextFontColor()�ۺ�������
	connect(addButton, SIGNAL(clicked()), this, SLOT(addInput()));
	connect(deletButton, SIGNAL(clicked()), this, SLOT(deleteInput()));
	connect(updateButton, SIGNAL(clicked()), this, SLOT(updateFigure()));
	connect(importButton, SIGNAL(clicked()), this, SLOT(importFile()));

	connect(magnifyButton, SIGNAL(clicked()), painter, SLOT(magnifyFigure()));
	connect(reduceButton, SIGNAL(clicked()), painter, SLOT(reduceFigure()));
}

void intersect::importFile()
{
	//�����ļ��Ի�����
	QFileDialog *fileDialog = new QFileDialog(this);
	//�����ļ��Ի������
	fileDialog->setWindowTitle(tr("File"));
	//����Ĭ���ļ�·��
	fileDialog->setDirectory(".");
	//�����ļ�������
	fileDialog->setNameFilter(tr("TXT(*.txt)"));
	//���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//������ͼģʽ
	fileDialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames)
		qDebug() << tmp << endl;
	if (fileNames.size() == 0) {
		return;
	}

	//TODO:
	//UI����ʾtxt����ļ����壬�ļ�̫��
	//ֻ��ʾ�ֶ����ӵļ�����
	//��filename����core.addGeometries����core����
	//core.addGeometries���������Ƿ�����
	//if ������ȷ������core.intersect
	//else��������ϢshowError()

	QFile file(fileNames[0]);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream data(&file);
	QString line;
	while (!data.atEnd())//���ж�ȡ�ı�����ȥ��ÿ�еĻس�
	{
		line = data.readLine();
		line.remove('\n');
		inputListModel->insertRow(0);
		QModelIndex index = inputListModel->index(0);
		inputListModel->setData(index, line, Qt::DisplayRole);
		inputListView->setCurrentIndex(index);
		qDebug() << line << endl;
		//fonts< ui->listWidget->addItems(fonts);//�Ѹ�����ӵ�listwidget
	}
	//showError();

}

void intersect::deleteInput()
{
	QModelIndex index = inputListView->currentIndex();
	inputListModel->removeRow(index.row());
	updateFigure();
	
}

void intersect::addInput()
{
	inputListModel->insertRow(0);
	QModelIndex index = inputListModel->index(0);
	string text = inputEdit->text().toStdString();
	inputListModel->setData(index, inputEdit->text(), Qt::DisplayRole);
	inputListView->setCurrentIndex(index);
	QString e = QString::fromStdString(errorinformation(text));
	//showError(e);
	updateFigure();
	if (e != "object is valid") {
		deleteInput();
	}
}

void intersect::showError(QString e)
{
	errorInformation->setText(e);
}

void intersect::updateFigure()
{
	
	Core core;
	for (int i = 0; i < inputListModel->stringList().size(); i++) {
		core.addGeomrtie(inputListModel->stringList().at(i).toStdString());
	}
	int result = core.intersect();

	QStringList *qls = new QStringList();

	for (auto it = core.intersections.begin(); it != core.intersections.end(); it++) {
		qls->append("(" + QString::number(it->first) + "," + QString::number(it->second) + ")");
	}
	/* qDebug() << "result is" << result << "error size is" << core.errorInformations.size() <<
		"obj size is" << core.geomrties.size() <<
		"input list size is" << inputList->size() <<
		"input list model" << inputListModel->stringList();
	*/
	QStringListModel *qlsm = new QStringListModel(this);
	qlsm->setStringList(*qls);
	intersectView->setModel(qlsm);
	intersectSize->setText("NUM:" + QString::number(intersectpoints->size()));
	//���»�
	//intersectSize->setNum(result);
	painter->intersectpoints = intersectpoints;     //����ָ���ǲ�������������Ԫ�ص�ʱ�򲻻��
	painter->inputListModel = inputListModel;
	update();
	QString e = "";
	for (int i = 0; i < core.errorInformations.size(); i++) {
		e += QString::number(i + 1) + ":" + QString::fromStdString(core.errorInformations.at(i)) + "\n";
	}showError(e);

}