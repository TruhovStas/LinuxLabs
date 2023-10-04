#!/bin/sh

while true; do
touch f1
echo "dollar 20000">f1
echo "euro 22000">>f1
echo "rus 300">>f1
selection=$(gdialog --menu "Select a currency:" 10 30 3 "dollar" "Dollar" "euro" "Euro" "rus" "Russian Ruble" "exit" "Exit" 2>&1
)
if [ "$selection" = "exit" ]
then
echo "Exiting the script"
exit 0
elif [ "$selection" = "dollar" ]
then
echo "dollar = 20000 rub"
elif [ "$selection" = "euro" ]
then
echo "euro = 23000 rub"
else
echo "we do not know for $selection"
fi
done
