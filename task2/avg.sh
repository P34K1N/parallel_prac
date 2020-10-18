#!/bin/bash
printf "${1} " >> ${2}
awk '{ total += $1; count++ } END  {print total / count}' ${3} >> ${2}
rm ${3}
