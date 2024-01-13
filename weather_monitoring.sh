gcc -c main.c -o main.o
gcc -c analyze_data.c -o analyze_data.o
gcc -c date_util.c -o date_util.o
gcc -c retrieve_data.c -o retrieve_data.o
gcc -c display_data.c -o display_data.o
gcc -c process_data.c -o process_data.o

gcc main.o analyze_data.o date_util.o retrieve_data.o display_data.o process_data.o -o project -lcurl -lcjson

rm main.o
rm analyze_data.o
rm date_util.o
rm retrieve_data.o
rm display_data.o
rm process_data.o

./project