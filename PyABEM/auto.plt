set style line 1 lw 2
set terminal png size 2000,1000
set key below right
set key textcolor lt 0
set xl textcolor lt 0
set yl textcolor lt 0

set title "HasVirus";set xl "Term";set yl "Agent";
set output "HasVirus.png";plot "output.txt" using 1:2 w l lw 1 title "has_virus_0";
set output "HasVirus.png";replot "output.txt" using 1:3 w l lw 1 title "has_virus_1";

set title "TagLenAverage";set xl "Term";set yl "Len";
set output "TagLenAverage.png";plot "ave.txt" using 1:2 w l lw 1 title "Len";

set title "Populatioin";set xl "Term";set yl "Len";
set output "Population.png";plot "ave.txt" using 1:3 w l lw 1 title "Population";

set output
