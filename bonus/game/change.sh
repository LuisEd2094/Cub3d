for file in *.c; do
    new_name="${file%.c}_bonus.c"
    mv "$file" "$new_name"
    echo "Renamed $file to $new_name"
done