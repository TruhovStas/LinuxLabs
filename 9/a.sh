sort -t: peoples > sorted_peoples
sort -t: peoples1 > sorted_peoples1

comm -3 sorted_peoples sorted_peoples1 > uncommon

echo "Файл с уникальными словами создан"

