#!/bin/bash

temp_file=$(mktemp)
line_number=0

while IFS= read -r line; do
    position=0
    octal_line=$(echo -n "$line" | od -b -A none)
    octal_line=${octal_line# }

    for octal_char in $octal_line; do
        echo -n "tput cup $line_number $position; printf '\\$octal_char'" >> "$temp_file"
        
        position=$((position + 1))

        if [ -n "$1" ]; then
            echo "; sleep $1" >> "$temp_file"
        else
            echo >> "$temp_file"
        fi
    done

    line_number=$((line_number + 1))
done

echo "tput clear" > "${temp_file}2"

shuf "$temp_file" >> "${temp_file}2"

chmod +x "${temp_file}2"
"${temp_file}2"

rm -f "$temp_file" "${temp_file}2"

tput cup $((line_number + 1)) 0
