#!/bin/bash
# sys_info_page: программа вывода страницы с информацией о системе
PROGNAME=$(basename $0)
TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"
report_uptime () {
cat <<- _EOF_
<H2>System Uptime</H2>
<PRE>$(uptime)</PRE>
_EOF_
return
}
report_disk_space () {
cat <<- _EOF_
<H2>Disk Space Utilization</H2>

<PRE>$(df -h)</PRE>
_EOF_
return
}

report_home_space () {
    local format="%8s%10s%10s\n"
    local i dir_list total_files total_dirs total_size user_name
    user_name=$(zenity --entry --title="Выберите пользователя" --text="Введите имя пользователя:")
    if [ -z "$user_name" ]; then
        zenity --info --text="Пользователь не выбран. Завершение..."
        return
    fi
    if [ "$user_name" == "root" ]; then
        dir_list="/home/*"
    else
        dir_list="/home/$user_name"
    fi

    echo "<H2>Home Space Utilization ($user_name)</H2>"
    for i in $dir_list; do
        total_files=$(find $i -type f | wc -l)
        total_dirs=$(find $i -type d | wc -l)
        total_size=$(du -sh $i | cut -f 1)
        echo "<H3>$i</H3>"
        echo "<PRE>"
        printf "$format" "Dirs" "Files" "Size"
        printf "$format" "----" "-----" "----"
        printf "$format" $total_dirs $total_files $total_size
        echo "</PRE>"
    done
}

usage () {
echo "$PROGNAME: usage: $PROGNAME [-f file | -i]"
return
}
write_html_page () {
cat <<- _EOF_
<HTML>
<HEAD>
<TITLE>$TITLE</TITLE>
</HEAD>
<BODY>

<H1>$TITLE</H1>
<P>$TIME_STAMP</P>
$(report_uptime)
$(report_disk_space)
$(report_home_space)
</BODY>
</HTML>
_EOF_
return
}
# обработка параметров командной строки
interactive=
filename=
while [[ -n $1 ]]; do
case $1 in
-f | --file)
shift
filename=$1
;;
-i | --interactive) interactive=1
;;
-h | --help)
usage
exit
;;
*) usage >&2
exit 1
;;
esac
shift
done
# интерактивный режим
if [[ -n $interactive ]]; then
while true; do
read -p "Enter name of output file: " filename
if [[ -e $filename ]]; then
read -p "'$filename' exists. Overwrite? [y/n/q] > "
case $REPLY in
Y|y) break
;;
Q|q) echo "Program terminated."
exit
;;
*) continue
;;
esac
fi
done
fi
# вывод страницы html
if [[ -n $filename ]]; then
if touch $filename && [[ -f $filename ]]; then
write_html_page > $filename
else
echo "$PROGNAME: Cannot write file '$filename'" >&2
exit 1
fi
else
write_html_page
fi
