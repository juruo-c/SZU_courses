function C = SelectParameterForHardKernelSVM(X, y)
    [m, ~] = size(X);

    minerror = 1000;
    sigma_list = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];
    for i = 1 : 8
        error = 0;
        for j = 1 : m
            X_train = [X(1:j-1, :); X(j + 1:m, :)];
            y_train = [y(1:j-1, :); y(j + 1:m, :)];
            model = hard_margin_kernel_SVM(X_train, y_train, @(x1, x2)gaussianKernel(x1, x2, sigma_list(i)));
            predict = svmPredict(model, X(j, :));
            error = error + (y(j) == predict);
        end
        error = error / m;
        if (error < minerror)
            minerror = error;
            C = C_list(i);
        end
    end
end
