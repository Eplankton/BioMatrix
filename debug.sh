printf "[Debug]: BEGIN\n\n"
mkdir runtime
cp test.bmx src/egg src/command_list runtime
gcc src/main.c -o runtime/biox_debug -lm -w
cd runtime
./biox_debug < test.bmx
cd ..
rm runtime -rf
printf "[Debug]: END\n\n"
