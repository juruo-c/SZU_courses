% input: training set, first kth dimensions for chosing
% output: the matrix for reducing dimension, the mean vector of training set
function [P, Mean] = PCA(X_train, k_dimensions)
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
    for i = size(V, 1) : -1 : (size(V, 1) - k_dimensions + 1) % because the eigenvalues with descending order
        P = [P; V(i, :)];
    end
end
