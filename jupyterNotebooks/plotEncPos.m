clear all;
close all;
clc;
pos500 = xlsread('Enc500RPM_2022-03-29_H14-M52-S01.csv', 'A2:B5085');
pos1k = xlsread('Enc1kRPM_2022-03-29_H14-M51-S17.csv', 'A2:B5085');
pos1500 = xlsread('Enc15kRPM_2022-03-29_H14-M55-S59.csv', 'A2:B5085');
pos3k = xlsread('Enc3kRPM_2022-03-29_H14-M52-S49.csv', 'A2:B5085');
pos5k = xlsread('Enc5kRPM_2022-03-29_H14-M54-S21.csv', 'A2:B5085'); 
pos6k = xlsread('Enc6kRPM_2022-03-29_H14-M54-S51.csv', 'A2:B5085');


figure()
plot(pos500(:,1).*1000, pos500(:,2)*360/(2*pi));
hold on
plot(pos1k(:,1).*1000, pos1k(:,2)*360/(2*pi));
xlim([0,30])