%Inputs: -V: the matrix of eigenvectors sorted by eigenvalue with
%        decending order
%        -X_train: training set
%        -X_test: testing set
%        -Label_train: the labels of training set
%        -Label_test: the labels of testing set
%        -Mean: the mean vector of training set
%        -K: the K nearest neighbors algorithm's parameter
%        -k: data's dimension after projection
%Outputs: -rate: the recognition rate
% Author: Yang Zheng
% Date: 2022.3.21
function rate = PCArecognize(V, X_train, X_test, Label_train, Label_test, Mean, K, k)
    %% get the matrix for projecting
    P = [];
    for i = size(V, 1) : -1 : (size(V, 1) - k + 1) % because the eigenvalues with descending order
        P = [P; V(i, :)];
    end
    %% project the datas
    [~, col] = size(X_test);
    [~, c] = size(X_train);
    Y_train = P * (X_train - repmat(Mean, 1, c));
    Y_test = P * (X_test - repmat(Mean, 1, col));
    %% nearest neighbor algorithm
    test_label = Kth_neighbor(Y_train, Y_test, Label_train, K); 
    %% calculate recognition rate
    right = 0;
    for i = 1 : col
        if (test_label(1, i) == Label_test(1, i))
            right = right + 1;
        end
    end
    rate = right / col;
end