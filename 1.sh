#!/bin/bash

# Создаем неименованный канал
PIPE=$(mktemp -u)
mkfifo $PIPE

# Именованный канал
NAMED_PIPE="named_pipe"
mkfifo $NAMED_PIPE

# Функция для получения информации об операционной системе
get_os_info() {
    echo "Week of semester: 12"
    echo "Operating System: $(cat /etc/os-release | grep PRETTY_NAME | cut -d= -f2)"
    echo "Kernel Version: $(uname -r)"
}

# Функция для получения системной даты и времени
get_date_time() {
    echo "Date and Time: $(date)"
}

# Функция для получения календаря
get_calendar() {
    echo "Calendar:"
    cal
}

# Функция для записи информации в неименованный канал
write_to_pipe() {
    get_os_info >$PIPE
    get_date_time >$PIPE
    get_calendar >$PIPE
    echo "END" >$PIPE
}

# Функция для записи информации в именованный канал
write_to_named_pipe() {
    get_os_info >$NAMED_PIPE
    get_date_time >$NAMED_PIPE
    get_calendar >$NAMED_PIPE
    echo "END" >$NAMED_PIPE
}

# Запускаем функцию записи в фоновом режиме
write_to_pipe &

# Запускаем функцию записи в именованный канал в фоновом режиме
write_to_named_pipe &

# Читаем из неименованного канала
while read line; do
    if [ "$line" == "END" ]; then
        break
    fi
    echo $line
done <$PIPE

# Читаем из именованного канала
while read line; do
    if [ "$line" == "END" ]; then
        break
    fi
    echo $line
done <$NAMED_PIPE

# Удаляем временные файлы
rm $PIPE
rm $NAMED_PIPE
