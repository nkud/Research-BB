set style line 1 lw 2
set terminal png size 1200,200
set title "HasVirus"
set xl "Term"
set yl "Agent"
set key box below left
set output "HasVirus.png";plot "A_hasVirus.txt" with l lw 2  title "has_virus_0" 
set output "HasVirus.png";replot "A_hasVirus.txt" using 1:3  with l lw 2  title "has_virus_1" 
set output "HasVirus.png";replot "A_hasVirus.txt" using 1:4  with l lw 2  title "has_all_virus" 
set title "HasVirus"
set xl "Term"
set yl "Agent"
set key box below left
set output "HasVirus_mini.png";plot [0:200] "A_hasVirus.txt" with l lw 2  title "has_virus_0" 
set output "HasVirus_mini.png";replot "A_hasVirus.txt" using 1:3  with l lw 2  title "has_virus_1" 
set output "HasVirus_mini.png";replot "A_hasVirus.txt" using 1:4  with l lw 2  title "has_all_virus" 
set title "HasVirus"
set xl "Term"
set yl "Agent"
set key box below left
set title "HasVirus ( 5.55556 [term cycle] / -100 [amplitude])"
set output "HasVirus_last.png";plot [0:200] "A_hasVirus.txt" with l lw 2  title "has_virus_0" 
set output "HasVirus_last.png";replot "A_hasVirus.txt" using 1:3  with l lw 2  title "has_virus_1" 
set output "HasVirus_last.png";replot "A_hasVirus.txt" using 1:4 with l lw 2  title "has_all_virus" 
set output "HasVirus_last.png";replot "PEAK_A_hasVirus.txt" with p ps 2 pt 4  title "peak" 
set title "hasImmunity"
set xl "Term"
set yl "Agent"
set key box below left
set output "HasImmunity.png";plot "A_hasImmunity.txt" with l lw 2  title "has_immunity_0" 
set output "HasImmunity.png";replot "A_hasImmunity.txt" using 1:3  with l lw 2  title "has_immunity_1" 
set output "HasImmunity.png";replot "A_hasImmunity.txt" using 1:4  with l lw 2  title "has_all_immunity" 
set output "HasImmunity_mini.png";plot [0:200] "A_hasImmunity.txt" with l lw 2  title "has_immunity_0" 
set output "HasImmunity_mini.png";replot "A_hasImmunity.txt" using 1:3  with l lw 2  title "has_immunity_1" 
set output "HasImmunity_mini.png";replot "A_hasImmunity.txt" using 1:4  with l lw 2  title "has_all_immunity" 
set title "hasImmunity"
set xl "Term"
set yl "Agent"
set key box below left
set title "HasImmunity ( 704.07 [term cycle] / -100 [amplitude])"
set output "HasImmunity_last.png";plot [0:200] "A_hasImmunity.txt" with l lw 2  title "has_immunity_0" 
set output "HasImmunity_last.png";replot "A_hasImmunity.txt" using 1:3  with l lw 2  title "has_immunity_1" 
set output "HasImmunity_last.png";replot "A_hasImmunity.txt" using 1:4  with l lw 2  title "has_all_immunity" 
set output "HasImmunity_last.png";replot "PEAK_A_hasImmunity.txt" with p ps 2 pt 4  title "peak" 
set title "SIR"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR.png";plot "A_hasVirus.txt" using 1:4 with l lw 2  title "I" 
set output "SIR.png";replot "A_hasImmunity.txt" using 1:4 with l lw 2  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR_0.png";plot "A_hasVirus.txt" with l lw 2  title "I_0"
set output "SIR_0.png";replot "A_hasImmunity.txt" with l lw 2  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1];
set output "SIR_RATIO.png";plot "A_hasVirus.txt" using 1:5 with l lw 2  title "I/POPULATION"
set output "SIR_RATIO.png"
set output "SIR_RATIO.png";replot "A_hasImmunity.txt" using 1:5 with l lw 2  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1];
set output "SIR_0_RATIO.png";plot "A_hasVirus.txt" using 1:6 with l lw 2  title "I_0/POPULATION"
set output "SIR_0_RATIO.png";replot "A_hasImmunity.txt" using 1:6 with l lw 2  title "R_0/POPULATION"
set autoscale y
set output "SIR_mini.png"
set title "SIR"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR_mini.png";plot [0:200] "A_hasVirus.txt" using 1:4 with l lw 2  title "I"
set output "SIR_mini.png";replot "A_hasImmunity.txt" using 1:4 with l lw 2  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR_0_mini.png";plot [0:200] "A_hasVirus.txt" with l lw 2  title "I_0" 
set output "SIR_0_mini.png";replot "A_hasImmunity.txt" with l lw 2  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1];
set output "SIR_RATIO_mini.png";plot [0:200] "A_hasVirus.txt" using 1:5 with l lw 2  title "I/POPULATION"
set output "SIR_RATIO_mini.png";replot "A_hasImmunity.txt" using 1:5 with l lw 2  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1];
set output "SIR_0_RATIO_mini.png";plot [0:200] "A_hasVirus.txt" using 1:6 with l lw 2  title "I_0/POPULATION"
set output "SIR_0_RATIO_mini.png";replot "A_hasImmunity.txt" using 1:6 with l lw 2  title "R_0/POPULATION"
set autoscale y
set output "SIR_last.png"
set title "SIR"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR_last.png";plot [0:200] "A_hasVirus.txt" using 1:4 with l lw 2  title "I"
set output "SIR_last.png";replot "A_hasImmunity.txt" using 1:4 with l lw 2  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set key box below left
set output "SIR_0_last.png";plot [0:200] "A_hasVirus.txt" with l lw 2  title "I_0" 
set output "SIR_0_last.png";replot "A_hasImmunity.txt" with l lw 2  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1]
set output "SIR_RATIO_last.png";plot [0:200] "A_hasVirus.txt" using 1:5 with l lw 2  title "I/POPULATION"
set output "SIR_RATIO_last.png";replot "A_hasImmunity.txt" using 1:5 with l lw 2  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1]
set output "SIR_0_RATIO_last.png";plot [0:200] "A_hasVirus.txt" using 1:6 with l lw 2  title "I_0/POPULATION"
set output "SIR_0_RATIO_last.png";replot "A_hasImmunity.txt" using 1:6 with l lw 2  title "R_0/POPULATION"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set key box below left
set output "Contact.png";plot "A_infectionContact.txt" with l lw 2  title "contact"
set output "Contact.png";replot "A_infectionContact.txt" using 1:3 with l lw 2  title "infect_contact_1"
set output "Contact.png";replot "A_infectionContact.txt" using 1:4 with l lw 2  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1]
set output "ContactRatio.png";plot "A_infectionContact.txt" using 1:5 with l lw 2  title "ratio"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set key box below left
set output "Contact_mini.png";plot [0:200] "A_infectionContact.txt" with l lw 2  title "contact"
set output "Contact_mini.png";replot "A_infectionContact.txt" using 1:3 with l lw 2  title "infect_contact_1"
set output "Contact_mini.png";replot "A_infectionContact.txt" using 1:4 with l lw 2  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1]
set output "ContactRatio_mini.png";plot [0:200] "A_infectionContact.txt" using 1:5 with l lw 2  title "ratio"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set key box below left
set output "Contact_last.png";plot [0:200] "A_infectionContact.txt" with l lw 2  title "contact"
set output "Contact_last.png";replot "A_infectionContact.txt" using 1:3 with l lw 2  title "infect_contact_1"
set output "Contact_last.png";replot "A_infectionContact.txt" using 1:4 with l lw 2  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set key box below left
set yrange[0:1]
set output "ContactRatio_last.png";plot [0:200] "A_infectionContact.txt" using 1:5 with l lw 2  title "ratio"
set autoscale y
set output
