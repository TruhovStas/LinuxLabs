sort -t: peoples peoples1 | uniq -d > common

total_words=$(wc -w < common)

echo "Общее количество одинаковых слов: $total_words"
