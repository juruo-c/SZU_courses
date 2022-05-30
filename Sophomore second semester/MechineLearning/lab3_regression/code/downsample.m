function X = downsample(X, n, m)
    % Inputs:
    %       -X: original matrix, [on x om]
    %       -n, m: the downsampled matrix's dimension, [int]
    % Outputs:
    %       -X: the downsampled matrix
    % Author: Yang Zheng
    % Date: 2022. 4. 4
    [on, om] = size(X);
    stepn = ceil(on / n);
    stepm = ceil(om / m);
    temp = (X(1 : stepn : on, :));
    X = temp(:, 1 : stepm : om);
end