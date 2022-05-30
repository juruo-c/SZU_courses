% Inputs: -X_train: training set
%         -k_dimensions: data dimension after projection
% Outputs: -V: the matrix of eigenvectors sorted by eigenvalue with
%          decending order
%          -Mean: the mean vector of training set
% Author: Yang Zheng
% Date: 2022.3.21
function [V, Mean] = PCA(X_train)
    P = []; % the result
    [~, col] = size(X_train);
    %% PCA
    Mean = mean(X_train, 2);
    X_mean = repmat(Mean, 1, col);
    X = X_train - X_mean; % centralized
    C = X' * X / col;
    [V, ~] = eig(C);
    V = X * V;
    V = V';
    % eigenvector normalization
    for i = 1 : size(V, 1)
        V(i, :) = V(i, :) / norm(V(i, :));
    end
end
