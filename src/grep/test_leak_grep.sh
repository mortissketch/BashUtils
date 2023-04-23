#!/bin/bash

TEMPLATE_FILE="./TEST_FILES/example.txt"
TEMPLATE_FILE1="./TEST_FILES/test_grep/test_0_grep.txt"
TEMPLATE_FILE2="./TEST_FILES/test_grep/test_1_grep.txt"
TEMPLATE_FILE4="./TEST_FILES/test_grep/test_2_grep.txt"
TEMPLATE_FILE5="./TEST_FILES/test_grep/test_4_grep.txt"
TEMPLATE_FILE6="./TEST_FILES/test_grep/test_5_grep.txt"
TEMPLATE_FILE7="./TEST_FILES/test_grep/test_6_grep.txt"
TEMPLATE_FILE8="./TEST_FILES/test_grep/test_ptrn_grep.txt"
TEMPLATE_FILE9="./TEST_FILES/test_grep/test_3_grep.txt"


SUCCESS=0
FAIL=0
COUNTER=0
RESULT=0
DIFF_RES=""

declare -a tests=(
"s ${TEMPLATE_FILE1} VAR"
"for s21_grep.c s21_grep.h Makefile VAR"
"for s21_grep.c VAR"
"-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
"-e for -e ^int s21_grep.c VAR"
"-e regex -e ^print s21_grep.c VAR -f ${TEMPLATE_FILE8}"
"-e while -e void s21_grep.c Makefile VAR -f ${TEMPLATE_FILE8}"
"VAR no_file.txt"
)

declare -a extra=(
"-n for ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-n for ${TEMPLATE_FILE2}"
"-n -e ^\} ${TEMPLATE_FILE2}"
"-c -e /\ ${TEMPLATE_FILE2}"
"-ce ^int ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-e ^int ${TEMPLATE_FILE2}"
"-nivh = ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-e"
"-ie INT ${TEMPLATE_FILE6}"
"-echar ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-ne out ${TEMPLATE_FILE6}"
"-iv int ${TEMPLATE_FILE6}"
"-in int ${TEMPLATE_FILE6}"
"-c -l aboba test_1.txt ${TEMPLATE_FILE6}"
"-v ${TEMPLATE_FILE2} -e ank"
"-noe ) ${TEMPLATE_FILE6}"
"-l for ${TEMPLATE_FILE2} ${TEMPLATE_FILE4}"
"-o -e int ${TEMPLATE_FILE5}"
"-e = -e out ${TEMPLATE_FILE6}"
"-e as ${TEMPLATE_FILE7}"
"-e ing -e as -e the -e not -e is ${TEMPLATE_FILE7}"
"-c -e . ${TEMPLATE_FILE2} -e '.'"
"-l for no_file.txt ${TEMPLATE_FILE4}"
"-f test_3_grep.txt ${TEMPLATE_FILE6}"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    leaks -quiet -atExit -- ./s21_grep $t > test_s21_grep.log
    leak=$(grep -A100000 leaks test_s21_grep.log)
    (( COUNTER++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
      (( SUCCESS++ ))
       echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
        echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
#        echo "$leak"
    fi
    rm test_s21_grep.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n h o f
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 сдвоенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

# 3 строенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $i
                done
            fi
        done
    done
done

echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
