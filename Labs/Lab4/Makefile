TESTS = test1
DEBUG = 0
DIFFFLAGS = -b

user_interaction: main.c
	gcc -o reverse_array_user_interaction_version main.c
	./reverse_array_user_interaction_version

reverse_array: main.c
	gcc -D DEBUG=$(DEBUG) -o reverse_array main.c

test1: reverse_array
	./reverse_array < test1_in.txt > my_test1_out.txt
	diff $(DIFFFLAGS) test1_out.txt my_test1_out.txt

test2: reverse_array
	./reverse_array < test2_In.txt > test2_Out.txt
	diff $(DIFFFLAGS) test2_ExpOut.txt test2_Out.txt

test3: reverse_array
	./reverse_array < test3_In.txt >test3_Out.txt
	diff $(DIFFFLAGS) test3_ExpOut.txt test3_Out.txt

test4: reverse_array
	./reverse_array < test4_In.txt > test4_Out.txt
	diff $(DIFFFLAGS) test4_ExpOut.txt test4_Out.txt

test5: reverse_array
	./reverse_array < test5_In.txt > test5_Out.txt
	diff $(DIFFFLAGS) test5_ExpOut.txt test5_Out.txt

test6:reverse_array
	./reverse_array < test6_In.txt > test6_Out.txt
	diff $(DIFFFLAGS) test6_ExpOut.txt test6_Out.txt	       

test7:reverse_array
	./reverse_array < test7_In.txt > test7_Out.txt
	diff $(DIFFFLAGS) test7_ExpOut.txt test7_Out.txt 
clean:
	/bin/rm -rf reverse_array reverse_array_user_interaction_version a.out my*out.txt
