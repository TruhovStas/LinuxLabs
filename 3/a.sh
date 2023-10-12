directory="/home/Kir/Desktop/LinuxLabs/3/files"

for file in "$directory"/*; do
  if [[ -f "$file" && -x "$file" && "$file" == *.sh ]]; then
    echo "Выполняем скрипт: $file"
    $file
  fi
done
