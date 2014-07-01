labels = data(:,1);
features = data(:,2:end);
names = colheaders;
cols = [6,11,16,21,26,31,36,37,38,39,40,41,42,43,44,45,50,55,60];
cols = cols + 1; % Ignore first value

pause on
% cols = size(features,2);
for i = 1:length(cols)
    for j = i:length(cols)
        fprintf('(%s,%s)\n',names{1,cols(i)},names{1,cols(j)});
%         gplotmatrix(features(:,[1,2,3]),features(:,[1,2,3]),labels,'rb','.o');
        scatter(features(:,i),features(:,j),[],labels,'.o');
        pause
    end
end

