
%{
load dane/det.txt
load dane/rank.txt
load dane/rul.txt
load dane/tur.txt

vals = [rul rank det tur];

figure;
boxplot(vals, 'Labels', {'Ruletkowa', 'Rankingowa', 'Deterministyczna', 'Turniejowa'});
title('Znaleznione pola p�ytek dla 30 test�w, dla r�nych metod selekcji');
xlabel('Metoda selekcji');
ylabel('Znaleziome pola x 10^6 [mm]')
%}

load dane/tur1.txt
load dane/tur05.txt
load dane/tur01.txt

vals = [tur01 tur05 tur1];
figure;
boxplot(vals, 'Labels', {'0.01', '0.05', '0.1'});
title(["Znaleznione pola p�ytek dla 30 test�w, " "dla r�nych prawdopodobie�stw mutacji"]);
xlabel('Prawdopodobie�stwo mutacji');
ylabel('Znaleziome pola x 10^6 [mm]')