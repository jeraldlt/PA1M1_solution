#!/bin/bash

TESTER=$1
SUBMISSION=$2

INST_CORRECT=0
TOTAL_CORRECT=0

function ws() {
  if [ -z "$1" ]; then
    rnd=$(( RANDOM % 4 ))
  else
    rnd=$(( RANDOM % (4 + $1) ))
  fi

  case "$rnd" in
    "0")
      echo -n " "
      ;;
    "1")
      echo -n "\t "
      ;;
    "2")
      echo -n "   "
      ;;
    "3")
      echo -n " \t  "
      ;;
  esac
}
    
function comment() {
  if [[ $(( RANDOM % 2 )) -eq 0 ]]; then
    echo -n "# this is a comment"
  fi
}

function imm() {

  rnd=$RANDOM
  ty=$(( RANDOM % 2 ))
  sign=$(( RANDOM % 2 ))

  # If imm is in decimal
  if [[ $ty -eq 0 ]]; then
    # if imm is positive
    if [[ $sign -eq 0 ]]; then
      echo -n $rnd
    # if imm is negative
    else
      echo -n "-$rnd"
    fi
  # if imm is in hex
  else
    # if imm is positive
    if [[ $sign -eq 0 ]]; then
      printf "0x%x" $(( rnd & 0x7FFF ))
    # if imm is negative
    else
      printf "0x%x" $(( rnd | 0x8000 ))
    fi
  fi
}

function reg() {
  rnd=$(( RANDOM % 32 ))
  ty=$(( RANDOM % 2 ))

  if [[ $ty -eq 0 ]]; then
    case "$rnd" in
      "0")
        echo -n "\$zero"
        ;;
      "1")
        echo -n "\$at"
        ;;
      "2")
        echo -n "\$v0"
        ;;
      "3")
        echo -n "\$v1"
        ;;
      "4")
        echo -n "\$a0"
        ;;
      "5")
        echo -n "\$a1"
        ;;
      "6")
        echo -n "\$a2"
        ;;
      "7")
        echo -n "\$a3"
        ;;
      "8")
        echo -n "\$t0"
        ;;
      "9")
        echo -n "\$t1"
        ;;
      "10")
        echo -n "\$t2"
        ;;
      "11")
        echo -n "\$t3"
        ;;
      "12")
        echo -n "\$t4"
        ;;
      "13")
        echo -n "\$t5"
        ;;
      "14")
        echo -n "\$t6"
        ;;
      "15")
        echo -n "\$t7"
        ;;
      "16")
        echo -n "\$s0"
        ;;
      "17")
        echo -n "\$s1"
        ;;
      "18")
        echo -n "\$s2"
        ;;
      "19")
        echo -n "\$s3"
        ;;
      "20")
        echo -n "\$s4"
        ;;
      "21")
        echo -n "\$s5"
        ;;
      "22")
        echo -n "\$s6"
        ;;
      "23")
        echo -n "\$s7"
        ;;
      "24")
        echo -n "\$t8"
        ;;
      "25")
        echo -n "\$t9"
        ;;
      "26")
        echo -n "\$k0"
        ;;
      "27")
        echo -n "\$k1"
        ;;
      "28")
        echo -n "\$gp"
        ;;
      "29")
        echo -n "\$sp"
        ;;
      "30")
        echo -n "\$fp"
        ;;
      "31")
        echo -n "\$ra"
        ;;
      esac
    else
      echo -n "\$$rnd"
  fi

}



function rtype() {
  echo -en "$(ws 4)$1$(ws)$(reg)$(ws 10),$(ws 1)$(reg)$(ws 10),$(reg)$(ws 4)$(comment)" 
}

function itype1() {
  echo -en "$(ws)$1$(ws)$(reg)$(ws),$(ws)$(reg)$(ws),$(imm)$(ws)$(comment)" 
}

function itype2() {
  echo -en "$(ws)$1$(ws)$(reg)$(ws),$(imm)$(ws)$(comment)" 
}

function execute_test() {
  case $1 in
    "add")
      line=$(rtype add)
      ;;
    "addiu")
      line=$(itype addiu)
      ;;
    "and")
      line=$(rtype and)
      ;;
    "andi")
      line=$(itype1 andi)
      ;;
    "beq")
      line=$(itype1 beq)
      ;;
    "bne")
      line=$(itype1 bne)
      ;;
    "j")
      line=$(echo -en "$(ws)j$(ws)0x0040$(printf "%x\n" $RANDOM)$(ws)$(comment)")
      ;;
    "lui")
      line=$(itype2 lui)
      ;;
    "or")
      line=$(rtype or)
      ;;
    "ori")
      line=$(itype1 ori)
      ;;
    "slt")
      line=$(rtype slt)
      ;;
    "sub")
      line=$(rtype sub)
      ;;
    "syscall")
      line=$(echo -en "$(ws)syscall$(ws)$(comment)")
  esac

  result=$($SUBMISSION "$line")
  correct_result=$($TESTER "$line")

  echo Evaluating line \"$line\"
  echo ".. Evaluated output: $result"
  echo ".. Expected output:  $correct_result"
  if [ $result = $correct_result ]; then
    ((INST_CORRECT++))
    ((TOTAL_CORRECT++))
    echo ".. Output is correct (1/1)"
    echo
  else
    echo ".. Output is incorrect (0/1)"
    echo
  fi
}

instructions=("add" "andiu" "and" "andi" "beq" "bne"
"j" "lui" "or" "ori" "slt" "sub" "syscall")


for inst in "${instructions[@]}"
do
  INST_CORRECT=0
  
  echo "**********"
  echo "* Testing instruction $inst"
  echo "**********"
  echo
  
  for ((i=0; i<5; i++))
  do
    execute_test $inst
  done

  echo
  echo "Instruction score: $INST_CORRECT / 5"
  echo
done

echo
echo "Total score: $TOTAL_CORRECT / 75"

exit $TOTAL_CORRECT
