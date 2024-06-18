#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RESULT=0
DIFF_RES=""

declare -a tests=(
"s test_text_grep.txt VAR"
"for s21_grep.c Makefile VAR"
"for s21_grep.c VAR"
"-e for -e ^int s21_grep.c Makefile VAR"
"-e for -e ^int s21_grep.c VAR"
"-e regex -e ^print s21_grep.c VAR -f test_ptrn_grep.txt"
"-e while -e void s21_grep.c Makefile VAR -f test_ptrn_grep.txt"
"VAR no_file.txt"
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-c -e /\ test_1_grep.txt"
"-e ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-n = test_1_grep.txt test_2_grep.txt"
"-e"
"-e -i INT test_5_grep.txt"
"-echar test_1_grep.txt test_2_grep.txt"
"-n -e = -e out test_5_grep.txt"
"-i int test_5_grep.txt"
"-i int test_5_grep.txt"
"-c -l aboba test_1.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-n -e ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-e int test_4_grep.txt"
"-e = -e out test_5_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    valgrind --leak-check=full --error-exitcode=1 ./s21_grep $t > test_s21_grep.log 2>&1
    valgrind_exit_code=$?
    ((COUNTER++))
    if [ $valgrind_exit_code -eq 0 ];
    then
      (( SUCCESS++ ))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (O)success (command): wvalg ./s21_grep $t"
    else
      (( FAIL++ ))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (!)fail (command): wvalg ./s21_grep $t"
        echo "$valgrind_exit_code"
        # valgrind --leak-check=full --error-exitcode=1 ./s21_grep $t
        echo "wvalg ./s21_grep $t"
        exit 0
    fi
    rm test_s21_grep.log
}

# specific tests
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# one param
for var1 in v c l n h
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# two params
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# three params
for var1 in v c l n h
do
    for var2 in v c l n h
    do
        for var3 in v c l n h
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done


echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
