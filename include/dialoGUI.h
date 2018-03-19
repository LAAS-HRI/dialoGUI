#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>

#include "DialogueSubscriber.h"
#include "ros/ros.h"

namespace Ui {
class dialoGUI;
}

class dialoGUI : public QMainWindow, public DialogueSubscriber_callback
{
  Q_OBJECT
public:
    explicit dialoGUI(QWidget *parent = 0);
    void messageCallback(const std_msgs::String::ConstPtr& msg);
    ~dialoGUI();

    void addId(std::string name, std::string topic);

    void init(ros::NodeHandle* n) {n_ = n; }

private slots:
    void on_cleanButton_clicked();

signals:
    void MySignal(QString);
    void ScrollBarSignal(int);

private:
    Ui::dialoGUI *ui;
    std::vector<DialogueSubscriber*> subscribers;
    std::vector<ros::Subscriber> ros_subscribers;
    std::vector<std::string> colors;
    std::map<std::string, std::string> colorMap;
    int cpt;
    ros::NodeHandle* n_;
    ros::Subscriber sub;

    void setInitText();
    void newLine(std::string name, std::string text);
};

#endif // MAINWINDOW_H
