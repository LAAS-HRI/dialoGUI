#include "include/dialoGUI.h"
#include "include/DarkStyle.h"
#include <QApplication>
#include <QSize>

#include "ros/ros.h"
#include <iostream>
#include <thread>

void spin()
{
    ros::spin();
}

int main(int argc, char *argv[])
{
    std::string name = std::string(argv[1]);
    std::cout << "name " << name << std::endl;
    char *p;
    size_t width = strtol(argv[2], &p, 10);
    size_t height = strtol(argv[3], &p, 10);
    std::vector<std::string> ids;
    std::vector<std::string> topics;

    int nb_topic = argc - 6;
    if(nb_topic % 2 != 0)
    {
      std::cout << "nb topic must be pair" << std::endl;
      return -1;
    }
    else
      nb_topic = nb_topic/2;

    for(int i = 0; i < nb_topic; i++)
      ids.push_back(std::string(argv[4 + i]));

    for(int i = 0; i < nb_topic; i++)
      topics.push_back(std::string(argv[4 + nb_topic + i]));

    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);
    dialoGUI w;
    w.setWindowTitle(QString::fromStdString(name));

    QSize size(width,height);

    w.resize(size);
    w.show();

    ros::init(argc, argv, "dialoGUI", ros::init_options::AnonymousName);

    ros::NodeHandle n;
    w.init(&n);
    for(int i = 0; i < topics.size(); i++)
    {
      std::cout << "id " << ids[i] << std::endl;
      std::cout << "topic " << topics[i] << std::endl;
      w.addId(ids[i], topics[i]);
    }

    std::thread t1(spin);

    return a.exec();
}
