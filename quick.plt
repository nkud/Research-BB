set title "SIR" font "helvetica, 24"
plot "A_hasImmunity.txt" using 1:2 w l title "R"
replot "A_hasVirus.txt" using 1:2 w l title "I"
set output
pause -1
set title "SIR_0" font "helvetica, 24"
plot "A_hasImmunity.txt" w l title "R"
replot "A_hasVirus.txt" w l title "I"
set output
pause -1
set title "SIR_RATIO" font "helvetica, 24"
plot "A_hasImmunity.txt" using 1:4 w l title "R/POPULATION"
replot "A_hasVirus.txt" using 1:4 w l title "I/POPULATION"
set output
pause -1
set title "SIR_0_RATIO" font "helvetica, 24"
plot "A_hasImmunity.txt" using 1:5 w l title "R/POPULATION"
replot "A_hasVirus.txt" using 1:5 w l title "I/POPULATION"
set output
pause -1
