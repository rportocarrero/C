# compile program
echo compiling program ...
cc -o hello hello.c 
echo
# run to verify functionality
echo testing output ...
./hello 
echo
# compile but do not link
echo compiling without linking ...
gcc -c -o hello.o hello.c 
echo

# view symbol dump of the object file
echo symbol dump of unlinked program ...
nm hello.o 
echo

# link the program to a memory location
echo linking program into elf file ...
gcc hello.o -o hello.elf 
echo

# veify that the symbols are assigned memory values.
echo symbol dump of elf file ...
nm hello.elf 
echo

# run the program.
echo runing linked elf file ...
./hello.elf 
echo 

# check that we didn't miss any steps
echo comparing compiled version with linked version ...
diff hello hello.elf 
echo