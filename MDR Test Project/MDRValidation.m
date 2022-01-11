clear all;
close all;

load([pwd,'\Memory.mat']);
temp = [LTM.performance];
L_D = [temp.L_D]';
M_empty = [temp.M_empty]';
MTOW = [temp.MTOW]';
Stall = [temp.Stall]';

pareto = readmatrix('pareto1.csv')';
pareto = pareto + ones(size(pareto));

pareto_L_D = zeros(size(pareto,1),1);
pareto_MTOW = zeros(size(pareto,1),1);

for i=1:size(pareto,1)
    pareto_L_D(i,1) = L_D(pareto(i),1);
    pareto_MTOW(i,1) = MTOW(pareto(i),1);
end

[pareto_L_D,LDsort]=sort(pareto_L_D);
pareto_MTOW=pareto_MTOW(LDsort);

figure(1)
% set figure position and size:
set(gcf,'position',[160 200 500 400])

% keep position and size when printing:
set(gcf,'PaperPositionMode','auto')

hold on
scatter(L_D,MTOW,'x');
plot(pareto_L_D,pareto_MTOW,'--r');
scatter(pareto_L_D,pareto_MTOW,200,'.');
hold off

xlim([-18 -6]);
ylim([5e3 30e3]);

% set fonts and frame:
set(gca,'Fontn','Times','FontSize',16,'linewidth',1)
