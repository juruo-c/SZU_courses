% main function
clear
close all

% % Yale
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\Yale_face10080\face10080\subject';
% suffix = '.bmp';
% ORL
address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\ORL56_46\ORL56_46\orl';
suffix = '.bmp';
%FERET
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\FERET_80\FERET_80\ff';
% suffix = '.tif';
% AR
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\AR_Gray_50by40\AR_Gray_50by40\AR';
% suffix = '.tif';

class_cnt = 3;      % the number of classes
train_cnt =7;       % the number of training samples of each class
eachclass_cnt = 10;  % the number of samples of each class
LDA_k = 20;          % data dimension after projection by LDA
PCA_k = 140;         % data dimension after projection by PCA
K = 4;               % K nearest neighbors

%% Two Classes
% X = [1, 1.1, 1.2, 1.34, 1.4, 1.57, 1.35, 1.42, 1.43, 1.46, 1.6, 1.69;
%      2, 2.4, 3, 2.5, 3.3, 3.1, 1, 1.5, 0.97, 1.4, 1.46, 1.43];
% Label = [1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2];
% c = [0, 0, 1;0, 0, 1;0, 0, 1;0, 0, 1;0, 0, 1;0, 0, 1;1 0 1;1 0 1;1 0 1;1 0 1;1 0 1;1 0 1;];
% scatter(X(1, :), X(2, :), 25, c, "filled");
% xlabel('x');
% ylabel('y');
% w = Two_Class_LDA(X, Label);
% X = w' * X;
% figure
% scatter(X, Label, 25, c, "filled");
% xlabel('w');
% ylabel('Class');

%% Multi Classes (just use LDA)
% [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% [W, D] = Multi_Class_LDA(X_train, Label_train, class_cnt);
% for k = 1 : 3 : 46
%     k
%     rate = LDArecognize(W, D, X_train, X_test, Label_train, Label_test, K, k)
% end

%% Multi Classes (just use PCA)
% [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% [V, Mean] = PCA(X_train);
% for k = 1 : 3 : 46
%     k
%     rate = PCArecognize(V, X_train, X_test, Label_train, Label_test, Mean, K, k)
% end

%% Multi Classes (use PCA and LDA together)
% [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% [V, Mean] = PCA(X_train);
% PCA_k = 100;
% for LDA_k = 1 : 3 : min(PCA_k - 1, 46)
%     res = [PCA_k, LDA_k];
%     rate = LDAwithPCA(V, PCA_k, LDA_k, X_train, X_test, Label_train, Label_test, K, Mean, class_cnt);
%     res = [res, rate]
% end

%% visualization
[X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% eigenfaceandfisherface(X_train, Label_train, class_cnt, row, col);
TwoandThreedimension(X_train, Label_train, X_test, Label_test, class_cnt, row, col);