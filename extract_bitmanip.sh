#!/bin/bash

FILE=texsrc/bext.tex

# 2 ops
#echo "// register-register"
#grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep rs2.*rs1 | grep -v rs3 | sed -e 's/rs2/-----/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "def "$14"_key =\tM\""$2$4$6$8$10$12"\"" }'

# 7bit simm
#echo "// register-immediate (7bits)"
#grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/-------/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "def "$14"_key =\tM\""$2$4$6$8$10$12"\"" }'

# 6bit simm
#echo "// register-immediate (6bits)"
#grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/------/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "def "$14"_key =\tM\""$2$4$6$8$10$12"\"" }'

# 5bit simm
#echo "// register-immediate (5bits)"
#grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/-----/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "def "$14"_key =\tM\""$2$4$6$8$10$12"\"" }'




echo "// register-register"
grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep rs2.*rs1 | grep -v rs3 | sed -e 's/rs2/-----/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "I""\t"$14"\t"$14"\t"$2$4$6$8$10$12"\t"$14 }' | sed -e 's/\./dot/g'

echo "// register-immediate (7bits)"
grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/-------/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "I""\t"$14"\t"$14"\t"$2$4$6$8$10$12"\t"$14 }' | sed -e 's/\./dot/g'

echo "// register-immediate (6bits)"
grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/------/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "I""\t"$14"\t"$14"\t"$2$4$6$8$10$12"\t"$14 }' | sed -e 's/\./dot/g'

echo "// register-immediate (5bits)"
grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01][01][01] *|' | grep imm.*rs1 | sed -e 's/imm/-----/' -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "I""\t"$14"\t"$14"\t"$2$4$6$8$10$12"\t"$14 }' | sed -e 's/\./dot/g'

echo "// unary register"
grep '^|.*|  [A-Z][A-Z]' $FILE |grep -v '\*$' | grep '^|  [01][01][01][01][01][01][01] *|  [01][01][01][01][01]  |' | sed -e 's/rs1/-----/' -e 's/rd/-----/' | awk  '{ print "I""\t"$14"\t"$14"\t"$2$4$6$8$10$12"\t"$14 }' | sed -e 's/\./dot/g'

echo "// register-register-register"
grep '^|.*|  [A-Z][A-Z]' $FILE | grep rs3 | sed -e 's/rs3/-----/' -e 's/rs2/-----/' -e 's/rs1/-----/' -e 's/rd/-----/' -e 's/ //g' -e 's/|1|imm/|1|------/' -e 's/|10|imm/|10|-----/' | awk '-F|' '{ print "I""\t"$9"\t"$9"\t"$2$3$4$5$6$7$8"\t"$9 }' | sed -e 's/\./dot/g'


