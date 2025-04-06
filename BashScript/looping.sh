#!/bin/bash

# Enable debugging mode
echo "Enable debugging mode"
set -x
set -e

echo "While looping"
i=1
while [[ $i -le 10 ]]; do
    echo "$i"
    (( i += 1))
done

echo "For looping"
for i in {1..5}; do
    echo "$i"
done

echo "Case statement"
echo "Type a type of fruit (apple, banana, orange, ...)"
read fruit

case $fruit in
    "apple")
        echo "This is a red fruit."
        ;;
    "banana")
        echo "This is a yellow fruit."
        ;;
    "orange")
        echo "This is an orange fruit."
        ;;
    *)
        echo "Unknown fruit."
        ;;
esac

set +u
