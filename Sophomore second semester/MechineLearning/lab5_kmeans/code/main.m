%% ================= Part 1: kmeans ====================
% load('ex7data2.mat');
% k = 3;
% 
% scatter(X(:,1), X(:,2), 15, 'blue','filled');
% 
% pause;
% 
% [centroids, idx] = kmeans(X, k, true);
% 
% fprintf('Program paused. Press enter to continue.\n');
% pause;

%% ================= Part 2: kmeans with PCA in face ====================
% % Yale
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\Yale_face10080\face10080\subject';
% suffix = '.bmp';
% ORL
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\ORL56_46\ORL56_46\orl';
% suffix = '.bmp';
% AR
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\AR_Gray_50by40\AR_Gray_50by40\AR';
% suffix = '.tif';

% k = 3;
% class_cnt = 3;
% train_cnt = 10;
% eachclass_cnt = 10;
% 
% [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% model = PCA(X_train, 2);
% X = (X_train - repmat(model.miu, 1, size(X_train, 2)))' * model.W;
% 
% m = size(X, 1);
% scatter(X(1:m/k,1), X(1:m/k,2), 15, 'blue','filled');
% hold on;
% scatter(X(m/k+1:2*m/k,1), X(m/k+1:2*m/k,2), 15, 'red','filled');
% hold on;
% scatter(X(2*m/k+1:3*m/k,1), X(2*m/k+1:3*m/k,2), 15, 'green','filled');
% hold on;
% 
% % for i = 1 : class_cnt
% %     for j = m / class_cnt * (i-1) + 1 : m / class_cnt * i
% %         str = num2str(i * 1000 + j - m / class_cnt * (i - 1));
% %         text(X(j, 1), X(j, 2), str);
% %     end
% % end
% pause;
% 
% [centroids, idx] = kmeans(X, k, true);
% fprintf('Program paused. Press enter to continue.\n');
% pause;

%% ================= Part 3: kmeans with PCA in object ====================
% coil
% address = 'D:\Grade Two second semester\mechine learning\report\PCA\database\coil-20-proc\obj';
% suffix = '.png';
% 
% k = 3;
% class_cnt = 3;
% train_cnt = 71;
% eachclass_cnt = 71;
% 
% [X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% model = PCA(X_train, 3);
% X = (X_train - repmat(model.miu, 1, size(X_train, 2)))' * model.W;
% 
% m = size(X, 1);
% figure;
% scatter3(X(1:m/k,1), X(1:m/k,2), X(1:m/k,3), 15, 'blue','filled');
% hold on;
% scatter3(X(m/k+1:2*m/k,1), X(m/k+1:2*m/k,2), X(m/k+1:2*m/k,3), 15, 'red','filled');
% hold on;
% scatter3(X(2*m/k+1:3*m/k,1), X(2*m/k+1:3*m/k,2), X(2*m/k+1:3*m/k,3), 15, 'green','filled');
% hold on;
% 
% for i = 1 : class_cnt
%     for j = m / class_cnt * (i-1) + 1 : m / class_cnt * i
%         str = num2str(i * 1000 + j - m / class_cnt * (i - 1));
%         text(X(j, 1), X(j, 2), X(j, 3), str);
%     end
% end
% 
% [centroids, idx] = kmeans(X, k, true);
% 
% figure;
% scatter3(X(idx == 1,1), X(idx == 1,2), X(idx == 1,3), 15, 'blue','filled');
% hold on;
% scatter3(X(idx == 2,1), X(idx == 2,2), X(idx == 2,3), 15, 'red','filled');
% hold on;
% scatter3(X(idx == 3,1), X(idx == 3,2), X(idx == 3,3), 15, 'green','filled');
% hold on;
% 
% fprintf('Program paused. Press enter to continue.\n');
% pause;

%% ================= Part 4: kmeans precision in different datas ====================
% % Yale
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\Yale_face10080\face10080\subject';
% suffix = '.bmp';
% ORL
% address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\ORL56_46\ORL56_46\orl';
% suffix = '.bmp';
% AR
address = 'D:\Grade Two second semester\mechine learning\report\LDA\database\AR_Gray_50by40\AR_Gray_50by40\AR';
suffix = '.tif';

k = 5;
class_cnt = 4;
train_cnt = 26;
eachclass_cnt = 26;

[X_train, X_test, Label_train, Label_test, row, col] = Read_data(address, suffix, class_cnt, train_cnt, eachclass_cnt);
% model = PCA(X_train, 2);
% X = (X_train - repmat(model.miu, 1, size(X_train, 2)))' * model.W;
X = X_train';

% scatter(X(1:m/k,1), X(1:m/k,2), 15, 'blue','filled');
% hold on;
% scatter(X(m/k+1:2*m/k,1), X(m/k+1:2*m/k,2), 15, 'red','filled');
% hold on;
% scatter(X(2*m/k+1:3*m/k,1), X(2*m/k+1:3*m/k,2), 15, 'green','filled');
% hold on;

% for i = 1 : class_cnt
%     for j = m / class_cnt * (i-1) + 1 : m / class_cnt * i
%         str = num2str(i * 1000 + j - m / class_cnt * (i - 1));
%         text(X(j, 1), X(j, 2), str);
%     end
% end

[centroids, idx] = kmeans(X, k, true);

ClustersClass = zeros(k, 1);
for i = 1 : k
    cnt = zeros(class_cnt, 1);
    label = Label_train(idx == i);
    for j = 1 : size(label, 2)
        cnt(label(j), 1) = cnt(label(j), 1) + 1;
    end
    [~, index] = sort(cnt, 'descend');
    ClustersClass(i) = index(1);
end

right = 0;
for i = 1 : k
    label = Label_train(idx == i);
    for j = 1 : size(label, 2)
        if (label(j) == ClustersClass(i))
            right = right + 1;
        end
    end
end
right / (class_cnt * train_cnt)
