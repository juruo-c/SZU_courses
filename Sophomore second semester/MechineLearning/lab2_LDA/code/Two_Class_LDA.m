% Inputs: -X: the training set 
%         -X_Label: the label of training set
% Outputs: -w: the vector for reducing dimension
% Author: Yang Zheng
% Date: 2022.3.21
function [w] = Two_Class_LDA(X, X_Label)
    [~, col] = size(X);
    X1 = []; % class one
    X2 = []; % class two
    N1 = 0; % number of class one
    N2 = 0; % number of class two
    for i = 1 : col 
        if (X_Label(i) == 1)
            X1 = [X1 X(:, i)];
            N1 = N1 + 1;
        else
            X2 = [X2 X(:, i)];
            N2 = N2 + 1;
            break;
        end
    end
    %% each class mean vector
    mean1 = mean(X1, 2);
    mean2 = mean(X2, 2);
    %% calculate Sw
    S1 = (X1 - repmat(mean1, 1, N1)) * (X1 - repmat(mean1, 1, N1))' / N1;
    S2 = (X2 - repmat(mean2, 1, N2)) * (X2 - repmat(mean2, 1, N2))' / N2;
    Sw = S1 + S2;
    %% calcutlate w
    w = Sw^(-1) * (mean1 - mean2);
    w = w / norm(w);
end