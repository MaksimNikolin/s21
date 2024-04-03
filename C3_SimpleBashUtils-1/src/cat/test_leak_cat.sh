#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RESULT=0
DIFF_RES=""

declare -a tests=(
"VAR test_case_cat.txt"
"VAR no_file.txt"
)

declare -a extra=(
"-s test_1_cat.txt"
"-b -e -n -s -t test_1_cat.txt"
"-t test_3_cat.txt"
"-n test_2_cat.txt"
"no_file.txt"
"-n -b test_1_cat.txt"
"-s -n -e test_4_cat.txt"
"test_1_cat.txt -n"
"-n test_1_cat.txt"
"-n test_1_cat.txt test_2_cat.txt"
)

# testing()
# {
#     t=$(echo $@ | sed "s/VAR/$var/")
#     leaks -quiet -atExit -- ./s21_cat $t > test_s21_cat.log
#     leak=$(grep -A100000 leaks test_s21_cat.log)
#     (( COUNTER++ ))
#     if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
#     then
#       (( SUCCESS++ ))
#         echo "(!)$FAIL (O)$SUCCESS - $COUNTER (O)success (command): cat $t"
#     else
#       (( FAIL++ ))
#         echo "(!)$FAIL (O)$SUCCESS - $COUNTER (!)fail (command): cat $t"
# #        echo "$leak"
#     fi
#     rm test_s21_cat.log
# }

testing() {
    t=$(echo "$@" | sed "s/VAR/$var/")
    valgrind --leak-check=full --error-exitcode=1 ./s21_cat $t > test_s21_cat.log 2>&1
    valgrind_exit_code=$?
    ((COUNTER++))
    if [ $valgrind_exit_code -eq 0 ]; then
        ((SUCCESS++))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (O)success (command): ./s21_cat $t"

        # exit 0
    else
        ((FAIL++))
        echo "(!)$FAIL (O)$SUCCESS - $COUNTER (!)fail (command): ./s21_cat $t"
        # Можно добавить вывод информации об утечках памяти:
        # echo "Memory leaks detected:"
        # cat test_s21_cat.log | grep "ERROR SUMMARY"
        # exit 0
    fi
    rm test_s21_cat.log
}


# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in b e n s t
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in b e n s t
do
    for var2 in b e n s t
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

# 3 параметра
for var1 in b e n s t
do
    for var2 in b e n s t
    do
        for var3 in b e n s t
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

# 4 параметра
for var1 in b e n s t
do
    for var2 in b e n s t
    do
        for var3 in b e n s t
        do
            for var4 in b e n s t
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
