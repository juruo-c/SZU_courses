%% Initialization
clear ; close all; clc
% %% =============== Part 1: Loading and Visualizing Data ================
% load('data1.mat');
% % Plot training data
% plotData(X, y);
% fprintf('Part 1 over! Press enter to continue Part 2.\n');
% pause;
% 
% %% =============== Part 2: train hard margin SVM model and plot the boundary ================
% model = hard_margin_SVM(X, y);
% visualizeBoundaryLinear(X, y, model);
% fprintf('Part 2 over! Press enter to continue Part 3.\n');
% pause;
% 
% %% =============== Part 3: train soft margin SVM model and plot the boundary(leave one out) ================
% C = SelectParameterForSoftSVM(X, y);
% model = soft_margin_SVM(X, y, C);
% visualizeBoundaryLinear(X, y, model);
% fprintf('Part 3 over! Press enter to continue Part 4.\n');
% pause;

%% =============== Part 4: Loading and Visualizing Data ================
% load('data2.mat');
% plotData(X, y);
% fprintf('Part 4 over! Press enter to continue Part 5.\n');
% pause;

%% =============== Part 5: train hard margin kernel SVM model and plot the boundary ================
% sigma = 0.03;
% model = hard_margin_kernel_SVM(X, y, @(x1, x2)gaussianKernel(x1, x2, sigma));
% visualizeBoundary(X, y, model);
% fprintf('Part 5 over! Press enter to continue Part 6.\n');
% pause;

%% =============== Part 6: train soft margin kernel SVM model and plot the boundary ================
% C = 0.03;
% sigma = 0.03;
% model = soft_margin_kernel_SVM(X, y, C, @(x1, x2)gaussianKernel(x1, x2, sigma));
% visualizeBoundary(X, y, model);
% fprintf('Part 6 over! Press enter to continue Part 7.\n');
% pause;

%% =============== Part 7: PCA and LDA ================
% orl
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\ORL56_46\orl';
% suffix = '.bmp';
% Yale
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\face10080\subject';
% suffix = '.bmp';
% FERET
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\FERET_80\ff';
% suffix = '.tif';
% AR
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\AR_Gray_50by40\AR';
% suffix = '.tif';
% read data
class_cnt = 40;
train_cnt = 7;
eachclass_cnt = 10;
knn = 3;
[X_train, X_test, Label_train, Label_test, row, col] = Readdata(address, suffix, class_cnt, train_cnt, eachclass_cnt);

% % PCA
% right = [];
% for PCA_component = 10 : 10 : 100
%     model = PCA(X_train, PCA_component);
%     traini = model.W' * (X_train - repmat(model.miu, 1, size(X_train, 2)));
%     testi = model.W' * (X_test - repmat(model.miu, 1, size(X_test, 2)));
%     predict = KNN(traini, testi, Label_train, knn);
%     right = [right mean(double(predict == Label_test))];
% end
% right
% LDA
% right = [];
% for LDA_component = 1 : 4 : 40
%     model = LDA(X_train, Label_train, LDA_component);
%     traini = model.W' * X_train;
%     testi = model.W' * X_test;
%     predict = KNN(traini, testi, Label_train, knn);
%     right = [right mean(double(predict == Label_test))];
% end
% right
% fprintf('Part 7 over! Press enter to continue Part 8.\n');
% pause;

%% =============== Part 8: PCA + SVM ================
% orl
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\ORL56_46\orl';
% suffix = '.bmp';
% Yale
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\face10080\subject';
% suffix = '.bmp';
% FERET
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\FERET_80\ff';
% suffix = '.tif';
% AR
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\AR_Gray_50by40\AR';
% suffix = '.tif';
% % read data
% class_cnt = 40;
% train_cnt = 5;
% eachclass_cnt = 7;
% [X_train, X_test, Label_train, Label_test, row, col] = Readdata(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% 
% right = [];
% for PCA_component = 10 : 10 : 100
%     model = PCA(X_train, PCA_component);
%     traini = model.W' * (X_train - repmat(model.miu, 1, size(X_train, 2)));
%     testi = model.W' * (X_test - repmat(model.miu, 1, size(X_test, 2)));
%     predict = MultiClassSVM(traini, testi, Label_train);
%     right = [right mean(double(predict == Label_test))];
% end
% right

%% =============== Part 9: LDA + SVM ================
% orl
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\ORL56_46\orl';
% suffix = '.bmp';
% Yale
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\face10080\subject';
% suffix = '.bmp';
% AR
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\AR_Gray_50by40\AR';
% suffix = '.tif';
% FERET
% address = 'C:\Users\lenovo\Desktop\GradeTwoSemesterTwo\ML\data\FERET_80\ff';
% suffix = '.tif';
% % read data
% class_cnt = 40;
% train_cnt = 5;
% eachclass_cnt = 7;
% [X_train, X_test, Label_train, Label_test, row, col] = Readdata(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% 
right = [];
for LDA_component = 1 : 4 : 40
    model = LDA(X_train, Label_train, LDA_component);
    traini = model.W' * X_train;
    testi = model.W' * X_test;
    predict = MultiClassSVM(traini, testi, Label_train);
    right = [right mean(double(predict == Label_test))];
end
right