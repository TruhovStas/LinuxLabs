#!/bin/sh

touch f1
echo "dollar 20000">f1
echo "euro 22000">>f1
echo "rus 300">>f1
z=$(gdialog --inputbox "Your currency?\n 1.dollar\n2.euro\n3.exit " 5 20 2>&1)
if [ "$z" = "exit" ]
then
echo "Exiting the script"
exit 0
elif [ "$z" = "dollar" ]
then
echo "dollar = 20000 rub"
elif [ "$z" = "euro" ]
then
echo "euro = 23000 rub"
else
echo "we do not know for $z"
fi

