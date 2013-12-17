set terminal png size 1000,200
set title "HasVirus"
set xl "Term"
set yl "Agent"
set output "HasVirus.png";plot "A_hasVirus.txt" with l  title "has_virus_0" 
set output "HasVirus.png";replot "A_hasVirus.txt" using 1:3  with l  title "has_virus_1" 
set output "HasVirus.png";replot "A_hasVirus.txt" using 1:4 with l  title "has_all_virus" 
set title "HasVirus"
set xl "Term"
set yl "Agent"
set output "HasVirus_mini.png";plot [0:200] "A_hasVirus.txt" with l  title "has_virus_0" 
set output "HasVirus_mini.png";replot "A_hasVirus.txt" using 1:3  with l  title "has_virus_1" 
set output "HasVirus_mini.png";replot "A_hasVirus.txt" using 1:4  with l  title "has_all_virus" 
set title "HasVirus"
set xl "Term"
set yl "Agent"
set title "HasVirus ( 6.03125 [term cycle] / 43 [amplitude])"
set output "HasVirus_last.png";plot [99800:100000] "A_hasVirus.txt" with l  title "has_virus_0" 
set output "HasVirus_last.png";replot "A_hasVirus.txt" using 1:3  with l  title "has_virus_1" 
set output "HasVirus_last.png";replot "A_hasVirus.txt" using 1:4 with l  title "has_all_virus" 
set output "HasVirus_last.png";replot "PEAK_A_hasVirus.txt" w p ps 1  title "peak" 
set title "hasImmunity"
set xl "Term"
set yl "Agent"
set output "HasImmunity.png";plot "A_hasImmunity.txt" with l  title "has_immunity_0" 
set output "HasImmunity.png";replot "A_hasImmunity.txt" using 1:3  with l  title "has_immunity_1" 
set output "HasImmunity.png";replot "A_hasImmunity.txt" using 1:4  with l  title "has_all_immunity" 
set output "HasImmunity_mini.png";plot [0:200] "A_hasImmunity.txt" with l  title "has_immunity_0" 
set output "HasImmunity_mini.png";replot "A_hasImmunity.txt" using 1:3  with l  title "has_immunity_1" 
set output "HasImmunity_mini.png";replot "A_hasImmunity.txt" using 1:4  with l  title "has_all_immunity" 
set title "hasImmunity"
set xl "Term"
set yl "Agent"
set title "HasImmunity ( 6.0303 [term cycle] / 31 [amplitude])"
set output "HasImmunity_last.png";plot [99800:100000] "A_hasImmunity.txt" with l  title "has_immunity_0" 
set output "HasImmunity_last.png";replot "A_hasImmunity.txt" using 1:3  with l  title "has_immunity_1" 
set output "HasImmunity_last.png";replot "A_hasImmunity.txt" using 1:4  with l  title "has_all_immunity" 
set output "HasImmunity_last.png";replot "PEAK_A_hasImmunity.txt" w p ps 1  title "peak" 
set title "SIR"
set xl "Term"
set yl "Agent"
set output "SIR.png";plot "A_hasVirus.txt" using 1:4 with l  title "I" 
set output "SIR.png";replot "A_hasImmunity.txt" using 1:4 with l  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set output "SIR_0.png";plot "A_hasVirus.txt" with l  title "I_0"
set output "SIR_0.png";replot "A_hasImmunity.txt" with l  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_RATIO.png";plot "A_hasVirus.txt" using 1:5 with l  title "I/POPULATION"
set output "SIR_RATIO.png"
set output "SIR_RATIO.png";replot "A_hasImmunity.txt" using 1:5 with l  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_0_RATIO.png";plot "A_hasVirus.txt" using 1:6 with l  title "I_0/POPULATION"
set output "SIR_0_RATIO.png";replot "A_hasImmunity.txt" using 1:6 with l  title "R_0/POPULATION"
set autoscale y
set output "SIR_mini.png"
set title "SIR"
set xl "Term"
set yl "Agent"
set output "SIR_mini.png";plot [0:200] "A_hasVirus.txt" using 1:4 with l  title "I"
set output "SIR_mini.png";replot "A_hasImmunity.txt" using 1:4 with l  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set output "SIR_0_mini.png";plot [0:200] "A_hasVirus.txt" with l  title "I_0" 
set output "SIR_0_mini.png";replot "A_hasImmunity.txt" with l  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_RATIO_mini.png";plot [0:200] "A_hasVirus.txt" using 1:5 with l  title "I/POPULATION"
set output "SIR_RATIO_mini.png";replot "A_hasImmunity.txt" using 1:5 with l  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_0_RATIO_mini.png";plot [0:200] "A_hasVirus.txt" using 1:6 with l  title "I_0/POPULATION"
set output "SIR_0_RATIO_mini.png";replot "A_hasImmunity.txt" using 1:6 with l  title "R_0/POPULATION"
set autoscale y
set output "SIR_last.png"
set title "SIR"
set xl "Term"
set yl "Agent"
set output "SIR_last.png";plot [99800:100000] "A_hasVirus.txt" using 1:4 with l  title "I"
set output "SIR_last.png";replot "A_hasImmunity.txt" using 1:4 with l  title "R"
set title "SIR_0"
set xl "Term"
set yl "Agent"
set output "SIR_0_last.png";plot [99800:100000] "A_hasVirus.txt" with l  title "I_0" 
set output "SIR_0_last.png";replot "A_hasImmunity.txt" with l  title "R_0" 
set title "SIR_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_RATIO_last.png";plot [99800:100000] "A_hasVirus.txt" using 1:5 with l  title "I/POPULATION"
set output "SIR_RATIO_last.png";replot "A_hasImmunity.txt" using 1:5 with l  title "R/POPULATION"
set autoscale y
set title "SIR_0_RATIO"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "SIR_0_RATIO_last.png";plot [99800:100000] "A_hasVirus.txt" using 1:6 with l  title "I_0/POPULATION"
set output "SIR_0_RATIO_last.png";replot "A_hasImmunity.txt" using 1:6 with l  title "R_0/POPULATION"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set output "Contact.png";plot "A_infectionContact.txt" with l  title "contact"
set output "Contact.png";replot "A_infectionContact.txt" using 1:3 with l  title "infect_contact_1"
set output "Contact.png";replot "A_infectionContact.txt" using 1:4 with l  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "ContactRatio.png";plot "A_infectionContact.txt" using 1:5 with l  title "ratio"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set output "Contact_mini.png";plot [0:200] "A_infectionContact.txt" with l  title "contact"
set output "Contact_mini.png";replot "A_infectionContact.txt" using 1:3 with l  title "infect_contact_1"
set output "Contact_mini.png";replot "A_infectionContact.txt" using 1:4 with l  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "ContactRatio_mini.png";plot [0:200] "A_infectionContact.txt" using 1:5 with l  title "ratio"
set autoscale y
set title "InfectionContact"
set xl "Term"
set yl "Agent"
set output "Contact_last.png";plot [99800:100000] "A_infectionContact.txt" with l  title "contact"
set output "Contact_last.png";replot "A_infectionContact.txt" using 1:3 with l  title "infect_contact_1"
set output "Contact_last.png";replot "A_infectionContact.txt" using 1:4 with l  title "infect_contact_2"
set title "InfectionContactRatio"
set xl "Term"
set yl "Ratio"
set yrange[0:1]
set output "ContactRatio_last.png";plot [99800:100000] "A_infectionContact.txt" using 1:5 with l  title "ratio"
set autoscale y
set output
