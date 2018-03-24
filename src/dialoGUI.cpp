#include "include/dialoGUI.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

#include <string>
#include <iostream>

dialoGUI::dialoGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dialoGUI)
{
    ui->setupUi(this);

    n_ = nullptr;

    QObject::connect(ui->cleanButton, SIGNAL(clicked()),this, SLOT(on_cleanButton_clicked()));
    QObject::connect( this, SIGNAL( MySignal(QString) ), ui->dialogue, SLOT( setHtml(QString) ) );
    QObject::connect( this, SIGNAL( ScrollBarSignal(int) ), ui->dialogue->verticalScrollBar(), SLOT( setValue(int) ) );
    QObject::connect( ui->dialogue->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT( on_range_Changed(int, int) ));


    cpt = 0;
    colors.push_back("a40000");
    colors.push_back("00a400");
    colors.push_back("5555d4");
    colors.push_back("a4a400");
    colors.push_back("a400a4");
    colors.push_back("00a4a4");

    colors.push_back("a45400");
    colors.push_back("a40054");
    colors.push_back("00a454");

    colors.push_back("54a400");
    colors.push_back("5400a4");
    colors.push_back("0054a4");

    colors.push_back("a46444");
    colors.push_back("a40064");
    colors.push_back("44a464");

    colors.push_back("64a444");
    colors.push_back("6444a4");
    colors.push_back("4464a4");

    setInitText();
}

dialoGUI::~dialoGUI()
{
  for(int i = 0; i < subscribers.size(); i++)
    delete subscribers[i];

  delete ui;
}

void dialoGUI::on_cleanButton_clicked()
{
    ui->dialogue->clear();
    setInitText();
}

void dialoGUI::on_range_Changed(int min, int max)
{
  /*if(max != 0)
    while(ui->dialogue->verticalScrollBar()->value() != max)
      ScrollBarSignal(max);*/

}

void dialoGUI::setInitText()
{
    QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                    "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                    "p, li { white-space: pre-wrap; }"
                    "</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">"
                    "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /><br /><br /></p>"
                    "</body></html>";
    ui->dialogue->setHtml(html);
}

void dialoGUI::newLine(std::string name, std::string text)
{
  std::string prev = ui->dialogue->toHtml().toStdString();
  std::string begin = prev.substr(0, prev.size() - std::string("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /><br /><br /></p></body></html>").size());
  prev = begin + text + "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /><br /><br /></p></body></html>";
  MySignal(QString::fromStdString(prev));
  int max = ui->dialogue->verticalScrollBar()->maximum();
  while(ui->dialogue->verticalScrollBar()->value() != max)
    ScrollBarSignal(max);
}

void dialoGUI::addId(std::string name, std::string topic)
{
    colorMap[name] = colors[cpt];
    cpt++;
    if(cpt > colors.size() - 1)
        cpt = colors.size() - 1;

    DialogueSubscriber* tmp = new DialogueSubscriber(name, topic, colorMap[name], this);
    subscribers.push_back(tmp);
    if(n_ != nullptr)
    {
      ros_subscribers.push_back(n_->subscribe(topic, 10000, &DialogueSubscriber::messageCallback, tmp));
      std::cout << "subscribe to " << topic << std::endl;
    }
    else
      std::cout << "Can't subscribe to " << topic << std::endl;
}
