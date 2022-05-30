clear;
close all;

% % Yale
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\Yale_face10080\face10080\subject';
% suffix = '.bmp';
% ORL
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\ORL56_46\ORL56_46\orl';
% suffix = '.bmp';
%FERET
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\FERET_80\FERET_80\ff';
% suffix = '.tif';
% AR
address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\AR_Gray_50by40\AR_Gray_50by40\AR';
suffix = '.tif';

class_cnt = 100;      % the number of classes
train_cnt = 20;       % the number of training samples of each class
eachclass_cnt = 26;   % the number of samples of each class
n = 2; m = 2;         % the dimension fo downsampled images
image_row = 50;
image_col = 40;

%% predict a simple sample
% data = load('data.txt');
% X = data(:, 1:2);
% [m, ~] = size(X);
% X = [ones(m, 1) X];
% y = data(:, 3);
% theta = regression(X(1:35, :), y(1:35));
% y_p = zeros(m, 1);
% y(36 : m)
% for i = 36 : m
%     y_p(i) = X(i, :) * theta;
% end
% y_p(36 : m)

%% LRC recognization rate
% [X_train, X_test, Label_train, Label_test] = Read_data_with_downsample(address, suffix, class_cnt, train_cnt, eachclass_cnt, n, m);
% rate = LRC(X_train, X_test, Label_train, Label_test)

%% leave one out
% [X_train, X_test, Label_train, Label_test] = Read_data_with_downsample(address, suffix, class_cnt, train_cnt, eachclass_cnt, n, m);
% X = [X_train X_test];
% label = [Label_train Label_test];
% siz = size(X, 2);
% rate = 0;
% for i = 1 : siz
%     temp_X = [X(:, 1 : i - 1) X(:, i + 1 : siz)];
%     label_x = [label(:, 1 : i - 1) label(:, i + 1 : siz)];
%     rate = rate + LRC(temp_X, X(:, i), label_x, label(i));
% end
% rate = rate / siz

%% ridge regression
% data = load('data.txt');
% X = data(:, 1:2);
% [m, ~] = size(X);
% X = [ones(m, 1) X];
% y = data(:, 3);
% lambda = [0.001 : 1 : 100];
% error = zeros(length(lambda), 1);
% for i = 1 : length(lambda)
%     y_p = zeros(m, 1);
%     theta = Ridge_regression(X(1:35, :), y(1:35), lambda(i));
%     for j = 36 : m
%         y_p(j) = X(j, :) * theta;
%     end
%     error(i) = sum(sqrt((y - y_p).^2));
% end
% plot(lambda, error);

%% MLRC
[X_train, X_test, Label_train, Label_test] = MLRC_ReadandPre(address, suffix, class_cnt, train_cnt, eachclass_cnt, image_row, image_col, n, m);
test_siz = size(X_test,2);
right = 0;
for i = 1 : test_siz
    dj = zeros(1, n * m);
    cj = zeros(1, n * m);
    for j = 1 : n * m
        y = X_test(:, i, j);
        d = zeros(1, class_cnt);
        for k = 1 : class_cnt 
            X = X_train(:, find(Label_train(:, :, j) == k), j);
            y_p = X * (X' * X)^-1 * X' * y;
            d(k) = sqrt(sum((y_p-y).^2));
        end
        [~, I] = sort(d);
        dj(j) = d(1);
        cj(j) = I(1);
    end
    [~, I] = sort(dj);
    if (cj(I(1)) == Label_test(1, i, 1))
        right = right + 1;
    end
end
rate = right / test_siz

