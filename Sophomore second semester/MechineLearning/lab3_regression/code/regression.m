function theta = regression(X, y)
    % Inputs:
    %       -X: training set, [data_num x dimension]
    %       -y: real value of training set, [data_num x 1]
    % Outputs:
    %       -theta: the parameter vector, [dimension x 1]           
    % Author: Yang Zheng
    % Date: 2022. 4. 4
    theta = (X' * X)^-1 * X' * y;
end