set style line 1 lw 2
set terminal png size 2000,500
set key below right
set key textcolor lt 0
set xl textcolor lt 0
set yl textcolor lt 0

set title "HasVirus";set xl "Term";set yl "Agent";
set output "HasVirus.png";plot "output.txt" using 1:2 w l lw 1 title "has_virus_0";
set output "HasVirus.png";replot "output.txt" using 1:3 w l lw 1 title "has_virus_1";

set output