while read LINE
  do ../cmake-build-debug/lab7 $LINE
done < test.txt