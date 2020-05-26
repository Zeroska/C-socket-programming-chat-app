echo "Executing script"
gcc -o lamb -g -Wall clientChat.c
gcc -o server -g -Wall serverChat.c
rm -rf *.dSYM