function theta = Ridge_regression(X, y, lambda)
    % Inputs:
    %       -X: training set, [data_num x dimension]
    %       -y: real value of training set, [data_num x 1]
    % Outputs:
    %       -theta: the parameter vector, [dimension x 1]           
    % Author: Yang Zheng
    % Date: 2022. 4. 6
    n = size(X, 2);
    I = eye(n);
    I(1, 1) = 0;
    theta = (X' * X + lambda * I)^-1 * X' * y;
end