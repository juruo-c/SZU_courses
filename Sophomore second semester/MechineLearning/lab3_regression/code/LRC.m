function rate = LRC(X, Y, label_x, label_y)
    % Inputs:
    %       -X: training set, [dimension x train_num]
    %       -Y: testing set, [dimension x test_num]
    %       -label_x: label of training set, [1 x train_num]
    %       -label_y: label of testing set, [1 x test_num]
    % Outputs:
    %       -rate: the recognization rate, [double]           
    % Author: Yang Zheng
    % Date: 2022. 4. 4
    [~, test_num] = size(Y);
    label = unique(label_x);
    N = size(label, 2);
    rate = 0;
    for i = 1 : test_num
        d = zeros(1, N);
        y = Y(:, i);
        for j = 1 : N
            Xj = X(:, find(label_x == j));
            y_p = Xj * (Xj' * Xj)^-1 * Xj' * y;
            d(j) = sqrt(sum((y_p-y).^2));
        end
        [~, I] = sort(d);
        if (label_y(i) == I(1))
            rate = rate + 1;
        end
    end
    rate = rate / test_num;
end