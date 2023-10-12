#!/bin/bash

read -p "Введите номер семестра: " semester
read -p "Введите номер лабы: " lab

directory="/home/stas/LinuxLabsSem$semester"

if [ ! -d "$directory" ]; then
  mkdir "$directory"
fi

directory="/home/stas/LinuxLabsSem$semester/Lab$lab"

if [ ! -d "$directory" ]; then
  mkdir "$directory"
  touch "/home/stas/LinuxLabsSem$semester/Lab$lab/Task{$lab}1"
  touch "/home/stas/LinuxLabsSem$semester/Lab$lab/Task{$lab}2"
  touch "/home/stas/LinuxLabsSem$semester/Lab$lab/Task{$lab}3"
fi
