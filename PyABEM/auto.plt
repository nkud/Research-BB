set style line 1 lw 2
set terminal png size 600, 300
set key below right
set key textcolor lt 0
set xl textcolor lt 0
set yl textcolor lt 0
set title "AverageTagLen";set xl "Term";set yl "AveTagLen";
set output "AverageTagLen.png";
plot "ave.txt" using 1:2 w l title "Len"
set output
