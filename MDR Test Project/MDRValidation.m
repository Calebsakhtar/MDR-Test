clear all;
close all;

% Set Style
cal_orange = [237 125 49]/255;
cal_blue = [50 142 216]/255;
cal_grey_light = [0.95 0.95 0.95];
cal_grey_dark = [0.35 0.35 0.35];

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
scatter(L_D,MTOW,50,'x','LineWidth',1.2,'DisplayName','Candidate Designs');
plot(pareto_L_D,pareto_MTOW,'Marker','.','MarkerSize',20,'color',cal_orange,...
    'LineWidth',1.5,'DisplayName','Pareto Front');
hold off

xlim([-18 -6]);
xticks(linspace(-18,-6,3));
ylim([4e3 32e3]);
yticks(linspace(4e3, 32e3, 3));

xlabel('$-L/D$','interpreter','latex');
ylabel('MTOW');

leg = legend('location','north','orientation','horizontal');

% set fonts and frame:
set(gca,'Fontn','Times','FontSize',18,'linewidth',1)
  

% For a vectorial figure (for latex):
print -deps2c MDR_Validation.eps

% For an image figure at resolution 300 pixels/inch (for word):
print -dpng -r300 MDR_Validation.png

%% Second Pareto Front

pareto2 = readmatrix('pareto2.csv')';
pareto2 = pareto2 + ones(size(pareto2));

pareto_M_empty = zeros(size(pareto2,1),1);
pareto_Stall = zeros(size(pareto2,1),1);

for i=1:size(pareto2,1)
    pareto_M_empty(i,1) = M_empty(pareto2(i),1);
    pareto_Stall(i,1) = Stall(pareto2(i),1);
end

[pareto_M_empty,LDsort]=sort(pareto_M_empty);
pareto_Stall=pareto_Stall(LDsort);

figure(2)
% set figure position and size:
set(gcf,'position',[160 200 500 400])

% keep position and size when printing:
set(gcf,'PaperPositionMode','auto')

hold on
scatter(M_empty,Stall,50,'x','LineWidth',1.2);
plot(pareto_M_empty,pareto_Stall,'Marker','*','color',cal_orange,...
    'LineStyle','--','LineWidth',1.5);
hold off

xlim([0.3e4 2.6e4]);
xticks(linspace(0.5e4,2.5e4,3));
ylim([0 250]);
yticks(linspace(0, 250, 3));

xlabel('Empty Weight','interpreter','latex');
ylabel('Stall Speed');

% set fonts and frame:
set(gca,'Fontn','Times','FontSize',16,'linewidth',1)