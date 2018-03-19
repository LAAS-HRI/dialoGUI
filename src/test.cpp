#include "ros/ros.h"
#include <iostream>
#include <unistd.h>
#include "std_msgs/String.h"

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "dialoGUI_test");

  ros::NodeHandle n;

  ros::Publisher Martoni = n.advertise<std_msgs::String>("Martoni", 10000);
  ros::Publisher Odile = n.advertise<std_msgs::String>("Odile", 10000);
  ros::Publisher Kara = n.advertise<std_msgs::String>("Kara", 10000);
  ros::Publisher Simon = n.advertise<std_msgs::String>("Simon", 10000);
  ros::Publisher Commissaire = n.advertise<std_msgs::String>("Commissaire", 10000);

  std_msgs::String msg;

  usleep(3000000);
  msg.data = "Stop ! N’avancez plus Bialès. Je veux un hélicoptère. Je veux que vous donniez l’ordre à vos hommes de me laisser quitter le palais sans problème ! Sinon je la flingue ! Et ce coup ci plus de tapette pour vous sauver !";
  Martoni.publish(msg);
  usleep(3000000);
  msg.data = "S’il vous plaît monsieur est commissaire de police.";
  Odile.publish(msg);
  usleep(3000000);
  msg.data = "Tu bluffes Martoni ! Il bluffe.";
  Commissaire.publish(msg);
  usleep(3000000);
  msg.data = "Pas sûr.";
  Kara.publish(msg);
  usleep(3000000);
  msg.data = "Si, si, il bluffe là ça se voit tout de suite !";
  Simon.publish(msg);
  usleep(3000000);
  msg.data = "Non, il a pas l’air de bluffer là quand même hein.";
  Kara.publish(msg);
  usleep(3000000);
  msg.data = "Siiihiii ! Il bluffe là !";
  Commissaire.publish(msg);
  usleep(3000000);
  msg.data = "Euh moi je suis de l’avis de Bialès, il bluffe hein. On, on vote ? On vote ? Moi je vote et je dis il bluffe.";
  Simon.publish(msg);
  usleep(3000000);
  msg.data = "Ça suffit ! Vous essayez de gagner du temps.";
  Martoni.publish(msg);
  usleep(3000000);
  msg.data = "Bon vous l’aurez voulu. Je la butte !";
  Martoni.publish(msg);
  usleep(3000000);
  msg.data = "Tu bluffes Martoni ! Ton arme n’est pas chargée !";
  Commissaire.publish(msg);
  usleep(3000000);

  return 0;
}
