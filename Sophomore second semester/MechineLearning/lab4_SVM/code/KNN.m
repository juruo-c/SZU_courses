% Inputs: -X_train: training set matrix 
%         -X_test: testing set matrix
%         -Label: the labels of testing set 
%         -K: the K nearest neighbor algorithm's parameter
% Outputs: -test_Label: the predicted labels of testing set 
% Author: Yang Zheng
% Date: 2022.3.21
function test_Label = KNN(X_train, X_test, Label, K)
    test_Label = [];
    [~, train_siz] = size(X_train);
    [~, test_siz] = size(X_test);
    for i = 1 : test_siz
        %% calculate dis
        dis = [];
        for j = 1 : train_siz
            dis(j) = sqrt(sum((X_train(:, j) - X_test(:, i)).^2));
        end
        %% sort dis, pick first k labels and count the labels
        [~, index] = sort(dis);
        labels_cnt = zeros(1, length(Label));
        for j = 1 : K
            tmp = Label(index(j));
            labels_cnt(tmp) = labels_cnt(tmp) + 1;
        end
        %% sort the labels count
        [~, index] = sort(labels_cnt, "descend");
        test_Label(i) = index(1);
    end
end