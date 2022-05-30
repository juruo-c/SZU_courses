% input: the matrix for reducing dimension, training set, 
%        testing set, the labels of training set,
%        the labels of testing set, the mean vector of training set
% output: the recognition rate
function rate = recognize(P, X_train, X_test, Label_train, Label_test, Mean)
    [~, col] = size(X_test);
    [~, c] = size(X_train);
    Y_train = P * (X_train - repmat(Mean, 1, c));
    Y_test = P * (X_test - repmat(Mean, 1, col));
    %% nearest neighbor algorithm
    test_label = []; 
    for i = 1 : col
        min_dist = inf;
        id = 0;
        for j = 1 : c
            tmp = (Y_train(:, j) - Y_test(:, i)).^2;
            dist = sqrt(sum(tmp));
            if (dist < min_dist) 
                id = j;
                min_dist = dist;
            end
        end
        test_label(1, i) = Label_train(1, id);
    end
    %% calculate recognition rate
    right = 0;
    for i = 1 : col
        if (test_label(1, i) == Label_test(1, i))
            right = right + 1;
        end
    end
    rate = right / col;
end