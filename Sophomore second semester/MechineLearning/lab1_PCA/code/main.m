% main funciton
clear
close all

address = 'C:\Users\19116\Desktop\Grade Two second semester\mechine learning\report\PCA\lab_1\database\FERET_80\FERET_80\ff';
suffix = '.tif';
class_cnt = 100;
train_cnt = 7;
eachclass_cnt = 7;
k_dimension = 3;
%% read data
[X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
%% PCA
[P, Mean] = PCA(X_train, k_dimension);
% for k = 10 : 10 : 160
%     k
%     %% recognition
%     rate = recognize(P, X_train, X_test, Label_train, Label_test, Mean)
% end
%% rebuild test face
% rebuild(P, X_train(:, [1, 11, 21, 31, 41, 51, 61, 71, 81, 91]), row, col, Mean);

%% visualization
% twovisualization(P, X_train, Mean);
threevisualization(P, X_train, Mean);