set terminal png
set output "Population.png"
set title "Population" font "monospace, 24"
plot "A_population.txt" w l title "population"
set output "HasVirus.png"
set title "ウイルス保持者" font "monospace, 24"
plot "A_hasVirus.txt" w l title "ウイルス0保持"
set output "HasVirus.png"
replot "A_hasVirus.txt" using 1:3 w l title "全ウイルス保持"
set output "HasImmunity.png"
set title "hasImmunity" font "monospace, 24"
plot "A_hasImmunity.txt" w l title "has_immunity_0"
set output "HasImmunity.png"
replot "A_hasImmunity.txt" using 1:3 w l title "has_all_immunity"
set output "SIR.png"
set title "SIR" font "monospace, 24"
plot "A_hasImmunity.txt" using 1:2 w l title "R"
set output "SIR.png"
replot "A_hasVirus.txt" using 1:2 w l title "I"
set output "SIR_0.png"
set title "SIR_0" font "monospace, 24"
plot "A_hasImmunity.txt" w l title "R"
set output "SIR_0.png"
replot "A_hasVirus.txt" w l title "I"
set output "SIR_RATIO.png"
set title "SIR_RATIO" font "monospace, 24"
plot "A_hasImmunity.txt" using 1:4 w l title "R/POPULATION"
set output "SIR_RATIO.png"
replot "A_hasVirus.txt" using 1:4 w l title "I/POPULATION"
set output "SIR_0_RATIO.png"
set title "SIR_0_RATIO" font "monospace, 24"
plot "A_hasImmunity.txt" using 1:5 w l title "R/POPULATION"
set output "SIR_0_RATIO.png"
replot "A_hasVirus.txt" using 1:5 w l title "I/POPULATION"
set output "Contact.png"
set title "InfectionContact" font "monospace, 24"
plot "A_infectionContact.txt" w l title "contact"
set output "Contact.png"
replot "A_infectionContact.txt" using 1:3 w l title "infect_contact_1"
set output "ContactRatio.png"
set title "InfectionContactRatio" font "monospace, 24"
plot "A_infectionContact.txt" using 1:4 w l title "ratio"
