BEGIN {
  printf "\caption{No of rotations} \n"
  printf "\\begin{tabular}{|c|c|c|} \n"
  printf "\\hline \n"
  printf "\\hline \n"
  printf "no of elements  &  no of rotation in avl & no of rotation in red-black \\\\ \n"
  printf "\\hline \n"
}

{ printf $1" & "
  printf $2" & "
  printf $3" \\\\ "
  printf "\n"
}

END {
  printf "\\hline \n"
  printf "\end{tabular}"
  printf "\n"
}
