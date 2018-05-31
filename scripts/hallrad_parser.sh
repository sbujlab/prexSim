!#/bin/bash
user_list=${1}
while read p; do
  #arr=(${p//${2}/ })
  result1=${p//${2}/}
  result2=${result1//${3}/}
  echo $result2
done <$user_list
