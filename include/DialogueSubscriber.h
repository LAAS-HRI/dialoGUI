#ifndef DIALOGUESUBSCRIBER_H
#define DIALOGUESUBSCRIBER_H

#include "std_msgs/String.h"
#include <string>
#include <iostream>

class DialogueSubscriber_callback
{
public:
  DialogueSubscriber_callback() {}
  ~DialogueSubscriber_callback() {}
  virtual void newLine(std::string name, std::string text) {}
};

class DialogueSubscriber
{
public:
  DialogueSubscriber(std::string name, std::string topic, std::string color, DialogueSubscriber_callback* interface)
  {
    name_ = name;
    topic_ = topic;
    color_ = color;
    interface_ = interface;
  }

  ~DialogueSubscriber(){}

  void messageCallback(const std_msgs::String::ConstPtr& msg)
  {
    std::string html = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                    "<span style=\" font-size:12pt; font-weight:600; color:#" + color_ + ";\">" + name_ + " : </span>"
                    "<span style=\" font-size:12pt; color:#" + color_ + ";\">" + msg->data + "</span>"
                    "</p>";
    interface_->newLine(name_ , html);
  }

private:
  std::string name_;
  std::string topic_;
  std::string color_;
  DialogueSubscriber_callback* interface_;
};

#endif
