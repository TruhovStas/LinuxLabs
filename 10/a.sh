sort -t: -k2 -n peoples | head -n1 | awk -F: '{print $1}'

