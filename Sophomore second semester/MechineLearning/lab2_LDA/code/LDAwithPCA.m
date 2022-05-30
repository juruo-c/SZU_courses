% Inputs: -V: the matrix of eigenvector abtained by PCA
%         -PCA_k: data's dimension after PCA projecting
%         -LDA_k: data's dimension after LDA projecting
%         -X_train: training set
%         -X_test: testing set
%         -Label_train: Labels of training set
%         -Label_test: Labels of testing set
%         -K: the K nearest neighbor algorithm's parameter
%         -Mean: the mean vector of training set
%         -class_cnt: the number of classes
% Outputs: -rate: the recognition rate
% Author: Yang Zheng
% Date: 2022.3.23
function rate = LDAwithPCA(V, PCA_k, LDA_k, X_train, X_test, Label_train, Label_test, K, Mean, class_cnt)
    %% get the matrix for PCA projecting
    P = [];
    for i = size(V, 1) : -1 : (size(V, 1) - PCA_k + 1) % because the eigenvalues with descending order
        P = [P; V(i, :)];
    end
    %% PCA project datas
    [~, test_siz] = size(X_test);
    [~, train_siz] = size(X_train);
    Y_train = P * (X_train - repmat(Mean, 1, train_siz));
    Y_test = P * (X_test - repmat(Mean, 1, test_siz));
    %% LDA
    [W, D] = Multi_Class_LDA(Y_train, Label_train, class_cnt);
    %% get the matrix for LDA projecting
    [~,I] = sort(diag(D), "descend");
    W = W(:, I(1 : LDA_k))';
    %% LDA project datas
    Y_train = W * Y_train;
    Y_test = W * Y_test;
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