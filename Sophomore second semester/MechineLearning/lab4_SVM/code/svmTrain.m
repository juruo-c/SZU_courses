function [model] = svmTrain(X, y, C1, C2)
    [m, ~] = size(X);

    %% build Q
    Q = zeros(m, m);
    for i = 1 : m
        for j = 1 : m
            Q(i, j) = y(i) * y(j) * X(i, :) * X(j, :)';
        end
    end
    
    alpha = quadprog(Q, ones(m, 1) * -1, [], [], y', 0, zeros(m, 1), []);

    %% build model
    index = alpha > 0;
    model.X = X(index, :);
    model.y = y(index);
    model.alpha = alpha(index);
    model.w = ((alpha .* y)' * X)';
    model.b = mean(model.y - model.X * model.w);
    model.C1 = C1;
    model.C2 = C2;
end