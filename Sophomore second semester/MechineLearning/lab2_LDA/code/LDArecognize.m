% Inputs: -W: the eigenvector matrix for reducing dimension
%         -D: the eigenvalue matrix
%         -X_train: training set 
%         -X_test: testing set 
%         -Label_train: the labels of training set
%         -Label_test: the labels of testing set 
%         -K: the K nearest neighbor algorithm's parameter
%         -k: data's dimension after projection
% Outputs: -rate: the recognition rate
% Author: Yang Zheng
% Date: 2022.3.21
function rate = LDArecognize(W, D, X_train, X_test, Label_train, Label_test, K, k)
    %% get the matrix for projecting
    [~,I] = sort(diag(D), "descend");
    W = W(:, I(1 : k))';
    %% project the date to k dimension
    [~, test_siz] = size(X_test);
    Y_train = W * X_train;
    Y_test = W * X_test;
    %% Kth nearest neighbor algorithm
    test_label = Kth_neighbor(Y_train, Y_test, Label_train, K);
    %% calculate recognition rate
    right = 0;
    for i = 1 : test_siz
        if (test_label(i) == Label_test(i))
            right = right + 1;
        end
    end
    rate = right / test_siz;
end