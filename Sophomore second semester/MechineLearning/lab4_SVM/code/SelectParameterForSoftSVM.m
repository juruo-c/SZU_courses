function C = SelectParameterForSoftSVM(X, y)
    [m, ~] = size(X);
    y(y == 0) = -1;

    minerror = 1000;
    C_list = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];
    for i = 1 : 8
        error = 0;
        for j = 1 : m
            X_train = [X(1:j-1, :); X(j + 1:m, :)];
            y_train = [y(1:j-1, :); y(j + 1:m, :)];
            model = soft_margin_SVM(X_train, y_train, C_list(i));
            predict = -sign(X(j, :) * model.w + model.b);
            error = error + (y(j) == predict);
        end
        error = error / m;
        if (error < minerror)
            minerror = error;
            C = C_list(i);
        end
    end
end
