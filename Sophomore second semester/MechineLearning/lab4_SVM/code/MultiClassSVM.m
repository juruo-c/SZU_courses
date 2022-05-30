function prediction = MultiClassSVM(X_train, X_test, Label_train)
    class = unique(Label_train);
    K = size(class, 2);
    test_siz = size(X_test, 2);
    X_test = X_test';

    models = [];
    for i = 1 : K
        for j = i + 1 : K
            classi_idx = find(Label_train == i);
            classj_idx = find(Label_train == j);
            idx = [classi_idx classj_idx];
            y = Label_train(idx);
            y(y == i) = 1;
            y(y == j) = -1;
            model = svmTrain(X_train(:, idx)', y', i, j);
            models = [models model];
        end
    end
    
    prediction = [];
    for test = 1 : test_siz
        token = zeros(K, 1);
        for i = 1 : K * (K - 1) / 2
            model = models(i);
            h = sign(X_test(test, :) * model.w + model.b);
            if (h == 1)
                token(model.C1) = token(model.C1) + 1;
            else
                token(model.C2) = token(model.C2) + 1;
            end
        end

        [~, index] = sort(token, 'descend');
        prediction = [prediction index(1)];
    end
    
end