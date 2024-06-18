#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
#"s test_0_grep.txt VAR"
#"for s21_grep.c Makefile VAR"
#"for s21_grep.c VAR"
#"-e for -e ^int s21_grep.c Makefile VAR"
#"-e for -e ^int s21_grep.c VAR"
#"-e regex -e ^print s21_grep.c VAR"
#"-e while -e void s21_grep.c Makefile VAR"
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-c -e /\ test_1_grep.txt"
"-e ^int test_1_grep.txt"
"-e"
"-echar test_1_grep.txt test_2_grep.txt"
"-e = -e out test_5_grep.txt"
"-i int test_5_grep.txt"
"-i int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-l for test_1_grep.txt test_2_grep.txt"
"-e = -e out test_5_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
)

testing()
{
    # if [ "$FAIL" -eq 5 ];  # If you want to see first 5 fails
    # then
    #    exit 0
    # fi
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (O)success (command): ./s21_grep $t"
    else
      (( FAIL++ ))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (!)fail (command): ./s21_grep $t"
        #  echo
        #  echo "./s21_grep $t"
        #  exit 0
    fi
    rm test_s21_grep.log test_sys_grep.log
}

# specific tests
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# one param
for var1 in v c l n
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# two params
for var1 in v c l n
do
    for var2 in v c l n
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
#for var1 in v c l n
#do
#    for var2 in v c l n
#    do
#        for var3 in v c l n
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1 -$var2 -$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done

echo "(!)FAIL: $FAIL"
echo "(O)SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
