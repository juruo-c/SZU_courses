% Inputs: -X: the training set
%         -X_Label: the label of training set
%         -class_cnt: number of classes
% Outputs: -W: the eigenvector matrix for projecting datas
%          -D: the eigenvalue matrix
% Author: Yang Zheng
% Date: 2022.3.21
function [W, D] = Multi_Class_LDA(X, X_Label, class_cnt)
    [feature_siz, sample_siz] = size(X);
    N = zeros(1, class_cnt); % the size of each class
    for i = 1 : sample_siz
        N(X_Label(i)) = N(X_Label(i)) + 1;
    end
    %% calculate Sw
    means = []; % mean of each class
    Sw = zeros(feature_siz, feature_siz);
    tmp = 1;
    for i = 1 : class_cnt
        tmp_X = X(:, tmp : tmp + N(i) - 1);
        means = [means mean(tmp_X, 2)];
        S = (tmp_X - repmat(means(:, i), 1, N(i))) * (tmp_X - repmat(means(:, i), 1, N(i)))' / N(i);
        Sw = Sw + S;
        tmp = tmp + N(i);
    end
    %% calculate Sb
    Sb = zeros(feature_siz, feature_siz);
    miu = mean(X, 2); % mean of all training samples
    for i = 1 : class_cnt
        Sb = Sb + (means(:, i) - miu) * (means(:, i) - miu)' * N(i);
    end
    %% calculate eigen vector and W
    [W, D] = eig(Sb, Sw);
    
%     V = V';
%     % eigenvector normalization
%     for i = 1 : size(V, 1)
%         V(i, :) = V(i, :) / norm(V(i, :));
%     end
%     W = [];
%     for i = size(V, 1) : -1 : (size(V, 1) - k_dimensions + 1) % because the eigenvalues with descending order
%         W = [W; V(i, :)];
%     end
end