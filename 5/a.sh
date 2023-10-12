echo "Путь к bash: $(which bash)"

echo "Путь к sh: $(which sh)"

echo "Путь к dash: $(which dash)"

echo "Текущий интерпретатор: $(ps -p $$ -o comm=)"
