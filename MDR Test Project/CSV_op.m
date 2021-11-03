clear all;
close all;

load([pwd,'\Memory.mat']);
temp = [LTM.performance];
write = [[temp.L_D]' [temp.M_empty]' [temp.MTOW]' [temp.Stall]'];
write(isnan(write))=100000000;
csvwrite('MATLAB_OP.csv', write);

