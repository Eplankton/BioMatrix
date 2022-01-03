printf "[Install]: Begins\n"
mkdir workplace
printf "[Install]: Creating workplace\n"
cp test.bmx src/egg src/help src/command_list workplace
printf "[Install]: Connecting source files\n"
gcc src/main.c -o workplace/biox -lm -w
printf "[Install]: Generating executive binary file\n"
cd workplace
printf "[Install]: Completed\n"
./biox
