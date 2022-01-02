mkdir runtime
cp test.bmx src/egg src/command_list runtime
gcc src/main.c -o biox -lm -w
mv biox runtime
cd runtime
./biox < test.bmx
cd ..
rm runtime -rf
