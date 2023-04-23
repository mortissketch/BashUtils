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
"VAR for ^int s21_grep.c s21_grep.h Makefile"
"VAR for ^int s21_grep.c"
"VAR ^print s21_grep.c ${TEMPLATE_FILE8}"
"-e while void s21_grep.c Makefile ${TEMPLATE_FILE8}"
)


declare -a extra=(
"-n for ${TEMPLATE_FILE1} ${TEMPLATE_FILE2}"
"-n for ${TEMPLATE_FILE1}"
"-n -e ^\} t${TEMPLATE_FILE1}"
"-c -e /\ ${TEMPLATE_FILE1}"
"-ce ^int ${TEMPLATE_FILE1} ${TEMPLATE_FILE2}"
"-e ^int ${TEMPLATE_FILE1}"
"-nivh = ${TEMPLATE_FILE1} ${TEMPLATE_FILE2}"
"-e"
"-ie INT ${TEMPLATE_FILE5}"
"-echar ${TEMPLATE_FILE1} ${TEMPLATE_FILE2}"
"-ne = -e out ${TEMPLATE_FILE5}"
"-iv int ${TEMPLATE_FILE5}"
"-in int ${TEMPLATE_FILE5}"
"-v ${TEMPLATE_FILE1} -e ank"
"-noe ) ${TEMPLATE_FILE5}"
"-l for ${TEMPLATE_FILE1} ${TEMPLATE_FILE2}"
"-o -e int ${TEMPLATE_FILE4}"
"-e = -e out ${TEMPLATE_FILE5}"
"-noe ing -e as -e the -e not -e is ${TEMPLATE_FILE6}"
"-e ing -e as -e the -e not -e is ${TEMPLATE_FILE6}"
"-c -e . ${TEMPLATE_FILE1} '.'"
"-l for no_file.txt ${TEMPLATE_FILE2}"
"-f test_3_grep.txt ${TEMPLATE_FILE5}"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
        CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_grep $t > test_s21_grep.log
        leak=$(grep ERROR RESULT_VALGRIND.txt)
        (( COUNTER++ ))
        if [[ $leak == *"ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"* ]]
        then
          (( SUCCESS++ ))
        echo -e "$FAIL/$SUCCESS/$COUNTER success grep $t"
    else
      (( FAIL++ ))
        echo -e "$FAIL/$SUCCESS/$COUNTER fail grep $t"
#        echo "$leak"
    fi
    rm test_s21_grep.log
    rm RESULT_VALGRIND.txt
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n h o
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done


echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
